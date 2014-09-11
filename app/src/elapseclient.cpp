#include <QStateMachine>
#include <QSignalTransition>
#include <QMessageBox>
#include <QDockWidget>
#include <QSettings>
#include <QxtLogger>
#include "pipeline.h"
#include "pluginmanager.h"
#include "deviceproxy.h"
#include "logview.h"
#include "batterymonitor.h"
#include "elapse/displayable.h"
#include "elapseclient.h"
#include "ui_elapseclient.h"

#define DEFAULT_ADDR    "192.168.2.2"

namespace elapse { namespace client {


/*!
 * Construct an ElapseClient as a child of the given \a parent widget.
 */
ElapseClient::ElapseClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElapseClient),
    logView(new log::LogView(this)),
    pluginManager(new plugin::Manager(this)),
    pipeline(new Pipeline(this)),
    proxy(new DeviceProxy(this)),
    batteryMonitor(new BatteryMonitor(this))
{
    ui->setupUi(this);
    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks);

    qxtLog->info("Using settings from", QSettings().fileName());
    createDefaultHardwareConfig();

    ui->buttonPlugins->setVisible(false);
    ui->buttonPlugins->setDefaultAction(ui->actionPlugins);
    ui->buttonConnect->setDefaultAction(ui->actionConnect);
    ui->connectedToolBar->setVisible(false);
    ui->connectedToolBar->addWidget(ui->spinnerStarting);

    connect(ui->autoConnect, &QCheckBox::toggled, [](bool checked){
        QSettings().setValue("auto-connect", checked);
    });
    ui->autoConnect->setChecked(QSettings().value("auto-connect").toBool());

    addDockWidgetFrom(batteryMonitor);

    connect(ui->actionLogView, SIGNAL(triggered(bool)),
            logView, SLOT(setVisible(bool)));
    connect(logView, SIGNAL(visibilityChanged(bool)),
            ui->actionLogView, SLOT(setChecked(bool)));

    connect(ui->actionPlugins, SIGNAL(triggered()),
            pluginManager, SLOT(loadElementsFromGui()));
    connect(pluginManager, SIGNAL(elementsLoaded(elapse::elements::ElementSetPtr)),
            pipeline, SLOT(setElements(elapse::elements::ElementSetPtr)));
    connect(pluginManager, SIGNAL(elementsLoaded(elapse::elements::ElementSetPtr)),
            SLOT(loadElementWidgets(elapse::elements::ElementSetPtr)));

    connect(pipeline, SIGNAL(error(QString)), SLOT(showErrorMessage(QString)));
    connect(proxy, SIGNAL(error(QString)), SLOT(showErrorMessage(QString)));

    buildStateMachine();
}

/*!
 * Destroy this ElapseClient.
 */
ElapseClient::~ElapseClient()
{
    delete ui;
}

void ElapseClient::showErrorMessage(QString message)
{
    if (!message.isEmpty())
        QMessageBox::warning(this, "Error", message);
}

void ElapseClient::warnBatteryLow()
{
    QMessageBox::warning(this, "Low battery",
                         "The device's battery is low. Power it off soon.");
}

void ElapseClient::maybeAutoConnect()
{
    if (QSettings().value("auto-connect").toBool())
        QMetaObject::invokeMethod(ui->actionConnect, "trigger", Qt::QueuedConnection);
}

/*!
 * \page elapseclient-fsm ElapseClient State Machine
 *
 * The behaviour of the ElapseClient is driven by the following state machine.
 *
 * @startuml{elapseclient-fsm.png}
 *
 * [*] -> Uninitialised
 * Uninitialised : enter / connectButton.disable()
 * Uninitialised : enter / loadPluginsFromSettings()
 * Uninitialised --> Disconnected : elementsLoaded / maybeAutoConnect()
 * Disconnected : enter / connectButton.enable()
 * Disconnected --> Connecting : connectButton / device.connect()
 *
 * Connecting : enter / spinner.run()
 * Connecting --> Disconnected : device.error
 * Connecting --> Connected : device.connected
 *
 * Connected : enter / showElementWidgets()
 * Connected : enter / configure()
 * Connected : exit / device.disconnect()
 * Connected : exit / hideElementWidgets()
 * Connected --> Disconnected : disconnect
 * Connected --> Disconnected : device.error
 *
 * state Connected {
 *      [*] -> Idle
 *      Idle -> Active : startStopButton
 *      Active -> Idle : startStopButton
 *      Active -> Idle : pipeline.error
 *      Active : enter / device.startStreaming()
 *      Active : enter / pipeline.start()
 *      Active : exit / device.stopStreaming()
 *      Active : exit / pipeline.stop()
 * }
 *
 * @enduml
 */
