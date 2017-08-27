#include <stdio.h>
#include "debug.h"
#include "Base.hpp"

class TestModule: public Base
{
    public:
        TestModule(int arg);
        ~TestModule(void);
        int execute(void);
};


TestModule::TestModule(int arg):Base(arg)
{
    SPEW("Calling %s arg=%d\n", __func__, arg);
}

TestModule::~TestModule(void)
{
    SPEW("Calling %s\n", __func__);
}

int TestModule::execute(void)
{
    SPEW("Calling %s\n", __func__);
    return 120;
}

static Base *create(int arg)
{
    return new TestModule(arg);
}

static void destroy(Base *b)
{
    delete b;
}

extern "C"
{
    void loader(void **c, void **d)
    {
        SPEW("\n");

        *c = (void *) create;
        *d = (void *) destroy;
    }
}
