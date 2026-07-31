#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef TARGET_PC
#error ACGC console libc headers are not host libc wrappers; include the system header instead
#endif

#if __STDC_VERSION__ >= 201112L
// The C11 way
#define static_assert(cond, msg) _Static_assert(cond, #msg)
#else
// The old, hacky way
#define static_assert(cond, msg) typedef char static_assertion_##msg[(cond)?1:-1]
#endif

#endif
