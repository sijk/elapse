#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include <memory>
#include <QObject>
#include <QList>
#include <QTimer>
#include "common/hardware.h"

namespace elapse { namespace client {

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

    hardware::Device *device() const;

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

    std::unique_ptr<dbus::Device> dev;
    QString deviceAddr;
    QString localAddr;
    QTimer connectionChecker;
};

}} // namespace elapse::client

#endif // DEVICEPROXY_H
