#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_tree3_leaf_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_tree3_leaf_tex[] = {
#include "assets/obj_s_tree3_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_tree3_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_s_tree3_v[] = {
#include "assets/obj_s_tree3_v.inc"
};
#endif

extern u8 obj_s_tree_young_tex[];

Gfx obj_s_gold_tree3_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree3_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree3_leafT_gfx_model[] = {
    gsSPVertex(obj_s_tree3_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 0, 2, 4),
    gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree3_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_gold_tree3_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree3_trunkT_gfx_model[] = {
    gsSPVertex(&obj_s_tree3_v[5], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 3, 6, 1, 1, 6, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
