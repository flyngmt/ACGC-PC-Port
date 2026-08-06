#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_liccasofa_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_liccasofa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_liccasofa_pal[] = {
#include "assets/int_sum_liccasofa_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccasofa_front_txt[0x400];
#else
u8 int_sum_liccasofa_front_txt[] = {
#include "assets/int_sum_liccasofa_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccasofa_back_txt[0x100];
#else
u8 int_sum_liccasofa_back_txt[] = {
#include "assets/int_sum_liccasofa_back_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccasofa_side_txt[0x180];
#else
u8 int_sum_liccasofa_side_txt[] = {
#include "assets/int_sum_liccasofa_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccasofa_frontside_txt[0x100];
#else
u8 int_sum_liccasofa_frontside_txt[] = {
#include "assets/int_sum_liccasofa_frontside_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccasofa_backside_txt[0x80];
#else
u8 int_sum_liccasofa_backside_txt[] = {
#include "assets/int_sum_liccasofa_backside_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_liccasofa_v[0x3A0 / sizeof(Vtx)];
#else
Vtx int_sum_liccasofa_v[] = {
#include "assets/int_sum_liccasofa_v.inc"
};
#endif

Gfx int_sum_liccasofa_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccasofa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_liccasofa_backside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_liccasofa_v, 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccasofa_frontside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_liccasofa_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_liccasofa_v[24], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 8, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 1),
    gsSPNTriangles_5b(18, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccasofa_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_liccasofa_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_liccasofa_v[48], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 5, 4, 7),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
