class Cat
{
    public:
        Cat(int arg);
        virtual ~Cat(void);
        virtual int execute(void) = 0;
    protected:

        int arg;
};
