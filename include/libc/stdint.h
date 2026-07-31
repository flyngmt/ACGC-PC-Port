#ifndef _STDINT_H_
#define _STDINT_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

typedef unsigned long int uintptr_t;

#endif
