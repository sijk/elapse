include(../test.pri)

QT        += gui widgets
CONFIG    += link_prl

SOURCES   += runner.cpp

linkStaticlib(app, pluginmanager)
linkSharedlib(app, elapseplugin, true)

INCLUDEPATH += $$ROOT/app/include $$shadowed($$ROOT/app/lib/pluginmanager)

plugin_src = $$PWD/plugin/__init__.py
plugin_dst = $$OUT_PWD/plugins/pytestplugin/__init__.py
plugin.target = $$plugin_dst
plugin.depends = $$plugin_src
plugin.commands = $(MKDIR) $$dirname(plugin_dst) && \
                  $(COPY_FILE) $$plugin_src $$plugin_dst
QMAKE_EXTRA_TARGETS += plugin
PRE_TARGETDEPS += $$plugin_dst
