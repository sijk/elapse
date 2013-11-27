TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginmanager \
              stripchart

app.depends += pipeline plugins stripchart
app.depends += pluginmanager
