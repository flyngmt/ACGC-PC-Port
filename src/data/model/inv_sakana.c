#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 inv_mushi_w5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 inv_mushi_w5_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_sakana_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_sakana_nuno_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w1_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w2_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w3_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w4_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w6_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 inv_mushi_w7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 inv_mushi_w7_tex_rgb_ci4_pal[] = {
#include "assets/inv_sakana/inv_mushi_w7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400];
#else
static u8 inv_mwin_nwaku_tex[] = {
#include "assets/inv_sakana/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_shirushi2_tex[0x200];
#else
u8 inv_mwin_shirushi2_tex[] = {
#include "assets/inv_mwin_shirushi2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_shirushi_tex[0x400];
#else
static u8 inv_mwin_shirushi_tex[] = {
#include "assets/inv_sakana/inv_mwin_shirushi_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_aw1_tex[0x200];
#else
static u8 inv_mushi_aw1_tex[] = {
#include "assets/inv_sakana/inv_mushi_aw1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_aw2_tex[0x400];
#else
static u8 inv_mushi_aw2_tex[] = {
#include "assets/inv_sakana/inv_mushi_aw2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_aw3_tex[0x400];
#else
static u8 inv_mushi_aw3_tex[] = {
#include "assets/inv_sakana/inv_mushi_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_aw4_tex[0x200];
#else
static u8 inv_mushi_aw4_tex[] = {
#include "assets/inv_sakana/inv_mushi_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_sakana_waku1_tex[0x800];
#else
u8 inv_sakana_waku1_tex[] = {
#include "assets/inv_sakana_waku1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_aw7_tex[0x400];
#else
static u8 inv_mushi_aw7_tex[] = {
#include "assets/inv_sakana/inv_mushi_aw7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_sakana_moji_tex[0x200];
#else
u8 inv_sakana_moji_tex[] = {
#include "assets/inv_sakana_moji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_sakana_waku2_tex[0x800];
#else
u8 inv_sakana_waku2_tex[] = {
#include "assets/inv_sakana_waku2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_aw5_tex[0x80];
#else
static u8 inv_mwin_aw5_tex[] = {
#include "assets/inv_sakana/inv_mwin_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w5_tex_rgb_ci4[0x80];
#else
static u8 inv_mushi_w5_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_sakana_nuno_tex_rgb_ci4[0x200];
#else
u8 inv_sakana_nuno_tex_rgb_ci4[] = {
#include "assets/inv_sakana_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w1_tex_rgb_ci4[0x200];
#else
static u8 inv_mushi_w1_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w2_tex_rgb_ci4[0x400];
#else
static u8 inv_mushi_w2_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w3_tex_rgb_ci4[0x400];
#else
static u8 inv_mushi_w3_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w4_tex_rgb_ci4[0x200];
#else
static u8 inv_mushi_w4_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w6_tex_rgb_ci4[0x400];
#else
static u8 inv_mushi_w6_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mushi_w7_tex_rgb_ci4[0x400];
#else
static u8 inv_mushi_w7_tex_rgb_ci4[] = {
#include "assets/inv_sakana/inv_mushi_w7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx inv_sakana_v[0x940 / sizeof(Vtx)];
#else
Vtx inv_sakana_v[] = {
#include "assets/inv_sakana_v.inc"
};
#endif

Gfx inv_sakana_w14_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, inv_mushi_w5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(inv_sakana_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_moji_model[] = {
    gsDPSetPrimColor(0, 255, 215, 215, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, inv_sakana_moji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_sakana_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&inv_sakana_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_w13T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[56], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_waku2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 50, 50, 235, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mwin_shirushi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_ueT_model[] = {
    gsDPSetPrimColor(0, 255, 185, 205, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_aw5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[64], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mushi_aw7_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 7, 8, 9),
    gsSPNTriangles_5b(7, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mushi_aw4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 12, 14, 15, 16),
    gsSPNTriangles_5b(17, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, inv_mushi_aw3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[82], 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mushi_aw2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 20, 19, 16),
    gsSPNTriangles_5b(20, 21, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mushi_aw1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[104], 25, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 3, 4, 5),
    gsSPNTriangles_5b(3, 6, 4, 7, 8, 9, 9, 10, 7, 11, 12, 13),
    gsSPNTriangles_5b(13, 14, 11, 15, 16, 17, 16, 18, 17, 19, 20, 21),
    gsSPNTriangles_5b(19, 16, 20, 22, 23, 24, 23, 0, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_ue2T_model[] = {
    gsDPSetPrimColor(0, 255, 185, 205, 255, 255),
    gsDPSetEnvColor(80, 165, 130, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[129], 7, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_daimeiT_model[] = {
    gsDPSetPrimColor(0, 255, 40, 40, 185, 255),
    gsDPSetEnvColor(100, 100, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_sakana_waku2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[136], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_sakana_waku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_shirushiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 215, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mwin_shirushi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_sakana_v[144], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_scroll_mode[] = {
    gsDPPipeSync(),
    gsDPLoadTLUT_Dolphin(14, 16, 1, inv_sakana_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_sakana_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_model[] = {
    gsDPPipeSync(),
    gsSPDisplayList(inv_sakana_w1T_model),
    gsSPDisplayList(inv_sakana_w2T_model),
    gsSPDisplayList(inv_sakana_w3T_model),
    gsSPDisplayList(inv_sakana_w4T_model),
    gsSPDisplayList(inv_sakana_w5T_model),
    gsSPDisplayList(inv_sakana_w6T_model),
    gsSPDisplayList(inv_sakana_w7T_model),
    gsSPDisplayList(inv_sakana_w8T_model),
    gsSPDisplayList(inv_sakana_w9T_model),
    gsSPDisplayList(inv_sakana_w10T_model),
    gsSPDisplayList(inv_sakana_w11T_model),
    gsSPDisplayList(inv_sakana_w12T_model),
    gsSPDisplayList(inv_sakana_w13T_model),
    gsSPDisplayList(inv_sakana_w14_model),
    gsSPDisplayList(inv_sakana_waku2T_model),
    gsSPDisplayList(inv_sakana_ueT_model),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPDisplayList(inv_sakana_ue2T_model),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(inv_sakana_daimeiT_model),
    gsSPDisplayList(inv_sakana_shirushiT_model),
    gsSPDisplayList(inv_sakana_moji_model),
    gsSPEndDisplayList(),
};

Gfx inv_sakana_part_model[] = {
    gsSPDisplayList(inv_sakana_waku2T_model),
    gsSPDisplayList(inv_sakana_shirushiT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_inv_sakana_c(void) {
    pc_load_asset("assets/inv_sakana/inv_mushi_w5_tex_rgb_ci4_pal.bin", inv_mushi_w5_tex_rgb_ci4_pal, 0x20, 0x71C0C0, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w1_tex_rgb_ci4_pal.bin", inv_mushi_w1_tex_rgb_ci4_pal, 0x20, 0x71C100, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w2_tex_rgb_ci4_pal.bin", inv_mushi_w2_tex_rgb_ci4_pal, 0x20, 0x71C120, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w3_tex_rgb_ci4_pal.bin", inv_mushi_w3_tex_rgb_ci4_pal, 0x20, 0x71C140, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w4_tex_rgb_ci4_pal.bin", inv_mushi_w4_tex_rgb_ci4_pal, 0x20, 0x71C160, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w6_tex_rgb_ci4_pal.bin", inv_mushi_w6_tex_rgb_ci4_pal, 0x20, 0x71C180, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mushi_w7_tex_rgb_ci4_pal.bin", inv_mushi_w7_tex_rgb_ci4_pal, 0x20, 0x71C1A0, 0, 1);
    pc_load_asset("assets/inv_sakana/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x7982E0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mwin_shirushi_tex.bin", inv_mwin_shirushi_tex, 0x400, 0x71C7C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_aw1_tex.bin", inv_mushi_aw1_tex, 0x200, 0x71CBC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_aw2_tex.bin", inv_mushi_aw2_tex, 0x400, 0x71CDC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_aw3_tex.bin", inv_mushi_aw3_tex, 0x400, 0x71D1C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_aw4_tex.bin", inv_mushi_aw4_tex, 0x200, 0x71D5C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_aw7_tex.bin", inv_mushi_aw7_tex, 0x400, 0x71DFC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mwin_aw5_tex.bin", inv_mwin_aw5_tex, 0x80, 0x71EDC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w5_tex_rgb_ci4.bin", inv_mushi_w5_tex_rgb_ci4, 0x80, 0x71EE40, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w1_tex_rgb_ci4.bin", inv_mushi_w1_tex_rgb_ci4, 0x200, 0x71F0C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w2_tex_rgb_ci4.bin", inv_mushi_w2_tex_rgb_ci4, 0x400, 0x71F2C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w3_tex_rgb_ci4.bin", inv_mushi_w3_tex_rgb_ci4, 0x400, 0x71F6C0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w4_tex_rgb_ci4.bin", inv_mushi_w4_tex_rgb_ci4, 0x200, 0x71FAC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w6_tex_rgb_ci4.bin", inv_mushi_w6_tex_rgb_ci4, 0x400, 0x71FCC0, 0, 0);
    pc_load_asset("assets/inv_sakana/inv_mushi_w7_tex_rgb_ci4.bin", inv_mushi_w7_tex_rgb_ci4, 0x400, 0x7200C0, 0, 0);
}
#endif
