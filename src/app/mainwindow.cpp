#include <QMessageBox>
#include <qwt_plot_curve.h>
#include "pluginloader.h"
#include "plugindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sampletypes.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loader(loader),
    plotLength(20),
    x(plotLength),
    y(plotLength),
    curve(new QwtPlotCurve)
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
    delete curve;
    delete ui;
}

void MainWindow::onDataReady(const EegSample &sample)
{
    static quint64 prev_seqnum = 0;

    int dropped = sample.seqnum - prev_seqnum - 1;
    if (dropped)
        qDebug() << "Dropped" << dropped << "samples";
    prev_seqnum = sample.seqnum;

    y.pop_front();
    y.push_back(sample.channel[6]);

    curve->setSamples(x, y);
    ui->plot->replot();
}

void MainWindow::onSourceError(const QString &message)
{
    bool wasBlocked = ui->pushButton->blockSignals(true);
    ui->pushButton->setChecked(false);
    ui->pushButton->blockSignals(wasBlocked);

    QMessageBox::warning(this, "Error", message);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
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
