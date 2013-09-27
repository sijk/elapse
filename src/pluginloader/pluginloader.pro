include(../../global.pri)

TARGET   = pluginloader

QT       = core
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pluginloader.cpp
HEADERS += pluginloader.h \
           plugin_base.h
