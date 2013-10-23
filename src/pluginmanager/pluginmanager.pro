include(../../global.pri)

TARGET   = pluginmanager

QT       = core gui widgets
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pluginmanager.cpp

HEADERS += pluginmanager.h \
           plugin.h

FORMS   += pluginmanager.ui
