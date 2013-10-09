#include <QStateMachine>
#include <QMessageBox>
#include <QMovie>
#include "sampletypes.h"
#include "pipeline.h"
#include "plugindialog.h"
#include "stripchart.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spinner(new QMovie(":/img/spinner.gif")),
    pipeline(new Pipeline)
{
    ui->setupUi(this);

    pipeline->setElementProperty("DataSource", "host", "overo.local");

    QObject::connect(pipeline,  SIGNAL(error(QString)),
                     this,      SLOT(showErrorMessage(QString)));

    buildStateMachine();
}

MainWindow::~MainWindow()
{
    delete pipeline;
    delete spinner;
    delete ui;
}

void MainWindow::onDataReady(const EegSample &sample)
{
    ui->eegPlot->appendData(sample.channel);
}

void MainWindow::showErrorMessage(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainWindow::on_actionPlugins_triggered()
{
    PluginDialog dialog(pipeline->pluginLoader(), this);
    dialog.exec();
}

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
