#ifndef TYPES_H
#define TYPES_H

#ifdef TARGET_PC
/* On PC, we don't have MSL_C - use standard math */
#include <math.h>
#include <string.h>
#ifdef __APPLE__
#include <stdlib.h>  /* alloca() on macOS */
#else
#include <malloc.h>  /* for alloca() */
#endif
/* Metrowerks __alloca is a compiler built-in; map to standard alloca on PC.
 * Skip on platforms where it's already a built-in or macro to avoid redefinition. */
#ifndef __alloca
#define __alloca alloca
#endif
/* Metrowerks __declspec(section "...") is not supported by GCC.
 * GCC defines __declspec as a builtin keyword, so we must #undef it first. */
#undef __declspec
#define __declspec(x)
#else
#include "MSL_C/w_math.h"
#endif

#include <dolphin/types.h>
#include "macros.h"

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

#define VER_GAFE01_00 0
#define VER_GAFU01_00 1

// TODO: add PAL version to this check
// Adjusts values based on regional frame rate (Hz)
#if VERSION == VER_GAFU01_00
#define FRAMERATE_ADJ(n) (((n) * 60) / 50) // less frames so more value
#define FRAMERATE_TIMER(n) (((n) * 50) / 60) // less frames so less timer
#define FRAMERATE_SELECT(f60, f50) (f50)
#else
#define FRAMERATE_ADJ(n) (n)
#define FRAMERATE_TIMER(n) (n)
#define FRAMERATE_SELECT(f60, f50) (f60)
#endif

typedef signed char s8;
typedef signed short s16;
#ifdef TARGET_PC
#include <stdint.h>
typedef int32_t  s32;
typedef uint32_t u32;
typedef int32_t  s32_compat;
typedef uint32_t u32_compat;
typedef int64_t  s64 ATTRIBUTE_ALIGN(8);
typedef uint64_t u64 ATTRIBUTE_ALIGN(8);
#include <stddef.h>
#else
typedef signed long s32;
typedef unsigned long u32;
typedef signed long s32_compat;
typedef unsigned long u32_compat;
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned long size_t;
#endif
typedef signed long long s64;
typedef unsigned long long u64;
#endif
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
#ifdef TARGET_PC
typedef double f64 ATTRIBUTE_ALIGN(8);
#else
typedef double f64;
#endif
typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef int BOOL;

// Pointer to unknown, to be determined at a later date.
typedef void* unkptr;
typedef u32 unknown;

#define TRUE 1
#define FALSE 0

#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*)0)
#else
#define NULL 0
#endif
#endif
#if !defined(__cplusplus) && !defined(nullptr)
#define nullptr 0
#endif

// #ifdef __MWERKS__
// #define AT_ADDRESS(x) : (x)
// #else
// #define AT_ADDRESS(x) __attribute__((section(".data." #x)))
// #endif

#define ALIGN_PREV(u, align) (u & (~(align - 1)))
#define ALIGN_NEXT(u, align) ((u + (align - 1)) & (~(align - 1)))
#define IS_ALIGNED(X, N) (((X) & ((N) - 1)) == 0)
#define IS_NOT_ALIGNED(X, N) (((X) & ((N) - 1)) != 0)

#define FLAG_ON(V, F) (((V) & (F)) == 0)
#define FLAG_OFF(V, F) (((V) & (F)) != 0)


#define BUTTON_NONE 0x0000
#define BUTTON_CRIGHT 0x0001
#define BUTTON_CLEFT 0x0002
#define BUTTON_CDOWN 0x0004
#define BUTTON_CUP 0x0008
#define BUTTON_R 0x0010
#define BUTTON_L 0x0020
#define BUTTON_X 0x0040
#define BUTTON_Y 0x0080
#define BUTTON_DRIGHT 0x0100
#define BUTTON_DLEFT 0x0200
#define BUTTON_DDOWN 0x0400
#define BUTTON_DUP 0x0800
#define BUTTON_START 0x1000
#define BUTTON_Z 0x2000
#define BUTTON_B 0x4000
#define BUTTON_A 0x8000

