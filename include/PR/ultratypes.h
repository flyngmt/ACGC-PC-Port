#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_


/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/


/*************************************************************************
 *
 *  File: ultratypes.h
 *
 *  This file contains various types used in Ultra64 interfaces.
 *
 *  $Revision: 1.6 $
 *  $Date: 1997/12/17 04:02:06 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/ultratypes.h,v $
 *
 **************************************************************************/



/**********************************************************************
 * General data types for R4300
 */
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) || defined(TARGET_PC)

#ifdef TARGET_PC
/* On PC, types are already defined by types.h / dolphin/types.h via stdint.h.
 * Only define them here if they haven't been defined yet. */
#include <stdint.h>
#include <stddef.h>
#ifndef _DOLPHIN_TYPES_H_
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef uint32_t            u32;
typedef uint64_t            u64;
typedef signed char         s8;
typedef short               s16;
typedef int32_t             s32;
typedef int64_t             s64;
typedef volatile unsigned char      vu8;
typedef volatile unsigned short     vu16;
typedef volatile uint32_t           vu32;
typedef volatile uint64_t           vu64;
typedef volatile signed char        vs8;
typedef volatile short              vs16;
typedef volatile int32_t            vs32;
typedef volatile int64_t            vs64;
typedef float   f32;
typedef double  f64;
#endif /* _DOLPHIN_TYPES_H_ */
#else
/* N64/GC original types */
typedef unsigned char       u8;     /* unsigned  8-bit */
typedef unsigned short      u16;    /* unsigned 16-bit */
typedef unsigned long       u32;    /* unsigned 32-bit */
typedef unsigned long long  u64;    /* unsigned 64-bit */

typedef signed char         s8;     /* signed  8-bit */
typedef short               s16;    /* signed 16-bit */
typedef long                s32;    /* signed 32-bit */
typedef long long           s64;    /* signed 64-bit */

typedef volatile unsigned char      vu8;    /* unsigned  8-bit */
typedef volatile unsigned short     vu16;   /* unsigned 16-bit */
typedef volatile unsigned long      vu32;   /* unsigned 32-bit */
typedef volatile unsigned long long vu64;   /* unsigned 64-bit */

typedef volatile signed char        vs8;    /* signed  8-bit */
typedef volatile short              vs16;   /* signed 16-bit */
typedef volatile long               vs32;   /* signed 32-bit */
typedef volatile long long          vs64;   /* signed 64-bit */

typedef float   f32;    /* single prec floating point */
typedef double  f64;    /* double prec floating point */
#endif /* TARGET_PC */

#ifndef TARGET_PC
#if !defined(_SIZE_T) && !defined(_SIZE_T_) && !defined(_SIZE_T_DEF)
#define _SIZE_T
#define _SIZE_T_DEF         /* exeGCC size_t define label */
#if (_MIPS_SZLONG == 32)
typedef unsigned int    size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long   size_t;
#endif
#endif
#endif /* TARGET_PC */

#endif  /* _LANGUAGE_C */

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL    0
#endif

#endif  /* _ULTRATYPES_H_ */
