#include <map>
#include "ModuleLoader.hpp"
#include "Cat.hpp"

class CatModuleLoader: private ModuleLoader<Cat, Cat *(*)(int)>
{
    public:
        CatModuleLoader(const char *dso_path);
        virtual ~CatModuleLoader(void);
        Cat *create(int arg);
        void destroy(Cat *cat);
    private:

        std::map<Cat *, Cat *> cats;   
};
