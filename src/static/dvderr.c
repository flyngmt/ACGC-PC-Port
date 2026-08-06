#include "dvderr.h"

#include "libultra/libultra.h"
#include "dolphin/dvd.h"
#include "libforest/gbi_extensions.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "jsyswrap.h"
#include "dolphin/vi.h"
#include "dolphin/gx.h"

/* imports */
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_1_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_1_tex[] = {
#include "assets/dvd_keikoku_moji1_1_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_2_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_2_tex[] = {
#include "assets/dvd_keikoku_moji1_2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_3_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_3_tex[] = {
#include "assets/dvd_keikoku_moji1_3_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_4_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji1_4_tex[] = {
#include "assets/dvd_keikoku_moji1_4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w1_tex[] = {
#include "assets/ctl_att_w1_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w2_tex[] = {
#include "assets/ctl_att_w2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w3_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w3_tex[] = {
#include "assets/ctl_att_w3_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w4_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w4_tex[] = {
#include "assets/ctl_att_w4_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w5_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w5_tex[] = {
#include "assets/ctl_att_w5_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w6_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_att_w6_tex[] = {
#include "assets/ctl_att_w6_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx dvd_keikoku1_v[0x3C0 / sizeof(Vtx)];
#else
static Vtx dvd_keikoku1_v[] = {
#include "assets/dvd_keikoku1_v.inc"
};
#endif
static Gfx keikoku1_dvd_att_moji_model[] = {
  /* init */
  gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 235, 235, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
  
  /* draw 1st text */
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji1_4_tex, G_IM_FMT_I, 192, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku1_v[0], 16, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji1_3_tex, G_IM_FMT_I, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji1_2_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji1_1_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    12, 13, 14, // tri0
    13, 15, 14, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

static Gfx keikoku1_dvd_att_winT_model[] = {
  gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 100, 0, 170, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku1_v[16], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),

  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),

  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),

  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),

  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&dvd_keikoku1_v[44], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),

  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),

  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_tex[0x280];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_tex[] = {
#include "assets/dvd_keikoku_moji2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_2_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_2_tex[] = {
#include "assets/dvd_keikoku_moji2_2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_3_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji2_3_tex[] = {
#include "assets/dvd_keikoku_moji2_3_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx dvd_keikoku2_v[0x380 / sizeof(Vtx)];
#else
static Vtx dvd_keikoku2_v[] = {
#include "assets/dvd_keikoku2_v.inc"
};
#endif
static Gfx keikoku2_dvd_att_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 235, 235, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji2_3_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku2_v[0], 12, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji2_2_tex, G_IM_FMT_I, 192, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji2_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

static Gfx keikoku2_dvd_att_winT_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 100, 0, 170, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku2_v[12], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&dvd_keikoku2_v[40], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji4_tex[0x280];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji4_tex[] = {
#include "assets/dvd_keikoku_moji4_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_1_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_1_tex[] = {
#include "assets/dvd_keikoku_moji3_1_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_2_tex[0x280];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_2_tex[] = {
#include "assets/dvd_keikoku_moji3_2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_3_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji3_3_tex[] = {
#include "assets/dvd_keikoku_moji3_3_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx dvd_keikoku3_v[0x440 / sizeof(Vtx)];
#else
static Vtx dvd_keikoku3_v[] = {
#include "assets/dvd_keikoku3_v.inc"
};
#endif
static Gfx keikoku3_dvd_att_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 235, 235, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji3_3_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku3_v[0], 24, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji3_2_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji3_1_tex, G_IM_FMT_I, 192, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    13, 15, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    19, 16, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji4_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    20, 21, 22, // tri0
    21, 23, 22, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

static Gfx keikoku3_dvd_att_winT_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 100, 0, 170, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku3_v[24], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&dvd_keikoku3_v[52], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji5_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji5_tex[] = {
#include "assets/dvd_keikoku_moji5_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_2_tex[0x480];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_2_tex[] = {
#include "assets/dvd_keikoku_moji6_2_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_3_tex[0x280];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_3_tex[] = {
#include "assets/dvd_keikoku_moji6_3_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_tex[] = {
#include "assets/dvd_keikoku_moji6_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_1_tex[0x580];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_1_tex[] = {
#include "assets/dvd_keikoku_moji6_1_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_new1_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_new1_tex[] = {
#include "assets/dvd_keikoku_moji6_new1_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_new2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji6_new2_tex[] = {
#include "assets/dvd_keikoku_moji6_new2_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx dvd_keikoku4_v[0x480 / sizeof(Vtx)];
#else
static Vtx dvd_keikoku4_v[] = {
#include "assets/dvd_keikoku4_v.inc"
};
#endif
static Gfx keikoku4_dvd_att_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 235, 235, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_new2_tex, G_IM_FMT_I, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku4_v[0], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_new1_tex, G_IM_FMT_I, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_1_tex, G_IM_FMT_I, 176, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_tex, G_IM_FMT_I, 128, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    12, 13, 14, // tri0
    13, 15, 14, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_3_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    16, 17, 18, // tri0
    17, 19, 18, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji6_2_tex, G_IM_FMT_I, 144, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    20, 21, 22, // tri0
    21, 23, 22, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji5_tex, G_IM_FMT_I, 96, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    24, 25, 26, // tri0
    25, 27, 26, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

static Gfx keikoku4_dvd_att_winT_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 100, 0, 170, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku4_v[28], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&dvd_keikoku4_v[56], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji7_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji7_tex[] = {
#include "assets/dvd_keikoku_moji7_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji8_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji8_tex[] = {
#include "assets/dvd_keikoku_moji8_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji10_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji10_tex[] = {
#include "assets/dvd_keikoku_moji10_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji11_tex[0x480];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji11_tex[] = {
#include "assets/dvd_keikoku_moji11_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji12_tex[0x280];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji12_tex[] = {
#include "assets/dvd_keikoku_moji12_tex.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji9_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) static u8 dvd_keikoku_moji9_tex[] = {
#include "assets/dvd_keikoku_moji9_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx dvd_keikoku5_v[0x440 / sizeof(Vtx)];
#else
static Vtx dvd_keikoku5_v[] = {
#include "assets/dvd_keikoku5_v.inc"
};
#endif
static Gfx keikoku5_dvd_att_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 235, 235, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji9_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku5_v[0], 24, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji12_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji11_tex, G_IM_FMT_I, 144, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji10_tex, G_IM_FMT_I, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    12, 13, 14, // tri0
    13, 15, 14, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji8_tex, G_IM_FMT_I, 128, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    16, 17, 18, // tri0
    17, 19, 18, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(dvd_keikoku_moji7_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    20, 21, 22, // tri0
    21, 23, 22, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

static Gfx keikoku5_dvd_att_winT_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 100, 0, 170, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&dvd_keikoku5_v[24], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&dvd_keikoku5_v[52], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(ctl_att_w1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};

static dvderr_work Dvderr_work;
static dvderr_work* const this = &Dvderr_work;

static Vp Dvderr_viewport = {{
  { 1280, 960, 511, 0 },
  { 1280, 960, 511, 0 }
}};

static Gfx Dvderr_initial_dl[] = {
  gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
  gsDPSetFillColor(GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1)), /* fill color to black */
  gsDPFillRectangle(0, 0, 639, 479), /* fill in rectangle which is the size of the screen */
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480), /* set scissor to screen size, TODO: should probably be defintions */
  gsSPClipRatio(FRUSTRATIO_2), /* 2:1 clipping ratio */
  gsSPViewport(&Dvderr_viewport),
  gsSPMatrix(&Dvderr_work.ortho, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION),
  gsSPMatrix(&Dvderr_work.projection, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION),
  gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
  gsSPMatrix(&Dvderr_work.modelview, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW),
  gsSPEndDisplayList(),
};


static void dvderr_exec_dl(Gfx* dl) {
  emu64_init();
  emu64_taskstart(dl);
  emu64_cleanup();
}

static int dvderr_check_drive() {
  int err = DVDERR_NONE;

  if (osShutdown == FALSE) {
    switch (DVDGetDriveStatus()) {
      case DVD_STATE_FATAL_ERROR:
        err = DVDERR_FATAL;
        break;

      case DVD_STATE_BUSY:
        err = this->next_error;
        break;

      case DVD_STATE_NO_DISK:
        err = DVDERR_NO_DISK;
        break;

      case DVD_STATE_COVER_OPEN:
        err = DVDERR_COVER_OPEN;
        break;

      case DVD_STATE_WRONG_DISK:
        err = DVDERR_WRONG_DISK;
        break;

      case DVD_STATE_RETRY:
        err = DVDERR_RETRY;
        break;
    }
  }

  return err;
}

static void dvderr_draw_CoverOpen() {
  gSPDisplayList(this->gfx_p++, keikoku1_dvd_att_winT_model);
  gSPDisplayList(this->gfx_p++, keikoku1_dvd_att_moji_model);
}

static void dvderr_draw_NoDisk() {
  gSPDisplayList(this->gfx_p++, keikoku2_dvd_att_winT_model);
  gSPDisplayList(this->gfx_p++, keikoku2_dvd_att_moji_model);
}

static void dvderr_draw_WrongDisk() {
  gSPDisplayList(this->gfx_p++, keikoku3_dvd_att_winT_model);
  gSPDisplayList(this->gfx_p++, keikoku3_dvd_att_moji_model);
}

static void dvderr_draw_Retry() {
  gSPDisplayList(this->gfx_p++, keikoku4_dvd_att_winT_model);
  gSPDisplayList(this->gfx_p++, keikoku4_dvd_att_moji_model);
}

static void dvderr_draw_Fatal() {
  gSPDisplayList(this->gfx_p++, keikoku5_dvd_att_winT_model);
  gSPDisplayList(this->gfx_p++, keikoku5_dvd_att_moji_model);
}

static void dvderr_mtx_set() {
  guScale(&this->modelview, this->scale, this->scale, 1.0f);
}

#define DVDERR_MOVE_SPEED (1.0f/18.0f)

static void dvderr_move_up();
static void dvderr_move_down();
static void dvderr_move_wait();

static void dvderr_move_up() {
  this->scale += DVDERR_MOVE_SPEED;
  if (this->scale >= 1.0f) {
    this->scale = 1.0f;
  }

  if (this->next_error != this->now_error) {
    this->draw_proc = &dvderr_move_down;
  }
}

static void dvderr_move_down() {
  this->scale -= DVDERR_MOVE_SPEED;
  if (this->scale <= 0.0f) {
    this->scale = 0.0f;
    this->now_error = this->next_error;
    this->draw_proc = &dvderr_move_wait;
  }
}

static void dvderr_move_wait() {
  if (this->next_error == DVDERR_NONE) {
    return;
  }

  this->now_error = this->next_error;
  this->draw_proc = &dvderr_move_up;
}

static void dvderr_move() {
  (*this->draw_proc)();
}

extern int dvderr_draw() {
  static const DVDERR_DRAW_PROC draw_proc[DVDERR_NUM] = {
    &dvderr_draw_CoverOpen,
    &dvderr_draw_NoDisk,
    &dvderr_draw_WrongDisk,
    &dvderr_draw_Retry,
    &dvderr_draw_Fatal
  };

  this->next_error = dvderr_check_drive();
  dvderr_move();

  if (this->now_error >= DVDERR_COVER_OPEN) {
    /* Under Aurora this function is called only from the main graph loop. The
     * console boot menu's secondary rendering thread is disabled at startup. */
    dvderr_mtx_set();
    JW_BeginFrame();
    this->gfx_p = this->gfx;
    gSPDisplayList(this->gfx_p++, Dvderr_initial_dl);

    if (draw_proc[this->now_error] != NULL) {
      (*draw_proc[this->now_error])();
    }

    gDPFullSync(this->gfx_p++);
    gSPEndDisplayList(this->gfx_p++);

    dvderr_exec_dl(this->gfx);
    JW_EndFrame();
    VISetBlack(FALSE);
    return TRUE;
  }
  else {
    return FALSE;
  }
}

extern void dvderr_init() {
  bzero(this, sizeof(dvderr_work));
  this->draw_proc = &dvderr_move_wait;
  this->now_error = DVDERR_NONE;
  this->next_error = DVDERR_NONE;
  guOrtho(&this->ortho, -160.0f, 160.0f, -120.0f, 120.0f, -800.0f, 800.0f, 1.0f); /* TODO: N64 screen size macros (float) */
  guLookAt(&this->projection, 0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_static_dvderr_c(void) {
    pc_load_asset("assets/dvd_keikoku_moji1_1_tex.bin", dvd_keikoku_moji1_1_tex, 0x500, 0xADA60, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji1_2_tex.bin", dvd_keikoku_moji1_2_tex, 0x500, 0xADF60, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji1_3_tex.bin", dvd_keikoku_moji1_3_tex, 0x200, 0xAE460, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji1_4_tex.bin", dvd_keikoku_moji1_4_tex, 0x600, 0xAE660, 1, 0);
    pc_load_asset("assets/ctl_att_w1_tex.bin", ctl_att_w1_tex, 0x400, 0x6A6C80, 0, 0);
    pc_load_asset("assets/ctl_att_w2_tex.bin", ctl_att_w2_tex, 0x400, 0x6A7080, 0, 0);
    pc_load_asset("assets/ctl_att_w3_tex.bin", ctl_att_w3_tex, 0x400, 0x6A7480, 0, 0);
    pc_load_asset("assets/ctl_att_w4_tex.bin", ctl_att_w4_tex, 0x400, 0x6A7880, 0, 0);
    pc_load_asset("assets/ctl_att_w5_tex.bin", ctl_att_w5_tex, 0x400, 0x6A7C80, 0, 0);
    pc_load_asset("assets/ctl_att_w6_tex.bin", ctl_att_w6_tex, 0x80, 0x6A8080, 0, 0);
    pc_load_asset("assets/dvd_keikoku1_v.bin", dvd_keikoku1_v, 0x3C0, 0xB00E0, 1, 2);
    pc_load_asset("assets/dvd_keikoku_moji2_tex.bin", dvd_keikoku_moji2_tex, 0x280, 0xB0640, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji2_2_tex.bin", dvd_keikoku_moji2_2_tex, 0x600, 0xB08C0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji2_3_tex.bin", dvd_keikoku_moji2_3_tex, 0x80, 0xB0EC0, 1, 0);
    pc_load_asset("assets/dvd_keikoku2_v.bin", dvd_keikoku2_v, 0x380, 0xB0F40, 1, 2);
    pc_load_asset("assets/dvd_keikoku_moji4_tex.bin", dvd_keikoku_moji4_tex, 0x280, 0xB1440, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji3_1_tex.bin", dvd_keikoku_moji3_1_tex, 0x600, 0xB16C0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji3_2_tex.bin", dvd_keikoku_moji3_2_tex, 0x280, 0xB1CC0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji3_3_tex.bin", dvd_keikoku_moji3_3_tex, 0x80, 0xB1F40, 1, 0);
    pc_load_asset("assets/dvd_keikoku3_v.bin", dvd_keikoku3_v, 0x440, 0xB1FC0, 1, 2);
    pc_load_asset("assets/dvd_keikoku_moji5_tex.bin", dvd_keikoku_moji5_tex, 0x300, 0xB25A0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_2_tex.bin", dvd_keikoku_moji6_2_tex, 0x480, 0xB28A0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_3_tex.bin", dvd_keikoku_moji6_3_tex, 0x280, 0xB2D20, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_tex.bin", dvd_keikoku_moji6_tex, 0x400, 0xB2FA0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_1_tex.bin", dvd_keikoku_moji6_1_tex, 0x580, 0xB33A0, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_new1_tex.bin", dvd_keikoku_moji6_new1_tex, 0x200, 0xB3920, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji6_new2_tex.bin", dvd_keikoku_moji6_new2_tex, 0x200, 0xB3B20, 1, 0);
    pc_load_asset("assets/dvd_keikoku4_v.bin", dvd_keikoku4_v, 0x480, 0xB3D20, 1, 2);
    pc_load_asset("assets/dvd_keikoku_moji7_tex.bin", dvd_keikoku_moji7_tex, 0x500, 0xB4380, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji8_tex.bin", dvd_keikoku_moji8_tex, 0x400, 0xB4880, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji10_tex.bin", dvd_keikoku_moji10_tex, 0x200, 0xB4C80, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji11_tex.bin", dvd_keikoku_moji11_tex, 0x480, 0xB4E80, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji12_tex.bin", dvd_keikoku_moji12_tex, 0x280, 0xB5300, 1, 0);
    pc_load_asset("assets/dvd_keikoku_moji9_tex.bin", dvd_keikoku_moji9_tex, 0x500, 0xB5580, 1, 0);
    pc_load_asset("assets/dvd_keikoku5_v.bin", dvd_keikoku5_v, 0x440, 0xB5A80, 1, 2);
}
#endif
