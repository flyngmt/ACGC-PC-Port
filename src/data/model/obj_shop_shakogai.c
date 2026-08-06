#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_shakogai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_shakogai_pal[]= {
#include "assets/obj_shop_shakogai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_shakogai_tex[0xC0];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_shakogai_tex[]= {
#include "assets/obj_shop_shakogai_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_shakogai_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_shop_shakogai_v[] = {
#include "assets/obj_shop_shakogai_v.inc"
};
#endif

Gfx obj_shakogaiT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_shakogai_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, obj_shop_shakogai_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shakogaiT_gfx_model[] = {
gsSPVertex(obj_shop_shakogai_v, 12, 0),
gsSPNTrianglesInit_5b(11, 0, 1, 2, 2, 3, 0, 3, 4, 0),
gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 7, 8, 4, 8, 9, 4),
gsSPNTriangles_5b(9, 0, 4, 8, 10, 9, 10, 0, 9, 10, 11, 0),
gsSPEndDisplayList(),
};

