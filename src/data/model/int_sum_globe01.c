#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_globe01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_globe01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_globe01_pal[] = {
#include "assets/int_sum_globe01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_globe01_stand_tex_txt[0x100];
#else
u8 int_sum_globe01_stand_tex_txt[] = {
#include "assets/int_sum_globe01_stand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_globe01_standtop_tex_txt[0x80];
#else
u8 int_sum_globe01_standtop_tex_txt[] = {
#include "assets/int_sum_globe01_standtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_globe01_standside_tex_txt[0x200];
#else
u8 int_sum_globe01_standside_tex_txt[] = {
#include "assets/int_sum_globe01_standside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_globe01_map_tex_txt[0x400];
#else
u8 int_sum_globe01_map_tex_txt[] = {
#include "assets/int_sum_globe01_map_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_globe01_v[0x2B0 / sizeof(Vtx)];
#else
Vtx int_sum_globe01_v[] = {
#include "assets/int_sum_globe01_v.inc"
};
#endif

Gfx int_sum_globe01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_globe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_globe01_stand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_globe01_v, 14, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_globe01_standtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_globe01_standside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_globe01_map_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_globe01_v[14], 29, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 1, 3, 2, 4, 0, 5),
    gsSPNTriangles_5b(6, 0, 2, 7, 8, 1, 7, 9, 8, 10, 9, 7),
    gsSPNTriangles_5b(8, 11, 1, 1, 11, 3, 8, 12, 11, 8, 9, 13),
    gsSPNTriangles_5b(4, 10, 7, 14, 10, 15, 16, 9, 17, 18, 19, 17),
    gsSPNTriangles_5b(20, 18, 21, 21, 18, 17, 14, 9, 10, 17, 9, 14),
    gsSPNTriangles_5b(21, 17, 14, 22, 23, 24, 25, 23, 15, 22, 20, 21),
    gsSPNTriangles_5b(22, 21, 23, 23, 21, 14, 23, 14, 15, 26, 15, 4),
    gsSPNTriangles_5b(15, 10, 4, 27, 18, 28, 28, 18, 20, 4, 7, 0),
    gsSPNTriangles_5b(7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
