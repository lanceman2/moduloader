#include "debug.h"
#include "CatModuleLoader.hpp"


CatModuleLoader::CatModuleLoader(const char *dso_path):ModuleLoader(dso_path)
{
    if(!ModuleLoader<Cat, Cat *(*)(int)>::create) return; // Fail
    SPEW();
}

CatModuleLoader::~CatModuleLoader(void)
{
    for(std::map<Cat *, Cat *>::iterator it= cats.begin();
        it!=cats.end(); ++it)
        // Call the destructor for all the remaining Cat objects
        // using the module factory
        ModuleLoader<Cat, Cat *(*)(int)>::destroy(it->first);

    // Empty the list of Cats
    cats.clear();
}

Cat *CatModuleLoader::create(int arg)
{
    // Create a Cat
    Cat *cat = ModuleLoader<Cat, Cat *(*)(int)>::create(arg);
    // Add the Cat to a list (map)
    cats[cat] = cat;
    return cat;
}

void CatModuleLoader::destroy(Cat *cat)
{
    // Find the Cat
    std::map<Cat *,Cat *>::iterator it = cats.find(cat);
    // Remove the Cat from the list (map)
    cats.erase(it);
    // Call the destructor using the module factory
    ModuleLoader<Cat, Cat *(*)(int)>::destroy(cat);

    SPEW();
}
