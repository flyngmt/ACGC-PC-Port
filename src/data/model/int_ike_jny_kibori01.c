#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_kibori01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_kibori01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_kibori01_pal[] = {
#include "assets/int_ike_jny_kibori01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_kiboribase_tex_txt[0x80];
#else
u8 int_ike_jny_kiboribase_tex_txt[] = {
#include "assets/int_ike_jny_kiboribase_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_kiboribody_tex_txt[0x200];
#else
u8 int_ike_jny_kiboribody_tex_txt[] = {
#include "assets/int_ike_jny_kiboribody_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_kiborineck_tex_txt[0x80];
#else
u8 int_ike_jny_kiborineck_tex_txt[] = {
#include "assets/int_ike_jny_kiborineck_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_kiboriface_tex_txt[0x200];
#else
u8 int_ike_jny_kiboriface_tex_txt[] = {
#include "assets/int_ike_jny_kiboriface_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_kiborifish_tex_txt[0x300];
#else
u8 int_ike_jny_kiborifish_tex_txt[] = {
#include "assets/int_ike_jny_kiborifish_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_kibori01_v[0xAA0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_kibori01_v[] = {
#include "assets/int_ike_jny_kibori01_v.inc"
};
#endif

Gfx int_ike_jny_kibori01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_kibori01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_kiboribase_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_kibori01_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_kiboribody_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPVertex(&int_ike_jny_kibori01_v[8], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(1, 9, 10, 11, 12, 5, 13, 4, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 23, 21, 23, 24, 25, 1, 26),
    gsSPNTriangles_5b(27, 4, 3, 10, 2, 1, 14, 4, 28, 29, 30, 31),
    gsSPVertex(&int_ike_jny_kibori01_v[40], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 6, 7, 8, 1, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(14, 11, 15, 16, 17, 18, 19, 10, 9, 20, 16, 21),
    gsSPNTriangles_5b(1, 4, 2, 22, 23, 24, 25, 26, 27, 7, 0, 27),
    gsSPNTriangles_5b(27, 24, 7, 24, 23, 28, 6, 8, 7, 26, 29, 27),
    gsSPNTriangles_5b(30, 31, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_kibori01_v[72], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 12, 13, 0, 3, 14),
    gsSPNTriangles_5b(15, 16, 13, 17, 18, 19, 20, 21, 22, 23, 24, 14),
    gsSPNTriangles_5b(23, 14, 3, 6, 25, 26, 27, 28, 29, 30, 31, 20),
    gsSPVertex(&int_ike_jny_kibori01_v[104], 18, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(8, 9, 10, 10, 9, 11, 12, 13, 0, 0, 14, 12),
    gsSPNTriangles_5b(8, 10, 13, 1, 0, 13, 1, 15, 16, 12, 14, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_kiborineck_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_kibori01_v[122], 16, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 2, 4, 9, 8, 11, 9, 11, 3),
    gsSPNTriangles_5b(12, 13, 1, 1, 11, 8, 0, 2, 10, 12, 1, 8),
    gsSPNTriangles_5b(5, 4, 14, 6, 9, 3, 14, 4, 15, 9, 6, 7),
    gsSPNTriangles_5b(11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_kiboriface_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_kibori01_v[138], 24, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 3, 2, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 3, 8, 9, 10, 11, 12, 0, 2, 13, 2, 3),
    gsSPNTriangles_5b(9, 12, 10, 14, 15, 16, 16, 17, 14, 11, 13, 9),
    gsSPNTriangles_5b(18, 19, 20, 4, 21, 5, 20, 22, 18, 3, 21, 13),
    gsSPNTriangles_5b(8, 3, 1, 6, 23, 4, 2, 13, 12, 7, 21, 3),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_ike_jny_kiborifish_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_kibori01_v[162], 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 5, 3, 2, 4, 1, 6, 1, 7, 6),
    gsSPNTriangles_5b(1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
