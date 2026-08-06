#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_w_tree_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_w_tree_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_w_tree_pal[] = {
#include "assets/int_w_tree_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_w_tree_grass_tex[0x200];
#else
u8 int_nog_w_tree_grass_tex[] = {
#include "assets/int_nog_w_tree_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_w_tree_leaf2_tex[0x200];
#else
u8 int_nog_w_tree_leaf2_tex[] = {
#include "assets/int_nog_w_tree_leaf2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_w_tree_trunk_tex[0x400];
#else
u8 int_nog_w_tree_trunk_tex[] = {
#include "assets/int_nog_w_tree_trunk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_w_tree_leaf1_tex[0x200];
#else
u8 int_nog_w_tree_leaf1_tex[] = {
#include "assets/int_nog_w_tree_leaf1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_w_tree_v[0x570 / sizeof(Vtx)];
#else
Vtx int_nog_w_tree_v[] = {
#include "assets/int_nog_w_tree_v.inc"
};
#endif

Gfx int_nog_w_tree_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_w_tree_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_w_tree_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_w_tree_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_w_treeT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_w_tree_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_w_tree_leaf1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_w_tree_v[4], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_w_tree_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_w_tree_v[9], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 3, 4, 5, 5, 6, 7),
    gsSPNTriangles_5b(7, 3, 5, 8, 6, 5, 4, 8, 5, 6, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 12, 7, 10, 10, 11, 12, 7, 6, 10),
    gsSPNTriangles_5b(13, 14, 15, 15, 16, 17, 17, 13, 15, 18, 16, 15),
    gsSPNTriangles_5b(14, 18, 15, 19, 20, 21, 20, 14, 21, 13, 22, 21),
    gsSPNTriangles_5b(21, 14, 13, 22, 19, 21, 12, 11, 23, 23, 19, 22),
    gsSPNTriangles_5b(22, 12, 23, 24, 19, 23, 11, 24, 23, 3, 25, 0),
    gsSPNTriangles_5b(7, 26, 3, 22, 27, 12, 12, 28, 7, 13, 29, 22),
    gsSPNTriangles_5b(17, 30, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_w_tree_v[40], 27, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 3, 10, 11, 5, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 18, 18, 19, 20, 21, 22, 23, 22, 24, 23),
    gsSPNTriangles_5b(25, 26, 23, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_w_tree_leaf2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_w_tree_v[67], 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 1, 0),
    gsSPNTriangles_5b(4, 0, 3, 5, 6, 7, 5, 8, 6, 6, 9, 7),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 10, 13, 11, 11, 14, 12),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 19, 16, 15),
    gsSPNTriangles_5b(19, 15, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
