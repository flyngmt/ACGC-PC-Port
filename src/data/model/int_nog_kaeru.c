#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_kaeru_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_kaeru_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_kaeru_pal[] = {
#include "assets/int_nog_kaeru/int_nog_kaeru_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_kaeru_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_kaeru_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_kaeru_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_mus_kaeru_a1_body_tex_txt[0x800];
#else
static u8 act_mus_kaeru_a1_body_tex_txt[] = {
#include "assets/int_nog_kaeru/act_mus_kaeru_a1_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_mus_kaeru_a1_foot_tex_txt[0x800];
#else
static u8 act_mus_kaeru_a1_foot_tex_txt[] = {
#include "assets/int_nog_kaeru/act_mus_kaeru_a1_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kaeru_top_tex_txt[0x100];
#else
u8 int_nog_kaeru_top_tex_txt[] = {
#include "assets/int_nog_kaeru_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kaeru_side_tex_txt[0x200];
#else
u8 int_nog_kaeru_side_tex_txt[] = {
#include "assets/int_nog_kaeru_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kaeru_base_tex_txt[0x80];
#else
u8 int_nog_kaeru_base_tex_txt[] = {
#include "assets/int_nog_kaeru_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kaeru_etc_tex_txt[0x80];
#else
u8 int_nog_kaeru_etc_tex_txt[] = {
#include "assets/int_nog_kaeru_etc_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kaeru_glass_tex_txt[0x100];
#else
u8 int_nog_kaeru_glass_tex_txt[] = {
#include "assets/int_nog_kaeru_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_kaeru_v[0x940 / sizeof(Vtx)];
#else
Vtx int_nog_kaeru_v[] = {
#include "assets/int_nog_kaeru_v.inc"
};
#endif

Gfx int_sum_kaeru_hara_model[] = {
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_kaeru_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[6], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_nog_kaeru_v[10], 20, 10),
    gsSPNTrianglesInit_5b(15, 1, 11, 10, 1, 13, 12, 6, 14, 15),
    gsSPNTriangles_5b(6, 16, 5, 7, 17, 6, 7, 8, 18, 8, 9, 19),
    gsSPNTriangles_5b(9, 21, 20, 3, 4, 22, 3, 24, 23, 2, 3, 25),
    gsSPNTriangles_5b(1, 2, 26, 0, 1, 27, 9, 0, 28, 4, 5, 29),
    gsSPVertex(&int_nog_kaeru_v[30], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 3, 4, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_foot_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[35], 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[46], 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 6, 3, 0, 5, 6, 7, 8, 6, 5, 7),
    gsSPNTriangles_5b(4, 9, 10, 4, 11, 2, 4, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(13, 12, 10, 13, 10, 14, 15, 13, 14, 10, 9, 14),
    gsSPNTriangles_5b(7, 16, 17, 8, 7, 17, 16, 18, 19, 17, 16, 19),
    gsSPNTriangles_5b(15, 14, 20, 20, 19, 18, 15, 20, 18, 21, 22, 23),
    gsSPNTriangles_5b(21, 24, 22, 22, 24, 25, 25, 24, 26, 26, 27, 25),
    gsSPNTriangles_5b(28, 25, 27, 22, 25, 28, 22, 28, 23, 28, 29, 23),
    gsSPNTriangles_5b(28, 27, 29, 27, 30, 29, 30, 31, 29, 0, 0, 0),
    gsSPVertex(&int_nog_kaeru_v[78], 20, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 1, 0, 4, 3, 0),
    gsSPNTriangles_5b(4, 0, 5, 3, 6, 1, 7, 8, 9, 8, 5, 9),
    gsSPNTriangles_5b(10, 7, 11, 8, 4, 5, 12, 13, 14, 15, 12, 14),
    gsSPNTriangles_5b(15, 14, 8, 8, 7, 10, 15, 8, 10, 16, 15, 10),
    gsSPNTriangles_5b(13, 6, 3, 14, 13, 3, 14, 3, 4, 8, 14, 4),
    gsSPNTriangles_5b(17, 18, 19, 9, 19, 18, 9, 18, 7, 7, 18, 11),
    gsSPNTriangles_5b(11, 18, 17, 16, 10, 11, 16, 11, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 100, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kaeru_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[109], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_leg_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, act_mus_kaeru_a1_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[98], 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kaeru_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[113], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kaeru_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_kaeru_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kaeru_v[123], 25, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_kaeru_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 12, 13, 14, 12),
    gsSPNTriangles_5b(14, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_kaeru_etc_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 15, 16, 17, 15, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_kaeru_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 1 };

s16 cKF_kn_int_nog_kaeru_tbl[] = { 4 };

s16 cKF_c_int_nog_kaeru_tbl[] = { -1138, 498, 1138, 0, -450, 0, 900, 900, 900, 0, 0, 0, 0,
                                  0,     0,   0,    0, 0,    0, 0,   0,   0,   0, 0, 0, 0 };

s16 cKF_ds_int_nog_kaeru_tbl[] = { 1, -50, -24, 28, -61, 36, 41, -49, 6, 65, -50, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_kaeru = {
    cKF_ckcb_r_int_nog_kaeru_tbl, cKF_ds_int_nog_kaeru_tbl, cKF_kn_int_nog_kaeru_tbl, cKF_c_int_nog_kaeru_tbl, -1, 65
};

cKF_Joint_R_c cKF_je_r_int_nog_kaeru_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64398, 498, 1138 } },
    { int_sum_kaeru_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kaeru_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kaeru_leg_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kaeru_top_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kaeru_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 610, 0, 0 } },
    { int_sum_kaeru_foot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kaeru_hara_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 780, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_kaeru = { ARRAY_COUNT(cKF_je_r_int_nog_kaeru_tbl), 7, cKF_je_r_int_nog_kaeru_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_nog_kaeru_c(void) {
    pc_load_asset("assets/int_nog_kaeru/int_nog_kaeru_pal.bin", int_nog_kaeru_pal, 0x20, 0xBDA520, 0, 1);
    pc_load_asset("assets/int_nog_kaeru/act_mus_kaeru_a1_body_tex_txt.bin", act_mus_kaeru_a1_body_tex_txt, 0x800, 0xBDA560, 0, 0);
    pc_load_asset("assets/int_nog_kaeru/act_mus_kaeru_a1_foot_tex_txt.bin", act_mus_kaeru_a1_foot_tex_txt, 0x800, 0xBDAD60, 0, 0);
}
#endif
