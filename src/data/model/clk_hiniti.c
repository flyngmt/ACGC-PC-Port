#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx clk_hiniti_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clk_win_suuji1_TA_tex_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 clk_win_suuji1_TA_tex_txt[] = {
#include "assets/clk_win_suuji1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji2_TA_tex_txt[0x400];
#else
u8 clk_win_suuji2_TA_tex_txt[] = {
#include "assets/clk_win_suuji2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji3_TA_tex_txt[0x400];
#else
u8 clk_win_suuji3_TA_tex_txt[] = {
#include "assets/clk_win_suuji3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji4_TA_tex_txt[0x400];
#else
u8 clk_win_suuji4_TA_tex_txt[] = {
#include "assets/clk_win_suuji4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji5_TA_tex_txt[0x400];
#else
u8 clk_win_suuji5_TA_tex_txt[] = {
#include "assets/clk_win_suuji5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji6_TA_tex_txt[0x400];
#else
u8 clk_win_suuji6_TA_tex_txt[] = {
#include "assets/clk_win_suuji6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji7_TA_tex_txt[0x400];
#else
u8 clk_win_suuji7_TA_tex_txt[] = {
#include "assets/clk_win_suuji7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji8_TA_tex_txt[0x400];
#else
u8 clk_win_suuji8_TA_tex_txt[] = {
#include "assets/clk_win_suuji8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji9_TA_tex_txt[0x400];
#else
u8 clk_win_suuji9_TA_tex_txt[] = {
#include "assets/clk_win_suuji9_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji10_TA_tex_txt[0x400];
#else
u8 clk_win_suuji10_TA_tex_txt[] = {
#include "assets/clk_win_suuji10_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji11_TA_tex_txt[0x400];
#else
u8 clk_win_suuji11_TA_tex_txt[] = {
#include "assets/clk_win_suuji11_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji12_TA_tex_txt[0x400];
#else
u8 clk_win_suuji12_TA_tex_txt[] = {
#include "assets/clk_win_suuji12_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji13_TA_tex_txt[0x400];
#else
u8 clk_win_suuji13_TA_tex_txt[] = {
#include "assets/clk_win_suuji13_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji14_TA_tex_txt[0x400];
#else
u8 clk_win_suuji14_TA_tex_txt[] = {
#include "assets/clk_win_suuji14_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji15_TA_tex_txt[0x400];
#else
u8 clk_win_suuji15_TA_tex_txt[] = {
#include "assets/clk_win_suuji15_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji16_TA_tex_txt[0x400];
#else
u8 clk_win_suuji16_TA_tex_txt[] = {
#include "assets/clk_win_suuji16_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji17_TA_tex_txt[0x400];
#else
u8 clk_win_suuji17_TA_tex_txt[] = {
#include "assets/clk_win_suuji17_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji18_TA_tex_txt[0x400];
#else
u8 clk_win_suuji18_TA_tex_txt[] = {
#include "assets/clk_win_suuji18_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji19_TA_tex_txt[0x400];
#else
u8 clk_win_suuji19_TA_tex_txt[] = {
#include "assets/clk_win_suuji19_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji20_TA_tex_txt[0x400];
#else
u8 clk_win_suuji20_TA_tex_txt[] = {
#include "assets/clk_win_suuji20_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji21_TA_tex_txt[0x400];
#else
u8 clk_win_suuji21_TA_tex_txt[] = {
#include "assets/clk_win_suuji21_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji22_TA_tex_txt[0x400];
#else
u8 clk_win_suuji22_TA_tex_txt[] = {
#include "assets/clk_win_suuji22_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji23_TA_tex_txt[0x400];
#else
u8 clk_win_suuji23_TA_tex_txt[] = {
#include "assets/clk_win_suuji23_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji24_TA_tex_txt[0x400];
#else
u8 clk_win_suuji24_TA_tex_txt[] = {
#include "assets/clk_win_suuji24_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji25_TA_tex_txt[0x400];
#else
u8 clk_win_suuji25_TA_tex_txt[] = {
#include "assets/clk_win_suuji25_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji26_TA_tex_txt[0x400];
#else
u8 clk_win_suuji26_TA_tex_txt[] = {
#include "assets/clk_win_suuji26_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji27_TA_tex_txt[0x400];
#else
u8 clk_win_suuji27_TA_tex_txt[] = {
#include "assets/clk_win_suuji27_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji28_TA_tex_txt[0x400];
#else
u8 clk_win_suuji28_TA_tex_txt[] = {
#include "assets/clk_win_suuji28_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji29_TA_tex_txt[0x400];
#else
u8 clk_win_suuji29_TA_tex_txt[] = {
#include "assets/clk_win_suuji29_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji30_TA_tex_txt[0x400];
#else
u8 clk_win_suuji30_TA_tex_txt[] = {
#include "assets/clk_win_suuji30_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_suuji31_TA_tex_txt[0x400];
#else
u8 clk_win_suuji31_TA_tex_txt[] = {
#include "assets/clk_win_suuji31_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx clk_hiniti_v[0x100 / sizeof(Vtx)];
#else
Vtx clk_hiniti_v[] = {
#include "assets/clk_hiniti_v.inc"
};
#endif

Gfx clk_win_hiniti3_bottom_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&clk_hiniti_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_hiniti1_top_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&clk_hiniti_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_hiniti2_middle_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(clk_hiniti_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_clk_hiniti_tbl[] = { { clk_win_hiniti1_top_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { clk_win_hiniti2_middle_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { clk_win_hiniti3_bottom_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_clk_hiniti = { ARRAY_COUNT(cKF_je_r_clk_hiniti_tbl), 3, cKF_je_r_clk_hiniti_tbl };
