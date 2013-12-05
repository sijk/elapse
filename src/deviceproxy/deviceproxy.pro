include(../staticlib.pri)

QT      += dbus

SOURCES += deviceproxy.cpp

HEADERS += deviceproxy.h

DBUS_INTERFACES = \
    ../../../elapse-server/files/interfaces/elapse.xml \
    ../../../elapse-server/files/interfaces/eeg.xml
