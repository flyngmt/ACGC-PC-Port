#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_f_tree_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_f_tree_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_f_tree_pal[] = {
#include "assets/int_nog_f_tree_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_f_tree_grass_tex[0x80];
#else
u8 int_nog_f_tree_grass_tex[] = {
#include "assets/int_nog_f_tree_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_f_tree_leaf_tex[0x200];
#else
u8 int_nog_f_tree_leaf_tex[] = {
#include "assets/int_nog_f_tree_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_f_tree_trunk_tex[0x400];
#else
u8 int_nog_f_tree_trunk_tex[] = {
#include "assets/int_nog_f_tree_trunk_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_f_tree_v[0x520 / sizeof(Vtx)];
#else
Vtx int_nog_f_tree_v[] = {
#include "assets/int_nog_f_tree_v.inc"
};
#endif

Gfx int_nog_f_tree_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_f_tree_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_f_tree_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_f_tree_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_f_treeT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_f_tree_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_f_tree_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_f_tree_v[4], 32, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 4, 5, 2),
    gsSPNTriangles_5b(2, 3, 4, 5, 0, 2, 4, 3, 6, 6, 7, 8),
    gsSPNTriangles_5b(8, 4, 6, 9, 7, 6, 3, 9, 6, 7, 10, 11),
    gsSPNTriangles_5b(10, 12, 11, 13, 8, 11, 11, 12, 13, 8, 7, 11),
    gsSPNTriangles_5b(14, 15, 16, 16, 17, 18, 18, 14, 16, 19, 17, 16),
    gsSPNTriangles_5b(15, 19, 16, 20, 21, 22, 21, 15, 22, 14, 23, 22),
    gsSPNTriangles_5b(22, 15, 14, 23, 20, 22, 13, 12, 24, 24, 20, 23),
    gsSPNTriangles_5b(23, 13, 24, 25, 20, 24, 12, 25, 24, 4, 26, 5),
    gsSPNTriangles_5b(8, 27, 4, 23, 28, 13, 13, 29, 8, 14, 30, 23),
    gsSPNTriangles_5b(18, 31, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_f_tree_v[36], 21, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 3, 10, 11, 5, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 18, 18, 19, 20, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_f_tree_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_f_tree_v[57], 25, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 3, 4, 5, 6, 7, 5, 7, 8, 9, 6, 5),
    gsSPNTriangles_5b(9, 5, 8, 10, 11, 12, 10, 13, 11, 11, 14, 12),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 18, 16, 16, 19, 17),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 21, 20),
    gsSPNTriangles_5b(24, 20, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
