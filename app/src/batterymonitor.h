#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <QObject>
#include <QTimer>
#include "elapse/displayable.h"

namespace elapse { namespace hardware { class Battery; } }
class DialWithSector;


/*!
 * \brief The BatteryMonitor class monitors the device's battery voltage and
 * displays it on a fuel-gauge–style dial.
 *
 * The gauge widget is exposed via the \ref elapse::Displayable "Displayable"
 * interface.
 *
 * The battery monitor polls the device's battery voltage at 1 Hz.
 */

class BatteryMonitor : public QObject, public elapse::Displayable
{
    Q_OBJECT
public:
    explicit BatteryMonitor(QObject *parent = nullptr);

    QWidget *getWidget();

    void setBattery(elapse::hardware::Battery *battery);

private slots:
    void updateVoltage();

private:
    elapse::hardware::Battery *battery;
    DialWithSector *gauge;
    QTimer timer;
};

#endif // BATTERYMONITOR_H
