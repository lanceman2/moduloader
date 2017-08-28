#include <stdio.h>
#include "debug.h"
#include "Cat.hpp"

class LionModule: public Cat
{
    public:
        LionModule(int arg);
        ~LionModule(void);
        int execute(void);
};


LionModule::LionModule(int arg):Cat(arg)
{
    SPEW("Calling %s arg=%d", __func__, arg);
}

LionModule::~LionModule(void)
{
    SPEW("Calling %s arg=%d", __func__, arg);
}

int LionModule::execute(void)
{
    WARN("Calling %s arg=%d", __func__, arg);
    return 120;
}

static Cat *create(int arg)
{
    return new LionModule(arg);
}

static void destroy(Cat *c)
{
    delete c;
}

extern "C"
{
    void loader(void **c, void **d)
    {
        SPEW();
        *c = (void *) create;
        *d = (void *) destroy;
    }
}
