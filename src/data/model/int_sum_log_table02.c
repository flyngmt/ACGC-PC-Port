#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_log_table02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_log_table02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_log_table02_pal[] = {
#include "assets/int_sum_log_table02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_table02_top_tex[0x400];
#else
u8 int_sum_log_table02_top_tex[] = {
#include "assets/int_sum_log_table02_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_table02_side_tex[0x100];
#else
u8 int_sum_log_table02_side_tex[] = {
#include "assets/int_sum_log_table02_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_table02_stand_tex[0x100];
#else
u8 int_sum_log_table02_stand_tex[] = {
#include "assets/int_sum_log_table02_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_log_table02_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_sum_log_table02_v[] = {
#include "assets/int_sum_log_table02_v.inc"
};
#endif

Gfx int_sum_log_table02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_table02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_log_table02_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_log_table02_v, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 6, 5, 4, 6, 7, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_table02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_table02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_table02_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_table02_v[8], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 4, 3, 5, 6),
    gsSPNTriangles_5b(5, 7, 8, 9, 10, 11, 12, 11, 13, 14, 13, 15),
    gsSPNTriangles_5b(16, 15, 17, 18, 19, 20, 19, 21, 22, 21, 23, 24),
    gsSPNTriangles_5b(23, 25, 26, 27, 28, 29, 30, 29, 31, 0, 0, 0),
    gsSPVertex(&int_sum_log_table02_v[40], 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 2, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_log_table02_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 9, 10, 11, 8),
    gsSPNTriangles_5b(12, 13, 10, 14, 15, 16, 16, 17, 18, 19, 18, 20),
    gsSPNTriangles_5b(12, 19, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
