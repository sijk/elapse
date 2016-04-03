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

#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <QObject>
#include <QTimer>
#include <QPointer>
#include "elapse/displayable.h"

namespace elapse {
namespace hardware { class Battery; }
namespace widgets { class DialWithSector; }
namespace client {


/*!
 * \brief The BatteryMonitor class monitors the device's battery voltage and
 * displays it on a fuel-gauge–style dial.
 *
 * The gauge widget is exposed via the Displayable interface.
 *
 * The battery monitor polls the device's battery voltage at 1 Hz.
 */

class BatteryMonitor : public QObject, public Displayable
{
    Q_OBJECT
public:
    explicit BatteryMonitor(QObject *parent = nullptr);

    QWidget *getWidget();

    void setBattery(hardware::Battery *battery);

private slots:
    void updateVoltage();

private:
    hardware::Battery *battery;
    QPointer<widgets::DialWithSector> gauge;
    QTimer timer;
};

}} // namespace elapse::client

#endif // BATTERYMONITOR_H
