#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_ido_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_ido_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_ido_pal[] = {
#include "assets/int_iku_ido_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_ab_tex_txt[0x200];
#else
u8 int_iku_ido_ab_tex_txt[] = {
#include "assets/int_iku_ido_ab_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_i_tex_txt[0x80];
#else
u8 int_iku_ido_i_tex_txt[] = {
#include "assets/int_iku_ido_i_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_h_tex_txt[0x80];
#else
u8 int_iku_ido_h_tex_txt[] = {
#include "assets/int_iku_ido_h_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_g_tex_txt[0x80];
#else
u8 int_iku_ido_g_tex_txt[] = {
#include "assets/int_iku_ido_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_f_tex_txt[0x200];
#else
u8 int_iku_ido_f_tex_txt[] = {
#include "assets/int_iku_ido_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_e_tex_txt[0x80];
#else
u8 int_iku_ido_e_tex_txt[] = {
#include "assets/int_iku_ido_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_c_tex_txt[0x80];
#else
u8 int_iku_ido_c_tex_txt[] = {
#include "assets/int_iku_ido_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_b_tex_txt[0x100];
#else
u8 int_iku_ido_b_tex_txt[] = {
#include "assets/int_iku_ido_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_j_tex_txt[0x80];
#else
u8 int_iku_ido_j_tex_txt[] = {
#include "assets/int_iku_ido_j_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ido_d_tex_txt[0x80];
#else
u8 int_iku_ido_d_tex_txt[] = {
#include "assets/int_iku_ido_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_ido_v[0x700 / sizeof(Vtx)];
#else
Vtx int_iku_ido_v[] = {
#include "assets/int_iku_ido_v.inc"
};
#endif

Gfx int_iku_ido_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_ido_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_ido_ab_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_ido_v, 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 5, 5, 10, 11, 12, 13, 14, 15, 16, 12),
    gsSPNTriangles_5b(12, 17, 18, 19, 20, 12, 21, 22, 0, 23, 24, 25),
    gsSPNTriangles_5b(26, 27, 24, 28, 29, 26, 30, 21, 31, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_i_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_iku_ido_v[32], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_h_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_ido_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(9, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 12, 22, 13, 23, 24, 25, 23, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 27, 29, 30, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_ido_v[63], 31, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 5, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_ido_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 24, 25, 23, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_iku_ido_j_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_ido_v[94], 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 0, 9, 10, 11, 0, 8, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ido_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};
