#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_island_sensui01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_island_sensui01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_island_sensui01_pal[] = {
#include "assets/int_ike_island_sensui01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_senhead1_tex_txt[0x400];
#else
u8 int_ike_island_senhead1_tex_txt[] = {
#include "assets/int_ike_island_senhead1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_senbody1_tex_txt[0x100];
#else
u8 int_ike_island_senbody1_tex_txt[] = {
#include "assets/int_ike_island_senbody1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_senleg1_tex_txt[0x100];
#else
u8 int_ike_island_senleg1_tex_txt[] = {
#include "assets/int_ike_island_senleg1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_senhead2_tex_txt[0x100];
#else
u8 int_ike_island_senhead2_tex_txt[] = {
#include "assets/int_ike_island_senhead2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_sensuiface_pic_i4[0x200];
#else
u8 int_ike_island_sensuiface_pic_i4[] = {
#include "assets/int_ike_island_sensuiface_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_island_sensui01_v[0x6B0 / sizeof(Vtx)];
#else
Vtx int_ike_island_sensui01_v[] = {
#include "assets/int_ike_island_sensui01_v.inc"
};
#endif

Gfx int_ike_island_sensui01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, int_ike_island_senhead1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_island_sensui01_v, 12, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 4, 3, 5),
    gsSPNTriangles_5b(1, 6, 7, 7, 8, 3, 3, 8, 5, 6, 9, 10),
    gsSPNTriangles_5b(10, 11, 8, 8, 11, 5, 7, 2, 1, 3, 2, 7),
    gsSPNTriangles_5b(8, 7, 10, 10, 7, 6, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_sensui01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_island_senbody1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_island_sensui01_v[12], 31, 0),
    gsSPNTrianglesInit_5b(40, 0, 1, 2, 3, 4, 2, 5, 3, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 5, 12, 13, 14, 15, 12, 16),
    gsSPNTriangles_5b(0, 4, 11, 14, 13, 9, 15, 9, 17, 6, 18, 19),
    gsSPNTriangles_5b(15, 20, 7, 7, 13, 12, 7, 12, 15, 9, 13, 7),
    gsSPNTriangles_5b(2, 4, 0, 6, 3, 2, 21, 22, 1, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 23, 24, 9, 8, 12, 14, 16, 5, 11, 3),
    gsSPNTriangles_5b(25, 6, 19, 11, 4, 3, 16, 26, 15, 6, 27, 5),
    gsSPNTriangles_5b(11, 27, 0, 9, 26, 14, 22, 8, 1, 22, 21, 24),
    gsSPNTriangles_5b(21, 0, 28, 29, 9, 24, 8, 22, 24, 1, 0, 21),
    gsSPNTriangles_5b(23, 20, 15, 16, 14, 30, 2, 18, 6, 23, 15, 17),
    gsSPNTriangles_5b(25, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_island_senleg1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_island_sensui01_v[43], 25, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(13, 3, 4, 5, 6, 7, 8, 3, 9, 10),
    gsSPNTriangles_5b(10, 11, 8, 12, 13, 14, 15, 16, 12, 14, 17, 12),
    gsSPNTriangles_5b(12, 18, 15, 19, 4, 3, 14, 20, 17, 15, 21, 6),
    gsSPNTriangles_5b(5, 20, 14, 18, 21, 15, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_island_sensui01_v[68], 18, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 0, 7),
    gsSPNTriangles_5b(8, 9, 6, 3, 10, 11, 6, 12, 8, 11, 4, 3),
    gsSPNTriangles_5b(5, 13, 3, 7, 12, 6, 0, 14, 15, 15, 16, 13),
    gsSPNTriangles_5b(2, 14, 0, 13, 16, 17, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_island_senhead2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_sensui01_v[86], 16, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 2, 1, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 2, 11, 0, 0, 11, 10),
    gsSPNTriangles_5b(7, 12, 13, 3, 14, 2, 14, 13, 12, 12, 9, 11),
    gsSPNTriangles_5b(11, 9, 10, 13, 6, 7, 8, 7, 15, 9, 12, 7),
    gsSPNTriangles_5b(11, 2, 12, 12, 2, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_island_sensui01_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, int_ike_island_sensuiface_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_sensui01_v[102], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 2, 1, 3),
    gsSPNTriangles_5b(2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
