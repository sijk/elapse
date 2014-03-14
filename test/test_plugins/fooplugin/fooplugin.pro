include(../../../plugin.pri)

TARGET   = fooplugin
DESTDIR  = ..

SOURCES += fooeegdecoder.cpp foodummysource.cpp
HEADERS += fooeegdecoder.h foodummysource.h

HEADERS += fooplugin.h
HEADERS += plugin.h elements/decoder.h elements/datasource.h
