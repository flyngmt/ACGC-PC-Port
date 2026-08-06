#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_stump_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_stump_tex[]= {
#include "assets/obj_s_cedar_stump_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_cstump4_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_s_cstump4_v[] = { 
#include "assets/obj_s_cstump4_v.inc"
};
#endif

Gfx obj_s_cstump4T_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_s_cedar_stump_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_s_cstump4T_gfx_model[] = { 
gsSPVertex(obj_s_cstump4_v, 7, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 2, 2, 4, 0),
gsSPNTriangles_5b(1, 5, 2, 2, 5, 3, 1, 6, 5, 5, 6, 3),
gsSPEndDisplayList()
};

