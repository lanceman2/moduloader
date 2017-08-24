
#include "moduloader.hpp"
#include "base.hpp"
#define DEBUG
#include "debug.hpp"

int main(void)
{
    SPEW("\n");
    SPEW("more spew %d\n", 56);

    Base *testModule =
       Moduloader<Base>("testModule.so", 0);

    testModule->execute();

    delete testModule;

    return 0;
}
