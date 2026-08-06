#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_snowlamp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_snowlamp_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_snowlamp_tex_pal[] = {
#include "assets/int_tak_snowlamp_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_face_tex[0x80];
#else
u8 int_tak_snowlamp_face_tex[] = {
#include "assets/int_tak_snowlamp_face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_back_tex[0x80];
#else
u8 int_tak_snowlamp_back_tex[] = {
#include "assets/int_tak_snowlamp_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_bou_tex[0x100];
#else
u8 int_tak_snowlamp_bou_tex[] = {
#include "assets/int_tak_snowlamp_bou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_asi_tex[0x80];
#else
u8 int_tak_snowlamp_asi_tex[] = {
#include "assets/int_tak_snowlamp_asi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_body_tex[0x200];
#else
u8 int_tak_snowlamp_body_tex[] = {
#include "assets/int_tak_snowlamp_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowlamp_side_tex[0x80];
#else
u8 int_tak_snowlamp_side_tex[] = {
#include "assets/int_tak_snowlamp_side_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_snowlamp_v[0x370 / sizeof(Vtx)];
#else
Vtx int_tak_snowlamp_v[] = {
#include "assets/int_tak_snowlamp_v.inc"
};
#endif

Gfx int_tak_snowlamp_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_snowlamp_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowlamp_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_snowlamp_v, 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 3, 2, 10, 3, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_snowlamp_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_snowlamp_v[12], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 8, 9, 8, 10, 7, 8, 9, 10, 11, 9),
    gsSPNTriangles_5b(12, 13, 14, 13, 15, 14, 15, 6, 14, 12, 14, 16),
    gsSPNTriangles_5b(14, 5, 16, 14, 6, 5, 6, 17, 4, 0, 18, 19),
    gsSPNTriangles_5b(15, 17, 6, 19, 18, 17, 0, 2, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_snowlamp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_snowlamp_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowlamp_asi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_snowlamp_v[32], 23, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 6, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_snowlamp_bou_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 7, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowlamp_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowlamp_face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
