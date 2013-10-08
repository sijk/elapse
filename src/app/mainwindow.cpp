#include <QStateMachine>
#include <QMessageBox>
#include <QMovie>
#include "sampletypes.h"
#include "util/signalblocker.h"
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

void MainWindow::showSpinner()
{
    ui->pushButton->setEnabled(false);
    ui->spinner->setMovie(spinner);
    spinner->start();
}

void MainWindow::hideSpinner()
{
    spinner->stop();
    ui->spinner->setText(" ");
    ui->pushButton->setEnabled(true);
    ui->pushButton->setFocus();
}

void MainWindow::buildStateMachine()
{
    machine = new QStateMachine(this);

    auto idle = new QState(machine);
    auto starting = new QState(machine);
    auto running = new QState(machine);

    machine->setInitialState(idle);

    // Define state transitions
    idle->addTransition(ui->pushButton, SIGNAL(toggled(bool)), starting);

    starting->addTransition(pipeline, SIGNAL(started()), running);
    starting->addTransition(pipeline, SIGNAL(error(QString)), idle);

    running->addTransition(pipeline, SIGNAL(error(QString)), idle);
    running->addTransition(ui->pushButton, SIGNAL(toggled(bool)), idle);

    // Assign entry/exit handlers
    connect(idle, SIGNAL(entered()), pipeline, SLOT(stop()));
    connect(idle, &QState::entered, [&](){
                SignalBlocker block(ui->pushButton);
                ui->pushButton->setChecked(false);
            });

    connect(starting, SIGNAL(entered()), pipeline, SLOT(start()));
    connect(starting, SIGNAL(entered()), this, SLOT(showSpinner()));
    connect(starting, SIGNAL(exited()), this, SLOT(hideSpinner()));

    machine->start();
}
