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
