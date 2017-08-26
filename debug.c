#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include "debug.h"

#ifndef SPEW_FILE
#define SPEW_FILE stdout
#endif



static void _vspew(const char *pre, const char *file,
        int line, const char *func,
        const char *fmt, va_list ap)
{
    fprintf(SPEW_FILE, "%s%s:%d %s(): ", pre, file, line, func);
    vfprintf(SPEW_FILE, fmt, ap);
}

void _spew(const char *pre, const char *file,
        int line, const char *func, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    _vspew(pre, file, line, func, fmt, ap);
    va_end(ap);
}

void _assertAction()
{
    pid_t pid;
    pid = getpid();
#ifdef ASSERT_ACTION_EXIT
    ERROR("With exit due to error");
    exit(1); // atexit() calls are called
    // See `man 3 exit' and `man _exit'
#else // ASSERT_ACTION_SLEEP
    int i = 1; // User debugger controller, unset to effect running code.
    ERROR("Consider running: \n\n  gdb -pid %u\n\n  "
        "pid=%u will now SLEEP ...\n", pid, pid);
    while(i) { sleep(1); }
#endif
}

static void segSaultCatcher(int sig)
{
    ERROR("caught signal %d SIGSEGV\n", sig);
    _assertAction();
}

// Add this to the start of your code so you may see where your code is
// seg faulting.
void _catchSigFault(void)
{
    struct sigaction s = {
        segSaultCatcher,
        0, // sa_sigaction
        0, // sa_mask;
        SA_RESETHAND,
        0
    };

    ASSERT(0 == sigaction(SIGSEGV, &s, 0));
}
