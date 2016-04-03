/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef ELAPSECLIENT_H
#define ELAPSECLIENT_H

#include <memory>
#include <QMainWindow>
#include "elementset.h"

class QStateMachine;
namespace Ui { class ElapseClient; }

namespace elapse {
namespace log { class LogView; }
namespace plugin { class Manager; }

/*!
 * \brief Implementation of the Elapse client application.
 */

namespace client {

class Pipeline;
class DeviceProxy;
class BatteryMonitor;


/*!
 * \brief The ElapseClient class provides the main window of the Elapse
 * application.
 *
 * It contains a Pipeline, a plugin::Manager, and a DeviceProxy which provide
 * all of the actual functionality of the application. It also provides a GUI
 * for interacting with these objects and displaying the state of the signal
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
    void loadElementWidgets(elapse::elements::ElementSetPtr elements);
    void connectToDevice();
    void createDefaultHardwareConfig();
    void applyHardwareConfig();
    void configure();
    void unconfigure();
    void start();
    void stop();

private:
    void addDockWidgetFrom(QObject *object);
    bool dockWidgetsVisible() const;
    void setDockWidgetsVisible(bool visible);
    void buildStateMachine();

    std::unique_ptr<Ui::ElapseClient> ui;
    log::LogView *logView;
    QStateMachine *machine;
    plugin::Manager *pluginManager;
    Pipeline *pipeline;
    DeviceProxy *proxy;
    BatteryMonitor *batteryMonitor;
};

}} // namespace elapse::client

#endif // ELAPSECLIENT_H
