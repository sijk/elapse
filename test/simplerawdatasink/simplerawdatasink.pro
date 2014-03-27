include(../test.pri)

QT += widgets

INCLUDEPATH += $$ROOT/coreplugin/src
VPATH += $$ROOT/coreplugin/src

SOURCES += simplerawdatasinkdelegate.cpp
HEADERS += simplerawdatasinkdelegate.h

SOURCES += simplerawdatasink_test.cpp

linkSharedlib(app, elapseplugin, true)

