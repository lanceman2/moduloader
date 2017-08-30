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
        // create is a function pointer.
        Create create;
        // destroy is a function pointer.
        void *(*destroy)(Base *base);
};


template <class Base, class Create>
ModuleLoader<Base, Create>::ModuleLoader(const char *dso_path):create(0),destroy(0)
{
    void *dhandle = dlopen(dso_path, RTLD_LAZY|RTLD_NODELETE);
    if(!dhandle) {
        WARN("dlopen() failed: %s\n", dlerror());
        return;
    }

    dlerror(); // clear the error.
    void *(*loader)(void **, void **) =
         (void *(*)(void **, void **)) dlsym(dhandle, "loader");
    char *error = dlerror();
    if(error != 0) {
        WARN("dlsym() failed: %s\n", error);
        return;
    }

    loader((void **) &create, (void **) &destroy);

    if(!create)
    {
        WARN("failed to get create factory function\n");
        destroy = 0;
    }

    dlerror(); // clear the error.
    if(dlclose(dhandle)) {
        error = dlerror();
        WARN("dlclose(%p) failed: %s\n", dhandle, error);
        return;
    }
}

template <class Base, class Create>
ModuleLoader<Base, Create>::~ModuleLoader(void)
{

}
