#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_prores_ling03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_ling03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_ling03_pal[] = {
#include "assets/int_ike_prores_ling03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_lope2_tex[0x80];
#else
u8 int_ike_prores_ling03_lope2_tex[] = {
#include "assets/int_ike_prores_ling03_lope2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_lope_tex[0x80];
#else
u8 int_ike_prores_ling03_lope_tex[] = {
#include "assets/int_ike_prores_ling03_lope_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_mat2_tex[0x80];
#else
u8 int_ike_prores_ling03_mat2_tex[] = {
#include "assets/int_ike_prores_ling03_mat2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_pole_tex[0x80];
#else
u8 int_ike_prores_ling03_pole_tex[] = {
#include "assets/int_ike_prores_ling03_pole_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_floor_tex[0x200];
#else
u8 int_ike_prores_ling03_floor_tex[] = {
#include "assets/int_ike_prores_ling03_floor_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_floorside_tex[0x80];
#else
u8 int_ike_prores_ling03_floorside_tex[] = {
#include "assets/int_ike_prores_ling03_floorside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_pole2_tex[0x80];
#else
u8 int_ike_prores_ling03_pole2_tex[] = {
#include "assets/int_ike_prores_ling03_pole2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_base_tex[0x80];
#else
u8 int_ike_prores_ling03_base_tex[] = {
#include "assets/int_ike_prores_ling03_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_ling03_pole3_tex[0x80];
#else
u8 int_ike_prores_ling03_pole3_tex[] = {
#include "assets/int_ike_prores_ling03_pole3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_prores_ling03_v[0x4C0 / sizeof(Vtx)];
#else
Vtx int_ike_prores_ling03_v[] = {
#include "assets/int_ike_prores_ling03_v.inc"
};
#endif

Gfx int_ike_prores_ling03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_ling03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_ling03_pole3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_prores_ling03_v, 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_ling03_pole2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 6, 8, 7, 5, 9, 6),
    gsSPNTriangles_5b(9, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_ling03_floorside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(10, 17, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_prores_ling03_floor_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_ling03_pole_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_prores_ling03_v[22], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_ling03_mat2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 16, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 21, 20, 22, 21, 22, 23, 23, 22, 17),
    gsSPNTriangles_5b(23, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_prores_ling03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_ling03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_ling03_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_ling03_v[46], 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_ling03_lope_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 11, 10, 16, 11, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_ling03_lope2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 18, 19, 20, 21, 22, 23, 24, 21, 23),
    gsSPNTriangles_5b(25, 26, 27, 26, 28, 27, 29, 18, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};
