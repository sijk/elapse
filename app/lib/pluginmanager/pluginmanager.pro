include(../../../staticlib.pri)

QT      += gui widgets

CONFIG  += link_pkgconfig
PKGCONFIG += python2

SOURCES += pluginmanager.cpp \
           nativepluginhost.cpp \
           pythonpluginhost.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginmanager_global.h \
           pluginhost.h \
           nativepluginhost.h \
           pythonpluginhost.h

FORMS   +=
