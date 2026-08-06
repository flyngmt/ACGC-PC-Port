#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_20_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_20_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_20_pal[] = {
#include "assets/tol_umb_20_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_20_kasa_tex_txt[0x400];
#else
u8 tol_umb_20_kasa_tex_txt[] = {
#include "assets/tol_umb_20_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_20_e_tex_txt[0x80];
#else
u8 tol_umb_20_e_tex_txt[] = {
#include "assets/tol_umb_20_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_20_v[0x280 / sizeof(Vtx)];
#else
Vtx tol_umb_20_v[] = {
#include "assets/tol_umb_20_v.inc"
};
#endif

Gfx kasa_umb20_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_20_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tol_umb_20_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_20_v, 12, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 3, 2, 5),
    gsSPNTriangles_5b(6, 3, 5, 3, 6, 7, 7, 4, 3, 2, 1, 5),
    gsSPNTriangles_5b(5, 1, 8, 9, 10, 11, 11, 6, 9, 5, 9, 6),
    gsSPNTriangles_5b(5, 8, 9, 10, 9, 8, 8, 1, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb20_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_20_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_umb_20_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_20_v[12], 28, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 4, 6, 9),
    gsSPNTriangles_5b(4, 9, 5, 10, 11, 12, 10, 12, 13, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 18, 19, 14, 16, 19),
    gsSPNTriangles_5b(14, 19, 15, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
