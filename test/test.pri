include(../global.pri)
include(gmock/gmock.pri)

CONFIG += testcase qxt
QT += testlib
QXT += core

SOURCES += $$PWD/test_main.cpp
HEADERS += $$PWD/test_utils.h

