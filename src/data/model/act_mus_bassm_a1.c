#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_bassm_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_bassm_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_bassm_pal[] = {
#include "assets/act_mus_bassm_a1/int_sum_bassm_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_bassm_body_txt[0x300];
#else
u8 act_mus_bassm_body_txt[] = {
#include "assets/act_mus_bassm_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_bassm_a1_v[0x3A0 / sizeof(Vtx)];
#else
Vtx act_mus_bassm_a1_v[] = {
#include "assets/act_mus_bassm_a1_v.inc"
};
#endif

Gfx act_mus_bassm_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_bassm_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bassm_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_bassm_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_bassm_a1_v[6], 16, 6),
    gsSPNTrianglesInit_5b(10, 0, 6, 2, 5, 7, 1, 5, 9, 8),
    gsSPNTriangles_5b(2, 11, 10, 5, 13, 12, 2, 15, 14, 3, 2, 16),
    gsSPNTriangles_5b(4, 17, 18, 3, 19, 20, 5, 4, 21, 0, 0, 0),
    gsSPVertex(&act_mus_bassm_a1_v[22], 22, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 4, 5, 3, 0),
    gsSPNTriangles_5b(6, 7, 8, 9, 7, 6, 10, 7, 9, 0, 4, 1),
    gsSPNTriangles_5b(11, 12, 13, 9, 14, 15, 15, 10, 9, 0, 2, 5),
    gsSPNTriangles_5b(6, 14, 9, 5, 13, 12, 8, 16, 6, 17, 18, 16),
    gsSPNTriangles_5b(16, 8, 19, 13, 20, 21, 12, 3, 5, 16, 19, 17),
    gsSPNTriangles_5b(21, 11, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_bassm_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bassm_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_bassm_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_bassm_a1_v[44], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 0, 6, 7),
    gsSPNTriangles_5b(8, 9, 5, 5, 10, 8, 7, 11, 0, 8, 12, 9),
    gsSPNTriangles_5b(4, 10, 5, 5, 9, 3, 6, 13, 7, 0, 11, 1),
    gsSPNTriangles_5b(2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_bassm_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8, 65524, 999 } },
    { act_mus_bassm_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_bassm_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_bassm_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_bassm_a1_tbl), 2,
                                               cKF_je_r_act_mus_bassm_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_bassm_a1_c(void) {
    pc_load_asset("assets/act_mus_bassm_a1/int_sum_bassm_pal.bin", int_sum_bassm_pal, 0x20, 0x958CE0, 0, 1);
}
#endif
