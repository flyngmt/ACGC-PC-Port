#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_rocket1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_rocket1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_rocket1_pal[] = {
#include "assets/int_tak_rocket1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_wing_tex[0x100];
#else
u8 int_tak_rocket1_wing_tex[] = {
#include "assets/int_tak_rocket1_wing_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_body1_tex[0x200];
#else
u8 int_tak_rocket1_body1_tex[] = {
#include "assets/int_tak_rocket1_body1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_body2_tex[0x300];
#else
u8 int_tak_rocket1_body2_tex[] = {
#include "assets/int_tak_rocket1_body2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_dai_tex[0x80];
#else
u8 int_tak_rocket1_dai_tex[] = {
#include "assets/int_tak_rocket1_dai_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_hone_tex[0x80];
#else
u8 int_tak_rocket1_hone_tex[] = {
#include "assets/int_tak_rocket1_hone_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_hasi1_tex[0x80];
#else
u8 int_tak_rocket1_hasi1_tex[] = {
#include "assets/int_tak_rocket1_hasi1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_rocket1_hasi2_tex[0x80];
#else
u8 int_tak_rocket1_hasi2_tex[] = {
#include "assets/int_tak_rocket1_hasi2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_rocket1_v[0x420 / sizeof(Vtx)];
#else
Vtx int_tak_rocket1_v[] = {
#include "assets/int_tak_rocket1_v.inc"
};
#endif

Gfx int_tak_rocket1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_rocket1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_rocket1_dai_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_rocket1_v, 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_tak_rocket1_body2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 7, 8, 9, 7, 10, 8),
    gsSPNTriangles_5b(7, 9, 11, 9, 4, 12, 9, 5, 4, 9, 8, 5),
    gsSPNTriangles_5b(13, 10, 7, 13, 14, 10, 13, 7, 15, 4, 16, 17),
    gsSPNTriangles_5b(4, 6, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_rocket1_body1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_rocket1_v[18], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(3, 2, 6, 7, 1, 0, 7, 8, 1, 7, 0, 9),
    gsSPNTriangles_5b(10, 8, 7, 10, 11, 8, 10, 7, 12, 0, 3, 13),
    gsSPNTriangles_5b(0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_rocket1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_rocket1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_rocket1_hasi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_rocket1_v[32], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_rocket1_hasi1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 9, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_rocket1_hone_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_tak_rocket1_wing_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_rocket1_v[56], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
