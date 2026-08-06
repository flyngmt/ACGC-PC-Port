#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_ghog_m_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_ghog_m_pal[] = {
#include "assets/obj_e_ghog_m_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_ghog_n_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_ghog_n_pal[] = {
#include "assets/obj_e_ghog_n_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_m1[0x40];
#else
u8 obj_e_ghog_m1[] = {
#include "assets/obj_e_ghog_m1.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_m2[0x40];
#else
u8 obj_e_ghog_m2[] = {
#include "assets/obj_e_ghog_m2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_m3[0x100];
#else
u8 obj_e_ghog_m3[] = {
#include "assets/obj_e_ghog_m3.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_m4[0x80];
#else
u8 obj_e_ghog_m4[] = {
#include "assets/obj_e_ghog_m4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_m5[0x80];
#else
u8 obj_e_ghog_m5[] = {
#include "assets/obj_e_ghog_m5.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_n2[0x80];
#else
u8 obj_e_ghog_n2[] = {
#include "assets/obj_e_ghog_n2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_ghog_n1[0x200];
#else
u8 obj_e_ghog_n1[] = {
#include "assets/obj_e_ghog_n1.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_ghog_v[0x450 / sizeof(Vtx)];
#else
Vtx obj_e_ghog_v[] = {
#include "assets/obj_e_ghog_v.inc"
};
#endif

Gfx obj_e_ghog_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_ghog_n_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_e_ghog_n1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_ghog_v[24], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 3, 0),
    gsSPNTriangles_5b(4, 0, 5, 6, 2, 1, 6, 1, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_ghog_n2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_ghog_m_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, obj_e_ghog_m4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_e_ghog_m3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_ghog_m2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_ghog_v[52], 17, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 1, 4, 5, 1, 6),
    gsSPNTriangles_5b(9, 11, 12, 9, 12, 8, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 7, 9, 10, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_ghog_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_ghog_m_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_ghog_m5),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_ghog_v, 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 6, 6, 0, 3, 6, 3, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_ghog_m1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(10, 12, 13, 14, 12, 14, 15, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 12, 18, 14, 13, 18, 13, 19, 20, 21, 13),
    gsSPNTriangles_5b(20, 13, 12, 15, 14, 22, 15, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
