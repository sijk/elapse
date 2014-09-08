include(../test.pri)
include($$ROOT/common/hardware.pri)

QT += dbus network testlib

SOURCES += configdbus_test.cpp

HEADERS += elapse/elements/datasource.h

linkSharedlib(app, elapseplugin, true)
linkStaticlib(app, deviceproxy)
