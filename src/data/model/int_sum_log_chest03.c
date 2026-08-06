#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_log_chest03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chest03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chest03_pal[] = {
#include "assets/int_sum_log_chest03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_back_tex[0x100];
#else
u8 int_sum_log_chest03_back_tex[] = {
#include "assets/int_sum_log_chest03_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_front_tex[0x200];
#else
u8 int_sum_log_chest03_front_tex[] = {
#include "assets/int_sum_log_chest03_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_top_tex[0x100];
#else
u8 int_sum_log_chest03_top_tex[] = {
#include "assets/int_sum_log_chest03_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_top2_tex[0x80];
#else
u8 int_sum_log_chest03_top2_tex[] = {
#include "assets/int_sum_log_chest03_top2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_draw_tex[0x80];
#else
u8 int_sum_log_chest03_draw_tex[] = {
#include "assets/int_sum_log_chest03_draw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_side_tex[0x100];
#else
u8 int_sum_log_chest03_side_tex[] = {
#include "assets/int_sum_log_chest03_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_foot_tex[0x100];
#else
u8 int_sum_log_chest03_foot_tex[] = {
#include "assets/int_sum_log_chest03_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_book_tex[0x80];
#else
u8 int_sum_log_chest03_book_tex[] = {
#include "assets/int_sum_log_chest03_book_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chest03_book2_tex[0x80];
#else
u8 int_sum_log_chest03_book2_tex[] = {
#include "assets/int_sum_log_chest03_book2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_log_chest03_v[0x4C0 / sizeof(Vtx)];
#else
Vtx int_sum_log_chest03_v[] = {
#include "assets/int_sum_log_chest03_v.inc"
};
#endif

Gfx int_sum_log_chest03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_chest03_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_log_chest03_v, 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chest03_draw_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chest03_top2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_log_chest03_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_log_chest03_v[30], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_log_chest03_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_chest03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chest03_book2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_chest03_v[38], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chest03_book_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_chest03_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_log_chest03_v[52], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 4, 7, 9, 8, 7, 10, 8, 9),
    gsSPNTriangles_5b(11, 10, 9, 12, 10, 11, 13, 12, 11, 14, 15, 16),
    gsSPNTriangles_5b(14, 17, 15, 18, 17, 14, 18, 19, 17, 2, 19, 18),
    gsSPNTriangles_5b(2, 1, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_log_chest03_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
