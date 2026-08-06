#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_totemp04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_totemp04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_totemp04_pal[] = {
#include "assets/int_sum_totemp04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_totemp04_front_txt[0x300];
#else
u8 int_sum_totemp04_front_txt[] = {
#include "assets/int_sum_totemp04_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_totemp04_side_txt[0x300];
#else
u8 int_sum_totemp04_side_txt[] = {
#include "assets/int_sum_totemp04_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_totemp04_top_txt[0x80];
#else
u8 int_sum_totemp04_top_txt[] = {
#include "assets/int_sum_totemp04_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_totemp04_wing_txt[0x100];
#else
u8 int_sum_totemp04_wing_txt[] = {
#include "assets/int_sum_totemp04_wing_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_totemp04_v[0x260 / sizeof(Vtx)];
#else
Vtx int_sum_totemp04_v[] = {
#include "assets/int_sum_totemp04_v.inc"
};
#endif

Gfx int_sum_totemp04_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_totemp04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_totemp04_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_totemp04_v, 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 96, int_sum_totemp04_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 6, 8, 9, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 6, 12, 13, 14, 12, 14, 15, 15, 8, 7),
    gsSPNTriangles_5b(15, 7, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 96, int_sum_totemp04_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_totemp04_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_totemp04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_totemp04_wing_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_totemp04_v[22], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
