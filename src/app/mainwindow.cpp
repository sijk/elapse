#include <qwt_plot_curve.h>
#include "pluginloader.h"
#include "plugindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(PluginLoader &loader, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loader(loader),
    plotLength(100),
    x(plotLength),
    y(plotLength),
    curve(new QwtPlotCurve)
{
    ui->setupUi(this);
    curve->attach(ui->plot);

    for (int i = 0; i < x.size(); i++)
        x[i] = i;

    curve->setSamples(x, y);
    ui->plot->setAxisScale(0, -1, 1);
    ui->plot->setAxisScale(1, 0, plotLength);

    QObject::connect(&loader, SIGNAL(createdKey(QString)),
                     this, SLOT(showProviderKey(QString)));
}

MainWindow::~MainWindow()
{
    delete curve;
    delete ui;
}

void MainWindow::onDataReady(double data)
{
    y.pop_front();
    y.push_back(data);

    curve->setSamples(x, y);
    ui->plot->replot();
}

void MainWindow::showProviderKey(const QString &key)
{
    ui->pluginName->setText(QStringLiteral("Using %1").arg(key));
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
