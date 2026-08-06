#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_ari_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_ari_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_ari_pal[] = {
#include "assets/int_nog_ari_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_ari_glass_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_ari_glass_tex_rgb_ci4_pal[] = {
#include "assets/int_nog_ari_glass_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_side_tex[0x200];
#else
u8 int_nog_ari_side_tex[] = {
#include "assets/int_nog_ari_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_foot_tex[0x80];
#else
u8 int_nog_ari_foot_tex[] = {
#include "assets/int_nog_ari_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_face_tex[0x300];
#else
u8 int_nog_ari_face_tex[] = {
#include "assets/int_nog_ari_face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_top_tex[0x100];
#else
u8 int_nog_ari_top_tex[] = {
#include "assets/int_nog_ari_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_base_tex[0x80];
#else
u8 int_nog_ari_base_tex[] = {
#include "assets/int_nog_ari_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ari_glass_tex_rgb_ci4[0x100];
#else
u8 int_nog_ari_glass_tex_rgb_ci4[] = {
#include "assets/int_nog_ari_glass_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_ari_v[0x340 / sizeof(Vtx)];
#else
Vtx int_nog_ari_v[] = {
#include "assets/int_nog_ari_v.inc"
};
#endif

Gfx int_nog_ari_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_ari_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_ari_v, 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_ari_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_nog_ari_face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 12, 15, 16, 15, 17, 18, 8, 11),
    gsSPNTriangles_5b(18, 11, 19, 19, 11, 20, 19, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_ari_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_ari_v[22], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 1, 8, 9, 1, 9, 6, 5, 10, 11),
    gsSPNTriangles_5b(5, 11, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ari_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 40),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ari_glass_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_ari_glass_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ari_v[34], 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 7, 2, 1),
    gsSPNTriangles_5b(7, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ari_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_ari_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ari_v[42], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
