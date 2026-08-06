#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_oikawa_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_oikawa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_oikawa_pal[] = {
#include "assets/act_mus_oikawa_a1/int_sum_oikawa_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_oikawa_body_txt[0x200];
#else
u8 act_mus_oikawa_body_txt[] = {
#include "assets/act_mus_oikawa_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_oikawa_a1_v[0x380 / sizeof(Vtx)];
#else
Vtx act_mus_oikawa_a1_v[] = {
#include "assets/act_mus_oikawa_a1_v.inc"
};
#endif

Gfx act_mus_oikawa_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_oikawa_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_oikawa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_oikawa_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_oikawa_a1_v[6], 24, 6),
    gsSPNTrianglesInit_5b(8, 0, 2, 6, 4, 7, 2, 3, 8, 5),
    gsSPNTriangles_5b(1, 10, 9, 0, 12, 11, 3, 14, 13, 2, 16, 15),
    gsSPNTriangles_5b(3, 1, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(10, 18, 19, 20, 18, 21, 22, 23, 18, 20),
    gsSPNTriangles_5b(24, 25, 26, 18, 22, 19, 21, 18, 23, 26, 27, 28),
    gsSPNTriangles_5b(28, 24, 26, 27, 26, 29, 29, 26, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_oikawa_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_oikawa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_oikawa_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_oikawa_a1_v[30], 26, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 6, 7),
    gsSPNTriangles_5b(3, 7, 8, 2, 1, 9, 2, 10, 0, 5, 6, 3),
    gsSPNTriangles_5b(8, 4, 3, 9, 11, 10, 9, 10, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(12, 12, 13, 14, 15, 16, 17, 18, 19, 12),
    gsSPNTriangles_5b(20, 21, 17, 17, 16, 22, 21, 23, 15, 12, 24, 18),
    gsSPNTriangles_5b(19, 13, 12, 14, 25, 24, 17, 22, 20, 14, 24, 12),
    gsSPNTriangles_5b(17, 21, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_oikawa_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 58, 65529, 803 } },
    { act_mus_oikawa_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_oikawa_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_oikawa_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_oikawa_a1_tbl), 2,
                                                cKF_je_r_act_mus_oikawa_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_oikawa_a1_c(void) {
    pc_load_asset("assets/act_mus_oikawa_a1/int_sum_oikawa_pal.bin", int_sum_oikawa_pal, 0x20, 0x9658E0, 0, 1);
}
#endif
