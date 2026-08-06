#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_donko_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_donko_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_donko_pal[] = {
#include "assets/act_mus_donko_a1/int_sum_donko_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_donko_body_txt[0x200];
#else
u8 act_mus_donko_body_txt[] = {
#include "assets/act_mus_donko_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_donko_a1_v[0x3A0 / sizeof(Vtx)];
#else
Vtx act_mus_donko_a1_v[] = {
#include "assets/act_mus_donko_a1_v.inc"
};
#endif

Gfx act_mus_donko_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_donko_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_donko_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_donko_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_donko_a1_v[6], 16, 6),
    gsSPNTrianglesInit_5b(10, 0, 6, 2, 5, 7, 1, 3, 9, 8),
    gsSPNTriangles_5b(4, 11, 10, 5, 4, 12, 3, 2, 13, 2, 15, 14),
    gsSPNTriangles_5b(5, 17, 16, 2, 19, 18, 5, 21, 20, 0, 0, 0),
    gsSPVertex(&act_mus_donko_a1_v[22], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 0, 4, 1, 12, 13, 14),
    gsSPNTriangles_5b(14, 3, 0, 11, 15, 16, 16, 9, 11, 15, 11, 17),
    gsSPNTriangles_5b(0, 5, 14, 6, 17, 11, 12, 14, 5, 17, 6, 8),
    gsSPNTriangles_5b(8, 7, 18, 19, 13, 12, 11, 10, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_donko_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_donko_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_donko_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_donko_a1_v[42], 16, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 2, 6, 7),
    gsSPNTriangles_5b(8, 9, 3, 1, 6, 2, 3, 9, 4, 2, 10, 0),
    gsSPNTriangles_5b(5, 11, 3, 1, 12, 6, 7, 10, 2, 7, 6, 13),
    gsSPNTriangles_5b(9, 14, 4, 3, 11, 8, 15, 9, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_donko_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_donko_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_donko_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_donko_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_donko_a1_tbl), 2,
                                               cKF_je_r_act_mus_donko_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_donko_a1_c(void) {
    pc_load_asset("assets/act_mus_donko_a1/int_sum_donko_pal.bin", int_sum_donko_pal, 0x20, 0x95A7A0, 0, 1);
}
#endif
