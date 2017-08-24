#include <stdio.h>
#include <signal.h>
#include <stdarg.h>
#include "debug.hpp"

#ifndef SPEW_FILE
#define SPEW_FILE stdout
#endif


static void SYM_PRX_vspew(const char *pre, const char *file,
        int line, const char *func,
        const char *fmt, va_list ap)
{
    fprintf(SPEW_FILE, "%s%s:%d %s(): ", pre, file, line, func);
    vfprintf(SPEW_FILE, fmt, ap);
}

void SYM_PRX_spew(const char *pre, const char *file,
        int line, const char *func, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    SYM_PRX_vspew(pre, file, line, func, fmt, ap);
    va_end(ap);
}

void SYM_PRX_assert(const char *pre, const char *file,
        int line, const char *func,
        const char *format, ...)
{

}

