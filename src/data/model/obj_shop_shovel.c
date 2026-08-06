#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_shovel_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_shovel_pal[]= {
#include "assets/obj_shop_shovel_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_shovel_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_shovel_tex[]= {
#include "assets/obj_shop_shovel_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_shovel_v[0x190 / sizeof(Vtx)];
#else
Vtx obj_shop_shovel_v[] = {
#include "assets/obj_shop_shovel_v.inc"
};
#endif

Gfx obj_shovelT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_shovel_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, obj_shop_shovel_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shovelT_gfx_model[] = {
gsSPVertex(obj_shop_shovel_v, 25, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 1, 4, 2),
gsSPNTriangles_5b(4, 5, 2, 5, 6, 3, 5, 3, 2, 7, 8, 9),
gsSPNTriangles_5b(9, 10, 7, 10, 11, 7, 11, 12, 7, 13, 14, 15),
gsSPNTriangles_5b(13, 15, 16, 12, 17, 7, 7, 17, 8, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 18, 21, 22, 18, 22, 23, 19, 18, 23),
gsSPNTriangles_5b(19, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

