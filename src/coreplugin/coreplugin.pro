include(../../global.pri)

TEMPLATE      = lib
CONFIG       += plugin
QT           += network
DESTDIR       = ../../plugins/

HEADERS       = tcpclientdatasource.h \
                dummyeegsource.h \
                eegdecoder.h \
                videodecoder.h \
                imudecoder.h \
                dummyeegfeatureextractor.h \
                dummyvideofeatureextractor.h \
                dummyimufeatureextractor.h \
                dummyclassifier.h

SOURCES       = tcpclientdatasource.cpp \
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
                plugin.h

TARGET        = $$qtLibraryTarget(coreplugin)
