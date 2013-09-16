#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:52:26
#
#-------------------------------------------------

# Directory containing the plugin interface headers
INTERFACE_DIR   = ../include

# Generic plugin settings
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += $$INTERFACE_DIR
VPATH          += $$INTERFACE_DIR
DESTDIR         = ../plugins

# Plugin-specific settings
HEADERS         = sineprovider.h\
                  dataproviderinterface.h
SOURCES         = sineprovider.cpp
TARGET          = $$qtLibraryTarget(sinedata)
