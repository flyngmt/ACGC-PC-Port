#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_bag1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_bag1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_bag1_pal[] = {
#include "assets/crw_bag1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_bag1_tex_txt[0x400];
#else
u8 crw_bag1_tex_txt[] = {
#include "assets/crw_bag1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_bagpikke1_tex_txt[0x40];
#else
u8 crw_bagpikke1_tex_txt[] = {
#include "assets/crw_bagpikke1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_bagpikke2_tex_txt[0x40];
#else
u8 crw_bagpikke2_tex_txt[] = {
#include "assets/crw_bagpikke2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_bag1_v[0x310 / sizeof(Vtx)];
#else
Vtx crw_bag1_v[] = {
#include "assets/crw_bag1_v.inc"
};
#endif

Gfx crw_bag1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_bag1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, crw_bag1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_bag1_v, 24, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 4, 5, 6, 4, 3),
    gsSPNTriangles_5b(7, 8, 9, 7, 1, 10, 5, 4, 11, 12, 11, 6),
    gsSPNTriangles_5b(11, 4, 6, 10, 1, 0, 11, 13, 5, 14, 13, 15),
    gsSPNTriangles_5b(15, 0, 14, 11, 12, 10, 6, 16, 12, 14, 5, 13),
    gsSPNTriangles_5b(12, 16, 7, 10, 15, 13, 10, 13, 11, 0, 15, 10),
    gsSPNTriangles_5b(10, 12, 7, 2, 1, 7, 17, 14, 0, 5, 14, 18),
    gsSPNTriangles_5b(19, 20, 21, 5, 22, 3, 2, 23, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, crw_bagpikke1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crw_bag1_v[24], 25, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, crw_bagpikke2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 9, 10, 11, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 23, 20, 24, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};
