#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_burner_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_burner_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_burner_pal[] = {
#include "assets/int_nog_burner_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_burner_gas_tex[0x100];
#else
u8 int_nog_burner_gas_tex[] = {
#include "assets/int_nog_burner_gas_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_burner_side_tex[0x400];
#else
u8 int_nog_burner_side_tex[] = {
#include "assets/int_nog_burner_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_burner_top_tex[0x200];
#else
u8 int_nog_burner_top_tex[] = {
#include "assets/int_nog_burner_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_burner_v[0x6F0 / sizeof(Vtx)];
#else
Vtx int_nog_burner_v[] = {
#include "assets/int_nog_burner_v.inc"
};
#endif

Gfx int_nog_burner_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_burner_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_burner_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_burner_v, 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_burner_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_burner_v[18], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_burner_v[50], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_burner_gas_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_nog_burner_v[54], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 2, 8, 6, 6, 9, 2, 10, 11, 12),
    gsSPNTriangles_5b(12, 13, 10, 10, 14, 15, 15, 16, 10, 12, 17, 18),
    gsSPNTriangles_5b(18, 19, 12, 20, 21, 18, 18, 22, 20, 20, 23, 24),
    gsSPNTriangles_5b(24, 25, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_burner_v[86], 25, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 18, 0, 22, 23, 2),
    gsSPNTriangles_5b(2, 24, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(12, 13, 14, 15, 16, 17, 19, 20, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
