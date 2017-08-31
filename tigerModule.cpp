#include <stdio.h>
#include "debug.h"
#include "CatModule.hpp"

class tigerModule: public Cat
{
    public:
        tigerModule(int arg);
        ~tigerModule(void);
        int execute(void);
};


tigerModule::tigerModule(int arg):Cat(arg)
{
    SPEW("Calling %s arg=%d", __func__, arg);
}

tigerModule::~tigerModule(void)
{
    SPEW("Calling %s arg=%d", __func__, arg);
}

int tigerModule::execute(void)
{
    WARN("Calling %s arg=%d", __func__, arg);
    return 1262;
}


// The two tiger/Cat factory functions:

static Cat *create(int arg)
{
    return new tigerModule(arg);
}

static void destroy(Cat *c)
{
    delete c;
}
