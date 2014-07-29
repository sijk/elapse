TEMPLATE    = subdirs
SUBDIRS	    = fooplugin barplugin

# Copy the python plugin to the build directory
bazplugin.target = $$OUT_PWD/bazplugin/__init__.py
bazplugin.commands = $(COPY_DIR) $$PWD/bazplugin $$OUT_PWD
QMAKE_EXTRA_TARGETS += bazplugin
PRE_TARGETDEPS += bazplugin
