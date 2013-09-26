include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
QT             += network
CONFIG         += plugin
DESTDIR         = ../

# Plugin-specific settings
HEADERS         = tcpprovider.h \
                  sineprovider.h \
                  dataprovider.h \
                  sineplugin.h \
                  plugin.h
SOURCES         = tcpprovider.cpp \
                  sineprovider.cpp
TARGET          = $$qtLibraryTarget(sineplugin)

INCLUDEPATH    += ..
VPATH          += ..
