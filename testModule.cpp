
#include <stdio.h>
#include "base.hpp"

class TestModule: public Base
{
    public:
        TestModule(int arg);
        ~TestModule(void);
        int execute(void);
};


TestModule::TestModule(int arg):Base(arg)
{
    printf("Calling %s arg=%d\n", __func__, arg);
}

TestModule::~TestModule(void)
{
    printf("Calling %s\n", __func__);
}

int TestModule::execute(void)
{
    printf("Calling %s\n", __func__);
    return 120;
}

extern "C"
{
    void *createModuleObject(int arg)
    {
        return new TestModule(arg);
    }
}

