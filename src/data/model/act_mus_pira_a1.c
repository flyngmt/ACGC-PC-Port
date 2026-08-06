#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_pira_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_piraluku_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_piraluku_pal[] = {
#include "assets/act_mus_pira_a1/int_nog_piraluku_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_pireluku_body_txt[0x400];
#else
u8 act_mus_pireluku_body_txt[] = {
#include "assets/act_mus_pireluku_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_pira_a1_v[0x6E0 / sizeof(Vtx)];
#else
Vtx act_mus_pira_a1_v[] = {
#include "assets/act_mus_pira_a1_v.inc"
};
#endif

Gfx act_mus_pira_sakana_leg_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_pira_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_pireluku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_pira_a1_v[8], 18, 8),
    gsSPNTrianglesInit_5b(12, 6, 1, 8, 2, 7, 9, 0, 6, 10),
    gsSPNTriangles_5b(7, 5, 11, 3, 0, 12, 5, 4, 13, 5, 14, 15),
    gsSPNTriangles_5b(6, 16, 17, 7, 18, 19, 6, 20, 21, 7, 22, 23),
    gsSPNTriangles_5b(0, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_pira_a1_v[26], 22, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 6, 1, 0),
    gsSPNTriangles_5b(7, 8, 9, 1, 10, 2, 11, 12, 13, 14, 13, 15),
    gsSPNTriangles_5b(9, 13, 12, 10, 1, 3, 9, 16, 17, 18, 4, 3),
    gsSPNTriangles_5b(9, 8, 16, 11, 13, 14, 3, 1, 6, 3, 6, 19),
    gsSPNTriangles_5b(17, 15, 13, 17, 13, 9, 19, 18, 3, 5, 10, 3),
    gsSPNTriangles_5b(6, 0, 20, 21, 14, 15, 9, 12, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_pira_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_mus_pira_a1_v[48], 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_pireluku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_pira_a1_v[56], 18, 8),
    gsSPNTrianglesInit_5b(12, 2, 8, 9, 3, 10, 11, 6, 5, 12),
    gsSPNTriangles_5b(4, 13, 14, 3, 0, 15, 1, 16, 17, 1, 18, 5),
    gsSPNTriangles_5b(5, 19, 20, 0, 21, 22, 4, 23, 0, 4, 7, 24),
    gsSPNTriangles_5b(1, 2, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_pira_a1_v[74], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 2, 6, 0),
    gsSPNTriangles_5b(7, 4, 3, 0, 6, 8, 5, 9, 3, 8, 10, 0),
    gsSPNTriangles_5b(7, 11, 12, 7, 12, 13, 3, 11, 7, 10, 8, 14),
    gsSPNTriangles_5b(10, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_pira_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_pireluku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_pira_a1_v[90], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(3, 7, 8, 9, 10, 11, 10, 12, 2, 3, 13, 4),
    gsSPNTriangles_5b(14, 15, 2, 16, 8, 17, 2, 1, 14, 3, 16, 13),
    gsSPNTriangles_5b(15, 11, 2, 2, 11, 10, 3, 18, 7, 8, 16, 3),
    gsSPNTriangles_5b(2, 19, 0, 6, 18, 3, 12, 19, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_pira_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 37, 65525, 2797 } },
    { act_mus_pira_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_pira_sakana_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1897, 0, 0 } },
    { act_mus_pira_sakana_leg_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1800, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_pira_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_pira_a1_tbl), 3,
                                              cKF_je_r_act_mus_pira_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_pira_a1_c(void) {
    pc_load_asset("assets/act_mus_pira_a1/int_nog_piraluku_pal.bin", int_nog_piraluku_pal, 0x20, 0x966D20, 0, 1);
}
#endif
