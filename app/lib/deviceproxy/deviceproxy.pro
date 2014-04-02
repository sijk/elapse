include(../../../staticlib.pri)
include($$ROOT/common/interfaces.pri)

QT      += dbus network

SOURCES += deviceproxy.cpp

HEADERS += deviceproxy.h \
           interfaces.h

DBUS_INTERFACES = $$ELAPSE_DBUS_XML
