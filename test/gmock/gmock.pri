INCLUDEPATH += $$PWD
LIBS += -L$$shadowed($$PWD) -lgmock

GMOCK_MAIN = $$PWD/gmock_main.cc

