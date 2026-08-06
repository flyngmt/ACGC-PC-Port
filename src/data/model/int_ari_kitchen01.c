#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ari_kitchen01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ari_kitchen01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ari_kitchen01_pal[] = {
#include "assets/int_ari_kitchen01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_00_tex[0x200];
#else
u8 int_ari_kitchen01_00_tex[] = {
#include "assets/int_ari_kitchen01_00_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_01_tex[0x100];
#else
u8 int_ari_kitchen01_01_tex[] = {
#include "assets/int_ari_kitchen01_01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_02_tex[0x100];
#else
u8 int_ari_kitchen01_02_tex[] = {
#include "assets/int_ari_kitchen01_02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_03_tex[0x100];
#else
u8 int_ari_kitchen01_03_tex[] = {
#include "assets/int_ari_kitchen01_03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_04_tex[0x80];
#else
u8 int_ari_kitchen01_04_tex[] = {
#include "assets/int_ari_kitchen01_04_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_05_tex[0x80];
#else
u8 int_ari_kitchen01_05_tex[] = {
#include "assets/int_ari_kitchen01_05_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_kitchen01_06_tex[0x80];
#else
u8 int_ari_kitchen01_06_tex[] = {
#include "assets/int_ari_kitchen01_06_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ari_kitchen01_v[0x2A0 / sizeof(Vtx)];
#else
Vtx int_ari_kitchen01_v[] = {
#include "assets/int_ari_kitchen01_v.inc"
};
#endif

Gfx int_ari_kitchen01_01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ari_kitchen01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ari_kitchen01_05_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ari_kitchen01_v, 27, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 6, 7, 2, 7, 8, 2),
    gsSPNTriangles_5b(8, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ari_kitchen01_03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 10, 12, 11, 11, 13, 14),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ari_kitchen01_02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 18, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ari_kitchen01_01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 22, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ari_kitchen01_00_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 24, 26, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ari_kitchen01_01T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ari_kitchen01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ari_kitchen01_06_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ari_kitchen01_v[27], 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ari_kitchen01_04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 3, 4, 5, 3, 6, 4, 3, 7, 8),
    gsSPNTriangles_5b(3, 9, 7, 3, 10, 11, 3, 12, 10, 3, 13, 14),
    gsSPNTriangles_5b(3, 5, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
