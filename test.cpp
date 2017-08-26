
#include "moduloader.hpp"
#include "base.hpp"
#include "debug.h"

int main(void)
{
    SPEW("\n");
    SPEW("more spew %d\n", 56);
    WARN("more spew %d\n", 56);

    _catchSigFault();

    Base *testModule = Moduloader<Base>("testModule.so", 0);

    ASSERT(testModule);

    testModule->execute();

    delete testModule;

    return 0;
}
