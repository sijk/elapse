#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include <QObject>
#include <QList>

#include "elapse_interface.h"
#include "eeg_interface.h"


class DeviceProxy : public QObject
{
    Q_OBJECT
public:
    explicit DeviceProxy(QObject *parent = nullptr);

    org::nzbri::elapse::Device *device;
    org::nzbri::elapse::Eeg::EegAdc *eeg;
    QList<org::nzbri::elapse::Eeg::EegChannel*> eeg_channels;
};


#endif // DEVICEPROXY_H
