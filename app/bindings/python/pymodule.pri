include(../../../global.pri)

QT         = core gui
TEMPLATE   = lib
CONFIG    += plugin no_plugin_name_prefix link_pkgconfig
PKGCONFIG += python2
LIBS      += -lboost_python

linkSharedlib(app, elapseplugin, true)
