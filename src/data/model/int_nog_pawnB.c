#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_pawnB_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_pawnB_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_pawnB_pal[] = {
#include "assets/int_nog_pawnB_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pawnB_top_tex_txt[0x100];
#else
u8 int_nog_pawnB_top_tex_txt[] = {
#include "assets/int_nog_pawnB_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pawnB_circle_tex_txt[0x80];
#else
u8 int_nog_pawnB_circle_tex_txt[] = {
#include "assets/int_nog_pawnB_circle_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pawnB_base_tex_txt[0x200];
#else
u8 int_nog_pawnB_base_tex_txt[] = {
#include "assets/int_nog_pawnB_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_pawnB_v[0x210 / sizeof(Vtx)];
#else
Vtx int_nog_pawnB_v[] = {
#include "assets/int_nog_pawnB_v.inc"
};
#endif

Gfx int_nog_pawnB_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_pawnB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_pawnB_circle_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_pawnB_v[5], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_pawnB_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(18, 4, 5, 6, 7, 8, 9, 10, 11, 5),
    gsSPNTriangles_5b(12, 13, 14, 15, 16, 17, 18, 19, 13, 19, 10, 20),
    gsSPNTriangles_5b(21, 17, 8, 14, 20, 4, 22, 20, 23, 24, 25, 21),
    gsSPNTriangles_5b(20, 26, 27, 13, 27, 18, 25, 16, 15, 23, 13, 12),
    gsSPNTriangles_5b(5, 11, 26, 9, 24, 7, 6, 5, 22, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_pawnB_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_pawnB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_pawnB_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_pawnB_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_pawnB_tbl[] = { 0, 0, 0 };

s16 cKF_c_int_nog_pawnB_tbl[] = { 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_pawnB = {
    cKF_ckcb_r_int_nog_pawnB_tbl, NULL, NULL, cKF_c_int_nog_pawnB_tbl, -1, 101
};

cKF_Joint_R_c cKF_je_r_int_nog_pawnB_tbl[] = { { int_nog_pawnB_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 4000, 0 } },
                                               { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_nog_pawnB = { ARRAY_COUNT(cKF_je_r_int_nog_pawnB_tbl), 2, cKF_je_r_int_nog_pawnB_tbl };
