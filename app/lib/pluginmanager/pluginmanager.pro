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

HEADERS += elementset.h \
           elapse/plugin.h \
           elapse/sampletypes.h \
           elapse/elements/datasource.h \
           elapse/elements/decoder.h \
           elapse/elements/featurextractor.h \
           elapse/elements/classifier.h \
           elapse/elements/datasinkdelegate.h

FORMS   += pluginmanager.ui
