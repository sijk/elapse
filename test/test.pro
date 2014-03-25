TEMPLATE = subdirs

SUBDIRS += gmock
SUBDIRS += test_plugins

SUBDIRS += pluginmanager
pluginmanager.depends = test_plugins

SUBDIRS += bigendian24
SUBDIRS += datasink
SUBDIRS += udpdatasource
