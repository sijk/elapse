include(../../global.pri)

TARGET   = pluginmanager

QT       = core gui widgets
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pluginmanager.cpp \
           pluginfilterproxymodel.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginfilterproxymodel.h \
           plugin.h

FORMS   += pluginmanager.ui
