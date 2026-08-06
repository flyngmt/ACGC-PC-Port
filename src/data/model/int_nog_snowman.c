#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_snowman_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_snowman_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_snowman_pal[] = {
#include "assets/int_nog_snowman_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_snowman_body_tex[0x200];
#else
u8 int_nog_snowman_body_tex[] = {
#include "assets/int_nog_snowman_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_snowman_head_tex[0x200];
#else
u8 int_nog_snowman_head_tex[] = {
#include "assets/int_nog_snowman_head_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_snowman_v[0x360 / sizeof(Vtx)];
#else
Vtx int_nog_snowman_v[] = {
#include "assets/int_nog_snowman_v.inc"
};
#endif

Gfx int_nog_snowman_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_snowman_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_snowman_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_snowman_v, 29, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 0, 2, 3, 3, 4, 0),
    gsSPNTriangles_5b(4, 5, 0, 2, 6, 7, 2, 7, 3, 1, 8, 9),
    gsSPNTriangles_5b(10, 11, 1, 1, 9, 2, 9, 6, 2, 0, 5, 10),
    gsSPNTriangles_5b(0, 10, 1, 12, 13, 14, 13, 15, 14, 5, 15, 10),
    gsSPNTriangles_5b(15, 13, 10, 12, 16, 13, 13, 17, 10, 4, 18, 15),
    gsSPNTriangles_5b(4, 15, 5, 14, 15, 18, 14, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 21, 20, 6, 21, 7, 21, 23, 7, 9, 24, 22),
    gsSPNTriangles_5b(9, 22, 21, 9, 21, 6, 25, 26, 27, 26, 28, 27),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_snowman_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_nog_snowman_v[29], 25, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 2, 3, 0, 2, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 5, 7, 6, 7, 8, 6),
    gsSPNTriangles_5b(9, 10, 11, 12, 9, 11, 12, 11, 13, 12, 13, 1),
    gsSPNTriangles_5b(0, 12, 1, 3, 14, 0, 6, 15, 3, 8, 16, 6),
    gsSPNTriangles_5b(0, 17, 12, 12, 18, 9, 1, 19, 20, 1, 13, 19),
    gsSPNTriangles_5b(13, 11, 19, 11, 21, 19, 11, 10, 21, 22, 23, 7),
    gsSPNTriangles_5b(22, 7, 5, 24, 22, 5, 24, 5, 4, 24, 4, 2),
    gsSPNTriangles_5b(20, 24, 2, 2, 1, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
