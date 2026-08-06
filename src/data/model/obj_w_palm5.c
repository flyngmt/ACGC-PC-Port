#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_leaf_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_leaf_tex[] = {
#include "assets/obj_w_palm5/obj_w_palm_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_trunk_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_trunk_tex[] = {
#include "assets/obj_w_palm5/obj_w_palm_trunk_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_palm5_v[0x370 / sizeof(Vtx)];
#else
Vtx obj_w_palm5_v[] = {
#include "assets/obj_w_palm5_v.inc"
};
#endif

Gfx obj_w_palm5_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_palm_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_palm5_trunkT_gfx_model[] = {
    gsSPVertex(obj_w_palm5_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 6, 1, 6, 4, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_palm5_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_palm_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_palm5_leafT_gfx_model[] = {
    gsSPVertex(&obj_w_palm5_v[7], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_palm5_v[39], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_w_palm5_c(void) {
    pc_load_asset("assets/obj_w_palm5/obj_w_palm_leaf_tex.bin", obj_w_palm_leaf_tex, 0x800, 0x3F5DE0, 0, 0);
    pc_load_asset("assets/obj_w_palm5/obj_w_palm_trunk_tex.bin", obj_w_palm_trunk_tex, 0x800, 0x3F65E0, 0, 0);
}
#endif
