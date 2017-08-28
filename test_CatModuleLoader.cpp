#include "debug.h"
#include "CatModuleLoader.hpp"

int main(void)
{
    modLoader_catchSigFault();

    CatModuleLoader *ml = new CatModuleLoader("./lionModule.so");

#define N 30

    Cat *cats[N];
    for(int i=0; i<30; ++i)
        cats[i] = ml->create(i);

    for(int i=0; i<30; ++i)
        cats[i]->execute();


    SPEW();

    delete ml;

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);

    return 0;
}
