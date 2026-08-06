#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_sum01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_sum01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_sum01_pal[] = {
#include "assets/int_ike_k_sum01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_sumuki2_tex_txt[0x100];
#else
u8 int_ike_k_sumuki2_tex_txt[] = {
#include "assets/int_ike_k_sumuki2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_sumuki1_tex_txt[0x200];
#else
u8 int_ike_k_sumuki1_tex_txt[] = {
#include "assets/int_ike_k_sumuki1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_sum01_v[0x540 / sizeof(Vtx)];
#else
Vtx int_ike_k_sum01_v[] = {
#include "assets/int_ike_k_sum01_v.inc"
};
#endif

Gfx int_ike_k_sum01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_sum01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_sumuki2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_sum01_v, 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 9, 11, 24, 9, 11, 10, 18),
    gsSPNTriangles_5b(20, 11, 18, 26, 27, 0, 2, 26, 0, 2, 1, 12),
    gsSPNTriangles_5b(14, 2, 12, 28, 29, 21, 23, 28, 21, 23, 22, 15),
    gsSPNTriangles_5b(17, 23, 15, 30, 31, 6, 8, 30, 6, 8, 7, 3),
    gsSPNTriangles_5b(5, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_k_sumuki1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_sum01_v[32], 32, 0),
    gsSPNTrianglesInit_5b(42, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 8, 9, 0),
    gsSPNTriangles_5b(8, 0, 10, 9, 11, 1, 9, 1, 0, 1, 12, 13),
    gsSPNTriangles_5b(1, 13, 2, 2, 13, 14, 2, 14, 4, 4, 14, 15),
    gsSPNTriangles_5b(4, 15, 6, 16, 5, 7, 16, 7, 17, 11, 18, 12),
    gsSPNTriangles_5b(11, 12, 1, 12, 19, 20, 12, 20, 13, 13, 20, 21),
    gsSPNTriangles_5b(13, 21, 14, 14, 21, 22, 14, 22, 15, 23, 3, 5),
    gsSPNTriangles_5b(23, 5, 16, 18, 24, 19, 18, 19, 12, 19, 25, 26),
    gsSPNTriangles_5b(19, 26, 20, 20, 26, 27, 20, 27, 21, 21, 27, 28),
    gsSPNTriangles_5b(21, 28, 22, 10, 0, 3, 10, 3, 23, 24, 29, 25),
    gsSPNTriangles_5b(24, 25, 19, 25, 30, 31, 25, 31, 26, 0, 0, 0),
    gsSPVertex(&int_ike_k_sum01_v[64], 20, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 12, 9, 14, 12, 14, 1, 1, 14, 15),
    gsSPNTriangles_5b(1, 15, 2, 2, 15, 16, 2, 16, 4, 15, 17, 18),
    gsSPNTriangles_5b(15, 18, 16, 11, 6, 9, 11, 9, 12, 9, 8, 19),
    gsSPNTriangles_5b(9, 19, 14, 14, 19, 17, 14, 17, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};
