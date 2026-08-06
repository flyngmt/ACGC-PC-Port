#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kob_ncube_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kob_ncube_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kob_ncube_pal[] = {
#include "assets/int_kob_ncube_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_gn[0x200];
#else
u8 int_kob_ncube_gn[] = {
#include "assets/int_kob_ncube_gn.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_bn[0x200];
#else
u8 int_kob_ncube_bn[] = {
#include "assets/int_kob_ncube_bn.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_top[0x80];
#else
u8 int_kob_ncube_top[] = {
#include "assets/int_kob_ncube_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_r[0x80];
#else
u8 int_kob_ncube_r[] = {
#include "assets/int_kob_ncube_r.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_g[0x80];
#else
u8 int_kob_ncube_g[] = {
#include "assets/int_kob_ncube_g.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_ncube_b[0x80];
#else
u8 int_kob_ncube_b[] = {
#include "assets/int_kob_ncube_b.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kob_ncube_v[0x480 / sizeof(Vtx)];
#else
Vtx int_kob_ncube_v[] = {
#include "assets/int_kob_ncube_v.inc"
};
#endif

Gfx int_kob_ncube_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_ncube_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_ncube_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kob_ncube_v, 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 6, 8, 9, 6, 9, 10),
    gsSPNTriangles_5b(6, 10, 11, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(12, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_ncube_g),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_kob_ncube_v[26], 26, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 6, 9, 10),
    gsSPNTriangles_5b(6, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_ncube_r),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kob_ncube_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_ncube_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_ncube_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_ncube_v[52], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kob_ncube_bn),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kob_ncube_gn),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
