#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_tent_mat_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_tent_mat_pal[] = {
#include "assets/obj_s_tent_mat_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_tent_main_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_tent_main_pal[] = {
#include "assets/obj_s_tent_main_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_tent_mat[0x100];
#else
u8 obj_s_tent_mat[] = {
#include "assets/obj_s_tent_mat.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_tent_wall1[0x400];
#else
u8 obj_s_tent_wall1[] = {
#include "assets/obj_s_tent_wall1.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_tent_wall2[0x800];
#else
u8 obj_s_tent_wall2[] = {
#include "assets/obj_s_tent_wall2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_tent_wall3[0x400];
#else
u8 obj_s_tent_wall3[] = {
#include "assets/obj_s_tent_wall3.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_tent_v[0x690 / sizeof(Vtx)];
#else
Vtx obj_s_tent_v[] = {
#include "assets/obj_s_tent_v.inc"
};
#endif

Gfx obj_s_tent_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_tent_mat_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_s_tent_mat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_tent_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_tent_main_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_tent_wall1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_tent_v[4], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(3, 5, 2, 3, 6, 5, 5, 7, 2, 8, 9, 10),
    gsSPNTriangles_5b(11, 8, 10, 9, 12, 10, 8, 13, 9, 9, 14, 12),
    gsSPNTriangles_5b(12, 15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPDisplayList(anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tent_wall2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_tent_v[20], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tent_wall2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_tent_v[25], 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 2, 4, 0, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_tent_wall3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_s_tent_v[34], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 8, 11),
    gsSPNTriangles_5b(12, 11, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 19, 26, 27),
    gsSPNTriangles_5b(19, 27, 20, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_s_tent_v[66], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 9, 12, 13),
    gsSPNTriangles_5b(9, 13, 10, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 24, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_s_tent_v[98], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPEndDisplayList(),
};
