TEMPLATE    = subdirs
SUBDIRS	    = app \
              pluginloader

app.depends += pluginloader
