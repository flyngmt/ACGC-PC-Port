#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_doll04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_doll04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_doll04_pal[] = {
#include "assets/int_sum_doll04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_top_txt_txt[0x100];
#else
u8 int_sum_doll04_top_txt_txt[] = {
#include "assets/int_sum_doll04_top_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_face_txt_txt[0x200];
#else
u8 int_sum_doll04_face_txt_txt[] = {
#include "assets/int_sum_doll04_face_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_back_txt_txt[0x100];
#else
u8 int_sum_doll04_back_txt_txt[] = {
#include "assets/int_sum_doll04_back_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_ear_txt_txt[0x80];
#else
u8 int_sum_doll04_ear_txt_txt[] = {
#include "assets/int_sum_doll04_ear_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_hand_txt_txt[0x100];
#else
u8 int_sum_doll04_hand_txt_txt[] = {
#include "assets/int_sum_doll04_hand_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_footdown_txt_txt[0x80];
#else
u8 int_sum_doll04_footdown_txt_txt[] = {
#include "assets/int_sum_doll04_footdown_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll04_foot_txt_txt[0x100];
#else
u8 int_sum_doll04_foot_txt_txt[] = {
#include "assets/int_sum_doll04_foot_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_doll04_v[0x4A0 / sizeof(Vtx)];
#else
Vtx int_sum_doll04_v[] = {
#include "assets/int_sum_doll04_v.inc"
};
#endif

Gfx int_sum_doll04_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_doll04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll04_top_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_doll04_v, 30, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 0, 4, 1, 3, 5),
    gsSPNTriangles_5b(1, 0, 3, 6, 0, 2, 6, 4, 0, 7, 4, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_doll04_face_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 11, 12, 13, 14, 11, 15),
    gsSPNTriangles_5b(14, 16, 11, 9, 13, 10, 9, 17, 13, 12, 10, 13),
    gsSPNTriangles_5b(18, 19, 20, 18, 10, 12, 8, 10, 18, 20, 21, 18),
    gsSPNTriangles_5b(14, 15, 22, 21, 8, 18, 13, 17, 23, 13, 15, 11),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll04_back_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 27, 25, 24, 28, 26, 25),
    gsSPNTriangles_5b(29, 28, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_doll04_ear_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_doll04_v[30], 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll04_hand_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 7, 6, 9, 10, 11, 12),
    gsSPNTriangles_5b(13, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_doll04_footdown_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll04_foot_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_doll04_v[56], 18, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 4, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_doll04_hand_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
