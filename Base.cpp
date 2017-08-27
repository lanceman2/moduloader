#include <stdio.h>
#include "debug.h"
#include "Base.hpp"


Base::Base(int arg):arg(arg)
{
    SPEW("Calling %s(arg=%d)\n", __func__, arg);
}

Base::~Base(void)
{
    SPEW("Calling %s arg=%d\n", __func__, arg);
}
