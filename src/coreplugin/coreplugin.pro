include(../../global.pri)

TEMPLATE      = lib
CONFIG       += plugin link_pkgconfig qxt
QT           += network
DESTDIR       = ../../plugins/
PKGCONFIG     = gstreamer-1.0 gstreamer-app-1.0
QXT          += core

HEADERS       = udpdatasource.h \
                dummyeegsource.h \
                eegdecoder.h \
                videodecoder.h \
                imudecoder.h \
                dummyeegfeatureextractor.h \
                dummyvideofeatureextractor.h \
                dummyimufeatureextractor.h \
                dummyclassifier.h

SOURCES       = udpdatasource.cpp \
                dummyeegsource.cpp \
                eegdecoder.cpp \
                videodecoder.cpp \
                imudecoder.cpp \
                dummyeegfeatureextractor.cpp \
                dummyvideofeatureextractor.cpp \
                dummyimufeatureextractor.cpp \
                dummyclassifier.cpp

HEADERS      += coreplugin.h \
                elements/datasource.h \
                elements/decoder.h \
                elements/featurextractor.h \
                elements/classifier.h \
                displayable.h \
                plugin.h

TARGET        = $$qtLibraryTarget(coreplugin)
