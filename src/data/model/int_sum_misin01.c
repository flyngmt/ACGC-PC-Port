#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_misin01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_misin01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_misin01_pal[] = {
#include "assets/int_sum_misin01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_sidefoot_tex[0x100];
#else
u8 int_sum_misin01_sidefoot_tex[] = {
#include "assets/int_sum_misin01_sidefoot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_desktop_tex[0x80];
#else
u8 int_sum_misin01_desktop_tex[] = {
#include "assets/int_sum_misin01_desktop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_deskfront_tex[0x100];
#else
u8 int_sum_misin01_deskfront_tex[] = {
#include "assets/int_sum_misin01_deskfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_deskback_tex[0x100];
#else
u8 int_sum_misin01_deskback_tex[] = {
#include "assets/int_sum_misin01_deskback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_deskside_tex[0x40];
#else
u8 int_sum_misin01_deskside_tex[] = {
#include "assets/int_sum_misin01_deskside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_misiside_tex[0x100];
#else
u8 int_sum_misin01_misiside_tex[] = {
#include "assets/int_sum_misin01_misiside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_pedal_tex[0x80];
#else
u8 int_sum_misin01_pedal_tex[] = {
#include "assets/int_sum_misin01_pedal_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_kaiten_tex[0x80];
#else
u8 int_sum_misin01_kaiten_tex[] = {
#include "assets/int_sum_misin01_kaiten_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_harigane_tex[0x80];
#else
u8 int_sum_misin01_harigane_tex[] = {
#include "assets/int_sum_misin01_harigane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_misibase_tex[0x40];
#else
u8 int_sum_misin01_misibase_tex[] = {
#include "assets/int_sum_misin01_misibase_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_top_tex[0x100];
#else
u8 int_sum_misin01_top_tex[] = {
#include "assets/int_sum_misin01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_misin01_temaki_tex[0x80];
#else
u8 int_sum_misin01_temaki_tex[] = {
#include "assets/int_sum_misin01_temaki_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_misin01_v[0x560 / sizeof(Vtx)];
#else
Vtx int_sum_misin01_v[] = {
#include "assets/int_sum_misin01_v.inc"
};
#endif

Gfx int_sum_misin01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_misin01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_misin01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_misin01_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_misin01_deskside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_misin01_desktop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_misin01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_misin01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_misin01_temaki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_misin01_v[24], 29, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_misin01_misibase_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(7, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 8, 3, 5, 16, 17, 18),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_misin01_harigane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 22, 23, 24, 25, 26, 24),
    gsSPNTriangles_5b(19, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_misin01_kaiten_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_misin01_v[53], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_misin01_pedal_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_misin01_misiside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_misin01_deskback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 19, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_misin01_deskfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_misin01_sidefoot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_misin01_v[78], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
