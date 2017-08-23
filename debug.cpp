#include <stdio.h>
#include <signal.h>
#include <stdarg.h>

static void _vspew(const char *pre, const char *file,
        const char *line, const char *func,
        const char *format, va_list ap)
{

}

void _spew(const char *pre, const char *file,
        const char *line, const char *func,
        const char *format, ...)
{
    va_list ap;
    va_start(ap, fmt);
    _vspew(pre, file, line, func, format, ap);
    va_end(ap);
}

void _assert(const char *pre, const char *file,
        const char *line, const char *func,
        const char *format, ...)
{

}

