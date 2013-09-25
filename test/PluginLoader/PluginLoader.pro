include(../test.pri)

SOURCES += tst_pluginloadertest.cpp

LIBS += -L$$OUT_PWD/../../src/pluginloader/ -lpluginloader
INCLUDEPATH += $$PWD/../../src/pluginloader
DEPENDPATH += $$PWD/../../src/pluginloader
PRE_TARGETDEPS += $$OUT_PWD/../../src/pluginloader/libpluginloader.a
