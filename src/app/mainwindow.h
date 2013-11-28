#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Pipeline;
class PluginManager;
class ElementSet;
class Sample;
class DeviceProxy;
class Spinner;
class QStateMachine;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onEegSample(const Sample &sample);

    void on_actionPlugins_triggered();
    void setupPipeline(ElementSet *elements);

    void showErrorMessage(const QString &message);

private:
    void buildStateMachine();

    Ui::MainWindow *ui;
    QStateMachine *machine;
    PluginManager *pluginManager;
    Pipeline *pipeline;
    DeviceProxy *device;
};

#endif // MAINWINDOW_H
