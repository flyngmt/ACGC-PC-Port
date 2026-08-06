#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 ef_axe_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 ef_axe_pal[] = {
#include "assets/ef_axe_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_axe_tuka1_tex_txt[0x200];
#else
u8 ef_axe_tuka1_tex_txt[] = {
#include "assets/ef_axe_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_axe_edge1_tex_txt[0x200];
#else
u8 ef_axe_edge1_tex_txt[] = {
#include "assets/ef_axe_edge1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_axe1_v[0x1D0 / sizeof(Vtx)];
#else
Vtx ef_axe1_v[] = {
#include "assets/ef_axe1_v.inc"
};
#endif

Gfx ef_axe1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_axe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, ef_axe_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_axe1_v, 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, ef_axe_edge1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(15, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 16, 21, 24, 21, 25, 25, 21, 26),
    gsSPNTriangles_5b(19, 22, 21, 19, 21, 16, 19, 16, 15, 20, 19, 15),
    gsSPNTriangles_5b(20, 15, 27, 21, 23, 26, 18, 28, 19, 28, 22, 19),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_axe_tuka2_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_axe_tuka2_tex_txt[] = {
#include "assets/ef_axe_tuka2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_axe_edge2_tex_txt[0x200];
#else
u8 ef_axe_edge2_tex_txt[] = {
#include "assets/ef_axe_edge2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_axe2_v[0x1B0 / sizeof(Vtx)];
#else
Vtx ef_axe2_v[] = {
#include "assets/ef_axe2_v.inc"
};
#endif

Gfx ef_axe2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_axe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, ef_axe_tuka2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_axe2_v, 27, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, ef_axe_edge2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(15, 14, 15, 16, 17, 18, 19, 17, 19, 14),
    gsSPNTriangles_5b(15, 20, 21, 22, 23, 24, 24, 23, 18, 24, 18, 17),
    gsSPNTriangles_5b(15, 19, 18, 15, 18, 23, 21, 25, 15, 23, 22, 26),
    gsSPNTriangles_5b(16, 15, 25, 23, 20, 15, 26, 20, 23, 14, 19, 15),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_axe_edge3_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_axe_edge3_tex_txt[] = {
#include "assets/ef_axe_edge3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_axe3_v[0xB0 / sizeof(Vtx)];
#else
Vtx ef_axe3_v[] = {
#include "assets/ef_axe3_v.inc"
};
#endif

Gfx ef_axe3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_axe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_axe_edge3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_axe3_v, 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(0, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
