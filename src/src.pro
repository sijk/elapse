TEMPLATE    = subdirs
SUBDIRS	    = app \
              pluginloader \
              decoders

app.depends += pluginloader decoders
