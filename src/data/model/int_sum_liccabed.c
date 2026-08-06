#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_liccabed_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_liccabed_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_liccabed_pal[] = {
#include "assets/int_sum_liccabed_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccabed_mat_tex[0x300];
#else
u8 int_sum_liccabed_mat_tex[] = {
#include "assets/int_sum_liccabed_mat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccabed_head_tex[0x200];
#else
u8 int_sum_liccabed_head_tex[] = {
#include "assets/int_sum_liccabed_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccabed_foot_tex[0x80];
#else
u8 int_sum_liccabed_foot_tex[] = {
#include "assets/int_sum_liccabed_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccabed_pillow_tex[0x100];
#else
u8 int_sum_liccabed_pillow_tex[] = {
#include "assets/int_sum_liccabed_pillow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_liccabed_v[0x400 / sizeof(Vtx)];
#else
Vtx int_sum_liccabed_v[] = {
#include "assets/int_sum_liccabed_v.inc"
};
#endif

Gfx int_sum_liccabed_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccabed_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccabed_pillow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_liccabed_v, 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 0, 2, 3),
    gsSPNTriangles_5b(0, 4, 1, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_liccabed_mat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 9, 11, 12, 13, 14, 15),
    gsSPNTriangles_5b(13, 12, 14, 12, 11, 14, 11, 15, 14, 13, 15, 16),
    gsSPNTriangles_5b(13, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_liccabed_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccabed_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_liccabed_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccabed_v[18], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 13, 14, 12, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_liccabed_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_liccabed_v[38], 26, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 8, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 15, 16, 13, 17, 18, 19, 17, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 0, 25, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
