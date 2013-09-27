include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
QT             += network
CONFIG         += plugin
DESTDIR         = ../

# Plugin-specific settings
HEADERS         = tcpproducer.h \
                  sineproducer.h \
                  producer.h \
                  sineplugin.h \
                  plugin.h
SOURCES         = tcpproducer.cpp \
                  sineproducer.cpp
TARGET          = $$qtLibraryTarget(sineplugin)

INCLUDEPATH    += ..
VPATH          += ..
