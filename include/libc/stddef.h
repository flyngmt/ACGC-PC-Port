#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))
#define membersize(type, member) (sizeof(((type*)0)->member))

#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL 0L

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif
#endif

#endif
