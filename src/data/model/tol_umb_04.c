#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_04_pal[] = {
#include "assets/tol_umb_04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_04_kasa1_tex_txt[0x100];
#else
u8 tol_umb_04_kasa1_tex_txt[] = {
#include "assets/tol_umb_04_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_04_kasa2_tex_txt[0x100];
#else
u8 tol_umb_04_kasa2_tex_txt[] = {
#include "assets/tol_umb_04_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_04_tuka_tex_txt[0x200];
#else
u8 tol_umb_04_tuka_tex_txt[] = {
#include "assets/tol_umb_04_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_04_v[0x380 / sizeof(Vtx)];
#else
Vtx tol_umb_04_v[] = {
#include "assets/tol_umb_04_v.inc"
};
#endif

Gfx kasa_umb04_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb_04_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_04_v, 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 10, 16, 17, 12),
    gsSPNTriangles_5b(6, 18, 19, 10, 9, 14, 12, 11, 16, 2, 4, 0),
    gsSPNTriangles_5b(19, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb_04_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 20, 21, 22, 22, 23, 20, 24, 23, 22),
    gsSPNTriangles_5b(25, 26, 27, 26, 28, 29, 29, 27, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb04_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_04_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_04_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};
