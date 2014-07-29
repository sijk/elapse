include(../../staticlib.pri)

TARGET        = coreplugin
CONFIG       += static plugin

CONFIG       += link_pkgconfig qwt qxt
QT           += network opengl
PKGCONFIG     = Qt5GStreamer-0.10 Qt5GStreamerUtils-0.10 Qt5GStreamerUi-0.10 gstreamer-0.10
QXT          += core

HEADERS      += udpdatasource.h \
                simplerawdatasource.h \
                eegdecoder.h \
                videodecoder.h \
                imudecoder.h \
                dummyeegfeatureextractor.h \
                dummyvideofeatureextractor.h \
                dummyimufeatureextractor.h \
                dummyclassifier.h \
                dummyaction.h \
                blackholedatasinkdelegate.h \
                simplerawdatasinkdelegate.h \
                util/bigendian24.h \
                util/gstwrappedbuffer.h

SOURCES      += udpdatasource.cpp \
                simplerawdatasource.cpp \
                eegdecoder.cpp \
                videodecoder.cpp \
                imudecoder.cpp \
                dummyeegfeatureextractor.cpp \
                dummyvideofeatureextractor.cpp \
                dummyimufeatureextractor.cpp \
                dummyclassifier.cpp \
                dummyaction.cpp \
                blackholedatasinkdelegate.cpp \
                simplerawdatasinkdelegate.cpp \
                util/gstwrappedbuffer.cpp

HEADERS      += coreplugin.h

linkStaticlib(stripchart)
linkStaticlib(headwidget)
