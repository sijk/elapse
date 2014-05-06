include(../../../global.pri)
include($$ROOT/common/interfaces.pri)

QT       = core gui dbus
TEMPLATE = lib
CONFIG  += shared qxt
QXT     += core

TARGET   = elapseplugin

HEADERS += \
    configproxies.h \
    featurextractor_p.h

SOURCES += \
    offlinedatasource.cpp \
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

LIBS += -L$$OUT_PWD/../../../common/dbus/ -ldbus
INCLUDEPATH += $$PWD/../../../common/dbus
DEPENDPATH += $$PWD/../../../common/dbus
PRE_TARGETDEPS += $$OUT_PWD/../../../common/dbus/libdbus.a

