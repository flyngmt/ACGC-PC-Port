#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_item_tane_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_item_tane_pal[] = {
#include "assets/obj_item_tane/obj_item_tane_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_item_tane_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_item_tane_tex[] = {
#include "assets/obj_item_tane/obj_item_tane_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx obj_item_tane_v[0x40 / sizeof(Vtx)];
#else
static Vtx obj_item_tane_v[] = {
#include "assets/obj_item_tane/obj_item_tane_v.inc"
};
#endif

Gfx obj_taneT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_tane_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_item_tane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_taneT_gfx_model[] = {
    gsSPVertex(obj_item_tane_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_item_tane_c(void) {
    pc_load_asset("assets/obj_item_tane/obj_item_tane_pal.bin", obj_item_tane_pal, 0x20, 0x3ECA40, 0, 1);
    pc_load_asset("assets/obj_item_tane/obj_item_tane_tex.bin", obj_item_tane_tex, 0x80, 0x3ECA60, 0, 0);
    pc_load_asset("assets/obj_item_tane/obj_item_tane_v.bin", obj_item_tane_v, 0x40, 0x3ECAE0, 0, 2);
}
#endif
