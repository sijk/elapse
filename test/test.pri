include(../global.pri)
include(gmock/gmock.pri)

CONFIG += testcase
QT -= gui

SOURCES += $$PWD/test_main.cpp
HEADERS += $$PWD/test_utils.h

