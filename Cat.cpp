#include <stdio.h>
#include "debug.h"
#include "Cat.hpp"


Cat::Cat(int arg):arg(arg)
{
    SPEW("Calling %s(arg=%d)\n", __func__, arg);
}

Cat::~Cat(void)
{
    SPEW("Calling %s arg=%d\n", __func__, arg);
}
