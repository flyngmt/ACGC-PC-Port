#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_botle01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_botle01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_botle01_pal[] = {
#include "assets/int_ike_jny_botle01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship1_tex_txt[0x40];
#else
u8 int_ike_jny_botleship1_tex_txt[] = {
#include "assets/int_ike_jny_botleship1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship3_tex_txt[0x40];
#else
u8 int_ike_jny_botleship3_tex_txt[] = {
#include "assets/int_ike_jny_botleship3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship2_tex_txt[0x40];
#else
u8 int_ike_jny_botleship2_tex_txt[] = {
#include "assets/int_ike_jny_botleship2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botlebase_tex_txt[0x80];
#else
u8 int_ike_jny_botlebase_tex_txt[] = {
#include "assets/int_ike_jny_botlebase_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botlebase2_tex_txt[0x40];
#else
u8 int_ike_jny_botlebase2_tex_txt[] = {
#include "assets/int_ike_jny_botlebase2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botlecap_tex_txt[0x40];
#else
u8 int_ike_jny_botlecap_tex_txt[] = {
#include "assets/int_ike_jny_botlecap_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship5_tex_txt[0xC0];
#else
u8 int_ike_jny_botleship5_tex_txt[] = {
#include "assets/int_ike_jny_botleship5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship4_tex_txt[0xC0];
#else
u8 int_ike_jny_botleship4_tex_txt[] = {
#include "assets/int_ike_jny_botleship4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botleship6_tex_txt[0xC0];
#else
u8 int_ike_jny_botleship6_tex_txt[] = {
#include "assets/int_ike_jny_botleship6_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_botle01_tex_rgb_ia8[0x400];
#else
u8 int_ike_jny_botle01_tex_rgb_ia8[] = {
#include "assets/int_ike_jny_botle01_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_botle01_v[0x8C0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_botle01_v[] = {
#include "assets/int_ike_jny_botle01_v.inc"
};
#endif

Gfx int_ike_jny_botle01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_botle01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botleship1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_botle01_v, 31, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 2, 13, 14, 2, 14, 0),
    gsSPNTriangles_5b(0, 3, 5, 5, 1, 0, 14, 13, 10, 12, 14, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botleship1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 15, 16, 17, 15, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 24, 25, 23, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botleship3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_botle01_v[31], 25, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botleship2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(3, 4, 5, 6, 4, 6, 7, 7, 8, 4),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_botlebase_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botlebase2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_botlebase_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_botle01_v[56], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botlebase2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_botlecap_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_botle01_v[72], 28, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(4, 8, 9, 5, 9, 10, 2, 11, 0, 8, 12, 13),
    gsSPNTriangles_5b(9, 13, 14, 12, 3, 6, 13, 6, 15, 6, 13, 12),
    gsSPNTriangles_5b(13, 9, 8, 5, 6, 3, 9, 5, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 92),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 92),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 92),
    gsSPVertex(&int_ike_jny_botle01_v[100], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 92),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 24, int_ike_jny_botleship6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_botle01_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0_ALPHA, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE,
                       0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(60, 170, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, int_ike_jny_botle01_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_botle01_v[120], 20, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 2, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(1, 8, 3, 7, 6, 9, 0, 10, 8, 11, 12, 13),
    gsSPNTriangles_5b(13, 14, 10, 12, 15, 14, 11, 4, 15, 16, 17, 15),
    gsSPNTriangles_5b(3, 8, 18, 10, 14, 19, 14, 15, 17, 19, 18, 8),
    gsSPNTriangles_5b(17, 19, 14, 4, 3, 16, 18, 16, 3, 8, 10, 19),
    gsSPNTriangles_5b(15, 4, 16, 2, 11, 0, 14, 13, 12, 15, 12, 11),
    gsSPNTriangles_5b(4, 11, 2, 3, 2, 1, 8, 1, 0, 10, 0, 13),
    gsSPNTriangles_5b(13, 0, 11, 5, 17, 16, 5, 16, 6, 6, 16, 18),
    gsSPNTriangles_5b(6, 18, 9, 9, 18, 19, 9, 19, 7, 7, 19, 17),
    gsSPNTriangles_5b(7, 17, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
