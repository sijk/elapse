TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginmanager \
              stripchart
#              pluginloader \

app.depends += pipeline plugins stripchart
app.depends += pluginmanager
#pipeline.depends += pluginloader
