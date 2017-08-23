
class Base
{
    public:
        Base(int arg);
        virtual ~Base(void);
        virtual int execute(void);
        void *loadModule(const char *path);
    private:

        int arg;
};

