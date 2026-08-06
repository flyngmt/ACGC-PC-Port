#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_doll11_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_doll11_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_doll11_pal[] = {
#include "assets/int_sum_doll11_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll11_face_tex_txt[0x400];
#else
u8 int_sum_doll11_face_tex_txt[] = {
#include "assets/int_sum_doll11_face_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_doll11_front_tex_txt[0x300];
#else
u8 int_sum_doll11_front_tex_txt[] = {
#include "assets/int_sum_doll11_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_doll11_v[0x210 / sizeof(Vtx)];
#else
Vtx int_sum_doll11_v[] = {
#include "assets/int_sum_doll11_v.inc"
};
#endif

Gfx int_sum_doll11_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_doll11_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_doll11_face_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_doll11_v, 23, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(3, 0, 9, 8, 10, 6, 11, 12, 13, 14, 15, 11),
    gsSPNTriangles_5b(12, 11, 16, 17, 6, 10, 5, 18, 19, 17, 20, 21),
    gsSPNTriangles_5b(0, 5, 19, 17, 21, 6, 16, 7, 12, 4, 3, 15),
    gsSPNTriangles_5b(16, 15, 3, 3, 9, 16, 15, 14, 4, 13, 14, 11),
    gsSPNTriangles_5b(1, 0, 19, 2, 9, 0, 22, 18, 5, 4, 14, 22),
    gsSPNTriangles_5b(22, 14, 13, 11, 15, 16, 22, 13, 21, 21, 13, 12),
    gsSPNTriangles_5b(7, 6, 12, 5, 0, 3, 12, 6, 21, 5, 4, 22),
    gsSPNTriangles_5b(21, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_doll11_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPVertex(&int_sum_doll11_v[23], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 5, 4, 6),
    gsSPNTriangles_5b(6, 1, 0, 2, 7, 0, 5, 8, 3, 6, 9, 5),
    gsSPNTriangles_5b(0, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
