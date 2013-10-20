TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginloader \
              stripchart

app.depends += pipeline plugins stripchart
pipeline.depends += pluginloader
