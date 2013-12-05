include(../../global.pri)

TEMPLATE        = lib
CONFIG         += plugin
QT             += network
DESTDIR         = ../../plugins/

HEADERS         = eegdecoder.h \
                  tcpclientdatasource.h \
                  dummyeegsource.h \
                  coreplugin.h \
                  elements/datasource.h \
                  elements/decoder.h \
                  plugin.h

SOURCES         = eegdecoder.cpp \
                  tcpclientdatasource.cpp \
                  dummyeegsource.cpp

TARGET          = $$qtLibraryTarget(coreplugin)
