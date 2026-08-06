#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_gomi03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_gomi03_gururi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_gomi03_gururi_pal[] = {
#include "assets/int_kon_gomi03_gururi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi03_gururi_tex[0x100];
#else
u8 int_kon_gomi03_gururi_tex[] = {
#include "assets/int_kon_gomi03_gururi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi03_mawari_tex[0x80];
#else
u8 int_kon_gomi03_mawari_tex[] = {
#include "assets/int_kon_gomi03_mawari_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi03_totte_tex[0x80];
#else
u8 int_kon_gomi03_totte_tex[] = {
#include "assets/int_kon_gomi03_totte_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi03_ue_tex[0x200];
#else
u8 int_kon_gomi03_ue_tex[] = {
#include "assets/int_kon_gomi03_ue_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_gomi03_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_kon_gomi03_v[] = {
#include "assets/int_kon_gomi03_v.inc"
};
#endif

Gfx int_kon_gomi03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_gomi03_gururi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_gomi03_ue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_gomi03_v, 21, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_gomi03_mawari_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(12, 7, 8, 9, 7, 9, 10, 10, 9, 11),
    gsSPNTriangles_5b(10, 11, 12, 12, 11, 13, 12, 13, 14, 15, 16, 8),
    gsSPNTriangles_5b(15, 8, 7, 17, 18, 16, 17, 16, 15, 19, 20, 18),
    gsSPNTriangles_5b(19, 18, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_gomi03_gururi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&int_kon_gomi03_v[21], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 10, 12, 13),
    gsSPNTriangles_5b(10, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_gomi03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_gomi03_gururi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_gomi03_totte_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_gomi03_v[35], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 1, 0),
    gsSPNTriangles_5b(4, 0, 5, 6, 2, 1, 6, 1, 7, 8, 3, 2),
    gsSPNTriangles_5b(8, 2, 9, 10, 0, 3, 10, 3, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};
