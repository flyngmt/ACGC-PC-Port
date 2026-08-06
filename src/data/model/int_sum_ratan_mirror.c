#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_ratan_mirror_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_mirror_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_mirror_pal[] = {
#include "assets/int_sum_ratan_mirror_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_ratan_mirror_grass_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_ratan_mirror_grass_tex_rgb_ci4_pal[] = {
#include "assets/int_sum_ratan_mirror_grass_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_table_tex[0x80];
#else
u8 int_sum_ratan_mirror_table_tex[] = {
#include "assets/int_sum_ratan_mirror_table_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_head_tex[0x100];
#else
u8 int_sum_ratan_mirror_head_tex[] = {
#include "assets/int_sum_ratan_mirror_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_front_tex[0x200];
#else
u8 int_sum_ratan_mirror_front_tex[] = {
#include "assets/int_sum_ratan_mirror_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_back_tex[0x200];
#else
u8 int_sum_ratan_mirror_back_tex[] = {
#include "assets/int_sum_ratan_mirror_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_side_tex[0x80];
#else
u8 int_sum_ratan_mirror_side_tex[] = {
#include "assets/int_sum_ratan_mirror_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_bin_tex[0x80];
#else
u8 int_sum_ratan_mirror_bin_tex[] = {
#include "assets/int_sum_ratan_mirror_bin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_mirror_grass_tex[0x100];
#else
u8 int_sum_ratan_mirror_grass_tex[] = {
#include "assets/int_sum_ratan_mirror_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_ratan_mirror_v[0x380 / sizeof(Vtx)];
#else
Vtx int_sum_ratan_mirror_v[] = {
#include "assets/int_sum_ratan_mirror_v.inc"
};
#endif

Gfx int_sum_ratan_mirror_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_mirror_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_ratan_mirror_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_ratan_mirror_v, 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 4, 10, 4, 7, 16, 17, 11),
    gsSPNTriangles_5b(16, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 5, 8, 9),
    gsSPNTriangles_5b(5, 9, 6, 12, 13, 14, 12, 14, 15, 16, 12, 15),
    gsSPNTriangles_5b(16, 15, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_ratan_mirror_table_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_ratan_mirror_v[18], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_ratan_mirror_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_mirror_grass_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_ratan_mirror_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_ratan_mirror_v[22], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_ratan_mirror_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_mirror_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_ratan_mirror_bin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_ratan_mirror_v[28], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_ratan_mirror_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_ratan_mirror_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 20, 21, 17),
    gsSPNTriangles_5b(20, 17, 16, 18, 22, 23, 18, 23, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_ratan_mirror_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
