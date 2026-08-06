#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_turkey_chair_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_chair_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_chair_pal[] = {
#include "assets/int_yaz_turkey_chair_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chair_side_tex_txt[0x200];
#else
u8 int_yaz_turkey_chair_side_tex_txt[] = {
#include "assets/int_yaz_turkey_chair_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chair_seet_tex_txt[0x200];
#else
u8 int_yaz_turkey_chair_seet_tex_txt[] = {
#include "assets/int_yaz_turkey_chair_seet_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chair_hane_asi_tex_txt[0x400];
#else
u8 int_yaz_turkey_chair_hane_asi_tex_txt[] = {
#include "assets/int_yaz_turkey_chair_hane_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_turkey_chair_v[0x5A0 / sizeof(Vtx)];
#else
Vtx int_yaz_turkey_chair_v[] = {
#include "assets/int_yaz_turkey_chair_v.inc"
};
#endif

Gfx int_yaz_turkey_chair_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_chair_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_turkey_chair_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_turkey_chair_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 13, 12, 15, 16, 17, 18),
    gsSPNTriangles_5b(18, 19, 16, 20, 17, 16, 20, 16, 21, 19, 18, 22),
    gsSPNTriangles_5b(14, 23, 12, 24, 25, 26, 21, 27, 28, 21, 28, 20),
    gsSPNTriangles_5b(29, 30, 0, 2, 29, 0, 26, 25, 31, 0, 0, 0),
    gsSPVertex(&int_yaz_turkey_chair_v[32], 21, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_turkey_chair_seet_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 11, 12, 13, 14, 15, 16, 16, 17, 14),
    gsSPNTriangles_5b(12, 18, 13, 17, 19, 14, 13, 20, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_yaz_turkey_chair_hane_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_turkey_chair_v[53], 16, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(1, 7, 2, 8, 9, 10, 8, 10, 11, 11, 9, 8),
    gsSPNTriangles_5b(12, 13, 14, 15, 12, 14, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_yaz_turkey_chair_v[69], 21, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPEndDisplayList(),
};
