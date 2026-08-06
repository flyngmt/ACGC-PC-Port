#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_bishopB_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_bishopB_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_bishopB_pal[] = {
#include "assets/int_nog_bishopB_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_bishopB_base_tex[0x200];
#else
u8 int_nog_bishopB_base_tex[] = {
#include "assets/int_nog_bishopB_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_bishopB_circle_tex[0x80];
#else
u8 int_nog_bishopB_circle_tex[] = {
#include "assets/int_nog_bishopB_circle_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_bishopB_crown_tex[0x200];
#else
u8 int_nog_bishopB_crown_tex[] = {
#include "assets/int_nog_bishopB_crown_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_bishopB_v[0x2A0 / sizeof(Vtx)];
#else
Vtx int_nog_bishopB_v[] = {
#include "assets/int_nog_bishopB_v.inc"
};
#endif

Gfx int_nog_bishopB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_bishopB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_bishopB_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_bishopB_v, 24, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 1),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 9, 15, 6, 16),
    gsSPNTriangles_5b(17, 13, 4, 10, 16, 0, 18, 16, 19, 20, 21, 17),
    gsSPNTriangles_5b(16, 22, 23, 9, 23, 14, 21, 12, 11, 19, 9, 8),
    gsSPNTriangles_5b(1, 7, 22, 5, 20, 3, 2, 1, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_bishopBT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_bishopB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_bishopB_crown_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_bishopB_v[24], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 6, 7, 8, 4, 7, 4, 9, 9, 10, 11),
    gsSPNTriangles_5b(10, 8, 11, 6, 12, 10, 12, 5, 10, 13, 3, 12),
    gsSPNTriangles_5b(2, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_bishopB_circle_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};
