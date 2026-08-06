#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_nigoi_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_nigoi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_nigoi_pal[] = {
#include "assets/act_mus_nigoi_a1/int_sum_nigoi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_nigoi_body_txt[0x300];
#else
u8 act_mus_nigoi_body_txt[] = {
#include "assets/act_mus_nigoi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_nigoi_a1_v[0x410 / sizeof(Vtx)];
#else
Vtx act_mus_nigoi_a1_v[] = {
#include "assets/act_mus_nigoi_a1_v.inc"
};
#endif

Gfx act_mus_nigoi_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_nigoi_a1_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nigoi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_nigoi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_nigoi_a1_v[7], 20, 7),
    gsSPNTrianglesInit_5b(12, 3, 8, 7, 5, 9, 3, 4, 10, 6),
    gsSPNTriangles_5b(4, 12, 11, 2, 14, 13, 0, 15, 16, 4, 1, 17),
    gsSPNTriangles_5b(1, 18, 19, 0, 3, 20, 4, 22, 21, 3, 24, 23),
    gsSPNTriangles_5b(4, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_nigoi_a1_v[27], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 9, 3, 0, 9, 0, 5),
    gsSPNTriangles_5b(8, 10, 11, 11, 6, 8, 10, 8, 12, 13, 14, 15),
    gsSPNTriangles_5b(16, 17, 9, 12, 8, 7, 12, 7, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_nigoi_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nigoi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_nigoi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_nigoi_a1_v[45], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 9, 10, 11, 9, 12, 13),
    gsSPNTriangles_5b(14, 10, 13, 15, 16, 6, 13, 12, 17, 18, 7, 19),
    gsSPNTriangles_5b(6, 16, 19, 19, 7, 6, 13, 10, 9, 13, 17, 14),
    gsSPNTriangles_5b(8, 15, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_nigoi_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 73, 65482, 1195 } },
    { act_mus_nigoi_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_nigoi_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_nigoi_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_nigoi_a1_tbl), 2,
                                               cKF_je_r_act_mus_nigoi_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_nigoi_a1_c(void) {
    pc_load_asset("assets/act_mus_nigoi_a1/int_sum_nigoi_pal.bin", int_sum_nigoi_pal, 0x20, 0x963E00, 0, 1);
}
#endif
