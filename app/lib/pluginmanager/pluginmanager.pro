include(../../../staticlib.pri)

QT      += gui widgets

CONFIG  += link_pkgconfig
PKGCONFIG += python2

SOURCES += pluginmanager.cpp \
           pluginhost.cpp \
           nativepluginhost.cpp \
           pythonpluginhost.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginmanager_global.h \
           pluginhost.h \
           nativepluginhost.h \
           pythonpluginhost.h

FORMS   += pluginmanager.ui

SOURCES += native/util.cpp
HEADERS += native/util.h

SOURCES += python/host.cpp
HEADERS += python/host.h \
           python/bindings/elapse.h \
           python/bindings/elements.h

