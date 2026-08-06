#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_27_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_27_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_27_pal[] = {
#include "assets/tol_umb_27_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_27_kasa1_tex_txt[0x200];
#else
u8 tol_umb_27_kasa1_tex_txt[] = {
#include "assets/tol_umb_27_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_27_kasa2_tex_txt[0x200];
#else
u8 tol_umb_27_kasa2_tex_txt[] = {
#include "assets/tol_umb_27_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_27_e_tex_txt[0x80];
#else
u8 tol_umb_27_e_tex_txt[] = {
#include "assets/tol_umb_27_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_27_v[0x4B0 / sizeof(Vtx)];
#else
Vtx tol_umb_27_v[] = {
#include "assets/tol_umb_27_v.inc"
};
#endif

Gfx kasa_umb27_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_27_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_27_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_27_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(1, 5, 2, 5, 6, 2, 6, 4, 2, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(22, 23, 24, 25, 26, 27, 25, 28, 26, 25, 27, 29),
    gsSPNTriangles_5b(25, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_umb_27_v[31], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 6, 0, 7, 4, 0, 8, 7, 0, 2, 9),
    gsSPNTriangles_5b(0, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_27_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb27_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_27_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_umb_27_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_27_v[59], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
