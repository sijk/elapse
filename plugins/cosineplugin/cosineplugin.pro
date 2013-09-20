include(../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
QT             += network
CONFIG         += plugin
DESTDIR         = ../../plugins

# Plugin-specific settings
HEADERS         = cosineprovider.h \
                  dataprovider.h \
                  cosineplugin.h \
                  plugin.h
SOURCES         = cosineprovider.cpp
TARGET          = $$qtLibraryTarget(cosineplugin)
