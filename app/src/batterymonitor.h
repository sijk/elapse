#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <QObject>
#include <QTimer>
#include "elapse_interface.h"
#include "elapse/displayable.h"

class DialWithSector;


class BatteryMonitor : public QObject, public elapse::Displayable
{
    Q_OBJECT
public:
    explicit BatteryMonitor(QObject *parent = nullptr);

    QWidget *getWidget();

    void setBattery(org::nzbri::elapse::Battery *battery);

private slots:
    void updateVoltage();

private:
    org::nzbri::elapse::Battery *battery;
    DialWithSector *gauge;
    QTimer timer;
};

#endif // BATTERYMONITOR_H
