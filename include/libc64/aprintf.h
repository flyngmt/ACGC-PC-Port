#ifndef APRINTF_H
#define APRINTF_H

#include "types.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
    void* (*prout_func)(void*, const char*, int);
} aprout_func_t;

extern int vaprintf(aprout_func_t* func, const char* fmt, va_list ap);

#ifdef __cplusplus
}
#endif
#endif
