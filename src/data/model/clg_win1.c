#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_kabe_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_kabe_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_kabe_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_kabe_tex_rgb_ci4[0x200];
#else
u8 clg_win_kabe_tex_rgb_ci4[] = {
#include "assets/clg_win_kabe_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_jyuutan_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_jyuutan_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_jyuutan_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_jyuutan_tex_rgb_ci4[0x200];
#else
u8 clg_win_jyuutan_tex_rgb_ci4[] = {
#include "assets/clg_win_jyuutan_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_fuku_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_fuku_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_fuku_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_fuku_tex_rgb_ci4[0x200];
#else
u8 clg_win_fuku_tex_rgb_ci4[] = {
#include "assets/clg_win_fuku_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_kasa_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_kasa_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_kasa_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_kasa_tex_rgb_ci4[0x200];
#else
u8 clg_win_kasa_tex_rgb_ci4[] = {
#include "assets/clg_win_kasa_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_tegami_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_tegami_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_tegami_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_tegami_tex_rgb_ci4[0x200];
#else
u8 clg_win_tegami_tex_rgb_ci4[] = {
#include "assets/clg_win_tegami_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_hani_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_hani_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_hani_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_hani_tex_rgb_ci4[0x200];
#else
u8 clg_win_hani_tex_rgb_ci4[] = {
#include "assets/clg_win_hani_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_hone_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_hone_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_hone_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_hone_tex_rgb_ci4[0x200];
#else
u8 clg_win_hone_tex_rgb_ci4[] = {
#include "assets/clg_win_hone_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_onpu_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_onpu_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_onpu_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_onpu_tex_rgb_ci4[0x200];
#else
u8 clg_win_onpu_tex_rgb_ci4[] = {
#include "assets/clg_win_onpu_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku8_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku8_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku8_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku1_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku2_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku3_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku4_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku5_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku6_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_waku7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_waku7_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_waku7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 clg_win_ha_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 clg_win_ha_tex_rgb_ci4_pal[] = {
#include "assets/clg_win_ha_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 inv_mwin_3Dma_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 inv_mwin_3Dma_tex[] = {
#include "assets/clg_win1/inv_mwin_3Dma_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 fri_win_bell_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 fri_win_bell_tex[] = {
#include "assets/clg_win1/fri_win_bell_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_ran_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_ran_tex[] = {
#include "assets/clg_win_ran_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w1_tex[] = {
#include "assets/clg_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w2_tex[] = {
#include "assets/clg_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w3_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w3_tex[] = {
#include "assets/clg_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w4_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w4_tex[] = {
#include "assets/clg_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 dlt_win_aw5_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 dlt_win_aw5_tex[] = {
#include "assets/dlt_win_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clk_win_sen_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clk_win_sen_tex[] = {
#include "assets/clk_win_sen_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w5_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w5_tex[] = {
#include "assets/clg_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w6_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w6_tex[] = {
#include "assets/clg_win_w6_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_w7_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_w7_tex[] = {
#include "assets/clg_win_w7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku8_tex_rgb_ci4[0x200];
#else
u8 clg_win_waku8_tex_rgb_ci4[] = {
#include "assets/clg_win_waku8_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku1_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku1_tex_rgb_ci4[] = {
#include "assets/clg_win_waku1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku2_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku2_tex_rgb_ci4[] = {
#include "assets/clg_win_waku2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku3_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku3_tex_rgb_ci4[] = {
#include "assets/clg_win_waku3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku4_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku4_tex_rgb_ci4[] = {
#include "assets/clg_win_waku4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku5_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku5_tex_rgb_ci4[] = {
#include "assets/clg_win_waku5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku6_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku6_tex_rgb_ci4[] = {
#include "assets/clg_win_waku6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_waku7_tex_rgb_ci4[0x400];
#else
u8 clg_win_waku7_tex_rgb_ci4[] = {
#include "assets/clg_win_waku7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 clg_win_ha_tex_rgb_ci4[0x200];
#else
u8 clg_win_ha_tex_rgb_ci4[] = {
#include "assets/clg_win_ha_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx clg_win1_v[0xAD0 / sizeof(Vtx)];
#else
Vtx clg_win1_v[] = {
#include "assets/clg_win1_v.inc"
};
#endif

Gfx clg_win_sen_model[] = {
    gsDPSetPrimColor(0, 255, 80, 80, 185, 255),
    gsSPVertex(clg_win1_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku13_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku8_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, clg_win_waku8_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&clg_win1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_ueT_model[] = {
    gsDPSetPrimColor(0, 255, 100, 100, 255, 255),
    gsDPSetEnvColor(185, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, clg_win_w7_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[8], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, clg_win_w6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[16], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, clg_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[20], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, clg_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[28], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, clg_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[36], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 0, 0),
    gsSP2Triangles(7, 8, 9, 0, 8, 10, 9, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, clg_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[47], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, clg_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[51], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_ue2T_model[] = {
    gsDPSetPrimColor(0, 255, 185, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, dlt_win_aw5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[59], 15, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 6, 2, 7, 8, 9, 7, 10, 8, 11, 10, 6),
    gsSPNTriangles_5b(10, 12, 6, 13, 14, 12, 14, 0, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na1T_model[] = {
    gsSPVertex(&clg_win1_v[74], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 2, 6, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na2T_model[] = {
    gsSPVertex(&clg_win1_v[81], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na3T_model[] = {
    gsSPVertex(&clg_win1_v[85], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na4T_model[] = {
    gsSPVertex(&clg_win1_v[89], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na5T_model[] = {
    gsSPVertex(&clg_win1_v[93], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na6T_model[] = {
    gsSPVertex(&clg_win1_v[97], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_na7T_model[] = {
    gsSPVertex(&clg_win1_v[101], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_3dT_model[] = {
    gsDPSetPrimColor(0, 255, 0, 50, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, inv_mwin_3Dma_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[105], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_beruT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 40, 40, 155, 255),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, fri_win_bell_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&clg_win1_v[109], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_shikiriT_model[] = {
    gsDPSetPrimColor(0, 255, 20, 20, 70, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clk_win_sen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[113], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[125], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[129], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[133], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[137], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[141], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[145], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[149], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[153], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[157], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, clg_win_waku3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[161], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[165], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};

Gfx clg_win_waku12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, clg_win_waku2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, clg_win_waku2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clg_win1_v[169], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};

Gfx clg_mwin_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPEndDisplayList(),
};

Gfx clg_name_mode[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, clg_win_ran_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetEnvColor(185, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx clg_mwin1_model[] = {
    gsSPDisplayList(clg_win_waku1T_model),
    gsSPDisplayList(clg_win_waku2T_model),
    gsSPDisplayList(clg_win_waku3T_model),
    gsSPDisplayList(clg_win_waku4T_model),
    gsSPDisplayList(clg_win_waku5T_model),
    gsSPDisplayList(clg_win_waku6T_model),
    gsSPDisplayList(clg_win_waku7T_model),
    gsSPDisplayList(clg_win_waku8T_model),
    gsSPDisplayList(clg_win_waku9T_model),
    gsSPDisplayList(clg_win_waku10T_model),
    gsSPDisplayList(clg_win_waku11T_model),
    gsSPDisplayList(clg_win_waku12T_model),
    gsSPDisplayList(clg_win_waku13_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsSPDisplayList(clg_win_ueT_model),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPDisplayList(clg_win_ue2T_model),
    gsSPEndDisplayList(),
};

Gfx clg_mwin2_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPDisplayList(clg_win_3dT_model),
    gsSPDisplayList(clg_win_shikiriT_model),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPDisplayList(clg_win_sen_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_clg_win1_c(void) {
    pc_load_asset("assets/clg_win1/inv_mwin_3Dma_tex.bin", inv_mwin_3Dma_tex, 0x800, 0x6C53E0, 0, 0);
    pc_load_asset("assets/clg_win1/fri_win_bell_tex.bin", fri_win_bell_tex, 0x100, 0x6C5BE0, 0, 0);
}
#endif
