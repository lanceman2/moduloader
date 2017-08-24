// The files debug.hpp and debug.cpp should be kept independent of all
// other source file, so they can be used in other software packages.

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
// WARN() being the same as NOTICE(), and whatever.  We can add tty escape
// color codes and the different spew levels later.  Additions like that
// will not effect the coding interfaces that we define here:

#include <stdbool.h>


#ifndef SYM_PRX
// Function name prefix used in debug.cpp so exposed symbols have this
// prefix.  With compiler options the prefix can hide or expose symbols.
// You also can use it like an API prefix, like a C style name space.
//
// Sorry C++ can't beat the CPP coupled with the printf streams for
// selecting code at compile time.
//
//Example:
//#define SYM_PRX   ACME_TOOL_

// empty
#define SYM_PRX
#endif


extern void SYM_PRX_spew(const char *pre, const char *file,
        int line, const char *func, const char *fmt, ...)
         // check printf format errors at compile time:
        __attribute__ ((format (printf, 5, 6)));

extern void SYM_PRX_assertAction(void);
extern void STM_PRX_catchSigFault(void);


#  define _SPEW(pre, fmt, ... )\
     SYM_PRX_spew(pre, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#  define ERROR(fmt, ...)\
     SYM_PRX_spew("ERROR: ", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#  define ASSERT(val) \
    do {\
        if(!((bool) val)) {\
            _SPEW("ERROR: ", "ASSERTION(%s) failed\n", #val);\
            SYM_PRX_assertAction();\
        }\
    while(0)
            
#  define VASSERT(val, fmt, ...) \
    do {\
        if(!((bool) val)) {\
            _SPEW("ERROR: ", "ASSERTION(%s) failed: " #fmt, #val, ##__VA_ARGS__);\
            SYM_PRX_assertAction();\
        }\
    while(0)


#  define FAIL(fmt, ...) \
    do {\
        _SPEW("ERROR:", fmt, ##__VA_ARGS__);\
        SYM_PRX_assertAction();\
    } while(0)

#  define ERROR(fmt, ...)\
     SYM_PRX_spew(pre, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)


#ifdef DEBUG

#  define _SPEW(pre, fmt, ... )\
     SYM_PRX_spew(pre, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#  define SPEW(fmt, ...) _SPEW("SPEW: ", fmt, ##__VA_ARGS__)

#  define WARN(fmt, ...) _SPEW("WARN: ", fmt, ##__VA_ARGS__)



#else


#  define SPEW()    /* empty marco */

#  define WARN()    /* empty marco */
#  define NOTICE()  /* empty marco */
#  define DSPEW()   /* empty marco */

#  define DASSERT() /* empty marco */



#endif // #ifdef DEBUG

#undef _SPEW

