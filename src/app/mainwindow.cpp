#include <QMessageBox>
#include <QMovie>
#include <qwt_plot_curve.h>
#include "pluginloader.h"
#include "plugindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sampletypes.h"

#include <QDebug>

MainWindow::MainWindow(PluginLoader &loader, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loader(loader),
    plotLength(1000),
    x(plotLength),
    y(plotLength),
    curve(new QwtPlotCurve),
    spinner(new QMovie(":/img/spinner.gif"))
{
    ui->setupUi(this);
    curve->attach(ui->plot);

    for (int i = 0; i < x.size(); i++)
        x[i] = i;

    curve->setSamples(x, y);
    ui->plot->setAxisAutoScale(0);
    ui->plot->setAxisScale(1, 0, plotLength);
    ui->plotLength->setValue(plotLength);
}

MainWindow::~MainWindow()
{
    delete spinner;
    delete curve;
    delete ui;
}

void MainWindow::onDataReady(const EegSample &sample)
{
    y.pop_front();
    y.push_back(sample.channel[0]);

    curve->setSamples(x, y);
    ui->plot->replot();
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

void MainWindow::on_plotLength_valueChanged(int len)
{
    int oldLength = plotLength;
    plotLength = len;

    x.resize(len);
    y.resize(len);

    if (len > oldLength)
        for (int i = oldLength; i < len; i++)
            x[i] = i;

    ui->plot->setAxisScale(1, 0, len);
    curve->setSamples(x, y); // replot() does nothing unless the curve has "changed"
    ui->plot->replot();
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