void ElapseClient::buildStateMachine()
{
    machine = new QStateMachine(this);
    machine->setGlobalRestorePolicy(QState::RestoreProperties);

    auto uninitialised = new QState(machine);
    auto disconnected = new QState(machine);
    auto connecting = new QState(machine);
    auto connected = new QState(machine);
    auto idle = new QState(connected);
    auto active = new QState(connected);

    machine->setInitialState(uninitialised);
    uninitialised->assignProperty(ui->actionConnect, "enabled", false);
    uninitialised->assignProperty(ui->groupConnect, "visible", false);
    uninitialised->assignProperty(ui->buttonPlugins, "visible", true);
    auto initialised = uninitialised->addTransition(pluginManager, SIGNAL(elementsLoaded(elapse::elements::ElementSetPtr)), disconnected);
    connect(uninitialised, SIGNAL(entered()), pluginManager, SLOT(loadElementsFromSettings()));
    connect(initialised, SIGNAL(triggered()), SLOT(maybeAutoConnect()));

    disconnected->addTransition(ui->actionConnect, SIGNAL(triggered()), connecting);

    connect(connecting, SIGNAL(entered()), SLOT(connectToDevice()));
    connecting->assignProperty(ui->spinnerConnecting, "running", true);
    connecting->assignProperty(ui->actionConnect, "enabled", false);
    connecting->assignProperty(ui->actionPlugins, "enabled", false);
    connecting->assignProperty(ui->autoConnect, "enabled", false);
    connecting->assignProperty(this, "cursor", QCursor(Qt::WaitCursor));
    connecting->addTransition(proxy, SIGNAL(error(QString)), disconnected);
    connecting->addTransition(proxy, SIGNAL(connected()), connected);

    connected->setInitialState(idle);
    connected->assignProperty(ui->centralWidget, "visible", false);
    connected->assignProperty(this, "dockWidgetsVisible", true);
    connected->assignProperty(ui->disconnectedToolBar, "visible", false);
    connected->assignProperty(ui->connectedToolBar, "visible", true);
    connected->assignProperty(ui->actionConnect, "text", "&Disconnect");
    connected->assignProperty(ui->actionConnect, "toolTip", "Disconnect from the device");
    connected->assignProperty(ui->actionPlugins, "enabled", false);
    connected->addTransition(ui->actionConnect, SIGNAL(triggered()), disconnected);
    connected->addTransition(proxy, SIGNAL(error(QString)), disconnected);
    connect(connected, SIGNAL(entered()), SLOT(stop())); // in case still running
    connect(connected, SIGNAL(entered()), SLOT(configure()));
    connect(connected, SIGNAL(exited()), SLOT(unconfigure()));
    connect(connected, SIGNAL(exited()), proxy, SLOT(disconnect()));

    auto beginCapture = idle->addTransition(ui->actionCapture, SIGNAL(triggered()), active);

    active->assignProperty(ui->actionCapture, "text", "Stop");
    active->assignProperty(ui->actionCapture, "icon", QIcon::fromTheme("media-playback-stop"));
    active->assignProperty(ui->actionSetCaptureInfo, "enabled", false);
    connect(active, SIGNAL(entered()), SLOT(start()));
    connect(active, SIGNAL(exited()), SLOT(stop()));
    connect(beginCapture, SIGNAL(triggered()), ui->spinnerStarting, SLOT(start()));
    connect(pipeline, SIGNAL(started()), ui->spinnerStarting, SLOT(stop()));
    connect(active, SIGNAL(exited()), ui->spinnerStarting, SLOT(stop()));
    active->addTransition(ui->actionCapture, SIGNAL(triggered()), idle);
    active->addTransition(pipeline, SIGNAL(error(QString)), idle);

    machine->start();
}

/**
 * Connect to the appropriate device address depending on whether the
 * DataSource::isOfflineSource().
 */
void ElapseClient::connectToDevice()
{
    auto elements = pipeline->elements();
    Q_ASSERT(elements);
    if (elements->dataSource->isOfflineSource()) {
        proxy->connectTo("localhost");
    } else {
        QString host = QSettings().value("host", DEFAULT_ADDR).toString();
        proxy->connectTo(host);
    }
}

/*!
 * Add widgets from Displayable elements.
 */
void ElapseClient::loadElementWidgets(elements::ElementSetPtr elements)
{
    for (auto &element : elements->allElements())
        addDockWidgetFrom(element.data());
}

/*!
 * If the given \a object implements the Displayable interface, create a
 * QDockWidget containing the exported widget. The dock widget is initialy
 * hidden.
 */
void ElapseClient::addDockWidgetFrom(QObject *object)
{
    QString className = object->metaObject()->className();
    className = className.mid(className.lastIndexOf(':') + 1)
                         .replace(QRegExp("([a-z])([A-Z])"), "\\1 \\2");

    auto displayable = dynamic_cast<Displayable*>(object);
    if (!displayable) {
        qxtLog->trace(className, "is not displayable");
        return;
    }

    qxtLog->trace("Adding widget provided by", className);

    auto widget = displayable->getWidget();
    Q_ASSERT(widget);

    auto dockWidget = new QDockWidget(className, this);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    dockWidget->setWidget(widget);
    addDockWidget(Qt::TopDockWidgetArea, dockWidget);
    dockWidget->hide();

    connect(object, SIGNAL(destroyed()), dockWidget, SLOT(deleteLater()));
}

