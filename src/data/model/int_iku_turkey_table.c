#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_turkey_table_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_table_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_table_pal[] = {
#include "assets/int_iku_turkey_table_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_table_a_txt[0x200];
#else
u8 int_iku_turkey_table_a_txt[] = {
#include "assets/int_iku_turkey_table_a_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_table_b_txt[0x100];
#else
u8 int_iku_turkey_table_b_txt[] = {
#include "assets/int_iku_turkey_table_b_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_table_d_txt[0x200];
#else
u8 int_iku_turkey_table_d_txt[] = {
#include "assets/int_iku_turkey_table_d_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_table_e_txt[0x100];
#else
u8 int_iku_turkey_table_e_txt[] = {
#include "assets/int_iku_turkey_table_e_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_table_c_txt[0x100];
#else
u8 int_iku_turkey_table_c_txt[] = {
#include "assets/int_iku_turkey_table_c_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_turkey_table_v[0x390 / sizeof(Vtx)];
#else
Vtx int_iku_turkey_table_v[] = {
#include "assets/int_iku_turkey_table_v.inc"
};
#endif

Gfx int_iku_turkey_table_model_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_turkey_table_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_table_a_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_turkey_table_v, 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 4, 5, 1, 6),
    gsSPNTriangles_5b(2, 1, 5, 7, 3, 4, 2, 5, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 12, 13, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_turkey_table_b_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 15, 16, 17, 15, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 22, 21, 23, 21, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 24, 29, 30, 24, 30, 23, 28, 18, 17),
    gsSPNTriangles_5b(28, 17, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_table_d_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_turkey_table_v[31], 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_table_e_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 9, 10, 11, 11, 12, 9),
    gsSPNTriangles_5b(11, 10, 12, 13, 14, 15, 13, 15, 16, 16, 14, 13),
    gsSPNTriangles_5b(17, 18, 19, 19, 20, 17, 20, 18, 17, 21, 7, 6),
    gsSPNTriangles_5b(8, 21, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_turkey_table_model_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_turkey_table_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_table_c_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_turkey_table_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
