#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_horagai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_horagai_pal[]= {
#include "assets/obj_shop_horagai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_horagai_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_horagai_tex[]= {
#include "assets/obj_shop_horagai_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_horagai_v[0xA0 / sizeof(Vtx)];
#else
Vtx obj_shop_horagai_v[] = {
#include "assets/obj_shop_horagai_v.inc"
};
#endif

Gfx obj_horagaiT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_horagai_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_horagai_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_horagaiT_gfx_model[] = {
gsSPVertex(obj_shop_horagai_v, 10, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 7, 5, 0, 5, 1, 0, 8, 0, 2),
gsSPNTriangles_5b(1, 9, 3, 8, 7, 0, 8, 6, 7, 4, 9, 5),
gsSPNTriangles_5b(9, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

