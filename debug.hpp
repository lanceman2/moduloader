
#ifndef SYM_PRX
// Function name prefix used in debug.cpp so exposed symbols have this
// prefix.  With compiler options the prefix can hide or expose symbols.
// You also can use it like an API prefix, like a C style name space.
//
// Sorry C++ can't beat the CPP coupled with the printf streams for
// selecting code at compile time.
//
// empty
#define SYM_PRX
#endif


#ifndef PRE
// Set the spew prefix
#  define PRE "DBG:"
#endif


// We can extend the functionally of these CPP MACRO functions as needs
// arise.  Some of the MACROs may start out as very simple wrappers.
// We'll keep these interfaces and can effectively change the code that
// uses them without editing the code that uses them by changing
// debug.cpp and this file.  We can add environment variable interfaces
// without changing these interfaces and so on.  For example in bash
// shell:
//
//   SDF_SPEW_LEVEL=debug SDF_ASSERTIONS_SLEEP=true ./foobar
//
// But there's no pressing need until we need it.  We can start with
// WARN() being the same as NOTICE(), and whatever.  We could tty color
// code the different spew levels, but that will not effect the coding
// interfaces.

#ifdef DEBUG

extern void SYM_PRX_spew(const char *pre, const char *file,
        int line, const char *func, const char *fmt, ...)
        __attribute__ ((format (printf, 5, 6)));


#  define SPEW(fmt, ... )\
    SYM_PRX_spew(PRE, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)



#else



#  define SPEW() /* empty marco */



#endif

