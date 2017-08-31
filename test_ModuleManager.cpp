#include <map>
#include "debug.h"
#include "Cat.hpp"
#include "ModuleLoader.hpp"
#include "ModuleManager.hpp"

int main(void)
{
    modLoader_catchSigFault();

    ModuleManager<Cat, Cat *(*)(int)> mm;

    Cat *cats[4];

    Cat *(*create)(int);

    create = mm.create("./lionModule.so");
    cats[0] = create(0);
    mm.addCleanup("./lionModule.so", cats[0]);

    create = mm.create("./lionModule.so"); 
    cats[1] = create(1);
    mm.addCleanup("./lionModule.so", cats[1]);

    create = mm.create("./tigerModule.so");
    cats[2] = create(10);
    mm.addCleanup("./tigerModule.so", cats[2]);

    create = mm.create("./tigerModule.so");
    cats[3] = create(11);
    mm.addCleanup("./tigerModule.so", cats[3]);

    for(int i=0; i<4; ++i)
        cats[i]->execute();

    mm.destroy(cats[1]); // test destroy method


    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);
    return 0;
}
