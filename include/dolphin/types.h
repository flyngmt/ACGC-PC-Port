#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_

typedef signed   char          s8;
typedef unsigned char          u8;
typedef signed   short int     s16;
typedef unsigned short int     u16;
#ifdef TARGET_PC
#include <stdint.h>
typedef int32_t                s32;
typedef uint32_t               u32;
typedef int64_t                s64;
typedef uint64_t               u64;
#else
typedef signed   long          s32;
typedef unsigned long          u32;
typedef signed   long long int s64;
typedef unsigned long long int u64;
#endif

typedef float  f32;
typedef double f64;

typedef char *Ptr;
#ifndef TARGET_PC
typedef unsigned int uintptr_t; // Manually added
#else
#include <stdint.h>
#endif

typedef int BOOL;

#define FALSE 0
#define TRUE 1

#if defined(TARGET_PC)
/* On PC, AT_ADDRESS is not used - hardware registers are regular externs */
#define AT_ADDRESS(addr)
#elif defined(__MWERKS__)
#define AT_ADDRESS(addr) : (addr)
#elif defined(__GNUC__)
//#define AT_ADDRESS(addr) __attribute__((address((addr))))
#define AT_ADDRESS(addr)  // was removed in GCC. define in linker script instead.
#else
#error unknown compiler
#endif

#ifndef TARGET_PC
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#else
#ifdef __GNUC__
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num) __declspec(align(num))
#else
#define ATTRIBUTE_ALIGN(num)
#endif
#endif

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*)0)
#else
#define NULL 0
#endif
#endif

#ifdef TARGET_PC
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#else
#include "libc/stdio.h"
#include "libc/stdarg.h"
#include "libc/string.h"
#include "libc/ctype.h"

#include "cmath.h"
#endif

#endif
