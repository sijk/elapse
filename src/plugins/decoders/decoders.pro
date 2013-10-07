include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
QT             += network
DESTDIR         = ../../../plugins/

# Plugin-specific settings
HEADERS         = eegdecoder.h \
                  decodersplugin.h \
                  decoder.h \
                  plugin.h
SOURCES         = eegdecoder.cpp
TARGET          = $$qtLibraryTarget(decodersplugin)
