#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_tire_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_tire_pal[]= {
#include "assets/obj_shop_tire_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_tire_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_tire_tex[]= {
#include "assets/obj_shop_tire_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_tire_v[0x2C0 / sizeof(Vtx)];
#else
Vtx obj_shop_tire_v[] = {
#include "assets/obj_shop_tire_v.inc"
};
#endif

Gfx obj_g1T_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_tire_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_tire_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_g1T_gfx_model[] = {
gsSPVertex(obj_shop_tire_v, 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(5, 6, 4, 5, 4, 1, 7, 5, 1, 8, 9, 10),
gsSPNTriangles_5b(9, 11, 10, 9, 12, 11, 10, 11, 6, 10, 6, 5),
gsSPNTriangles_5b(13, 10, 5, 14, 15, 16, 15, 17, 16, 15, 18, 17),
gsSPNTriangles_5b(19, 20, 18, 19, 18, 15, 21, 19, 15, 22, 16, 23),
gsSPNTriangles_5b(16, 24, 23, 16, 17, 24, 23, 24, 12, 23, 12, 9),
gsSPNTriangles_5b(25, 23, 9, 26, 27, 28, 28, 29, 30, 0, 0, 0),
gsSPVertex(&obj_shop_tire_v[31], 13, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 0, 5, 6, 7),
gsSPNTriangles_5b(7, 8, 9, 10, 11, 5, 2, 12, 10, 0, 0, 0),
gsSPEndDisplayList(),
};

