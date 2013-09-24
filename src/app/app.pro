include(../../global.pri)

QT           += core gui widgets network
CONFIG       += qwt

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                mainwindow.cpp \
                plugindialog.cpp \
                tcpclienteegdatasource.cpp
#                udpeegdatasource.cpp
HEADERS      += mainwindow.h \
                plugindialog.h \
                dataprovider.h \
                datasource.h \
                eegdecoder.h \
                tcpclienteegdatasource.h
#                udpeegdatasource.h
FORMS        += mainwindow.ui \
                plugindialog.ui

LIBS            += -L$$OUT_PWD/../pluginloader/ -lpluginloader
INCLUDEPATH     += $$PWD/../pluginloader
DEPENDPATH      += $$PWD/../pluginloader
PRE_TARGETDEPS  += $$OUT_PWD/../pluginloader/libpluginloader.a

LIBS            += -L$$OUT_PWD/../decoders/eeg/ -leegdecoder
INCLUDEPATH     += $$PWD/../decoders/eeg
DEPENDPATH      += $$PWD/../decoders/eeg
PRE_TARGETDEPS  += $$OUT_PWD/../decoders/eeg/libeegdecoder.a
