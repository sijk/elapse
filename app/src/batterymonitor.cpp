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

#include <QxtLogger>
#include "common/hardware/battery_iface.h"
#include "dialwithsector.h"
#include "batterymonitor.h"


namespace elapse { namespace client {

/*!
 * Create a BatteryMonitor as a child of the given \a parent.
 */
BatteryMonitor::BatteryMonitor(QObject *parent) :
    QObject(parent),
    battery(nullptr)
{
    gauge = new widgets::DialWithSector;
    gauge->setLowerBound(3.0);
    gauge->setUpperBound(4.0);

    connect(&timer, SIGNAL(timeout()), SLOT(updateVoltage()));
}

/*!
 * \return the battery voltage gauge widget.
 */
QWidget *BatteryMonitor::getWidget()
{
    return gauge;
}

/*!
 * Set the DBus interface to the device's \a battery.
 */
void BatteryMonitor::setBattery(hardware::Battery *battery)
{
    this->battery = battery;
    if (!battery) {
        timer.stop();
        return;
    }

    gauge->setLowerBound(battery->criticalThresh());
    gauge->setSectorBound(battery->lowThresh());

    timer.start(1000);
}

/*!
 * Read the battery voltage from the device and display it on the gauge.
 */
void BatteryMonitor::updateVoltage()
{
    Q_ASSERT(battery);

    double voltage = battery->voltage();

    if (voltage > gauge->upperBound())
        gauge->setUpperBound(voltage);

    gauge->setValue(voltage);
}

}} // namespace elapse::client
