include(../../../staticlib.pri)
include($$ROOT/common/hardware.pri)

QT      += dbus network

SOURCES += deviceproxy.cpp

HEADERS += deviceproxy.h \
           dbus_interfaces.h

DBUS_INTERFACES = $$ELAPSE_DBUS_XML
