#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_wakasa_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_wakasagi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_wakasagi_pal[] = {
#include "assets/act_mus_wakasa_a1/int_sum_wakasagi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_wakasagi_body_txt[0x100];
#else
u8 act_mus_wakasagi_body_txt[] = {
#include "assets/act_mus_wakasagi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_wakasa_a1_v[0x3E0 / sizeof(Vtx)];
#else
Vtx act_mus_wakasa_a1_v[] = {
#include "assets/act_mus_wakasa_a1_v.inc"
};
#endif

Gfx act_mus_wakasa_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_wakasa_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wakasagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_wakasagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_wakasa_a1_v[8], 14, 8),
    gsSPNTrianglesInit_5b(10, 3, 9, 8, 2, 6, 10, 7, 3, 11),
    gsSPNTriangles_5b(2, 12, 13, 6, 0, 14, 1, 7, 15, 2, 16, 17),
    gsSPNTriangles_5b(2, 18, 4, 5, 19, 20, 5, 21, 3, 0, 0, 0),
    gsSPVertex(&act_mus_wakasa_a1_v[22], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(0, 4, 1, 7, 8, 9, 9, 5, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_wakasa_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wakasagi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_wakasagi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_wakasa_a1_v[32], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 2, 1),
    gsSPNTriangles_5b(6, 1, 7, 2, 8, 0, 9, 10, 11, 5, 12, 3),
    gsSPNTriangles_5b(13, 14, 7, 11, 10, 15, 11, 12, 5, 11, 5, 9),
    gsSPNTriangles_5b(7, 14, 6, 15, 12, 11, 7, 1, 13, 0, 0, 0),
    gsSPNTrianglesInit_5b(12, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 18, 22, 25, 20, 22, 26, 25, 18, 27, 19),
    gsSPNTriangles_5b(18, 24, 27, 28, 26, 22, 21, 29, 22, 18, 17, 23),
    gsSPNTriangles_5b(22, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_wakasa_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 65529, 697 } },
    { act_mus_wakasa_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_wakasa_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_wakasa_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_wakasa_a1_tbl), 2,
                                                cKF_je_r_act_mus_wakasa_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_wakasa_a1_c(void) {
    pc_load_asset("assets/act_mus_wakasa_a1/int_sum_wakasagi_pal.bin", int_sum_wakasagi_pal, 0x20, 0x96C340, 0, 1);
}
#endif
