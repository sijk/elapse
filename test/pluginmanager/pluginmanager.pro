include(../test.pri)

QT      += gui widgets
CONFIG  += qxt
QXT     += core

SOURCES += pluginmanager_test.cpp \
           elementsetfactory_test.cpp

INCLUDEPATH += $$ROOT/app/include
INCLUDEPATH += $$shadowed($$ROOT/app/lib/pluginmanager)
linkStaticlib(app, pluginmanager)
linkSharedlib(app, elapseplugin, true)

