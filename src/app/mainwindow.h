#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PluginLoader;
class EegSample;
class QMovie;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PluginLoader &loader, QWidget *parent = 0);
    ~MainWindow();

signals:
    void start();
    void stop();

public slots:
    void onDataReady(const EegSample &sample);
    void onSourceStarted();
    void onSourceError(const QString &message);

private slots:
    void on_pushButton_toggled(bool checked);
    void on_actionPlugins_triggered();

    void showSpinner();
    void hideSpinner();

private:
    Ui::MainWindow *ui;
    PluginLoader &loader;
    QMovie *spinner;
};

#endif // MAINWINDOW_H
