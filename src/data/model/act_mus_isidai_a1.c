#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_isidai_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_isidai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_isidai_pal[] = {
#include "assets/act_mus_isidai_a1/int_nog_isidai_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_isidai_body_txt[0x300];
#else
u8 act_mus_isidai_body_txt[] = {
#include "assets/act_mus_isidai_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_isidai_a1_v[0x420 / sizeof(Vtx)];
#else
Vtx act_mus_isidai_a1_v[] = {
#include "assets/act_mus_isidai_a1_v.inc"
};
#endif

Gfx act_mus_isidai_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_isidai_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_isidai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_isidai_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_isidai_a1_v[8], 22, 8),
    gsSPNTrianglesInit_5b(14, 5, 8, 9, 0, 5, 10, 6, 11, 12),
    gsSPNTriangles_5b(7, 13, 14, 2, 15, 16, 3, 6, 17, 7, 4, 18),
    gsSPNTriangles_5b(5, 7, 19, 6, 2, 20, 1, 21, 22, 2, 1, 23),
    gsSPNTriangles_5b(0, 24, 25, 2, 26, 27, 5, 28, 29, 0, 0, 0),
    gsSPVertex(&act_mus_isidai_a1_v[30], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 1, 1, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 9, 10, 5, 7, 11, 12, 13),
    gsSPNTriangles_5b(4, 11, 1, 5, 9, 6, 14, 15, 8, 16, 15, 14),
    gsSPNTriangles_5b(13, 12, 17, 2, 1, 11, 11, 13, 2, 14, 8, 5),
    gsSPNTriangles_5b(14, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_isidai_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_isidai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_isidai_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_isidai_a1_v[48], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 3, 8, 9, 10, 11, 4, 9, 12, 3),
    gsSPNTriangles_5b(11, 5, 4, 5, 13, 6, 1, 14, 2, 3, 12, 0),
    gsSPNTriangles_5b(7, 15, 4, 1, 16, 14, 3, 2, 8, 13, 17, 6),
    gsSPNTriangles_5b(4, 15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_isidai_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 25, 65512, 1195 } },
    { act_mus_isidai_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_isidai_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_isidai_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_isidai_a1_tbl), 2,
                                                cKF_je_r_act_mus_isidai_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_isidai_a1_c(void) {
    pc_load_asset("assets/act_mus_isidai_a1/int_nog_isidai_pal.bin", int_nog_isidai_pal, 0x20, 0x95CF00, 0, 1);
}
#endif
