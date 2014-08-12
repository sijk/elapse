include(../../../staticlib.pri)

QT      += gui widgets

CONFIG  += link_pkgconfig link_prl
PKGCONFIG += python2

SOURCES += pluginmanager.cpp \
           pluginhost.cpp \
           staticpluginhost.cpp \
           nativepluginhost.cpp \
           pythonpluginhost.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginmanager_global.h \
           pluginhost.h \
           staticpluginhost.h \
           nativepluginhost.h \
           pythonpluginhost.h

FORMS   += pluginmanager.ui

SOURCES += native/util.cpp
HEADERS += native/util.h

SOURCES += python/host.cpp
HEADERS += python/host.h \
           python/exception.h \
           python/bindings/elapse.h \
           python/bindings/elements.h \
           python/bindings/log.h \
           python/bindings/settings.h

LIBS    += -lboost_python

LIBS += -L$$OUT_PWD/../../../coreplugin/src/ -lcoreplugin
DEPENDPATH += $$PWD/../../../coreplugin/src
PRE_TARGETDEPS += $$OUT_PWD/../../../coreplugin/src/libcoreplugin.a
