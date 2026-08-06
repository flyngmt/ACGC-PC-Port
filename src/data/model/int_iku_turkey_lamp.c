#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_turkey_lamp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_lamp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_turkey_lamp_pal[] = {
#include "assets/int_iku_turkey_lamp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_lamp_c_txt[0x100];
#else
u8 int_iku_turkey_lamp_c_txt[] = {
#include "assets/int_iku_turkey_lamp_c_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_lamp_d_txt[0x100];
#else
u8 int_iku_turkey_lamp_d_txt[] = {
#include "assets/int_iku_turkey_lamp_d_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_lamp_e_txt[0x200];
#else
u8 int_iku_turkey_lamp_e_txt[] = {
#include "assets/int_iku_turkey_lamp_e_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_lamp_b_txt[0x200];
#else
u8 int_iku_turkey_lamp_b_txt[] = {
#include "assets/int_iku_turkey_lamp_b_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_turkey_lamp_a_txt[0x200];
#else
u8 int_iku_turkey_lamp_a_txt[] = {
#include "assets/int_iku_turkey_lamp_a_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_turkey_lamp_v[0x480 / sizeof(Vtx)];
#else
Vtx int_iku_turkey_lamp_v[] = {
#include "assets/int_iku_turkey_lamp_v.inc"
};
#endif

Gfx int_iku_turkey_lamp_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_turkey_lamp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_lamp_c_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_turkey_lamp_v, 28, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 2, 3, 3, 1, 0),
    gsSPNTriangles_5b(4, 5, 6, 5, 7, 6, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(12, 14, 13, 15, 8, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_turkey_lamp_d_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 19, 20, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_lamp_e_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 21, 22, 23, 23, 24, 25, 22, 24, 23),
    gsSPNTriangles_5b(25, 26, 23, 26, 27, 23, 23, 27, 21, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_lamp_b_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_turkey_lamp_v[28], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 2, 5, 0),
    gsSPNTriangles_5b(5, 2, 3, 17, 18, 15, 11, 14, 9, 14, 11, 12),
    gsSPNTriangles_5b(8, 19, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_turkey_lamp_a_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_turkey_lamp_v[48], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
