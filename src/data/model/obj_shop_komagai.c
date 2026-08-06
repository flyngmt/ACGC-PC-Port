#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_komagai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_komagai_pal[]= {
#include "assets/obj_shop_komagai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_komagai_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_komagai_tex[]= {
#include "assets/obj_shop_komagai_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_komagai_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_shop_komagai_v[] = {
#include "assets/obj_shop_komagai_v.inc"
};
#endif

Gfx obj_komagaiT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_komagai_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_komagai_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_komagaiT_gfx_model[] = {
gsSPVertex(obj_shop_komagai_v, 7, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(0, 5, 1, 5, 6, 1, 6, 4, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

