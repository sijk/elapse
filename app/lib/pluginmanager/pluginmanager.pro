include(../../../staticlib.pri)

QT      += gui widgets

SOURCES += pluginmanager.cpp \
           pluginfilterproxymodel.cpp \
           elementsetfactory.cpp

HEADERS += pluginmanager.h \
           pluginmanager_p.h \
           pluginmanager_def.h \
           pluginfilterproxymodel.h \
           elementsetfactory.h

FORMS   += pluginmanager.ui
