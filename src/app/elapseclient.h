#ifndef ELAPSECLIENT_H
#define ELAPSECLIENT_H

#include <QMainWindow>
#include "elements.h"

class Pipeline;
class PluginManager;
class Sample;
class DeviceProxy;
class LogView;
class QStateMachine;

namespace Ui {
class ElapseClient;
}


/*!
 * \brief The ElapseClient class provides the main window of the Elapse
 * application.
 *
 * It contains a Pipeline, a PluginManager, and a DeviceProxy which provide all
 * of the actual functionality of the application. It also provides a GUI for
 * interacting with these objects and displaying the state of the signal
 * processing elements.
 *
 * \see \ref elapseclient-fsm
 * \ingroup app
 */

class ElapseClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit ElapseClient(QWidget *parent = nullptr);
    ~ElapseClient();

private slots:
    void onEegSample(SamplePtr sample);
    void onVideoSample(SamplePtr sample);
    void showErrorMessage(QString message);
    void onBatteryLow();
    void setupElements();

private:
    void buildStateMachine();

    Ui::ElapseClient *ui;
    LogView *logView;
    QStateMachine *machine;
    PluginManager *pluginManager;
    Pipeline *pipeline;
    DeviceProxy *device;
};

#endif // ELAPSECLIENT_H
