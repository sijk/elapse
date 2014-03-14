include(../../global.pri)
include(../test.pri)

SOURCES += tst_eegdecoder.cpp \
           eegdecoder.cpp

HEADERS += eegdecoder.h \
           decoder.h

INCLUDEPATH += ../../src/plugins/decoders
VPATH += ../../src/plugins/decoders
