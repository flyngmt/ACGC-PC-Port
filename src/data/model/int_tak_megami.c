#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_megami_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_magami_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_magami_pal[] = {
#include "assets/int_tak_magami_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_fire_tex[0x20];
#else
u8 int_tak_megami_fire_tex[] = {
#include "assets/int_tak_megami_fire_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_ita_tex[0x80];
#else
u8 int_tak_megami_ita_tex[] = {
#include "assets/int_tak_megami_ita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_totte_tex[0x40];
#else
u8 int_tak_megami_totte_tex[] = {
#include "assets/int_tak_megami_totte_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_face_tex[0x80];
#else
u8 int_tak_megami_face_tex[] = {
#include "assets/int_tak_megami_face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_body_tex[0x400];
#else
u8 int_tak_megami_body_tex[] = {
#include "assets/int_tak_megami_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_suso_tex[0x80];
#else
u8 int_tak_megami_suso_tex[] = {
#include "assets/int_tak_megami_suso_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_hand_tex[0x80];
#else
u8 int_tak_megami_hand_tex[] = {
#include "assets/int_tak_megami_hand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_sode_tex[0x80];
#else
u8 int_tak_megami_sode_tex[] = {
#include "assets/int_tak_megami_sode_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_asi_tex[0x80];
#else
u8 int_tak_megami_asi_tex[] = {
#include "assets/int_tak_megami_asi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_dai_tex[0x40];
#else
u8 int_tak_megami_dai_tex[] = {
#include "assets/int_tak_megami_dai_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_megami_top_tex[0x20];
#else
u8 int_tak_megami_top_tex[] = {
#include "assets/int_tak_megami_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_megami_v[0xB50 / sizeof(Vtx)];
#else
Vtx int_tak_megami_v[] = {
#include "assets/int_tak_megami_v.inc"
};
#endif

Gfx int_tak_megami_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_magami_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_megami_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_megami_v, 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_tak_megami_dai_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 8, 9, 5),
    gsSPNTriangles_5b(8, 5, 4, 10, 11, 9, 10, 9, 8, 7, 6, 12),
    gsSPNTriangles_5b(7, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_megami_sode_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(14, 14, 15, 16, 14, 16, 17, 14, 18, 15),
    gsSPNTriangles_5b(17, 19, 14, 20, 21, 22, 23, 24, 20, 23, 20, 22),
    gsSPNTriangles_5b(23, 25, 26, 25, 23, 22, 22, 27, 25, 25, 27, 21),
    gsSPNTriangles_5b(28, 26, 25, 25, 21, 28, 21, 29, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_megami_hand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_tak_megami_v[30], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 4, 7, 5, 8, 9, 10, 8, 10, 11),
    gsSPNTriangles_5b(12, 9, 8, 11, 13, 14, 11, 10, 13, 15, 16, 17),
    gsSPNTriangles_5b(18, 11, 14, 18, 14, 15, 17, 18, 15, 17, 19, 12),
    gsSPNTriangles_5b(17, 12, 18, 18, 12, 11, 12, 8, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 5, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_megami_face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[50], 20, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 2, 4, 5, 2),
    gsSPNTriangles_5b(5, 0, 2, 6, 1, 0, 7, 1, 6, 7, 8, 1),
    gsSPNTriangles_5b(4, 9, 5, 4, 10, 9, 4, 3, 10, 3, 11, 10),
    gsSPNTriangles_5b(8, 12, 3, 10, 13, 9, 13, 14, 9, 13, 10, 15),
    gsSPNTriangles_5b(7, 16, 8, 17, 18, 7, 7, 6, 17, 6, 19, 17),
    gsSPNTriangles_5b(8, 3, 2, 1, 8, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_megami_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_magami_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_megami_fire_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[70], 6, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 0, 0, 1, 4),
    gsSPNTriangles_5b(5, 1, 0, 1, 0, 4, 1, 5, 0, 1, 0, 2),
    gsSPNTriangles_5b(1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_megami_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_magami_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_megami_asi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[76], 20, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_tak_megami_suso_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11, 7, 8, 9, 8, 10, 9, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 12, 11, 13, 12, 13, 14, 7, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 17, 18, 19, 19, 16, 17, 16, 8, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_tak_megami_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[96], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 7, 8, 3),
    gsSPNTriangles_5b(7, 9, 8, 7, 10, 9, 1, 3, 8, 12, 19, 13),
    gsSPNTriangles_5b(19, 20, 13, 21, 19, 12, 21, 12, 18, 21, 18, 0),
    gsSPNTriangles_5b(2, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(13, 3, 4, 5, 4, 6, 5, 5, 7, 3),
    gsSPNTriangles_5b(11, 12, 13, 14, 12, 11, 15, 12, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 12, 12, 17, 18, 18, 22, 0, 18, 23, 22),
    gsSPNTriangles_5b(23, 3, 22, 22, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_megami_totte_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[120], 32, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 27, 28, 0, 29, 30, 31),
    gsSPNTriangles_5b(1, 0, 28, 1, 29, 31, 1, 31, 2, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 3, 4, 5, 6, 3, 5, 6, 5, 7),
    gsSPNTriangles_5b(8, 6, 7, 8, 7, 9, 10, 8, 9, 10, 9, 11),
    gsSPNTriangles_5b(12, 10, 11, 12, 11, 13, 14, 12, 13, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 19, 20, 21, 22, 23, 24, 20),
    gsSPNTriangles_5b(25, 26, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_megami_ita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_megami_v[152], 29, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28),
    gsSPEndDisplayList(),
};
