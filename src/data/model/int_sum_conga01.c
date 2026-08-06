#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_conga01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_conga01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_conga01_pal[] = {
#include "assets/int_sum_conga01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_conga01_side_tex[0x300];
#else
u8 int_sum_conga01_side_tex[] = {
#include "assets/int_sum_conga01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_conga01_stand_tex[0x80];
#else
u8 int_sum_conga01_stand_tex[] = {
#include "assets/int_sum_conga01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_conga01_top_tex[0x80];
#else
u8 int_sum_conga01_top_tex[] = {
#include "assets/int_sum_conga01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_conga01_v[0x2C0 / sizeof(Vtx)];
#else
Vtx int_sum_conga01_v[] = {
#include "assets/int_sum_conga01_v.inc"
};
#endif

Gfx int_sum_conga01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_conga01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_conga01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_conga01_v, 21, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 3, 0, 6, 7, 3, 7, 4, 3),
    gsSPNTriangles_5b(4, 8, 5, 4, 9, 8, 9, 10, 8, 7, 11, 9),
    gsSPNTriangles_5b(7, 9, 4, 12, 13, 14, 13, 9, 14, 12, 15, 13),
    gsSPNTriangles_5b(13, 10, 9, 9, 11, 14, 11, 16, 14, 16, 12, 14),
    gsSPNTriangles_5b(15, 12, 17, 12, 18, 17, 18, 19, 17, 16, 20, 18),
    gsSPNTriangles_5b(16, 18, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_conga01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_conga01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_conga01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_conga01_v[21], 23, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 6, 5, 4, 6, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_conga01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 12, 10, 13, 14, 15),
    gsSPNTriangles_5b(13, 16, 17, 18, 19, 20, 21, 22, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};
