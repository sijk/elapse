include(global.pri)

TEMPLATE    = lib
CONFIG     += plugin
DESTDIR     = $$shadowed($$ROOT)/plugins/

HEADERS    += elapse/plugin.h \
              elapse/sampletypes.h \
              elapse/elements/datasource.h \
              elapse/elements/decoder.h \
              elapse/elements/featurextractor.h \
              elapse/elements/classifier.h \
              elapse/displayable.h
