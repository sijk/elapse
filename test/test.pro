TEMPLATE = subdirs

SUBDIRS += test_plugins PluginLoader
PluginLoader.depends += test_plugins

SUBDIRS += eegdecoder
SUBDIRS += bigendian24
