TEMPLATE    = subdirs
SUBDIRS	    = src lib bindings

src.depends = lib
lib.depends = bindings
