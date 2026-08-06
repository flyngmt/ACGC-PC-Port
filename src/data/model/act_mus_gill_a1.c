#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_gill_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_gill_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_gill_pal[] = {
#include "assets/act_mus_gill_a1/int_sum_gill_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_gill_body_txt[0x200];
#else
u8 act_mus_gill_body_txt[] = {
#include "assets/act_mus_gill_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_gill_a1_v[0x380 / sizeof(Vtx)];
#else
Vtx act_mus_gill_a1_v[] = {
#include "assets/act_mus_gill_a1_v.inc"
};
#endif

Gfx act_mus_gill_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_gill_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gill_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_gill_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_gill_a1_v[6], 16, 6),
    gsSPNTrianglesInit_5b(10, 0, 6, 2, 5, 7, 1, 5, 9, 8),
    gsSPNTriangles_5b(2, 11, 10, 5, 13, 12, 3, 2, 14, 5, 4, 15),
    gsSPNTriangles_5b(2, 17, 16, 4, 19, 18, 3, 21, 20, 0, 0, 0),
    gsSPVertex(&act_mus_gill_a1_v[22], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 6, 10, 0, 4, 1, 11, 3, 0),
    gsSPNTriangles_5b(11, 0, 5, 10, 12, 13, 13, 9, 10, 12, 10, 14),
    gsSPNTriangles_5b(14, 10, 6, 14, 6, 8, 15, 16, 8, 11, 17, 18),
    gsSPNTriangles_5b(18, 19, 11, 11, 19, 3, 8, 7, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_gill_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gill_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_gill_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_gill_a1_v[42], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 4, 7, 8, 9, 10, 0, 0, 3, 9),
    gsSPNTriangles_5b(8, 11, 4, 9, 12, 10, 0, 10, 1, 7, 13, 8),
    gsSPNTriangles_5b(4, 11, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_gill_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_gill_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_gill_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_gill_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_gill_a1_tbl), 2,
                                              cKF_je_r_act_mus_gill_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_gill_a1_c(void) {
    pc_load_asset("assets/act_mus_gill_a1/int_sum_gill_pal.bin", int_sum_gill_pal, 0x20, 0x95B6C0, 0, 1);
}
#endif
