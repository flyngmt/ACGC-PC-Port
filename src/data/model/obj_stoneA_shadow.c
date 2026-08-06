#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_stone_shadow_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_stone_shadow_tex[]= {
#include "assets/obj_stone_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_stoneA_shadow_v[0xA0 / sizeof(Vtx)];
#else
Vtx obj_stoneA_shadow_v[] = { 
#include "assets/obj_stoneA_shadow_v.inc"
};
#endif

Gfx obj_stoneA_shadowT_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_stone_shadow_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_stoneA_shadowT_gfx_model[] = { 
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 8, 9, 1),
gsSPNTriangles_5b(8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList()
};

