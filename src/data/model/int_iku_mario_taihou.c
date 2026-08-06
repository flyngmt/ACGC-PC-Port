#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_mario_taihou_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_taihou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_taihou_pal[] = {
#include "assets/int_iku_mario_taihou_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_taihou_a_tex_txt[0x200];
#else
u8 int_iku_mario_taihou_a_tex_txt[] = {
#include "assets/int_iku_mario_taihou_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_taihou_e_tex_txt[0x200];
#else
u8 int_iku_mario_taihou_e_tex_txt[] = {
#include "assets/int_iku_mario_taihou_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_taihou_d_tex_txt[0x200];
#else
u8 int_iku_mario_taihou_d_tex_txt[] = {
#include "assets/int_iku_mario_taihou_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_taihou_c_tex_txt[0x100];
#else
u8 int_iku_mario_taihou_c_tex_txt[] = {
#include "assets/int_iku_mario_taihou_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_taihou_b_tex_txt[0x400];
#else
u8 int_iku_mario_taihou_b_tex_txt[] = {
#include "assets/int_iku_mario_taihou_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_mario_taihou_v[0x3C0 / sizeof(Vtx)];
#else
Vtx int_iku_mario_taihou_v[] = {
#include "assets/int_iku_mario_taihou_v.inc"
};
#endif

Gfx int_iku_mario_taihou_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_mario_taihou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_mario_taihou_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_mario_taihou_v, 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_mario_taihou_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 8, 10, 11, 9, 12, 13),
    gsSPNTriangles_5b(9, 13, 10, 14, 15, 16, 14, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 16, 12, 14, 17, 12, 17, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_mario_taihou_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_mario_taihou_v[20], 18, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 6, 9, 12, 9, 13, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_mario_taihou_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_mario_taihou_v[38], 22, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 4, 12, 13, 14, 12, 14, 15, 15, 0, 3),
    gsSPNTriangles_5b(15, 3, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_mario_taihou_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
