#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_chest01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chest01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chest01_pal[] = {
#include "assets/int_sum_hal_chest01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_back_tex[0x100];
#else
u8 int_sum_hal_chest01_back_tex[] = {
#include "assets/int_sum_hal_chest01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_front_tex[0x200];
#else
u8 int_sum_hal_chest01_front_tex[] = {
#include "assets/int_sum_hal_chest01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_top_tex[0x80];
#else
u8 int_sum_hal_chest01_top_tex[] = {
#include "assets/int_sum_hal_chest01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_intop_tex[0x80];
#else
u8 int_sum_hal_chest01_intop_tex[] = {
#include "assets/int_sum_hal_chest01_intop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_inback_tex[0x100];
#else
u8 int_sum_hal_chest01_inback_tex[] = {
#include "assets/int_sum_hal_chest01_inback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_kuki_tex[0x100];
#else
u8 int_sum_hal_chest01_kuki_tex[] = {
#include "assets/int_sum_hal_chest01_kuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest01_book_tex[0x100];
#else
u8 int_sum_hal_chest01_book_tex[] = {
#include "assets/int_sum_hal_chest01_book_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_chest01_v[0x430 / sizeof(Vtx)];
#else
Vtx int_sum_hal_chest01_v[] = {
#include "assets/int_sum_hal_chest01_v.inc"
};
#endif

Gfx int_sum_hal_chest01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_chest01_kuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_chest01_v, 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(8, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest01_intop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 18, 20, 21, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 22, 23, 24, 22, 24, 25, 28, 25, 24),
    gsSPNTriangles_5b(28, 24, 29, 18, 23, 22, 18, 22, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_chest01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_hal_chest01_book_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chest01_v[30], 21, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_chest01_inback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 16, 17, 18, 19, 20, 18, 20, 16, 18),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_chest01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chest01_v[51], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 1, 7, 8, 1, 3, 7, 3, 9, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_chest01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 11, 12, 13, 11, 14, 12, 14, 15, 12),
    gsSPEndDisplayList(),
};
