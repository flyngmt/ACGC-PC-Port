#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bon_momiji_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_momiji_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_momiji_pal[] = {
#include "assets/int_sum_bon_momiji_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_momiji_hachi_tex[0x100];
#else
u8 int_sum_bon_momiji_hachi_tex[] = {
#include "assets/int_sum_bon_momiji_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_momiji_tree_tex[0x200];
#else
u8 int_sum_bon_momiji_tree_tex[] = {
#include "assets/int_sum_bon_momiji_tree_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_momiji_eda_tex[0x100];
#else
u8 int_sum_bon_momiji_eda_tex[] = {
#include "assets/int_sum_bon_momiji_eda_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_momiji_earth_tex[0x80];
#else
u8 int_sum_bon_momiji_earth_tex[] = {
#include "assets/int_sum_bon_momiji_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_momiji_leaf_tex[0x200];
#else
u8 int_sum_bon_momiji_leaf_tex[] = {
#include "assets/int_sum_bon_momiji_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bon_momiji_v[0x5F0 / sizeof(Vtx)];
#else
Vtx int_sum_bon_momiji_v[] = {
#include "assets/int_sum_bon_momiji_v.inc"
};
#endif

Gfx int_sum_bon_momiji_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_momiji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bon_momiji_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bon_momiji_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 6, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bon_momiji_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_momiji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bon_momiji_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bon_momiji_v[7], 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&int_sum_bon_momiji_v[37], 21, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_momiji_eda_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_momiji_v[58], 25, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 5),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 10, 13, 14, 15, 16, 17, 15),
    gsSPNTriangles_5b(0, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_bon_momiji_tree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_momiji_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_momiji_v[83], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(0, 8, 9, 8, 10, 11, 6, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
