#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_truth01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_truth01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_truth01_pal[] = {
#include "assets/int_ike_jny_truth01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthbases_tex_txt[0x100];
#else
u8 int_ike_jny_truthbases_tex_txt[] = {
#include "assets/int_ike_jny_truthbases_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthbaset_tex_txt[0x40];
#else
u8 int_ike_jny_truthbaset_tex_txt[] = {
#include "assets/int_ike_jny_truthbaset_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthface3_tex_txt[0x200];
#else
u8 int_ike_jny_truthface3_tex_txt[] = {
#include "assets/int_ike_jny_truthface3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthface2_tex_txt[0x80];
#else
u8 int_ike_jny_truthface2_tex_txt[] = {
#include "assets/int_ike_jny_truthface2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthface1_TA_tex_txt[0x200];
#else
u8 int_ike_jny_truthface1_TA_tex_txt[] = {
#include "assets/int_ike_jny_truthface1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_truthface2_TA_tex_txt[0x200];
#else
u8 int_ike_jny_truthface2_TA_tex_txt[] = {
#include "assets/int_ike_jny_truthface2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_truth01_v[0x4A0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_truth01_v[] = {
#include "assets/int_ike_jny_truth01_v.inc"
};
#endif

Gfx int_ike_jny_truth01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_truth01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_truthbases_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_truth01_v, 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_truthbaset_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_truthface3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_truth01_v[24], 13, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(5, 4, 2, 6, 5, 2, 7, 6, 2, 8, 7, 2),
    gsSPNTriangles_5b(9, 8, 2, 10, 9, 2, 11, 10, 2, 12, 11, 2),
    gsSPNTriangles_5b(1, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_jny_truthface2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_truth01_v[37], 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(0, 2, 7, 4, 8, 9, 4, 9, 5, 10, 7, 11),
    gsSPNTriangles_5b(8, 12, 13, 8, 13, 9, 1, 14, 15, 12, 16, 17),
    gsSPNTriangles_5b(12, 17, 13, 1, 15, 2, 16, 18, 19, 16, 19, 17),
    gsSPNTriangles_5b(10, 0, 7, 18, 20, 21, 18, 21, 19, 14, 3, 6),
    gsSPNTriangles_5b(20, 22, 23, 20, 23, 21, 14, 6, 15, 22, 10, 11),
    gsSPNTriangles_5b(22, 11, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_truth01_v[61], 13, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 2, 5, 3, 2),
    gsSPNTriangles_5b(6, 7, 2, 8, 0, 2, 1, 9, 2, 4, 10, 2),
    gsSPNTriangles_5b(7, 11, 2, 12, 8, 2, 10, 12, 2, 9, 6, 2),
    gsSPNTriangles_5b(11, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
