include(../staticlib.pri)

QT      += gui widgets

SOURCES += pluginmanager.cpp \
           pluginfilterproxymodel.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginfilterproxymodel.h \
           plugin.h \
           elements.h \
           elements/datasource.h \
           elements/decoder.h

FORMS   += pluginmanager.ui
