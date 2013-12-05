TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              coreplugin \
              pluginmanager \
              stripchart \
              deviceproxy

app.depends += pluginmanager
app.depends += coreplugin
app.depends += pipeline
app.depends += deviceproxy
app.depends += stripchart
