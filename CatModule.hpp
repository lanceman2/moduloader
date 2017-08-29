#include "Cat.hpp"

// The module must define these two Cat object 
// factory functions:
static Cat *create(int arg);
static void destroy(Cat *c);

extern "C"
{
    void loader(void **c, void **d)
    {
        SPEW();
        *c = (void *) create;
        *d = (void *) destroy;
    }
}