bool ElapseClient::dockWidgetsVisible() const
{
    auto dockWidget = findChild<QDockWidget*>("", Qt::FindDirectChildrenOnly);
    return dockWidget && dockWidget->isVisible();
}

void ElapseClient::setDockWidgetsVisible(bool visible)
{
    bool offlineSource = pipeline->elements()->dataSource->isOfflineSource();
    auto dockWidgets = findChildren<QDockWidget*>("", Qt::FindDirectChildrenOnly);
    for (auto dockWidget : dockWidgets) {
        if (dockWidget->windowTitle() == "BatteryMonitor")
            dockWidget->setVisible(visible && !offlineSource);
        else
            dockWidget->setVisible(visible);
    }
}

/*!
 * Write the default hardware configuration to the settings file. This will
 * not overwrite any existing settings.
 */
void ElapseClient::createDefaultHardwareConfig()
{
    QSettings settings;

    auto setDefault = [&](const QString &prop, QVariant val) {
        if (!settings.contains(prop))
            settings.setValue(prop, val);
    };

    settings.beginGroup("hardware");

    setDefault("eeg/useRefElec", true);
    setDefault("eeg/sampleRate", 250);
    setDefault("eeg/samplesPerChunk", 20);
    setDefault("eeg/all-channels/enabled", true);
    setDefault("eeg/all-channels/gain", hardware::EegChannel::x24);
    setDefault("eeg/all-channels/inputMux", hardware::EegChannel::Normal);

    settings.endGroup();
}

/*!
 * Read the hardware configuration from the settings file and apply it to the
 * device.
 */
void ElapseClient::applyHardwareConfig()
{
    QSettings settings;

    settings.beginGroup("hardware");
    std::vector<std::pair<const char*, QObject*>> sensors = {
        { "eeg",    proxy->device()->eeg() },
        { "camera", proxy->device()->camera() },
        { "imu",    proxy->device()->imu() },
        { "battery",proxy->device()->battery() },
    };
    for (auto &s : sensors) {
        const char *name = s.first;
        QObject *sensor = s.second;
        settings.beginGroup(name);

        qxtLog->trace(name);
        for (auto &prop : settings.childKeys()) {
            auto val = settings.value(prop);
            qxtLog->trace("  ", prop, "=", val);
            sensor->setProperty(prop.toLatin1().constData(), val);
        }

        // Special case for EEG channels
        auto eeg = proxy->device()->eeg();
        if (sensor == eeg) {
            settings.beginGroup("all-channels");
            qxtLog->trace("  all");
            QVariantMap allChannels;
            for (auto &prop : settings.childKeys()) {
                auto val = settings.value(prop);
                qxtLog->trace("    ", prop, "=", val);
                allChannels.insert(prop, val);
            }
            eeg->setAllChannels(allChannels);
            settings.endGroup();

            settings.beginGroup("channel");
            for (auto &channel : settings.childGroups()) {
                uint ch = channel.toUInt();
                qxtLog->trace("  ", ch);
                settings.beginGroup(channel);
                for (auto &prop : settings.childKeys()) {
                    auto val = settings.value(prop);
                    qxtLog->trace("    ", prop, "=", val);
                    eeg->channel(ch)->setProperty(prop.toLatin1().constData(), val);
                }
                settings.endGroup();
            }
            settings.endGroup();
        }
        settings.endGroup();
    }
    settings.endGroup();
}

/*!
 * Configure the client. Configuration of the hardware is done in start().
 */
void ElapseClient::configure()
{
    QSettings settings;

    settings.beginGroup("pipeline/window");
    pipeline->setWindowLength(settings.value("length", 1000).toUInt());
    pipeline->setWindowStep(settings.value("step", 500).toUInt());
    settings.endGroup();

    qxtLog->debug("Notifying server that our address is", proxy->localAddress());
    proxy->device()->setClientAddress(proxy->localAddress());

    auto battery = proxy->device()->battery();
    batteryMonitor->setBattery(battery);
    connect(battery, SIGNAL(batteryLow()), SLOT(warnBatteryLow()));
    if (battery->isLow())
        warnBatteryLow();

    connect(ui->actionSetCaptureInfo, SIGNAL(triggered()),
            pipeline->elements()->dataSink.data(), SLOT(getCaptureInfo()));
}

/*!
 * Clean up client configuration to avoid dangling references.
 */
void ElapseClient::unconfigure()
{
    batteryMonitor->setBattery(nullptr);
    disconnect(ui->actionSetCaptureInfo, SIGNAL(triggered()), 0, 0);
}

/*!
 * Start data capture.
 */
void ElapseClient::start()
{
    pipeline->start();

    // Must be done here rather than in configure() because some
    // OfflineDataSources need to be start()ed before they can be configured.
    applyHardwareConfig();

    auto cfg = proxy->getDeviceConfig();
    pipeline->setDeviceConfig(cfg);

    proxy->device()->startStreaming();
}

/*!
 * Stop data capture.
 */
void ElapseClient::stop()
{
    proxy->device()->stopStreaming();
    pipeline->stop();
}

}} // namespace elapse::client
