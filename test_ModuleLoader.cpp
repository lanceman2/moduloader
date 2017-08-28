#include "Cat.hpp"
#include "debug.h"
#include "ModuleLoader.hpp"

int main(void)
{
    SPEW();
    modLoader_catchSigFault();

    ModuleLoader<Cat, Cat *(*)(int)> *ml =
        new ModuleLoader<Cat, Cat *(*)(int)>("./lionModule.so");

    Cat *catModule = ml->create(45);

    SPEW();
    ASSERT(catModule, "");
    SPEW();
    catModule->execute();
    catModule->execute();
    catModule->execute();
    catModule->execute();
    SPEW();

    ml->destroy(catModule);

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);

    return 0;
}
