include(../../../global.pri)

TARGET   = eegdecoder

QT       = core
TEMPLATE = lib
CONFIG  += staticlib

SOURCES += eegdecoder.cpp
HEADERS += eegdecoder.h \
           sampletypes.h \
           ../decoder.h
