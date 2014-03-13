TARGET   = gmock
TEMPLATE = lib
CONFIG  += static

SOURCES  = gmock-gtest-all.cc

QMAKE_CXXFLAGS += -Wno-missing-field-initializers

