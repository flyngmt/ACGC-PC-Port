#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_hata_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_hata_e_pal[] = {
#include "assets/tol_hata_e_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_hata_e_tex[0x80];
#else
u8 tol_hata_e_tex[] = {
#include "assets/tol_hata_e_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_hata_hata_tex_inta_ia8[0x100];
#else
u8 tol_hata_hata_tex_inta_ia8[] = {
#include "assets/tol_hata_hata_tex_inta_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_hata_01_v[0xF0 / sizeof(Vtx)];
#else
Vtx tol_hata_01_v[] = {
#include "assets/tol_hata_01_v.inc"
};
#endif

Gfx tol_hata_e_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_hata_e_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_hata_e_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_hata_01_v, 9, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 3, 5, 6, 7, 8, 4),
    gsSPNTriangles_5b(7, 4, 3, 7, 6, 5, 7, 5, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_hata_hataT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, PRIMITIVE, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 128, 0, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_3_txt + 0x90, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
