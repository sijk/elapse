include(../../global.pri)

QT           += core gui widgets
CONFIG       += qwt

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                mainwindow.cpp \
                eegfilesink.cpp
HEADERS      += mainwindow.h \
                eegfilesink.h \
                datasource.h \
                decoder.h
FORMS        += mainwindow.ui
RESOURCES    += ../../elapse.qrc

LIBS            += -L$$OUT_PWD/../pipeline/ -lpipeline
INCLUDEPATH     += $$PWD/../pipeline
DEPENDPATH      += $$PWD/../pipeline
PRE_TARGETDEPS  += $$OUT_PWD/../pipeline/libpipeline.a

LIBS            += -L$$OUT_PWD/../pluginmanager/ -lpluginmanager
INCLUDEPATH     += $$PWD/../pluginmanager
DEPENDPATH      += $$PWD/../pluginmanager
PRE_TARGETDEPS  += $$OUT_PWD/../pluginmanager/libpluginmanager.a

LIBS            += -L$$OUT_PWD/../stripchart/ -lstripchart
INCLUDEPATH     += $$PWD/../stripchart
DEPENDPATH      += $$PWD/../stripchart
PRE_TARGETDEPS  += $$OUT_PWD/../stripchart/libstripchart.a

LIBS            += -L$$OUT_PWD/../pluginmanager/ -lpluginmanager
INCLUDEPATH     += $$PWD/../pluginmanager
DEPENDPATH      += $$PWD/../pluginmanager
PRE_TARGETDEPS  += $$OUT_PWD/../pluginmanager/libpluginmanager.a
