include(../../global.pri)

TARGET   = pluginmanager

QT       = core gui widgets
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pluginmanager.cpp

HEADERS += pluginmanager.h \
           plugin_base.h

FORMS   += pluginmanager.ui
