include(../../plugin.pri)

TARGET        = coreplugin
CONFIG       += link_pkgconfig qwt qxt
QT           += network opengl
PKGCONFIG     = Qt5GStreamer-0.10 Qt5GStreamerUtils-0.10 Qt5GStreamerUi-0.10
QXT          += core

HEADERS      += udpdatasource.h \
#                dummyeegsource.h \
                eegdecoder.h \
                videodecoder.h \
                imudecoder.h \
                dummyeegfeatureextractor.h \
                dummyvideofeatureextractor.h \
                dummyimufeatureextractor.h \
                dummyclassifier.h \
                blackholedatasinkdelegate.h \
                simplerawdatasinkdelegate.h \
                util/bigendian24.h \
                util/gstwrappedbuffer.h \
                util/timestampedvalues.h

SOURCES      += udpdatasource.cpp \
#                dummyeegsource.cpp \
                eegdecoder.cpp \
                videodecoder.cpp \
                imudecoder.cpp \
                dummyeegfeatureextractor.cpp \
                dummyvideofeatureextractor.cpp \
                dummyimufeatureextractor.cpp \
                dummyclassifier.cpp \
                blackholedatasinkdelegate.cpp \
                simplerawdatasinkdelegate.cpp \
                util/gstwrappedbuffer.cpp

HEADERS      += coreplugin.h

linkStaticlib(stripchart)
linkStaticlib(headwidget)
