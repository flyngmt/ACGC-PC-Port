#ifndef __GBI_EXTENSIONS_H__
#define __GBI_EXTENSIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

#include "types.h"

#ifndef _GBI_STATIC_PTR
#ifdef TARGET_PC
#if UINTPTR_MAX > 0xFFFFFFFFu
#define _GBI_STATIC_PTR(s) (uintptr_t)(s)
#else
#define _GBI_STATIC_PTR(s) (unsigned int)(uintptr_t)(s)
#endif
#else
#define _GBI_STATIC_PTR(s) (unsigned int)(s)
#endif
#endif
#include <PR/mbi.h>
#include "dolphin/gx.h"

#define SOFTSPRITE_MTX_SEG 0x07
#define ANIME_1_TXT_SEG 0x08
#define ANIME_2_TXT_SEG 0x09
#define ANIME_3_TXT_SEG 0x0A
#define ANIME_4_TXT_SEG 0x0B
#define ANIME_5_TXT_SEG 0x0C
#define ANIME_6_TXT_SEG 0x0D

#define ANIME_4_TXT_SIZE 0x800
#define ANIME_6_MODEL_SIZE 0x408

#define SEG_EQUALS(seg_addr, seg) (seg_addr == SEGMENT_ADDR(seg, 0))

#define softsprite_mtx SEGMENT_ADDR(SOFTSPRITE_MTX_SEG, 0)
#define anime_1_txt SEGMENT_ADDR(ANIME_1_TXT_SEG, 0)
#define anime_1_model SEGMENT_ADDR(ANIME_1_TXT_SEG, 0)
#define anime_2_txt SEGMENT_ADDR(ANIME_2_TXT_SEG, 0)
#define anime_2_model SEGMENT_ADDR(ANIME_2_TXT_SEG, 0)
#define anime_3_txt SEGMENT_ADDR(ANIME_3_TXT_SEG, 0)
#define anime_3_model SEGMENT_ADDR(ANIME_3_TXT_SEG, 0)
#define anime_4_txt SEGMENT_ADDR(ANIME_4_TXT_SEG, 0)
#define anime_4_model SEGMENT_ADDR(ANIME_4_TXT_SEG, 0)
#define anime_5_txt SEGMENT_ADDR(ANIME_5_TXT_SEG, 0)
#define anime_5_model SEGMENT_ADDR(ANIME_5_TXT_SEG, 0)
#define anime_6_txt SEGMENT_ADDR(ANIME_6_TXT_SEG, 0)
#define anime_6_model SEGMENT_ADDR(ANIME_6_TXT_SEG, 0)
#define anime_6_mdl ((Mtx*)anime_6_model)

/* New Microcode Command Ids */
#define G_TRIN 0x09
#define G_TRIN_INDEPEND 0x0A

#define G_SETTEXEDGEALPHA 0xCE
#define G_SETCOMBINE_NOTEV 0xCF
#define G_SETCOMBINE_TEV 0xD0
#define G_SETTILE_DOLPHIN 0xD2

#define G_FIRST_CMD G_SETTEXEDGEALPHA

#define G_CC_BLENDPRIMDECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0

/* Triangle/Quad vertex bit size */
#define POLY_5b 0 /* 5 bits per vertex index (0 - 31) */
#define POLY_7b 1 /* 7 bits per vertex index (0 - 127) */
#define POLY_BITMASK 1

/* First face, 5 bits */
#define POLY_GET_V0_5b(g)((g->words.w1 >> 4) & 0x1F)
#define POLY_GET_V1_5b(g)((g->words.w1 >> 9) & 0x1F)
#define POLY_GET_V2_5b(g)((g->words.w1 >> 14) & 0x1F)

/* Second face, 5 bits */
#define POLY_GET_V3_5b(g)((g->words.w1 >> 19) & 0x1F)
#define POLY_GET_V4_5b(g)((g->words.w1 >> 24) & 0x1F)
#define POLY_GET_V5_5b(g)((((g->words.w1 >> 29) & 7) | ((g->words.w0 & 3) << 3)) & 0x1F)

/* Third face, 5 bits */
#define POLY_GET_V6_5b(g)((g->words.w0 >> 2) & 0x1F)
#define POLY_GET_V7_5b(g)((g->words.w0 >> 7) & 0x1F)
#define POLY_GET_V8_5b(g)((g->words.w0 >> 12) & 0x1F)

/* Fourth face, 5 bits */
#define POLY_GET_V9_5b(g)((g->words.w0 >> 17) & 0x1F)
#define POLY_GET_V10_5b(g)((g->words.w0 >> 22) & 0x1F)
#define POLY_GET_V11_5b(g)((g->words.w0 >> 27) & 0x1F)

/* First face, 7 bits */
#define POLY_GET_V0_7b(g)((g->words.w1 >> 1) & 0x7F)
#define POLY_GET_V1_7b(g)((g->words.w1 >> 8) & 0x7F)
#define POLY_GET_V2_7b(g)((g->words.w1 >> 15) & 0x7F)

/* Second face, 7 bits */
#define POLY_GET_V3_7b(g)((g->words.w1 >> 22) & 0x7F)
#define POLY_GET_V4_7b(g)((((g->words.w1 >> 29) & 7) | ((g->words.w0 & 0xF) << 3)) & 0x7F)
#define POLY_GET_V5_7b(g)((g->words.w0 >> 4) & 0x7F)

/* Third face, 7 bits */
#define POLY_GET_V6_7b(g)((g->words.w0 >> 11) & 0x7F)
#define POLY_GET_V7_7b(g)((g->words.w0 >> 18) & 0x7F)
#define POLY_GET_V8_7b(g)((g->words.w0 >> 25) & 0x7F)

/* Vertex matrix types */
#define SHARED_MTX GX_PNMTX0
#define NONSHARED_MTX GX_PNMTX1

#define MTX_SHARED 0
#define MTX_NONSHARED 1

