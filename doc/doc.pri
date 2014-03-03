ROOT_DIR = $$dirname(PWD)

docs.commands = SRCDIR=$$ROOT_DIR doxygen $$PWD/Doxyfile
docs.depends += uml

uml.commands = java -Djava.awt.headless=true -jar $$ROOT_DIR/tools/plantuml.jar -v \
               -Sshadowing=false \
               -o $$OUT_PWD/img \"$$ROOT_DIR/**.(c|cpp|h|dox)\"

QMAKE_EXTRA_TARGETS += docs uml
QMAKE_CLEAN += doc/html/** doc/html/search/** doc/img/**

