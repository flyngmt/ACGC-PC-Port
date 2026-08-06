#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 ef_tamaire01_r_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 ef_tamaire01_r_pal[] = {
#include "assets/ef_tamaire01_r/ef_tamaire01_r_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tama01_r_tex[0x200];
#else
u8 tama01_r_tex[] = {
#include "assets/tama01_r_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx ef_tamaire01_r_v[0x40 / sizeof(Vtx)];
#else
static Vtx ef_tamaire01_r_v[] = {
#include "assets/ef_tamaire01_r/ef_tamaire01_r_v.inc"
};
#endif

Gfx tama01_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_tamaire01_r_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(ef_tamaire01_r_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tama01_w_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 tama01_w_tex[] = {
#include "assets/tama01_w_tex.inc"
};
#endif

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ef_tamaire01_r_c(void) {
    pc_load_asset("assets/ef_tamaire01_r/ef_tamaire01_r_pal.bin", ef_tamaire01_r_pal, 0x20, 0x950500, 0, 1);
    pc_load_asset("assets/ef_tamaire01_r/ef_tamaire01_r_v.bin", ef_tamaire01_r_v, 0x40, 0x950720, 0, 2);
}
#endif
