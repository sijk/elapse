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

#define DEFAULT_ADDR    "overo.local"


/*!
 * Construct an ElapseClient as a child of the given \a parent widget.
 */
ElapseClient::ElapseClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElapseClient),
    logView(new LogView(this)),
    pluginManager(new PluginManager(this)),
    pipeline(new Pipeline(this)),
    proxy(new DeviceProxy(this)),
    batteryMonitor(new BatteryMonitor(this))
{
    ui->setupUi(this);
    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks);

    qxtLog->info("Using settings from", QSettings().fileName());

    ui->buttonPlugins->setVisible(false);
    ui->buttonPlugins->setDefaultAction(ui->actionPlugins);
    ui->buttonConnect->setDefaultAction(ui->actionConnect);
    ui->connectedToolBar->setVisible(false);
    ui->connectedToolBar->addWidget(ui->spinnerStarting);

    addDockWidgetFrom(batteryMonitor);

    connect(ui->deviceAddress, SIGNAL(returnPressed()),
            ui->actionConnect, SLOT(trigger()));

    connect(ui->actionLogView, SIGNAL(triggered(bool)),
            logView, SLOT(setVisible(bool)));
    connect(logView, SIGNAL(visibilityChanged(bool)),
            ui->actionLogView, SLOT(setChecked(bool)));

    connect(ui->actionPlugins, SIGNAL(triggered()),
            pluginManager, SLOT(loadElementsFromGui()));
    connect(pluginManager, SIGNAL(elementsLoaded(ElementSetPtr)),
            pipeline, SLOT(setElements(ElementSetPtr)));
    connect(pluginManager, SIGNAL(elementsLoaded(ElementSetPtr)),
            SLOT(loadElementWidgets(ElementSetPtr)));
    connect(pluginManager, SIGNAL(elementsLoaded(ElementSetPtr)),
            SLOT(fillDeviceAddress()));

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
    if (QSettings().value("auto-connect", true).toBool())
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
    auto initialised = uninitialised->addTransition(pluginManager, SIGNAL(elementsLoaded(ElementSetPtr)), disconnected);
    connect(uninitialised, SIGNAL(entered()), pluginManager, SLOT(loadElementsFromSettings()));
    connect(initialised, SIGNAL(triggered()), SLOT(maybeAutoConnect()));

    disconnected->addTransition(ui->actionConnect, SIGNAL(triggered()), connecting);

    connect(connecting, &QState::entered,
            [=]{ proxy->connectTo(ui->deviceAddress->text()); });
    connecting->assignProperty(ui->spinnerConnecting, "running", true);
    connecting->assignProperty(ui->actionConnect, "enabled", false);
    connecting->assignProperty(ui->actionPlugins, "enabled", false);
    connecting->assignProperty(this, "cursor", QCursor(Qt::WaitCursor));
    connecting->addTransition(proxy, SIGNAL(error(QString)), disconnected);
    connecting->addTransition(proxy, SIGNAL(connected()), connected);

    connected->setInitialState(idle);
    connected->assignProperty(ui->centralWidget, "visible", false);
    connected->assignProperty(this, "dockWidgetsVisible", true);
    connected->assignProperty(ui->disconnectedToolBar, "visible", false);
    connected->assignProperty(ui->connectedToolBar, "visible", true);
    connected->assignProperty(ui->actionConnect, "text", "&Disconnect");
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

/*!
 * Add widgets from Displayable elements.
 */
void ElapseClient::loadElementWidgets(ElementSetPtr elements)
{
    foreach (auto &element, elements->allElements())
        addDockWidgetFrom(element.data());
}

/*!
 * Fill in the device address entry appropriately depending on whether the
 * DataSource::isOfflineSource().
 */
void ElapseClient::fillDeviceAddress()
{
    auto elements = pipeline->elements();
    Q_ASSERT(elements);

    if (elements->dataSource->isOfflineSource()) {
        qxtLog->debug(elements->dataSource->metaObject()->className(),
                      "is an offline data source");
        ui->deviceAddress->setText("localhost");
        ui->deviceAddress->setEnabled(false);
    } else {
        qxtLog->debug(elements->dataSource->metaObject()->className(),
                      "is an online data source");
        auto defaultAddr = QSettings().value("host", DEFAULT_ADDR).toString();
        auto address = ui->deviceAddress->text();
        if (address.isEmpty() || address == "localhost")
            ui->deviceAddress->setText(defaultAddr);
        ui->deviceAddress->setEnabled(true);
    }
}

/*!
 * If the given \a object implements the Displayable interface, create a
 * QDockWidget containing the exported widget. The dock widget is initialy
 * hidden.
 */
void ElapseClient::addDockWidgetFrom(QObject *object)
{
    QString className = object->metaObject()->className();

    auto displayable = dynamic_cast<elapse::Displayable*>(object);
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
    foreach (auto dockWidget, dockWidgets) {
        if (dockWidget->windowTitle() == "BatteryMonitor")
            dockWidget->setVisible(visible && !offlineSource);
        else
            dockWidget->setVisible(visible);
    }
}

void ElapseClient::configure()
{
    QSettings settings;

    // Configure the device

    uint eegSampleRate = settings.value("eeg/samplerate", 250).toUInt();
    uint eegChunkSize  = settings.value("eeg/chunksize", 20).toUInt();
    uint eegGain       = settings.value("eeg/gain", 24).toUInt();

    auto eeg = proxy->device()->eeg();
    eeg->setSampleRate(iface::EegAdc::SampleRate(eegSampleRate));
    eeg->setSamplesPerChunk(eegChunkSize);
    eeg->setUseRefElec(true);
    eeg->setAllChannels({{"enabled", true},
                         {"gain", eegGain},
                         {"inputMux", "Normal"}});

    // Other setup

    pipeline->setWindowLength(1000);
    pipeline->setWindowStep(500);

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

void ElapseClient::unconfigure()
{
    batteryMonitor->setBattery(nullptr);
    disconnect(ui->actionSetCaptureInfo, SIGNAL(triggered()), 0, 0);
}

void ElapseClient::start()
{
    pipeline->start();

    // Save the device configuration
    auto cfg = proxy->readDeviceConfig();
    pipeline->dataSink()->saveDeviceConfig(cfg);

    // Do any setup that requires an offline source to have been started
    auto eeg = proxy->device()->eeg();
    auto eegDecoder = pipeline->elements()->sampleDecoders[Signal::EEG];
    eegDecoder->setProperty("gain", eeg->channel(0)->gain());
    eegDecoder->setProperty("vref", eeg->vref());
    eegDecoder->setProperty("nChannels", eeg->nChannels());

    proxy->device()->startStreaming();
}

void ElapseClient::stop()
{
    proxy->device()->stopStreaming();
    pipeline->stop();
}

