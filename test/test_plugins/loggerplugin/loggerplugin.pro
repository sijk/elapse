include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
DESTDIR         = ../

# Plugin-specific settings
HEADERS         = loggerconsumer.h \
                  consumer.h \
                  loggerplugin.h \
                  plugin.h
SOURCES         = loggerconsumer.cpp
TARGET          = $$qtLibraryTarget(loggerplugin)

INCLUDEPATH    += ..
VPATH          += ..