/* NOOP Debug Tags */
#define G_TAG_NONE 0
#define G_TAG_HERE 1
#define G_TAG_STRING 2
#define G_TAG_WORD 3
#define G_TAG_FLOAT 4
#define G_TAG_INFO 5
#define G_TAG_CALLBACK 6
#define G_TAG_OPENDISP 7
#define G_TAG_CLOSEDISP 8
#define G_TAG_FILL 9

/* Vertex Culling Flags */
#define G_CULL_X_LESSTHAN 0x100 /* x component left of culling plane */
#define G_CULL_X_GREATERTHAN 0x200 /* x component right of culling plane */
#define G_CULL_Y_LESSTHAN 0x400 /* y component below culling plane */
#define G_CULL_Y_GREATERTHAN 0x800 /* y component above culling plane */
#define G_CULL_Z_LESSTHAN 0x1000 /* z component behind culling plane */
#define G_CULL_Z_GREATERTHAN 0x2000 /* z component farther than culling plane */

/* Extra Geometry Mode Flags */
#define G_LIGHTING_POSITIONAL 0x400000
#define G_DECAL_LEQUAL 0x00
#define G_DECAL_GEQUAL 0x10
#define G_DECAL_EQUAL 0x20
#define G_DECAL_ALWAYS 0x30
#define G_DECAL_SPECIAL 0x40
#define G_DECAL_ALL (G_DECAL_ALWAYS | G_DECAL_SPECIAL)

/* Indicies for G_SPECIAL_1 */
#define G_SPECIAL_NONE 0
#define G_SPECIAL_UNKNOWN 1
#define G_SPECIAL_TA_MODE 2

/* Texture Adjust Modes (used in G_SPECIAL1) */
#define G_TA_N64 0
#define G_TA_DOLPHIN 1

/* Combiner Param Ids */
#define COMBINER_PARAM_A 1
#define COMBINER_PARAM_B 2
#define COMBINER_PARAM_C 3
#define COMBINER_PARAM_D 4

/* TEV Combiner Settings */

#define TEV_COMBINED 0
#define TEV_COMBINED_ALPHA 1
#define TEV_FILL 2
#define TEV_PRIM_LOD_FRAC 3
#define TEV_PRIMITIVE 4
#define TEV_PRIMITIVE_ALPHA 5
#define TEV_ENVIRONMENT 6
#define TEV_ENV_ALPHA 7
#define TEV_TEXEL0 8
#define TEV_TEXEL0_ALPHA 9
#define TEV_SHADE 10
#define TEV_SHADE_ALPHA 11
#define TEV_ONE 12
#define TEV_HALF 13
#define TEV_KONST 14
#define TEV_ZERO 15

#define TEV_ALPHA_COMBINED 0
#define TEV_ALPHA_PRIM_LOD_FRAC 1
#define TEV_ALPHA_PRIMITIVE 2
#define TEV_ALPHA_ENVIRONMENT 3
#define TEV_ALPHA_TEXEL0 4
#define TEV_ALPHA_SHADE 5
#define TEV_ALPHA_ONE 6
#define TEV_ALPHA_ZERO 7

/* Macro to expand packed image/tile width and height */
#define EXPAND_WIDTH(wd)(wd + 1)
#define EXPAND_HEIGHT(ht)((ht + 1) * 4)

/* Combiner Macros */

#define COMBINER_GET_a0(words)((words.w0 >> 20) & 0xF)
#define COMBINER_GET_b0(words)((words.w1 >> 28) & 0xF)
#define COMBINER_GET_c0(words)((words.w0 >> 15) & 0x1F)
#define COMBINER_GET_d0(words)((words.w1 >> 15) & 7)

#define COMBINER_GET_Aa0(words)((words.w0 >> 12) & 7)
#define COMBINER_GET_Ab0(words)((words.w1 >> 12) & 7)
#define COMBINER_GET_Ac0(words)((words.w0 >> 9) & 7)
#define COMBINER_GET_Ad0(words)((words.w1 >> 9) & 7)

#define COMBINER_GET_a1(words)((words.w0 >> 5) & 0xF)
#define COMBINER_GET_b1(words)((words.w1 >> 24) & 0xF)
#define COMBINER_GET_c1(words)(words.w0 & 0x1F)
#define COMBINER_GET_d1(words)((words.w1 >> 6) & 7)

#define COMBINER_GET_Aa1(words)((words.w1 >> 21) & 7)
#define COMBINER_GET_Ab1(words)((words.w1 >> 3) & 7)
#define COMBINER_GET_Ac1(words)((words.w1 >> 18) & 7)
#define COMBINER_GET_Ad1(words)(words.w1 & 7)

/* TEV Combiner Macros */

#define COMBINER_TEV_GET_a0(words)((words.w1 >> 28) & 0xF)
#define COMBINER_TEV_GET_b0(words)((words.w1 >> 24) & 0xF)
#define COMBINER_TEV_GET_c0(words)((words.w1 >> 20) & 0xF)
#define COMBINER_TEV_GET_d0(words)((words.w1 >> 16) & 0xF)

#define COMBINER_TEV_GET_Aa0(words)((words.w0 >> 21) & 7)
#define COMBINER_TEV_GET_Ab0(words)((words.w0 >> 18) & 7)
#define COMBINER_TEV_GET_Ac0(words)((words.w0 >> 15) & 7)
#define COMBINER_TEV_GET_Ad0(words)((words.w0 >> 12) & 7)

#define COMBINER_TEV_GET_a1(words)((words.w1 >> 12) & 0xF)
#define COMBINER_TEV_GET_b1(words)((words.w1 >>  8) & 0xF)
#define COMBINER_TEV_GET_c1(words)((words.w1 >>  4) & 0xF)
#define COMBINER_TEV_GET_d1(words)((words.w1 >>  0) & 0xF)

#define COMBINER_TEV_GET_Aa1(words)((words.w0 >>  9) & 7)
#define COMBINER_TEV_GET_Ab1(words)((words.w0 >>  6) & 7)
#define COMBINER_TEV_GET_Ac1(words)((words.w0 >>  3) & 7)
#define COMBINER_TEV_GET_Ad1(words)((words.w0 >>  0) & 7)

