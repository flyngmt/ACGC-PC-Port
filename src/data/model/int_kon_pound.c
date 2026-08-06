#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_pound_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_pound_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_pound_pal[] = {
#include "assets/int_kon_pound_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_kon_pound_suimen_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_kon_pound_suimen_tex_rgb_ci4_pal[] = {
#include "assets/int_kon_pound_suimen_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_pound_rock_tex[0x200];
#else
u8 int_kon_pound_rock_tex[] = {
#include "assets/int_kon_pound_rock_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_pound_gl_tex[0x200];
#else
u8 int_kon_pound_gl_tex[] = {
#include "assets/int_kon_pound_gl_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_pound_soko_tex[0x80];
#else
u8 int_kon_pound_soko_tex[] = {
#include "assets/int_kon_pound_soko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_pound_flo_tex[0x200];
#else
u8 int_kon_pound_flo_tex[] = {
#include "assets/int_kon_pound_flo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_pound_suimen_tex[0x80];
#else
u8 int_kon_pound_suimen_tex[] = {
#include "assets/int_kon_pound_suimen_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_pound_v[0x420 / sizeof(Vtx)];
#else
Vtx int_kon_pound_v[] = {
#include "assets/int_kon_pound_v.inc"
};
#endif

Gfx int_kon_pound_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_pound_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_pound_soko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_pound_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPEndDisplayList(),
};

Gfx int_kon_pound_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_pound_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_pound_flo_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_pound_v[5], 13, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 3, 1, 5, 6, 7, 8, 5, 7, 7, 6, 9),
    gsSPNTriangles_5b(8, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_pound_gl_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_pound_rock_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_pound_v[18], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(19, 21, 20, 22, 23, 24, 6, 25, 26, 6, 26, 7),
    gsSPNTriangles_5b(9, 26, 27, 9, 27, 10, 3, 28, 25, 3, 25, 4),
    gsSPNTriangles_5b(0, 29, 28, 0, 28, 1, 12, 27, 30, 12, 30, 13),
    gsSPNTriangles_5b(15, 30, 31, 15, 31, 16, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_kon_pound_v[50], 9, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 1, 8, 6, 8, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_pound_alphaT_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_pound_suimen_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_pound_suimen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_pound_v[59], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
