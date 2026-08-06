#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop4_2w_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[] = {
#include "assets/rom_shop4_2w/rom_shop4_1_floor_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop4_2_stair_tex_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop4_2_stair_tex_pal[] = {
#include "assets/rom_shop4_2_stair_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop4_1_table_tex_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop4_1_table_tex_pal[] = {
#include "assets/rom_shop4_2w/rom_shop4_1_table_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop4_2_wall_tex_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop4_2_wall_tex_pal[] = {
#include "assets/rom_shop4_2_wall_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop4_2_sign01_tex_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop4_2_sign01_tex_pal[] = {
#include "assets/rom_shop4_2_sign01_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop4_2_sign01_us_tex_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop4_2_sign01_us_tex_pal[] = {
#include "assets/rom_shop4_2w/rom_shop4_2_sign01_us_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_shop4_2_space_tex_pal[0x20 / sizeof(u16)];
#else
u16 rom_shop4_2_space_tex_pal[] = {
#include "assets/rom_shop4_2_space_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_floor01_tex[0x800];
#else
u8 rom_shop4_2_floor01_tex[] = {
#include "assets/rom_shop4_2_floor01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_stair01_tex[0x100];
#else
u8 rom_shop4_2_stair01_tex[] = {
#include "assets/rom_shop4_2_stair01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_table01_tex[0x100];
#else
u8 rom_shop4_2_table01_tex[] = {
#include "assets/rom_shop4_2_table01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_table02_tex[0x100];
#else
u8 rom_shop4_2_table02_tex[] = {
#include "assets/rom_shop4_2_table02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_wall01_tex[0x800];
#else
u8 rom_shop4_2_wall01_tex[] = {
#include "assets/rom_shop4_2_wall01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_sign05_tex[0x80];
#else
u8 rom_shop4_2_sign05_tex[] = {
#include "assets/rom_shop4_2_sign05_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop4_2_us_sign01_tex[0x400];
#else
static u8 rom_shop4_2_us_sign01_tex[] = {
#include "assets/rom_shop4_2w/rom_shop4_2_us_sign01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_space_tex[0x400];
#else
u8 rom_shop4_2_space_tex[] = {
#include "assets/rom_shop4_2_space_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_wall02_tex[0x800];
#else
u8 rom_shop4_2_wall02_tex[] = {
#include "assets/rom_shop4_2_wall02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_floor02_tex[0x800];
#else
u8 rom_shop4_2_floor02_tex[] = {
#include "assets/rom_shop4_2_floor02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_floor03_tex[0x800];
#else
u8 rom_shop4_2_floor03_tex[] = {
#include "assets/rom_shop4_2_floor03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_floor04_tex[0x800];
#else
u8 rom_shop4_2_floor04_tex[] = {
#include "assets/rom_shop4_2_floor04_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop4_2_shadow02_tex[0x100];
#else
u8 rom_shop4_2_shadow02_tex[] = {
#include "assets/rom_shop4_2_shadow02_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop4_2w_v[0xE20 / sizeof(Vtx)];
#else
Vtx rom_shop4_2w_v[] = {
#include "assets/rom_shop4_2w_v.inc"
};
#endif

Gfx rom_shop4_2w_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 120, 20, 0, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, rom_shop4_2_shadow02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop4_2w_v[218], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_shop4_2w_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_sign01_us_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_shop4_2_us_sign01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop4_2w_v[214], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_stair_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_2_stair01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop4_2w_v, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(1, 5, 3, 1, 6, 5, 5, 7, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_floor_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_floor01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[8], 23, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 7, 10, 9, 0, 7, 0, 2, 7, 2, 8, 7),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 15, 17, 16, 17, 18, 16),
    gsSPNTriangles_5b(19, 5, 20, 5, 21, 20, 5, 22, 21, 5, 19, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_floor02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[31], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(3, 5, 7, 4, 8, 5, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(13, 9, 14, 15, 16, 17, 15, 18, 16, 19, 17, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_floor03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[51], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 1, 7),
    gsSPNTriangles_5b(1, 8, 7, 8, 9, 7, 3, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(3, 5, 14, 13, 3, 14, 6, 2, 1, 7, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 18, 20, 19, 17, 19, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_floor04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[73], 21, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 9, 8, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 14, 12, 15, 17, 18, 12, 19, 20, 3),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_space_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_shop4_2_space_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[94], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(2, 5, 0, 4, 6, 3, 1, 7, 4, 5, 8, 0),
    gsSPNTriangles_5b(9, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_wall_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_wall01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[104], 26, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 8, 12, 9),
    gsSPNTriangles_5b(13, 5, 4, 13, 14, 5, 15, 16, 17, 16, 18, 17),
    gsSPNTriangles_5b(18, 19, 17, 16, 20, 18, 20, 21, 18, 16, 22, 20),
    gsSPNTriangles_5b(22, 21, 20, 22, 23, 21, 24, 15, 19, 15, 17, 19),
    gsSPNTriangles_5b(12, 25, 11, 12, 11, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_2_wall02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[130], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 12, 13, 11, 13, 9),
    gsSPNTriangles_5b(11, 9, 8, 14, 15, 16, 15, 17, 16, 14, 18, 15),
    gsSPNTriangles_5b(14, 19, 18, 17, 20, 16, 20, 21, 16, 20, 22, 21),
    gsSPNTriangles_5b(22, 23, 21, 24, 25, 26, 24, 27, 25, 7, 28, 29),
    gsSPNTriangles_5b(28, 26, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[160], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[164], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 7, 6, 8, 9, 10, 8, 10, 7, 8),
    gsSPNTriangles_5b(8, 11, 9, 8, 12, 11, 1, 13, 14, 13, 15, 14),
    gsSPNTriangles_5b(13, 16, 15, 16, 17, 15, 1, 14, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[182], 16, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 0, 2, 4, 2, 1),
    gsSPNTriangles_5b(5, 4, 1, 0, 5, 1, 5, 6, 4, 5, 7, 6),
    gsSPNTriangles_5b(8, 9, 10, 11, 9, 8, 11, 12, 9, 12, 10, 9),
    gsSPNTriangles_5b(13, 8, 10, 14, 8, 13, 15, 14, 13, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_table_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop4_2_table02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[198], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_2_table01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[206], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_sign01_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop4_2_sign05_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_2w_v[210], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop4_2w_c(void) {
    pc_load_asset("assets/rom_shop4_2w/rom_shop4_1_floor_tex_pal.bin", rom_shop4_1_floor_tex_pal, 0x20, 0xC3CC60, 0, 1);
    pc_load_asset("assets/rom_shop4_2w/rom_shop4_1_table_tex_pal.bin", rom_shop4_1_table_tex_pal, 0x20, 0xC3CCA0, 0, 1);
    pc_load_asset("assets/rom_shop4_2w/rom_shop4_2_sign01_us_tex_pal.bin", rom_shop4_2_sign01_us_tex_pal, 0x20, 0xC3CD00, 0, 1);
    pc_load_asset("assets/rom_shop4_2w/rom_shop4_2_us_sign01_tex.bin", rom_shop4_2_us_sign01_tex, 0x400, 0xC3E0C0, 0, 0);
}
#endif
