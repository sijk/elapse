TEMPLATE    = subdirs
SUBDIRS	    = app \
              plugins \
              pluginloader \
              stripchart

app.depends += plugins pluginloader stripchart
