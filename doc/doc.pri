ROOT = $$_PRO_FILE_PWD_

docs.commands = SRCDIR=$$ROOT doxygen $$ROOT/doc/Doxyfile
docs.depends += uml

uml.commands = java -Djava.awt.headless=true \
               -jar $$ROOT/tools/plantuml.jar \
               -v -Sshadowing=false \
               -o $$shadowed($$ROOT)/doc/img \
               \"$$ROOT/**.(c|cpp|h|dox)\"

QMAKE_EXTRA_TARGETS += docs uml
QMAKE_CLEAN += doc/html/** doc/html/search/** doc/img/**

