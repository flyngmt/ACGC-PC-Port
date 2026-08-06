#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_museum5_kusa3_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_museum5_kusa1_tex_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_museum5_kusa1_tex_txt[] = {
#include "assets/obj_museum5_kusa3/obj_museum5_kusa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_museum5_kusa3_v[0x240 / sizeof(Vtx)];
#else
Vtx obj_museum5_kusa3_v[] = {
#include "assets/obj_museum5_kusa3_v.inc"
};
#endif

Gfx obj_museum5_kusa3_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, obj_museum5_kusa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_kusa3_v[28], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_museum5_kusa3_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, obj_museum5_kusa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_kusa3_v[10], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, obj_museum5_kusa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_museum5_kusa3_v[14], 14, 4),
    gsSPNTrianglesInit_5b(4, 0, 1, 4, 1, 6, 5, 2, 3, 7),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_museum5_kusa3_3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, obj_museum5_kusa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_museum5_kusa3_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, obj_museum5_kusa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_museum5_kusa3_v[4], 6, 4),
    gsSPNTrianglesInit_5b(4, 0, 1, 4, 1, 6, 5, 2, 3, 7),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_museum5_kusa3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 5000, 0 } },
    { obj_museum5_kusa3_1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_museum5_kusa3_2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { obj_museum5_kusa3_3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_museum5_kusa3 = { ARRAY_COUNT(cKF_je_r_obj_museum5_kusa3_tbl), 3,
                                                cKF_je_r_obj_museum5_kusa3_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_museum5_kusa3_c(void) {
    pc_load_asset("assets/obj_museum5_kusa3/obj_museum5_kusa1_tex_txt.bin", obj_museum5_kusa1_tex_txt, 0x400, 0x9733C0, 0, 0);
}
#endif
