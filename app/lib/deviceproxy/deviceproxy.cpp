#include <QDBusConnection>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSettings>
#include <QtConcurrent/QtConcurrentRun>
#include <QxtLogger>
#include "dbus_interfaces.h"
#include "deviceproxy.h"

#define DEFAULT_PORT    9000


/*!
 * Create a new DeviceProxy as a child of the given \a parent.
 */
DeviceProxy::DeviceProxy(QObject *parent) :
    QObject(parent),
    dev(nullptr)
{
    connect(&connectionChecker, SIGNAL(timeout()), SLOT(checkConnectivity()));
}

/*!
 * Delete this DeviceProxy.
 */
DeviceProxy::~DeviceProxy()
{
    delete dev;
}

/*!
 * \return the D-Bus interface for the root device object.
 */
iface::Device *DeviceProxy::device() const
{
    return dev;
}

/*!
 * \return the address of the connected device.
 *
 * The return value is only valid after the proxy is connected().
 */
QString DeviceProxy::deviceAddress() const
{
    return deviceAddr;
}

/*!
 * \return the address of this computer on the device's network.
 *
 * The return value is only valid after the proxy is connected().
 */
QString DeviceProxy::localAddress() const
{
    return localAddr;
}

/*!
 * \return the device's configuration; i.e., the values of all of the
 * properties of all of the device's subsystems.
 *
 * The result is structured like:
 * \code
 * { "subSystem1", {{ "prop1", value1 },
 *                  { "prop2", value2 }},
 *   "subSystem2", ... }
 * \endcode
 */
QMap<QString, QVariantMap> DeviceProxy::getDeviceConfig() const
{
    Q_ASSERT(dev);
    QMap<QString, QVariantMap> config;

    auto getProperties = [](const QObject *obj) {
        QVariantMap props;
        if (!obj)
            return props;

        for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
            auto prop = obj->metaObject()->property(i);
            if (prop.isReadable() && qstrcmp(prop.name(), "objectName")) {
                qxtLog->trace("    ", prop.name(), "=", prop.read(obj));
                props.insert(prop.name(), prop.read(obj));
            }
        }
        return props;
    };

    auto readConfig = [&](const QString &subSystem, const QObject *obj) {
        qxtLog->trace("  ", subSystem);
        config.insert(subSystem, getProperties(obj));
    };

    qxtLog->trace("Hardware config:");
    readConfig("battery", dev->battery());
    readConfig("imu", dev->imu());
    readConfig("camera", dev->camera());
    readConfig("eeg", dev->eeg());
    uint nChannels = dev->eeg()->nChannels();
    for (uint i = 0; i < nChannels; i++)
        readConfig(QString("eeg/channel/%1").arg(i), dev->eeg()->channel(i));

    return config;
}

/*!
 * Asynchronously connect to the \a device. The connected() signal will be
 * emitted if connecting succeeds, otherwise an error() will be emitted.
 *
 * The \a device argument can be an IP address or a hostname.
 */
void DeviceProxy::connectTo(const QString &device)
{
    deviceAddr = device;
    QtConcurrent::run(this, &DeviceProxy::connectInBackground);
}

/*!
 * Do the actual connecting to the device. This method is run in the
 * background by connect().
 */
void DeviceProxy::connectInBackground()
{
    QDBusConnection bus("none");

    if (deviceAddr == "localhost") {
        localAddr = "localhost";
        bus = QDBusConnection::sessionBus();
        if (!bus.isConnected()) {
            qxtLog->error("Connect:", bus.lastError().message());
            emit error("Could not connect to the device.");
            return;
        }
    } else {
        QSettings settings;
        uint port = settings.value("port", DEFAULT_PORT).toUInt();
        QString address = QString("tcp:host=%1,port=%2").arg(deviceAddr).arg(port);

        if (!detectLocalAddressByConnectingTo(deviceAddr, port))
            return;

        // Connect to the remote session bus
        bus = QDBusConnection::connectToBus(address, "elapse-bus");
        if (!bus.isConnected()) {
            qxtLog->error("Connect:", bus.lastError().message());
            emit error("Could not connect to the device.");
            QDBusConnection::disconnectFromBus("elapse-bus");
            return;
        }
    }

    dev = new dbus::Device(bus);
    if (!dev->checkConnected()) {
        emit error("The server is not running on the device.");
        return;
    }

    emit connected();
    connectionChecker.start(2000);
}

/*!
 * Delete all D-Bus interfaces and emit disconnected().
 */
void DeviceProxy::disconnect()
{
    connectionChecker.stop();

    delete dev;
    dev = nullptr;

    emit disconnected();
}

/*!
 * Poll device.isAccessible() periodically.
 */
void DeviceProxy::checkConnectivity()
{
    Q_ASSERT(dev);
    if (!dev->isAccessible()) {
        qxtLog->error("Device connectivity check failed");
        emit error("The connection to the device was lost");
        disconnect();
    }
}

/*!
 * Connect to the given (host, port) on the device so that we can inspect
 * our own IP address.
 *
 * An error() will be emitted if it could not connect to the device.
 *
 * \return whether it successfully connected to the device.
 */
bool DeviceProxy::detectLocalAddressByConnectingTo(const QString &host,
                                                   quint16 port)
{
    QTcpSocket sock;
    sock.connectToHost(host, port);

    if (!sock.waitForConnected(5000)) {
        qxtLog->error(QString("Connecting to %1:%2:").arg(host).arg(port),
                      sock.errorString());
        emit error("Could not connect to the device.");
        return false;
    }

    localAddr = sock.localAddress().toString();
    return true;
}

/*!
 * \fn DeviceProxy::connected()
 * Emitted when the proxy has successfully connected to the remote D-Bus daemon.
 */

/*!
 * \fn DeviceProxy::disconnected()
 * Emitted when the proxy has disconnected from the remote D-Bus daemon.
 */

/*!
 * \fn DeviceProxy::error(QString msg)
 * Emitted when an error occurs with the connection to the device.
 */
