#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <stdio.h>
#include "base.hpp"
#include "debug.h"
#include "moduloader.hpp"


Base *BaseLoadModule(const char *dso_path, int arg)
{
    void *dhandle = dlopen(dso_path, RTLD_LAZY);
    if(!dhandle) {
        ERROR("dlopen() failed: %s\n", dlerror());
        return 0;
    }

    dlerror(); // clear the error.
    void *(*loader)(void) =
         (void *(*)(void)) dlsym(dhandle, "loader");
    char *error = dlerror();
    if(error != 0) {
        ERROR("dlsym() failed: %s\n", error);
        return 0;
    }
    void *l = loader();

    Base *(*create)(int) = (Base *(*)(int)) l;

    if(!create) return 0;

    Base *b = create(arg);
    SPEW("\n");

    return b;
}

