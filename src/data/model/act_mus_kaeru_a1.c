#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_kaeru_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 act_mus_kaeru_a1_body_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 act_mus_kaeru_a1_body_tex_txt[] = {
#include "assets/act_mus_kaeru_a1/act_mus_kaeru_a1_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_mus_kaeru_a1_foot_tex_txt[0x800];
#else
static u8 act_mus_kaeru_a1_foot_tex_txt[] = {
#include "assets/act_mus_kaeru_a1/act_mus_kaeru_a1_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_kaeru_a1_v[0x6D0 / sizeof(Vtx)];
#else
Vtx act_mus_kaeru_a1_v[] = {
#include "assets/act_mus_kaeru_a1_v.inc"
};
#endif

Gfx act_mus_kaeru_a1_anime_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_mus_kaeru_a1_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&act_mus_kaeru_a1_v[10], 20, 10),
    gsSPNTrianglesInit_5b(15, 4, 11, 10, 4, 13, 12, 5, 14, 15),
    gsSPNTriangles_5b(5, 16, 6, 2, 17, 5, 2, 0, 18, 0, 1, 19),
    gsSPNTriangles_5b(1, 21, 20, 8, 9, 22, 8, 24, 23, 7, 8, 25),
    gsSPNTriangles_5b(4, 7, 26, 3, 4, 27, 1, 3, 28, 9, 6, 29),
    gsSPVertex(&act_mus_kaeru_a1_v[30], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 3, 4, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kaeru_a1_foot2_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_kaeru_a1_v[35], 7, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_kaeru_a1_v[42], 4, 7),
    gsSPNTrianglesInit_5b(4, 5, 4, 7, 4, 6, 8, 2, 3, 9),
    gsSPNTriangles_5b(0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kaeru_a1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_kaeru_a1_v[46], 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 6, 3, 0, 5, 6, 7, 8, 6, 5, 7),
    gsSPNTriangles_5b(4, 9, 10, 4, 11, 2, 4, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(13, 12, 10, 13, 10, 14, 15, 13, 14, 10, 9, 14),
    gsSPNTriangles_5b(7, 16, 17, 8, 7, 17, 16, 18, 19, 17, 16, 19),
    gsSPNTriangles_5b(15, 14, 20, 20, 19, 18, 15, 20, 18, 21, 22, 23),
    gsSPNTriangles_5b(21, 24, 22, 22, 24, 25, 25, 24, 26, 26, 27, 25),
    gsSPNTriangles_5b(28, 25, 27, 22, 25, 28, 22, 28, 23, 28, 29, 23),
    gsSPNTriangles_5b(28, 27, 29, 27, 30, 29, 30, 31, 29, 0, 0, 0),
    gsSPVertex(&act_mus_kaeru_a1_v[78], 20, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 1, 0, 4, 3, 0),
    gsSPNTriangles_5b(4, 0, 5, 3, 6, 1, 7, 8, 9, 8, 5, 9),
    gsSPNTriangles_5b(10, 7, 11, 8, 4, 5, 12, 13, 14, 15, 12, 14),
    gsSPNTriangles_5b(15, 14, 8, 8, 7, 10, 15, 8, 10, 16, 15, 10),
    gsSPNTriangles_5b(13, 6, 3, 14, 13, 3, 14, 3, 4, 8, 14, 4),
    gsSPNTriangles_5b(17, 18, 19, 9, 19, 18, 9, 18, 7, 7, 18, 11),
    gsSPNTriangles_5b(11, 18, 17, 16, 10, 11, 16, 11, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kaeru_a1_foot1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_kaeru_a1_v[98], 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_kaeru_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 1610 } },
    { act_mus_kaeru_a1_foot1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_kaeru_a1_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 610, 0, 0 } },
    { act_mus_kaeru_a1_foot2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_kaeru_a1_anime_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 780, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_kaeru_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_kaeru_a1_tbl), 4,
                                               cKF_je_r_act_mus_kaeru_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_kaeru_a1_c(void) {
    pc_load_asset("assets/act_mus_kaeru_a1/act_mus_kaeru_a1_body_tex_txt.bin", act_mus_kaeru_a1_body_tex_txt, 0x800, 0x95EC40, 0, 0);
    pc_load_asset("assets/act_mus_kaeru_a1/act_mus_kaeru_a1_foot_tex_txt.bin", act_mus_kaeru_a1_foot_tex_txt, 0x800, 0x95F440, 0, 0);
}
#endif
