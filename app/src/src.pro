include(../../global.pri)

QT           += core gui widgets dbus network
CONFIG       += qxt qwt
QXT          += core

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                elapseclient.cpp \
                batterymonitor.cpp \
                spinner.cpp \
                eegfilesink.cpp
HEADERS      += elapseclient.h \
                batterymonitor.h \
                spinner.h \
                eegfilesink.h \
                elementset.h \
                elapse/displayable.h
FORMS        += elapseclient.ui
RESOURCES    += ../img/images.qrc

linkStaticlib(deviceproxy)
linkStaticlib(pipeline)
linkStaticlib(pluginmanager)
linkStaticlib(loggerwidget)

INCLUDEPATH  += $$OUT_PWD/../lib/deviceproxy   # for foo_interface.h
