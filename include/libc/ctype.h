#ifndef _DOLPHIN_LIBC_CTYPE_H_
#define _DOLPHIN_LIBC_CTYPE_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#ifdef __cplusplus
extern "C" {
#endif

int tolower(int c);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_LIBC_CTYPE_H_
