#ifndef _ERRNO_H_
#define _ERRNO_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#define ERANGE 32

extern int errno;

#endif
