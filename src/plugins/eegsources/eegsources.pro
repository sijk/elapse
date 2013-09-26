include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
QT             += network
DESTDIR         = ../../../plugins/

# Plugin-specific settings
HEADERS         = tcpclienteegdatasource.h \
                  udpeegdatasource.h \
                  threadedtcpclienteegdatasource.h \
                  eegthread.h \
                  datasource.h \
                  eegsourcesplugin.h \
                  plugin.h
SOURCES         = tcpclienteegdatasource.cpp \
                  udpeegdatasource.cpp \
                  threadedtcpclienteegdatasource.cpp \
                  eegthread.cpp
TARGET          = $$qtLibraryTarget(eegsourcesplugin)
