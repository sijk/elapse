TEMPLATE    = subdirs
SUBDIRS	    = app common coreplugin test

app.depends = common

include(doc/doc.pri)
