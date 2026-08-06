#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_dojyo_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_dojyo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_dojyo_pal[] = {
#include "assets/act_mus_dojyo_a1/int_sum_dojyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_dojyo_body_txt[0x100];
#else
u8 act_mus_dojyo_body_txt[] = {
#include "assets/act_mus_dojyo_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_dojyo_a1_v[0x3B0 / sizeof(Vtx)];
#else
Vtx act_mus_dojyo_a1_v[] = {
#include "assets/act_mus_dojyo_a1_v.inc"
};
#endif

Gfx act_mus_dojyo_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_dojyo_a1_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_dojyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_dojyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_dojyo_a1_v[4], 12, 4),
    gsSPNTrianglesInit_5b(8, 0, 4, 1, 3, 5, 0, 2, 1, 6),
    gsSPNTriangles_5b(3, 2, 7, 3, 9, 8, 1, 11, 10, 3, 13, 12),
    gsSPNTriangles_5b(1, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_dojyo_a1_v[16], 22, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 0, 12, 1, 13, 3, 0),
    gsSPNTriangles_5b(13, 0, 5, 11, 2, 14, 14, 15, 11, 2, 11, 6),
    gsSPNTriangles_5b(16, 17, 5, 6, 8, 16, 17, 13, 5, 17, 18, 19),
    gsSPNTriangles_5b(4, 12, 0, 11, 15, 9, 20, 16, 8, 19, 13, 17),
    gsSPNTriangles_5b(6, 11, 10, 6, 10, 7, 17, 16, 18, 21, 20, 8),
    gsSPNTriangles_5b(8, 7, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_dojyo_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_dojyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_mus_dojyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_dojyo_a1_v[38], 21, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 0, 6, 5),
    gsSPNTriangles_5b(7, 3, 5, 5, 1, 0, 2, 3, 7, 2, 6, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 8, 9, 10, 11, 12, 13, 10, 9, 13),
    gsSPNTriangles_5b(13, 14, 11, 11, 14, 8, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 15, 16, 17, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 18, 19, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_dojyo_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_dojyo_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_dojyo_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_dojyo_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_dojyo_a1_tbl), 2,
                                               cKF_je_r_act_mus_dojyo_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_dojyo_a1_c(void) {
    pc_load_asset("assets/act_mus_dojyo_a1/int_sum_dojyo_pal.bin", int_sum_dojyo_pal, 0x20, 0x95A0A0, 0, 1);
}
#endif
