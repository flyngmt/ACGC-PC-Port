#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 rom_museum4_step_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 rom_museum4_step_pal[] = {
#include "assets/rom_museum4_step_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_stone_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_stone_pal[] = {
#include "assets/obj_s_stone_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_01_zassou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_01_zassou_pal[] = {
#include "assets/obj_01_zassou_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_c_01_flower_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_c_01_flower_pal[] = {
#include "assets/obj_c_01_flower_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_b_01_flower_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_b_01_flower_pal[] = {
#include "assets/obj_b_01_flower_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_a_01_flower_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_a_01_flower_pal[] = {
#include "assets/obj_a_01_flower_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_tree_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_tree_pal[] = {
#include "assets/obj_tree_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_leaf_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_leaf_tex[] = {
#include "assets/obj_s_tree_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_trunk_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_tree_trunk_tex[] = {
#include "assets/obj_s_tree_trunk_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_c_01_flower_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_c_01_flower_tex[] = {
#include "assets/obj_c_01_flower_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_b_01_flower_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_b_01_flower_tex[] = {
#include "assets/obj_b_01_flower_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_a_01_flower_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_a_01_flower_tex[] = {
#include "assets/obj_a_01_flower_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_zassou_01_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_zassou_01_tex[] = {
#include "assets/obj_zassou_01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_stone_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_stone_tex[] = {
#include "assets/obj_s_stone_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 rom_museum4_plate_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 rom_museum4_plate_tex[] = {
#include "assets/rom_museum4_plate_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_museum4_ue_v[0x1650 / sizeof(Vtx)];
#else
Vtx rom_museum4_ue_v[] = {
#include "assets/rom_museum4_ue_v.inc"
};
#endif

extern u16 bush_pal_dummy[];
extern u8 bush_a_tex_dummy[];

Gfx rom_museum4_ue_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, bush_a_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_museum4_ue_v[27], 11, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 4, 5, 3, 6),
    gsSPNTriangles_5b(7, 5, 8, 9, 7, 10, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tree_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[38], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
    gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
    gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[68], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
    gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
    gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[98], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
    gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
    gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[128], 30, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
    gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
    gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_trunk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[158], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 5, 2, 6, 2, 3, 6, 7, 8, 9),
    gsSPNTriangles_5b(8, 10, 9, 11, 9, 12, 11, 7, 9, 12, 9, 13),
    gsSPNTriangles_5b(9, 10, 13, 14, 15, 16, 15, 17, 16, 18, 16, 19),
    gsSPNTriangles_5b(18, 14, 16, 19, 16, 20, 16, 17, 20, 21, 22, 23),
    gsSPNTriangles_5b(22, 24, 23, 25, 23, 26, 25, 21, 23, 26, 23, 27),
    gsSPNTriangles_5b(23, 24, 27, 28, 29, 30, 29, 31, 30, 0, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[190], 27, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 7, 8, 7, 9, 8, 10, 8, 11),
    gsSPNTriangles_5b(10, 6, 8, 11, 8, 12, 8, 9, 12, 13, 14, 15),
    gsSPNTriangles_5b(14, 16, 15, 17, 15, 18, 17, 13, 15, 18, 15, 19),
    gsSPNTriangles_5b(15, 16, 19, 20, 21, 22, 21, 23, 22, 24, 22, 25),
    gsSPNTriangles_5b(24, 20, 22, 25, 22, 26, 22, 23, 26, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_a_01_flower_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_a_01_flower_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[217], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[249], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_b_01_flower_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_b_01_flower_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[265], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_c_01_flower_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_c_01_flower_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[297], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_01_zassou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_zassou_01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[329], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_step_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum4_plate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_ue_v[333], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_stone_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_stone_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(rom_museum4_ue_v, 27, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 3, 1, 4, 3, 5),
    gsSPNTriangles_5b(4, 1, 3, 3, 6, 5, 3, 0, 6, 4, 7, 1),
    gsSPNTriangles_5b(7, 2, 1, 8, 6, 9, 6, 0, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 9, 14, 10, 9, 0, 14, 14, 13, 10),
    gsSPNTriangles_5b(8, 9, 12, 9, 10, 12, 15, 16, 17, 16, 18, 17),
    gsSPNTriangles_5b(18, 19, 17, 16, 20, 18, 20, 21, 18, 16, 22, 20),
    gsSPNTriangles_5b(18, 23, 19, 23, 24, 19, 18, 21, 23, 15, 25, 16),
    gsSPNTriangles_5b(25, 22, 16, 15, 26, 25, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
