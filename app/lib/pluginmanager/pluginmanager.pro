include(../../../staticlib.pri)

QT      += gui widgets

CONFIG  += link_pkgconfig
PKGCONFIG += python2

SOURCES += pluginmanager.cpp \
           nativepluginhost.cpp \
           pythonpluginhost.cpp \
           python/util.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginmanager_global.h \
           pluginhost.h \
           nativepluginhost.h \
           pythonpluginhost.h \
           python/util.h \
           python/bindings/elapse.h \
           python/bindings/elements.h

FORMS   +=
