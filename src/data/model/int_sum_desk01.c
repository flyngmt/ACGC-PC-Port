#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_desk01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_desk01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_desk01_pal[] = {
#include "assets/int_sum_desk01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_side[0x100];
#else
u8 int_sum_desk01_side[] = {
#include "assets/int_sum_desk01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_top[0x100];
#else
u8 int_sum_desk01_top[] = {
#include "assets/int_sum_desk01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_topside[0x100];
#else
u8 int_sum_desk01_topside[] = {
#include "assets/int_sum_desk01_topside.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_drawer[0x100];
#else
u8 int_sum_desk01_drawer[] = {
#include "assets/int_sum_desk01_drawer.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_back[0x200];
#else
u8 int_sum_desk01_back[] = {
#include "assets/int_sum_desk01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_front[0x100];
#else
u8 int_sum_desk01_front[] = {
#include "assets/int_sum_desk01_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_light[0x80];
#else
u8 int_sum_desk01_light[] = {
#include "assets/int_sum_desk01_light.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_mini[0x40];
#else
u8 int_sum_desk01_mini[] = {
#include "assets/int_sum_desk01_mini.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_desk01_book[0x40];
#else
u8 int_sum_desk01_book[] = {
#include "assets/int_sum_desk01_book.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_desk01_v[0x4A0 / sizeof(Vtx)];
#else
Vtx int_sum_desk01_v[] = {
#include "assets/int_sum_desk01_v.inc"
};
#endif

Gfx int_sum_desk01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_desk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_desk01_mini),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_desk01_v, 27, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_desk01_light),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 4, 5, 6, 4, 7, 8, 5, 9, 10),
    gsSPNTriangles_5b(9, 5, 4, 8, 9, 4, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_desk01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 11, 12, 13, 14, 15, 16, 14, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 18, 20, 21, 22, 23, 24, 22, 24, 25),
    gsSPNTriangles_5b(11, 26, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_desk01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_desk01_v[27], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(0, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_desk01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_desk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_desk01_book),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_desk01_v[39], 23, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_desk01_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 8, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_desk01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 12, 13, 9, 12, 9, 11),
    gsSPNTriangles_5b(9, 14, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_desk01_drawer),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 21, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_desk01_topside),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_desk01_v[62], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};
