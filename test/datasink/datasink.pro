include(../test.pri)

SOURCES += datasink_test.cpp

linkStaticlib(app, pipeline)
linkSharedlib(app, elapseplugin, true)

