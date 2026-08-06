#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_keitai_1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_keitai_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_keitai_1_pal[] = {
#include "assets/tol_keitai_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_keitai_1_ueura1_tex_txt[0x100];
#else
u8 tol_keitai_1_ueura1_tex_txt[] = {
#include "assets/tol_keitai_1_ueura1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_keitai_1_ueomote1_tex_txt[0x100];
#else
u8 tol_keitai_1_ueomote1_tex_txt[] = {
#include "assets/tol_keitai_1_ueomote1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_keitai_1_shitaura1_tex_txt[0x100];
#else
u8 tol_keitai_1_shitaura1_tex_txt[] = {
#include "assets/tol_keitai_1_shitaura1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_keitai_1_shitaomote1_tex_txt[0x100];
#else
u8 tol_keitai_1_shitaomote1_tex_txt[] = {
#include "assets/tol_keitai_1_shitaomote1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_keitai_1_v[0x1D0 / sizeof(Vtx)];
#else
Vtx tol_keitai_1_v[] = {
#include "assets/tol_keitai_1_v.inc"
};
#endif

Gfx main1_keitai1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_keitai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_keitai_1_shitaura1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_keitai_1_v[15], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(6, 4, 3, 6, 3, 2, 0, 7, 8, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 0, 5, 7, 1, 9, 6, 3, 4, 0),
    gsSPNTriangles_5b(1, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_keitai_1_shitaomote1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main2_keitai1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_keitai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_keitai_1_ueura1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_keitai_1_v, 15, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(6, 1, 0, 3, 7, 8, 6, 5, 1, 4, 6, 8),
    gsSPNTriangles_5b(7, 9, 10, 2, 9, 7, 8, 6, 0, 0, 3, 8),
    gsSPNTriangles_5b(8, 7, 10, 8, 10, 4, 7, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_keitai_1_ueomote1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 11, 13, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_keitai_1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { main1_keitai1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { main2_keitai1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_keitai_1 = { ARRAY_COUNT(cKF_je_r_tol_keitai_1_tbl), 2, cKF_je_r_tol_keitai_1_tbl };
