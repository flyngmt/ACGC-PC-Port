#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_baby_tex[0x180];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_cedar_baby_tex[]= {
#include "assets/obj_s_cedar_baby_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_cedar1_v[0x40 / sizeof(Vtx)];
#else
Vtx obj_s_cedar1_v[] = { 
#include "assets/obj_s_cedar1_v.inc"
};
#endif

Gfx obj_s_cedar1T_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 24, obj_s_cedar_baby_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_s_cedar1T_gfx_model[] = { 
gsSPVertex(obj_s_cedar1_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList()
};

