#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_turis01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_turis01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_turis01_pal[] = {
#include "assets/int_ike_k_turis01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb6_tex_txt[0x100];
#else
u8 int_ike_k_turisb6_tex_txt[] = {
#include "assets/int_ike_k_turisb6_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb7_tex_txt[0x80];
#else
u8 int_ike_k_turisb7_tex_txt[] = {
#include "assets/int_ike_k_turisb7_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb1_tex_txt[0x400];
#else
u8 int_ike_k_turisb1_tex_txt[] = {
#include "assets/int_ike_k_turisb1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb3_tex_txt[0x400];
#else
u8 int_ike_k_turisb3_tex_txt[] = {
#include "assets/int_ike_k_turisb3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb2_tex_txt[0x80];
#else
u8 int_ike_k_turisb2_tex_txt[] = {
#include "assets/int_ike_k_turisb2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb5_tex_txt[0x80];
#else
u8 int_ike_k_turisb5_tex_txt[] = {
#include "assets/int_ike_k_turisb5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb8_tex_txt[0x80];
#else
u8 int_ike_k_turisb8_tex_txt[] = {
#include "assets/int_ike_k_turisb8_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turisb4_tex_txt[0x80];
#else
u8 int_ike_k_turisb4_tex_txt[] = {
#include "assets/int_ike_k_turisb4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turibass3_tex_txt[0x200];
#else
u8 int_ike_k_turibass3_tex_txt[] = {
#include "assets/int_ike_k_turibass3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turibass2_tex_txt[0x80];
#else
u8 int_ike_k_turibass2_tex_txt[] = {
#include "assets/int_ike_k_turibass2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_turibass1_tex_txt[0x300];
#else
u8 int_ike_k_turibass1_tex_txt[] = {
#include "assets/int_ike_k_turibass1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_turis01_v[0x750 / sizeof(Vtx)];
#else
Vtx int_ike_k_turis01_v[] = {
#include "assets/int_ike_k_turis01_v.inc"
};
#endif

Gfx int_ike_k_turis01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_turis01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_k_turisb6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_turis01_v, 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turisb7_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_ike_k_turisb1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 16, 17, 18, 16, 18, 19, 16, 20, 21),
    gsSPNTriangles_5b(16, 21, 17, 20, 22, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_ike_k_turisb3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 23, 24, 25, 23, 25, 26, 23, 27, 24),
    gsSPNTriangles_5b(26, 25, 28, 26, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turisb2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_k_turis01_v[30], 31, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turisb5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turisb8_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 23, 25, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turisb4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, int_ike_k_turibass3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_k_turis01_v[61], 21, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 4, 2, 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 8, 9, 10, 11, 12, 10, 10, 12, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_turibass2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 19, 20, 18, 18, 20, 16),
    gsSPNTriangles_5b(18, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_ike_k_turibass1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_k_turis01_v[82], 15, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 2),
    gsSPNTriangles_5b(8, 9, 3, 2, 10, 11, 9, 12, 3, 1, 10, 2),
    gsSPNTriangles_5b(2, 13, 0, 3, 12, 4, 5, 14, 3, 3, 14, 8),
    gsSPNTriangles_5b(2, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_k_turis01_v[97], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 4, 1),
    gsSPNTriangles_5b(7, 15, 8, 15, 3, 0, 14, 16, 17, 17, 12, 14),
    gsSPNTriangles_5b(16, 14, 18, 8, 15, 0, 14, 19, 9, 0, 5, 8),
    gsSPNTriangles_5b(9, 18, 14, 14, 13, 19, 9, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
