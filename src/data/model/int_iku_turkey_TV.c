#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_turkey_TV_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_TV_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_TV_pal[] = {
#include "assets/int_iku_turkey_TV_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_c_tex_txt[0x200];
#else
u8 int_iku_turkey_TV_c_tex_txt[] = {
#include "assets/int_iku_turkey_TV_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_b_tex_txt[0x100];
#else
u8 int_iku_turkey_TV_b_tex_txt[] = {
#include "assets/int_iku_turkey_TV_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_a_tex_txt[0x100];
#else
u8 int_iku_turkey_TV_a_tex_txt[] = {
#include "assets/int_iku_turkey_TV_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_d_tex_txt[0x100];
#else
u8 int_iku_turkey_TV_d_tex_txt[] = {
#include "assets/int_iku_turkey_TV_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_e_tex_txt[0x200];
#else
u8 int_iku_turkey_TV_e_tex_txt[] = {
#include "assets/int_iku_turkey_TV_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_f_tex_txt[0x80];
#else
u8 int_iku_turkey_TV_f_tex_txt[] = {
#include "assets/int_iku_turkey_TV_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_g_tex_txt[0x80];
#else
u8 int_iku_turkey_TV_g_tex_txt[] = {
#include "assets/int_iku_turkey_TV_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_h_tex_txt[0x80];
#else
u8 int_iku_turkey_TV_h_tex_txt[] = {
#include "assets/int_iku_turkey_TV_h_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_TV_i_tex_txt[0x80];
#else
u8 int_iku_turkey_TV_i_tex_txt[] = {
#include "assets/int_iku_turkey_TV_i_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_turkey_TV_v[0x440 / sizeof(Vtx)];
#else
Vtx int_iku_turkey_TV_v[] = {
#include "assets/int_iku_turkey_TV_v.inc"
};
#endif

Gfx int_iku_turkey_TV_model_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_turkey_TV_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_turkey_TV_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_turkey_TV_model_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_turkey_TV_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_TV_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_turkey_TV_v[4], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_TV_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_turkey_TV_v[11], 27, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 22, 21, 21, 23, 25, 2, 1, 26),
    gsSPNTriangles_5b(2, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_TV_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_turkey_TV_v[38], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_TV_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 6, 7, 8, 7, 6, 9, 10, 11, 12),
    gsSPNTriangles_5b(8, 13, 6, 7, 11, 10, 8, 10, 14, 9, 11, 7),
    gsSPNTriangles_5b(14, 13, 8, 12, 14, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_TV_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 15, 16, 17, 18, 19, 20, 17, 21, 15),
    gsSPNTriangles_5b(21, 17, 22, 23, 24, 25, 26, 27, 28, 25, 20, 23),
    gsSPNTriangles_5b(20, 25, 18, 28, 29, 26, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
