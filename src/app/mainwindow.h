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


/*!
 * \brief The MainWindow class provides the main window of the Elapse
 * application.
 *
 * It contains a Pipeline, a PluginManager, and a DeviceProxy which provide all
 * of the actual functionality of the application. It also provides a GUI for
 * interacting with these objects and displaying the state of the signal
 * processing elements.
 *
 * \see \ref mainwindow-fsm
 * \ingroup app
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onEegSample(const Sample &sample);
    void onVideoSample(const Sample &sample);
    void showErrorMessage(QString message);
    void setupPipeline(ElementSet *elements);

private:
    void buildStateMachine();

    Ui::MainWindow *ui;
    QStateMachine *machine;
    PluginManager *pluginManager;
    Pipeline *pipeline;
    DeviceProxy *device;
};

#endif // MAINWINDOW_H
