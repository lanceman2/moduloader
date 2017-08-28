// Test that we can make many many ModuleLoaders which may be a dumb thing
// to do, but never the less this should be able to do it.

#include "debug.h"
#include "CatModuleLoader.hpp"

int main(void)
{
    modLoader_catchSigFault();

#define N 8
#define M 5

    Cat *cats[N*M];

    CatModuleLoader *ml[M];
    for(int j=0; j<M; ++j) {

        ml[j] = new CatModuleLoader("./lionModule.so");
    }

    for(int j=0; j<M; ++j) {
        for(int i=0; i<N; ++i)
            cats[i + N*j] = ml[j]->create(i + N*j);

        SPEW("j=%d", j);

        SPEW("%s RAN loop %d", __FILE__, j);
    }

    for(int i=0; i<N*M; ++i)
        cats[i]->execute();

    for(int j=0; j<M; ++j)
        delete ml[j];


    SPEW("%s RAN SUCCESSFULLY\n", __FILE__);
    return 0;
}
