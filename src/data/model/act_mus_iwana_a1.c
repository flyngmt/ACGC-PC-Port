#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_iwana_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_iwana_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_iwana_pal[] = {
#include "assets/act_mus_iwana_a1/int_sum_iwana_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_iwana_body_txt[0x300];
#else
u8 act_mus_iwana_body_txt[] = {
#include "assets/act_mus_iwana_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_iwana_a1_v[0x400 / sizeof(Vtx)];
#else
Vtx act_mus_iwana_a1_v[] = {
#include "assets/act_mus_iwana_a1_v.inc"
};
#endif

Gfx act_mus_iwana_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_iwana_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_iwana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_iwana_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_iwana_a1_v[8], 14, 8),
    gsSPNTrianglesInit_5b(10, 2, 8, 7, 0, 9, 2, 3, 10, 1),
    gsSPNTriangles_5b(6, 11, 3, 6, 12, 13, 7, 14, 15, 2, 17, 16),
    gsSPNTriangles_5b(3, 19, 18, 4, 7, 20, 6, 5, 21, 0, 0, 0),
    gsSPVertex(&act_mus_iwana_a1_v[22], 18, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 3, 6, 7),
    gsSPNTriangles_5b(3, 8, 4, 2, 9, 0, 10, 9, 2, 5, 11, 12),
    gsSPNTriangles_5b(5, 4, 13, 6, 5, 12, 14, 1, 0, 5, 13, 11),
    gsSPNTriangles_5b(5, 6, 3, 0, 15, 16, 16, 14, 0, 15, 0, 9),
    gsSPNTriangles_5b(1, 17, 2, 2, 17, 10, 7, 8, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_iwana_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_iwana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_iwana_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_iwana_a1_v[40], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 0, 2, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 8, 11, 12, 9, 9, 13, 7),
    gsSPNTriangles_5b(2, 3, 0, 3, 2, 14, 15, 9, 8, 15, 11, 9),
    gsSPNTriangles_5b(2, 6, 14, 14, 4, 3, 8, 10, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_iwana_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 74, 65488, 1201 } },
    { act_mus_iwana_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_iwana_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1351, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_iwana_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_iwana_a1_tbl), 2,
                                               cKF_je_r_act_mus_iwana_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_iwana_a1_c(void) {
    pc_load_asset("assets/act_mus_iwana_a1/int_sum_iwana_pal.bin", int_sum_iwana_pal, 0x20, 0x95E340, 0, 1);
}
#endif
