include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
DESTDIR         = ../

# Plugin-specific settings
HEADERS         = cosineprovider.h \
                  dataprovider.h \
                  cosineplugin.h \
                  plugin.h
SOURCES         = cosineprovider.cpp
TARGET          = $$qtLibraryTarget(cosineplugin)

INCLUDEPATH    += ..
VPATH          += ..
