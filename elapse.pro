TEMPLATE    = subdirs
SUBDIRS	    = src \
#              test

docs.commands = SRCDIR=$$PWD doxygen $$PWD/Doxyfile
QMAKE_EXTRA_TARGETS += docs
