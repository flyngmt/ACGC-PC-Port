#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_tanago_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_tanago_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_tanago_pal[] = {
#include "assets/act_mus_tanago_a1/int_sum_tanago_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_tanago_body_txt[0x200];
#else
u8 act_mus_tanago_body_txt[] = {
#include "assets/act_mus_tanago_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_tanago_a1_v[0x350 / sizeof(Vtx)];
#else
Vtx act_mus_tanago_a1_v[] = {
#include "assets/act_mus_tanago_a1_v.inc"
};
#endif

Gfx act_mus_tanago_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_tanago_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tanago_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_tanago_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_tanago_a1_v[6], 18, 6),
    gsSPNTrianglesInit_5b(11, 5, 7, 6, 0, 8, 2, 5, 9, 1),
    gsSPNTriangles_5b(5, 11, 10, 2, 13, 12, 3, 2, 14, 4, 15, 16),
    gsSPNTriangles_5b(4, 17, 18, 2, 20, 19, 3, 21, 22, 5, 4, 23),
    gsSPVertex(&act_mus_tanago_a1_v[24], 17, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 5, 9, 10, 5, 8, 0, 4, 1, 11, 3, 0),
    gsSPNTriangles_5b(8, 12, 13, 13, 10, 8, 11, 0, 2, 9, 5, 7),
    gsSPNTriangles_5b(14, 3, 11, 12, 8, 9, 7, 6, 15, 14, 16, 3),
    gsSPEndDisplayList(),
};

Gfx act_mus_tanago_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tanago_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_tanago_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_tanago_a1_v[41], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(7, 4, 3, 7, 3, 8, 2, 9, 0, 2, 1, 10),
    gsSPNTriangles_5b(11, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_tanago_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8, 65524, 697 } },
    { act_mus_tanago_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_tanago_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_tanago_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_tanago_a1_tbl), 2,
                                                cKF_je_r_act_mus_tanago_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_tanago_a1_c(void) {
    pc_load_asset("assets/act_mus_tanago_a1/int_sum_tanago_pal.bin", int_sum_tanago_pal, 0x20, 0x96A600, 0, 1);
}
#endif
