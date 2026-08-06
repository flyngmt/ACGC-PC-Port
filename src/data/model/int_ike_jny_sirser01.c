#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_sirser01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_sirser01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_sirser01_pal[] = {
#include "assets/int_ike_jny_sirser01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserface_tex_txt[0x200];
#else
u8 int_ike_jny_sirserface_tex_txt[] = {
#include "assets/int_ike_jny_sirserface_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserear_tex_txt[0x80];
#else
u8 int_ike_jny_sirserear_tex_txt[] = {
#include "assets/int_ike_jny_sirserear_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserhead_tex_txt[0x100];
#else
u8 int_ike_jny_sirserhead_tex_txt[] = {
#include "assets/int_ike_jny_sirserhead_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserhair_tex_txt[0x100];
#else
u8 int_ike_jny_sirserhair_tex_txt[] = {
#include "assets/int_ike_jny_sirserhair_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserfoot_tex_txt[0x80];
#else
u8 int_ike_jny_sirserfoot_tex_txt[] = {
#include "assets/int_ike_jny_sirserfoot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirsertail_tex_txt[0x100];
#else
u8 int_ike_jny_sirsertail_tex_txt[] = {
#include "assets/int_ike_jny_sirsertail_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirserfoot2_tex_txt[0x80];
#else
u8 int_ike_jny_sirserfoot2_tex_txt[] = {
#include "assets/int_ike_jny_sirserfoot2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_sirser01_v[0x570 / sizeof(Vtx)];
#else
Vtx int_ike_jny_sirser01_v[] = {
#include "assets/int_ike_jny_sirser01_v.inc"
};
#endif

Gfx int_ike_jny_sirser01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_sirser01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_sirserface_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_sirser01_v, 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 5, 6, 1),
    gsSPNTriangles_5b(3, 2, 7, 8, 9, 10, 1, 6, 8, 1, 0, 5),
    gsSPNTriangles_5b(4, 0, 2, 10, 11, 7, 7, 8, 10, 9, 8, 6),
    gsSPNTriangles_5b(3, 7, 11, 8, 7, 2, 8, 2, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirserear_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 14, 15, 12, 16, 17, 18),
    gsSPNTriangles_5b(19, 13, 12, 18, 20, 16, 16, 20, 21, 21, 17, 16),
    gsSPNTriangles_5b(12, 15, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_sirserhead_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_jny_sirser01_v[22], 27, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 0, 3, 4, 1, 5),
    gsSPNTriangles_5b(2, 1, 4, 0, 2, 6, 7, 0, 6, 4, 6, 2),
    gsSPNTriangles_5b(1, 3, 8, 9, 3, 0, 5, 10, 4, 6, 11, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_sirserhair_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(13, 12, 13, 14, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 21, 22, 23, 24, 25, 12, 24, 12, 20),
    gsSPNTriangles_5b(14, 18, 17, 14, 17, 12, 20, 19, 24, 25, 13, 12),
    gsSPNTriangles_5b(26, 19, 21, 23, 26, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirserfoot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPVertex(&int_ike_jny_sirser01_v[49], 28, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 2, 1, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 6, 7, 8, 9, 6, 2, 3, 10, 9, 8),
    gsSPNTriangles_5b(4, 3, 1, 0, 9, 10, 11, 10, 8, 5, 4, 12),
    gsSPNTriangles_5b(11, 13, 10, 4, 14, 12, 2, 15, 9, 12, 6, 5),
    gsSPNTriangles_5b(16, 17, 10, 4, 18, 19, 19, 14, 4, 10, 13, 16),
    gsSPNTriangles_5b(10, 17, 0, 2, 9, 0, 1, 18, 4, 8, 7, 11),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_sirsertail_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 20, 21, 22, 20, 23, 24, 24, 25, 20),
    gsSPNTriangles_5b(26, 23, 22, 27, 21, 25, 21, 27, 22, 22, 23, 20),
    gsSPNTriangles_5b(22, 27, 26, 24, 23, 26, 25, 21, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirserfoot2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_sirser01_v[77], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 2, 6, 0),
    gsSPNTriangles_5b(7, 4, 3, 5, 8, 3, 2, 1, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};
