#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_pisa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_pisa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_pisa01_pal[] = {
#include "assets/int_ike_jny_pisa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisatop2_tex_txt[0x80];
#else
u8 int_ike_jny_pisatop2_tex_txt[] = {
#include "assets/int_ike_jny_pisatop2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisa2_tex_txt[0x100];
#else
u8 int_ike_jny_pisa2_tex_txt[] = {
#include "assets/int_ike_jny_pisa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisabase1_tex_txt[0x200];
#else
u8 int_ike_jny_pisabase1_tex_txt[] = {
#include "assets/int_ike_jny_pisabase1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisabase2_tex_txt[0x80];
#else
u8 int_ike_jny_pisabase2_tex_txt[] = {
#include "assets/int_ike_jny_pisabase2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisabase3_tex_txt[0x100];
#else
u8 int_ike_jny_pisabase3_tex_txt[] = {
#include "assets/int_ike_jny_pisabase3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisa3_tex_txt[0x100];
#else
u8 int_ike_jny_pisa3_tex_txt[] = {
#include "assets/int_ike_jny_pisa3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisa1_tex_txt[0x100];
#else
u8 int_ike_jny_pisa1_tex_txt[] = {
#include "assets/int_ike_jny_pisa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_pisatop1_tex_txt[0x80];
#else
u8 int_ike_jny_pisatop1_tex_txt[] = {
#include "assets/int_ike_jny_pisatop1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_pisa01_v[0x700 / sizeof(Vtx)];
#else
Vtx int_ike_jny_pisa01_v[] = {
#include "assets/int_ike_jny_pisa01_v.inc"
};
#endif

Gfx int_ike_jny_pisa01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_pisa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_pisatop2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_pisa01_v, 11, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(5, 3, 2, 4, 6, 2, 7, 5, 2, 8, 7, 2),
    gsSPNTriangles_5b(6, 9, 2, 10, 8, 2, 9, 10, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_pisa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_ike_jny_pisa01_v[11], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 4, 7, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 9, 15, 5, 16, 17, 5, 17, 6),
    gsSPNTriangles_5b(1, 14, 15, 18, 10, 13, 18, 13, 19, 1, 15, 2),
    gsSPNTriangles_5b(20, 18, 19, 20, 19, 21, 16, 20, 21, 16, 21, 17),
    gsSPNTriangles_5b(14, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_pisabase1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_pisabase2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_pisa01_v[37], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_pisabase3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_pisa3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 316, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_pisa01_v[57], 22, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 8, 6, 8, 9, 10, 11, 5),
    gsSPNTriangles_5b(10, 5, 4, 12, 13, 14, 12, 14, 15, 9, 8, 11),
    gsSPNTriangles_5b(9, 11, 10, 16, 17, 7, 16, 7, 6, 15, 14, 18),
    gsSPNTriangles_5b(15, 18, 19, 20, 21, 17, 20, 17, 16, 19, 18, 21),
    gsSPNTriangles_5b(19, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_pisa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 636),
    gsSPVertex(&int_ike_jny_pisa01_v[79], 22, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 1),
    gsSPNTriangles_5b(12, 1, 0, 14, 15, 5, 14, 5, 4, 7, 6, 16),
    gsSPNTriangles_5b(7, 16, 17, 3, 2, 9, 3, 9, 8, 18, 19, 15),
    gsSPNTriangles_5b(18, 15, 14, 20, 21, 19, 20, 19, 18, 17, 16, 13),
    gsSPNTriangles_5b(17, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_pisatop1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_pisa01_v[101], 11, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 4, 0, 5, 3),
    gsSPNTriangles_5b(6, 5, 0, 0, 7, 6, 8, 1, 0, 0, 4, 9),
    gsSPNTriangles_5b(9, 8, 0, 0, 2, 10, 0, 10, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};
