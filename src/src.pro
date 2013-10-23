TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              stripchart
#              pluginloader \

app.depends += pipeline plugins stripchart
#pipeline.depends += pluginloader
