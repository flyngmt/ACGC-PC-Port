#ifndef _STDINT_H_
#define _STDINT_H_

#ifdef TARGET_PC
#include <stdint.h>
#else

typedef unsigned long int uintptr_t;

#endif /* TARGET_PC */
#endif
