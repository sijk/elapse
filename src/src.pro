TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginloader \
              decoders \
              stripchart

app.depends += pipeline plugins pluginloader decoders stripchart
