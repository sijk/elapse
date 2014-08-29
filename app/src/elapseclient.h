#ifndef ELAPSECLIENT_H
#define ELAPSECLIENT_H

#include <QMainWindow>
#include "elementset.h"

class Pipeline;
class PluginManager;
class DeviceProxy;
class LogView;
class BatteryMonitor;
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
    Q_PROPERTY(bool dockWidgetsVisible
               READ dockWidgetsVisible WRITE setDockWidgetsVisible)

public:
    explicit ElapseClient(QWidget *parent = nullptr);
    ~ElapseClient();

private slots:
    void showErrorMessage(QString message);
    void warnBatteryLow();
    void maybeAutoConnect();
    void loadElementWidgets(ElementSetPtr elements);
    void connectToDevice();
    void configure();
    void unconfigure();
    void start();
    void stop();

private:
    void connectSaveActions();
    void addDockWidgetFrom(QObject *object);
    bool dockWidgetsVisible() const;
    void setDockWidgetsVisible(bool visible);
    void buildStateMachine();

    Ui::ElapseClient *ui;
    LogView *logView;
    QStateMachine *machine;
    PluginManager *pluginManager;
    Pipeline *pipeline;
    DeviceProxy *proxy;
    BatteryMonitor *batteryMonitor;
};

#endif // ELAPSECLIENT_H
