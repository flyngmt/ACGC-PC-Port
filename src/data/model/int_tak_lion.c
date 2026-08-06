#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_lion_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_lion_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_lion_pal[] = {
#include "assets/int_tak_lion_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_lion_water_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_lion_water_tex_rgb_ci4_pal[] = {
#include "assets/int_tak_lion_water_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_lion_back_tex[0x200];
#else
u8 int_tak_lion_back_tex[] = {
#include "assets/int_tak_lion_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_lion_body_tex[0x20];
#else
u8 int_tak_lion_body_tex[] = {
#include "assets/int_tak_lion_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_lion_face_tex[0x400];
#else
u8 int_tak_lion_face_tex[] = {
#include "assets/int_tak_lion_face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_lion_tail2_tex[0x180];
#else
u8 int_tak_lion_tail2_tex[] = {
#include "assets/int_tak_lion_tail2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_lion_water_tex[0x20];
#else
u8 int_tak_lion_water_tex[] = {
#include "assets/int_tak_lion_water_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_lion_v[0x520 / sizeof(Vtx)];
#else
Vtx int_tak_lion_v[] = {
#include "assets/int_tak_lion_v.inc"
};
#endif

Gfx int_tak_lion_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_lion_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_lion_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_lion_v, 21, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 1, 7, 1, 5, 7, 8, 3, 6),
    gsSPNTriangles_5b(3, 1, 6, 6, 9, 10, 6, 10, 8, 7, 11, 9),
    gsSPNTriangles_5b(7, 9, 6, 9, 11, 12, 9, 12, 13, 14, 10, 9),
    gsSPNTriangles_5b(14, 9, 13, 0, 2, 15, 0, 15, 16, 4, 0, 16),
    gsSPNTriangles_5b(4, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 18, 19, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_lion_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_lion_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_tak_lion_tail2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_lion_v[21], 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 4, 6, 7, 2, 4, 8),
    gsSPNTriangles_5b(4, 7, 8, 2, 9, 0, 2, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_tak_lion_face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_lion_v[31], 30, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 5, 12, 11, 5, 7, 12, 11, 12, 13),
    gsSPNTriangles_5b(7, 13, 12, 7, 14, 13, 13, 14, 11, 14, 15, 11),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 19, 18, 7, 20, 19, 7),
    gsSPNTriangles_5b(19, 20, 16, 20, 7, 21, 16, 20, 21, 21, 7, 4),
    gsSPNTriangles_5b(6, 21, 4, 18, 14, 7, 18, 17, 15, 18, 15, 14),
    gsSPNTriangles_5b(25, 26, 17, 25, 17, 16, 17, 26, 15, 15, 26, 28),
    gsSPNTriangles_5b(11, 15, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(17, 6, 5, 8, 8, 9, 6, 8, 5, 10),
    gsSPNTriangles_5b(5, 11, 10, 22, 16, 21, 22, 21, 9, 9, 21, 6),
    gsSPNTriangles_5b(22, 9, 8, 22, 8, 10, 23, 24, 25, 25, 16, 23),
    gsSPNTriangles_5b(16, 22, 23, 10, 27, 23, 10, 23, 22, 27, 10, 11),
    gsSPNTriangles_5b(27, 11, 28, 28, 29, 27, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_tak_lion_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_lion_v[61], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 5, 0, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 0, 10, 1, 11, 7, 9, 6, 5, 11),
    gsSPNTriangles_5b(6, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 1, 3, 4, 1, 4, 2, 2, 4, 5),
    gsSPNTriangles_5b(5, 4, 11, 11, 4, 7, 4, 3, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_lion_alphaT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, SHADE, 0, PRIM_LOD_FRAC, 0, COMBINED, 0, SHADE, 0, 0, 0,
                       0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_lion_water_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_lion_water_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_lion_water_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_lion_v[73], 9, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 3, 0, 5),
    gsSPNTriangles_5b(0, 2, 5, 4, 6, 0, 7, 1, 0, 7, 0, 6),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 7, 6, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
