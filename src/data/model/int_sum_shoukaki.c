#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_shoukaki_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_shoukaki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_shoukaki_pal[] = {
#include "assets/int_sum_shoukaki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_front_tex_txt[0x200];
#else
u8 int_sum_shoukaki_front_tex_txt[] = {
#include "assets/int_sum_shoukaki_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_cupside_tex_txt[0x80];
#else
u8 int_sum_shoukaki_cupside_tex_txt[] = {
#include "assets/int_sum_shoukaki_cupside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_tube_tex_txt[0x100];
#else
u8 int_sum_shoukaki_tube_tex_txt[] = {
#include "assets/int_sum_shoukaki_tube_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_grip_tex_txt[0x80];
#else
u8 int_sum_shoukaki_grip_tex_txt[] = {
#include "assets/int_sum_shoukaki_grip_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_pull_tex_txt[0x80];
#else
u8 int_sum_shoukaki_pull_tex_txt[] = {
#include "assets/int_sum_shoukaki_pull_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_griptop_tex_txt[0x80];
#else
u8 int_sum_shoukaki_griptop_tex_txt[] = {
#include "assets/int_sum_shoukaki_griptop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_shoukaki_gripdown_tex_txt[0x80];
#else
u8 int_sum_shoukaki_gripdown_tex_txt[] = {
#include "assets/int_sum_shoukaki_gripdown_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_shoukaki_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_shoukaki_v[] = {
#include "assets/int_sum_shoukaki_v.inc"
};
#endif

Gfx int_sum_shoukaki_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_shoukaki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_shoukaki_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_shoukaki_v, 24, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 8, 4, 7, 7, 9, 8, 10, 7, 6),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 15, 16, 12, 15, 12, 11),
    gsSPNTriangles_5b(17, 18, 16, 17, 16, 15, 19, 20, 9, 19, 1, 20),
    gsSPNTriangles_5b(19, 2, 1, 21, 6, 3, 21, 3, 22, 23, 7, 10),
    gsSPNTriangles_5b(23, 9, 7, 10, 6, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_shoukaki_cupside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 188, 60),
    gsSPVertex(&int_sum_shoukaki_v[24], 25, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 5, 0),
    gsSPNTriangles_5b(3, 7, 8, 0, 9, 6, 8, 4, 3, 5, 6, 3),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_shoukaki_tube_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_shoukaki_grip_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 16, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_shoukaki_pull_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_shoukaki_griptop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_shoukaki_v[49], 17, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_shoukaki_gripdown_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 14, 15, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};
