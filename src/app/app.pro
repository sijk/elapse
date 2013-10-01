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
                datasource.h \
                eegfilesink.h
FORMS        += mainwindow.ui \
                plugindialog.ui
RESOURCES    += ../../elapse.qrc

LIBS            += -L$$OUT_PWD/../pluginloader/ -lpluginloader
INCLUDEPATH     += $$PWD/../pluginloader
DEPENDPATH      += $$PWD/../pluginloader
PRE_TARGETDEPS  += $$OUT_PWD/../pluginloader/libpluginloader.a

LIBS            += -L$$OUT_PWD/../decoders/eeg/ -leegdecoder
INCLUDEPATH     += $$PWD/../decoders/eeg
DEPENDPATH      += $$PWD/../decoders/eeg
PRE_TARGETDEPS  += $$OUT_PWD/../decoders/eeg/libeegdecoder.a

LIBS            += -L$$OUT_PWD/../stripchart/ -lstripchart
INCLUDEPATH     += $$PWD/../stripchart
DEPENDPATH      += $$PWD/../stripchart
PRE_TARGETDEPS  += $$OUT_PWD/../stripchart/libstripchart.a
