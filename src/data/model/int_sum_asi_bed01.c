#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_asi_bed01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_bed01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_bed01_pal[] = {
#include "assets/int_sum_asi_bed01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_bed01_pillow_tex[0x80];
#else
u8 int_sum_asi_bed01_pillow_tex[] = {
#include "assets/int_sum_asi_bed01_pillow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_bed01_top_tex[0x300];
#else
u8 int_sum_asi_bed01_top_tex[] = {
#include "assets/int_sum_asi_bed01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_bed01_side_tex[0x100];
#else
u8 int_sum_asi_bed01_side_tex[] = {
#include "assets/int_sum_asi_bed01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_bed01_heard_tex[0x300];
#else
u8 int_sum_asi_bed01_heard_tex[] = {
#include "assets/int_sum_asi_bed01_heard_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_asi_bed01_v[0x3B0 / sizeof(Vtx)];
#else
Vtx int_sum_asi_bed01_v[] = {
#include "assets/int_sum_asi_bed01_v.inc"
};
#endif

Gfx int_sum_asi_bed01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_asi_bed01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_asi_bed01_v, 19, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 3, 4, 8, 4, 7, 8, 7, 0, 8),
    gsSPNTriangles_5b(0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_asi_bed01_pillow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 10, 9, 12, 13, 10, 12),
    gsSPNTriangles_5b(13, 11, 10, 14, 15, 16, 17, 16, 15, 17, 15, 18),
    gsSPNTriangles_5b(15, 14, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_asi_bed01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_asi_bed01_heard_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_asi_bed01_v[19], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 15, 14, 22, 15, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 11, 9, 12, 6, 13),
    gsSPNTriangles_5b(12, 7, 6, 14, 15, 16, 17, 14, 16, 18, 19, 20),
    gsSPNTriangles_5b(21, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_asi_bed01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_asi_bed01_v[47], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 0),
    gsSPNTriangles_5b(3, 4, 0, 6, 7, 8, 6, 9, 7, 10, 6, 8),
    gsSPNTriangles_5b(10, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
