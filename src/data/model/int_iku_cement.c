#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_cement_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_cement_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_cement_pal[] = {
#include "assets/int_iku_cement_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_a_tex_txt[0x200];
#else
u8 int_iku_cement_a_tex_txt[] = {
#include "assets/int_iku_cement_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_d_tex_txt[0x100];
#else
u8 int_iku_cement_d_tex_txt[] = {
#include "assets/int_iku_cement_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_f_tex_txt[0x100];
#else
u8 int_iku_cement_f_tex_txt[] = {
#include "assets/int_iku_cement_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_c_tex_txt[0x100];
#else
u8 int_iku_cement_c_tex_txt[] = {
#include "assets/int_iku_cement_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_b_tex_txt[0x100];
#else
u8 int_iku_cement_b_tex_txt[] = {
#include "assets/int_iku_cement_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_e_tex_txt[0x100];
#else
u8 int_iku_cement_e_tex_txt[] = {
#include "assets/int_iku_cement_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cement_g_tex_txt[0x100];
#else
u8 int_iku_cement_g_tex_txt[] = {
#include "assets/int_iku_cement_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_cement_v[0x4F0 / sizeof(Vtx)];
#else
Vtx int_iku_cement_v[] = {
#include "assets/int_iku_cement_v.inc"
};
#endif

Gfx int_iku_cement_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_cement_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_cement_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_cement_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iku_cement_v[8], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 2, 4, 0, 2),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 16, 17, 13, 17, 14, 18, 8, 11),
    gsSPNTriangles_5b(18, 11, 19, 20, 15, 14, 20, 14, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_cement_v[34], 25, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 4, 2, 4, 0),
    gsSPNTriangles_5b(5, 1, 0, 3, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 6, 7, 8, 6, 8, 9, 9, 10, 6),
    gsSPNTriangles_5b(10, 11, 6, 9, 12, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 16, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 22, 23, 24, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_cement_v[59], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 5, 4, 2, 8, 7, 2, 11, 0),
    gsSPNTriangles_5b(6, 9, 3, 3, 5, 6, 1, 0, 10, 10, 4, 1),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cement_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 14, 15, 12, 16, 17, 18),
    gsSPNTriangles_5b(18, 19, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
