#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_cornucopia_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_cornucopia_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_cornucopia_pal[] = {
#include "assets/int_nog_cornucopia_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_pampB_tex[0x80];
#else
u8 int_nog_cornucopia_pampB_tex[] = {
#include "assets/int_nog_cornucopia_pampB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_pampC_tex[0x80];
#else
u8 int_nog_cornucopia_pampC_tex[] = {
#include "assets/int_nog_cornucopia_pampC_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_pampD_tex[0x80];
#else
u8 int_nog_cornucopia_pampD_tex[] = {
#include "assets/int_nog_cornucopia_pampD_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_runner_tex[0x100];
#else
u8 int_nog_cornucopia_runner_tex[] = {
#include "assets/int_nog_cornucopia_runner_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_horn_tex[0x100];
#else
u8 int_nog_cornucopia_horn_tex[] = {
#include "assets/int_nog_cornucopia_horn_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_leafA_tex[0x80];
#else
u8 int_nog_cornucopia_leafA_tex[] = {
#include "assets/int_nog_cornucopia_leafA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_leafB_tex[0x80];
#else
u8 int_nog_cornucopia_leafB_tex[] = {
#include "assets/int_nog_cornucopia_leafB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_cornucopia_ear_tex[0x100];
#else
u8 int_nog_cornucopia_ear_tex[] = {
#include "assets/int_nog_cornucopia_ear_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_cornucopia_v[0x500 / sizeof(Vtx)];
#else
Vtx int_nog_cornucopia_v[] = {
#include "assets/int_nog_cornucopia_v.inc"
};
#endif

Gfx int_nog_cornucopiaT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_cornucopia_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_cornucopia_ear_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_cornucopia_v, 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_cornucopia_leafB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_cornucopia_leafA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_cornucopia_horn_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&int_nog_cornucopia_v[16], 21, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 4, 8, 5, 0, 3, 8, 4, 9, 0),
    gsSPNTriangles_5b(0, 8, 4, 6, 5, 10, 11, 12, 6, 6, 10, 11),
    gsSPNTriangles_5b(13, 14, 2, 2, 15, 13, 13, 16, 14, 2, 14, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_cornucopia_runner_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 19, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_cornucopia_pampD_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_cornucopia_v[37], 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 4, 3, 5, 0),
    gsSPNTriangles_5b(6, 7, 8, 6, 9, 7, 1, 6, 10, 1, 11, 6),
    gsSPNTriangles_5b(0, 12, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_cornucopia_pampC_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 13, 14, 15, 16, 17, 18, 16, 19, 17),
    gsSPNTriangles_5b(20, 21, 22, 20, 23, 24, 25, 20, 26, 25, 27, 28),
    gsSPNTriangles_5b(17, 29, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_cornucopia_pampB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_nog_cornucopia_v[67], 13, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 0, 5, 6, 3),
    gsSPNTriangles_5b(5, 3, 7, 2, 8, 9, 0, 2, 10, 3, 0, 11),
    gsSPNTriangles_5b(2, 12, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
