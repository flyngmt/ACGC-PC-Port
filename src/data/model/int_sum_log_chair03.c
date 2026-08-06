#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_log_chair03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chair03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chair03_pal[] = {
#include "assets/int_sum_log_chair03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair03_seat_tex[0x100];
#else
u8 int_sum_log_chair03_seat_tex[] = {
#include "assets/int_sum_log_chair03_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair03_seatside_tex[0x80];
#else
u8 int_sum_log_chair03_seatside_tex[] = {
#include "assets/int_sum_log_chair03_seatside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair03_head_tex[0x100];
#else
u8 int_sum_log_chair03_head_tex[] = {
#include "assets/int_sum_log_chair03_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair03_headtop_tex[0x80];
#else
u8 int_sum_log_chair03_headtop_tex[] = {
#include "assets/int_sum_log_chair03_headtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair03_foot_tex[0x100];
#else
u8 int_sum_log_chair03_foot_tex[] = {
#include "assets/int_sum_log_chair03_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_log_chair03_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_log_chair03_v[] = {
#include "assets/int_sum_log_chair03_v.inc"
};
#endif

Gfx int_sum_log_chair03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chair03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chair03_headtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_log_chair03_v, 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_chair03_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 9, 7, 8, 10, 11),
    gsSPNTriangles_5b(8, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_chair03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chair03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_chair03_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_chair03_v[12], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 10, 12, 10, 14, 15),
    gsSPNTriangles_5b(10, 15, 11, 14, 16, 17, 14, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(21, 18, 20, 21, 20, 22, 23, 21, 22, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_chair03_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_log_chair03_v[38], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 7),
    gsSPNTriangles_5b(13, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chair03_seatside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 15, 16, 17, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 24, 23, 25, 26, 25, 15, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
