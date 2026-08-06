#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_wc01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_wc01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_wc01_pal[] = {
#include "assets/int_sum_wc01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_wc01_mizu_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_wc01_mizu_tex_rgb_ci4_pal[] = {
#include "assets/int_sum_wc01_mizu_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_tankfront_tex[0x100];
#else
u8 int_sum_wc01_tankfront_tex[] = {
#include "assets/int_sum_wc01_tankfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_huta_tex[0x100];
#else
u8 int_sum_wc01_huta_tex[] = {
#include "assets/int_sum_wc01_huta_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_tanktop_tex[0x80];
#else
u8 int_sum_wc01_tanktop_tex[] = {
#include "assets/int_sum_wc01_tanktop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_jyaguchi_tex[0x80];
#else
u8 int_sum_wc01_jyaguchi_tex[] = {
#include "assets/int_sum_wc01_jyaguchi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_tankrevar_tex[0x40];
#else
u8 int_sum_wc01_tankrevar_tex[] = {
#include "assets/int_sum_wc01_tankrevar_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_paip_tex[0x80];
#else
u8 int_sum_wc01_paip_tex[] = {
#include "assets/int_sum_wc01_paip_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_paipside_tex[0x80];
#else
u8 int_sum_wc01_paipside_tex[] = {
#include "assets/int_sum_wc01_paipside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_base_tex[0x100];
#else
u8 int_sum_wc01_base_tex[] = {
#include "assets/int_sum_wc01_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_benza_tex[0x100];
#else
u8 int_sum_wc01_benza_tex[] = {
#include "assets/int_sum_wc01_benza_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_benzaside_tex[0x80];
#else
u8 int_sum_wc01_benzaside_tex[] = {
#include "assets/int_sum_wc01_benzaside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_benzafront_tex[0x80];
#else
u8 int_sum_wc01_benzafront_tex[] = {
#include "assets/int_sum_wc01_benzafront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc01_mizu_tex[0x40];
#else
u8 int_sum_wc01_mizu_tex[] = {
#include "assets/int_sum_wc01_mizu_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_wc01_v[0x500 / sizeof(Vtx)];
#else
Vtx int_sum_wc01_v[] = {
#include "assets/int_sum_wc01_v.inc"
};
#endif

Gfx int_sum_wc01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc01_tanktop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_wc01_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_wc01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc01_benzafront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc01_v[5], 28, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc01_benzaside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 6, 5, 4, 7, 5, 8),
    gsSPNTriangles_5b(5, 7, 9, 5, 10, 11, 10, 5, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc01_benza_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 12, 13, 14, 15, 14, 13, 15, 16, 14),
    gsSPNTriangles_5b(12, 14, 17, 14, 18, 17, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc01_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 19, 22, 23, 23, 24, 25),
    gsSPNTriangles_5b(25, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_wc01_paipside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc01_v[33], 29, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_wc01_paip_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc01_tankrevar_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc01_jyaguchi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 21, 22, 23, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc01_huta_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 24, 25, 26, 24, 27, 25, 28, 24, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc01_tankfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc01_v[62], 14, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_wc01_envT_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc01_mizu_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc01_mizu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 4),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc01_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
