include(../test.pri)

QT      += gui widgets
CONFIG  += qxt
QXT     += core

SOURCES += pluginmanager_test.cpp

INCLUDEPATH += $$ROOT/app/include
linkStaticlib(app, pluginmanager)

