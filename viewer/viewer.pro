#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:52:26
#
#-------------------------------------------------

QT           += core gui widgets
CONFIG       += c++11 qwt

DESTDIR       = ../
INTERFACE_DIR = ../include
INCLUDEPATH  += $$INTERFACE_DIR
VPATH        += $$INTERFACE_DIR

TARGET        = elapse
TEMPLATE      = app

SOURCES      += main.cpp \
                mainwindow.cpp \
                dataproviderplugin.cpp
HEADERS      += mainwindow.h \
                dataprovider.h \
                dataproviderplugin.h
FORMS        += mainwindow.ui
