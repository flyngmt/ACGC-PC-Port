#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_jack_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_jack_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_jack_pal[] = {
#include "assets/int_iku_jack_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_jack_a_tex_txt[0x80];
#else
u8 int_iku_jack_a_tex_txt[] = {
#include "assets/int_iku_jack_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_jack_b_tex_txt[0x400];
#else
u8 int_iku_jack_b_tex_txt[] = {
#include "assets/int_iku_jack_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_jack_d_tex_txt[0x100];
#else
u8 int_iku_jack_d_tex_txt[] = {
#include "assets/int_iku_jack_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_jack_c_tex_txt[0x80];
#else
u8 int_iku_jack_c_tex_txt[] = {
#include "assets/int_iku_jack_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_jack_e_tex_txt[0x200];
#else
u8 int_iku_jack_e_tex_txt[] = {
#include "assets/int_iku_jack_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_jack_v[0x3C0 / sizeof(Vtx)];
#else
Vtx int_iku_jack_v[] = {
#include "assets/int_iku_jack_v.inc"
};
#endif

Gfx int_iku_jack_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_jack_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_jack_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_jack_v, 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_jack_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_jack_v[10], 31, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 6, 7, 8, 6, 8, 9, 10, 6, 9),
    gsSPNTriangles_5b(11, 12, 13, 4, 14, 15, 4, 15, 5, 13, 16, 11),
    gsSPNTriangles_5b(17, 13, 12, 7, 18, 8, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 26, 25, 27, 26, 27, 28),
    gsSPNTriangles_5b(22, 21, 29, 22, 29, 30, 30, 29, 20, 30, 20, 19),
    gsSPNTriangles_5b(28, 27, 24, 28, 24, 23, 30, 26, 28, 30, 28, 22),
    gsSPNTriangles_5b(19, 23, 26, 19, 26, 30, 22, 28, 23, 22, 23, 19),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_jack_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_jack_v[41], 19, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_jack_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_jack_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 9, 10, 11, 11, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 16, 17, 18, 11, 13, 13, 15, 18, 15, 14, 16),
    gsSPNTriangles_5b(18, 17, 9, 17, 18, 15, 11, 18, 9, 12, 13, 11),
    gsSPNTriangles_5b(14, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
