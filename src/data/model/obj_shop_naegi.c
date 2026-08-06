#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_naegi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_naegi_pal[]= {
#include "assets/obj_shop_naegi_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_naegi_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_naegi_tex[]= {
#include "assets/obj_shop_naegi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_naegi_v[0x1B0 / sizeof(Vtx)];
#else
Vtx obj_shop_naegi_v[] = {
#include "assets/obj_shop_naegi_v.inc"
};
#endif

Gfx obj_naegiT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_naegi_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, obj_shop_naegi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_naegiT_gfx_model[] = {
gsSPVertex(obj_shop_naegi_v, 27, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 1, 3, 1, 4, 3),
gsSPNTriangles_5b(13, 14, 1, 15, 16, 17, 18, 17, 14, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 7, 9, 10, 11),
gsSPNTriangles_5b(9, 12, 10, 19, 20, 21, 20, 22, 21, 23, 24, 25),
gsSPNTriangles_5b(23, 26, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

