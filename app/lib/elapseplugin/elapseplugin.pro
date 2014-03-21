include(../../../global.pri)

QT       = core gui
TEMPLATE = lib
CONFIG  += shared qxt
QXT     += core

TARGET   = elapseplugin

SOURCES += \
    featurextractor.cpp \
    classifier.cpp \

HEADERS += \
    elapse/elements/featurextractor.h \
    elapse/elements/classifier.h

