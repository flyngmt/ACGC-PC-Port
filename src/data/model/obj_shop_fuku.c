#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_fuku_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_fuku_pal[]= {
#include "assets/obj_shop_fuku_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_fuku_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_fuku_tex[]= {
#include "assets/obj_shop_fuku_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_fuku_v[0x260 / sizeof(Vtx)];
#else
Vtx obj_shop_fuku_v[] = {
#include "assets/obj_shop_fuku_v.inc"
};
#endif

Gfx obj_fukuT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_fuku_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_fuku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_fukuT_gfx_model[] = {
gsSPVertex(obj_shop_fuku_v, 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 4, 7, 6, 4, 8, 7),
gsSPNTriangles_5b(9, 10, 11, 9, 11, 2, 12, 13, 10, 12, 10, 9),
gsSPNTriangles_5b(14, 15, 13, 14, 13, 12, 16, 17, 15, 16, 15, 14),
gsSPNTriangles_5b(18, 19, 17, 18, 17, 16, 20, 21, 19, 20, 19, 18),
gsSPNTriangles_5b(0, 22, 23, 0, 23, 24, 24, 23, 25, 24, 25, 26),
gsSPNTriangles_5b(27, 28, 29, 27, 30, 28, 30, 31, 28, 0, 0, 0),
gsSPVertex(&obj_shop_fuku_v[32], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(4, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

