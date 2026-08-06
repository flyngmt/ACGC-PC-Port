#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_yoroi_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_yoroi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_yoroi_pal[] = {
#include "assets/int_tak_yoroi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_yoroi_yari_tex[0x40];
#else
u8 int_tak_yoroi_yari_tex[] = {
#include "assets/int_tak_yoroi_yari_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_yoroi_head_tex[0x100];
#else
u8 int_tak_yoroi_head_tex[] = {
#include "assets/int_tak_yoroi_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_yoroi_body_tex[0x200];
#else
u8 int_tak_yoroi_body_tex[] = {
#include "assets/int_tak_yoroi_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_yoroi_leg_tex[0x200];
#else
u8 int_tak_yoroi_leg_tex[] = {
#include "assets/int_tak_yoroi_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_yoroi_arm_tex[0x200];
#else
u8 int_tak_yoroi_arm_tex[] = {
#include "assets/int_tak_yoroi_arm_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_yoroi_v[0x960 / sizeof(Vtx)];
#else
Vtx int_tak_yoroi_v[] = {
#include "assets/int_tak_yoroi_v.inc"
};
#endif

Gfx int_tak_yoroi_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_yoroi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_tak_yoroi_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_yoroi_v, 32, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 2, 1),
    gsSPNTriangles_5b(1, 5, 4, 5, 6, 4, 7, 4, 6, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(20, 8, 9, 10, 9, 11, 10, 11, 12, 10),
    gsSPNTriangles_5b(13, 14, 15, 13, 16, 14, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(15, 21, 13, 15, 18, 21, 17, 21, 18, 22, 23, 24),
    gsSPNTriangles_5b(23, 22, 15, 25, 23, 15, 19, 20, 22, 19, 22, 24),
    gsSPNTriangles_5b(14, 26, 25, 15, 14, 25, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(27, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_yoroi_v[32], 8, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 5, 5, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_yoroi_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&int_tak_yoroi_v[40], 28, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 5, 7, 6, 3, 6, 8),
    gsSPNTriangles_5b(8, 1, 3, 8, 9, 1, 1, 10, 2, 8, 11, 12),
    gsSPNTriangles_5b(8, 12, 9, 9, 13, 10, 10, 14, 2, 10, 13, 14),
    gsSPNTriangles_5b(14, 15, 16, 2, 14, 16, 16, 15, 17, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 20, 21, 19, 2, 16, 22, 22, 17, 19),
    gsSPNTriangles_5b(23, 22, 19, 19, 24, 23, 24, 19, 21, 24, 25, 26),
    gsSPNTriangles_5b(23, 24, 26, 23, 26, 27, 23, 27, 0, 22, 23, 0),
    gsSPNTriangles_5b(2, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_tak_yoroi_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_yoroi_v[68], 23, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 1, 0, 4, 1, 3),
    gsSPNTriangles_5b(4, 3, 5, 4, 5, 6, 4, 6, 7, 8, 7, 9),
    gsSPNTriangles_5b(4, 7, 8, 1, 10, 2, 1, 4, 8, 10, 1, 8),
    gsSPNTriangles_5b(10, 8, 11, 12, 13, 14, 13, 15, 14, 13, 16, 15),
    gsSPNTriangles_5b(2, 14, 15, 13, 17, 16, 18, 17, 13, 17, 19, 16),
    gsSPNTriangles_5b(19, 20, 16, 20, 21, 16, 21, 15, 16, 22, 15, 21),
    gsSPNTriangles_5b(2, 15, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_yoroi_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_yoroi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_tak_yoroi_arm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_yoroi_v[91], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 4, 5, 4, 3),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 8, 10, 6, 8, 6, 11, 7),
    gsSPNTriangles_5b(11, 12, 7, 13, 12, 14, 13, 14, 15, 16, 17, 9),
    gsSPNTriangles_5b(16, 9, 18, 18, 13, 15, 18, 15, 16, 19, 20, 21),
    gsSPNTriangles_5b(22, 19, 21, 23, 22, 21, 21, 20, 24, 24, 23, 21),
    gsSPNTriangles_5b(25, 26, 27, 27, 28, 25, 25, 29, 26, 25, 30, 29),
    gsSPNTriangles_5b(25, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_yoroi_v[122], 28, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(4, 5, 0, 1, 6, 3, 6, 7, 3, 8, 7, 9),
    gsSPNTriangles_5b(8, 9, 10, 11, 10, 12, 11, 12, 4, 11, 8, 10),
    gsSPNTriangles_5b(13, 14, 15, 14, 13, 16, 17, 18, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_yoroi_yari_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 19, 20, 21, 22, 23, 24, 22, 24, 25),
    gsSPNTriangles_5b(23, 20, 24, 26, 19, 21, 26, 21, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
