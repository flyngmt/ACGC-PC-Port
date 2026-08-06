#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_turkey_watch_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_turkey_clk_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_turkey_clk_pal[] = {
#include "assets/int_yos_turkey_clk_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_hari_tex_txt[0x100];
#else
u8 int_yos_turkey_clk_hari_tex_txt[] = {
#include "assets/int_yos_turkey_clk_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_ashi_tex_txt[0x80];
#else
u8 int_yos_turkey_clk_ashi_tex_txt[] = {
#include "assets/int_yos_turkey_clk_ashi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_yubi_tex_txt[0x80];
#else
u8 int_yos_turkey_clk_yubi_tex_txt[] = {
#include "assets/int_yos_turkey_clk_yubi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_sukart_tex_txt[0x100];
#else
u8 int_yos_turkey_clk_sukart_tex_txt[] = {
#include "assets/int_yos_turkey_clk_sukart_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_mae_tex_txt[0x400];
#else
u8 int_yos_turkey_clk_mae_tex_txt[] = {
#include "assets/int_yos_turkey_clk_mae_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_turkey_clk_ato_tex_txt[0x20];
#else
u8 int_yos_turkey_clk_ato_tex_txt[] = {
#include "assets/int_yos_turkey_clk_ato_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_turkey_watch_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_yos_turkey_watch_v[] = {
#include "assets/int_yos_turkey_watch_v.inc"
};
#endif

Gfx int_yos_turkey_clk_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_turkey_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yos_turkey_clk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_turkey_watch_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yos_turkey_clk_obj_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_turkey_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_yos_turkey_clk_ashi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yos_turkey_watch_v[6], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 1, 3, 4, 2, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_yos_turkey_clk_yubi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 5, 6, 7, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(9, 8, 10, 13, 6, 5, 12, 11, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yos_turkey_clk_sukart_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 15, 16, 17, 18, 19, 17, 15, 20, 21),
    gsSPNTriangles_5b(18, 22, 21, 16, 23, 17, 22, 23, 21, 17, 23, 22),
    gsSPNTriangles_5b(21, 23, 16, 21, 16, 15, 21, 20, 18, 17, 22, 18),
    gsSPNTriangles_5b(17, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_yos_turkey_clk_mae_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 24, 26, 27, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_yos_turkey_clk_ato_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yos_turkey_watch_v[36], 10, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(7, 0, 8, 6, 5, 8, 6, 8, 2, 6, 1, 9),
    gsSPNTriangles_5b(8, 4, 7, 9, 3, 6, 6, 2, 1, 8, 5, 4),
    gsSPNTriangles_5b(2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yos_turkey_clk_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_turkey_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yos_turkey_clk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yos_turkey_watch_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_yos_turkey_watch_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_yos_turkey_watch_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_yos_turkey_watch = { cKF_ckcb_r_int_yos_turkey_watch_tbl, NULL, NULL,
                                                    cKF_c_int_yos_turkey_watch_tbl,      -1,   13 };

cKF_Joint_R_c cKF_je_r_int_yos_turkey_watch_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_yos_turkey_clk_obj_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 5000, 0, 0 } },
    { int_yos_turkey_clk_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_yos_turkey_clk_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 5000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_yos_turkey_watch = { ARRAY_COUNT(cKF_je_r_int_yos_turkey_watch_tbl), 3,
                                                   cKF_je_r_int_yos_turkey_watch_tbl };
