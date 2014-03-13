include(../../../plugin.pri)

TARGET   = barplugin
DESTDIR  = ..

SOURCES += bareegdecoder.cpp barvideodecoder.cpp
HEADERS += bareegdecoder.h barvideodecoder.h

HEADERS += barplugin.h
HEADERS += plugin.h elements/decoder.h

