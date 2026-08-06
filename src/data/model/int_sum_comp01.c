#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_comp01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_comp01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_comp01_pal[] = {
#include "assets/int_sum_comp01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_front_tex[0x100];
#else
u8 int_sum_comp01_front_tex[] = {
#include "assets/int_sum_comp01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_side_tex[0x100];
#else
u8 int_sum_comp01_side_tex[] = {
#include "assets/int_sum_comp01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_backtop_tex[0x40];
#else
u8 int_sum_comp01_backtop_tex[] = {
#include "assets/int_sum_comp01_backtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_fronttop_tex[0x40];
#else
u8 int_sum_comp01_fronttop_tex[] = {
#include "assets/int_sum_comp01_fronttop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_mainfront[0x100];
#else
u8 int_sum_comp01_mainfront[] = {
#include "assets/int_sum_comp01_mainfront.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_key_tex[0x100];
#else
u8 int_sum_comp01_key_tex[] = {
#include "assets/int_sum_comp01_key_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_deskfront_tex[0x80];
#else
u8 int_sum_comp01_deskfront_tex[] = {
#include "assets/int_sum_comp01_deskfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_deskside_tex[0x100];
#else
u8 int_sum_comp01_deskside_tex[] = {
#include "assets/int_sum_comp01_deskside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_desktop_tex[0x80];
#else
u8 int_sum_comp01_desktop_tex[] = {
#include "assets/int_sum_comp01_desktop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_mainback[0x80];
#else
u8 int_sum_comp01_mainback[] = {
#include "assets/int_sum_comp01_mainback.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_comp01_back_tex[0x80];
#else
u8 int_sum_comp01_back_tex[] = {
#include "assets/int_sum_comp01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_comp01_v[0x5B0 / sizeof(Vtx)];
#else
Vtx int_sum_comp01_v[] = {
#include "assets/int_sum_comp01_v.inc"
};
#endif

Gfx int_sum_comp01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_comp01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_comp01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_comp01_v, 29, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_comp01_mainback),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 10, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_comp01_desktop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 11, 12, 13, 14, 15, 16, 14, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 18, 20, 21, 22, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(11, 28, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_comp01_deskside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_comp01_v[29], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 8, 0, 11, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_comp01_key_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_comp01_mainfront),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 16, 27, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_comp01_fronttop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_comp01_v[57], 22, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 0, 13, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_comp01_backtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 17, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_comp01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 21, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_comp01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_comp01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_comp01_deskfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_comp01_v[79], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_comp01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
