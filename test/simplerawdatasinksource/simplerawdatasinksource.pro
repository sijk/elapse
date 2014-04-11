include(../test.pri)

QT += widgets testlib

INCLUDEPATH += $$ROOT/coreplugin/src
VPATH += $$ROOT/coreplugin/src

SOURCES += simplerawdatasinkdelegate.cpp simplerawdatasource.cpp
HEADERS += simplerawdatasinkdelegate.h simplerawdatasource.h

SOURCES += simplerawdatasinksource_test.cpp

linkSharedlib(app, elapseplugin, true)

