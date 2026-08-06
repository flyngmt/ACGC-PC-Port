#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_otome01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_otome01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_otome01_pal[] = {
#include "assets/int_ike_k_otome01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otomefront_tex[0x80];
#else
u8 int_ike_k_otomefront_tex[] = {
#include "assets/int_ike_k_otomefront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otomeleg_tex[0x200];
#else
u8 int_ike_k_otomeleg_tex[] = {
#include "assets/int_ike_k_otomeleg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otomeside_tex[0x80];
#else
u8 int_ike_k_otomeside_tex[] = {
#include "assets/int_ike_k_otomeside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otometop_tex[0x80];
#else
u8 int_ike_k_otometop_tex[] = {
#include "assets/int_ike_k_otometop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otometle1_tex[0x200];
#else
u8 int_ike_k_otometle1_tex[] = {
#include "assets/int_ike_k_otometle1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otometle2_tex[0x80];
#else
u8 int_ike_k_otometle2_tex[] = {
#include "assets/int_ike_k_otometle2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_otometle3_tex[0x80];
#else
u8 int_ike_k_otometle3_tex[] = {
#include "assets/int_ike_k_otometle3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_otome01_v[0x6E0 / sizeof(Vtx)];
#else
Vtx int_ike_k_otome01_v[] = {
#include "assets/int_ike_k_otome01_v.inc"
};
#endif

Gfx int_ike_k_otome01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_otome01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_otometle3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_otome01_v, 29, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_otometle2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(34, 4, 5, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(7, 10, 11, 7, 11, 12, 11, 13, 12, 11, 5, 4),
    gsSPNTriangles_5b(11, 10, 5, 6, 5, 9, 9, 5, 10, 8, 12, 14),
    gsSPNTriangles_5b(8, 7, 12, 15, 16, 17, 16, 18, 17, 16, 11, 18),
    gsSPNTriangles_5b(16, 13, 11, 18, 19, 17, 19, 20, 17, 18, 11, 19),
    gsSPNTriangles_5b(11, 4, 19, 21, 22, 23, 24, 21, 23, 25, 26, 27),
    gsSPNTriangles_5b(27, 26, 28, 26, 25, 17, 20, 26, 17, 21, 15, 17),
    gsSPNTriangles_5b(21, 17, 22, 17, 25, 22, 25, 27, 23, 25, 23, 22),
    gsSPNTriangles_5b(28, 26, 20, 21, 24, 15, 13, 14, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_k_otometle1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_k_otome01_v[29], 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 1, 16, 17, 1, 17, 2, 5, 18, 19),
    gsSPNTriangles_5b(5, 19, 6, 9, 20, 21, 9, 21, 10, 13, 22, 23),
    gsSPNTriangles_5b(13, 23, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_otometop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_otomeside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_otome01_v[57], 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_otomefront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_k_otome01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_otome01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_k_otomeleg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_otome01_v[73], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 27, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_k_otome01_v[104], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
