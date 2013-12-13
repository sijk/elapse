include(../staticlib.pri)

QT      += widgets

SOURCES += logview.cpp \
           logmodel.cpp \
           tablemodelloggerengine.cpp \
           logfilterproxymodel.cpp
HEADERS += logview.h \
           logmodel.h \
           tablemodelloggerengine.h \
           logfilterproxymodel.h
FORMS   += logview.ui
