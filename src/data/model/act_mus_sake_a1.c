#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_sake_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_sake_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_sake_pal[] = {
#include "assets/act_mus_sake_a1/int_sum_sake_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_sake_body_txt[0x300];
#else
u8 act_mus_sake_body_txt[] = {
#include "assets/act_mus_sake_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_sake_a1_v[0x3E0 / sizeof(Vtx)];
#else
Vtx act_mus_sake_a1_v[] = {
#include "assets/act_mus_sake_a1_v.inc"
};
#endif

Gfx act_mus_sake_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_sake_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sake_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_sake_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_sake_a1_v[6], 12, 6),
    gsSPNTrianglesInit_5b(8, 0, 6, 2, 4, 7, 0, 1, 8, 5),
    gsSPNTriangles_5b(3, 9, 1, 2, 10, 11, 3, 12, 13, 1, 15, 14),
    gsSPNTriangles_5b(0, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_sake_a1_v[18], 18, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 0, 5, 9, 8, 10, 11),
    gsSPNTriangles_5b(11, 6, 8, 10, 8, 12, 9, 3, 0, 8, 7, 13),
    gsSPNTriangles_5b(9, 14, 3, 13, 12, 8, 15, 12, 13, 9, 5, 16),
    gsSPNTriangles_5b(16, 14, 9, 13, 17, 15, 7, 17, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_sake_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sake_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_sake_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_sake_a1_v[36], 26, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPNTriangles_5b(3, 5, 7, 0, 8, 1, 5, 9, 7, 6, 8, 0),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(14, 10, 11, 12, 13, 14, 15, 10, 16, 11),
    gsSPNTriangles_5b(14, 17, 15, 18, 17, 14, 15, 19, 13, 17, 20, 21),
    gsSPNTriangles_5b(11, 16, 22, 12, 23, 10, 24, 25, 16, 10, 23, 24),
    gsSPNTriangles_5b(21, 19, 15, 24, 16, 10, 15, 17, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_sake_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 74, 65488, 1103 } },
    { act_mus_sake_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_sake_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1351, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_sake_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_sake_a1_tbl), 2,
                                              cKF_je_r_act_mus_sake_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_sake_a1_c(void) {
    pc_load_asset("assets/act_mus_sake_a1/int_sum_sake_pal.bin", int_sum_sake_pal, 0x20, 0x968B80, 0, 1);
}
#endif
