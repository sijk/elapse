#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <QObject>
#include <QTimer>
#include "elapse/displayable.h"

class DialWithSector;

namespace elapse {

namespace hardware { class Battery; }

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
    DialWithSector *gauge;
    QTimer timer;
};

}} // namespace elapse::client

#endif // BATTERYMONITOR_H
