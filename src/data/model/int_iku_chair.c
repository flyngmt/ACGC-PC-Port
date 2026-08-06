#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_chair_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_chair_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_chair_pal[] = {
#include "assets/int_iku_chair_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_chair_d_tex_txt[0x100];
#else
u8 int_iku_chair_d_tex_txt[] = {
#include "assets/int_iku_chair_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_chair_a_tex_txt[0x200];
#else
u8 int_iku_chair_a_tex_txt[] = {
#include "assets/int_iku_chair_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_chair_e_tex_txt[0x200];
#else
u8 int_iku_chair_e_tex_txt[] = {
#include "assets/int_iku_chair_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_chair_b_tex_txt[0x200];
#else
u8 int_iku_chair_b_tex_txt[] = {
#include "assets/int_iku_chair_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_chair_c_tex_txt[0x100];
#else
u8 int_iku_chair_c_tex_txt[] = {
#include "assets/int_iku_chair_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_chair_v[0x6F0 / sizeof(Vtx)];
#else
Vtx int_iku_chair_v[] = {
#include "assets/int_iku_chair_v.inc"
};
#endif

Gfx int_iku_chair_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_chair_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_chair_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_chair_v, 21, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 2, 1),
    gsSPNTriangles_5b(3, 5, 0, 0, 7, 3, 2, 7, 0, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 17, 16, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_chair_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_chair_v[21], 27, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iku_chair_v[48], 16, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 7, 8, 9, 10, 11, 12, 13, 14, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_chair_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_chair_v[64], 30, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_chair_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_chair_v[94], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 0, 2, 2, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 5, 7, 10, 5, 5, 10, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_chair_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 11, 13, 16, 11),
    gsSPNTriangles_5b(11, 16, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
