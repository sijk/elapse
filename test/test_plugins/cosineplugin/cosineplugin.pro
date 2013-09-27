include(../../../global.pri)

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
DESTDIR         = ../

# Plugin-specific settings
HEADERS         = cosineproducer.h \
                  producer.h \
                  cosineplugin.h \
                  test_plugins.h
SOURCES         = cosineproducer.cpp
TARGET          = $$qtLibraryTarget(cosineplugin)

INCLUDEPATH    += ..
VPATH          += ..
