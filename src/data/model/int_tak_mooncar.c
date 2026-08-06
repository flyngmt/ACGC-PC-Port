#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_mooncar_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_mooncar_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_mooncar_pal[] = {
#include "assets/int_tak_mooncar_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_bou1_tex[0x80];
#else
u8 int_tak_mooncar_bou1_tex[] = {
#include "assets/int_tak_mooncar_bou1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_base_tex[0x100];
#else
u8 int_tak_mooncar_base_tex[] = {
#include "assets/int_tak_mooncar_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_body_tex[0x100];
#else
u8 int_tak_mooncar_body_tex[] = {
#include "assets/int_tak_mooncar_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_kasa_tex[0x80];
#else
u8 int_tak_mooncar_kasa_tex[] = {
#include "assets/int_tak_mooncar_kasa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_se_tex[0x80];
#else
u8 int_tak_mooncar_se_tex[] = {
#include "assets/int_tak_mooncar_se_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_cover2_tex[0x80];
#else
u8 int_tak_mooncar_cover2_tex[] = {
#include "assets/int_tak_mooncar_cover2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_ant_tex[0x80];
#else
u8 int_tak_mooncar_ant_tex[] = {
#include "assets/int_tak_mooncar_ant_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_bodyside_tex[0x80];
#else
u8 int_tak_mooncar_bodyside_tex[] = {
#include "assets/int_tak_mooncar_bodyside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_tire2_tex[0x80];
#else
u8 int_tak_mooncar_tire2_tex[] = {
#include "assets/int_tak_mooncar_tire2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_bou2_tex[0x80];
#else
u8 int_tak_mooncar_bou2_tex[] = {
#include "assets/int_tak_mooncar_bou2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_mooncar_kasa2_tex[0x80];
#else
u8 int_tak_mooncar_kasa2_tex[] = {
#include "assets/int_tak_mooncar_kasa2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_mooncar_v[0x510 / sizeof(Vtx)];
#else
Vtx int_tak_mooncar_v[] = {
#include "assets/int_tak_mooncar_v.inc"
};
#endif

Gfx int_tak_mooncar_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_mooncar_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_bodyside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_mooncar_v, 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_kasa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 8, 9, 10, 11, 8, 12, 13, 11, 14),
    gsSPNTriangles_5b(9, 15, 16, 15, 17, 18, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_mooncar_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_mooncar_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_kasa2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_mooncar_v[19], 26, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_bou2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_tire2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_ant_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 18, 19, 20, 21, 22, 23, 18, 24, 25),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_cover2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_tak_mooncar_v[45], 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(5, 6, 4, 5, 4, 3, 7, 8, 9, 7, 10, 8),
    gsSPNTriangles_5b(8, 11, 9, 11, 12, 9, 11, 13, 12, 13, 14, 12),
    gsSPNTriangles_5b(1, 15, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_se_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_tak_mooncar_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 20, 24, 25),
    gsSPNTriangles_5b(20, 25, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_tak_mooncar_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_mooncar_bou1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_mooncar_v[75], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
