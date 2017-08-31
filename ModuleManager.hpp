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

template <class T, class TCreate>
class ModuleManager
{
    public:
        ModuleManager(void);
        virtual ~ModuleManager(void);
        // We assume that the dso_path string is unique
        // to the DSO plugin file.
        TCreate create(const char *dso_path);
        // Add to the list of T objects that get destroyed
        // when this ModuleManager is destroyed.
        bool addCleanup(const char *dso_path, T *t);
        // You do not have to add it if you want to manage
        // it's destruction with this function:
        bool destroy(T* t);

    private:

        // list of T object create() factory functions
        typename std::map<const char *, TCreate> creators;

        // list of T object destroy() factory functions
        typename std::map<const char *, void *(*)(T *)> destroyers;

        // list of existing T object's and destroy functions
        // used in cleaning up in the ModuleManager destructor
        typename std::map<T *, void *(*)(T *)> cleanupObjects;
};

template <class T, class TCreate>
ModuleManager<T, TCreate>::ModuleManager(void)
{
    DSPEW();
}

template <class T, class TCreate>
ModuleManager<T, TCreate>::~ModuleManager(void)
{
    DSPEW("Enter");
    // First: destroy all the T cleanupObjects that have been listed with
    // addCleanup():
    typename std::map<T *, void *(*)(T *)>::const_iterator it;
    for(it=cleanupObjects.begin(); it!=cleanupObjects.end(); ++it)
        (it->second)(it->first);

    // Empty the lists
    creators.clear();
    destroyers.clear();
    cleanupObjects.clear();

    DSPEW("Finish");
    // TODO: We are not releasing resources in the dlclose() call
    // in ModuleLoader, but that is likely okay for our use case.
}


// Returns 0 on error.
template <class T, class TCreate>
TCreate ModuleManager<T, TCreate>::create(const char *dso_path)
{
    typename std::map<const char *, TCreate>::const_iterator it =
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
bool ModuleManager<T, TCreate>::addCleanup(const char *dso_path, T *t)
{
    typename std::map<const char *, void *(*)(T *)>::const_iterator it = destroyers.find(dso_path);
    if(it != destroyers.end())
    {
        // Add this ModuleLoader's destroy function to the cleanupObjects list.
        cleanupObjects[t] = it->second;
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
    typename std::map<T *, void *(*)(T *)>::const_iterator it = cleanupObjects.find(t);
    if(it != cleanupObjects.end())
    {
        // Call function destroy()
        (it->second)(it->first);
        // Remove the T object from the list (map)
        cleanupObjects.erase(it->first);
        return false; // success
    }
    WARN("destroy function for object %p was not found\n", t);
    return true; // error
}
