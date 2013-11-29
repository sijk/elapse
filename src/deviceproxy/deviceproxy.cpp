#include <QDBusConnection>
#include <QSettings>
#include <QtConcurrent/QtConcurrentRun>
#include "deviceproxy.h"

#define DEFAULT_HOST    "overo.local"
#define DEFAULT_PORT    9000
#define SERVICE         "org.nzbri.elapse"

using namespace org::nzbri::elapse;


DeviceProxy::DeviceProxy(QObject *parent) :
    QObject(parent)
{
}

DeviceProxy::~DeviceProxy()
{
    qDeleteAll(_eeg_channels);
    delete _eeg;
    delete _device;
}

Device *DeviceProxy::device() const
{
    return _device;
}

Eeg::EegAdc *DeviceProxy::eeg() const
{
    return _eeg;
}

Eeg::EegChannel *DeviceProxy::eeg_channel(uint i) const
{
    return _eeg_channels.at(i);
}

QString DeviceProxy::host() const
{
    return QSettings().value("host", DEFAULT_HOST).toString();
}

void DeviceProxy::connect()
{
    QtConcurrent::run(this, &DeviceProxy::connectInBackground);
}

void DeviceProxy::connectInBackground()
{
    QSettings settings;
    uint port = settings.value("port", DEFAULT_PORT).toUInt();
    QString address = QString("tcp:host=%1,port=%2").arg(host()).arg(port);

    // Connect to the remote session bus
    auto connection = QDBusConnection::connectToBus(address, "elapse-bus");
    if (!connection.isConnected()) {
        qDebug() << connection.lastError().message();
        emit error("Could not connect to the device.");
        return;
    }

    _device = new Device(SERVICE, "/elapse", connection);

    // TODO: implement method on the server to test connectivity
    if (_device->hello() != "Hello, world!") {
        qDebug() << _device->lastError().message();
        emit error("The server is not running on the device.");
        return;
    }

    _eeg = new Eeg::EegAdc(SERVICE, "/elapse/eeg", connection);

    for (uint i = 0; i < _eeg->nChannels(); i++) {
        auto ch = new Eeg::EegChannel(SERVICE,
                                      QString("/elapse/eeg/channel/%1").arg(i),
                                      connection);
        _eeg_channels.append(ch);
    }

    emit connected();
}
