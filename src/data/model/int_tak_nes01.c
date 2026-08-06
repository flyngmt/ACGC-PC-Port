#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_nes01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_nes01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_nes01_pal[] = {
#include "assets/int_tak_nes01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_cl_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_cl_pal[] = {
#include "assets/int_tak_nes_cl_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_af_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_af_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_af_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_bb_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_bb_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_bb_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_bf_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_bf_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_bf_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_d2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_d2_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_d2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_d3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_d3_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_d3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_dk_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_dk_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_dk_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_eb_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_eb_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_eb_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_g_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_g_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_g_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_ic_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_ic_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_ic_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_mb_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_mb_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_mb_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_pb_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_pb_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_pb_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_po_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_po_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_po_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_sa_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_sa_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_sa_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_sm_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_sm_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_sm_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_so_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_so_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_so_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_t_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_t_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_t_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_wm_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_wm_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_wm_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_nes_zl_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_nes_zl_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_nes_zl_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes01_top_tex[0x200];
#else
u8 int_tak_nes01_top_tex[] = {
#include "assets/int_tak_nes01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes01_side_tex[0x400];
#else
u8 int_tak_nes01_side_tex[] = {
#include "assets/int_tak_nes01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes01_con_tex[0x40];
#else
u8 int_tak_nes01_con_tex[] = {
#include "assets/int_tak_nes01_con_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes01_code_tex[0x80];
#else
u8 int_tak_nes01_code_tex[] = {
#include "assets/int_tak_nes01_code_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_cl_tex[0x200];
#else
u8 int_tak_nes_cl_tex[] = {
#include "assets/int_tak_nes_cl_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_af_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_af_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_af_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_bb_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_bb_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_bb_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_bf_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_bf_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_bf_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_d2_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_d2_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_d2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_d3_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_d3_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_d3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_dk_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_dk_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_dk_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_eb_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_eb_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_eb_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_g_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_g_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_g_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_ic_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_ic_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_ic_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_mb_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_mb_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_mb_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_pb_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_pb_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_pb_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_po_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_po_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_po_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_sa_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_sa_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_sa_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_sm_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_sm_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_sm_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_so_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_so_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_so_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_t_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_t_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_t_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_wm_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_wm_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_wm_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_zl_tex_rgb_ci4[0x200];
#else
u8 int_tak_nes_zl_tex_rgb_ci4[] = {
#include "assets/int_tak_nes_zl_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nes_ds_tex_rgb_i4[0x200];
#else
u8 int_tak_nes_ds_tex_rgb_i4[] = {
#include "assets/int_tak_nes_ds_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_nes01_v[0x640 / sizeof(Vtx)];
#else
Vtx int_tak_nes01_v[] = {
#include "assets/int_tak_nes01_v.inc"
};
#endif

Gfx int_tak_nes01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_nes01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_tak_nes01_con_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_nes01_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_nes01_v[32], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 16, int_tak_nes01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_nes01_v[40], 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 1, 20, 21),
    gsSPNTriangles_5b(1, 21, 2, 22, 23, 24, 22, 24, 25, 26, 16, 19),
    gsSPNTriangles_5b(26, 19, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_nes01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_nes01_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_nes01_game_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_nes01_v[72], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_nes01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_nes01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_nes01_code_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_nes01_v[92], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
