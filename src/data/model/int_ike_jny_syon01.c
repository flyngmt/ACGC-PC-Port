#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_syon01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_ike_jny_syon01_tex[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 int_ike_jny_syon01_tex[] = {
#include "assets/int_ike_jny_syon01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonfoot2_tex_txt[0x100];
#else
u8 int_ike_jny_syonfoot2_tex_txt[] = {
#include "assets/int_ike_jny_syonfoot2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonfoot1_tex_txt[0x100];
#else
u8 int_ike_jny_syonfoot1_tex_txt[] = {
#include "assets/int_ike_jny_syonfoot1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonbody2_tex_txt[0x200];
#else
u8 int_ike_jny_syonbody2_tex_txt[] = {
#include "assets/int_ike_jny_syonbody2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonhead_tex_txt[0x100];
#else
u8 int_ike_jny_syonhead_tex_txt[] = {
#include "assets/int_ike_jny_syonhead_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonbody1_tex_txt[0x200];
#else
u8 int_ike_jny_syonbody1_tex_txt[] = {
#include "assets/int_ike_jny_syonbody1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonface_tex_txt[0x100];
#else
u8 int_ike_jny_syonface_tex_txt[] = {
#include "assets/int_ike_jny_syonface_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonwater1_pic_i4[0x200];
#else
u8 int_ike_jny_syonwater1_pic_i4[] = {
#include "assets/int_ike_jny_syonwater1_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_syonwater2_pic_i4[0x200];
#else
u8 int_ike_jny_syonwater2_pic_i4[] = {
#include "assets/int_ike_jny_syonwater2_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_syon01_v[0x6C0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_syon01_v[] = {
#include "assets/int_ike_jny_syon01_v.inc"
};
#endif

Gfx int_ike_jny_syon01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_syon01_tex),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_syonfoot2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_syon01_v, 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_syonfoot1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 18, 23, 24, 15),
    gsSPNTriangles_5b(23, 15, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_syonfoot1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_syonfoot2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_syon01_v[30], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_syonbody2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(27, 4, 5, 6, 7, 5, 4, 7, 4, 8),
    gsSPNTriangles_5b(6, 5, 9, 9, 5, 7, 10, 11, 12, 13, 14, 8),
    gsSPNTriangles_5b(8, 14, 15, 16, 9, 12, 11, 16, 12, 4, 17, 13),
    gsSPNTriangles_5b(18, 16, 11, 18, 19, 9, 16, 18, 9, 7, 20, 21),
    gsSPNTriangles_5b(20, 7, 8, 12, 7, 21, 4, 13, 8, 6, 9, 19),
    gsSPNTriangles_5b(6, 22, 17, 21, 20, 15, 21, 15, 10, 15, 20, 8),
    gsSPNTriangles_5b(12, 21, 10, 7, 12, 9, 17, 4, 6, 19, 23, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_syonhead_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_jny_syon01_v[54], 30, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 1, 6, 2),
    gsSPNTriangles_5b(3, 7, 8, 5, 4, 9, 7, 3, 5, 8, 0, 3),
    gsSPNTriangles_5b(4, 10, 11, 11, 9, 4, 11, 10, 6, 10, 4, 3),
    gsSPNTriangles_5b(10, 3, 0, 6, 10, 2, 0, 2, 10, 1, 0, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_syonbody1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(22, 12, 13, 14, 15, 16, 12, 17, 18, 19),
    gsSPNTriangles_5b(20, 21, 22, 12, 23, 21, 21, 23, 18, 18, 17, 24),
    gsSPNTriangles_5b(19, 25, 17, 24, 26, 22, 12, 20, 13, 23, 19, 18),
    gsSPNTriangles_5b(18, 24, 22, 19, 23, 16, 16, 27, 19, 22, 28, 20),
    gsSPNTriangles_5b(12, 16, 23, 16, 15, 27, 12, 21, 20, 29, 15, 12),
    gsSPNTriangles_5b(12, 14, 29, 22, 21, 18, 28, 13, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_syonfoot1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_syon01_v[84], 18, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 0, 5, 6),
    gsSPNTriangles_5b(2, 7, 0, 1, 0, 6, 5, 0, 3, 7, 3, 0),
    gsSPNTriangles_5b(6, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_syonface_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 9, 10, 11, 11, 12, 13, 14, 15, 10),
    gsSPNTriangles_5b(10, 9, 14, 12, 10, 16, 17, 9, 11, 12, 11, 10),
    gsSPNTriangles_5b(9, 17, 14, 15, 16, 10, 11, 13, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_syon01_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetEnvColor(130, 100, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, int_ike_jny_syonwater1_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, int_ike_jny_syonwater2_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_syon01_v[102], 6, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 5, 3),
    gsSPNTriangles_5b(0, 4, 3, 2, 5, 4, 2, 4, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
