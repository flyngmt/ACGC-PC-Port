#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowbed_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_snowbed_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_snowbed_tex_pal[] = {
#include "assets/int_kon_snowbed_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbed01_tex[0x200];
#else
u8 int_kon_snowbed01_tex[] = {
#include "assets/int_kon_snowbed01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbed02_tex[0x300];
#else
u8 int_kon_snowbed02_tex[] = {
#include "assets/int_kon_snowbed02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbed03_tex[0x200];
#else
u8 int_kon_snowbed03_tex[] = {
#include "assets/int_kon_snowbed03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbed04_tex[0x100];
#else
u8 int_kon_snowbed04_tex[] = {
#include "assets/int_kon_snowbed04_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowbed_v[0x2D0 / sizeof(Vtx)];
#else
Vtx int_kon_snowbed_v[] = {
#include "assets/int_kon_snowbed_v.inc"
};
#endif

Gfx int_kon_snoebed_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowbed_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_kon_snowbed02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowbed_v, 23, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 4, 3, 5),
    gsSPNTriangles_5b(6, 7, 5, 8, 6, 5, 9, 8, 5, 9, 5, 3),
    gsSPNTriangles_5b(9, 3, 2, 2, 1, 10, 9, 2, 10, 4, 5, 7),
    gsSPNTriangles_5b(11, 4, 7, 4, 11, 0, 2, 4, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_snowbed01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 12, 13, 14, 13, 15, 14, 15, 16, 14),
    gsSPNTriangles_5b(17, 18, 12, 13, 19, 15, 18, 20, 12, 20, 21, 12),
    gsSPNTriangles_5b(21, 13, 12, 21, 22, 13, 22, 19, 13, 12, 14, 17),
    gsSPNTriangles_5b(14, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snoebed_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowbed_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_snowbed04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowbed_v[23], 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 0, 3),
    gsSPNTriangles_5b(4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_snowbed03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 6, 7, 8, 9, 6, 10, 11, 12, 9),
    gsSPNTriangles_5b(13, 14, 15, 16, 13, 15, 15, 17, 16, 15, 18, 17),
    gsSPNTriangles_5b(19, 20, 11, 10, 21, 19, 8, 7, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
