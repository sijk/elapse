include(../../../staticlib.pri)
include($$ROOT/common/interfaces.pri)

QT      += dbus network

SOURCES += deviceproxy.cpp

HEADERS += deviceproxy.h \
           dbus_interfaces.h

DBUS_INTERFACES = $$ELAPSE_DBUS_XML
