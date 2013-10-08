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

    QObject::connect(pipeline,  SIGNAL(started()),
                     this,      SLOT(hideSpinner()));
    QObject::connect(pipeline,  SIGNAL(error(QString)),
                     this,      SLOT(onPipelineError(QString)));
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

void MainWindow::onPipelineError(const QString &message)
{
    hideSpinner();

    SignalBlocker block(ui->pushButton);
    ui->pushButton->setChecked(false);

    QMessageBox::warning(this, "Error", message);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        showSpinner();
        pipeline->start();
    } else {
        pipeline->stop();
    }
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
