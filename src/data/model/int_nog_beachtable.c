#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_beachtable_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_beachtable_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_beachtable_pal[] = {
#include "assets/int_nog_beachtable_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_beachtable_fruit_tex[0x200];
#else
u8 int_nog_beachtable_fruit_tex[] = {
#include "assets/int_nog_beachtable_fruit_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_beachtable_pole_tex[0x200];
#else
u8 int_nog_beachtable_pole_tex[] = {
#include "assets/int_nog_beachtable_pole_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_beachtable_top_tex[0x400];
#else
u8 int_nog_beachtable_top_tex[] = {
#include "assets/int_nog_beachtable_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_beachtable_bubble_tex_rgb_ci4[0x80];
#else
u8 int_nog_beachtable_bubble_tex_rgb_ci4[] = {
#include "assets/int_nog_beachtable_bubble_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_beachtable_juice_tex[0x100];
#else
u8 int_nog_beachtable_juice_tex[] = {
#include "assets/int_nog_beachtable_juice_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_beachtable_v[0xC30 / sizeof(Vtx)];
#else
Vtx int_nog_beachtable_v[] = {
#include "assets/int_nog_beachtable_v.inc"
};
#endif

Gfx int_nog_beachtable_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_beachtable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_beachtable_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_beachtable_v, 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 8, 9, 7, 9, 4, 8, 10, 9),
    gsSPNTriangles_5b(11, 12, 13, 14, 11, 13, 14, 13, 7, 7, 6, 15),
    gsSPNTriangles_5b(7, 15, 14, 16, 17, 18, 16, 18, 19, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 16, 20, 22, 21, 23, 24, 25, 16, 23, 25),
    gsSPNTriangles_5b(16, 25, 14, 14, 15, 17, 14, 17, 16, 19, 18, 26),
    gsSPNTriangles_5b(19, 26, 27, 27, 28, 29, 27, 29, 19, 28, 30, 29),
    gsSPVertex(&int_nog_beachtable_v[31], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(4, 5, 6, 4, 6, 3, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_beachtable_pole_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_beachtable_v[38], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 8, 6, 8, 9, 9, 8, 5),
    gsSPNTriangles_5b(9, 5, 4, 10, 11, 12, 10, 13, 11, 11, 14, 12),
    gsSPNTriangles_5b(11, 15, 14, 16, 14, 17, 14, 15, 17, 16, 17, 10),
    gsSPNTriangles_5b(17, 13, 10, 18, 19, 20, 20, 21, 18, 22, 23, 24),
    gsSPNTriangles_5b(24, 25, 22, 26, 27, 28, 27, 29, 28, 26, 30, 27),
    gsSPNTriangles_5b(30, 31, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_beachtable_v[70], 24, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 4, 0, 2),
    gsSPNTriangles_5b(4, 5, 0, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 13, 14, 12, 14, 15, 10, 12, 15),
    gsSPNTriangles_5b(10, 15, 11, 16, 17, 18, 16, 18, 19, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 18, 22, 16, 19, 22, 19, 23, 13, 22, 23),
    gsSPNTriangles_5b(13, 23, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_beachtable_fruit_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_beachtable_v[94], 27, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 6, 5, 8, 5, 9, 24, 25, 26),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 12, 13, 14, 12, 14, 10),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_beachtable_glassT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 60),
    gsDPSetEnvColor(255, 255, 255, 120),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_beachtable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_beachtable_juice_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_beachtable_v[121], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 5, 9, 6, 9, 10, 6),
    gsSPNTriangles_5b(3, 11, 4, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 25, 27, 26, 27, 28, 26),
    gsSPNTriangles_5b(29, 30, 26, 31, 29, 26, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_beachtable_v[153], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 1, 4, 1, 0, 4),
    gsSPNTriangles_5b(5, 1, 3, 5, 6, 1, 7, 8, 9, 8, 6, 9),
    gsSPNTriangles_5b(10, 11, 12, 10, 13, 11, 14, 11, 15, 11, 16, 15),
    gsSPNTriangles_5b(15, 17, 18, 15, 16, 17, 19, 20, 21, 22, 19, 21),
    gsSPNTriangles_5b(21, 20, 23, 21, 23, 24, 23, 25, 26, 27, 23, 26),
    gsSPNTriangles_5b(28, 29, 19, 28, 19, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_beachtable_v[184], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_beachtable_bubbleT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_beachtable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_beachtable_bubble_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_beachtable_v[190], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