/*
 * NOTE: On TARGET_PC (little-endian), bitfield order is reversed within each
 * 32-bit word so that fields map to the same bit positions as the GBI shift
 * macros. See gbi.h for detailed explanation.
 */

#ifdef TARGET_PC
typedef struct {
    unsigned int c1:5;
    unsigned int a1:4;
    unsigned int Ac0:3;
    unsigned int Aa0:3;
    unsigned int c0:5;
    unsigned int a0:4;
    unsigned int cmd:8;
    unsigned int Ad1:3;
    unsigned int Ab1:3;
    unsigned int d1:3;
    unsigned int Ad0:3;
    unsigned int Ab0:3;
    unsigned int d0:3;
    unsigned int Ac1:3;
    unsigned int Aa1:3;
    unsigned int b1:4;
    unsigned int b0:4;
} Gsetcombine_new;
#else
typedef struct {
    unsigned int cmd:8;
    unsigned int a0:4;
    unsigned int c0:5;
    unsigned int Aa0:3;
    unsigned int Ac0:3;
    unsigned int a1:4;
    unsigned int c1:5;
    unsigned int b0:4;
    unsigned int b1:4;
    unsigned int Aa1:3;
    unsigned int Ac1:3;
    unsigned int d0:3;
    unsigned int Ab0:3;
    unsigned int Ad0:3;
    unsigned int d1:3;
    unsigned int Ab1:3;
    unsigned int Ad1:3;
} Gsetcombine_new;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int Ad1:3;
    unsigned int Ac1:3;
    unsigned int Ab1:3;
    unsigned int Aa1:3;
    unsigned int Ad0:3;
    unsigned int Ac0:3;
    unsigned int Ab0:3;
    unsigned int Aa0:3;
    int cmd:8;
    unsigned int d1:4;
    unsigned int c1:4;
    unsigned int b1:4;
    unsigned int a1:4;
    unsigned int d0:4;
    unsigned int c0:4;
    unsigned int b0:4;
    unsigned int a0:4;
} Gsetcombine_tev;
#else
typedef struct {
    int cmd:8; /* 0xCF */
    unsigned int Aa0:3;
    unsigned int Ab0:3;
    unsigned int Ac0:3;
    unsigned int Ad0:3;
    unsigned int Aa1:3;
    unsigned int Ab1:3;
    unsigned int Ac1:3;
    unsigned int Ad1:3;
    unsigned int a0:4;
    unsigned int b0:4;
    unsigned int c0:4;
    unsigned int d0:4;
    unsigned int a1:4;
    unsigned int b1:4;
    unsigned int c1:4;
    unsigned int d1:4;
} Gsetcombine_tev;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int lower0:16;
    unsigned int upper0:8;
    int cmd:8;
    unsigned int lower1:16;
    unsigned int upper1:16;
} Gsetcombine_raw;
#else
typedef struct {
    int cmd:8;
    unsigned int upper0:8;
    unsigned int lower0:16;
    unsigned int upper1:16;
    unsigned int lower1:16;
} Gsetcombine_raw;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int yl:12;
    unsigned int xl:12;
    unsigned int cmd:8;
    unsigned int yh:12;
    unsigned int xh:12;
    unsigned int tile:3;
    unsigned int pad1:5;
    unsigned int pad2:32;
    unsigned int t:16;
    unsigned int s:16;
    unsigned int pad3:32;
    unsigned int dtdy:16;
    unsigned int dsdx:16;
} Gtexrect2;
#else
typedef struct {
    unsigned int cmd:8;
    unsigned int xl:12;
    unsigned int yl:12;
    unsigned int pad1:5;
    unsigned int tile:3;
    unsigned int xh:12;
    unsigned int yh:12;
    unsigned int pad2:32;
    unsigned int s:16;
    unsigned int t:16;
    unsigned int pad3:32;
    unsigned int dsdx:16;
    unsigned int dtdy:16;
} Gtexrect2;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int shift_t:4;
    unsigned int shift_s:4;
    unsigned int wrap_t:2;
    unsigned int wrap_s:2;
    unsigned int tlut_name:4;
    unsigned int tile:3;
    unsigned int pad0:1;
    unsigned int dol_fmt:4;
    int cmd:8;
    unsigned int pad1:32;
} Gsettile_dolphin;
#else
typedef struct {
    int cmd:8;
    unsigned int dol_fmt:4;
    unsigned int pad0:1;
    unsigned int tile:3;
    unsigned int tlut_name:4;
    unsigned int wrap_s:2;
    unsigned int wrap_t:2;
    unsigned int shift_s:4;
    unsigned int shift_t:4;
    unsigned int pad1:32;
} Gsettile_dolphin;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int slen:10;
    unsigned int sl:14;
    int cmd:8;
    unsigned int tlen:10;
    unsigned int tl:14;
    unsigned int tile:3;
    unsigned int pad:4;
    s8 isDolphin:1;
} Gsettilesize_Dolphin;
#else
typedef struct {
    int cmd:8;
    unsigned int sl:14;
    unsigned int slen:10;
    s8 isDolphin:1;
    unsigned int pad:4;
    unsigned int tile:3;
    unsigned int tl:14;
    unsigned int tlen:10;
} Gsettilesize_Dolphin;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int wd:10;
    unsigned int ht:8;
    unsigned int isDolphin:1;
    unsigned int siz:2;
    unsigned int fmt:3;
    int cmd:8;
    unsigned int imgaddr:32;
} Gsetimg2;
#else
typedef struct {
    int cmd:8;
    unsigned int fmt:3;
    unsigned int siz:2;
    unsigned int isDolphin:1;
    unsigned int ht:8;
    unsigned int wd:10;
    unsigned int imgaddr:32;
} Gsetimg2;
#endif

typedef union {
    Gsetimg setimg;
    Gsetimg2 setimg2;
} Gsetimg_new;

