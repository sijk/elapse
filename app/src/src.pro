include(../../global.pri)

QT           += core gui widgets
CONFIG       += qxt qwt link_prl
QXT          += core

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                elapseclient.cpp \
                batterymonitor.cpp \
                spinner.cpp
HEADERS      += elapseclient.h \
                batterymonitor.h \
                spinner.h \
                elementset.h \
                elapse/displayable.h
FORMS        += elapseclient.ui
RESOURCES    += ../img/images.qrc

linkStaticlib(deviceproxy)
linkStaticlib(pipeline)
linkStaticlib(pluginmanager)
linkStaticlib(loggerwidget)

linkSharedlib(app, elapseplugin, true)

include($$ROOT/common/hardware.pri)
