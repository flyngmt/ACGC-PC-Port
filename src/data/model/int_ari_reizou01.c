#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ari_reizou01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ari_reizou01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ari_reizou01_pal[] = {
#include "assets/int_ari_reizou01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_reizou01_00_tex[0x180];
#else
u8 int_ari_reizou01_00_tex[] = {
#include "assets/int_ari_reizou01_00_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_reizou01_01_tex[0x300];
#else
u8 int_ari_reizou01_01_tex[] = {
#include "assets/int_ari_reizou01_01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_reizou01_02_tex[0x180];
#else
u8 int_ari_reizou01_02_tex[] = {
#include "assets/int_ari_reizou01_02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_reizou01_03_tex[0x180];
#else
u8 int_ari_reizou01_03_tex[] = {
#include "assets/int_ari_reizou01_03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_reizou01_04_tex[0x80];
#else
u8 int_ari_reizou01_04_tex[] = {
#include "assets/int_ari_reizou01_04_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ari_reizou01_v[0x200 / sizeof(Vtx)];
#else
Vtx int_ari_reizou01_v[] = {
#include "assets/int_ari_reizou01_v.inc"
};
#endif

Gfx int_ari_reizou01_01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ari_reizou01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ari_reizou01_04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ari_reizou01_v, 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_ari_reizou01_03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 7, 5, 8, 7, 4),
    gsSPNTriangles_5b(8, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_ari_reizou01_02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 12, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_ari_reizou01_01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 16, 17, 18, 19, 20, 21, 22, 23, 20),
    gsSPNTriangles_5b(23, 21, 20, 24, 16, 18, 24, 25, 16, 17, 16, 19),
    gsSPNTriangles_5b(16, 20, 19, 25, 20, 16, 25, 22, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_ari_reizou01_00_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ari_reizou01_v[26], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
