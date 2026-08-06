#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_snowisu_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_snoisu_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_snoisu_tex_pal[] = {
#include "assets/int_tak_snoisu_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowisu_back_tex[0x100];
#else
u8 int_tak_snowisu_back_tex[] = {
#include "assets/int_tak_snowisu_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowisu_face_tex[0x100];
#else
u8 int_tak_snowisu_face_tex[] = {
#include "assets/int_tak_snowisu_face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowisu_futi_tex[0x80];
#else
u8 int_tak_snowisu_futi_tex[] = {
#include "assets/int_tak_snowisu_futi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowisu_body2_tex[0x100];
#else
u8 int_tak_snowisu_body2_tex[] = {
#include "assets/int_tak_snowisu_body2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_snowisu_side_tex[0x80];
#else
u8 int_tak_snowisu_side_tex[] = {
#include "assets/int_tak_snowisu_side_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_snowisu_v[0x320 / sizeof(Vtx)];
#else
Vtx int_tak_snowisu_v[] = {
#include "assets/int_tak_snowisu_v.inc"
};
#endif

Gfx int_tak_snowisu_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_snoisu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowisu_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_snowisu_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 15, 14, 16, 15, 16, 17, 17, 16, 1),
    gsSPNTriangles_5b(17, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_snowisu_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_snoisu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_snowisu_body2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_snowisu_v[18], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_snowisu_futi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 15, 18, 19, 15, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 21, 12, 13, 21, 13, 22, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 12, 8, 11, 12, 11, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 20, 23, 18, 23, 19, 9, 4, 7),
    gsSPNTriangles_5b(9, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_snowisu_face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_snowisu_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_snowisu_v[46], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
