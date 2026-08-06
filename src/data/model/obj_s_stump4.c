#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_stump_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_stump_tex[]= {
#include "assets/obj_s_tree_stump_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_stump4_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_s_stump4_v[] = { 
#include "assets/obj_s_stump4_v.inc"
};
#endif

Gfx obj_stump4T_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_s_tree_stump_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_gold_stump4T_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_s_tree_stump_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_stump4T_gfx_model[] = { 
gsSPVertex(obj_s_stump4_v, 7, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(0, 5, 1, 5, 4, 1, 6, 3, 4, 5, 6, 4),
gsSPEndDisplayList()
};

