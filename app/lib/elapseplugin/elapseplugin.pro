include(../../../global.pri)

QT       = core gui
TEMPLATE = lib
CONFIG  += shared qxt
QXT     += core

TARGET   = elapseplugin

SOURCES += \
    featurextractor.cpp \
    classifier.cpp \
    datasinkdelegate.cpp

HEADERS += \
    elapse/sampletypes.h \
    elapse/elements/datasource.h \
    elapse/elements/decoder.h \
    elapse/elements/featurextractor.h \
    elapse/elements/classifier.h \
    elapse/elements/datasinkdelegate.h

