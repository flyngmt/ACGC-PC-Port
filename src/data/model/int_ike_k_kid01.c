#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_kid01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_kid01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_kid01_pal[] = {
#include "assets/int_ike_k_kid01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidfront1_tex[0x80];
#else
u8 int_ike_k_kidfront1_tex[] = {
#include "assets/int_ike_k_kidfront1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidfront2_tex[0x40];
#else
u8 int_ike_k_kidfront2_tex[] = {
#include "assets/int_ike_k_kidfront2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidfront3_tex[0x200];
#else
u8 int_ike_k_kidfront3_tex[] = {
#include "assets/int_ike_k_kidfront3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidfront4_tex[0x40];
#else
u8 int_ike_k_kidfront4_tex[] = {
#include "assets/int_ike_k_kidfront4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidtire_tex[0x40];
#else
u8 int_ike_k_kidtire_tex[] = {
#include "assets/int_ike_k_kidtire_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidtunagi_tex[0x40];
#else
u8 int_ike_k_kidtunagi_tex[] = {
#include "assets/int_ike_k_kidtunagi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidsumi_tex[0x80];
#else
u8 int_ike_k_kidsumi_tex[] = {
#include "assets/int_ike_k_kidsumi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidyane_tex[0x40];
#else
u8 int_ike_k_kidyane_tex[] = {
#include "assets/int_ike_k_kidyane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidunder_tex[0x40];
#else
u8 int_ike_k_kidunder_tex[] = {
#include "assets/int_ike_k_kidunder_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidside2_tex[0x100];
#else
u8 int_ike_k_kidside2_tex[] = {
#include "assets/int_ike_k_kidside2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidside3_tex[0x80];
#else
u8 int_ike_k_kidside3_tex[] = {
#include "assets/int_ike_k_kidside3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidside4_tex[0x100];
#else
u8 int_ike_k_kidside4_tex[] = {
#include "assets/int_ike_k_kidside4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidside1_tex[0x100];
#else
u8 int_ike_k_kidside1_tex[] = {
#include "assets/int_ike_k_kidside1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kidbase_tex[0x80];
#else
u8 int_ike_k_kidbase_tex[] = {
#include "assets/int_ike_k_kidbase_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_kid01_v[0xB40 / sizeof(Vtx)];
#else
Vtx int_ike_k_kid01_v[] = {
#include "assets/int_ike_k_kid01_v.inc"
};
#endif

Gfx int_ike_k_kid01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_kid01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kidbase_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_kid01_v, 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kidside1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid01_v[16], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 8, 6, 9, 7, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 17, 18, 19, 20, 17, 19),
    gsSPNTriangles_5b(21, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidyane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 22, 23, 24, 23, 25, 24, 24, 26, 27),
    gsSPNTriangles_5b(24, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kidsumi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid01_v[44], 25, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 19, 16, 18, 20, 2, 3),
    gsSPNTriangles_5b(20, 0, 2, 21, 22, 23, 21, 24, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_k_kidfront3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid01_v[69], 26, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 1, 6, 2),
    gsSPNTriangles_5b(3, 6, 4, 7, 1, 0, 5, 4, 8, 9, 5, 8),
    gsSPNTriangles_5b(7, 0, 9, 7, 9, 8, 4, 6, 8, 7, 6, 1),
    gsSPNTriangles_5b(8, 6, 7, 10, 11, 12, 12, 13, 10, 2, 6, 3),
    gsSPNTriangles_5b(3, 14, 2, 3, 5, 14, 14, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidfront2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kidfront1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 19, 20, 21, 19, 22, 20, 19, 23, 22),
    gsSPNTriangles_5b(24, 25, 19, 19, 21, 24, 25, 23, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_k_kid01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_kid01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kidside4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_kid01_v[95], 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kidside3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(14, 21, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 18, 19, 20),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kidside2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 23, 26, 24, 27, 28, 29),
    gsSPNTriangles_5b(27, 30, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidunder_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_kid01_v[126], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidtunagi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(9, 15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidtire_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid01_v[142], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 9, 7, 10, 11, 12, 13, 14, 15, 16, 13, 15),
    gsSPNTriangles_5b(17, 10, 12, 18, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 28, 25, 27, 19, 29, 20, 3, 5, 30),
    gsSPNTriangles_5b(0, 2, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kidfront4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_k_kid01_v[174], 6, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(3, 5, 1, 1, 5, 2, 2, 4, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
