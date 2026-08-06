#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_apollo1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_apollo1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_apollo1_pal[] = {
#include "assets/int_tak_apollo1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_antena1_tex[0x80];
#else
u8 int_tak_apollo1_antena1_tex[] = {
#include "assets/int_tak_apollo1_antena1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_antena2_tex[0x80];
#else
u8 int_tak_apollo1_antena2_tex[] = {
#include "assets/int_tak_apollo1_antena2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_asi2_tex[0x80];
#else
u8 int_tak_apollo1_asi2_tex[] = {
#include "assets/int_tak_apollo1_asi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_asi3_tex[0x80];
#else
u8 int_tak_apollo1_asi3_tex[] = {
#include "assets/int_tak_apollo1_asi3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_asi_tex[0x80];
#else
u8 int_tak_apollo1_asi_tex[] = {
#include "assets/int_tak_apollo1_asi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_atama_tex[0x80];
#else
u8 int_tak_apollo1_atama_tex[] = {
#include "assets/int_tak_apollo1_atama_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_body_tex[0x100];
#else
u8 int_tak_apollo1_body_tex[] = {
#include "assets/int_tak_apollo1_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_kosi_tex[0x80];
#else
u8 int_tak_apollo1_kosi_tex[] = {
#include "assets/int_tak_apollo1_kosi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_kutu_tex[0x80];
#else
u8 int_tak_apollo1_kutu_tex[] = {
#include "assets/int_tak_apollo1_kutu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_apollo1_kao_tex[0x100];
#else
u8 int_tak_apollo1_kao_tex[] = {
#include "assets/int_tak_apollo1_kao_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_apollo1_v[0x600 / sizeof(Vtx)];
#else
Vtx int_tak_apollo1_v[] = {
#include "assets/int_tak_apollo1_v.inc"
};
#endif

Gfx int_tak_apollo1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_apollo1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_apollo1_kao_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_apollo1_v, 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 3, 1, 3, 6, 2, 6, 7, 2),
    gsSPNTriangles_5b(3, 8, 6, 8, 9, 6, 9, 7, 6, 9, 10, 7),
    gsSPNTriangles_5b(9, 11, 10, 11, 12, 10, 12, 13, 10, 13, 7, 10),
    gsSPNTriangles_5b(14, 15, 16, 15, 12, 16, 14, 17, 15, 17, 13, 15),
    gsSPNTriangles_5b(13, 12, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_kosi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_atama_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_apollo1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_apollo1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_kutu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_apollo1_v[26], 21, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_apollo1_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 12, 14, 17, 18),
    gsSPNTriangles_5b(19, 20, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_asi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_apollo1_v[47], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_asi3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_asi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_apollo1_v[71], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_antena2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 15, 16, 17, 18, 16, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_apollo1_antena1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 22, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};
