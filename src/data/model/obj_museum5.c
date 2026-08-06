#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_museum5_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_museum5_on_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_museum5_on_pal[] = {
#include "assets/obj_museum5_on_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_museum5_wallB_pal[0x20 / sizeof(u16)];
#else
u16 obj_museum5_wallB_pal[] = {
#include "assets/obj_museum5_wallB_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_museum5_soko_pal[0x20 / sizeof(u16)];
#else
u16 obj_museum5_soko_pal[] = {
#include "assets/obj_museum5_soko_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_museum5_hitode_pal[0x20 / sizeof(u16)];
#else
u16 obj_museum5_hitode_pal[] = {
#include "assets/obj_museum5_hitode_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_museum5_evw_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 obj_museum5_evw_tex_rgb_ci4_pal[] = {
#include "assets/obj_museum5_evw_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_isi_tex[0x800];
#else
u8 obj_museum5_isi_tex[] = {
#include "assets/obj_museum5_isi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_pink_tex[0x800];
#else
u8 obj_museum5_pink_tex[] = {
#include "assets/obj_museum5_pink_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_inside_tex[0x80];
#else
u8 obj_museum5_inside_tex[] = {
#include "assets/obj_museum5_inside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_soko_tex[0x400];
#else
u8 obj_museum5_soko_tex[] = {
#include "assets/obj_museum5_soko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_hitode1_tex[0x100];
#else
u8 obj_museum5_hitode1_tex[] = {
#include "assets/obj_museum5_hitode1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_wallB_tex[0x400];
#else
u8 obj_museum5_wallB_tex[] = {
#include "assets/obj_museum5_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_hitode2_tex[0x100];
#else
u8 obj_museum5_hitode2_tex[] = {
#include "assets/obj_museum5_hitode2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_fuji_tex[0x80];
#else
u8 obj_museum5_fuji_tex[] = {
#include "assets/obj_museum5_fuji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_evw_tex[0x80];
#else
u8 obj_museum5_evw_tex[] = {
#include "assets/obj_museum5_evw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_water1_tex_rgb_i4[0x200];
#else
u8 obj_museum5_water1_tex_rgb_i4[] = {
#include "assets/obj_museum5_water1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_water2_tex_rgb_i4[0x200];
#else
u8 obj_museum5_water2_tex_rgb_i4[] = {
#include "assets/obj_museum5_water2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_museum5_v[0x18D0 / sizeof(Vtx)];
#else
Vtx obj_museum5_v[] = {
#include "assets/obj_museum5_v.inc"
};
#endif

Gfx obj_museum5_modelT[] = {
    gsSPTexture(1500, 5000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, 1, 0, ENVIRONMENT, COMBINED, 1, 0, PRIMITIVE,
                       COMBINED),
    gsDPSetPrimColor(0, 20, 255, 255, 255, 60),
    gsDPSetEnvColor(0, 30, 120, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_evw_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_evw_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_v[83], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, COMBINED, TEXEL0, 0, SHADE, COMBINED),
    gsDPSetEnvColor(150, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_museum5_water1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_museum5_water2_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_v[326], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 1),
    gsSPNTriangles_5b(5, 6, 1, 7, 8, 5, 8, 9, 5, 10, 11, 8),
    gsSPNTriangles_5b(11, 12, 8, 13, 14, 15, 14, 16, 15, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 2, 3, 21, 22, 2, 21, 0, 2, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 26, 24, 24, 27, 25, 27, 28, 25),
    gsSPNTriangles_5b(27, 29, 28, 29, 30, 28, 29, 31, 30, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[358], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 2, 3, 4, 2, 1, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 16, 17, 15, 16, 18, 17),
    gsSPNTriangles_5b(18, 19, 17, 19, 20, 17, 19, 21, 20, 19, 22, 21),
    gsSPNTriangles_5b(23, 24, 25, 24, 26, 27, 28, 29, 26, 30, 28, 23),
    gsSPVertex(&obj_museum5_v[389], 8, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(6, 5, 3, 7, 6, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_museum5_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_soko_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_museum5_soko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_museum5_v, 17, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 2, 5, 1, 6),
    gsSPNTriangles_5b(7, 2, 1, 8, 9, 4, 4, 10, 2, 1, 11, 6),
    gsSPNTriangles_5b(12, 8, 4, 7, 1, 5, 0, 11, 1, 13, 8, 12),
    gsSPNTriangles_5b(13, 14, 8, 14, 9, 8, 15, 6, 16, 15, 5, 6),
    gsSPNTriangles_5b(3, 12, 4, 4, 9, 10, 11, 16, 6, 7, 3, 2),
    gsSPNTriangles_5b(10, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_wallB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_inside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_museum5_v[17], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 0, 4, 5),
    gsSPNTriangles_5b(6, 7, 8, 7, 9, 8, 10, 11, 8, 10, 12, 11),
    gsSPNTriangles_5b(6, 13, 7, 6, 14, 13, 14, 15, 16, 14, 16, 13),
    gsSPNTriangles_5b(15, 17, 16, 17, 5, 16, 17, 0, 5, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_on_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_museum5_isi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_museum5_v[35], 30, 0),
    gsSPNTrianglesInit_5b(33, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(4, 7, 6, 7, 8, 6, 7, 1, 8, 2, 9, 0),
    gsSPNTriangles_5b(9, 10, 0, 10, 8, 0, 8, 1, 0, 2, 11, 9),
    gsSPNTriangles_5b(10, 12, 8, 12, 6, 8, 12, 13, 6, 13, 5, 6),
    gsSPNTriangles_5b(14, 15, 16, 14, 16, 17, 14, 17, 18, 19, 14, 18),
    gsSPNTriangles_5b(19, 18, 20, 21, 19, 20, 21, 20, 22, 23, 21, 22),
    gsSPNTriangles_5b(17, 16, 24, 17, 24, 25, 18, 17, 25, 18, 25, 26),
    gsSPNTriangles_5b(20, 18, 26, 20, 26, 27, 22, 20, 27, 22, 27, 28),
    gsSPNTriangles_5b(23, 22, 28, 29, 23, 28, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_museum5_pink_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_museum5_v[65], 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_hitode_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_museum5_hitode2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_museum5_v[87], 22, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 2, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 9, 1, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_museum5_hitode1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 11, 12, 13, 14, 15, 12, 16, 17, 15),
    gsSPNTriangles_5b(18, 19, 17, 20, 21, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_fuji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_v[109], 29, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 12, 13, 14, 15, 16, 12),
    gsSPNTriangles_5b(16, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 26, 27, 28, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[138], 29, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 6, 8, 8, 7, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[167], 29, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 6, 7, 8, 9, 10, 6),
    gsSPNTriangles_5b(10, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 20, 21, 22, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[196], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[222], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 3),
    gsSPNTriangles_5b(7, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[248], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[274], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum5_v[300], 17, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 3),
    gsSPNTriangles_5b(7, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_wallB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_museum5_wallB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_v[317], 9, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(2, 4, 5, 6, 5, 4, 6, 7, 5, 7, 8, 5),
    gsSPEndDisplayList(),
};
