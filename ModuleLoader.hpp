#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <list>
#include <dlfcn.h>
#include <stdio.h>

#include "debug.h"


template <class Base, class Create>
class ModuleLoader
{
    public:
        ModuleLoader(const char *dso_path);
        virtual ~ModuleLoader(void);
        Create create;
        void *(*destroy)(Base *base);

    private:
        // We keep a list of Base objects
        // that are created so we may cleanup.
        std::list<Base *> objects;
};

template <class Base, class Create>
ModuleLoader<Base, Create>::ModuleLoader(const char *dso_path)
{
    void *dhandle = dlopen(dso_path, RTLD_LAZY);
    if(!dhandle) {
        ERROR("dlopen() failed: %s\n", dlerror());
        return;
    }

    dlerror(); // clear the error.
    void *(*loader)(void **, void **) =
         (void *(*)(void **, void **)) dlsym(dhandle, "loader");
    char *error = dlerror();
    if(error != 0) {
        ERROR("dlsym() failed: %s\n", error);
        return;
    }

    loader((void **) &create, (void **) &destroy);

    if(!create)
        ERROR("failed to get create factory function\n");
}

template <class Base, class Create>
ModuleLoader<Base, Create>::~ModuleLoader(void)
{

}

