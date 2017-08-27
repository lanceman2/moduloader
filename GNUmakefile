# This is a GNU make file that uses GNU make extensions.

test_SOURCES := test.cpp debug.c Base.cpp
test_CPPFLAGS := -DDEBUG
test_LDFLAGS := -Wl,--export-dynamic -ldl

testModule.so_SOURCES := testModule.cpp

include ./quickbuild.make
