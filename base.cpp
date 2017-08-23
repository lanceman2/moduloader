#include <stdio.h>
#include "base.hpp"


Base::Base(int arg):arg(arg)
{
    printf("Calling %s arg=%d\n", __func__, arg);
}

Base::~Base(void)
{
    printf("Calling %s arg=%d\n", __func__, arg);
}

int Base::execute(void)
{
    printf("Calling %s arg=%d\n", __func__, arg);
    return 0;
}

