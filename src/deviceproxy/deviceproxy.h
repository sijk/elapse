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
    ~DeviceProxy();

    org::nzbri::elapse::Device *device() const;
    org::nzbri::elapse::Battery *battery() const;
    org::nzbri::elapse::Eeg::EegAdc *eeg() const;
    org::nzbri::elapse::Eeg::EegChannel* eeg_channel(uint i) const;

    QString deviceAddress() const;
    QString localAddress() const;

public slots:
    void connect();
    void disconnect();

signals:
    void connected();
    void disconnected();
    void error(QString msg);

private:
    void connectInBackground();
    bool detectLocalAddressByConnectingTo(const QString& host, quint16 port);

    org::nzbri::elapse::Device *_device;
    org::nzbri::elapse::Battery *_battery;
    org::nzbri::elapse::Eeg::EegAdc *_eeg;
    QList<org::nzbri::elapse::Eeg::EegChannel*> _eeg_channels;
    QString localAddr;
};


#endif // DEVICEPROXY_H
