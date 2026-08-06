#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_roller_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_roller_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_roller_pal[] = {
#include "assets/int_iku_roller_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_g_tex_txt[0x80];
#else
u8 int_iku_roller_g_tex_txt[] = {
#include "assets/int_iku_roller_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_b_tex_txt[0x200];
#else
u8 int_iku_roller_b_tex_txt[] = {
#include "assets/int_iku_roller_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_e_tex_txt[0x80];
#else
u8 int_iku_roller_e_tex_txt[] = {
#include "assets/int_iku_roller_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_d_tex_txt[0x100];
#else
u8 int_iku_roller_d_tex_txt[] = {
#include "assets/int_iku_roller_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_c_tex_txt[0x100];
#else
u8 int_iku_roller_c_tex_txt[] = {
#include "assets/int_iku_roller_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_f_tex_txt[0x100];
#else
u8 int_iku_roller_f_tex_txt[] = {
#include "assets/int_iku_roller_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_roller_a_tex_txt[0x200];
#else
u8 int_iku_roller_a_tex_txt[] = {
#include "assets/int_iku_roller_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_roller_v[0x5D0 / sizeof(Vtx)];
#else
Vtx int_iku_roller_v[] = {
#include "assets/int_iku_roller_v.inc"
};
#endif

Gfx int_iku_roller_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_roller_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_roller_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_roller_v[6], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_roller_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 12, 15, 13, 15, 12, 14),
    gsSPVertex(&int_iku_roller_v[22], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(4, 7, 8, 4, 8, 5, 7, 9, 10, 7, 10, 8),
    gsSPNTriangles_5b(9, 11, 12, 9, 12, 10, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 13, 16, 17, 16, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(14, 19, 22, 14, 22, 15, 23, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_roller_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_roller_v[48], 29, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_roller_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 12, 13, 14, 12, 14, 15),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23),
    gsSPNTriangles_5b(9, 24, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_roller_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 25, 28, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_roller_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_roller_v[77], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(0, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_roller_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_roller_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_roller_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_roller_v, 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
