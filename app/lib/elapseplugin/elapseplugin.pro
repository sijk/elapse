include(../../../global.pri)
include($$ROOT/common/hardware.pri)

QT       = core gui dbus
TEMPLATE = lib
CONFIG  += shared qxt link_pkgconfig
QXT     += core
PKGCONFIG= eigen3

TARGET   = elapseplugin

HEADERS += \
    configproxies.h \
    featurextractor_p.h

SOURCES += \
    offlinedatasource.cpp \
    featurextractor.cpp \
    classifier.cpp \
    datasink.cpp

HEADERS += \
    elapse/timestamps.h \
    elapse/datatypes.h \
    elapse/elements/datasource.h \
    elapse/elements/decoder.h \
    elapse/elements/featurextractor.h \
    elapse/elements/classifier.h \
    elapse/elements/outputaction.h \
    elapse/elements/datasink.h \
    elapse/elements/simple/eegfeaturextractor.h

LIBS += -L$$OUT_PWD/../../../common/dbus/ -ldbus
INCLUDEPATH += $$PWD/../../../common/dbus
DEPENDPATH += $$PWD/../../../common/dbus
PRE_TARGETDEPS += $$OUT_PWD/../../../common/dbus/libdbus.a

