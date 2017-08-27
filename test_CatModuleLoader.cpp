#include "CatModuleLoader.hpp"

int main(void)
{
    SPEW("\n");
    SPEW("more spew %d\n", 56);
    //ASSERT(0);
    //FAIL("\n");

    _catchSigFault();

    CatModuleLoader *ml = new CatModuleLoader("./lionModule.so");

#define N 30

    Cat *cats[N];
    for(int i=0; i<30; ++i)
        cats[i] = ml->create(i);

    for(int i=0; i<30; ++i)
        cats[i]->execute();


    SPEW("\n");

    delete ml;

    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);

    return 0;
}
