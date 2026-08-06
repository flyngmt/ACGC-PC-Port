#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_28_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_28_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_28_pal[] = {
#include "assets/tol_umb_28_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_28_kasa_tex_txt[0x200];
#else
u8 tol_umb_28_kasa_tex_txt[] = {
#include "assets/tol_umb_28_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_28_tuka_tex_txt[0x200];
#else
u8 tol_umb_28_tuka_tex_txt[] = {
#include "assets/tol_umb_28_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_28_v[0x360 / sizeof(Vtx)];
#else
Vtx tol_umb_28_v[] = {
#include "assets/tol_umb_28_v.inc"
};
#endif

Gfx kasa_umb28_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_28_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_28_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_28_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 3, 0, 1, 0, 4),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 9, 9, 7, 6, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 11, 10, 16, 17, 18, 19, 18, 20, 21),
    gsSPNTriangles_5b(21, 19, 18, 22, 23, 24, 24, 25, 22, 23, 22, 26),
    gsSPNTriangles_5b(27, 28, 29, 28, 30, 31, 31, 29, 28, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb28_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_28_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_28_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_28_v[32], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 11, 16, 11, 10, 5, 4, 17),
    gsSPNTriangles_5b(5, 17, 16, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
