#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_funa_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_funa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_funa_pal[] = {
#include "assets/act_mus_funa_a1/int_sum_funa_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_funa_body_txt[0x200];
#else
u8 act_mus_funa_body_txt[] = {
#include "assets/act_mus_funa_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_funa_a1_v[0x380 / sizeof(Vtx)];
#else
Vtx act_mus_funa_a1_v[] = {
#include "assets/act_mus_funa_a1_v.inc"
};
#endif

Gfx act_mus_funa_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_funa_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_funa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_funa_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_funa_a1_v[6], 20, 6),
    gsSPNTrianglesInit_5b(12, 5, 6, 7, 5, 8, 9, 2, 10, 11),
    gsSPNTriangles_5b(2, 12, 13, 5, 15, 14, 2, 17, 16, 3, 19, 18),
    gsSPNTriangles_5b(5, 3, 20, 2, 0, 21, 1, 5, 22, 4, 24, 23),
    gsSPNTriangles_5b(4, 2, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_funa_a1_v[26], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTriangles_5b(5, 6, 7, 8, 6, 5, 9, 4, 10, 5, 11, 12),
    gsSPNTriangles_5b(12, 8, 5, 10, 4, 0, 10, 13, 9, 14, 15, 7),
    gsSPNTriangles_5b(7, 6, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_funa_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_funa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_funa_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_funa_a1_v[42], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 2, 6, 7),
    gsSPNTriangles_5b(8, 1, 0, 8, 7, 9, 10, 11, 3, 5, 4, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 10, 5, 0, 7, 8, 2, 7, 0),
    gsSPNTriangles_5b(5, 10, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_funa_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 40, 65499, 795 } },
    { act_mus_funa_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_funa_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_funa_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_funa_a1_tbl), 2,
                                              cKF_je_r_act_mus_funa_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_funa_a1_c(void) {
    pc_load_asset("assets/act_mus_funa_a1/int_sum_funa_pal.bin", int_sum_funa_pal, 0x20, 0x95AF40, 0, 1);
}
#endif
