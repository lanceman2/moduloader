#include "Base.hpp"
#include "ModuleLoader.hpp"

int main(void)
{
    SPEW("\n");
    SPEW("more spew %d\n", 56);
    //ASSERT(0);
    //FAIL("\n");

    _catchSigFault();

    ModuleLoader<Base, Base *(*)(int)> *ml =
        new ModuleLoader<Base, Base *(*)(int)>("./testModule.so");

    Base *testModule = ml->create(45);

    SPEW("\n");
    ASSERT(testModule);
    SPEW("\n");
    testModule->execute();
    testModule->execute();
    testModule->execute();
    testModule->execute();
    testModule->execute();
    testModule->execute();
    testModule->execute();
    SPEW("\n");

    ml->destroy(testModule);

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);

    return 0;
}
