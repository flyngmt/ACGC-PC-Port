#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_yamame_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_yamame_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_yamame_pal[] = {
#include "assets/act_mus_yamame_a1/int_sum_yamame_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_yamame_body_txt[0x300];
#else
u8 act_mus_yamame_body_txt[] = {
#include "assets/act_mus_yamame_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_yamame_a1_v[0x420 / sizeof(Vtx)];
#else
Vtx act_mus_yamame_a1_v[] = {
#include "assets/act_mus_yamame_a1_v.inc"
};
#endif

Gfx act_mus_yamame_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_yamame_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_yamame_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_yamame_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_yamame_a1_v[6], 16, 6),
    gsSPNTrianglesInit_5b(10, 2, 0, 6, 4, 7, 0, 1, 8, 5),
    gsSPNTriangles_5b(3, 9, 10, 2, 11, 12, 3, 13, 14, 0, 16, 15),
    gsSPNTriangles_5b(1, 18, 17, 2, 19, 20, 1, 3, 21, 0, 0, 0),
    gsSPVertex(&act_mus_yamame_a1_v[22], 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 0, 5, 9, 8, 10, 11),
    gsSPNTriangles_5b(11, 6, 8, 10, 8, 12, 9, 13, 0, 8, 14, 15),
    gsSPNTriangles_5b(15, 12, 8, 13, 3, 0, 8, 7, 14, 13, 16, 3),
    gsSPNTriangles_5b(17, 5, 18, 19, 12, 20, 7, 21, 14, 20, 22, 19),
    gsSPNTriangles_5b(18, 23, 17, 14, 21, 15, 9, 16, 13, 15, 20, 12),
    gsSPNTriangles_5b(5, 17, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_yamame_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_yamame_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_yamame_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_yamame_a1_v[46], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 9, 10, 11, 12, 13, 6),
    gsSPNTriangles_5b(14, 7, 6, 14, 6, 13, 11, 15, 16, 17, 18, 15),
    gsSPNTriangles_5b(11, 10, 17, 13, 19, 14, 15, 11, 17, 16, 9, 11),
    gsSPNTriangles_5b(6, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_yamame_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 74, 65488, 999 } },
    { act_mus_yamame_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_yamame_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 899, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_yamame_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_yamame_a1_tbl), 2,
                                                cKF_je_r_act_mus_yamame_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_yamame_a1_c(void) {
    pc_load_asset("assets/act_mus_yamame_a1/int_sum_yamame_pal.bin", int_sum_yamame_pal, 0x20, 0x96CA20, 0, 1);
}
#endif
