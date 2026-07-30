#ifndef _DOLPHIN_LIBC_CTYPE_H_
#define _DOLPHIN_LIBC_CTYPE_H_

#ifdef TARGET_PC
#include <ctype.h>
#else

#ifdef __cplusplus
extern "C" {
#endif

int tolower(int c);

#ifdef __cplusplus
}
#endif

#endif /* TARGET_PC */
#endif // _DOLPHIN_LIBC_CTYPE_H_