#ifdef TARGET_PC
typedef struct {
    unsigned int count:14;
    unsigned int pad1:2;
    unsigned int tlut_name:4;
    unsigned int pad0:2;
    unsigned int type:2;
    int cmd:8;
    unsigned int tlut_addr:32;
} Gloadtlut_dolphin;
#else
typedef struct {
    int cmd:8;
    unsigned int type:2;
    unsigned int pad0:2;
    unsigned int tlut_name:4;
    unsigned int pad1:2;
    unsigned int count:14;
    unsigned int tlut_addr:32;
} Gloadtlut_dolphin;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int on:8;
    unsigned int tile:3;
    unsigned int level:3;
    unsigned int pad:2;
    unsigned int xparam:8;
    unsigned int cmd:8;
    unsigned short t;
    unsigned short s;
} Gtexture_internal;
#else
typedef struct {
    unsigned int cmd:8;
    unsigned int xparam:8;
    unsigned int pad:2;
    unsigned int level:3;
    unsigned int tile:3;
    unsigned int on:8;
    unsigned short s;
    unsigned short t;
} Gtexture_internal;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int offset:16;
    unsigned int index:8;
    unsigned int cmd:8;
    unsigned int data;
} Gmoveword;
#else
typedef struct {
    unsigned int cmd:8;
    unsigned int index:8;
    unsigned int offset:16;
    unsigned int data;
} Gmoveword;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int index:8;
    unsigned int offset:8;
    unsigned int length:8;
    unsigned int cmd:8;
    unsigned int data;
} Gmovemem;
#else
typedef struct {
    unsigned int cmd:8;
    unsigned int length:8;
    unsigned int offset:8;
    unsigned int index:8;
    unsigned int data;
} Gmovemem;
#endif

#ifdef TARGET_PC
typedef struct Gsettexedgealpha {
    unsigned int unused0:24;
    unsigned int cmd:8;
    unsigned int tex_edge_alpha:8;
    unsigned int unused1:24;
} Gsettexedgealpha;
#else
typedef struct Gsettexedgealpha {
    unsigned int cmd:8;
    unsigned int unused0:24;
    unsigned int unused1:24;
    unsigned int tex_edge_alpha:8;
} Gsettexedgealpha;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int		y0frac:2;
    unsigned int		y0:10;
    unsigned int		x0frac:2;
    unsigned int		x0:10;
    int		            cmd:8;
    unsigned int		y1frac:2;
    unsigned int		y1:10;
    unsigned int		x1frac:2;
    unsigned int		x1:10;
    unsigned int        pad:8;
} Gscissor;
#else
typedef struct {
    int		            cmd:8;
    unsigned int		x0:10;
    unsigned int		x0frac:2;
    unsigned int		y0:10;
    unsigned int		y0frac:2;
    unsigned int        pad:8;
    unsigned int		x1:10;
    unsigned int		x1frac:2;
    unsigned int		y1:10;
    unsigned int		y1frac:2;
} Gscissor;
#endif

#ifdef TARGET_PC
typedef struct {
    unsigned int		y0frac:2;
    unsigned int		y0:10;
    unsigned int		x0frac:2;
    unsigned int		x0:10;
    int		            cmd:8;
    unsigned int		y1frac:2;
    unsigned int		y1:10;
    unsigned int		x1frac:2;
    unsigned int		x1:10;
    unsigned int	    pad:8;
} Gfillrect2;
#else
typedef struct {
    int		            cmd:8;
    unsigned int		x0:10;
    unsigned int		x0frac:2;
    unsigned int		y0:10;
    unsigned int		y0frac:2;
    unsigned int	    pad:8;
    unsigned int		x1:10;
    unsigned int		x1frac:2;
    unsigned int		y1:10;
    unsigned int		y1frac:2;
} Gfillrect2;
#endif

#ifdef TARGET_PC
typedef struct Gnoop {
    unsigned int param0: 16;
    unsigned int tag: 8;
    unsigned int cmd: 8;
    unsigned int param1;
} Gnoop;
#else
typedef struct Gnoop {
    unsigned int cmd: 8;
    unsigned int tag: 8;
    unsigned int param0: 16;
    unsigned int param1;
} Gnoop;
#endif

#ifdef TARGET_PC
typedef struct Gmtx {
    unsigned int type: 8;
    unsigned int pad: 8;
    unsigned int par: 8;
    unsigned int cmd: 8;
    unsigned int addr;
} Gmtx;
#else
typedef struct Gmtx {
    unsigned int cmd: 8;
    unsigned int par: 8;
    unsigned int pad: 8;
    unsigned int type: 8;
    unsigned int addr;
} Gmtx;
#endif

#ifdef TARGET_PC
typedef struct Gvtx {
    unsigned int vn:8;
    unsigned int pad1: 4;
    unsigned int n: 8;
    unsigned int pad0: 4;
    unsigned int cmd: 8;
    unsigned int addr;
} Gvtx;
#else
typedef struct Gvtx {
    unsigned int cmd: 8;
    unsigned int pad0: 4;
    unsigned int n: 8;
    unsigned int pad1: 4;
    unsigned int vn:8;
    unsigned int addr;
} Gvtx;
#endif

#ifdef TARGET_PC
typedef struct Gline3D_new {
    unsigned int wd: 8;
    unsigned int v1: 8;
    unsigned int v0: 8;
    unsigned int cmd: 8;
    unsigned int pad;
} Gline3D_new;
#else
typedef struct Gline3D_new {
    unsigned int cmd: 8;
    unsigned int v0: 8;
    unsigned int v1: 8;
    unsigned int wd: 8;
    unsigned int pad;
} Gline3D_new;
#endif

#ifdef TARGET_PC
typedef struct Gtri1 {
    unsigned int v2: 8;
    unsigned int v1: 8;
    unsigned int v0: 8;
    unsigned int cmd: 8;
    unsigned int pad;
} Gtri1;
#else
typedef struct Gtri1 {
    unsigned int cmd: 8;
    unsigned int v0: 8;
    unsigned int v1: 8;
    unsigned int v2: 8;
    unsigned int pad;
} Gtri1;
#endif

