#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_amber_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_din_amber_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_din_amber_pal[] = {
#include "assets/int_din_amber_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_din_amber_4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_din_amber_4_tex_rgb_ci4_pal[] = {
#include "assets/int_din_amber_4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_amber_3_tex[0x200];
#else
u8 int_din_amber_3_tex[] = {
#include "assets/int_din_amber_3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_amber_1_tex[0x400];
#else
u8 int_din_amber_1_tex[] = {
#include "assets/int_din_amber_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_amber_2_tex[0x100];
#else
u8 int_din_amber_2_tex[] = {
#include "assets/int_din_amber_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_amber_5_tex[0x80];
#else
u8 int_din_amber_5_tex[] = {
#include "assets/int_din_amber_5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_amber_4_tex[0x80];
#else
u8 int_din_amber_4_tex[] = {
#include "assets/int_din_amber_4_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_amber_v[0x4E0 / sizeof(Vtx)];
#else
Vtx int_din_amber_v[] = {
#include "assets/int_din_amber_v.inc"
};
#endif

Gfx int_din_amber_on1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_amber_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_amber_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_amber_v, 27, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_din_amber_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_amber_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(5, 20, 21, 22, 20, 22, 23, 24, 20, 23),
    gsSPNTriangles_5b(24, 23, 25, 25, 26, 24, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_din_amber_v[27], 13, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(5, 6, 7, 8, 6, 8, 9, 8, 7, 10),
    gsSPNTriangles_5b(11, 10, 7, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_amber_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_amber_4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_amber_4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_din_amber_v[40], 32, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30),
    gsSPVertex(&int_din_amber_v[71], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_amber_on1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_amber_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_amber_5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_amber_v[74], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
