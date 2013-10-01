#include <QMessageBox>
#include <QMovie>
#include "pluginloader.h"
#include "plugindialog.h"
#include "stripchart.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sampletypes.h"

#include <QDebug>

MainWindow::MainWindow(PluginLoader &loader, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loader(loader),
    spinner(new QMovie(":/img/spinner.gif"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete spinner;
    delete ui;
}

void MainWindow::onDataReady(const EegSample &sample)
{
    ui->eegPlot->appendData(sample.channel);
}

void MainWindow::onSourceStarted()
{
    hideSpinner();
}

void MainWindow::onSourceError(const QString &message)
{
    hideSpinner();

    bool wasBlocked = ui->pushButton->blockSignals(true);
    ui->pushButton->setChecked(false);
    ui->pushButton->blockSignals(wasBlocked);

    QMessageBox::warning(this, "Error", message);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) showSpinner();
    emit (checked ? start() : stop());
}

void MainWindow::on_actionPlugins_triggered()
{
    PluginDialog dialog(loader, this);
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
