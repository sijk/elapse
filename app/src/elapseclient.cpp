#include <QStateMachine>
#include <QMessageBox>
#include <QDockWidget>
#include <QSettings>
#include <QxtLogger>
#include "pipeline.h"
#include "pluginmanager.h"
#include "deviceproxy.h"
#include "logview.h"
#include "displayable.h"
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
    device(new DeviceProxy(this))
{
    ui->setupUi(this);
    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks);

    QSettings settings;
    qxtLog->info("Using settings from", settings.fileName());

    ui->buttonPlugins->setVisible(false);
    ui->buttonPlugins->setDefaultAction(ui->actionPlugins);
    ui->buttonConnect->setDefaultAction(ui->actionConnect);
    ui->connectedToolBar->setVisible(false);
    ui->connectedToolBar->addWidget(ui->spinnerStarting);

    QString defaultAddress = settings.value("host", DEFAULT_ADDR).toString();
    ui->deviceAddress->setText(defaultAddress);
    connect(ui->deviceAddress, SIGNAL(returnPressed()),
            ui->actionConnect, SLOT(trigger()));

    connect(ui->actionLogView, SIGNAL(triggered(bool)),
            logView, SLOT(setVisible(bool)));
    connect(logView, SIGNAL(visibilityChanged(bool)),
            ui->actionLogView, SLOT(setChecked(bool)));

    connect(ui->actionPlugins, SIGNAL(triggered()),
            pluginManager, SLOT(selectPluginsToLoad()));
    connect(pluginManager, SIGNAL(pluginsLoaded(ElementSetPtr)),
            pipeline, SLOT(setElements(ElementSetPtr)));
    connect(pluginManager, SIGNAL(pluginsLoaded(ElementSetPtr)),
            SLOT(loadElementWidgets(ElementSetPtr)));

    connect(pipeline, SIGNAL(error(QString)), SLOT(showErrorMessage(QString)));
    connect(device, SIGNAL(error(QString)), SLOT(showErrorMessage(QString)));

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
    QMessageBox::warning(this, "Error", message);
}

void ElapseClient::onBatteryLow()
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
 * Uninitialised --> Disconnected : pluginsLoaded / maybeAutoConnect()
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
    auto initialised = uninitialised->addTransition(pluginManager, SIGNAL(pluginsLoaded(ElementSetPtr)), disconnected);
    connect(uninitialised, SIGNAL(entered()), pluginManager, SLOT(loadPluginsFromSettings()));
    connect(initialised, SIGNAL(triggered()), SLOT(maybeAutoConnect()));

    disconnected->addTransition(ui->actionConnect, SIGNAL(triggered()), connecting);

    connect(connecting, &QState::entered,
            [=]{ device->connectTo(ui->deviceAddress->text()); });
    connecting->assignProperty(ui->spinnerConnecting, "running", true);
    connecting->assignProperty(ui->actionConnect, "enabled", false);
    connecting->assignProperty(this, "cursor", QCursor(Qt::WaitCursor));
    connecting->addTransition(device, SIGNAL(error(QString)), disconnected);
    connecting->addTransition(device, SIGNAL(connected()), connected);

    connected->setInitialState(idle);
    connected->assignProperty(ui->centralWidget, "visible", false);
    connected->assignProperty(this, "elementWidgetsVisible", true);
    connected->assignProperty(ui->disconnectedToolBar, "visible", false);
    connected->assignProperty(ui->connectedToolBar, "visible", true);
    connected->assignProperty(ui->actionConnect, "text", "&Disconnect");
    connected->addTransition(ui->actionConnect, SIGNAL(triggered()), disconnected);
    connected->addTransition(device, SIGNAL(error(QString)), disconnected);
    connect(connected, SIGNAL(entered()), SLOT(configure()));
    connect(connected, SIGNAL(exited()), device, SLOT(disconnect()));

    idle->addTransition(ui->actionCapture, SIGNAL(triggered()), active);

    active->assignProperty(ui->actionCapture, "text", "Stop");
    active->assignProperty(ui->actionCapture, "icon", QIcon::fromTheme("media-playback-stop"));
    connect(active, SIGNAL(entered()), pipeline, SLOT(start()));
    connect(active, SIGNAL(exited()), pipeline, SLOT(stop()));
    // We need to delay evaluation of device->device() by wrapping it in a
    // closure since it is not valid until the device is connected.
    connect(active, &QState::entered, [=]{ device->device()->startStreaming(); });
    connect(active, &QState::exited, [=]{ device->device()->stopStreaming(); });
    connect(active, SIGNAL(entered()), ui->spinnerStarting, SLOT(start()));
    connect(pipeline, SIGNAL(started()), ui->spinnerStarting, SLOT(stop()));
    connect(active, SIGNAL(exited()), ui->spinnerStarting, SLOT(stop()));
    active->addTransition(ui->actionCapture, SIGNAL(triggered()), idle);
    active->addTransition(pipeline, SIGNAL(error(QString)), idle);

    machine->start();
}

