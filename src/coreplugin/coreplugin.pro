include(../../global.pri)

TEMPLATE      = lib
CONFIG       += plugin link_pkgconfig qwt qxt
QT           += network opengl
DESTDIR       = ../../plugins/
PKGCONFIG     = Qt5GStreamer-0.10 Qt5GStreamerUtils-0.10 Qt5GStreamerUi-0.10
QXT          += core

HEADERS       = udpdatasource.h \
                dummyeegsource.h \
                eegdecoder.h \
                videodecoder.h \
                imudecoder.h \
                dummyeegfeatureextractor.h \
                dummyvideofeatureextractor.h \
                dummyimufeatureextractor.h \
                dummyclassifier.h \
                util/gstwrappedbuffer.h

SOURCES       = udpdatasource.cpp \
                dummyeegsource.cpp \
                eegdecoder.cpp \
                videodecoder.cpp \
                imudecoder.cpp \
                dummyeegfeatureextractor.cpp \
                dummyvideofeatureextractor.cpp \
                dummyimufeatureextractor.cpp \
                dummyclassifier.cpp \
                util/gstwrappedbuffer.cpp

HEADERS      += coreplugin.h \
                elements/datasource.h \
                elements/decoder.h \
                elements/featurextractor.h \
                elements/classifier.h \
                displayable.h \
                plugin.h

TARGET        = $$qtLibraryTarget(coreplugin)

LIBS            += -L$$OUT_PWD/../stripchart/ -lstripchart
INCLUDEPATH     += $$PWD/../stripchart
DEPENDPATH      += $$PWD/../stripchart
PRE_TARGETDEPS  += $$OUT_PWD/../stripchart/libstripchart.a

LIBS            += -L$$OUT_PWD/../headwidget/ -lheadwidget
INCLUDEPATH     += $$PWD/../headwidget
DEPENDPATH      += $$PWD/../headwidget
PRE_TARGETDEPS  += $$OUT_PWD/../headwidget/libheadwidget.a
