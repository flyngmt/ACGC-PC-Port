#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_museum4_v[];
extern u8 cliff_tex_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_tex_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 bush_pal_dummy[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum4_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum4_wall_pal[] = {
#include "assets/rom_museum4/rom_museum4_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rom_museum4_floor_pal[0x20 / sizeof(u16)];
#else
u16 rom_museum4_floor_pal[] = {
#include "assets/rom_museum4_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_museum4_step_pal2[0x20];
#else
u8 rom_museum4_step_pal2[] = {
#include "assets/rom_museum4_step_pal2.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_museum4_wallB_tex[0x400];
#else
u8 rom_museum4_wallB_tex[] = {
#include "assets/rom_museum4_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_museum4_step_tex[0x800];
#else
u8 rom_museum4_step_tex[] = {
#include "assets/rom_museum4_step_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_museum4_wallA_tex[0x200];
#else
static u8 rom_museum4_wallA_tex[] = {
#include "assets/rom_museum4/rom_museum4_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_museum4_floorA_tex[0x800];
#else
u8 rom_museum4_floorA_tex[] = {
#include "assets/rom_museum4_floorA_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_museum4_v[0x1510 / sizeof(Vtx)];
#else
Vtx rom_museum4_v[] = {
#include "assets/rom_museum4_v.inc"
};
#endif

Gfx rom_museum4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_wall_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_museum4_wallB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_museum4_v[309], 28, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 6, 9, 8, 10, 11, 1),
    gsSPNTriangles_5b(12, 13, 11, 13, 1, 11, 13, 3, 1, 14, 15, 3),
    gsSPNTriangles_5b(14, 13, 16, 13, 14, 3, 3, 15, 17, 3, 17, 4),
    gsSPNTriangles_5b(13, 12, 18, 13, 18, 16, 19, 20, 21, 20, 22, 21),
    gsSPNTriangles_5b(9, 23, 8, 23, 24, 8, 8, 25, 21, 19, 21, 25),
    gsSPNTriangles_5b(8, 24, 25, 7, 8, 21, 26, 7, 21, 26, 21, 22),
    gsSPNTriangles_5b(7, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_step_pal2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum4_step_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(rom_museum4_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 1, 4, 2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_museum4_v[5], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_wall_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum4_wallA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_v[13], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 10, 12, 10, 9, 12),
    gsSPNTriangles_5b(13, 12, 9, 13, 11, 12, 9, 8, 14, 8, 15, 14),
    gsSPNTriangles_5b(16, 14, 15, 16, 9, 14, 10, 11, 17, 18, 10, 17),
    gsSPNTriangles_5b(19, 15, 8, 20, 10, 18, 10, 20, 8, 21, 8, 20),
    gsSPNTriangles_5b(21, 19, 8, 0, 22, 23, 22, 24, 23, 0, 2, 22),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 7, 27, 6, 7, 28, 29, 30),
    gsSPVertex(&rom_museum4_v[44], 7, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, river_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_v[51], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 2, 4, 5, 4, 6),
    gsSPNTriangles_5b(7, 6, 8, 9, 7, 8, 9, 8, 10, 11, 10, 12),
    gsSPNTriangles_5b(13, 12, 14, 15, 14, 16, 17, 16, 18, 19, 17, 18),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_floor_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum4_floorA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_v[71], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 8, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(17, 14, 18, 17, 15, 14, 17, 19, 15, 6, 20, 21),
    gsSPNTriangles_5b(22, 23, 24, 25, 22, 24, 1, 26, 27, 28, 0, 2),
    gsSPNTriangles_5b(1, 29, 3, 30, 10, 5, 12, 5, 10, 9, 14, 16),
    gsSPNTriangles_5b(9, 31, 14, 31, 9, 20, 9, 21, 20, 31, 18, 14),
    gsSPNTriangles_5b(22, 25, 31, 26, 8, 27, 26, 13, 8, 8, 10, 30),
    gsSPNTriangles_5b(13, 11, 10, 0, 28, 13, 15, 7, 16, 0, 0, 0),
    gsSPVertex(&rom_museum4_v[103], 15, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 1, 0, 3, 1, 6, 7, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(12, 13, 2, 14, 2, 4, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, cliff_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_v[118], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 9, 7, 10, 11, 12, 10, 13, 11, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 14, 18, 14, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 20, 23, 24, 20, 24, 25, 26, 2, 27),
    gsSPNTriangles_5b(2, 1, 27, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_v[149], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 13, 17, 18, 19, 17, 18, 17, 3),
    gsSPNTriangles_5b(19, 16, 17, 20, 21, 22, 11, 23, 5, 23, 6, 5),
    gsSPNTriangles_5b(23, 24, 6, 10, 9, 4, 10, 4, 25, 9, 5, 4),
    gsSPNTriangles_5b(13, 26, 22, 26, 20, 22, 13, 16, 26, 6, 24, 27),
    gsSPNTriangles_5b(14, 21, 15, 15, 21, 10, 15, 10, 25, 6, 27, 7),
    gsSPNTriangles_5b(11, 5, 9, 28, 29, 30, 29, 31, 30, 0, 0, 0),
    gsSPVertex(&rom_museum4_v[181], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 7, 8, 9, 2, 4, 10),
    gsSPNTriangles_5b(2, 10, 11, 12, 8, 2, 12, 2, 11, 9, 8, 12),
    gsSPNTriangles_5b(4, 6, 10, 13, 14, 15, 16, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 20, 19, 16, 24, 17, 25, 26, 27),
    gsSPNTriangles_5b(26, 28, 27, 25, 29, 26, 15, 14, 30, 21, 15, 30),
    gsSPNTriangles_5b(21, 30, 22, 13, 31, 14, 31, 16, 14, 31, 24, 16),
    gsSPNTriangles_5b(28, 20, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_museum4_v[213], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(5, 4, 6, 5, 6, 7, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 16, 17, 18, 17, 2, 18),
    gsSPNTriangles_5b(1, 4, 5, 19, 20, 21, 20, 10, 21, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, earth_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_v[235], 11, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 4, 1, 5, 6),
    gsSPNTriangles_5b(5, 7, 8, 9, 3, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, grass_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum4_v[246], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 1, 0, 4),
    gsSPNTriangles_5b(0, 5, 4, 5, 6, 4, 0, 7, 5, 0, 8, 7),
    gsSPNTriangles_5b(9, 10, 11, 10, 12, 11, 13, 2, 3, 2, 13, 12),
    gsSPNTriangles_5b(13, 14, 12, 14, 11, 12, 7, 15, 5, 5, 16, 6),
    gsSPNTriangles_5b(5, 17, 16, 17, 18, 16, 17, 11, 18, 14, 19, 11),
    gsSPNTriangles_5b(19, 18, 11, 20, 21, 22, 21, 23, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 27, 28, 26, 10, 29, 12, 0, 0, 0),
    gsSPVertex(&rom_museum4_v[276], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 9, 11, 13, 12, 13, 14, 12, 15, 16, 14),
    gsSPNTriangles_5b(11, 17, 18, 19, 20, 18, 10, 21, 8, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, bush_b_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum4_v[298], 11, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 4, 6, 7),
    gsSPNTriangles_5b(1, 8, 9, 8, 3, 10, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_museum4_c(void) {
    pc_load_asset("assets/rom_museum4/rom_museum4_wall_pal.bin", rom_museum4_wall_pal, 0x20, 0xBB3960, 0, 1);
    pc_load_asset("assets/rom_museum4/rom_museum4_wallA_tex.bin", rom_museum4_wallA_tex, 0x200, 0xBB3980, 0, 0);
}
#endif