#ifdef TARGET_PC
typedef struct Gtri2 {
    unsigned int t0v2: 8;
    unsigned int t0v1: 8;
    unsigned int t0v0: 8;
    int cmd: 8;
    unsigned int t1v2: 8;
    unsigned int t1v1: 8;
    unsigned int t1v0: 8;
    unsigned int pad: 8;
} Gtri2;
#else
typedef struct Gtri2 {
    int cmd: 8;
    unsigned int t0v0: 8;
    unsigned int t0v1: 8;
    unsigned int t0v2: 8;
    unsigned int pad: 8;
    unsigned int t1v0: 8;
    unsigned int t1v1: 8;
    unsigned int t1v2: 8;
} Gtri2;
#endif

#ifdef TARGET_PC
typedef struct Gtrin_independ {
    unsigned int f1v2_1: 2;
    unsigned int f2v0: 5;
    unsigned int f2v1: 5;
    unsigned int f2v2: 5;
    unsigned int count: 7;
    unsigned int cmd: 8;
    unsigned int is7bit: 1;
    unsigned int pad: 3;
    unsigned int f0v0: 5;
    unsigned int f0v1: 5;
    unsigned int f0v2: 5;
    unsigned int f1v0: 5;
    unsigned int f1v1: 5;
    unsigned int f1v2_0: 3;
} Gtrin_independ;
#else
typedef struct Gtrin_independ {
    unsigned int cmd: 8;
    unsigned int count: 7;
    unsigned int f2v2: 5;
    unsigned int f2v1: 5;
    unsigned int f2v0: 5;
    unsigned int f1v2_1: 2;
    unsigned int f1v2_0: 3;
    unsigned int f1v1: 5;
    unsigned int f1v0: 5;
    unsigned int f0v2: 5;
    unsigned int f0v1: 5;
    unsigned int f0v0: 5;
    unsigned int pad: 3;
    unsigned int is7bit: 1;
} Gtrin_independ;
#endif

#ifdef TARGET_PC
typedef struct Gtrin {
    unsigned int f1v2_1: 2;
    unsigned int f2v0: 5;
    unsigned int f2v1: 5;
    unsigned int f2v2: 5;
    unsigned int f3v0: 5;
    unsigned int f3v1: 5;
    unsigned int f3v2: 5;
    unsigned int is7bit: 1;
    unsigned int pad: 3;
    unsigned int f0v0: 5;
    unsigned int f0v1: 5;
    unsigned int f0v2: 5;
    unsigned int f1v0: 5;
    unsigned int f1v1: 5;
    unsigned int f1v2_0: 3;
} Gtrin;
#else
typedef struct Gtrin {
    unsigned int f3v2: 5;
    unsigned int f3v1: 5;
    unsigned int f3v0: 5;
    unsigned int f2v2: 5;
    unsigned int f2v1: 5;
    unsigned int f2v0: 5;
    unsigned int f1v2_1: 2;
    unsigned int f1v2_0: 3;
    unsigned int f1v1: 5;
    unsigned int f1v0: 5;
    unsigned int f0v2: 5;
    unsigned int f0v1: 5;
    unsigned int f0v0: 5;
    unsigned int pad: 3;
    unsigned int is7bit: 1;
} Gtrin;
#endif

#ifdef TARGET_PC
typedef struct Gtrin_7b {
    unsigned int f1v1_1: 4;
    unsigned int f1v2: 7;
    unsigned int f2v0: 7;
    unsigned int f2v1: 7;
    unsigned int f2v2: 7;
    unsigned int is7bit: 1;
    unsigned int f0v0: 7;
    unsigned int f0v1: 7;
    unsigned int f0v2: 7;
    unsigned int f1v0: 7;
    unsigned int f1v1_0: 3;
} Gtrin_7b;
#else
typedef struct Gtrin_7b {
    unsigned int f2v2: 7;
    unsigned int f2v1: 7;
    unsigned int f2v0: 7;
    unsigned int f1v2: 7;
    unsigned int f1v1_1: 4;
    unsigned int f1v1_0: 3;
    unsigned int f1v0: 7;
    unsigned int f0v2: 7;
    unsigned int f0v1: 7;
    unsigned int f0v0: 7;
    unsigned int is7bit: 1;
} Gtrin_7b;
#endif

#ifdef TARGET_PC
typedef struct Gquad_independ {
    unsigned int f1v1_1: 2;
    unsigned int f1v2: 5;
    unsigned int f1v3: 5;
    unsigned int unused: 5;
    unsigned int count: 7;
    unsigned int cmd: 8;
    unsigned int is7bit: 1;
    unsigned int pad: 3;
    unsigned int f0v0: 5;
    unsigned int f0v1: 5;
    unsigned int f0v2: 5;
    unsigned int f0v3: 5;
    unsigned int f1v0: 5;
    unsigned int f1v1_0: 3;
} Gquad_independ;
#else
typedef struct Gquad_independ {
    unsigned int cmd: 8;
    unsigned int count: 7;
    unsigned int unused: 5;
    unsigned int f1v3: 5;
    unsigned int f1v2: 5;
    unsigned int f1v1_1: 2;
    unsigned int f1v1_0: 3;
    unsigned int f1v0: 5;
    unsigned int f0v3: 5;
    unsigned int f0v2: 5;
    unsigned int f0v1: 5;
    unsigned int f0v0: 5;
    unsigned int pad: 3;
    unsigned int is7bit: 1;
} Gquad_independ;
#endif

