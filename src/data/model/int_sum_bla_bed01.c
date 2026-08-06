#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bla_bed01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_bed01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_bed01_pal[] = {
#include "assets/int_sum_bla_bed01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_bed01_top_tex[0x300];
#else
u8 int_sum_bla_bed01_top_tex[] = {
#include "assets/int_sum_bla_bed01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_bed01_side_tex[0x80];
#else
u8 int_sum_bla_bed01_side_tex[] = {
#include "assets/int_sum_bla_bed01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_bed01_pillow_tex[0x100];
#else
u8 int_sum_bla_bed01_pillow_tex[] = {
#include "assets/int_sum_bla_bed01_pillow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_bed01_head_tex[0x180];
#else
u8 int_sum_bla_bed01_head_tex[] = {
#include "assets/int_sum_bla_bed01_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_bed01_headside_tex[0x100];
#else
u8 int_sum_bla_bed01_headside_tex[] = {
#include "assets/int_sum_bla_bed01_headside_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bla_bed01_v[0x310 / sizeof(Vtx)];
#else
Vtx int_sum_bla_bed01_v[] = {
#include "assets/int_sum_bla_bed01_v.inc"
};
#endif

Gfx int_sum_bla_bed01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bla_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bla_bed01_headside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bla_bed01_v, 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 4, 1, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 9, 5, 9, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_bla_bed01_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 10, 13, 11, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 17, 16, 18, 17, 18, 19, 18, 10, 19),
    gsSPNTriangles_5b(10, 12, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bla_bed01_pillow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_bla_bed01_v[20], 29, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(4, 1, 0, 5, 6, 7, 5, 7, 8, 5, 8, 9),
    gsSPNTriangles_5b(9, 6, 5, 10, 11, 12, 13, 10, 12, 14, 13, 12),
    gsSPNTriangles_5b(12, 11, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bla_bed01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 18, 19, 15, 18, 15, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_bla_bed01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 20, 21, 22, 23, 24, 20, 22, 23, 20),
    gsSPNTriangles_5b(25, 26, 21, 26, 22, 21, 23, 27, 24, 27, 28, 24),
    gsSPNTriangles_5b(24, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
