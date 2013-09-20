include(../../global.pri)

QT           += core gui widgets
CONFIG       += qwt

TARGET        = elapse
TEMPLATE      = app

DESTDIR       = ../../

SOURCES      += main.cpp \
                mainwindow.cpp \
                plugindialog.cpp
HEADERS      += mainwindow.h \
                plugindialog.h \
                dataprovider.h
FORMS        += mainwindow.ui \
                plugindialog.ui

# Link to PluginLoader
LIBS            += -L$$OUT_PWD/../pluginloader/ -lpluginloader
INCLUDEPATH     += $$PWD/../pluginloader
DEPENDPATH      += $$PWD/../pluginloader
PRE_TARGETDEPS  += $$OUT_PWD/../pluginloader/libpluginloader.a
