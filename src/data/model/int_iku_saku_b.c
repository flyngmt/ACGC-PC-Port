#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_saku_b_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_saku_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_saku_b_pal[] = {
#include "assets/int_iku_saku_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_saku_b_b_tex_txt[0x80];
#else
u8 int_iku_saku_b_b_tex_txt[] = {
#include "assets/int_iku_saku_b_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_saku_b_a_tex_txt[0x200];
#else
u8 int_iku_saku_b_a_tex_txt[] = {
#include "assets/int_iku_saku_b_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_saku_b_c_tex_txt[0x80];
#else
u8 int_iku_saku_b_c_tex_txt[] = {
#include "assets/int_iku_saku_b_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_saku_b_v[0x2A0 / sizeof(Vtx)];
#else
Vtx int_iku_saku_b_v[] = {
#include "assets/int_iku_saku_b_v.inc"
};
#endif

Gfx int_iku_saku_b_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_saku_b_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_saku_b_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_saku_b_v, 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_saku_b_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_saku_b_v[6], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 9, 7, 6, 0, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 12, 15),
    gsSPNTriangles_5b(20, 15, 21, 22, 20, 21, 22, 21, 23, 17, 24, 25),
    gsSPNTriangles_5b(17, 25, 18, 24, 26, 27, 24, 27, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_saku_b_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_saku_b_v[34], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