/*!
 * For each element that implements the Displayable interface, add a
 * QDockWidget containing the widget exported by the element.
 */
void ElapseClient::loadElementWidgets(ElementSetPtr elements)
{
    foreach (QObject *element, elements->allElements()) {
        QString className = element->metaObject()->className();

        auto displayable = dynamic_cast<Displayable*>(element);
        if (!displayable) {
            qxtLog->debug(className, "is not displayable");
            continue;
        }

        qxtLog->debug("Adding widget provided by", className);

        auto widget = displayable->getWidget();
        Q_ASSERT(widget);

        auto dockWidget = new QDockWidget(className, this);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidget->setWidget(widget);
        addDockWidget(Qt::TopDockWidgetArea, dockWidget);
        dockWidget->hide();
        connect(element, SIGNAL(destroyed()), dockWidget, SLOT(deleteLater()));
    }
}

bool ElapseClient::elementWidgetsVisible() const
{
    auto dockWidget = findChild<QDockWidget*>("", Qt::FindDirectChildrenOnly);
    return dockWidget && dockWidget->isVisible();
}

void ElapseClient::setElementWidgetsVisible(bool visible)
{
    auto dockWidgets = findChildren<QDockWidget*>("", Qt::FindDirectChildrenOnly);
    foreach (auto dockWidget, dockWidgets)
        dockWidget->setVisible(visible);
}

void ElapseClient::configure()
{
    auto elements = pipeline->elements();
    Q_ASSERT(elements);
    QSettings settings;

    // Configure hardware

    uint eegSampleRate = settings.value("eeg/samplerate", 250).toUInt();
    uint eegChunkSize  = settings.value("eeg/chunksize", 20).toUInt();
    uint eegGain       = settings.value("eeg/gain", 24).toUInt();

    device->eeg()->setSampleRate(eegSampleRate);
    device->eeg()->setSamplesPerChunk(eegChunkSize);
    device->eeg()->setUseRefElec(true);
    device->eeg()->setAllChannels({{"enabled", true},
                                   {"gain", eegGain},
                                   {"inputMux", "Normal"}});

    // Configure pipeline to match

    elements->dataSource->setProperty("host", device->deviceAddress());

    elements->sampleDecoders[SampleType::EEG]->setProperty("gain", eegGain);
    elements->sampleDecoders[SampleType::EEG]->setProperty("vref", device->eeg()->vref());
    elements->sampleDecoders[SampleType::EEG]->setProperty("nChannels", device->eeg()->nChannels());

    // Other setup

    qxtLog->debug("Notifying server that our address is", device->localAddress());
    device->device()->setClientAddress(device->localAddress());

    connect(device->battery(), SIGNAL(batteryLow()), SLOT(onBatteryLow()));
    if (device->battery()->isLow())
        onBatteryLow();
}
