#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_sawhorsev_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_sawhorsev_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_sawhorsev_pal[] = {
#include "assets/int_iku_sawhorsev_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_sawhorsev_a_tex_txt[0x200];
#else
u8 int_iku_sawhorsev_a_tex_txt[] = {
#include "assets/int_iku_sawhorsev_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_sawhorsev_b_tex_txt[0x200];
#else
u8 int_iku_sawhorsev_b_tex_txt[] = {
#include "assets/int_iku_sawhorsev_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_sawhorsev_c_tex_txt[0x100];
#else
u8 int_iku_sawhorsev_c_tex_txt[] = {
#include "assets/int_iku_sawhorsev_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_sawhorsev_d_tex_txt[0x100];
#else
u8 int_iku_sawhorsev_d_tex_txt[] = {
#include "assets/int_iku_sawhorsev_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_sawhorsev_v[0x670 / sizeof(Vtx)];
#else
Vtx int_iku_sawhorsev_v[] = {
#include "assets/int_iku_sawhorsev_v.inc"
};
#endif

Gfx int_iku_sawhorsev_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_sawhorsev_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_sawhorsev_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_sawhorsev_v, 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 2, 15, 0, 8, 16, 6),
    gsSPNTriangles_5b(5, 17, 3, 14, 18, 12, 11, 19, 9, 0, 0, 0),
    gsSPVertex(&int_iku_sawhorsev_v[20], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 5, 4),
    gsSPNTriangles_5b(12, 4, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 21, 20),
    gsSPNTriangles_5b(26, 20, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&int_iku_sawhorsev_v[52], 27, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 3, 2, 8, 2, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 15, 14, 22, 14, 23, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_sawhorsev_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_sawhorsev_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_iku_sawhorsev_v[79], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_sawhorsev_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
