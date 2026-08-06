#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_tub_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_tub_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_tub_pal[] = {
#include "assets/int_yaz_tub_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_tub_wood2_txt[0x200];
#else
u8 int_yaz_tub_wood2_txt[] = {
#include "assets/int_yaz_tub_wood2_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_tub_wood_txt[0x400];
#else
u8 int_yaz_tub_wood_txt[] = {
#include "assets/int_yaz_tub_wood_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_tub_water_4i4_pic_i4[0x100];
#else
u8 int_yaz_tub_water_4i4_pic_i4[] = {
#include "assets/int_yaz_tub_water_4i4_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_tub_v[0x580 / sizeof(Vtx)];
#else
Vtx int_yaz_tub_v[] = {
#include "assets/int_yaz_tub_v.inc"
};
#endif

Gfx int_yaz_tub_water_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0,
                       SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 30, 155, 155, 200, 100),
    gsDPSetEnvColor(100, 100, 175, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, int_yaz_tub_water_4i4_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_tub_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_tub_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_tub_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_tub_wood2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_tub_v[4], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&int_yaz_tub_v[34], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_yaz_tub_wood_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_tub_v[64], 24, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(0, 19, 1, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
