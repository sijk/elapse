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
CONFIG         += plugin
INCLUDEPATH    += $$INTERFACE_DIR
VPATH          += $$INTERFACE_DIR
DESTDIR         = ../plugins

# Plugin-specific settings
HEADERS         = tcpprovider.h\
                  dataproviderinterface.h
SOURCES         = tcpprovider.cpp
TARGET          = $$qtLibraryTarget(tcpdata)
