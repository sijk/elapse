include(../test.pri)
include(../../global.pri)

SOURCES += tst_pluginloadertest.cpp
HEADERS += producer.h consumer.h

INCLUDEPATH += ../test_plugins
VPATH       += ../test_plugins

LIBS += -L$$OUT_PWD/../../src/pluginloader/ -lpluginloader
INCLUDEPATH += $$PWD/../../src/pluginloader
DEPENDPATH += $$PWD/../../src/pluginloader
PRE_TARGETDEPS += $$OUT_PWD/../../src/pluginloader/libpluginloader.a
