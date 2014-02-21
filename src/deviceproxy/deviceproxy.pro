include(../staticlib.pri)

QT      += dbus network

SOURCES += deviceproxy.cpp

HEADERS += deviceproxy.h

DBUS_INTERFACES = \
    ../../../elapse-server/files/src/interfaces/elapse.xml \
    ../../../elapse-server/files/src/interfaces/eeg.xml
