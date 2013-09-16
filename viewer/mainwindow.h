#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot_curve.h>

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
    void onDataReady(double data);
    void showPluginName(QObject *obj);

private slots:
    void on_pushButton_toggled(bool checked);
    void on_plotLength_valueChanged(int len);

private:
    Ui::MainWindow *ui;
    int plotLength;
    QVector<double> x, y;
    QwtPlotCurve *curve;
};

#endif // MAINWINDOW_H
