class Base
{
    public:
        Base(int arg);
        virtual ~Base(void);
        virtual int execute(void) = 0;
    private:

        int arg;
};
