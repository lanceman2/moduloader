#include <map>
#include "debug.h"
#include "Cat.hpp"
#include "ModuleLoader.hpp"
#include "ModuleManager.hpp"

int main(void)
{
    modLoader_catchSigFault();

    ModuleManager<Cat, Cat *(*)(int)> ml;

    Cat *cats[4];

    Cat *(*create)(int);

    create = ml.create("./lionModule.so");
    cats[0] = create(0);

    create = ml.create("./lionModule.so"); 
    cats[1] = create(1);

    create = ml.create("./tigerModule.so");
    cats[2] = create(10);

    create = ml.create("./tigerModule.so");
    cats[3] = create(11);

    for(int i=0; i<4; ++i)
        cats[i]->execute();

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);
    return 0;
}
