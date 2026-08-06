#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[] = {
#include "assets/rom_myhome1_wall/rom_myhome_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_myhome_window_tex[0x200];
#else
static u8 rom_myhome_window_tex[] = {
#include "assets/rom_myhome1_wall/rom_myhome_window_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_myhome_enter2_tex[0x800];
#else
static u8 rom_myhome_enter2_tex[] = {
#include "assets/rom_myhome1_wall/rom_myhome_enter2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_myhome1_wall_v[0x550 / sizeof(Vtx)];
#else
Vtx rom_myhome1_wall_v[] = {
#include "assets/rom_myhome1_wall_v.inc"
};
#endif

Gfx rom_myhome1_wall_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome1_wall_v[77], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome1_wall_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 4, 0),
    gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[6], 23, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 13, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 16, 20, 16, 18, 20, 18, 21, 20),
    gsSPNTriangles_5b(16, 22, 17, 22, 5, 17, 16, 3, 22, 3, 5, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[29], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 1, 1, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(11, 13, 7, 5, 7, 13, 11, 12, 13, 14, 4, 3),
    gsSPNTriangles_5b(14, 3, 15, 14, 15, 16, 2, 17, 18, 2, 18, 19),
    gsSPNTriangles_5b(2, 19, 0, 20, 4, 14, 21, 20, 14, 10, 9, 17),
    gsSPNTriangles_5b(2, 10, 17, 22, 23, 24, 23, 25, 24, 8, 6, 26),
    gsSPNTriangles_5b(6, 27, 26, 22, 24, 28, 22, 28, 29, 22, 29, 30),
    gsSPNTriangles_5b(26, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[61], 8, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(1, 6, 4, 5, 4, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome1_wall_v[69], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome1_wall_new_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome1_wall_v[77], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome1_wall_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 4, 0),
    gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[6], 23, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 13, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 16, 20, 16, 18, 20, 18, 21, 20),
    gsSPNTriangles_5b(16, 22, 17, 22, 5, 17, 16, 3, 22, 3, 5, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[29], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 1, 1, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(11, 13, 7, 5, 7, 13, 11, 12, 13, 14, 4, 3),
    gsSPNTriangles_5b(14, 3, 15, 14, 15, 16, 2, 17, 18, 2, 18, 19),
    gsSPNTriangles_5b(2, 19, 0, 20, 4, 14, 21, 20, 14, 10, 9, 17),
    gsSPNTriangles_5b(2, 10, 17, 22, 23, 24, 23, 25, 24, 8, 6, 26),
    gsSPNTriangles_5b(6, 27, 26, 22, 24, 28, 22, 28, 29, 22, 29, 30),
    gsSPNTriangles_5b(26, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[61], 8, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(1, 6, 4, 5, 4, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome1_wall_v[69], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome1_wall_new2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome1_wall_v[77], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome1_wall_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 4, 0),
    gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 16, 124, 140),
    gsSPVertex(&rom_myhome1_wall_v[6], 23, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 13, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 16, 20, 16, 18, 20, 18, 21, 20),
    gsSPNTriangles_5b(16, 22, 17, 22, 5, 17, 16, 3, 22, 3, 5, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 16, 124, 140),
    gsSPVertex(&rom_myhome1_wall_v[29], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 1, 1, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(11, 13, 7, 5, 7, 13, 11, 12, 13, 14, 4, 3),
    gsSPNTriangles_5b(14, 3, 15, 14, 15, 16, 2, 17, 18, 2, 18, 19),
    gsSPNTriangles_5b(2, 19, 0, 20, 4, 14, 21, 20, 14, 10, 9, 17),
    gsSPNTriangles_5b(2, 10, 17, 22, 23, 24, 23, 25, 24, 8, 6, 26),
    gsSPNTriangles_5b(6, 27, 26, 22, 24, 28, 22, 28, 29, 22, 29, 30),
    gsSPNTriangles_5b(26, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome1_wall_v[61], 8, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(1, 6, 4, 5, 4, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome1_wall_v[69], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_myhome1_wall_c(void) {
    pc_load_asset("assets/rom_myhome1_wall/rom_myhome_pal.bin", rom_myhome_pal, 0x20, 0x594E40, 0, 1);
    pc_load_asset("assets/rom_myhome1_wall/rom_myhome_window_tex.bin", rom_myhome_window_tex, 0x200, 0x594E60, 0, 0);
    pc_load_asset("assets/rom_myhome1_wall/rom_myhome_enter2_tex.bin", rom_myhome_enter2_tex, 0x800, 0x595060, 0, 0);
}
#endif
