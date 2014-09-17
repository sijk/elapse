include(../test.pri)

CONFIG += link_pkgconfig
PKGCONFIG += eigen3

SOURCES += simpleeegfeatex_test.cpp

linkSharedlib(app, elapseplugin, true)

