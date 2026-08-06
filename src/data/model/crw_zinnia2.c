#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_zinnia2_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_zinnia2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_zinnia2_pal[] = {
#include "assets/crw_zinnia2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_zinnia21_tex_txt[0x200];
#else
u8 crw_zinnia21_tex_txt[] = {
#include "assets/crw_zinnia21_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_zinnia22_tex_txt[0x80];
#else
u8 crw_zinnia22_tex_txt[] = {
#include "assets/crw_zinnia22_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_zinnia2_v[0x440 / sizeof(Vtx)];
#else
Vtx crw_zinnia2_v[] = {
#include "assets/crw_zinnia2_v.inc"
};
#endif

Gfx crw_zinnia2_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_zinnia2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_zinnia21_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_zinnia2_v, 31, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 1, 3, 3, 1, 4),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 10, 9, 11, 11, 9, 12),
    gsSPNTriangles_5b(11, 13, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 14, 15, 16, 16, 15, 17, 17, 15, 18),
    gsSPNTriangles_5b(17, 19, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 22, 21, 23, 23, 21, 24),
    gsSPNTriangles_5b(23, 25, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_zinnia22_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 26, 27, 28, 29, 26, 28, 27, 30, 28),
    gsSPNTriangles_5b(30, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&crw_zinnia2_v[31], 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_zinnia21_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 7, 6, 8, 8, 6, 9),
    gsSPNTriangles_5b(8, 10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 13, 12, 14, 14, 12, 15),
    gsSPNTriangles_5b(14, 16, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 17, 18, 19, 19, 18, 20, 20, 18, 21),
    gsSPNTriangles_5b(20, 22, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(3, 23, 24, 25, 25, 24, 26, 26, 24, 27),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&crw_zinnia2_v[62], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 1, 3, 3, 1, 4),
    gsSPNTriangles_5b(3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
