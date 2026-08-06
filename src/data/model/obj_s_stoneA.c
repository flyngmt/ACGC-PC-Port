#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_stoneA_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_stoneA_pal[] = {
#include "assets/obj_s_stoneA_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_stoneA_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_stoneA_tex[] = {
#include "assets/obj_s_stoneA_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_stoneA_v[0xA0 / sizeof(Vtx)];
#else
Vtx obj_s_stoneA_v[] = {
#include "assets/obj_s_stoneA_v.inc"
};
#endif

Gfx obj_s_stoneA_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_stoneA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_stoneA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_stoneA_gfx_model[] = {
    gsSPVertex(obj_s_stoneA_v, 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 1, 0),
    gsSPNTriangles_5b(4, 5, 1, 1, 6, 3, 6, 7, 3, 1, 5, 6),
    gsSPNTriangles_5b(2, 8, 9, 2, 3, 8, 3, 7, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
