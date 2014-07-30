include(../test.pri)

QT += widgets testlib

INCLUDEPATH += $$ROOT/coreplugin/src
VPATH += $$ROOT/coreplugin/src

SOURCES += simplerawdatasink.cpp simplerawdatasource.cpp
HEADERS += simplerawdatasink.h simplerawdatasource.h

SOURCES += simplerawdatasinksource_test.cpp

linkSharedlib(app, elapseplugin, true)

