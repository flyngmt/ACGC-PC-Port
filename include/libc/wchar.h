#ifndef _WCHAR_H_
#define _WCHAR_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#include <stdio.h>

typedef unsigned short wchar_t;

int fwide(FILE *stream, int mode);

#endif
