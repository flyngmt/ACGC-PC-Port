#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_zassou_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_zassou_tex[] = {
#include "assets/obj_zassou_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_zassou_a_v[0x40 / sizeof(Vtx)];
#else
Vtx obj_zassou_a_v[] = {
#include "assets/obj_zassou_a_v.inc"
};
#endif

Gfx obj_zassou_aT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_zassou_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 3, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_zassou_aT_gfx_model[] = {
    gsSPVertex(obj_zassou_a_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
