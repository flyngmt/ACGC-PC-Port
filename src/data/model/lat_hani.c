#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 lat_fusen_TXT[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 lat_fusen_TXT[] = {
#include "assets/lat_hani/lat_fusen_TXT.inc"
};
#endif

#ifdef TARGET_PC
Vtx lat_hani_v[0x40 / sizeof(Vtx)];
#else
Vtx lat_hani_v[] = {
#include "assets/lat_hani_v.inc"
};
#endif

Gfx lat_hani_senT_model[] = {
    gsDPSetPrimColor(0, 255, 0, 0, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_fusen_TXT),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(lat_hani_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_lat_hani_c(void) {
    pc_load_asset("assets/lat_hani/lat_fusen_TXT.bin", lat_fusen_TXT, 0x80, 0x69DAC0, 0, 0);
}
#endif
