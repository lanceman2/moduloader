#include "Cat.hpp"
#include "ModuleLoader.hpp"

int main(void)
{
    SPEW("\n");
    SPEW("more spew %d\n", 56);
    //ASSERT(0);
    //FAIL("\n");

    _catchSigFault();

    ModuleLoader<Cat, Cat *(*)(int)> *ml =
        new ModuleLoader<Cat, Cat *(*)(int)>("./lionModule.so");

    Cat *catModule = ml->create(45);

    SPEW("\n");
    ASSERT(catModule);
    SPEW("\n");
    catModule->execute();
    catModule->execute();
    catModule->execute();
    catModule->execute();
    SPEW("\n");

    ml->destroy(catModule);

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);

    return 0;
}
