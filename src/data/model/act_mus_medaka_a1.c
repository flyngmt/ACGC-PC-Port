#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_medaka_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_medaka_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_medaka_pal[] = {
#include "assets/act_mus_medaka_a1/int_nog_medaka_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_medaka_body_txt[0x100];
#else
u8 act_mus_medaka_body_txt[] = {
#include "assets/act_mus_medaka_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_medaka_a1_v[0x300 / sizeof(Vtx)];
#else
Vtx act_mus_medaka_a1_v[] = {
#include "assets/act_mus_medaka_a1_v.inc"
};
#endif

Gfx act_mus_medaka_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_medaka_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_medaka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_medaka_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_medaka_a1_v[6], 12, 6),
    gsSPNTrianglesInit_5b(8, 0, 6, 2, 5, 7, 1, 5, 9, 8),
    gsSPNTriangles_5b(2, 11, 10, 3, 2, 12, 2, 14, 13, 5, 4, 15),
    gsSPNTriangles_5b(4, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_medaka_a1_v[18], 18, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 6, 10, 0, 4, 1, 11, 3, 0),
    gsSPNTriangles_5b(10, 12, 13, 13, 9, 10, 12, 10, 14, 0, 5, 11),
    gsSPNTriangles_5b(10, 6, 8, 5, 15, 11, 15, 16, 11, 11, 16, 3),
    gsSPNTriangles_5b(8, 7, 17, 8, 14, 10, 8, 17, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_medaka_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_medaka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_medaka_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_medaka_a1_v[36], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(7, 6, 3, 2, 8, 9, 9, 10, 2, 1, 8, 2),
    gsSPNTriangles_5b(2, 10, 0, 3, 11, 7, 5, 11, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_medaka_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 58, 65499, 605 } },
    { act_mus_medaka_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_medaka_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 605, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_medaka_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_medaka_a1_tbl), 2,
                                                cKF_je_r_act_mus_medaka_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_medaka_a1_c(void) {
    pc_load_asset("assets/act_mus_medaka_a1/int_nog_medaka_pal.bin", int_nog_medaka_pal, 0x20, 0x962CE0, 0, 1);
}
#endif
