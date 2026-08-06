#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_cedar_trunk_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_cedar_trunk_tex[] = {
#include "assets/obj_w_cedar_trunk_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_cedar4_v[0x360 / sizeof(Vtx)];
#else
Vtx obj_w_cedar4_v[] = {
#include "assets/obj_w_cedar4_v.inc"
};
#endif

Gfx obj_w_cedar4_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_cedar_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_cedar4_trunkT_gfx_model[] = {
    gsSPVertex(obj_w_cedar4_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 5, 2, 6, 2, 3, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

extern u8 obj_w_cedar_leaf_tex[];

Gfx obj_w_cedar4_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_cedar_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_cedar4_leafT_gfx_model[] = {
    gsSPVertex(&obj_w_cedar4_v[7], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 11, 12, 13, 14, 15, 9),
    gsSPNTriangles_5b(16, 17, 14, 18, 19, 20, 21, 22, 23, 23, 24, 16),
    gsSPNTriangles_5b(25, 26, 7, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_cedar4_v[37], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(8, 9, 10, 10, 11, 12, 13, 14, 15, 12, 16, 13),
    gsSPEndDisplayList(),
};
