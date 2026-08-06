#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_kamakura_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 rom_kamakura_carp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 rom_kamakura_carp_pal[] = {
#include "assets/rom_kamakura_carp_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_kamakura_goza_pal[0x20 / sizeof(u16)];
#else
u16 rom_kamakura_goza_pal[] = {
#include "assets/rom_kamakura_goza_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_kamakura_yuki_pal[0x20 / sizeof(u16)];
#else
u16 rom_kamakura_yuki_pal[] = {
#include "assets/rom_kamakura_yuki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_kamakura_rou_pal[0x20 / sizeof(u16)];
#else
u16 rom_kamakura_rou_pal[] = {
#include "assets/rom_kamakura_rou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_kamakura_a1_pal[0x20 / sizeof(u16)];
#else
u16 rom_kamakura_a1_pal[] = {
#include "assets/rom_kamakura_a1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_kamakura_nabe_pal[0x20 / sizeof(u16)];
#else
u16 rom_kamakura_nabe_pal[] = {
#include "assets/rom_kamakura_nabe_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_carp[0x800];
#else
u8 rom_kamakura_carp[] = {
#include "assets/rom_kamakura_carp.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_goza[0x200];
#else
u8 rom_kamakura_goza[] = {
#include "assets/rom_kamakura_goza.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_yuki1[0x400];
#else
u8 rom_kamakura_yuki1[] = {
#include "assets/rom_kamakura_yuki1.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_yuki2[0x800];
#else
u8 rom_kamakura_yuki2[] = {
#include "assets/rom_kamakura_yuki2.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_yuki3[0x400];
#else
u8 rom_kamakura_yuki3[] = {
#include "assets/rom_kamakura_yuki3.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_yuki4[0x200];
#else
u8 rom_kamakura_yuki4[] = {
#include "assets/rom_kamakura_yuki4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_rou[0x100];
#else
u8 rom_kamakura_rou[] = {
#include "assets/rom_kamakura_rou.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_a1[0x200];
#else
u8 rom_kamakura_a1[] = {
#include "assets/rom_kamakura_a1.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_wa[0x80];
#else
u8 rom_kamakura_wa[] = {
#include "assets/rom_kamakura_wa.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_nabe1[0x80];
#else
u8 rom_kamakura_nabe1[] = {
#include "assets/rom_kamakura_nabe1.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_etc[0x800];
#else
u8 rom_kamakura_etc[] = {
#include "assets/rom_kamakura_etc.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_kage_us[0x80];
#else
u8 rom_kamakura_kage_us[] = {
#include "assets/rom_kamakura_kage_us.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_a2_rgb_ci4[0x200];
#else
u8 rom_kamakura_a2_rgb_ci4[] = {
#include "assets/rom_kamakura_a2_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura__takibi1_int_i4[0x100];
#else
u8 rom_kamakura__takibi1_int_i4[] = {
#include "assets/rom_kamakura__takibi1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura__takibi2_int_i4[0x100];
#else
u8 rom_kamakura__takibi2_int_i4[] = {
#include "assets/rom_kamakura__takibi2_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_fire1_rgb_i4[0x80];
#else
u8 rom_kamakura_fire1_rgb_i4[] = {
#include "assets/rom_kamakura_fire1_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_fire2_rgb_i4[0x80];
#else
u8 rom_kamakura_fire2_rgb_i4[] = {
#include "assets/rom_kamakura_fire2_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_kamakura_fire3_rgb_i4[0x80];
#else
u8 rom_kamakura_fire3_rgb_i4[] = {
#include "assets/rom_kamakura_fire3_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_kamakura_v[0x1390 / sizeof(Vtx)];
#else
Vtx rom_kamakura_v[] = {
#include "assets/rom_kamakura_v.inc"
};
#endif

Gfx rom_kamakura_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 40, 10, 0, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_kamakura_kage_us),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_kamakura_v[191], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 230, 0, 150),
    gsDPSetEnvColor(255, 50, 0, 255),
    gsSPDisplayList(anime_1_txt),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_kamakura_v[203], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetPrimColor(0, 255, 255, 220, 0, 180),
    gsSPDisplayList(anime_5_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_kamakura_v[207], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                       ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 255, 255, 170, 0, 255),
    gsDPSetEnvColor(255, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, rom_kamakura__takibi1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, rom_kamakura__takibi2_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 8),
    gsSPDisplayList(anime_6_mdl),
    gsSPVertex(&rom_kamakura_v[211], 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_kamakura_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_rou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_kamakura_rou),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_kamakura_v[195], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_nabe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_kamakura_etc),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_kamakura_v[231], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_kamakura_v[263], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 2, 5, 8, 5, 9, 10, 11, 2),
    gsSPNTriangles_5b(10, 2, 1, 12, 6, 5, 12, 5, 13, 5, 2, 11),
    gsSPNTriangles_5b(5, 11, 13, 12, 10, 1, 12, 1, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_kamakura_wa),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_kamakura_etc),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_kamakura_v[281], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 8, 11, 12),
    gsSPNTriangles_5b(8, 12, 13, 14, 13, 15, 13, 8, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 17, 20, 21, 17, 21, 19, 21, 22, 23),
    gsSPNTriangles_5b(21, 23, 19, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_a1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_kamakura_v[309], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_yuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_kamakura_yuki3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(rom_kamakura_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_kamakura_yuki1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_kamakura_v[5], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 8, 3, 9, 10, 11, 12, 11, 13, 12),
    gsSPNTriangles_5b(14, 15, 16, 15, 10, 16, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(17, 21, 22, 21, 23, 22, 22, 23, 24, 18, 25, 20),
    gsSPNTriangles_5b(4, 26, 6, 7, 27, 8, 12, 13, 28, 16, 29, 14),
    gsSPVertex(&rom_kamakura_v[35], 21, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 2, 6, 0),
    gsSPNTriangles_5b(6, 7, 0, 3, 5, 8, 7, 9, 0, 7, 5, 9),
    gsSPNTriangles_5b(10, 11, 12, 11, 13, 12, 14, 15, 16, 15, 17, 16),
    gsSPNTriangles_5b(18, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_carp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_kamakura_carp),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_kamakura_v[56], 17, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 4, 5, 0, 6),
    gsSPNTriangles_5b(7, 0, 8, 9, 0, 2, 0, 10, 1, 9, 6, 0),
    gsSPNTriangles_5b(5, 11, 0, 11, 8, 0, 7, 12, 0, 12, 4, 0),
    gsSPNTriangles_5b(3, 10, 0, 13, 3, 4, 14, 5, 6, 1, 15, 2),
    gsSPNTriangles_5b(16, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_goza_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_kamakura_goza),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_kamakura_v[73], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 1, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 9, 10, 9, 8, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_yuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_kamakura_yuki4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_kamakura_v[89], 19, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 1, 6, 7, 8, 9, 8, 2, 9, 1, 5, 3),
    gsSPNTriangles_5b(10, 11, 0, 11, 1, 0, 11, 6, 1, 2, 8, 12),
    gsSPNTriangles_5b(0, 2, 12, 0, 12, 10, 3, 9, 2, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 15, 14, 17, 18, 15, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 128, rom_kamakura_yuki2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_kamakura_v[108], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(4, 7, 5, 7, 8, 5, 9, 7, 4, 10, 5, 11),
    gsSPNTriangles_5b(10, 3, 5, 5, 8, 11, 8, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(14, 16, 15, 17, 18, 19, 16, 17, 15, 20, 21, 17),
    gsSPNTriangles_5b(21, 18, 17, 14, 22, 16, 22, 23, 16, 24, 11, 25),
    gsSPNTriangles_5b(24, 10, 11, 12, 26, 27, 11, 27, 25, 27, 21, 20),
    gsSPNTriangles_5b(27, 26, 21, 22, 25, 23, 22, 24, 25, 28, 29, 30),
    gsSPNTriangles_5b(2, 28, 30, 9, 4, 6, 9, 6, 31, 0, 0, 0),
    gsSPVertex(&rom_kamakura_v[140], 22, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 0, 6, 7, 0, 2, 6, 5, 8, 4),
    gsSPNTriangles_5b(5, 9, 8, 9, 10, 11, 12, 7, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 18, 12, 19, 12, 20, 19, 12, 13, 20),
    gsSPNTriangles_5b(19, 15, 14, 19, 20, 15, 21, 17, 14, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_kamakura_nabe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, rom_kamakura_nabe1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_kamakura_v[162], 29, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 6, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(10, 14, 11, 14, 12, 11, 9, 14, 10, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 16, 18, 16, 15, 8, 19, 18, 15, 17, 20),
    gsSPNTriangles_5b(21, 22, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 rom_kamakura_ring1[0x100];
#else
u8 rom_kamakura_ring1[] = {
#include "assets/rom_kamakura_ring1.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_kamakura_ring_v[0x40 / sizeof(Vtx)];
#else
Vtx rom_kamakura_ring_v[] = {
#include "assets/rom_kamakura_ring_v.inc"
};
#endif

Gfx rom_kamakura_ring_modelT[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, rom_kamakura_ring1),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(rom_kamakura_ring_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
