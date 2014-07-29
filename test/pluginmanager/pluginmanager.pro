include(../test.pri)

QT        += gui widgets
CONFIG    += qxt link_pkgconfig
QXT       += core
PKGCONFIG += python2

SOURCES   += pluginmanager_test.cpp \
             nativehost_test.cpp \
             pythonhost_test.cpp

INCLUDEPATH += $$ROOT/app/include $$shadowed($$ROOT/app/lib/pluginmanager)
linkStaticlib(app, pluginmanager)
linkSharedlib(app, elapseplugin, true)

LIBS += -lboost_python

