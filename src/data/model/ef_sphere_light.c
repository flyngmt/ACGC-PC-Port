#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_sphere_light_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_sphere_light_tex_4i4_rgb_i4[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_sphere_light_tex_4i4_rgb_i4[] = {
#include "assets/ef_sphere_light_tex_4i4_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_sphere_light_v[0x300 / sizeof(Vtx)];
#else
Vtx ef_sphere_light_v[] = {
#include "assets/ef_sphere_light_v.inc"
};
#endif

Gfx ef_sphere_light_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetEnvColor(255, 255, 120, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_sphere_light_tex_4i4_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(ef_sphere_light_v, 14, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 7, 8, 10, 9, 9, 6, 7),
    gsSPNTriangles_5b(1, 11, 3, 11, 8, 3, 11, 10, 8, 12, 2, 3),
    gsSPNTriangles_5b(8, 12, 3, 7, 12, 8, 7, 5, 12, 5, 2, 12),
    gsSPNTriangles_5b(4, 13, 5, 5, 13, 2, 2, 13, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_sphere_light_tex_4i4_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&ef_sphere_light_v[14], 14, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 7, 8, 10, 9, 9, 6, 7),
    gsSPNTriangles_5b(1, 11, 3, 11, 8, 3, 11, 10, 8, 12, 2, 3),
    gsSPNTriangles_5b(8, 12, 3, 7, 12, 8, 7, 5, 12, 5, 2, 12),
    gsSPNTriangles_5b(4, 13, 5, 5, 13, 2, 2, 13, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_sphere_light_tex_4i4_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&ef_sphere_light_v[28], 20, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 2, 1, 3, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 0, 7, 6, 5, 7, 8, 6, 7, 5, 9),
    gsSPNTriangles_5b(5, 10, 9, 5, 2, 10, 2, 3, 11, 10, 2, 11),
    gsSPNTriangles_5b(11, 12, 10, 12, 9, 10, 13, 14, 12, 13, 12, 11),
    gsSPNTriangles_5b(11, 15, 13, 11, 3, 15, 13, 15, 16, 14, 13, 16),
    gsSPNTriangles_5b(14, 16, 7, 17, 8, 7, 16, 17, 7, 18, 17, 16),
    gsSPNTriangles_5b(3, 4, 19, 3, 19, 15, 15, 19, 18, 15, 18, 16),
    gsSPNTriangles_5b(14, 9, 12, 7, 9, 14, 5, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
