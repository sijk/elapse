TEMPLATE    = subdirs
SUBDIRS	    = app \
              plugins \
              pluginloader \
              decoders

app.depends += plugins pluginloader decoders
