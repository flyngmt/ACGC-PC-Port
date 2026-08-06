#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_21_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_21_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_21_pal[] = {
#include "assets/tol_umb_21_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_21_kasa_tex_txt[0x400];
#else
u8 tol_umb_21_kasa_tex_txt[] = {
#include "assets/tol_umb_21_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_21_tuka_tex_txt[0x200];
#else
u8 tol_umb_21_tuka_tex_txt[] = {
#include "assets/tol_umb_21_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_21_v[0x380 / sizeof(Vtx)];
#else
Vtx tol_umb_21_v[] = {
#include "assets/tol_umb_21_v.inc"
};
#endif

Gfx kasa_umb21_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_21_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_umb_21_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_21_v, 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 0, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 4, 2, 7, 8, 2, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(11, 10, 2, 13, 14, 2, 14, 13, 15, 16, 17, 18),
    gsSPNTriangles_5b(17, 16, 2, 19, 20, 21, 20, 19, 22, 23, 19, 24),
    gsSPNTriangles_5b(21, 24, 19, 21, 25, 26, 27, 26, 25, 24, 26, 28),
    gsSPNTriangles_5b(26, 24, 21, 29, 25, 21, 25, 29, 30, 31, 29, 20),
    gsSPNTriangles_5b(21, 20, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb21_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_21_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_21_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_21_v[32], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 3, 8, 3, 2, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
