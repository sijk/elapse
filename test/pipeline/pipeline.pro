include(../test.pri)

SOURCES += pipeline_test.cpp

INCLUDEPATH += $$ROOT/app/include
linkStaticlib(app, pipeline)
linkSharedlib(app, elapseplugin, true)

QMAKE_CXXFLAGS += -Wno-unused-variable

