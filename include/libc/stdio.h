#ifndef _STDIO_H_
#define _STDIO_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "MSL_C/ansi_files.h"

int puts(const char *s);
int printf(const char *, ...);
int sprintf(char *s, const char *format, ...);
int vprintf(const char *format, va_list arg);
int vsprintf(char *s, const char *format, va_list arg);

#ifdef __cplusplus
}
#endif

#endif
