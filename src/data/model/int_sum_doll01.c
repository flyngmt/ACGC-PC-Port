#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_doll01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_doll01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_doll01_pal[] = {
#include "assets/int_sum_doll01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_byubu_txt[0x80];
#else
u8 int_sum_doll01_byubu_txt[] = {
#include "assets/int_sum_doll01_byubu_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_hinadan_txt[0x180];
#else
u8 int_sum_doll01_hinadan_txt[] = {
#include "assets/int_sum_doll01_hinadan_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_hina_txt[0x100];
#else
u8 int_sum_doll01_hina_txt[] = {
#include "assets/int_sum_doll01_hina_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_dairi_txt[0x100];
#else
u8 int_sum_doll01_dairi_txt[] = {
#include "assets/int_sum_doll01_dairi_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_kanjyo_txt[0x100];
#else
u8 int_sum_doll01_kanjyo_txt[] = {
#include "assets/int_sum_doll01_kanjyo_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_gonin_txt[0x100];
#else
u8 int_sum_doll01_gonin_txt[] = {
#include "assets/int_sum_doll01_gonin_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_bonbori_txt[0x100];
#else
u8 int_sum_doll01_bonbori_txt[] = {
#include "assets/int_sum_doll01_bonbori_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll01_side_txt[0x100];
#else
u8 int_sum_doll01_side_txt[] = {
#include "assets/int_sum_doll01_side_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_doll01_v[0x580 / sizeof(Vtx)];
#else
Vtx int_sum_doll01_v[] = {
#include "assets/int_sum_doll01_v.inc"
};
#endif

Gfx int_sum_doll01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_doll01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_doll01_byubu_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_doll01_v, 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 4, 6, 5, 4, 7, 6, 7, 8, 6),
    gsSPNTriangles_5b(8, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_doll01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_doll01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_doll01_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_doll01_v[10], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll01_gonin_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll01_kanjyo_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_doll01_v[38], 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll01_dairi_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll01_hina_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_doll01_hinadan_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_doll01_v[58], 20, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(5, 3, 0, 6, 5, 4, 6, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 12, 9, 8, 12, 13, 9, 14, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 18, 15, 14, 18, 19, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_doll01_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_doll01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll01_bonbori_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_doll01_v[78], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
