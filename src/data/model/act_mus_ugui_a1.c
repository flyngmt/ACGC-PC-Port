#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_ugui_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_ugui_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_ugui_pal[] = {
#include "assets/act_mus_ugui_a1/int_sum_ugui_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_ugui_body_txt[0x300];
#else
u8 act_mus_ugui_body_txt[] = {
#include "assets/act_mus_ugui_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_ugui_a1_v[0x2E0 / sizeof(Vtx)];
#else
Vtx act_mus_ugui_a1_v[] = {
#include "assets/act_mus_ugui_a1_v.inc"
};
#endif

Gfx act_mus_ugui_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_ugui_a1_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ugui_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_ugui_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_ugui_a1_v[4], 16, 4),
    gsSPNTrianglesInit_5b(10, 0, 4, 1, 3, 5, 0, 3, 7, 6),
    gsSPNTriangles_5b(3, 9, 8, 1, 11, 10, 1, 13, 12, 2, 15, 14),
    gsSPNTriangles_5b(3, 2, 16, 2, 18, 17, 2, 1, 19, 0, 0, 0),
    gsSPVertex(&act_mus_ugui_a1_v[20], 17, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 7, 6, 0, 4, 1, 10, 11, 12),
    gsSPNTriangles_5b(6, 2, 13, 13, 9, 6, 2, 6, 14, 14, 8, 15),
    gsSPNTriangles_5b(12, 11, 5, 14, 6, 8, 11, 3, 0, 11, 0, 5),
    gsSPNTriangles_5b(15, 8, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_ugui_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ugui_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_ugui_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_ugui_a1_v[37], 9, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 1, 3),
    gsSPNTriangles_5b(4, 5, 6, 2, 1, 4, 6, 7, 4, 0, 8, 5),
    gsSPNTriangles_5b(7, 8, 0, 4, 7, 2, 3, 5, 4, 5, 3, 0),
    gsSPNTriangles_5b(0, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_ugui_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 73, 65482, 1195 } },
    { act_mus_ugui_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_ugui_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1080, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_ugui_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_ugui_a1_tbl), 2,
                                              cKF_je_r_act_mus_ugui_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_ugui_a1_c(void) {
    pc_load_asset("assets/act_mus_ugui_a1/int_sum_ugui_pal.bin", int_sum_ugui_pal, 0x20, 0x96AD40, 0, 1);
}
#endif
