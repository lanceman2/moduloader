// The create method has a major stumbling block.

#include <map>
#include "ModuleLoader.hpp"

template <class T, class TCreate>
class ModuleManager: private ModuleLoader<T, TCreate>
{
    public:
        ModuleManager(const char *dso_path);
        virtual ~ModuleManager(void);
        virtual TCreate create;
        void addObject(T *t);
        void destroy(T *t);

    private:
        std::map<T *, T *> map; // list of created T objects
};

template <class T, class TCreate>
ModuleManager::ModuleManager(const char *dso_path):ModuleLoader(dso_path)
{
    if(!ModuleLoader<T, TCreate>::create) return; // Fail
    SPEW();
}

template <class T, class TCreate>
ModuleManager::~ModuleManager(void)
{
    for(std::map<T *, T *>::iterator it= map.begin();
        it!=map.end(); ++it)
        // Call the destructor for all the remaining T objects
        // using the module factory
        ModuleLoader<T, TCreate>::destroy(it->first);

    // Empty the list of map
    map.clear();
}

template <class T, class TCreate>
TCreate *ModuleManager::create(void)
{
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    // HELP ME
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //
    // TODO: How do I do this?
    // Call a T Creator function?
    //
    // This doe not know how to call this creator function with arguments
    // and then add the new T object to the map (list).  So the user calls
    // this function, creates the new T* with it and then add the T*
    // to the list with addObject().  Kind of sucks.
    //
    return ModuleLoader<T, TCreate>::create;


    // Add the T to a list (map)
    //map[t] = t;
    //return t;
}

template <class T, class TCreate>
void ModuleManager::addObject(T *t);
{
    // Add the T to a list (map)
    map[t] = t;
}

template <class T, class TCreate>
void ModuleManager::destroy(T *t)
{
    // Find the T object
    std::map<T *,T *>::iterator it = map.find(t);
    // Remove the T object from the list (map)
    map.erase(it);
    // Call the destructor using the module factory
    ModuleLoader<T, TCreate>::destroy(t);

    SPEW();
}
