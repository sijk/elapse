TEMPLATE    = subdirs
SUBDIRS	    = app \
              pipeline \
              coreplugin \
              pluginmanager \
              stripchart \
              headwidget \
              deviceproxy \
              loggerwidget

app.depends += pluginmanager
app.depends += coreplugin
app.depends += pipeline
app.depends += deviceproxy
app.depends += stripchart
app.depends += headwidget
app.depends += loggerwidget
