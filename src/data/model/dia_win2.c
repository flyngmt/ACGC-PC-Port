#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 lat_letter01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 lat_letter01_pal[]= {
#include "assets/dia_win2/lat_letter01_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 lat_letter01_04_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 lat_letter01_04_tex[]= {
#include "assets/dia_win2/lat_letter01_04_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 lat_tegami_fusen_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 lat_tegami_fusen_tex[]= {
#include "assets/dia_win2/lat_tegami_fusen_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx dia_win2_v[0xE0 / sizeof(Vtx)];
#else
Vtx dia_win2_v[] = {
#include "assets/dia_win2_v.inc"
};
#endif

Gfx dia_win2_wT_model[] = {
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter01_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter01_04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(dia_win2_v, 10, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 1, 3, 4),
gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 9, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx dia_win2_fusenT_model[] = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 100, 100, 135, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_tegami_fusen_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&dia_win2_v[10], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_dia_win2_c(void) {
    pc_load_asset("assets/dia_win2/lat_letter01_pal.bin", lat_letter01_pal, 0x20, 0x6E7EE0, 0, 1);
    pc_load_asset("assets/dia_win2/lat_letter01_04_tex.bin", lat_letter01_04_tex, 0x80, 0x6E7F00, 0, 0);
    pc_load_asset("assets/dia_win2/lat_tegami_fusen_tex.bin", lat_tegami_fusen_tex, 0x80, 0x6E7F80, 0, 0);
}
#endif
