#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_orange_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_orange_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_orange_pal[] = {
#include "assets/int_iku_orange_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_orange_b_tex_txt[0x200];
#else
u8 int_iku_orange_b_tex_txt[] = {
#include "assets/int_iku_orange_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_orange_a_tex_txt[0x200];
#else
u8 int_iku_orange_a_tex_txt[] = {
#include "assets/int_iku_orange_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_orange_c_tex_txt[0x400];
#else
u8 int_iku_orange_c_tex_txt[] = {
#include "assets/int_iku_orange_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_orange_v[0x240 / sizeof(Vtx)];
#else
Vtx int_iku_orange_v[] = {
#include "assets/int_iku_orange_v.inc"
};
#endif

Gfx int_iku_orange_model_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_orange_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_orange_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_orange_v[12], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_iku_orange_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 4, 5, 6, 4, 6, 7, 5, 8, 9),
    gsSPNTriangles_5b(5, 9, 6, 10, 11, 12, 10, 12, 13, 11, 14, 15),
    gsSPNTriangles_5b(11, 15, 12, 16, 4, 7, 16, 7, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 16, 17, 22, 17, 23, 19, 10, 13),
    gsSPNTriangles_5b(19, 13, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_orange_model_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_orange_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_orange_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_orange_v, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 0, 3, 8, 3, 9, 5, 10, 11),
    gsSPNTriangles_5b(5, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
