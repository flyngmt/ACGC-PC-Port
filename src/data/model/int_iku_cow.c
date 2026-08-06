#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_cow_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_cow_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_cow_pal[] = {
#include "assets/int_iku_cow_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cow_5_tex_txt[0x100];
#else
u8 int_iku_cow_5_tex_txt[] = {
#include "assets/int_iku_cow_5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cow1_tex_txt[0x400];
#else
u8 int_iku_cow1_tex_txt[] = {
#include "assets/int_iku_cow1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cow_4_tex_txt[0x100];
#else
u8 int_iku_cow_4_tex_txt[] = {
#include "assets/int_iku_cow_4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cow_3_tex_txt[0x100];
#else
u8 int_iku_cow_3_tex_txt[] = {
#include "assets/int_iku_cow_3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_cow_2_tex_txt[0x100];
#else
u8 int_iku_cow_2_tex_txt[] = {
#include "assets/int_iku_cow_2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_cow_v[0x360 / sizeof(Vtx)];
#else
Vtx int_iku_cow_v[] = {
#include "assets/int_iku_cow_v.inc"
};
#endif

Gfx int_iku_cow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_cow_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cow_5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_cow_v, 18, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 1, 5, 0, 6),
    gsSPNTriangles_5b(2, 7, 8, 1, 0, 3, 2, 6, 0, 5, 6, 8),
    gsSPNTriangles_5b(3, 0, 5, 8, 6, 2, 9, 10, 11, 12, 9, 13),
    gsSPNTriangles_5b(11, 10, 14, 13, 9, 11, 10, 9, 12, 14, 10, 15),
    gsSPNTriangles_5b(13, 16, 12, 15, 17, 14, 12, 15, 10, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_iku_cow1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_cow_v[18], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 4, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 9, 10, 7, 5, 0, 2, 7, 10, 3),
    gsSPNTriangles_5b(9, 11, 10, 12, 3, 10, 2, 13, 5, 3, 0, 5),
    gsSPNTriangles_5b(6, 7, 3, 13, 2, 14, 15, 9, 8, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_cow_4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 19, 20, 21, 18, 22, 23),
    gsSPNTriangles_5b(23, 21, 16, 22, 24, 19, 18, 23, 16, 19, 23, 22),
    gsSPNTriangles_5b(21, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_cow_3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 27, 28, 29, 27, 29, 25),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_cow_2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_cow_v[48], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
