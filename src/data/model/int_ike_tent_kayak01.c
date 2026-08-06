#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_tent_kayak01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_kayak01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_kayak01_pal[] = {
#include "assets/int_ike_tent_kayak01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_kayak_pab[0x200];
#else
u8 int_ike_tent_kayak_pab[] = {
#include "assets/int_ike_tent_kayak_pab.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_kayak_under[0x80];
#else
u8 int_ike_tent_kayak_under[] = {
#include "assets/int_ike_tent_kayak_under.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_kayak_chair[0x100];
#else
u8 int_ike_tent_kayak_chair[] = {
#include "assets/int_ike_tent_kayak_chair.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_kayak_topf[0x180];
#else
u8 int_ike_tent_kayak_topf[] = {
#include "assets/int_ike_tent_kayak_topf.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_kayak_topr[0x180];
#else
u8 int_ike_tent_kayak_topr[] = {
#include "assets/int_ike_tent_kayak_topr.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_tent_kayak01_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_ike_tent_kayak01_v[] = {
#include "assets/int_ike_tent_kayak01_v.inc"
};
#endif

Gfx int_ike_tent_kayak01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_tent_kayak01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_ike_tent_kayak_topr),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_tent_kayak01_v, 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_ike_tent_kayak_topf),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 7, 6, 6, 10, 9),
    gsSPNTriangles_5b(11, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_kayak_under),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_tent_kayak01_v[12], 24, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 2, 3, 4, 3, 5, 4),
    gsSPNTriangles_5b(3, 6, 5, 5, 8, 13, 14, 11, 0, 9, 8, 6),
    gsSPNTriangles_5b(6, 8, 5, 1, 11, 10, 1, 0, 11, 13, 15, 16),
    gsSPNTriangles_5b(15, 14, 16, 16, 0, 4, 16, 14, 0, 16, 5, 13),
    gsSPNTriangles_5b(16, 4, 5, 0, 2, 4, 12, 17, 18, 10, 12, 18),
    gsSPNTriangles_5b(19, 7, 20, 20, 7, 9, 17, 12, 14, 13, 7, 19),
    gsSPNTriangles_5b(19, 20, 21, 22, 19, 21, 22, 21, 23, 23, 18, 17),
    gsSPNTriangles_5b(22, 23, 17, 19, 22, 15, 13, 19, 15, 17, 14, 15),
    gsSPNTriangles_5b(22, 17, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 7, 8, 9, 10, 11, 12, 14, 14, 14),
    gsSPNTriangles_5b(14, 14, 12, 14, 12, 11, 7, 13, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_tent_kayak01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_tent_kayak01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_tent_kayak_chair),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_tent_kayak01_v[36], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_ike_tent_kayak_pab),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};
