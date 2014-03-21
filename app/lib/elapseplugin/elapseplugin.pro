include(../../../global.pri)

QT       = core gui
TEMPLATE = lib
CONFIG  += shared qxt
QXT     += core

TARGET   = elapseplugin

SOURCES += classifier.cpp

HEADERS += elapse/elements/classifier.h

