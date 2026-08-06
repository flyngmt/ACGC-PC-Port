#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_noise_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_noise_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_noise_pal[] = {
#include "assets/int_tak_noise_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_noise_1_tex[0x200];
#else
u8 int_tak_noise_1_tex[] = {
#include "assets/int_tak_noise_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_noise_2_tex[0x80];
#else
u8 int_tak_noise_2_tex[] = {
#include "assets/int_tak_noise_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_noise_3_tex[0x40];
#else
u8 int_tak_noise_3_tex[] = {
#include "assets/int_tak_noise_3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_noise_v[0x430 / sizeof(Vtx)];
#else
Vtx int_tak_noise_v[] = {
#include "assets/int_tak_noise_v.inc"
};
#endif

Gfx int_tak_noise_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_noise_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_noise_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_noise_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 12, 15, 16, 12, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 18, 21, 22, 18, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_noise_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_noise_v[24], 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 17, 16, 11, 17, 11, 10, 18, 19, 15),
    gsSPNTriangles_5b(18, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_noise_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_noise_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_noise_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_noise_v[44], 23, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 0, 3, 12, 3, 13, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 4, 6, 7, 8, 12, 13),
    gsSPNTriangles_5b(8, 13, 9, 14, 15, 16, 14, 16, 17, 14, 17, 8),
    gsSPNTriangles_5b(18, 19, 20, 18, 20, 21, 18, 21, 22, 0, 0, 0),
    gsSPEndDisplayList(),
};
