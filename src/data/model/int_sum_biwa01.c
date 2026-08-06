#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_biwa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_biwa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_biwa01_pal[] = {
#include "assets/int_sum_biwa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_front_tex[0x200];
#else
u8 int_sum_biwa01_front_tex[] = {
#include "assets/int_sum_biwa01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_nec_tex[0x100];
#else
u8 int_sum_biwa01_nec_tex[] = {
#include "assets/int_sum_biwa01_nec_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_back_tex[0x80];
#else
u8 int_sum_biwa01_back_tex[] = {
#include "assets/int_sum_biwa01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_necback_tex[0x80];
#else
u8 int_sum_biwa01_necback_tex[] = {
#include "assets/int_sum_biwa01_necback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_head_tex[0x80];
#else
u8 int_sum_biwa01_head_tex[] = {
#include "assets/int_sum_biwa01_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_headtop_tex[0x80];
#else
u8 int_sum_biwa01_headtop_tex[] = {
#include "assets/int_sum_biwa01_headtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_headfront_tex[0x40];
#else
u8 int_sum_biwa01_headfront_tex[] = {
#include "assets/int_sum_biwa01_headfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_stand_tex[0x100];
#else
u8 int_sum_biwa01_stand_tex[] = {
#include "assets/int_sum_biwa01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_biwa01_standhand_tex[0x80];
#else
u8 int_sum_biwa01_standhand_tex[] = {
#include "assets/int_sum_biwa01_standhand_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_biwa01_v[0x410 / sizeof(Vtx)];
#else
Vtx int_sum_biwa01_v[] = {
#include "assets/int_sum_biwa01_v.inc"
};
#endif

Gfx int_sum_biwa01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_biwa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_biwa01_headfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_biwa01_v, 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_biwa01_headtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 9, 6, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_biwa01_necback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 10, 11, 12, 13, 11, 14, 15, 16, 14),
    gsSPNTriangles_5b(16, 13, 14, 11, 17, 12, 11, 13, 17, 14, 10, 18),
    gsSPNTriangles_5b(14, 11, 10, 15, 14, 18, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_biwa01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 19, 20, 21, 20, 22, 21, 23, 19, 24),
    gsSPNTriangles_5b(23, 25, 19, 26, 19, 25, 26, 20, 19, 19, 21, 24),
    gsSPNTriangles_5b(21, 27, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_biwa01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_biwa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_biwa01_standhand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_biwa01_v[28], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_biwa01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 4, 5, 6, 7, 8, 9, 8, 10, 9),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_biwa01_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 11, 12, 13, 14, 15, 16, 14, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 21, 24, 25, 26, 27, 28, 26),
    gsSPNTriangles_5b(11, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_biwa01_nec_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_biwa01_v[59], 6, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_biwa01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
