#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_cube_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_tak_cube_body_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 int_tak_cube_body_tex[] = {
#include "assets/int_tak_cube_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_cube_glass_tex[0x80];
#else
u8 int_tak_cube_glass_tex[] = {
#include "assets/int_tak_cube_glass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_cube_evw_tex_rgb_i4[0x80];
#else
u8 int_tak_cube_evw_tex_rgb_i4[] = {
#include "assets/int_tak_cube_evw_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_cube_v[0x8A0 / sizeof(Vtx)];
#else
Vtx int_tak_cube_v[] = {
#include "assets/int_tak_cube_v.inc"
};
#endif

Gfx int_tak_cube_body_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 240, 250, 255, 255),
    gsDPSetEnvColor(80, 65, 160, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_tak_cube_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_cube_v, 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 16, 18, 19, 16, 19, 17, 18, 20, 21),
    gsSPNTriangles_5b(18, 21, 19, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 28, 30, 31, 28, 31, 29, 0, 0, 0),
    gsSPVertex(&int_tak_cube_v[32], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 1, 0, 8, 1, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 7, 14, 7, 6, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&int_tak_cube_v[64], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 4, 8, 5, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 20, 22, 23, 20, 23, 21, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&int_tak_cube_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_cube_evwT_model[] = {
    gsSPTexture(3500, 600, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetEnvColor(200, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_tak_cube_evw_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_cube_v[100], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_cube_glass_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetEnvColor(150, 200, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_tak_cube_glass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_cube_v[124], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 5, 9, 12),
    gsSPNTriangles_5b(5, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 0, 5, 4, 5, 6, 1, 7, 8),
    gsSPNTriangles_5b(1, 8, 9, 7, 10, 11, 7, 11, 8, 0, 1, 9),
    gsSPNTriangles_5b(0, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
