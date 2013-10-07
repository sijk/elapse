include(../../global.pri)

TARGET   = pipeline

QT       = core
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += pipeline.cpp
HEADERS += pipeline.h


LIBS += -L$$OUT_PWD/../pluginloader/ -lpluginloader
INCLUDEPATH += $$PWD/../pluginloader
DEPENDPATH += $$PWD/../pluginloader
PRE_TARGETDEPS += $$OUT_PWD/../pluginloader/libpluginloader.a
