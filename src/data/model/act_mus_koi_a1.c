#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_koi_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_koi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_koi_pal[] = {
#include "assets/act_mus_koi_a1/int_sum_koi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_koi_body_txt[0x300];
#else
u8 act_mus_koi_body_txt[] = {
#include "assets/act_mus_koi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_koi_a1_v[0x3C0 / sizeof(Vtx)];
#else
Vtx act_mus_koi_a1_v[] = {
#include "assets/act_mus_koi_a1_v.inc"
};
#endif

Gfx act_mus_koi_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_koi_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_koi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_koi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_koi_a1_v[6], 16, 6),
    gsSPNTrianglesInit_5b(10, 2, 7, 6, 0, 8, 2, 5, 9, 1),
    gsSPNTriangles_5b(5, 11, 10, 3, 2, 12, 5, 4, 13, 2, 15, 14),
    gsSPNTriangles_5b(5, 17, 16, 2, 19, 18, 5, 21, 20, 0, 0, 0),
    gsSPVertex(&act_mus_koi_a1_v[22], 24, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 3, 4, 3, 0, 5),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 8, 9, 10, 10, 6, 8),
    gsSPNTriangles_5b(9, 8, 11, 12, 13, 14, 15, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 20, 21, 22, 23, 21, 23, 14, 17, 18, 15),
    gsSPNTriangles_5b(14, 23, 12, 5, 0, 2, 13, 3, 5, 11, 8, 7),
    gsSPNTriangles_5b(11, 7, 16, 11, 16, 15, 14, 13, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_koi_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_koi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_koi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_koi_a1_v[46], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 2, 7),
    gsSPNTriangles_5b(8, 1, 0, 8, 6, 9, 3, 10, 11, 5, 4, 12),
    gsSPNTriangles_5b(13, 10, 12, 5, 10, 3, 2, 6, 0, 12, 10, 5),
    gsSPNTriangles_5b(0, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_koi_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 56, 65486, 1195 } },
    { act_mus_koi_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_koi_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_koi_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_koi_a1_tbl), 2, cKF_je_r_act_mus_koi_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_koi_a1_c(void) {
    pc_load_asset("assets/act_mus_koi_a1/int_sum_koi_pal.bin", int_sum_koi_pal, 0x20, 0x961DA0, 0, 1);
}
#endif
