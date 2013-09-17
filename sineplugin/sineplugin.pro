#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:52:26
#
#-------------------------------------------------

# Directory containing the plugin interface headers
INTERFACE_DIR   = ../include

# Generic plugin settings
TEMPLATE        = lib
QT             += network
CONFIG         += plugin c++11
INCLUDEPATH    += $$INTERFACE_DIR
VPATH          += $$INTERFACE_DIR
DESTDIR         = ../plugins

# Plugin-specific settings
HEADERS         = tcpprovider.h \
                  sineprovider.h \
                  dataprovider.h \
                  sineplugin.h \
                  plugin.h
SOURCES         = tcpprovider.cpp \
                  sineprovider.cpp
TARGET          = $$qtLibraryTarget(sineplugin)
