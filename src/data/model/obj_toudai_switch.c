#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_toudai_switch_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_toudai_switch_pal[] = {
#include "assets/obj_toudai_switch_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_switch_tex_txt[0x80];
#else
u8 obj_toudai_switch_tex_txt[] = {
#include "assets/obj_toudai_switch_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_toudai_switch_v[0xB0 / sizeof(Vtx)];
#else
Vtx obj_toudai_switch_v[] = {
#include "assets/obj_toudai_switch_v.inc"
};
#endif

Gfx obj_toudai_switch_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_switch_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_toudai_switch_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(obj_toudai_switch_v, 11, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 8, 9, 7, 8),
    gsSPNTriangles_5b(9, 8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_toudai_switch_tbl[] = { 0, 2 };

s16 cKF_kn_obj_toudai_switch_tbl[] = { 11 };

s16 cKF_c_obj_toudai_switch_tbl[] = { 19200, 6000, 8800, -900, 0, 0, 0, -1350 };

s16 cKF_ds_obj_toudai_switch_tbl[] = { 1,    -150, 0,   20,   -150, 0,   21,  -150, 1055, 22,   -80,
                                       3375, 24,   230, 3375, 25,   300, 830, 26,   285,  -450, 27,
                                       270,  225,  28,  300,  450,  29,  300, 0,    48,   300,  0 };

cKF_Animation_R_c cKF_ba_r_obj_toudai_switch = { cKF_ckcb_r_obj_toudai_switch_tbl,
                                                 cKF_ds_obj_toudai_switch_tbl,
                                                 cKF_kn_obj_toudai_switch_tbl,
                                                 cKF_c_obj_toudai_switch_tbl,
                                                 -1,
                                                 48 };

u8 cKF_ckcb_r_obj_toudai_switch_off_tbl[] = { 0, 2 };

s16 cKF_kn_obj_toudai_switch_off_tbl[] = { 9 };

s16 cKF_c_obj_toudai_switch_off_tbl[] = { 19200, 6000, 8800, -900, 0, 0, 0, -1350 };

s16 cKF_ds_obj_toudai_switch_off_tbl[] = { 1,   300, -378, 2,    287, -702, 10,   -137, -702, 11, -150, 111,  12, -130,
                                           150, 13,  -140, -300, 14,  -150, -150, 15,   -150, 0,  48,   -150, 0 };

cKF_Animation_R_c cKF_ba_r_obj_toudai_switch_off = { cKF_ckcb_r_obj_toudai_switch_off_tbl,
                                                     cKF_ds_obj_toudai_switch_off_tbl,
                                                     cKF_kn_obj_toudai_switch_off_tbl,
                                                     cKF_c_obj_toudai_switch_off_tbl,
                                                     -1,
                                                     48 };

cKF_Joint_R_c cKF_je_r_obj_toudai_switch_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 19200, 6000, 8800 } },
    { obj_toudai_switch_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_toudai_switch = { ARRAY_COUNT(cKF_je_r_obj_toudai_switch_tbl), 1,
                                                cKF_je_r_obj_toudai_switch_tbl };