#define FRAMES_PER_SECOND 60
#define FRAMES_PER_MINUTE (FRAMES_PER_SECOND * 60)

#define ARRAY_SIZE(arr, type) (sizeof(arr) / sizeof(type))
#define ARRAY_COUNT(arr) (int)(sizeof(arr) / sizeof(arr[0]))

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define FLOOR(n, f) (((n) / (f)) * (f))

#define F32_IS_ZERO(v) (fabsf(v) < 0.008f)

#define DECREMENT_TIMER(timer) ((timer) == 0 ? 0 : --(timer))

/* ARGB8 color format (32 bits) to RGB5A3 color format (16 bits) */
#define ARGB8_to_RGB5A3(argb8)                                                                                     \
    ((u16)(((argb8) & 0xFF000000) >= 0xE0000000                                                                    \
               ? /* Fully opaque, 5 bits per color channel */ (0x8000 | ((((argb8) >> 16) & 0xF8) << 7) |          \
                                                               ((((argb8) >> 8) & 0xF8) << 2) |                    \
                                                               (((argb8) & 0xFF) >> 3))                            \
               : /* 3 bits of transparency, 4 bits per color channel */ (                                          \
                     ((((argb8) >> 24) & 0xE0) << 7) | ((((argb8) >> 16) & 0xF0) << 4) | (((argb8) >> 8) & 0xF0) | \
                     (((argb8) & 0xF0) >> 4))))

#define GPACK_RGB5A3(r, g, b, a) \
    ARGB8_to_RGB5A3((((a) & 0xFF) << 24) | (((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))

#if !defined(TARGET_PC)
#pragma section RX "forcestrip"
#endif
#if !defined(__INTELLISENSE__) && !defined(TARGET_PC)
#define FORCESTRIP __declspec(section "forcestrip")
#else
#define FORCESTRIP
#endif

#if defined(MUST_MATCH) && defined(__MWERKS__)
#define MATCH_FORCESTRIP FORCESTRIP
#else
#define MATCH_FORCESTRIP
#endif

#if !defined(__INTELLISENSE__) && defined(MUST_MATCH) && !defined(TARGET_PC)
#define ORDER_BSS_DATA static asm void order_bss()
#define ORDER_BSS(s) lis r3, s @ha
#define BSS_ORDER_GROUP_START FORCESTRIP ORDER_BSS_DATA {
#define BSS_ORDER_GROUP_END }
#define BSS_ORDER_ITEM(v) ORDER_BSS(v)
#else
#define BSS_ORDER_GROUP_START
#define BSS_ORDER_GROUP_END
#define BSS_ORDER_ITEM(v)
#endif

#if !defined(__cplusplus) && !defined(TARGET_PC)
// Some definitions rely on wchar_t being defined
typedef unsigned short wchar_t;
#endif

// #if DEBUG
// #define ASSERTLINE(line, cond) \
//     ((cond) || (OSPanic(__FILE__, line, "Failed assertion " #cond), 0))

// #define ASSERTMSGLINE(line, cond, msg) \
//     ((cond) || (OSPanic(__FILE__, line, msg), 0))

// // This is dumb but we dont have a Metrowerks way to do variadic macros in the macro to make this done in a not scrubby way.
// #define ASSERTMSG1LINE(line, cond, msg, arg1) \
//     ((cond) || (OSPanic(__FILE__, line, msg, arg1), 0))
    
// #define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
//     ((cond) || (OSPanic(__FILE__, line, msg, arg1, arg2), 0))

// #define ASSERTMSGLINEV(line, cond, ...) \
//     ((cond) || (OSPanic(__FILE__, line, __VA_ARGS__), 0))

// #else
// #define ASSERTLINE(line, cond) (void)0
// #define ASSERTMSGLINE(line, cond, msg) (void)0
// #define ASSERTMSG1LINE(line, cond, msg, arg1) (void)0
// #define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) (void)0
// #define ASSERTMSGLINEV(line, cond, ...) (void)0
// #endif

#endif
