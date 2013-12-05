TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              plugins \
              pluginmanager \
              stripchart \
              deviceproxy

app.depends += pipeline plugins stripchart
app.depends += pluginmanager
app.depends += deviceproxy
