#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_fence_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_fence_pal[] = {
#include "assets/obj_fence_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_fence_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_fence_tex[] = {
#include "assets/obj_s_fence_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_fenceL_v[0x40 / sizeof(Vtx)];
#else
Vtx obj_s_fenceL_v[] = {
#include "assets/obj_s_fenceL_v.inc"
};
#endif

Gfx obj_s_fenceLT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_fence_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_s_fence_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_fenceLT_gfx_model[] = {
    gsSPVertex(obj_s_fenceL_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
