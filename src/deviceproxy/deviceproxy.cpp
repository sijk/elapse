#include <QDBusConnection>
#include "deviceproxy.h"

const QString SERVICE("org.nzbri.elapse");

using namespace org::nzbri::elapse;


DeviceProxy::DeviceProxy(QObject *parent) :
    QObject(parent)
{
    device = new Device(SERVICE, "/elapse", QDBusConnection::sessionBus());

    // TODO: implement method on the server to test connectivity
    if (device->hello() != "Hello, world!") {
        qDebug() << "Could not connect to remote session bus.";
        return;
    }

    eeg = new Eeg::EegAdc(SERVICE, "/elapse/eeg", QDBusConnection::sessionBus());

    for (uint i = 0; i < eeg->nChannels(); i++) {
        auto ch = new Eeg::EegChannel(SERVICE,
                                      QString("/elapse/eeg/channel/%1").arg(i),
                                      QDBusConnection::sessionBus());
        eeg_channels.append(ch);
    }

    qDebug() << eeg_channels.size() << eeg_channels[0]->gain();
}
