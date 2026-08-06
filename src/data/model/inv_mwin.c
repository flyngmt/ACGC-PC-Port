#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_w1_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_w2_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_w3_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_w4_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_w6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_w6_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_w6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400];
#else
static u8 inv_mwin_nwaku_tex[] = {
#include "assets/inv_mwin/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_aw6_tex[0x400];
#else
u8 inv_mwin_aw6_tex[] = {
#include "assets/inv_mwin_aw6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_shirushi4_tex[0x200];
#else
u8 inv_mwin_shirushi4_tex[] = {
#include "assets/inv_mwin_shirushi4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_sen_tex[0x80];
#else
u8 inv_mwin_sen_tex[] = {
#include "assets/inv_mwin_sen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_sen2_tex[0x80];
#else
u8 inv_mwin_sen2_tex[] = {
#include "assets/inv_mwin_sen2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_suujiwaku1_tex[0x200];
#else
u8 inv_mwin_suujiwaku1_tex[] = {
#include "assets/inv_mwin_suujiwaku1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_original_shirushi_tex[0x200];
#else
u8 inv_original_shirushi_tex[] = {
#include "assets/inv_original_shirushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_suujiwaku2_tex[0x200];
#else
u8 inv_mwin_suujiwaku2_tex[] = {
#include "assets/inv_mwin_suujiwaku2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_original_shirushi3_tex[0x800];
#else
u8 inv_original_shirushi3_tex[] = {
#include "assets/inv_original_shirushi3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_3Dma_tex[0x800];
#else
static u8 inv_mwin_3Dma_tex[] = {
#include "assets/inv_mwin/inv_mwin_3Dma_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 originl[0x200];
#else
u8 originl[] = {
#include "assets/originl.inc"
};
#endif

#ifdef TARGET_PC
u8 original2[0x400];
#else
u8 original2[] = {
#include "assets/original2.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_aw3_tex[0x400];
#else
u8 inv_mwin_aw3_tex[] = {
#include "assets/inv_mwin_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_aw4_tex[0x200];
#else
u8 inv_mwin_aw4_tex[] = {
#include "assets/inv_mwin_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_aw5_tex[0x80];
#else
static u8 inv_mwin_aw5_tex[] = {
#include "assets/inv_mwin/inv_mwin_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_items_tex[0x200];
#else
u8 inv_mwin_items_tex[] = {
#include "assets/inv_mwin_items_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_letters_tex[0x200];
#else
u8 inv_mwin_letters_tex[] = {
#include "assets/inv_mwin_letters_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_bells_tex[0x200];
#else
u8 inv_mwin_bells_tex[] = {
#include "assets/inv_mwin_bells_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w5_tex_rgb_ci4[0x80];
#else
u8 inv_mwin_w5_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w1_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_w1_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w2_tex_rgb_ci4[0x400];
#else
u8 inv_mwin_w2_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w3_tex_rgb_ci4[0x400];
#else
u8 inv_mwin_w3_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w4_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_w4_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_w6_tex_rgb_ci4[0x400];
#else
u8 inv_mwin_w6_tex_rgb_ci4[] = {
#include "assets/inv_mwin_w6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx inv_mwin_v[0x1280 / sizeof(Vtx)];
#else
Vtx inv_mwin_v[] = {
#include "assets/inv_mwin_v.inc"
};
#endif

Gfx inv_mwin_w13_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, inv_mwin_w5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(inv_mwin_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_1c_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, original2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[4], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, originl),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(12, 7, 8, 9, 8, 10, 9, 11, 12, 13),
    gsSPNTriangles_5b(12, 14, 13, 15, 16, 17, 17, 18, 15, 19, 20, 21),
    gsSPNTriangles_5b(21, 22, 19, 23, 24, 25, 23, 22, 24, 26, 27, 21),
    gsSPNTriangles_5b(27, 24, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_kuni_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 35, 160, 255, 110),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_sen2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[32], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_sen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_kuni2_model[] = {
    gsDPSetPrimColor(0, 255, 80, 140, 255, 120),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_sen2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[44], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_sen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_item_model[] = {
    gsDPSetPrimColor(0, 255, 120, 120, 225, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, inv_mwin_items_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[56], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_tegami_model[] = {
    gsDPSetPrimColor(0, 255, 195, 80, 80, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, inv_mwin_letters_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_okane_model[] = {
    gsDPSetPrimColor(0, 255, 70, 160, 190, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, inv_mwin_bells_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_shirushi3_model[] = {
    gsDPSetPrimColor(0, 255, 75, 50, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_original_shirushi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mwin_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mwin_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&inv_mwin_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mwin_w6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mwin_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mwin_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[108], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[112], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_w12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mwin_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[116], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_shirushi2T_model[] = {
    gsDPSetPrimColor(0, 255, 255, 205, 70, 255),
    gsDPSetEnvColor(165, 145, 50, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, inv_original_shirushi3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[120], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_1cT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_aw5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[124], 30, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 2, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 0, 8, 7, 9, 0, 1, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 10, 12, 3, 12, 4, 3, 13, 11, 14),
    gsSPNTriangles_5b(13, 15, 11, 16, 17, 7, 16, 18, 17, 19, 20, 5),
    gsSPNTriangles_5b(19, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mwin_aw4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 22, 23, 24, 24, 25, 22, 26, 27, 28),
    gsSPNTriangles_5b(27, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, inv_mwin_aw3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[154], 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mwin_aw6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 16, 20, 19),
    gsSPNTriangles_5b(20, 21, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_1bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[176], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_2bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[180], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_3bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[184], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_4bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[188], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_5bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[192], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_6bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[196], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_7bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[200], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_8bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[204], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_9bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[208], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_10bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[212], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_11bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[216], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_12bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[220], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_13bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[224], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_14bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[228], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_15bT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[232], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_1aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[236], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_2aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[240], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_3aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[244], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_4aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[248], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_5aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[252], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_6aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[256], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_7aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[260], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_8aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[264], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_9aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[268], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_10aT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[272], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_3DmT_model[] = {
    gsDPSetPrimColor(0, 255, 100, 155, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, inv_mwin_3Dma_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[276], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_shirushiT_model[] = {
    gsDPSetPrimColor(0, 255, 100, 80, 100, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mwin_shirushi4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_mwin_v[280], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_suujiwakuT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(70, 160, 190, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, inv_mwin_suujiwaku2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&inv_mwin_v[284], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, inv_mwin_suujiwaku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_model[] = {
    gsSPDisplayList(inv_mwin_w1T_model),
    gsSPDisplayList(inv_mwin_w2T_model),
    gsSPDisplayList(inv_mwin_w3T_model),
    gsSPDisplayList(inv_mwin_w4T_model),
    gsSPDisplayList(inv_mwin_w5T_model),
    gsSPDisplayList(inv_mwin_w6T_model),
    gsSPDisplayList(inv_mwin_w7T_model),
    gsSPDisplayList(inv_mwin_w8T_model),
    gsSPDisplayList(inv_mwin_w9T_model),
    gsSPDisplayList(inv_mwin_w10T_model),
    gsSPDisplayList(inv_mwin_w11T_model),
    gsSPDisplayList(inv_mwin_w12T_model),
    gsSPDisplayList(inv_mwin_w13_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPDisplayList(inv_mwin_1cT_model),
    gsSPDisplayList(inv_mwin_1c_model),
    gsSPDisplayList(inv_mwin_3DmT_model),
    gsSPDisplayList(inv_mwin_item_model),
    gsSPDisplayList(inv_mwin_tegami_model),
    gsSPDisplayList(inv_mwin_okane_model),
    gsSPDisplayList(inv_mwin_shirushiT_model),
    gsSPDisplayList(inv_mwin_shirushi2T_model),
    gsSPDisplayList(inv_mwin_shirushi3_model),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsSPDisplayList(inv_mwin_suujiwakuT_model),
    gsSPEndDisplayList(),
};

Gfx inv_mwin_item_frame_mode[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_inv_mwin_c(void) {
    pc_load_asset("assets/inv_mwin/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x7982E0, 0, 0);
    pc_load_asset("assets/inv_mwin/inv_mwin_3Dma_tex.bin", inv_mwin_3Dma_tex, 0x800, 0x717820, 0, 0);
    pc_load_asset("assets/inv_mwin/inv_mwin_aw5_tex.bin", inv_mwin_aw5_tex, 0x80, 0x718C20, 0, 0);
}
#endif
