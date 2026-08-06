#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_unagi_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_unagi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_unagi_pal[] = {
#include "assets/act_mus_unagi_a1/int_sum_unagi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_unagi_body_txt[0x200];
#else
u8 act_mus_unagi_body_txt[] = {
#include "assets/act_mus_unagi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_unagi_a1_v[0x900 / sizeof(Vtx)];
#else
Vtx act_mus_unagi_a1_v[] = {
#include "assets/act_mus_unagi_a1_v.inc"
};
#endif

Gfx act_mus_unagi_sakana_tail_model[] = {
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_unagi_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_unagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, act_mus_unagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[8], 20, 8),
    gsSPNTrianglesInit_5b(10, 2, 7, 8, 0, 6, 9, 6, 3, 10),
    gsSPNTriangles_5b(7, 1, 11, 3, 4, 12, 4, 14, 13, 5, 16, 15),
    gsSPNTriangles_5b(7, 17, 18, 6, 19, 20, 5, 2, 21, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 25, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_unagi_sakana_leg2_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_mus_unagi_a1_v[28], 8, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_unagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, act_mus_unagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[36], 18, 8),
    gsSPNTrianglesInit_5b(12, 2, 0, 8, 0, 10, 9, 7, 4, 11),
    gsSPNTriangles_5b(4, 13, 12, 6, 2, 14, 2, 16, 15, 5, 6, 17),
    gsSPNTriangles_5b(6, 19, 18, 3, 7, 20, 7, 22, 21, 1, 3, 23),
    gsSPNTriangles_5b(3, 25, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[54], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 1, 8, 1, 0, 10, 11, 5),
    gsSPNTriangles_5b(10, 5, 4, 12, 13, 9, 12, 9, 8, 14, 15, 11),
    gsSPNTriangles_5b(14, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_unagi_sakana_leg_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_mus_unagi_a1_v[70], 6, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_unagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, act_mus_unagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[76], 12, 6),
    gsSPNTrianglesInit_5b(8, 3, 1, 6, 1, 8, 7, 2, 0, 9),
    gsSPNTriangles_5b(0, 11, 10, 4, 12, 0, 3, 13, 5, 3, 15, 14),
    gsSPNTriangles_5b(0, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[88], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 1, 4, 1, 0),
    gsSPNTriangles_5b(11, 12, 13, 10, 9, 11, 10, 11, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_unagi_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_mus_unagi_a1_v[102], 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_unagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, act_mus_unagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[108], 24, 6),
    gsSPNTrianglesInit_5b(8, 0, 5, 6, 5, 8, 7, 2, 1, 9),
    gsSPNTriangles_5b(1, 11, 10, 5, 3, 12, 3, 14, 13, 4, 2, 15),
    gsSPNTriangles_5b(2, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(8, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 25, 24, 26, 25, 26, 27, 28, 29, 19),
    gsSPNTriangles_5b(28, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_unagi_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_unagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, act_mus_unagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_unagi_a1_v[132], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 2, 3, 4, 5, 3, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 6, 11, 7, 6, 2, 1, 5),
    gsSPNTriangles_5b(6, 10, 11, 2, 4, 0, 8, 9, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_unagi_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 32, 65527, 2095 } },
    { act_mus_unagi_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_unagi_sakana_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1145, 0, 0 } },
    { act_mus_unagi_sakana_leg_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 951, 0, 0 } },
    { act_mus_unagi_sakana_leg2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 849, 0, 0 } },
    { act_mus_unagi_sakana_tail_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_unagi_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_unagi_a1_tbl), 5,
                                               cKF_je_r_act_mus_unagi_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_unagi_a1_c(void) {
    pc_load_asset("assets/act_mus_unagi_a1/int_sum_unagi_pal.bin", int_sum_unagi_pal, 0x20, 0x96B440, 0, 1);
}
#endif
