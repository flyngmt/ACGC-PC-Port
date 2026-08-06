#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_ham_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_ham_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_ham_pal[] = {
#include "assets/int_iku_ham_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ham_c_tex_txt[0x100];
#else
u8 int_iku_ham_c_tex_txt[] = {
#include "assets/int_iku_ham_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ham_e_tex_txt[0x80];
#else
u8 int_iku_ham_e_tex_txt[] = {
#include "assets/int_iku_ham_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ham_a_tex_txt[0x200];
#else
u8 int_iku_ham_a_tex_txt[] = {
#include "assets/int_iku_ham_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_ham_f_tex_txt[0x400];
#else
u8 int_iku_ham_f_tex_txt[] = {
#include "assets/int_iku_ham_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_ham_v[0x510 / sizeof(Vtx)];
#else
Vtx int_iku_ham_v[] = {
#include "assets/int_iku_ham_v.inc"
};
#endif

Gfx int_iku_ham_model_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_ham_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_ham_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_ham_v[46], 21, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 2, 3, 0, 3, 4, 1),
    gsSPNTriangles_5b(3, 5, 6, 7, 4, 3, 6, 7, 3, 2, 5, 3),
    gsSPNTriangles_5b(0, 3, 1, 8, 9, 10, 8, 11, 12, 13, 9, 8),
    gsSPNTriangles_5b(8, 12, 13, 14, 11, 8, 10, 14, 8, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 19, 20, 18, 19, 18, 17, 19, 17, 16),
    gsSPNTriangles_5b(15, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_ham_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_ham_v[67], 14, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_ham_model_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_ham_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_ham_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_ham_v, 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 6, 7, 8, 6, 9, 7, 6, 8, 10),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 13, 15, 16, 13, 16, 14),
    gsSPNTriangles_5b(17, 18, 19, 18, 20, 19, 21, 17, 19, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 24, 26, 27, 24, 27, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_ham_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_ham_v[28], 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};
