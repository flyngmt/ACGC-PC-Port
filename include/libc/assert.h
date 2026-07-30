#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef TARGET_PC
#include <assert.h>
#else

#if __STDC_VERSION__ >= 201112L
// The C11 way
#define static_assert(cond, msg) _Static_assert(cond, #msg)
#else
// The old, hacky way
#define static_assert(cond, msg) typedef char static_assertion_##msg[(cond)?1:-1]
#endif

#endif /* TARGET_PC */
#endif
