include(../../../plugin.pri)

TARGET   = fooplugin
DESTDIR  = ..

SOURCES += fooeegdecoder.cpp
HEADERS += fooeegdecoder.h
HEADERS += fooplugin.h

HEADERS += plugin.h elements/decoder.h
