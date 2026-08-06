#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_leaf_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_leaf_tex[] = {
#include "assets/obj_s_cedar_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_young_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_young_tex[] = {
#include "assets/obj_s_cedar_young_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_cedar3_v[0x1E0 / sizeof(Vtx)];
#else
Vtx obj_s_cedar3_v[] = {
#include "assets/obj_s_cedar3_v.inc"
};
#endif

Gfx obj_s_cedar3_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_cedar_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_cedar3_leafT_gfx_model[] = {
    gsSPVertex(obj_s_cedar3_v, 23, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 12, 13, 7, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_cedar3_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_cedar_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_cedar3_trunkT_gfx_model[] = {
    gsSPVertex(&obj_s_cedar3_v[23], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 3, 6, 1, 1, 6, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
