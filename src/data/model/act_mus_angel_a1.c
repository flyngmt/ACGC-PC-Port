#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_angel_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_mus_angel_body_txt[0xC00];
#else
ATTRIBUTE_ALIGN(32) u8 act_mus_angel_body_txt[] = {
#include "assets/act_mus_angel_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_angel_a1_v[0x360 / sizeof(Vtx)];
#else
Vtx act_mus_angel_a1_v[] = {
#include "assets/act_mus_angel_a1_v.inc"
};
#endif

Gfx act_mus_angel_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_angel_a1_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, act_mus_angel_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_angel_a1_v[7], 18, 7),
    gsSPNTrianglesInit_5b(11, 4, 7, 8, 0, 9, 2, 4, 10, 1),
    gsSPNTriangles_5b(4, 12, 11, 2, 13, 14, 4, 5, 15, 6, 2, 16),
    gsSPNTriangles_5b(3, 18, 17, 5, 19, 20, 5, 21, 22, 6, 23, 24),
    gsSPVertex(&act_mus_angel_a1_v[25], 15, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 7, 8, 9, 6, 5, 0, 4, 1, 5, 10, 11),
    gsSPNTriangles_5b(11, 9, 5, 12, 13, 3, 12, 3, 0, 8, 7, 14),
    gsSPEndDisplayList(),
};

Gfx act_mus_angel_sakana_head_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, act_mus_angel_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_angel_a1_v[40], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(1, 7, 2, 2, 7, 8, 9, 6, 3, 2, 10, 0),
    gsSPNTriangles_5b(5, 11, 3, 12, 6, 9, 3, 11, 9, 8, 7, 13),
    gsSPNTriangles_5b(8, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_angel_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8, 65524, 699 } },
    { act_mus_angel_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_angel_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_angel_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_angel_a1_tbl), 2,
                                               cKF_je_r_act_mus_angel_a1_tbl };
