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

HEADERS += plugin.h \
           sampletypes.h \
           elementset.h \
           elements/datasource.h \
           elements/decoder.h \
           elements/featurextractor.h \
           elements/classifier.h

FORMS   += pluginmanager.ui
