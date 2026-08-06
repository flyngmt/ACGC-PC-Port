#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_suisou1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_suisou1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_suisou1_pal[] = {
#include "assets/obj_suisou1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_suisou1_evw_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 obj_suisou1_evw_tex_rgb_ci4_pal[] = {
#include "assets/obj_suisou1_evw_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_front_tex[0x200];
#else
u8 obj_suisou1_front_tex[] = {
#include "assets/obj_suisou1_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_futi_tex[0x80];
#else
u8 obj_suisou1_futi_tex[] = {
#include "assets/obj_suisou1_futi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_isi_tex[0x800];
#else
u8 obj_suisou1_isi_tex[] = {
#include "assets/obj_suisou1_isi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_mizu_tex[0x80];
#else
u8 obj_suisou1_mizu_tex[] = {
#include "assets/obj_suisou1_mizu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_evw_tex[0x80];
#else
u8 obj_suisou1_evw_tex[] = {
#include "assets/obj_suisou1_evw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_water1_tex_rgb_i4[0x200];
#else
u8 obj_suisou1_water1_tex_rgb_i4[] = {
#include "assets/obj_suisou1_water1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_suisou1_water2_tex_rgb_i4[0x200];
#else
u8 obj_suisou1_water2_tex_rgb_i4[] = {
#include "assets/obj_suisou1_water2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_suisou1_v[0x6D0 / sizeof(Vtx)];
#else
Vtx obj_suisou1_v[] = {
#include "assets/obj_suisou1_v.inc"
};
#endif

Gfx obj_suisou1_modelT[] = {
    gsSPTexture(1500, 5000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, 1, 0, ENVIRONMENT, COMBINED, 1, 0, PRIMITIVE,
                       COMBINED),
    gsDPSetPrimColor(0, 10, 255, 255, 255, 30),
    gsDPSetEnvColor(0, 30, 120, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_suisou1_evw_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_suisou1_evw_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_suisou1_v[5], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 12, 5, 4),
    gsSPNTriangles_5b(12, 4, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 1, 0, PRIMITIVE, COMBINED),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 90),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_suisou1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_suisou1_mizu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_suisou1_v[43], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, COMBINED, TEXEL0, 0, SHADE, COMBINED),
    gsDPSetEnvColor(150, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_suisou1_water1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_suisou1_water2_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_suisou1_v[55], 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 3, 5, 3, 2, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 1, 8, 4, 1, 7, 6, 5, 7, 5, 8),
    gsSPNTriangles_5b(5, 4, 8, 9, 10, 11, 10, 9, 12, 13, 10, 12),
    gsSPNTriangles_5b(11, 10, 13, 14, 15, 16, 14, 17, 15, 15, 18, 16),
    gsSPNTriangles_5b(18, 19, 16, 18, 20, 19, 20, 21, 19, 20, 22, 21),
    gsSPNTriangles_5b(20, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_suisou1_v[79], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 4, 6, 5, 6, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(6, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 11, 13, 12, 13, 14, 12),
    gsSPNTriangles_5b(13, 15, 14, 15, 16, 14, 15, 17, 16, 17, 18, 16),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 20, 21, 22, 21, 23, 22, 23, 24, 22),
    gsSPNTriangles_5b(23, 25, 24, 25, 26, 24, 26, 27, 24, 26, 28, 27),
    gsSPNTriangles_5b(26, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_suisou1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_suisou1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_suisou1_isi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_suisou1_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, obj_suisou1_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_suisou1_v[19], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 21, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_suisou1_futi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_suisou1_v[49], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_fish_set_mode[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};
