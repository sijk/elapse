include(../staticlib.pri)

QT      += widgets

SOURCES += logview.cpp \
           logmodel.cpp \
           tablemodelloggerengine.cpp
HEADERS += logview.h \
           logmodel.h \
           tablemodelloggerengine.h
FORMS   += logview.ui
