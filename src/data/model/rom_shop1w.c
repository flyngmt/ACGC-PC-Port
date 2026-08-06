#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop1w_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop1_pal[] = {
#include "assets/rom_shop1w/rom_shop1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop1_tubo_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop1_tubo_pal[] = {
#include "assets/rom_shop1_tubo_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_table_tex[0x600];
#else
static u8 rom_shop1_table_tex[] = {
#include "assets/rom_shop1w/rom_shop1_table_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_window_tex[0x800];
#else
static u8 rom_shop1_window_tex[] = {
#include "assets/rom_shop1w/rom_shop1_window_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_shadow_tex[0x400];
#else
static u8 rom_shop1_shadow_tex[] = {
#include "assets/rom_shop1w/rom_shop1_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_tubo_tex[0x400];
#else
u8 rom_shop1_tubo_tex[] = {
#include "assets/rom_shop1_tubo_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop1w_v[0x12E0 / sizeof(Vtx)];
#else
Vtx rom_shop1w_v[] = {
#include "assets/rom_shop1w_v.inc"
};
#endif

Gfx rom_shop1w_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 10, 0, 40, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, rom_shop1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop1w_v[282], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetPrimColor(0, 255, 160, 160, 160, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, rom_shop1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1w_v[298], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_shop1w_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 48, rom_shop1_table_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop1w_v[233], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 23),
    gsSPNTriangles_5b(26, 23, 22, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&rom_shop1w_v[265], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1w_v[269], 13, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(12, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop1w_v, 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 0, 10, 0, 2, 10, 2, 11, 10, 12, 13, 6),
    gsSPNTriangles_5b(12, 14, 13, 14, 15, 13, 15, 6, 13, 15, 16, 6),
    gsSPNTriangles_5b(0, 17, 1, 17, 5, 1, 0, 3, 17, 3, 5, 17),
    gsSPNTriangles_5b(8, 6, 16, 18, 19, 20, 21, 20, 19, 11, 21, 22),
    gsSPNTriangles_5b(21, 19, 22, 9, 22, 19, 9, 11, 22, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 24, 23, 25, 24, 26, 24, 25, 26, 19, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop1w_v[27], 31, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 3, 2, 1, 2, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 7, 5, 15, 5, 16, 15),
    gsSPNTriangles_5b(15, 17, 10, 18, 1, 6, 1, 0, 6, 8, 10, 17),
    gsSPNTriangles_5b(19, 12, 3, 12, 4, 3, 15, 16, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 27, 24, 26, 20, 11, 9),
    gsSPNTriangles_5b(21, 20, 9, 28, 29, 26, 30, 22, 21, 22, 30, 24),
    gsSPNTriangles_5b(25, 24, 30, 25, 28, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPVertex(&rom_shop1w_v[58], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop1_tubo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_shop1_tubo_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop1w_v[66], 32, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 6, 1, 6, 7, 1, 7, 8, 1),
    gsSPNTriangles_5b(8, 3, 1, 9, 10, 11, 9, 12, 10, 12, 13, 10),
    gsSPNTriangles_5b(13, 14, 10, 13, 15, 14, 13, 16, 15, 16, 17, 15),
    gsSPNTriangles_5b(17, 18, 15, 17, 19, 18, 17, 20, 19, 21, 22, 20),
    gsSPNTriangles_5b(21, 20, 17, 21, 17, 16, 23, 21, 16, 24, 23, 16),
    gsSPNTriangles_5b(24, 16, 13, 24, 13, 12, 25, 24, 12, 26, 25, 12),
    gsSPNTriangles_5b(26, 12, 9, 27, 28, 29, 27, 30, 28, 30, 31, 28),
    gsSPVertex(&rom_shop1w_v[98], 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 5, 7, 6, 5, 8, 7),
    gsSPNTriangles_5b(6, 7, 9, 6, 9, 10, 6, 10, 11, 3, 6, 11),
    gsSPNTriangles_5b(1, 3, 11, 1, 11, 12, 1, 12, 13, 2, 1, 13),
    gsSPNTriangles_5b(14, 2, 13, 14, 13, 15, 16, 17, 18, 16, 19, 17),
    gsSPNTriangles_5b(19, 20, 17, 20, 21, 17, 20, 22, 21, 20, 23, 22),
    gsSPNTriangles_5b(23, 24, 22, 24, 25, 22, 24, 26, 25, 24, 27, 26),
    gsSPNTriangles_5b(28, 29, 27, 28, 27, 24, 28, 24, 23, 30, 28, 23),
    gsSPNTriangles_5b(31, 30, 23, 31, 23, 20, 31, 20, 19, 0, 0, 0),
    gsSPVertex(&rom_shop1w_v[130], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 8, 9, 6, 9, 10, 6),
    gsSPNTriangles_5b(9, 11, 10, 9, 12, 11, 12, 13, 11, 13, 14, 11),
    gsSPNTriangles_5b(13, 15, 14, 13, 16, 15, 14, 15, 17, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 19, 11, 14, 19, 10, 11, 19, 10, 19, 20),
    gsSPNTriangles_5b(10, 20, 21, 6, 10, 21, 7, 6, 21, 7, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 26, 24, 26, 27, 24, 27, 28, 24),
    gsSPNTriangles_5b(27, 29, 28, 27, 30, 29, 30, 31, 29, 0, 0, 0),
    gsSPVertex(&rom_shop1w_v[162], 32, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 4, 5, 4, 0, 5, 0, 7, 8, 5, 7),
    gsSPNTriangles_5b(9, 8, 7, 9, 7, 10, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(13, 12, 11, 13, 11, 14, 15, 16, 17, 15, 18, 16),
    gsSPNTriangles_5b(18, 19, 16, 19, 20, 16, 19, 21, 20, 19, 22, 21),
    gsSPNTriangles_5b(22, 23, 21, 23, 24, 21, 23, 25, 24, 23, 26, 25),
    gsSPNTriangles_5b(24, 25, 6, 24, 6, 5, 24, 5, 8, 21, 24, 8),
    gsSPNTriangles_5b(20, 21, 8, 20, 8, 9, 20, 9, 12, 16, 20, 12),
    gsSPNTriangles_5b(17, 16, 12, 17, 12, 13, 27, 28, 29, 27, 30, 28),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop1w_v[194], 32, 0),
    gsSPNTrianglesInit_5b(37, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 5, 7, 6, 5, 8, 7),
    gsSPNTriangles_5b(9, 10, 8, 9, 8, 5, 9, 5, 4, 11, 9, 4),
    gsSPNTriangles_5b(12, 11, 4, 12, 4, 0, 12, 0, 13, 14, 12, 13),
    gsSPNTriangles_5b(15, 14, 13, 15, 13, 16, 17, 18, 19, 17, 2, 18),
    gsSPNTriangles_5b(2, 1, 18, 1, 20, 18, 1, 21, 20, 1, 3, 21),
    gsSPNTriangles_5b(3, 6, 21, 6, 22, 21, 6, 23, 22, 6, 7, 23),
    gsSPNTriangles_5b(22, 23, 24, 22, 24, 25, 22, 25, 26, 21, 22, 26),
    gsSPNTriangles_5b(20, 21, 26, 20, 26, 27, 20, 27, 28, 18, 20, 28),
    gsSPNTriangles_5b(19, 18, 28, 19, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop1w_v[224], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(5, 4, 2, 6, 5, 2, 7, 6, 2, 2, 1, 8),
    gsSPNTriangles_5b(7, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop1w_c(void) {
    pc_load_asset("assets/rom_shop1w/rom_shop1_pal.bin", rom_shop1_pal, 0x20, 0xC4F4C0, 0, 1);
    pc_load_asset("assets/rom_shop1w/rom_shop1_table_tex.bin", rom_shop1_table_tex, 0x600, 0xC4F540, 0, 0);
    pc_load_asset("assets/rom_shop1w/rom_shop1_window_tex.bin", rom_shop1_window_tex, 0x800, 0xC4FB40, 0, 0);
    pc_load_asset("assets/rom_shop1w/rom_shop1_shadow_tex.bin", rom_shop1_shadow_tex, 0x400, 0xC4CF00, 0, 0);
}
#endif
