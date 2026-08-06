#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kob_jimuisu_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kob_jimuisu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kob_jimuisu_pal[] = {
#include "assets/int_kob_jimuisu_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_main1_tex[0x100];
#else
u8 int_kob_jimuisu_main1_tex[] = {
#include "assets/int_kob_jimuisu_main1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_se1_tex[0x80];
#else
u8 int_kob_jimuisu_se1_tex[] = {
#include "assets/int_kob_jimuisu_se1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_se2_tex[0x80];
#else
u8 int_kob_jimuisu_se2_tex[] = {
#include "assets/int_kob_jimuisu_se2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_hone1_tex[0x80];
#else
u8 int_kob_jimuisu_hone1_tex[] = {
#include "assets/int_kob_jimuisu_hone1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_ashi1_tex[0x80];
#else
u8 int_kob_jimuisu_ashi1_tex[] = {
#include "assets/int_kob_jimuisu_ashi1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_ashi2_tex[0x100];
#else
u8 int_kob_jimuisu_ashi2_tex[] = {
#include "assets/int_kob_jimuisu_ashi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_hone2_tex[0x100];
#else
u8 int_kob_jimuisu_hone2_tex[] = {
#include "assets/int_kob_jimuisu_hone2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_jimuisu_ashi3_tex[0x100];
#else
u8 int_kob_jimuisu_ashi3_tex[] = {
#include "assets/int_kob_jimuisu_ashi3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kob_jimuisu_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_kob_jimuisu_v[] = {
#include "assets/int_kob_jimuisu_v.inc"
};
#endif

Gfx int_kob_jimuisu_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_jimuisu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kob_jimuisu_ashi3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kob_jimuisu_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kob_jimuisu_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_jimuisu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kob_jimuisu_hone2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_jimuisu_v[8], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kob_jimuisu_ashi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_jimuisu_ashi1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 28, 29, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_jimuisu_hone1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kob_jimuisu_v[38], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_jimuisu_se2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_jimuisu_se1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 10, 12, 12, 13, 14, 12),
    gsSPNTriangles_5b(13, 12, 11, 13, 15, 14, 13, 14, 14, 15, 10, 12),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kob_jimuisu_main1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 16, 17, 18, 16, 18, 19, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 16, 21, 22, 17, 21, 17, 16, 20, 23, 22),
    gsSPNTriangles_5b(20, 22, 21, 19, 18, 23, 19, 23, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};