#ifdef TARGET_PC
typedef struct Gquad {
    unsigned int f1v1_1: 2;
    unsigned int f1v2: 5;
    unsigned int f1v3: 5;
    unsigned int f2v0: 5;
    unsigned int f2v1: 5;
    unsigned int f2v2: 5;
    unsigned int f2v3: 5;
    unsigned int is7bit: 1;
    unsigned int pad: 3;
    unsigned int f0v0: 5;
    unsigned int f0v1: 5;
    unsigned int f0v2: 5;
    unsigned int f0v3: 5;
    unsigned int f1v0: 5;
    unsigned int f1v1_0: 3;
} Gquad;
#else
typedef struct Gquad {
    unsigned int f2v3: 5;
    unsigned int f2v2: 5;
    unsigned int f2v1: 5;
    unsigned int f2v0: 5;
    unsigned int f1v3: 5;
    unsigned int f1v2: 5;
    unsigned int f1v1_1: 2;
    unsigned int f1v1_0: 3;
    unsigned int f1v0: 5;
    unsigned int f0v3: 5;
    unsigned int f0v2: 5;
    unsigned int f0v1: 5;
    unsigned int f0v0: 5;
    unsigned int pad: 3;
    unsigned int is7bit: 1;
} Gquad;
#endif

#ifdef TARGET_PC
typedef struct Gquad_7b {
    unsigned int pad: 4;
    unsigned int f1v0_0: 3;
    unsigned int f1v0_1: 4;
    unsigned int f1v1: 7;
    unsigned int f1v2: 7;
    unsigned int f1v3: 7;
    unsigned int is7bit: 1;
    unsigned int pad0: 3;
    unsigned int f0v0: 7;
    unsigned int f0v1: 7;
    unsigned int f0v2: 7;
    unsigned int f0v3: 7;
} Gquad_7b;
#else
typedef struct Gquad_7b {
    unsigned int f1v3: 7;
    unsigned int f1v2: 7;
    unsigned int f1v1: 7;
    unsigned int f1v0_1: 4;
    unsigned int f1v0_0: 3;
    unsigned int pad: 4;
    unsigned int f0v3: 7;
    unsigned int f0v2: 7;
    unsigned int f0v1: 7;
    unsigned int f0v0: 7;
    unsigned int pad0: 3;
    unsigned int is7bit: 1;
} Gquad_7b;
#endif

#ifdef TARGET_PC
typedef struct Gquad0 {
    unsigned int v2: 8;
    unsigned int v1: 8;
    unsigned int v0: 8;
    int cmd: 8;
    unsigned int v3: 8;
    unsigned int pad: 24;
} Gquad0;
#else
typedef struct Gquad0 {
    int cmd: 8;
    unsigned int v0: 8;
    unsigned int v1: 8;
    unsigned int v2: 8;
    unsigned int pad: 24;
    unsigned int v3: 8;
} Gquad0;
#endif

#ifdef TARGET_PC
typedef struct Gculldl {
    unsigned int vstart: 16;
    unsigned int pad0: 8;
    int cmd: 8;
    unsigned int vend: 16;
    unsigned int pad1: 16;
} Gculldl;
#else
typedef struct Gculldl {
    int cmd: 8;
    unsigned int pad0: 8;
    unsigned int vstart: 16;
    unsigned int pad1: 16;
    unsigned int vend: 16;
} Gculldl;
#endif

#ifdef TARGET_PC
typedef struct Gspecial1 {
    unsigned int param0: 16;
    int mode: 8;
    int cmd: 8;
    unsigned int param1;
} Gspecial1;
#else
typedef struct Gspecial1 {
    int cmd: 8;
    int mode: 8;
    unsigned int param0: 16;
    unsigned int param1;
} Gspecial1;
#endif

#ifdef TARGET_PC
typedef struct {
		u32		len:8;
		u32		sft:8;
		int		pad0:8;
		int		cmd:8;
		unsigned int	data:32;
} Gsetothermode_dolphin;
#else
typedef struct {
		int		cmd:8;
		int		pad0:8;
		u32		sft:8;
		u32		len:8;
		unsigned int	data:32;
} Gsetothermode_dolphin;
#endif

typedef struct {
    unsigned char col[3];
    unsigned char kc;
    unsigned char colc[3];
    unsigned char kl;
    signed short pos[3]; /* position of light */
    unsigned char kq;
} Light_pos_t;

typedef union {
    Light_t l;
    Light_pos_t p;
    long long int force_align[2];
} Light_new;

/* Combiner Structs */
typedef struct {
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
} combiner_tev_color;

typedef struct {
    u8 alpha0;
    u8 alpha1;
} combiner_tev_alpha;

/* New Command Macros */
#define gDPParam2(cmd, tag, param, extra) \
do { \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(cmd, 24, 8) | _SHIFTL(tag, 16, 8) | _SHIFTL(param, 0, 16)); \
  _GBI_SET_W1_RAW(_g, (extra)); \
} while(0)

#define gsDPParam2(cmd, tag, param, extra) \
{{ \
	_SHIFTL(cmd, 24, 8) | _SHIFTL(tag, 16, 8) | _SHIFTL(param, 0, 16), extra \
}}

#define gDPNoOpTag2(tag, param, extra) gDPParam2(G_NOOP, tag, param, extra)
#define gsDPNoOpTag2(tag, param, extra) gsDPParam2(G_NOOP, tag, param, extra)

#define gDPNoOpHere() gDPNoOpTag2(G_TAG_HERE, __LINE__, __FILE__)
#define	gsDPNoOpHere() gsDPNoOpTag2(G_TAG_HERE, __LINE__, __FILE__)

#define gDPNoOpString(str, param) gDPNoOpTag2(G_TAG_STRING, param, str)
#define gsDPNoOpString(str, param) gsDPNoOpTag2(G_TAG_STRING, param, str)

#define gDPNoOpWord(word, param) gDPNoOpTag2(G_TAG_WORD, param, word)
#define gsDPNoOpWord(word, param) gsDPNoOpTag2(G_TAG_WORD, param, word)

#define gDPNoOpFloat(float, param) gDPNoOpTag2(G_TAG_FLOAT, param, float)
#define gsDPNoOpFloat(float, param) gsDPNoOpTag2(G_TAG_FLOAT, param, float)

#define gDPNoOpQuiet() gDPNoOpTag2(G_TAG_INFO, 0, 0)
#define gsDPNoOpQuiet() gsDPNoOpTag2(G_TAG_INFO, 0, 0)

