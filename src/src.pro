TEMPLATE    = subdirs
SUBDIRS	    = app \
              plugins \
              pluginloader \
              decoders \
              stripchart

app.depends += plugins pluginloader decoders stripchart
