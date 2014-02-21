#include <QDBusConnection>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSettings>
#include <QtConcurrent/QtConcurrentRun>
#include <QxtLogger>
#include "deviceproxy.h"

#define DEFAULT_HOST    "overo.local"
#define DEFAULT_PORT    9000
#define SERVICE         "org.nzbri.elapse"

using namespace org::nzbri::elapse;


DeviceProxy::DeviceProxy(QObject *parent) :
    QObject(parent),
    _device(nullptr),
    _battery(nullptr),
    _eeg(nullptr)
{
}

DeviceProxy::~DeviceProxy()
{
    qDeleteAll(_eeg_channels);
    delete _eeg;
    delete _battery;
    delete _device;
}

Device *DeviceProxy::device() const
{
    return _device;
}

org::nzbri::elapse::Battery *DeviceProxy::battery() const
{
    return _battery;
}

Eeg::EegAdc *DeviceProxy::eeg() const
{
    return _eeg;
}

Eeg::EegChannel *DeviceProxy::eeg_channel(uint i) const
{
    return _eeg_channels.at(i);
}

QString DeviceProxy::deviceAddress() const
{
    return QSettings().value("host", DEFAULT_HOST).toString();
}

QString DeviceProxy::localAddress() const
{
    return localAddr;
}

void DeviceProxy::connect()
{
    QtConcurrent::run(this, &DeviceProxy::connectInBackground);
}

void DeviceProxy::connectInBackground()
{
    QSettings settings;
    QString host = deviceAddress();
    uint port = settings.value("port", DEFAULT_PORT).toUInt();
    QString address = QString("tcp:host=%1,port=%2").arg(host).arg(port);

    if (!detectLocalAddressByConnectingTo(host, port))
        return;

    // Connect to the remote session bus
    auto connection = QDBusConnection::connectToBus(address, "elapse-bus");
    if (!connection.isConnected()) {
        qxtLog->error("Connect:", connection.lastError().message());
        emit error("Could not connect to the device.");
        return;
    }

    _device = new Device(SERVICE, "/elapse", connection);

    // Check whether the root object is accessible on the bus
    auto reply = _device->isAccessible();
    reply.waitForFinished();
    if (reply.isError()) {
        qxtLog->error("Server:", reply.error().message());
        qxtLog->error("Proxy:", _device->lastError().message());
        emit error("The server is not running on the device.");
        return;
    }

    _battery = new Battery(SERVICE, "/elapse/battery", connection);
    _eeg = new Eeg::EegAdc(SERVICE, "/elapse/eeg", connection);

    for (uint i = 0; i < _eeg->nChannels(); i++) {
        auto ch = new Eeg::EegChannel(SERVICE,
                                      QString("/elapse/eeg/channel/%1").arg(i),
                                      connection);
        _eeg_channels.append(ch);
    }

    emit connected();
}

void DeviceProxy::disconnect()
{
    delete _device;
    _device = nullptr;

    delete _battery;
    _battery = nullptr;

    delete _eeg;
    _eeg = nullptr;

    qDeleteAll(_eeg_channels);
    _eeg_channels.clear();

    emit disconnected();
}

bool DeviceProxy::detectLocalAddressByConnectingTo(const QString &host,
                                                     quint16 port)
{
    QTcpSocket sock;
    sock.connectToHost(host, port);

    if (!sock.waitForConnected(5000)) {
        qxtLog->error("Connect:", sock.errorString());
        emit error("Could not connect to the device.");
        return false;
    }

    localAddr = sock.localAddress().toString();
    return true;
}
