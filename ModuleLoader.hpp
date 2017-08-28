#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#include <dlfcn.h>
#include <stdio.h>

template <class Base, class Create>
class ModuleLoader
{
    public:
        ModuleLoader(const char *dso_path);
        virtual ~ModuleLoader(void);
        Create create;
        void *(*destroy)(Base *base);
};


template <class Base, class Create>
ModuleLoader<Base, Create>::ModuleLoader(const char *dso_path)
{
    void *dhandle = dlopen(dso_path, RTLD_LAZY|RTLD_NODELETE);
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

    dlerror(); // clear the error.
    if(dlclose(dhandle)) {
        error = dlerror();
        ERROR("dlclose() failed: %s\n", error);
        return;
    }
}

template <class Base, class Create>
ModuleLoader<Base, Create>::~ModuleLoader(void)
{

}

