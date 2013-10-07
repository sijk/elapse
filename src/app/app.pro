include(../../global.pri)

QT           += core gui widgets
CONFIG       += qwt

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                mainwindow.cpp \
                plugindialog.cpp \
                eegfilesink.cpp
HEADERS      += mainwindow.h \
                plugindialog.h \
                eegfilesink.h \
                datasource.h \
                decoder.h
FORMS        += mainwindow.ui \
                plugindialog.ui
RESOURCES    += ../../elapse.qrc

LIBS            += -L$$OUT_PWD/../pipeline/ -lpipeline
INCLUDEPATH     += $$PWD/../pipeline
DEPENDPATH      += $$PWD/../pipeline
PRE_TARGETDEPS  += $$OUT_PWD/../pipeline/libpipeline.a

LIBS            += -L$$OUT_PWD/../pluginloader/ -lpluginloader
INCLUDEPATH     += $$PWD/../pluginloader
DEPENDPATH      += $$PWD/../pluginloader
PRE_TARGETDEPS  += $$OUT_PWD/../pluginloader/libpluginloader.a

LIBS            += -L$$OUT_PWD/../stripchart/ -lstripchart
INCLUDEPATH     += $$PWD/../stripchart
DEPENDPATH      += $$PWD/../stripchart
PRE_TARGETDEPS  += $$OUT_PWD/../stripchart/libstripchart.a
