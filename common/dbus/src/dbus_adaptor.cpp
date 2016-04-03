#include <qxtlogger.h>
#include "common/hardware.h"
#include "common/dbus/paths.h"
#include "common/dbus/adaptor.h"

// Generated headers
#include "device_adaptor.h"
#include "battery_adaptor.h"
#include "eegadc_adaptor.h"
#include "eegchannel_adaptor.h"
#include "imu_adaptor.h"

namespace elapse { namespace common { namespace dbus {

/*!
 * Construct a dbus::Adaptor to expose the given \a device and all
 * of its sub-systems to D-Bus.
 *
 * This constructor will abort with \c qFatal() if it fails to connect to the
 * bus and register all objects.
 *
 * When exposing a simulated device, rather than the real thing, set
 * \a isFake = true. This will expose the \a device on the session bus rather
 * than the system bus.
 */
Adaptor::Adaptor(hardware::Device *device, bool isFake) :
    con(isFake ? QDBusConnection::sessionBus() : QDBusConnection::systemBus())
{
    if (!con.isConnected())
        qxtLog->fatal("Could not open D-Bus connection.");

    if (!con.registerService(dbus::service))
        qxtLog->fatal("Could not register service.");

    registerObject<DeviceAdaptor>(dbus::rootPath, device);
    registerObject<BatteryAdaptor>(dbus::batteryPath, device->battery());
    registerObject<EegAdcAdaptor>(dbus::eegPath, device->eeg());

    uint nChannels = device->eeg()->nChannels();
    for (uint i = 0; i < nChannels; i++)
        registerObject<EegChannelAdaptor>(dbus::eegChanPath.arg(i),
                                          device->eeg()->channel(i));

    registerObject<ImuAdaptor>(dbus::imuPath, device->imu());
}

/*!
 * Convenience method for registering an object on the bus.
 */
template<class AdaptorClass, class Class>
void Adaptor::registerObject(QString path, Class *obj)
{
    new AdaptorClass(obj);
    if (!con.registerObject(path, obj))
        qxtLog->fatal("Could not register object", path);
}

}}} // namespace elapse::common::dbus
