include(../../../plugin.pri)

TARGET   = fooplugin
DESTDIR  = ..

SOURCES += fooeegdecoder.cpp foodummysource.cpp
HEADERS += fooeegdecoder.h foodummysource.h
HEADERS += fooplugin.h


# This should be up a level, but qmake doesn't support EXTRA_TARGETS on
# SUBDIRS projects
bazplugin.commands = $(COPY_DIR) $$PWD/../bazplugin $$OUT_PWD/..
QMAKE_EXTRA_TARGETS += bazplugin
PRE_TARGETDEPS += bazplugin
