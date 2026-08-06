#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum4_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum4_wall_pal[] = {
#include "assets/rom_museum4_wall/rom_museum4_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_museum4_wallA_tex[0x200];
#else
static u8 rom_museum4_wallA_tex[] = {
#include "assets/rom_museum4_wall/rom_museum4_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_museum4_wall_v[0x70 / sizeof(Vtx)];
#else
Vtx rom_museum4_wall_v[] = {
#include "assets/rom_museum4_wall_v.inc"
};
#endif

Gfx rom_museum4_wall_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_wall_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum4_wallA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(rom_museum4_wall_v, 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 2, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 2, 3, 4, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_museum4_wall_c(void) {
    pc_load_asset("assets/rom_museum4_wall/rom_museum4_wall_pal.bin", rom_museum4_wall_pal, 0x20, 0xBB3960, 0, 1);
    pc_load_asset("assets/rom_museum4_wall/rom_museum4_wallA_tex.bin", rom_museum4_wallA_tex, 0x200, 0xBB3980, 0, 0);
}
#endif
