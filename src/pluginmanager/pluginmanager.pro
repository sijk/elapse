include(../../global.pri)

TARGET   = pluginmanager

QT       = core gui
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pluginmanager.cpp

HEADERS += pluginmanager.h \
           plugin_base.h
