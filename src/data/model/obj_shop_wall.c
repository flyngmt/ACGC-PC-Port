#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_wall_pal[]= {
#include "assets/obj_shop_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_wall_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_wall_tex[]= {
#include "assets/obj_shop_wall_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_wall_v[0x240 / sizeof(Vtx)];
#else
Vtx obj_shop_wall_v[] = {
#include "assets/obj_shop_wall_v.inc"
};
#endif

Gfx obj_wallT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, obj_shop_wall_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_wallT_gfx_model[] = {
gsSPVertex(obj_shop_wall_v, 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 1, 4, 5, 1, 5, 2, 4, 6, 7),
gsSPNTriangles_5b(4, 7, 5, 6, 8, 9, 6, 9, 7, 10, 11, 12),
gsSPNTriangles_5b(10, 12, 13, 8, 10, 13, 8, 13, 9, 14, 15, 16),
gsSPNTriangles_5b(14, 16, 17, 15, 0, 3, 15, 3, 16, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 19, 22, 23, 19, 23, 20, 24, 25, 26),
gsSPNTriangles_5b(25, 27, 26, 25, 28, 27, 28, 29, 27, 0, 0, 0),
gsSPVertex(&obj_shop_wall_v[30], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

