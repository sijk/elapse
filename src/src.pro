TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginloader \
              stripchart

app.depends += pipeline plugins pluginloader stripchart
