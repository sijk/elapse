include(../../global.pri)

QT           += core gui widgets dbus
CONFIG       += qwt qxt
QXT          += core

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                elapseclient.cpp \
                spinner.cpp \
                eegfilesink.cpp
HEADERS      += elapseclient.h \
                spinner.h \
                eegfilesink.h \
                elements.h
FORMS        += elapseclient.ui
RESOURCES    += ../../elapse.qrc

LIBS            += -L$$OUT_PWD/../pipeline/ -lpipeline
INCLUDEPATH     += $$PWD/../pipeline
DEPENDPATH      += $$PWD/../pipeline
PRE_TARGETDEPS  += $$OUT_PWD/../pipeline/libpipeline.a

LIBS            += -L$$OUT_PWD/../pluginmanager/ -lpluginmanager
INCLUDEPATH     += $$PWD/../pluginmanager
DEPENDPATH      += $$PWD/../pluginmanager
PRE_TARGETDEPS  += $$OUT_PWD/../pluginmanager/libpluginmanager.a

LIBS            += -L$$OUT_PWD/../stripchart/ -lstripchart
INCLUDEPATH     += $$PWD/../stripchart
DEPENDPATH      += $$PWD/../stripchart
PRE_TARGETDEPS  += $$OUT_PWD/../stripchart/libstripchart.a

LIBS            += -L$$OUT_PWD/../pluginmanager/ -lpluginmanager
INCLUDEPATH     += $$PWD/../pluginmanager
DEPENDPATH      += $$PWD/../pluginmanager
PRE_TARGETDEPS  += $$OUT_PWD/../pluginmanager/libpluginmanager.a

LIBS            += -L$$OUT_PWD/../deviceproxy/ -ldeviceproxy
INCLUDEPATH     += $$PWD/../deviceproxy
DEPENDPATH      += $$PWD/../deviceproxy
PRE_TARGETDEPS  += $$OUT_PWD/../deviceproxy/libdeviceproxy.a
INCLUDEPATH     += $$OUT_PWD/../deviceproxy   # for foo_interface.h

LIBS            += -L$$OUT_PWD/../loggerwidget/ -lloggerwidget
INCLUDEPATH     += $$PWD/../loggerwidget
DEPENDPATH      += $$PWD/../loggerwidget
PRE_TARGETDEPS  += $$OUT_PWD/../loggerwidget/libloggerwidget.a
