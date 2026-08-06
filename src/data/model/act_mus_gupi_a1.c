#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_gupi_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_gupi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_gupi_pal[] = {
#include "assets/act_mus_gupi_a1/int_sum_gupi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_gupi_body_txt[0x200];
#else
u8 act_mus_gupi_body_txt[] = {
#include "assets/act_mus_gupi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_gupi_a1_v[0x3C0 / sizeof(Vtx)];
#else
Vtx act_mus_gupi_a1_v[] = {
#include "assets/act_mus_gupi_a1_v.inc"
};
#endif

Gfx act_mus_gupi_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_gupi_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gupi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_gupi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_gupi_a1_v[6], 20, 6),
    gsSPNTrianglesInit_5b(12, 4, 2, 6, 0, 7, 2, 3, 8, 1),
    gsSPNTriangles_5b(5, 9, 10, 3, 11, 12, 2, 13, 14, 3, 5, 15),
    gsSPNTriangles_5b(3, 16, 17, 2, 18, 19, 4, 20, 21, 4, 22, 23),
    gsSPNTriangles_5b(5, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_gupi_a1_v[26], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 0, 2, 5),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 3, 0, 9, 8, 10, 11),
    gsSPNTriangles_5b(11, 6, 8, 8, 12, 13, 12, 8, 7, 14, 15, 16),
    gsSPNTriangles_5b(14, 3, 9, 16, 3, 14, 12, 7, 17, 18, 19, 17),
    gsSPNTriangles_5b(17, 7, 18, 5, 9, 0, 13, 10, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_gupi_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gupi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_gupi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_gupi_a1_v[46], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 5, 2, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 7, 10, 9, 11, 10),
    gsSPNTriangles_5b(5, 4, 0, 10, 7, 9, 0, 2, 5, 10, 12, 13),
    gsSPNTriangles_5b(6, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_gupi_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_gupi_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_gupi_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 631, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_gupi_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_gupi_a1_tbl), 2,
                                              cKF_je_r_act_mus_gupi_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_gupi_a1_c(void) {
    pc_load_asset("assets/act_mus_gupi_a1/int_sum_gupi_pal.bin", int_sum_gupi_pal, 0x20, 0x95BE40, 0, 1);
}
#endif
