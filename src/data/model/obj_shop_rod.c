#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_rod_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_rod_pal[]= {
#include "assets/obj_shop_rod_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_rod_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_rod_tex[]= {
#include "assets/obj_shop_rod_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_rod_v[0x190 / sizeof(Vtx)];
#else
Vtx obj_shop_rod_v[] = {
#include "assets/obj_shop_rod_v.inc"
};
#endif

Gfx obj_rodT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_rod_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_rod_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_rodT_gfx_model[] = {
gsSPVertex(obj_shop_rod_v, 22, 0),
gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 6, 2, 7, 6, 7, 8, 2, 5, 9),
gsSPNTriangles_5b(2, 9, 7, 10, 7, 11, 10, 11, 12, 7, 13, 14),
gsSPNTriangles_5b(7, 14, 11, 15, 11, 16, 11, 14, 16, 17, 18, 19),
gsSPNTriangles_5b(18, 20, 19, 17, 21, 18, 21, 20, 18, 1, 0, 4),
gsSPEndDisplayList(),
};

Gfx obj_rod_lineT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_rod_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_rod_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_rod_lineT_gfx_model[] = {
gsSPVertex(&obj_shop_rod_v[22], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

