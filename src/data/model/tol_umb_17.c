#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_17_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_17_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_17_pal[] = {
#include "assets/tol_umb_17_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_17_kasa_tex_txt[0x200];
#else
u8 tol_umb_17_kasa_tex_txt[] = {
#include "assets/tol_umb_17_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_17_tuka_tex_txt[0x200];
#else
u8 tol_umb_17_tuka_tex_txt[] = {
#include "assets/tol_umb_17_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_17_v[0x4D0 / sizeof(Vtx)];
#else
Vtx tol_umb_17_v[] = {
#include "assets/tol_umb_17_v.inc"
};
#endif

Gfx kasa_umb17_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_17_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_17_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_17_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 8),
    gsSPNTriangles_5b(2, 1, 20, 21, 22, 17, 23, 24, 14, 11, 10, 25),
    gsSPNTriangles_5b(26, 27, 5, 5, 27, 28, 28, 3, 5, 8, 19, 29),
    gsSPNTriangles_5b(29, 6, 8, 30, 31, 2, 20, 30, 2, 0, 0, 0),
    gsSPVertex(&tol_umb_17_v[32], 26, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 18, 19, 20, 21, 22, 10, 9, 23),
    gsSPNTriangles_5b(4, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb17_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_17_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_17_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_17_v[58], 19, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 17, 15, 8, 18, 9, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
