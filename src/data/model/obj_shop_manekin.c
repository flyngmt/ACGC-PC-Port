#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_manekin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_manekin_pal[]= {
#include "assets/obj_shop_manekin_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_shop_manekin_bottom_tex_txt[0x200];
#else
u8 obj_shop_manekin_bottom_tex_txt[] = {
#include "assets/obj_shop_manekin_bottom_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_shop_manekin_foot_tex_txt[0x100];
#else
u8 obj_shop_manekin_foot_tex_txt[] = {
#include "assets/obj_shop_manekin_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_shop_manekin_top_tex_txt[0x80];
#else
u8 obj_shop_manekin_top_tex_txt[] = {
#include "assets/obj_shop_manekin_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_manekin_v[0x390 / sizeof(Vtx)];
#else
Vtx obj_shop_manekin_v[] = {
#include "assets/obj_shop_manekin_v.inc"
};
#endif

Gfx obj_shop_manekin_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_manekin_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_manekin_bottom_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_shop_manekin_v, 27, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 1, 4, 5, 1, 6),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_manekin_foot_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(3, 7, 8, 9, 10, 7, 11, 12, 10, 13),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_manekin_top_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(7, 14, 15, 16, 15, 17, 16, 14, 18, 15),
gsSPNTriangles_5b(19, 20, 21, 19, 22, 20, 23, 24, 25, 23, 26, 24),
gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&obj_shop_manekin_v[27], 30, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 0, 7, 1, 0, 8, 7),
gsSPNTriangles_5b(9, 10, 11, 9, 12, 10, 13, 14, 12, 13, 15, 14),
gsSPNTriangles_5b(12, 14, 10, 16, 17, 18, 16, 19, 17, 18, 20, 16),
gsSPNTriangles_5b(18, 21, 20, 19, 22, 17, 23, 24, 25, 26, 27, 28),
gsSPNTriangles_5b(26, 28, 29, 29, 23, 25, 29, 25, 26, 0, 0, 0),
gsSPEndDisplayList(),
};

