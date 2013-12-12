include(../global.pri)

TARGET   = $$basename(_PRO_FILE_PWD_)

QT       = core
TEMPLATE = lib
CONFIG  += staticlib qxt
QXT     += core
