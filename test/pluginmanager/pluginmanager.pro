include(../test.pri)

QT += gui widgets
CONFIG += qxt
QXT += core

SOURCES += pluginmanager_test.cpp

INCLUDEPATH += $$ROOT/app/include
INCLUDEPATH += ../test_plugins
VPATH       += ../test_plugins

linkStaticlib(app, pluginmanager)

