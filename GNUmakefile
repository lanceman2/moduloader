# This is a GNU make file that uses GNU make extensions.


# You can set in config.make
#  CPPFLAGS := -DDEBUG


# test_ModuleLoader tests the ModuleLoader template base class
test_ModuleLoader_SOURCES := test_ModuleLoader.cpp debug.c Cat.cpp
test_ModuleLoader_LDFLAGS := -Wl,--export-dynamic -ldl

# test_CatModuleLoader test a more specific class Cat loader
# using a class that inherits the ModuleLoader template class
test_CatModuleLoader_SOURCES := test_CatModuleLoader.cpp CatModuleLoader.cpp debug.c Cat.cpp
test_CatModuleLoader_LDFLAGS := -Wl,--export-dynamic -ldl

# test_NCatModuleLoader test a more specific class Cat loader
# using a class that inherits the ModuleLoader template class
# and makes many ModuleLoader objects.
test_NCatModuleLoader_SOURCES := test_NCatModuleLoader.cpp CatModuleLoader.cpp debug.c Cat.cpp
test_NCatModuleLoader_LDFLAGS := -Wl,--export-dynamic -ldl



lionModule.so_SOURCES := lionModule.cpp

include ./quickbuild.make

