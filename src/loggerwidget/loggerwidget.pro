include(../staticlib.pri)

QT      += widgets

SOURCES += logview.cpp \
           logmodel.cpp \
           modelloggerengine.cpp
HEADERS += logview.h \
           logmodel.h \
           modelloggerengine.h
FORMS   += logview.ui
