#include <QStateMachine>
#include <QMessageBox>
#include <QMovie>
#include "elements.h"
#include "pipeline.h"
#include "pluginmanager.h"
#include "stripchart.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

/*!
 * \class MainWindow
 * \ingroup app
 * \inmodule elapse-core
 *
 * \brief The MainWindow class provides the main window of the Elapse
 *        application.
 *
 * It contains a Pipeline, a PluginManager, and a ServerProxy which provide all
 * of the actual functionality of the application. It also provides a GUI for
 * interacting with these objects and displaying the state of the signal
 * processing elements.
 */


/*!
 * Construct a MainWindow as a child of the given \a parent widget.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spinner(new QMovie(":/img/spinner.gif")),
    pluginManager(new PluginManager(this)),
    pipeline(new Pipeline(this))
{
    ui->setupUi(this);

    connect(ui->spacingSlider, SIGNAL(valueChanged(int)),
            ui->eegPlot, SLOT(setSpacing(int)));

    ui->eegPlot->setNStrips(8);
    ui->eegPlot->setNSamples(1000);
    ui->spacingSlider->setValue(6e3);

    connect(pipeline, SIGNAL(error(QString)),
            this, SLOT(showErrorMessage(QString)));

    connect(pluginManager, SIGNAL(pluginsLoaded(ElementSet*)),
            SLOT(setupPipeline(ElementSet*)));

    buildStateMachine();
}

/*!
 * Destroy this MainWindow.
 */
MainWindow::~MainWindow()
{
    delete spinner;
    delete ui;
}

void MainWindow::onEegSample(const Sample &sample)
{
    auto eeg = static_cast<const EegSample&>(sample);
    ui->eegPlot->appendData(eeg.values);
}

void MainWindow::on_actionPlugins_triggered()
{
    pluginManager->loadPlugins();
}

void MainWindow::showErrorMessage(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

/*!
 * \property MainWindow::showSpinner
 * \brief whether to hide/show the spinner animation.
 */
bool MainWindow::showSpinner() const
{
    return spinner->state() == QMovie::Running;
}

void MainWindow::showSpinner(bool show)
{
    if (show) {
        ui->spinner->setMovie(spinner);
        spinner->start();
    } else {
        spinner->stop();
        ui->spinner->setText(" ");
    }
}

void MainWindow::buildStateMachine()
{
    machine = new QStateMachine(this);
    machine->setGlobalRestorePolicy(QState::RestoreProperties);

    auto idle = new QState(machine);
    auto active = new QState(machine);
    auto starting = new QState(active);
    auto running = new QState(active);

    // Define state transitions

    machine->setInitialState(idle);

    idle->addTransition(ui->pushButton, SIGNAL(clicked()), active);

    active->setInitialState(starting);

    starting->addTransition(pipeline, SIGNAL(started()), running);

    active->addTransition(pipeline, SIGNAL(error(QString)), idle);
    active->addTransition(ui->pushButton, SIGNAL(clicked()), idle);

    // Assign entry/exit actions

    connect(active, SIGNAL(entered()), pipeline, SLOT(start()));
    connect(active, SIGNAL(exited()), pipeline, SLOT(stop()));

    starting->assignProperty(this, "showSpinner", true);
    starting->assignProperty(ui->pushButton, "enabled", false);

    running->assignProperty(ui->pushButton, "text", "Stop");

    machine->start();
}

void MainWindow::setupPipeline(ElementSet *elements)
{
    Q_ASSERT(elements);
    pipeline->setElements(elements);

    elements->dataSource->setProperty("host", "overo.local");
    elements->sampleDecoders[EEG]->setProperty("gain", 1);
    elements->sampleDecoders[EEG]->setProperty("vref", 4.5e6);

    connect(elements->sampleDecoders[EEG],
            SIGNAL(newSample(Sample)), SLOT(onEegSample(Sample)));
}
