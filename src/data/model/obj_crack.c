#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_crack_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_crack_tex[]= {
#include "assets/obj_crack_tex.inc"
};
#endif

Gfx obj_crack0T_g_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_crack_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 4, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

Gfx obj_crack0T_s_mat_model[] = { 
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_crack_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 5, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList()
};

