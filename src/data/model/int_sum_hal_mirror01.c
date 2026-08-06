#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_mirror01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_mirror01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_mirror01_pal[] = {
#include "assets/int_sum_hal_mirror01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_hal_mirror01_glass_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_hal_mirror01_glass_tex_rgb_ci4_pal[] = {
#include "assets/int_sum_hal_mirror01_glass_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_front_tex[0x100];
#else
u8 int_sum_hal_mirror01_front_tex[] = {
#include "assets/int_sum_hal_mirror01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_mirror_tex[0x300];
#else
u8 int_sum_hal_mirror01_mirror_tex[] = {
#include "assets/int_sum_hal_mirror01_mirror_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_top_tex[0x80];
#else
u8 int_sum_hal_mirror01_top_tex[] = {
#include "assets/int_sum_hal_mirror01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_hikite_tex[0x80];
#else
u8 int_sum_hal_mirror01_hikite_tex[] = {
#include "assets/int_sum_hal_mirror01_hikite_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_kuki_tex[0x80];
#else
u8 int_sum_hal_mirror01_kuki_tex[] = {
#include "assets/int_sum_hal_mirror01_kuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_side_tex[0x80];
#else
u8 int_sum_hal_mirror01_side_tex[] = {
#include "assets/int_sum_hal_mirror01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_mirror01_glass_tex[0x200];
#else
u8 int_sum_hal_mirror01_glass_tex[] = {
#include "assets/int_sum_hal_mirror01_glass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_mirror01_v[0x440 / sizeof(Vtx)];
#else
Vtx int_sum_hal_mirror01_v[] = {
#include "assets/int_sum_hal_mirror01_v.inc"
};
#endif

Gfx int_sum_hal_mirror01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_mirror01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_mirror01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_mirror01_v, 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 0, 4),
    gsSPNTriangles_5b(1, 4, 5, 6, 7, 5, 6, 5, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_mirror01_kuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 10, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_mirror01_hikite_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_hal_mirror01_v[18], 31, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(8, 3, 9, 10, 11, 12, 12, 0, 13, 2, 14, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_mirror01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(12, 15, 16, 17, 17, 16, 18, 17, 18, 19),
    gsSPNTriangles_5b(20, 21, 22, 20, 22, 23, 23, 22, 24, 23, 24, 25),
    gsSPNTriangles_5b(19, 18, 21, 19, 21, 20, 26, 27, 28, 26, 28, 29),
    gsSPNTriangles_5b(15, 30, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_hal_mirror01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_hal_mirror01_v[49], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_mirror01_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_mirror01_glass_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_mirror01_glass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_mirror01_v[54], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_mirror01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_mirror01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_hal_mirror01_mirror_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_mirror01_v[58], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 8, 9, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};
