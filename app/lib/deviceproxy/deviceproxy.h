#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "common/interfaces.h"

namespace dbus { class Device; }


/*!
 * \brief The DeviceProxy class provides an interface to the device over D-Bus.
 * \ingroup app
 */

class DeviceProxy : public QObject
{
    Q_OBJECT
public:
    explicit DeviceProxy(QObject *parent = nullptr);
    ~DeviceProxy();

    iface::Device *device() const;

    QString deviceAddress() const;
    QString localAddress() const;

    QMap<QString, QVariantMap> getDeviceConfig() const;

public slots:
    void connectTo(const QString &hostname);
    void disconnect();

signals:
    void connected();
    void disconnected();
    void error(QString msg);

private slots:
    void checkConnectivity();

private:
    void connectInBackground();
    bool detectLocalAddressByConnectingTo(const QString& host, quint16 port);

    dbus::Device *dev;
    QString deviceAddr;
    QString localAddr;
    QTimer connectionChecker;
};


#endif // DEVICEPROXY_H
