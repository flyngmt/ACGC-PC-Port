#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_prores_mat01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_mat01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_mat01_pal[] = {
#include "assets/int_ike_prores_mat01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_mat01_handle_tex[0x40];
#else
u8 int_ike_prores_mat01_handle_tex[] = {
#include "assets/int_ike_prores_mat01_handle_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_mat01_top_tex[0x100];
#else
u8 int_ike_prores_mat01_top_tex[] = {
#include "assets/int_ike_prores_mat01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_mat01_side_tex[0x40];
#else
u8 int_ike_prores_mat01_side_tex[] = {
#include "assets/int_ike_prores_mat01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_prores_mat01_v[0x240 / sizeof(Vtx)];
#else
Vtx int_ike_prores_mat01_v[] = {
#include "assets/int_ike_prores_mat01_v.inc"
};
#endif

Gfx int_ike_prores_mat1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_mat01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_mat01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_prores_mat01_v, 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 2),
    gsSPNTriangles_5b(14, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_prores_mat01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 15, 16, 17, 16, 18, 17, 15, 17, 19),
    gsSPNTriangles_5b(17, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_prores_mat1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_mat01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_mat01_handle_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_mat01_v[20], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
