#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_moai01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_moai01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_moai01_pal[] = {
#include "assets/int_ike_jny_moai01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_moai2_tex_txt[0x100];
#else
u8 int_ike_jny_moai2_tex_txt[] = {
#include "assets/int_ike_jny_moai2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_moai5_tex_txt[0x80];
#else
u8 int_ike_jny_moai5_tex_txt[] = {
#include "assets/int_ike_jny_moai5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_moai4_tex_txt[0x100];
#else
u8 int_ike_jny_moai4_tex_txt[] = {
#include "assets/int_ike_jny_moai4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_moai1_tex_txt[0x400];
#else
u8 int_ike_jny_moai1_tex_txt[] = {
#include "assets/int_ike_jny_moai1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_moai3_tex_txt[0x100];
#else
u8 int_ike_jny_moai3_tex_txt[] = {
#include "assets/int_ike_jny_moai3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_moai01_v[0x4D0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_moai01_v[] = {
#include "assets/int_ike_jny_moai01_v.inc"
};
#endif

Gfx int_ike_jny_moai01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_moai01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_moai2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_moai01_v, 21, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(5, 4, 7, 8, 9, 10, 11, 12, 13, 6, 5, 14),
    gsSPNTriangles_5b(7, 2, 1, 10, 9, 15, 16, 12, 11, 17, 3, 18),
    gsSPNTriangles_5b(3, 0, 18, 7, 17, 14, 3, 17, 7, 1, 3, 7),
    gsSPNTriangles_5b(7, 14, 5, 13, 8, 19, 8, 10, 19, 20, 6, 14),
    gsSPNTriangles_5b(13, 19, 11, 20, 14, 17, 18, 20, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_moai5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_moai01_v[21], 16, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 4, 5, 6, 7),
    gsSPNTriangles_5b(3, 8, 0, 2, 9, 4, 7, 6, 10, 7, 10, 11),
    gsSPNTriangles_5b(9, 5, 7, 3, 11, 12, 3, 12, 13, 5, 9, 14),
    gsSPNTriangles_5b(12, 11, 10, 9, 7, 4, 4, 7, 11, 4, 11, 3),
    gsSPNTriangles_5b(15, 14, 9, 15, 9, 2, 15, 2, 1, 8, 3, 13),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_moai4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_jny_moai01_v[37], 31, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(7, 6, 9, 10, 1, 11, 9, 6, 12, 13, 14, 3),
    gsSPNTriangles_5b(13, 3, 5, 5, 15, 7, 5, 7, 13, 15, 1, 8),
    gsSPNTriangles_5b(16, 12, 6, 9, 14, 13, 11, 1, 15, 9, 13, 7),
    gsSPNTriangles_5b(15, 5, 11, 1, 17, 18, 5, 4, 11, 7, 15, 8),
    gsSPNTriangles_5b(0, 2, 16, 16, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_16b, 32, 16, int_ike_jny_moai1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 19, 20, 21, 22, 23, 24, 20, 19, 25),
    gsSPNTriangles_5b(21, 26, 19, 21, 22, 27, 25, 28, 29, 25, 29, 30),
    gsSPNTriangles_5b(27, 26, 21, 24, 27, 22, 25, 30, 20, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_moai3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_jny_moai01_v[68], 9, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(5, 4, 1, 5, 1, 0, 7, 0, 2, 6, 5, 0),
    gsSPNTriangles_5b(6, 0, 7, 3, 6, 7, 3, 7, 8, 8, 7, 2),
    gsSPEndDisplayList(),
};
