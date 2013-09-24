#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PluginLoader;
class QwtPlotCurve;
class EegSample;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void start();
    void stop();

public slots:
    void onDataReady(const EegSample &sample);
    void onSourceError(const QString &message);

private slots:
    void on_pushButton_toggled(bool checked);
    void on_plotLength_valueChanged(int len);
    void on_actionPlugins_triggered();

private:
    Ui::MainWindow *ui;
    PluginLoader &loader;
    int plotLength;
    QVector<double> x, y;
    QwtPlotCurve *curve;
};

#endif // MAINWINDOW_H
