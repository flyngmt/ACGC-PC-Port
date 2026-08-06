#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_a_pal[]= {
#include "assets/obj_shop_paint_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_b_pal[]= {
#include "assets/obj_shop_paint_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_c_pal[]= {
#include "assets/obj_shop_paint_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_d_pal[]= {
#include "assets/obj_shop_paint_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_e_pal[]= {
#include "assets/obj_shop_paint_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_f_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_f_pal[]= {
#include "assets/obj_shop_paint_f_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_g_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_g_pal[]= {
#include "assets/obj_shop_paint_g_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_h_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_h_pal[]= {
#include "assets/obj_shop_paint_h_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_i_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_i_pal[]= {
#include "assets/obj_shop_paint_i_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_j_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_j_pal[]= {
#include "assets/obj_shop_paint_j_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_k_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_k_pal[]= {
#include "assets/obj_shop_paint_k_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_l_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paint_l_pal[]= {
#include "assets/obj_shop_paint_l_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_paint_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_paint_tex[]= {
#include "assets/obj_shop_paint_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_paint_v[0x1B0 / sizeof(Vtx)];
#else
Vtx obj_shop_paint_v[] = {
#include "assets/obj_shop_paint_v.inc"
};
#endif

Gfx obj_shop_paintT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_shop_paint_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_paintT_a_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_a_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_b_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_b_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_c_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_c_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_d_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_d_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_e_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_e_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_f_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_f_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_g_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_g_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_h_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_h_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_i_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_i_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_j_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_j_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_k_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_k_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_l_mat_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paint_l_pal),
gsSPDisplayList(obj_shop_paintT_mat_model),
gsSPEndDisplayList(),
};

Gfx obj_paintT_gfx_model[] = {
gsSPVertex(obj_shop_paint_v, 27, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 7, 1, 7, 8, 1),
gsSPNTriangles_5b(8, 5, 1, 9, 10, 11, 9, 11, 12, 12, 11, 13),
gsSPNTriangles_5b(12, 13, 14, 0, 15, 16, 16, 17, 0, 18, 16, 15),
gsSPNTriangles_5b(15, 19, 18, 20, 0, 17, 17, 21, 20, 21, 22, 23),
gsSPNTriangles_5b(23, 20, 21, 19, 24, 25, 25, 18, 19, 26, 23, 22),
gsSPEndDisplayList(),
};

