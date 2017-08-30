
#include <map>

// T is the base class (not a pointer)
// TCreate is the creator factory function so like
//
//   static T *create(int foo, float *bar)
//   {
//       T *t = new T *t(foo, bar)
//       return t;
//   }
//
//  where create is the type for the create function
//  pointer like so:
//
//  TCreate create_ptr = create;
//
//  T *t = create_ptr(foo, bar);
//
//

// This class is the highest lever we take this idea in this package.

template <class T, class TCreate>
class ModuleManager
{
    public:
        ModuleManager(void);
        virtual ~ModuleManager(void);
        // We assume that the dso_path string is unique
        // to the DSO plugin file.
        TCreate * create(const char *dso_path);
        bool addCleanup(T *t, const char *dso_path);
        bool destroy(T*);

    private:
        // list of created ModuleLoader objects
        std::map<const char *, ModuleLoader<T, TCreate> *> loaders;

        // list of existing T object's destroy functions
        std::map<T *, void *(*)(T *)> destroyers;
};

template <class T, class TCreate>
ModuleManager::ModuleManager(void)
{
    SPEW();
}

template <class T, class TCreate>
ModuleManager::~ModuleManager(void)
{
    // First: destroy all the T objects that have been listed with
    // addCleanup():
    for(std::map<T *, void *(*)(T *)>::iterator it = destroys.begin();
            it!=map.end(); ++it)
        (it->second)(it->first);

    // Second: delete all the ModuleLoader objects
    for(std::map<const char *, ModuleLoader<T, TCreate> *> it =
            loaders.begin(); it!=map.end(); ++it)
        delete it->second;

    // Empty the lists
    loaders.clear();
    destroyers.clear();

    // The maps where all statically declared so they cleanup with
    // this ModuleManager object.
}


// Returns 0 on error.
template <class T, class TCreate>
TCreate *ModuleManager::create(const char *dso_path)
{
    std::map<const char *, ModuleLoader<T, TCreate> *>::iterator it;
    TCreate *create;
    
    it = loaders.find[dso_path];

    if(it == std::map::end)
    {
        ModuleLoader<T, TCreate> *ml = new ModuleLoader<T, TCreate>(dso_path);
        loaders[dso_path] = ml->create;
        if(!ml->create)
            WARN("Module with file: %s was not loaded\n", dso_path);
        return ml->create; // error
    }

    // We return the create function and we cannot call it because there
    // is no way to declare generic argument prototypes in C++.  They must
    // call addCleanup(t) after this so this object may cleanup it in the
    // destructor.
    return it.second; // success
}


// Return false on success.
template <class T, class TCreate>
bool addCleanup(T *t, const char *dso_path)
{
    std::map<const char *, ModuleLoader<T, TCreate> *> lm_it = loaders.find(dso_path);
    if(it == std::map::end)
    {
        WARN("Plugin loader for DSO file \"%s\" was not found\n", dso_path);
        return true; // error
    }
    // Add this ModuleLoader's destroy function to the list.
    destroyers[t] = lm_it->second->destroy;
    return false; // success
}


// Returns false if the destructor was called and true otherwise.
template <class T, class TCreate>
bool ModuleManager::destroy(T *t)
{
    // Find the T object
    std::map<T *, void *(*)(T *)> destroyers; it = destroyers.find(t);
    if(it != std::map::end)
    {
        (it->second)(it->first);
    
        // Remove the T object from the list (map)
        destroyers.erase(it);
        return false; // success
    }

    WARN("destroy function for object %p was not found\n", t);
    return true; // error
}
