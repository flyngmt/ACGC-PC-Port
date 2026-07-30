#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef TARGET_PC
/* Undefine our guard so GCC's stddef.h doesn't skip itself */
#undef _STDDEF_H_
#include <stddef.h>
/* Re-define it to prevent re-entry of this file */
#define _STDDEF_H_
#define membersize(type, member) (sizeof(((type*)0)->member))
#else

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))
#define membersize(type, member) (sizeof(((type*)0)->member))

#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL 0L
#endif

#endif /* TARGET_PC */
#endif
