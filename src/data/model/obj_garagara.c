#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_gara_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_gara_pal[] = {
#include "assets/obj_gara_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_gara_tex_txt[0x800];
#else
u8 obj_gara_tex_txt[] = {
#include "assets/obj_gara_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_gara_v[0x420 / sizeof(Vtx)];
#else
Vtx obj_gara_v[] = {
#include "assets/obj_gara_v.inc"
};
#endif

Gfx obj_gara_base_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_gara_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_gara_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_gara_v[42], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 4, 0),
    gsSP2Triangles(4, 9, 7, 0, 6, 9, 4, 0),
    gsSPVertex(&obj_gara_v[52], 4, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPVertex(&obj_gara_v[56], 6, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(3, 4, 2, 0, 2, 5, 0, 0),
    gsSPVertex(&obj_gara_v[62], 4, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx obj_gara_hex_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_gara_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_gara_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(obj_gara_v, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 1, 5, 3, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 22, 24, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
    gsSPVertex(&obj_gara_v[30], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPVertex(&obj_gara_v[34], 8, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_gara_tbl[] = { 0, 0, 1 };

s16 cKF_kn_obj_gara_tbl[] = { 10 };

s16 cKF_c_obj_gara_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_gara_tbl[] = { 1,  0,     -2019, 2,  -67,   -2141, 17, -1674, -3504, 21, -2136, -3460, 26, -2700, -3221,
                              31, -3157, -2242, 40, -3581, -637,  43, -3616, -58,   47, -3602, 97,    48, -3600, 58 };

cKF_Animation_R_c cKF_ba_r_obj_gara = {
    cKF_ckcb_r_obj_gara_tbl, cKF_ds_obj_gara_tbl, cKF_kn_obj_gara_tbl, cKF_c_obj_gara_tbl, -1, 48
};

#ifdef TARGET_PC
u16 act_fukuball_pal[0x20 / sizeof(u16)];
#else
u16 act_fukuball_pal[] = {
#include "assets/act_fukuball_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_fukutama1_tex[0x80];
#else
u8 act_fukutama1_tex[] = {
#include "assets/act_fukutama1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 act_fukutama2_tex[0x80];
#else
u8 act_fukutama2_tex[] = {
#include "assets/act_fukutama2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 act_fukutama3_tex[0x80];
#else
u8 act_fukutama3_tex[] = {
#include "assets/act_fukutama3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 act_fukutama4_tex[0x80];
#else
u8 act_fukutama4_tex[] = {
#include "assets/act_fukutama4_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_fukutama_v[0x50 / sizeof(Vtx)];
#else
Vtx act_fukutama_v[] = {
#include "assets/act_fukutama_v.inc"
};
#endif

Gfx act_fukutama_modelT[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_fukuball_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, anime_1_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_fukutama_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(3, 4, 1, 0, 4, 2, 1, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_gara_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_gara_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_gara_hex_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1400, 0, 0 } },
};

cKF_Skeleton_R_c cKF_bs_r_obj_gara = { ARRAY_COUNT(cKF_je_r_obj_gara_tbl), 2, cKF_je_r_obj_gara_tbl };
