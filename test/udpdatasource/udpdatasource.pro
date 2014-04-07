include(../test.pri)

QT += network testlib

SOURCES += udpdatasource_test.cpp

INCLUDEPATH += $$ROOT/coreplugin/src
VPATH += $$ROOT/coreplugin/src

SOURCES += udpdatasource.cpp
HEADERS += udpdatasource.h \
           elapse/elements/datasource.h

linkSharedlib(app, elapseplugin, true)
