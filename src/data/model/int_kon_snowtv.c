#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowtv_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_snowtv_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_snowtv_pal[] = {
#include "assets/int_kon_snowtv_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv07a_TA_tex_txt[0x80];
#else
u8 int_kon_snowtv07a_TA_tex_txt[] = {
#include "assets/int_kon_snowtv07a_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv07b_TA_tex_txt[0x80];
#else
u8 int_kon_snowtv07b_TA_tex_txt[] = {
#include "assets/int_kon_snowtv07b_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv07c_TA_tex_txt[0x80];
#else
u8 int_kon_snowtv07c_TA_tex_txt[] = {
#include "assets/int_kon_snowtv07c_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv07d_TA_tex_txt[0x80];
#else
u8 int_kon_snowtv07d_TA_tex_txt[] = {
#include "assets/int_kon_snowtv07d_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv03_tex_txt[0x100];
#else
u8 int_kon_snowtv03_tex_txt[] = {
#include "assets/int_kon_snowtv03_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv02_tex_txt[0x100];
#else
u8 int_kon_snowtv02_tex_txt[] = {
#include "assets/int_kon_snowtv02_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv01_tex_txt[0x200];
#else
u8 int_kon_snowtv01_tex_txt[] = {
#include "assets/int_kon_snowtv01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv04_tex_txt[0x80];
#else
u8 int_kon_snowtv04_tex_txt[] = {
#include "assets/int_kon_snowtv04_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv06_tex_txt[0x80];
#else
u8 int_kon_snowtv06_tex_txt[] = {
#include "assets/int_kon_snowtv06_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv05_tex_txt[0x80];
#else
u8 int_kon_snowtv05_tex_txt[] = {
#include "assets/int_kon_snowtv05_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowtv08_tex_txt[0x100];
#else
u8 int_kon_snowtv08_tex_txt[] = {
#include "assets/int_kon_snowtv08_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowtv_v[0x420 / sizeof(Vtx)];
#else
Vtx int_kon_snowtv_v[] = {
#include "assets/int_kon_snowtv_v.inc"
};
#endif

Gfx int_kon_snowtv_face_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtv_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowtv_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowtv_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtv_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowtv03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowtv_v[4], 23, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 8, 11, 12, 11, 13, 14, 12, 13),
    gsSPNTriangles_5b(14, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_snowtv02_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_snowtv01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtv04_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowtv_v[27], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(7, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtv06_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 9, 10, 11, 11, 10, 12, 12, 10, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 15, 14, 18, 15, 17, 19, 20, 21),
    gsSPNTriangles_5b(22, 20, 19, 23, 20, 22, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowtv05_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_snowtv_v[51], 15, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 4, 5, 6, 2),
    gsSPNTriangles_5b(7, 6, 5, 4, 3, 7, 2, 6, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_snowtv08_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 8, 9, 10, 8, 11, 12, 8, 13, 14),
    gsSPEndDisplayList(),
};
