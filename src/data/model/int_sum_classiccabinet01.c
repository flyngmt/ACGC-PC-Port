#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_classiccabinet01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_classiccabinet01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_classiccabinet01_pal[] = {
#include "assets/int_sum_classiccabinet01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_front[0x400];
#else
u8 int_sum_classiccabinet01_front[] = {
#include "assets/int_sum_classiccabinet01_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_in[0x80];
#else
u8 int_sum_classiccabinet01_in[] = {
#include "assets/int_sum_classiccabinet01_in.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_rack[0x80];
#else
u8 int_sum_classiccabinet01_rack[] = {
#include "assets/int_sum_classiccabinet01_rack.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_back[0x200];
#else
u8 int_sum_classiccabinet01_back[] = {
#include "assets/int_sum_classiccabinet01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_saucer[0x80];
#else
u8 int_sum_classiccabinet01_saucer[] = {
#include "assets/int_sum_classiccabinet01_saucer.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classiccabinet01_saucer2[0x80];
#else
u8 int_sum_classiccabinet01_saucer2[] = {
#include "assets/int_sum_classiccabinet01_saucer2.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_classiccabinet01_v[0x480 / sizeof(Vtx)];
#else
Vtx int_sum_classiccabinet01_v[] = {
#include "assets/int_sum_classiccabinet01_v.inc"
};
#endif

Gfx int_sum_classiccabinet01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classiccabinet01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classiccabinet01_rack),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_classiccabinet01_v, 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 17, 19, 18, 19, 17, 20),
    gsSPNTriangles_5b(17, 21, 20, 22, 20, 21, 22, 23, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classiccabinet01_in),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classiccabinet01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classiccabinet01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classiccabinet01_saucer2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classiccabinet01_v[28], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classiccabinet01_saucer),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classiccabinet01_v[40], 24, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_classiccabinet01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 21, 23, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_classiccabinet01_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_classiccabinet01_v[64], 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 5, 1, 0, 5, 7, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
