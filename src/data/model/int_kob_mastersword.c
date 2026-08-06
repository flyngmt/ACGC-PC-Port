#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kob_mastersword_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kob_mastersword_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kob_mastersword_pal[] = {
#include "assets/int_kob_mastersword_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_kob_mastersword_kan_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_kob_mastersword_kan_tex_rgb_ci4_pal[] = {
#include "assets/int_kob_mastersword_kan_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_tuka_tex[0x180];
#else
u8 int_kob_mastersword_tuka_tex[] = {
#include "assets/int_kob_mastersword_tuka_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_tuba_tex[0x100];
#else
u8 int_kob_mastersword_tuba_tex[] = {
#include "assets/int_kob_mastersword_tuba_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_ishi1_tex[0x80];
#else
u8 int_kob_mastersword_ishi1_tex[] = {
#include "assets/int_kob_mastersword_ishi1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_ishi2_tex[0x80];
#else
u8 int_kob_mastersword_ishi2_tex[] = {
#include "assets/int_kob_mastersword_ishi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_ishi3_tex[0x80];
#else
u8 int_kob_mastersword_ishi3_tex[] = {
#include "assets/int_kob_mastersword_ishi3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_mastersword_kan_tex[0x400];
#else
u8 int_kob_mastersword_kan_tex[] = {
#include "assets/int_kob_mastersword_kan_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kob_mastersword_v[0x4C0 / sizeof(Vtx)];
#else
Vtx int_kob_mastersword_v[] = {
#include "assets/int_kob_mastersword_v.inc"
};
#endif

Gfx int_kob_mastersword_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_mastersword_kan_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_kob_mastersword_kan_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 100, 124, 352),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_kob_mastersword_v, 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 20, 21, 22, 21, 23, 22, 24, 25, 26),
    gsSPNTriangles_5b(24, 27, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kob_mastersword_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_mastersword_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_mastersword_ishi3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_mastersword_v[28], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kob_mastersword_tuba_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14, 4, 5, 6, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 8, 10, 12, 11, 13, 6, 5, 8, 14, 15, 16),
    gsSPNTriangles_5b(17, 14, 18, 17, 19, 14, 15, 20, 21, 16, 15, 21),
    gsSPNTriangles_5b(22, 16, 23, 24, 18, 25, 26, 6, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kob_mastersword_tuka_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kob_mastersword_v[56], 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 4, 6, 7, 4, 7, 5, 0, 7, 1),
    gsSPNTriangles_5b(6, 2, 1, 6, 1, 7, 5, 7, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kob_mastersword_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_mastersword_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_mastersword_ishi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_mastersword_v[64], 12, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_mastersword_ishi1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
