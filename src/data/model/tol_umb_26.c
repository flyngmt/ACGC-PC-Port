#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_26_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_26_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_26_pal[] = {
#include "assets/tol_umb_26_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_26_kasa1_tex_txt[0x100];
#else
u8 tol_umb_26_kasa1_tex_txt[] = {
#include "assets/tol_umb_26_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_26_kasa2_tex_txt[0x200];
#else
u8 tol_umb_26_kasa2_tex_txt[] = {
#include "assets/tol_umb_26_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_26_tuka_tex_txt[0x200];
#else
u8 tol_umb_26_tuka_tex_txt[] = {
#include "assets/tol_umb_26_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_26_v[0x3C0 / sizeof(Vtx)];
#else
Vtx tol_umb_26_v[] = {
#include "assets/tol_umb_26_v.inc"
};
#endif

Gfx kasa_umb26_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_26_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb_26_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_26_v, 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 12),
    gsSPNTriangles_5b(19, 20, 21, 16, 22, 14, 12, 11, 17, 5, 7, 3),
    gsSPNTriangles_5b(21, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_26_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_umb_26_v[24], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 1, 3, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 9, 9, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb26_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_26_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_26_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_26_v[34], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};
