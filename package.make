# This make file is distributed with this package.

# If you need to make local configuration changes edit config.make.  This
# file is for package specific changes to quickbuild.


# We set specific GCC options that are set here

# We assume that we are using the GCC compile suite:


# Any time the (g++) C++ compiler runs we set these command line
# option flags
CXXFLAGS := -std=gnu++11 -g -Wall -Werror

# Any time the gcc C compiler runs we set these command line
# option flags
CFLAGS := -g -Wall -Werror



##########################################################################
#   START: To do with debug.c and debug.h
#


# C/C++ Pre-processor flags used for all in this package
CPPFLAGS := -DDEBUG -DSPEW_LEVEL_DEBUG

# Tell quickbuild to sub @DEBUG_SYMBOL_PREFIX@ @MACRO_API_PREFIX@ (and so
# on) with the values from the make variables given here:
IN_VARS := DEBUG_SYMBOL_PREFIX MACRO_API_PREFIX


# default value that may be overridden config.make
# DEBUG_SYMBOL_PREFIX is a prefix added to symbol names the code in
# debug.c is compiled with.  This may not be blank.
DEBUG_SYMBOL_PREFIX ?= modLoader_

# empty string by default
# Prefix added to CPP macro functions: WARN() ERROR() ASSERT() etc.
MACRO_API_PREFIX ?=

#
#    END: To do with debug.c and debug.h
##########################################################################



