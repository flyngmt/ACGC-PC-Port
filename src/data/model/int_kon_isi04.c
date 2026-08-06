#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_isi04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_isi04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_isi04_pal[] = {
#include "assets/int_kon_isi04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi04_yoko_tex[0x100];
#else
u8 int_kon_isi04_yoko_tex[] = {
#include "assets/int_kon_isi04_yoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi04_ue_tex[0x180];
#else
u8 int_kon_isi04_ue_tex[] = {
#include "assets/int_kon_isi04_ue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi04_mae_tex[0x480];
#else
u8 int_kon_isi04_mae_tex[] = {
#include "assets/int_kon_isi04_mae_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi04_koke_tex[0x80];
#else
u8 int_kon_isi04_koke_tex[] = {
#include "assets/int_kon_isi04_koke_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_isi04_v[0x350 / sizeof(Vtx)];
#else
Vtx int_kon_isi04_v[] = {
#include "assets/int_kon_isi04_v.inc"
};
#endif

Gfx int_kon_isi04_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_isi04_ue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi04_v, 18, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPNTriangles_5b(7, 8, 5, 7, 5, 0, 6, 7, 0, 5, 4, 1),
    gsSPNTriangles_5b(5, 1, 0, 8, 9, 5, 9, 3, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_isi04_yoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 10, 11, 12, 10, 12, 13, 11, 14, 15),
    gsSPNTriangles_5b(11, 15, 12, 16, 10, 13, 16, 13, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_isi04_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_isi04_koke_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_isi04_v[18], 17, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(1, 3, 6, 7, 8, 9, 8, 10, 11, 8, 11, 9),
    gsSPNTriangles_5b(4, 12, 13, 12, 7, 14, 10, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 48, int_kon_isi04_mae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_isi04_v[35], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 7, 6, 13, 14, 3, 13, 3, 5),
    gsSPNTriangles_5b(4, 2, 15, 9, 8, 16, 9, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};
