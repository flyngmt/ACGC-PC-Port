#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) Vtx obj_s_tree5_v[0x160 / sizeof(Vtx)];
#else
ATTRIBUTE_ALIGN(32) Vtx obj_s_tree5_v[] = {
#include "assets/obj_s_tree5_v.inc"
};
#endif

extern u8 obj_s_tree3_leaf_tex[], obj_s_tree4_trunk_tex[];

Gfx obj_s_tree5_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree3_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_gold_tree5_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree3_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree5_leafT_gfx_model[] = {
    gsSPVertex(obj_s_tree5_v, 15, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 2, 1, 4, 0, 2),
    gsSPNTriangles_5b(3, 4, 2, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 10, 13, 11, 13, 14, 11),
    gsSPNTriangles_5b(14, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree5_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree4_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_gold_tree5_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree4_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_tree5_trunkT_gfx_model[] = {
    gsSPVertex(&obj_s_tree5_v[15], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 5, 2, 6, 2, 3, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};
