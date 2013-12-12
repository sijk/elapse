TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              coreplugin \
              pluginmanager \
              stripchart \
              deviceproxy \
              loggerwidget

app.depends += pluginmanager
app.depends += coreplugin
app.depends += pipeline
app.depends += deviceproxy
app.depends += stripchart
app.depends += loggerwidget
