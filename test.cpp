
#include "moduloader.hpp"
#include "base.hpp"

int main(void)
{
    Base *testModule =
       Moduloader<Base>("testModule.so", 0);

    testModule->execute();

    delete testModule;

    return 0;
}
