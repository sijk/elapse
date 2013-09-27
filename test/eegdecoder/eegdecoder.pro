include(../test.pri)

SOURCES += tst_eegdecoder.cpp

LIBS += -L$$OUT_PWD/../../src/decoders/eeg/ -leegdecoder
INCLUDEPATH += $$PWD/../../src/decoders/eeg
DEPENDPATH += $$PWD/../../src/decoders/eeg
PRE_TARGETDEPS += $$OUT_PWD/../../src/decoders/eeg/libeegdecoder.a
