#include <QStateMachine>
#include <QMessageBox>
#include <QSettings>
#include <QxtLogger>
#include "pipeline.h"
#include "pluginmanager.h"
#include "deviceproxy.h"
#include "stripchart.h"
#include "logview.h"
#include "elapseclient.h"
#include "ui_elapseclient.h"


/*!
 * Construct a ElapseClient as a child of the given \a parent widget.
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

    qxtLog->info("Using settings from", QSettings().fileName());

    ui->buttonPlugins->setVisible(false);
    ui->buttonPlugins->setDefaultAction(ui->actionPlugins);
    ui->buttonConnect->setDefaultAction(ui->actionConnect);
    connect(ui->actionLogView, SIGNAL(triggered(bool)),
            logView, SLOT(setVisible(bool)));
    connect(logView, SIGNAL(visibilityChanged(bool)),
            ui->actionLogView, SLOT(setChecked(bool)));

    connect(ui->spacingSlider, SIGNAL(valueChanged(int)),
            ui->eegPlot, SLOT(setSpacing(int)));
    connect(ui->actionPlugins, SIGNAL(triggered()),
            pluginManager, SLOT(selectPluginsToLoad()));
    connect(pluginManager, SIGNAL(pluginsLoaded(ElementSetPtr)),
            pipeline, SLOT(setElements(ElementSetPtr)));
    connect(device, SIGNAL(connected()), SLOT(setupElements()));

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

void ElapseClient::onEegSample(SamplePtr sample)
{
    auto eeg = sample.staticCast<const EegSample>();
    ui->eegPlot->appendData(eeg->values);
}

void ElapseClient::onImuSample(SamplePtr sample)
{
    auto imu = sample.staticCast<const ImuSample>();

    // Calculate the direction of the acceleration vector.
    // By assuming this is purely due to gravity, we get an approximation
    // of the head orientation (though with no information about z rotation).
    float ax = imu->acc.x();
    float ay = imu->acc.y();
    float az = imu->acc.z();
    double theta = atan2(ax, az);
    double phi = atan2(ay, sqrt(ax*ax + az*az));

    ui->headWidget->setXRotation(-theta);
    ui->headWidget->setZRotation(phi);
}

void ElapseClient::onVideoSample(SamplePtr sample)
{
    auto frame = sample.staticCast<const VideoSample>();
    qxtLog->trace(frame->timestamp);
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
 * The behaviour of the ElapseClient is driven by the following hierarchical
 * state machine.
 *
 * @startuml{elapseclient-fsm.png}
 *
 * [*] -> Uninitialised
 * Uninitialised : enter / connect.disable()
 * Uninitialised : enter / loadPluginsFromSettings()
 * Uninitialised --> Disconnected : pluginsLoaded / maybeAutoConnect()
 * Disconnected : enter / connect.enable()
 * Disconnected --> Connecting : connect
 *
 * Connecting : enter / device.connect()
 * Connecting : enter / spinner.run()
 * Connecting --> Disconnected : device.error
 * Connecting --> Connected : connected
 *
 * Connected : enter / ui.showPage(connected)
 * Connected : exit / device.disconnect()
 * Connected --> Disconnected : disconnect
 * Connected --> Disconnected : device.error
 *
 * state Connected {
 *      [*] -> Idle
 *      Idle -> Active : capture
 *      Active -> Idle : stop
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
    uninitialised->assignProperty(ui->buttonConnect, "visible", false);
    uninitialised->assignProperty(ui->buttonPlugins, "visible", true);
    auto initialised = uninitialised->addTransition(pluginManager, SIGNAL(pluginsLoaded(ElementSetPtr)), disconnected);
    connect(uninitialised, SIGNAL(entered()), pluginManager, SLOT(loadPluginsFromSettings()));
    connect(initialised, SIGNAL(triggered()), SLOT(maybeAutoConnect()));

    disconnected->addTransition(ui->actionConnect, SIGNAL(triggered()), connecting);

    connecting->assignProperty(ui->spinnerConnecting, "running", true);
    connecting->assignProperty(ui->actionConnect, "enabled", false);
    connecting->assignProperty(this, "cursor", QCursor(Qt::WaitCursor));
    connect(connecting, SIGNAL(entered()), device, SLOT(connect()));
    connecting->addTransition(device, SIGNAL(error(QString)), disconnected);
    connecting->addTransition(device, SIGNAL(connected()), connected);

    connected->setInitialState(idle);
    connected->assignProperty(ui->stackedWidget, "currentIndex", 1);
    connected->assignProperty(ui->actionConnect, "text", "&Disconnect");
    connected->addTransition(ui->actionConnect, SIGNAL(triggered()), disconnected);
    connected->addTransition(device, SIGNAL(error(QString)), disconnected);
    connect(connected, SIGNAL(exited()), device, SLOT(disconnect()));

    idle->addTransition(ui->buttonCapture, SIGNAL(clicked()), active);

    active->assignProperty(ui->buttonCapture, "text", "Stop");
    connect(active, SIGNAL(entered()), pipeline, SLOT(start()));
    connect(active, SIGNAL(exited()), pipeline, SLOT(stop()));
    // We need to delay evaluation of device->device() by wrapping it in a
    // closure since it is not valid until the device is connected.
    connect(active, &QState::entered, [=]{ device->device()->startStreaming(); });
    connect(active, &QState::exited, [=]{ device->device()->stopStreaming(); });
    connect(active, SIGNAL(entered()), ui->spinnerStarting, SLOT(start()));
    connect(pipeline, SIGNAL(started()), ui->spinnerStarting, SLOT(stop()));
    active->addTransition(ui->buttonCapture, SIGNAL(clicked()), idle);
    active->addTransition(pipeline, SIGNAL(error(QString)), idle);

    machine->start();
}

void ElapseClient::setupElements()
{
    auto elements = pipeline->elements();
    Q_ASSERT(elements);
    auto eeg = device->eeg();

    // Configure hardware

    eeg->setSampleRate(250);
    eeg->setSamplesPerChunk(20);
    eeg->setUseRefElec(true);
    eeg->setAllChannels({{"enabled", true},
                         {"gain", 24},
                         {"inputMux", "Normal"}});

    // Configure pipeline to match

    elements->dataSource->setProperty("host", device->host());

    elements->sampleDecoders[EEG]->setProperty("gain", 24);
    elements->sampleDecoders[EEG]->setProperty("vref", eeg->vref());
    elements->sampleDecoders[EEG]->setProperty("nChannels", eeg->nChannels());

    // Configure GUI

    ui->eegPlot->setNStrips(eeg->nChannels());
    ui->eegPlot->setNSamples(5 * eeg->sampleRate());
    ui->spacingSlider->setValue(6e3);

    // Connect signals to GUI

    connect(elements->sampleDecoders[EEG], SIGNAL(newSample(SamplePtr)),
            SLOT(onEegSample(SamplePtr)));
    connect(elements->sampleDecoders[IMU], SIGNAL(newSample(SamplePtr)),
            SLOT(onImuSample(SamplePtr)));
    connect(elements->sampleDecoders[VIDEO], SIGNAL(newSample(SamplePtr)),
            SLOT(onVideoSample(SamplePtr)));

    connect(device->battery(), SIGNAL(batteryLow()), SLOT(onBatteryLow()));
}
