TEMPLATE = subdirs

SUBDIRS += test_plugins pluginloader
pluginloader.depends += test_plugins

SUBDIRS += eegdecoder
SUBDIRS += bigendian24
