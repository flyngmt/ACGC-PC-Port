#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_whi_mirror_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_mirror_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_mirror_pal[] = {
#include "assets/int_sum_whi_mirror_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_whi_mirror_glass_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_whi_mirror_glass_tex_rgb_ci4_pal[] = {
#include "assets/int_sum_whi_mirror_glass_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_front_tex[0x180];
#else
u8 int_sum_whi_mirror_front_tex[] = {
#include "assets/int_sum_whi_mirror_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_side_tex[0x200];
#else
u8 int_sum_whi_mirror_side_tex[] = {
#include "assets/int_sum_whi_mirror_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_short_tex[0x80];
#else
u8 int_sum_whi_mirror_short_tex[] = {
#include "assets/int_sum_whi_mirror_short_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_mirror_tex[0x200];
#else
u8 int_sum_whi_mirror_mirror_tex[] = {
#include "assets/int_sum_whi_mirror_mirror_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_top_tex[0x100];
#else
u8 int_sum_whi_mirror_top_tex[] = {
#include "assets/int_sum_whi_mirror_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_up_tex[0x80];
#else
u8 int_sum_whi_mirror_up_tex[] = {
#include "assets/int_sum_whi_mirror_up_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_mirror_glass_tex[0x80];
#else
u8 int_sum_whi_mirror_glass_tex[] = {
#include "assets/int_sum_whi_mirror_glass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_whi_mirror_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_whi_mirror_v[] = {
#include "assets/int_sum_whi_mirror_v.inc"
};
#endif

Gfx int_sum_whi_mirror_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_mirror_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_mirror_up_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_whi_mirror_v, 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_mirror_short_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 13, 12, 14, 13, 14, 15, 16, 17, 15),
    gsSPNTriangles_5b(16, 15, 14, 18, 19, 20, 18, 20, 21, 19, 18, 7),
    gsSPNTriangles_5b(19, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_whi_mirror_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_mirror_glass_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_mirror_glass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_mirror_v[22], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_whi_mirror_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_mirror_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_whi_mirror_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_mirror_v[26], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_whi_mirror_mirror_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_whi_mirror_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_whi_mirror_v[50], 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 6, 7, 5, 6, 5, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_whi_mirror_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};
