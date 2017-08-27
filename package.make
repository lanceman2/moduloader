# This make file is distributed with this package.

# If you need to make local configuration changes edit config.make.  This
# file is for package specific changes to quickbuild.


# We set specific GCC options that are set here

# We assume that we are using the GCC compile suite:


# C/C++ Pre-processor flags used for all in this package
#CPPFLAGS := -DDEBUG

# Any time the (g++) C++ compiler runs we set these command line
# option flags
CXXFLAGS := -std=gnu++11 -g -Wall -Werror

# Any time the gcc C compiler runs we set these command line
# option flags
CFLAGS := -g -Wall -Werror
