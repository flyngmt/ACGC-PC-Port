#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowtansu_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_kon_snowtansu_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_kon_snowtansu_tex_pal[] = {
#include "assets/int_kon_snowtansu/int_kon_snowtansu_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu04_tex_txt[0x80];
#else
u8 int_kon_snowtansu04_tex_txt[] = {
#include "assets/int_kon_snowtansu04_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu06_tex_txt[0x80];
#else
u8 int_kon_snowtansu06_tex_txt[] = {
#include "assets/int_kon_snowtansu06_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu05_tex_txt[0x80];
#else
u8 int_kon_snowtansu05_tex_txt[] = {
#include "assets/int_kon_snowtansu05_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu01_tex_txt[0x180];
#else
u8 int_kon_snowtansu01_tex_txt[] = {
#include "assets/int_kon_snowtansu01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu02_tex_txt[0x180];
#else
u8 int_kon_snowtansu02_tex_txt[] = {
#include "assets/int_kon_snowtansu02_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu07_tex_txt[0x100];
#else
u8 int_kon_snowtansu07_tex_txt[] = {
#include "assets/int_kon_snowtansu07_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtansu03_tex_txt[0x80];
#else
u8 int_kon_snowtansu03_tex_txt[] = {
#include "assets/int_kon_snowtansu03_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowtansu_v[0x400 / sizeof(Vtx)];
#else
Vtx int_kon_snowtansu_v[] = {
#include "assets/int_kon_snowtansu_v.inc"
};
#endif

Gfx int_kon_snowtansu_hiki_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtansu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtansu04_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowtansu_v, 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtansu06_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 5, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtansu05_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowtansu_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtansu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_snowtansu01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowtansu_v[15], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_snowtansu02_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowtansu07_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 10, 11, 9, 12, 13),
    gsSPNTriangles_5b(9, 13, 10, 12, 14, 15, 12, 15, 13, 14, 16, 17),
    gsSPNTriangles_5b(14, 17, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 18, 19, 20, 18, 20, 21, 19, 22, 23),
    gsSPNTriangles_5b(19, 23, 20, 24, 25, 26, 24, 26, 27, 28, 24, 27),
    gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_kon_snowtansu_v[45], 19, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtansu03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 14, 13, 15, 16),
    gsSPNTriangles_5b(15, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_snowtansu_tbl[] = { 56, 7, 7 };

s16 cKF_kn_int_kon_snowtansu_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_kon_snowtansu_tbl[] = { 0, 900, 0 };

s16 cKF_ds_int_kon_snowtansu_tbl[] = { 1, 2000, 0, 10, 2000, 0, 1, -24000, 0, 10, -24000, 0, 1, 1250, 0, 10, 1250, 0,
                                       1, 0,    0, 10, 0,    0, 1, 0,      0, 10, 0,      0, 1, 900,  0, 10, 900,  0,
                                       1, 0,    0, 10, 0,    0, 1, 0,      0, 10, 0,      0, 1, 0,    0, 10, 28,   83 };

cKF_Animation_R_c cKF_ba_r_int_kon_snowtansu = { cKF_ckcb_r_int_kon_snowtansu_tbl,
                                                 cKF_ds_int_kon_snowtansu_tbl,
                                                 cKF_kn_int_kon_snowtansu_tbl,
                                                 cKF_c_int_kon_snowtansu_tbl,
                                                 -1,
                                                 10 };

cKF_Joint_R_c cKF_je_r_int_kon_snowtansu_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 41536, 1250 } },
    { int_kon_snowtansu_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_snowtansu_hiki_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_snowtansu = { ARRAY_COUNT(cKF_je_r_int_kon_snowtansu_tbl), 2,
                                                cKF_je_r_int_kon_snowtansu_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_kon_snowtansu_c(void) {
    pc_load_asset("assets/int_kon_snowtansu/int_kon_snowtansu_tex_pal.bin", int_kon_snowtansu_tex_pal, 0x20, 0xB91220, 0, 1);
}
#endif
