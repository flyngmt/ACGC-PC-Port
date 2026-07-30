#ifndef _WCHAR_H_
#define _WCHAR_H_

#ifdef TARGET_PC
#include <wchar.h>
#else

#include <stdio.h>

typedef unsigned short wchar_t;

int fwide(FILE *stream, int mode);

#endif /* TARGET_PC */
#endif
