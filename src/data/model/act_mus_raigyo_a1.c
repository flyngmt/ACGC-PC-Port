#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_raigyo_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_raigyo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_raigyo_pal[] = {
#include "assets/act_mus_raigyo_a1/int_sum_raigyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_raigyo_body_txt[0x400];
#else
u8 act_mus_raigyo_body_txt[] = {
#include "assets/act_mus_raigyo_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_raigyo_a1_v[0x330 / sizeof(Vtx)];
#else
Vtx act_mus_raigyo_a1_v[] = {
#include "assets/act_mus_raigyo_a1_v.inc"
};
#endif

Gfx act_mus_raigyo_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_raigyo_a1_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_raigyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_raigyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_raigyo_a1_v[4], 16, 4),
    gsSPNTrianglesInit_5b(10, 2, 4, 5, 3, 2, 6, 3, 8, 7),
    gsSPNTriangles_5b(1, 10, 9, 1, 12, 11, 0, 13, 1, 3, 14, 0),
    gsSPNTriangles_5b(3, 16, 15, 2, 1, 17, 2, 18, 19, 0, 0, 0),
    gsSPVertex(&act_mus_raigyo_a1_v[20], 22, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 8, 9, 10, 11, 5, 7, 8, 0),
    gsSPNTriangles_5b(5, 11, 6, 12, 13, 14, 12, 15, 16, 1, 12, 14),
    gsSPNTriangles_5b(17, 18, 19, 12, 16, 13, 15, 12, 1, 19, 20, 21),
    gsSPNTriangles_5b(21, 17, 19, 20, 19, 4, 9, 15, 0, 5, 18, 10),
    gsSPNTriangles_5b(15, 1, 0, 5, 4, 18, 4, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_raigyo_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_raigyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_raigyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_raigyo_a1_v[42], 9, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 5, 2),
    gsSPNTriangles_5b(3, 5, 4, 3, 6, 5, 5, 7, 2, 5, 8, 7),
    gsSPNTriangles_5b(2, 1, 4, 2, 7, 0, 6, 8, 5, 4, 1, 3),
    gsSPNTriangles_5b(0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_raigyo_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 19, 65529, 1723 } },
    { act_mus_raigyo_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_raigyo_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1526, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_raigyo_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_raigyo_a1_tbl), 2,
                                                cKF_je_r_act_mus_raigyo_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_raigyo_a1_c(void) {
    pc_load_asset("assets/act_mus_raigyo_a1/int_sum_raigyo_pal.bin", int_sum_raigyo_pal, 0x20, 0x968240, 0, 1);
}
#endif
