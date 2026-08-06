#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_bugzapper_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_bugzapper_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_bugzapper_pal[] = {
#include "assets/int_iku_bugzapper_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_bugzapper_d_tex_txt[0x100];
#else
u8 int_iku_bugzapper_d_tex_txt[] = {
#include "assets/int_iku_bugzapper_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_bugzapper_c_tex_txt[0x400];
#else
u8 int_iku_bugzapper_c_tex_txt[] = {
#include "assets/int_iku_bugzapper_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_bugzapper_a_tex_txt[0x80];
#else
u8 int_iku_bugzapper_a_tex_txt[] = {
#include "assets/int_iku_bugzapper_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_bugzapper_e_tex_txt[0x100];
#else
u8 int_iku_bugzapper_e_tex_txt[] = {
#include "assets/int_iku_bugzapper_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_bugzapper_v[0x400 / sizeof(Vtx)];
#else
Vtx int_iku_bugzapper_v[] = {
#include "assets/int_iku_bugzapper_v.inc"
};
#endif

Gfx int_iku_bugzapper_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_bugzapper_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_bugzapper_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_bugzapper_v, 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 2, 3, 0),
    gsSPNTriangles_5b(4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_bugzapper_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(18, 5, 6, 7, 5, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 10, 13, 14, 10, 14, 11, 15, 5, 8),
    gsSPNTriangles_5b(15, 8, 16, 17, 12, 11, 17, 11, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 24, 25, 23, 25, 26, 25, 27, 28),
    gsSPNTriangles_5b(25, 28, 26, 29, 19, 22, 29, 22, 30, 0, 0, 0),
    gsSPVertex(&int_iku_bugzapper_v[31], 25, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(11, 8, 9, 10, 8, 10, 11, 9, 12, 13),
    gsSPNTriangles_5b(9, 13, 10, 12, 14, 15, 12, 15, 13, 14, 8, 11),
    gsSPNTriangles_5b(14, 11, 15, 11, 10, 13, 11, 13, 15, 16, 17, 18),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_bugzapper_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_bugzapper_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_bugzapper_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_bugzapper_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_bugzapper_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_bugzapper_v[56], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
