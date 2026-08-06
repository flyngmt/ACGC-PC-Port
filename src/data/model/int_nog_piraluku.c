#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_piraluku_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_piraluku_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_piraluku_pal[] = {
#include "assets/int_nog_piraluku/int_nog_piraluku_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_piraluku_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_piraluku_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_piraluku_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pireluku_body_tex_txt[0x400];
#else
u8 int_nog_pireluku_body_tex_txt[] = {
#include "assets/int_nog_pireluku_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pireluku_side_tex_txt[0x200];
#else
u8 int_nog_pireluku_side_tex_txt[] = {
#include "assets/int_nog_pireluku_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pireluku_base_tex_txt[0x80];
#else
u8 int_nog_pireluku_base_tex_txt[] = {
#include "assets/int_nog_pireluku_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pireluku_top_tex_txt[0x80];
#else
u8 int_nog_pireluku_top_tex_txt[] = {
#include "assets/int_nog_pireluku_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_pireluku_glass_tex_txt[0x100];
#else
u8 int_nog_pireluku_glass_tex_txt[] = {
#include "assets/int_nog_pireluku_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_piraluku_v[0x3F0 / sizeof(Vtx)];
#else
Vtx int_nog_piraluku_v[] = {
#include "assets/int_nog_piraluku_v.inc"
};
#endif

Gfx int_nog_piraluku_sakana_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_pireluku_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_piraluku_v, 28, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 5, 6, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 7, 8, 9, 8, 10, 9, 10, 11, 9),
    gsSPNTriangles_5b(11, 12, 9, 9, 12, 13, 14, 15, 16, 16, 15, 17),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 16, 19, 20, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 25, 26, 27, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_piraluku_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 100, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_pireluku_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_piraluku_v[49], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_piraluku_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_pireluku_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_piraluku_v[53], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_piraluku_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_pireluku_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_piraluku_v[28], 21, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_pireluku_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 19, 20, 18),
    gsSPNTriangles_5b(20, 16, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_piraluku_tbl[] = { 56, 7, 0, 0, 7 };

s16 cKF_kn_int_nog_piraluku_tbl[] = { 2, 2, 2, 2, 2, 2, 3, 4, 4 };

s16 cKF_c_int_nog_piraluku_tbl[] = { 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_piraluku_tbl[] = { 1,   2000, 0,  129, 2000, 0,   1,  -5000, 0, 129, -5000, 0,  1,   0,
                                      0,   129,  0,  0,   1,    0,   0,  129,   0, 0,   1,     0,  0,   129,
                                      0,   0,    1,  0,   0,    129, 0,  0,     1, 200, 0,     81, 200, 0,
                                      129, 200,  0,  1,   -5,   0,   81, 5,     2, 101, 0,     -6, 129, -5,
                                      0,   1,    10, 0,   81,   -10, -3, 101,   0, 21,  129,   10, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_piraluku = { cKF_ckcb_r_int_nog_piraluku_tbl,
                                                cKF_ds_int_nog_piraluku_tbl,
                                                cKF_kn_int_nog_piraluku_tbl,
                                                cKF_c_int_nog_piraluku_tbl,
                                                -1,
                                                129 };

cKF_Joint_R_c cKF_je_r_int_nog_piraluku_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 60536, 0 } },
    { int_sum_piraluku_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_piraluku_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_piraluku_top_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_piraluku_sakana_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_piraluku = { ARRAY_COUNT(cKF_je_r_int_nog_piraluku_tbl), 4,
                                               cKF_je_r_int_nog_piraluku_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_nog_piraluku_c(void) {
    pc_load_asset("assets/int_nog_piraluku/int_nog_piraluku_pal.bin", int_nog_piraluku_pal, 0x20, 0xBEC3A0, 0, 1);
}
#endif
