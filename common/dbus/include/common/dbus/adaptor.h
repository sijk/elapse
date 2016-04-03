#ifndef DEVICEDBUSADAPTOR_H
#define DEVICEDBUSADAPTOR_H

#include <QDBusConnection>

namespace elapse {
namespace hardware { class Device; }
namespace common { namespace dbus {

/*!
 * \brief The dbus::Adaptor class exposes a hardware::Device
 * over D-Bus.
 * \headerfile common/dbus/adaptor.h
 */

class Adaptor
{
public:
    explicit Adaptor(hardware::Device *device, bool isFake = false);
private:
    QDBusConnection con;

    template<class AdaptorClass, class Class>
    void registerObject(QString path, Class *obj);
};

}}} // namespace elapse::common::dbus

#endif // DEVICEDBUSADAPTOR_H
