#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_ito_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_ito_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_ito_pal[] = {
#include "assets/act_mus_ito_a1/int_sum_ito_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_ito_body_txt[0x400];
#else
u8 act_mus_ito_body_txt[] = {
#include "assets/act_mus_ito_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_ito_a1_v[0x4E0 / sizeof(Vtx)];
#else
Vtx act_mus_ito_a1_v[] = {
#include "assets/act_mus_ito_a1_v.inc"
};
#endif

Gfx act_mus_ito_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_ito_a1_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ito_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_ito_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_ito_a1_v[10], 20, 10),
    gsSPNTrianglesInit_5b(14, 2, 0, 10, 4, 2, 11, 4, 13, 12),
    gsSPNTriangles_5b(5, 15, 14, 5, 17, 16, 5, 9, 18, 6, 8, 19),
    gsSPNTriangles_5b(9, 7, 20, 8, 4, 21, 4, 23, 22, 1, 25, 24),
    gsSPNTriangles_5b(3, 5, 26, 1, 3, 27, 0, 29, 28, 0, 0, 0),
    gsSPVertex(&act_mus_ito_a1_v[30], 24, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPNTriangles_5b(7, 8, 9, 10, 7, 11, 1, 0, 3, 6, 2, 12),
    gsSPNTriangles_5b(13, 14, 15, 11, 13, 15, 13, 11, 16, 17, 3, 6),
    gsSPNTriangles_5b(18, 14, 16, 17, 19, 20, 9, 21, 22, 20, 3, 17),
    gsSPNTriangles_5b(9, 8, 21, 20, 23, 4, 9, 11, 7, 19, 23, 20),
    gsSPNTriangles_5b(22, 11, 9, 4, 3, 20, 15, 10, 11, 3, 5, 1),
    gsSPNTriangles_5b(6, 3, 0, 16, 11, 22, 14, 13, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_ito_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ito_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_ito_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_ito_a1_v[54], 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 0, 6, 1),
    gsSPNTriangles_5b(4, 7, 5, 5, 7, 8, 0, 9, 10, 11, 12, 1),
    gsSPNTriangles_5b(13, 14, 15, 4, 16, 17, 6, 18, 1, 4, 19, 7),
    gsSPNTriangles_5b(20, 21, 22, 15, 6, 13, 2, 9, 0, 5, 23, 3),
    gsSPNTriangles_5b(17, 19, 4, 4, 3, 16, 7, 22, 8, 1, 18, 11),
    gsSPNTriangles_5b(12, 2, 1, 10, 13, 6, 8, 23, 5, 10, 6, 0),
    gsSPNTriangles_5b(22, 7, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_ito_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 90, 65479, 1723 } },
    { act_mus_ito_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_ito_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1825, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_ito_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_ito_a1_tbl), 2, cKF_je_r_act_mus_ito_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_ito_a1_c(void) {
    pc_load_asset("assets/act_mus_ito_a1/int_sum_ito_pal.bin", int_sum_ito_pal, 0x20, 0x95D840, 0, 1);
}
#endif
