TEMPLATE    = subdirs
SUBDIRS	    = src \
#              test

docs.commands = SRCDIR=$$PWD doxygen $$PWD/Doxyfile
docs.depends += uml

uml.commands = java -Djava.awt.headless=true -jar $$PWD/tools/plantuml.jar -v \
               -Sshadowing=false \
               -o $$OUT_PWD/doc/img \"$$PWD/**.(c|cpp|h|dox)\"

QMAKE_EXTRA_TARGETS += docs uml
QMAKE_CLEAN += doc/html/** doc/html/search/** doc/img/**