#define gDPNoOpVerbose() gDPNoOpTag2(G_TAG_INFO, 0xF, 0)
#define gsDPNoOpVerbose() gsDPNoOpTag2(G_TAG_INFO, 0xF, 0)

#define gDPNoOpCallBack(callback, param) gDPNoOpTag2(G_TAG_CALLBACK, param, callback)
#define gsDPNoOpCallBack(callback, param) gsDPNoOpTag2(G_TAG_CALLBACK, param, callback)

#define gDPNoOpOpenDisp() gDPNoOpTag2(G_TAG_OPENDISP, __LINE__, __FILE__)
#define gsDPNoOpOpenDisp() gsDPNoOpTag2(G_TAG_OPENDISP, __LINE__, __FILE__)

#define gDPNoOpCloseDisp() gDPNoOpTag2(G_TAG_CLOSEDISP, __LINE__, __FILE__)
#define gsDPNoOpCloseDisp() gsDPNoOpTag2(G_TAG_CLOSEDISP, __LINE__, __FILE__)

#define gDPNoOpFill() gDPNoOpTag2(G_TAG_FILL, 0, 0)
#define gsDPNoOpFill() gsDPNoOpTag2(G_TAG_FILL, 0, 0)

#define gDPNoOpTag3(tag, extra, param) gDPNoOpTag2(tag, param, extra)
#define gsDPNoOpTag3(tag, extra, param) gsDPNoOpTag2(tag, param, extra)

#define G_TLUT_DOLPHIN 2
#define gDPLoadTLUT_Dolphin(pkt, name, count, unk, addr) \
do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL(G_TLUT_DOLPHIN, 22, 2) | _SHIFTL(name, 16, 4) | _SHIFTL(unk, 14, 2) | _SHIFTL(count, 0, 14); \
    _GBI_SET_W1(_g, addr); \
} while (0)

#define gsDPLoadTLUT_Dolphin(name, count, unk, addr) \
{{ \
    _SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL(G_TLUT_DOLPHIN, 22, 2) | _SHIFTL(name, 16, 4) | _SHIFTL(unk, 14, 2) | _SHIFTL(count, 0, 14), _GBI_STATIC_PTR(addr) \
}}

#define gsDPSetTextureImage_Dolphin(fmt, siz, w, h, img) \
{{ \
    _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(1, 18, 1) | \
        _SHIFTL((h/4)-1, 10, 8) | _SHIFTL((w-1), 0, 10), _GBI_STATIC_PTR(img) \
}}

#define gsDPSetTile_Dolphin(d_fmt, tile, tlut_name, wrap_s, wrap_t, shift_s, shift_t) \
{{ \
    _SHIFTL(G_SETTILE_DOLPHIN, 24, 8) | _SHIFTL(d_fmt, 20, 4) | _SHIFTL(tile, 16, 3) | \
        _SHIFTL(tlut_name, 12, 4) | _SHIFTL(wrap_s, 10, 2) | _SHIFTL(wrap_t, 8, 2) | \
        _SHIFTL(shift_s, 4, 4) | _SHIFTL(shift_t, 0, 4), 0 \
}}

#define gDPSetTextureImage_Dolphin(pkt, fmt, siz, h, w, img) \
{{ \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(1, 18, 1) | \
        _SHIFTL((h/4)-1, 10, 8) | _SHIFTL((w-1), 0, 10); \
    _GBI_SET_W1(_gfx, img); \
}}

#define gDPSetTile_Dolphin(pkt, d_fmt, tile, tlut_name, wrap_s, wrap_t, shift_s, shift_t) \
{{ \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTILE_DOLPHIN, 24, 8) | _SHIFTL(d_fmt, 20, 4) | _SHIFTL(tile, 16, 3) | \
        _SHIFTL(tlut_name, 12, 4) | _SHIFTL(wrap_s, 10, 2) | _SHIFTL(wrap_t, 8, 2) | \
        _SHIFTL(shift_s, 4, 4) | _SHIFTL(shift_t, 0, 4); \
    /*_gfx->words.w1 = 0;*/ /* bug? they don't set the second word */ \
}}

#define gDPSetTileSize_Dolphin(pkt, tile, s, t, width, height)		\
do { \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(s, 10, 14) | _SHIFTL(width - 1, 0, 10); \
    _gfx->words.w1 = _SHIFTL(1, 31, 1) | _SHIFTL(tile, 24, 3) | _SHIFTL(t, 10, 14) | _SHIFTL(height - 1, 0, 10); \
} while (0)

#define gsDPSetTileSize_Dolphin(tile, s, t, width, height)		\
{{									\
	_SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(s, 10, 14) | _SHIFTL(width - 1, 0, 10),	\
	_SHIFTL(1, 31, 1) | _SHIFTL(tile, 24, 3) | _SHIFTL(t, 10, 14) | _SHIFTL(height - 1, 0, 10)\
}}

#define G_DOLPHIN_TLUT_DEFAULT_MODE 15 // used almost always? CI palettes are forced to GX_TF_RGB5A3
#define gsDPLoadTextureBlock_4b_Dolphin(timg, fmt, w, h, pal, ws, wt, ss, st) \
    gsDPSetTextureImage_Dolphin(fmt, G_IM_SIZ_4b, w, h, timg), \
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, pal, ws, wt, ss, st)

#define gDPLoadTextureBlock_4b_Dolphin(pkt, timg, fmt, w, h, pal, ws, wt, ss, st) \
do { \
    gDPSetTextureImage_Dolphin(pkt, fmt, G_IM_SIZ_4b, w, h, timg); \
    gDPSetTile_Dolphin(pkt, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, pal, ws, wt, ss, st); \
} while (0)

#define gDPLoadTextureBlock_8b_Dolphin(pkt, timg, fmt, w, h, pal, ws, wt, ss, st) \
do { \
    gDPSetTextureImage_Dolphin(pkt, fmt, G_IM_SIZ_8b, w, h, timg); \
    gDPSetTile_Dolphin(pkt, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, pal, ws, wt, ss, st); \
} while (0)

