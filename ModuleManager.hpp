

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
        TCreate create(const char *dso_path);
        bool addCleanup(T *t, const char *dso_path);
        bool destroy(T*);

    private:

        // list of T object create() factory functions
        typename std::map<const char *, TCreate> creators;

        // list of T object destroy() factory functions
        typename std::map<const char *, void *(*)(T *)> destroyers;

        // list of existing T object's and destroy functions
        typename std::map<T *, void *(*)(T *)> objects;
};

template <class T, class TCreate>
ModuleManager<T, TCreate>::ModuleManager(void)
{
    SPEW();
}

template <class T, class TCreate>
ModuleManager<T, TCreate>::~ModuleManager(void)
{
    // First: destroy all the T objects that have been listed with
    // addCleanup():
    typename std::map<T *, void *(*)(T *)>::iterator it;
    for(it=objects.begin(); it!=objects.end(); ++it)
        (it->second)(it->first);

    // Empty the lists
    creators.clear();
    destroyers.clear();
    objects.clear();

    // TODO: We are not releasing resources in the dlclose() call
    // in ModuleLoader, but that is likely okay for our use case.
}


// Returns 0 on error.
template <class T, class TCreate>
TCreate ModuleManager<T, TCreate>::create(const char *dso_path)
{
    typename std::map<const char *, TCreate>::iterator it =
        creators.find(dso_path);

    if(it == creators.end())
    {
        // Create a ModuleLoader on this stack
        ModuleLoader<T, TCreate> ml(dso_path);
        creators[dso_path] = ml.create;
        destroyers[dso_path] = ml.destroy;
        if(!ml.create)
            WARN("Module with file: %s was not loaded\n", dso_path);
        return ml.create; // error if 0
    }

    // We return the create function and we cannot call it because there
    // is no way to declare generic argument prototypes in C++.  They must
    // call addCleanup(t) after this so this object may cleanup it in the
    // destructor, or not.  They can't call delete object, the factory
    // destroy() needs to do that so that modules more do that modules
    // do.
    return it->second; // success
}


// Return false on success.
template <class T, class TCreate>
bool ModuleManager<T, TCreate>::addCleanup(T *t, const char *dso_path)
{
    typename std::map<const char *, TCreate> it = destroyers.find(dso_path);
    if(it != destroyers.end())
    {
        // Add this ModuleLoader's destroy function to the list.
        destroyers[t] = it->second;
        return false; // success
    }
    WARN("Plugin loader for DSO file \"%s\" was not found\n", dso_path);
    return true; // error
}


// Returns false if the destructor was called and true otherwise.
template <class T, class TCreate>
bool ModuleManager<T, TCreate>::destroy(T *t)
{
    // Find the T object
    typename std::map<T *, void *(*)(T *)> it = destroyers.find(t);
    if(it != destroyers.end())
    {
        (it->second)(it->first);
        // Remove the T object from the list (map)
        destroyers.erase(it);
        return false; // success
    }
    WARN("destroy function for object %p was not found\n", t);
    return true; // error
}
