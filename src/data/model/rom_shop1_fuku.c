#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop1_fuku_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop1_pal[] = {
#include "assets/rom_shop1_fuku/rom_shop1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop1_w_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop1_w_pal[] = {
#include "assets/rom_shop1_w_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop1_f_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop1_f_pal[] = {
#include "assets/rom_shop1_f_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop_kouhaku_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop_kouhaku_pal[] = {
#include "assets/rom_shop1_fuku/rom_shop_kouhaku_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_table_tex[0x600];
#else
static u8 rom_shop1_table_tex[] = {
#include "assets/rom_shop1_fuku/rom_shop1_table_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_window_tex[0x800];
#else
static u8 rom_shop1_window_tex[] = {
#include "assets/rom_shop1_fuku/rom_shop1_window_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop1_shadow_tex[0x400];
#else
static u8 rom_shop1_shadow_tex[] = {
#include "assets/rom_shop1_fuku/rom_shop1_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_w1_tex[0x800];
#else
u8 rom_shop1_w1_tex[] = {
#include "assets/rom_shop1_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_w2_tex[0x800];
#else
u8 rom_shop1_w2_tex[] = {
#include "assets/rom_shop1_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_f1_tex[0x800];
#else
u8 rom_shop1_f1_tex[] = {
#include "assets/rom_shop1_f1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_f2_tex[0x800];
#else
u8 rom_shop1_f2_tex[] = {
#include "assets/rom_shop1_f2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_f3_tex[0x800];
#else
u8 rom_shop1_f3_tex[] = {
#include "assets/rom_shop1_f3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop1_f4_tex[0x800];
#else
u8 rom_shop1_f4_tex[] = {
#include "assets/rom_shop1_f4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop_kouhaku_tex[0x800];
#else
static u8 rom_shop_kouhaku_tex[] = {
#include "assets/rom_shop1_fuku/rom_shop_kouhaku_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop1_fuku_v[0xE90 / sizeof(Vtx)];
#else
Vtx rom_shop1_fuku_v[] = {
#include "assets/rom_shop1_fuku_v.inc"
};
#endif

Gfx rom_shop1_fuku_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, rom_shop1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 240, 220, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop1_fuku_v[174], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, rom_shop1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[178], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_shop1_fuku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 48, rom_shop1_table_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop1_fuku_v[157], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[161], 13, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(12, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop_kouhaku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop_kouhaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[182], 32, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 0, 6, 1, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 0, 9, 7, 11, 8, 10, 6, 0, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 15, 16, 13, 15, 17, 16, 15, 18, 17),
    gsSPNTriangles_5b(19, 12, 20, 12, 14, 20, 21, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(21, 23, 27, 26, 21, 27, 24, 26, 27, 28, 29, 30),
    gsSPVertex(&rom_shop1_fuku_v[213], 20, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(5, 4, 3, 6, 7, 8, 7, 9, 8, 9, 10, 8),
    gsSPNTriangles_5b(9, 11, 10, 6, 12, 7, 13, 14, 15, 14, 16, 15),
    gsSPNTriangles_5b(16, 17, 15, 13, 18, 14, 16, 19, 17, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop1_w_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop1_fuku_v, 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 0, 10, 0, 2, 10, 2, 11, 10, 12, 13, 6),
    gsSPNTriangles_5b(12, 14, 13, 14, 15, 13, 15, 6, 13, 15, 16, 6),
    gsSPNTriangles_5b(0, 17, 1, 17, 5, 1, 0, 3, 17, 3, 5, 17),
    gsSPNTriangles_5b(8, 6, 16, 18, 19, 20, 21, 20, 19, 11, 21, 22),
    gsSPNTriangles_5b(21, 19, 22, 9, 22, 19, 9, 11, 22, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 24, 23, 25, 24, 26, 24, 25, 26, 19, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[27], 31, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 3, 2, 1, 2, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 7, 5, 15, 5, 16, 15),
    gsSPNTriangles_5b(15, 17, 10, 18, 1, 6, 1, 0, 6, 8, 10, 17),
    gsSPNTriangles_5b(19, 12, 3, 12, 4, 3, 15, 16, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 27, 24, 26, 20, 11, 9),
    gsSPNTriangles_5b(21, 20, 9, 28, 29, 26, 30, 22, 21, 22, 30, 24),
    gsSPNTriangles_5b(25, 24, 30, 25, 28, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop1_f_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[58], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[70], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(7, 6, 5, 0, 8, 1, 9, 10, 11, 12, 13, 11),
    gsSPNTriangles_5b(10, 12, 11, 0, 14, 8, 15, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[90], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 3, 0, 4),
    gsSPNTriangles_5b(0, 5, 4, 6, 7, 8, 6, 9, 7, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(19, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[118], 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 8, 6, 9, 7, 6, 10, 9),
    gsSPNTriangles_5b(6, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 13, 16, 17, 18, 19),
    gsSPNTriangles_5b(20, 18, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop1_f4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop1_fuku_v[140], 9, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(5, 1, 6, 0, 2, 7, 2, 3, 8, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_shop1_fuku_v[149], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop1_fuku_c(void) {
    pc_load_asset("assets/rom_shop1_fuku/rom_shop1_pal.bin", rom_shop1_pal, 0x20, 0xC4F4C0, 0, 1);
    pc_load_asset("assets/rom_shop1_fuku/rom_shop_kouhaku_pal.bin", rom_shop_kouhaku_pal, 0x20, 0xC4F520, 0, 1);
    pc_load_asset("assets/rom_shop1_fuku/rom_shop1_table_tex.bin", rom_shop1_table_tex, 0x600, 0xC4F540, 0, 0);
    pc_load_asset("assets/rom_shop1_fuku/rom_shop1_window_tex.bin", rom_shop1_window_tex, 0x800, 0xC4FB40, 0, 0);
    pc_load_asset("assets/rom_shop1_fuku/rom_shop1_shadow_tex.bin", rom_shop1_shadow_tex, 0x400, 0xC50340, 0, 0);
    pc_load_asset("assets/rom_shop1_fuku/rom_shop_kouhaku_tex.bin", rom_shop_kouhaku_tex, 0x800, 0xC53740, 0, 0);
}
#endif