#define gDPLoadTextureTile_4b_Dolphin(pkt, timg, fmt, w, h) \
do { \
    gDPSetTextureImage_Dolphin(pkt, fmt, G_IM_SIZ_4b, h, w, timg); \
    gDPSetTile_Dolphin(pkt, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, 0, 0, 0, 0) \
} while (0);

#define gsDPLoadMultiBlock_4b_Dolphin(timg, tile, fmt, w, h, pal, ws, wt, ss, st) \
    gsDPSetTextureImage_Dolphin(fmt, G_IM_SIZ_4b, w, h, timg), \
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, tile, pal, ws, wt, ss, st)

#define gsSPNTriangles_Independ(n) \
{{ \
    _SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7), 0 \
}}

/* 5 bits per vertex id (32) */
#define gsSPNTriangleData1(v0, v1, v2, flag) (_SHIFTL(v2, 10, 5) | _SHIFTL(v1, 5, 5) | _SHIFTL(v0, 0, 5))

/* 7 bits per vertex id (128) */
#define gsSPNTriangleData2(v0, v1, v2, flag) \
{{ \
    (unsigned long long)(_SHIFTL(v2, 14, 7) | _SHIFTL(v1, 7, 7) | _SHIFTL(v0, 0, 7)) \
}}

#define G_VTX_MODE_5bit 0
#define G_VTX_MODE_7bit 1

#define gSPNTriangles_5b(pkt, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
{{ \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)((gsSPNTriangleData1(v9, v10, v11) << 17) | (gsSPNTriangleData1(v6, v7, v8) << 2) | ((gsSPNTriangleData1(v3, v4, v5) >> 13) & 3)); \
  _g->words.w1 = (u32)(((gsSPNTriangleData1(v3, v4, v5) & 7) << 19) | (gsSPNTriangleData1(v0, v1, v2) << 4) | G_VTX_MODE_5bit); \
}}

#define gSPNTrianglesInit_5b(pkt, n, v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 2, 13), 0, 2)); \
  _g->words.w1 = (u32)(_SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1)); \
}}

#define gsSPNTriangles_5b(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
{{ \
    _SHIFTL(gsSPNTriangleData1(v9, v10, v11, 0), 17, 15) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 13, 2), 0, 2), \
    _SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1) \
}}

#define gsSPNTrianglesInit_5b(n, v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    _SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 13, 2), 0, 2), \
    _SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1) \
}}

#define gsSPNTriangles_7b(v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    (unsigned long long)((gsSPNTriangleData2(v6, v7, v8) << 43) | (gsSPNTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gsSPNTrianglesInit_7b(n, v0, v1, v2, v3, v4, v5) \
{{ \
    (unsigned long long)((((unsigned long long)gsSPNTriangles_Independ(n)) << 32) | (gsSPNTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gsSPNTriangles(n, v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    _SHIFTL(G_TRIN, 24, 8) | _SHIFTL(n-1, 17, 7) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 13, 2), 0, 2), \
    _SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1) \
}}

#define gDPSetTexEdgeAlpha(pkt, alpha) \
do { \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_SETTEXEDGEALPHA, 24, 8)); \
  _g->words.w1 = (u32)(_SHIFTL(alpha, 0, 8)); \
} while(0)

#define gsDPSetTexEdgeAlpha(alpha) \
{{ \
  (u32)(_SHIFTL(G_SETTEXEDGEALPHA, 24, 8)), \
  (u32)(_SHIFTL(alpha, 0, 8)) \
}}

#define gDPSetTextureAdjustMode(pkt, mode) \
do { \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_SPECIAL_1, 24, 8) | _SHIFTL(G_SPECIAL_TA_MODE, 16, 8) | _SHIFTL(mode, 0, 16)); \
  _g->words.w1 = (u32)0; \
} while(0)

#define gsDPSetTextureAdjustMode(mode) \
{{ \
  (u32)(_SHIFTL(G_SPECIAL_1, 24, 8) | _SHIFTL(G_SPECIAL_TA_MODE, 16, 8) | _SHIFTL(mode, 0, 16)), \
  (u32)0 \
}}

//Helpful macro for defining values of a Matrix

#define qs1616(e) ((s32)((e) * 0x00010000))

#define IPART(x) ((qs1616(x) >> 16) & 0xFFFF)
#define FPART(x) (qs1616(x) & 0xFFFF)

#define gdSPDefMtx(     \
        xx, yx, zx, wx, \
        xy, yy, zy, wy, \
        xz, yz, zz, wz, \
        xw, yw, zw, ww) \
    {{                                  \
        (IPART(xx) << 0x10) | IPART(xy),  \
        (IPART(xz) << 0x10) | IPART(xw),  \
        (IPART(yx) << 0x10) | IPART(yy),  \
        (IPART(yz) << 0x10) | IPART(yw),  \
        (IPART(zx) << 0x10) | IPART(zy),  \
        (IPART(zz) << 0x10) | IPART(zw),  \
        (IPART(wx) << 0x10) | IPART(wy),  \
        (IPART(wz) << 0x10) | IPART(ww),  \
        (FPART(xx) << 0x10) | FPART(xy),  \
        (FPART(xz) << 0x10) | FPART(xw),  \
        (FPART(yx) << 0x10) | FPART(yy),  \
        (FPART(yz) << 0x10) | FPART(yw),  \
        (FPART(zx) << 0x10) | FPART(zy),  \
        (FPART(zz) << 0x10) | FPART(zw),  \
        (FPART(wx) << 0x10) | FPART(wy),  \
        (FPART(wz) << 0x10) | FPART(ww),  \
    }}


#define G_DL_GXDL 2

/* Macro for calling GC formatted display lists from N64 lists */
#define gGXCallDisplayList(pkt, dl, nbytes) gDma1p(pkt, G_DL, dl, nbytes, G_DL_GXDL)
#define gsGXCallDisplayList(dl, nbytes) gsDma1p(pkt, G_DL, dl, nbytes, G_DL_GXDL)

// clang-format on

#ifdef __cplusplus
}
#endif

#endif /* __GBI_EXTENSIONS_H__ */
