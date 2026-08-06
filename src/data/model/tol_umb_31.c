#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_31_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_umb_31_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_umb_31_pal[] = {
#include "assets/tol_umb_31_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_31_kasa_tex_txt[0x200];
#else
u8 tol_umb_31_kasa_tex_txt[] = {
#include "assets/tol_umb_31_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_31_tuka_tex_txt[0x200];
#else
u8 tol_umb_31_tuka_tex_txt[] = {
#include "assets/tol_umb_31_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_umb_31_e_tex_txt[0x80];
#else
u8 tol_umb_31_e_tex_txt[] = {
#include "assets/tol_umb_31_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_31_v[0x360 / sizeof(Vtx)];
#else
Vtx tol_umb_31_v[] = {
#include "assets/tol_umb_31_v.inc"
};
#endif

Gfx kasa_umb31_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_31_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_31_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_31_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(7, 2, 1, 1, 8, 7, 9, 10, 11, 11, 12, 9),
    gsSPNTriangles_5b(13, 14, 15, 15, 16, 13, 17, 18, 19, 19, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 23, 24, 21, 6, 5, 25, 26, 19, 18),
    gsSPNTriangles_5b(22, 21, 27, 28, 9, 12, 14, 13, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb31_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_31_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_31_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_31_v[30], 24, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 3, 8, 3, 2, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_umb_31_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
