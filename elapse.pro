TEMPLATE    = subdirs
SUBDIRS	    = src \
#              test

docs.commands = SRCDIR=$$PWD doxygen $$PWD/Doxyfile
QMAKE_EXTRA_TARGETS += docs
QMAKE_CLEAN += doc/html/** doc/html/search/**

uml.commands = java -Djava.awt.headless=true -jar $$PWD/tools/plantuml.jar -v \
               -o $$OUT_PWD/doc/img \"$$PWD/**.(c|cpp|h|dox)\"
docs.depends += uml
QMAKE_EXTRA_TARGETS += uml
QMAKE_CLEAN += doc/img/**
