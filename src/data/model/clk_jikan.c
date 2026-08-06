#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx clk_jikan_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clk_win_jikan0_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 clk_win_jikan0_TA_tex_txt[] = {
#include "assets/clk_win_jikan0_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan1_TA_tex_txt[0x100];
#else
u8 clk_win_jikan1_TA_tex_txt[] = {
#include "assets/clk_win_jikan1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan2_TA_tex_txt[0x100];
#else
u8 clk_win_jikan2_TA_tex_txt[] = {
#include "assets/clk_win_jikan2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan3_TA_tex_txt[0x100];
#else
u8 clk_win_jikan3_TA_tex_txt[] = {
#include "assets/clk_win_jikan3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan4_TA_tex_txt[0x100];
#else
u8 clk_win_jikan4_TA_tex_txt[] = {
#include "assets/clk_win_jikan4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan5_TA_tex_txt[0x100];
#else
u8 clk_win_jikan5_TA_tex_txt[] = {
#include "assets/clk_win_jikan5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan6_TA_tex_txt[0x100];
#else
u8 clk_win_jikan6_TA_tex_txt[] = {
#include "assets/clk_win_jikan6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan7_TA_tex_txt[0x100];
#else
u8 clk_win_jikan7_TA_tex_txt[] = {
#include "assets/clk_win_jikan7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan8_TA_tex_txt[0x100];
#else
u8 clk_win_jikan8_TA_tex_txt[] = {
#include "assets/clk_win_jikan8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan9_TA_tex_txt[0x100];
#else
u8 clk_win_jikan9_TA_tex_txt[] = {
#include "assets/clk_win_jikan9_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_jikan_TA_tex_txt[0x100];
#else
u8 clk_win_jikan_TA_tex_txt[] = {
#include "assets/clk_win_jikan_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx clk_jikan_v[0x100 / sizeof(Vtx)];
#else
Vtx clk_jikan_v[] = {
#include "assets/clk_jikan_v.inc"
};
#endif

Gfx clk_win_jikan3_bottom_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&clk_jikan_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_jikan1_top_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&clk_jikan_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_jikan2_middle_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(clk_jikan_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_clk_jikan_tbl[] = { { clk_win_jikan1_top_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { clk_win_jikan2_middle_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { clk_win_jikan3_bottom_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_clk_jikan = { ARRAY_COUNT(cKF_je_r_clk_jikan_tbl), 3, cKF_je_r_clk_jikan_tbl };
