#include "libforest/gbi_extensions.h"

// clang-format off

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_flower_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_flower_tex[] = {
#include "assets/flower/obj_flower_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx obj_flower_leaf_v[0x40 / sizeof(Vtx)];
#else
static Vtx obj_flower_leaf_v[] = {
#include "assets/flower/obj_flower_leaf_v.inc"
};
#endif

extern Gfx obj_flower_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPLoadTextureBlock_4b_Dolphin(obj_flower_tex, G_IM_FMT_CI, 128, 32, 0, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_leafT_gfx_model[] = {
    gsSPVertex(&obj_flower_leaf_v[0], 4, 0),
    gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    0, 2, 3, // tri1
    0, 0, 0 // tri2
    ),
    gsSPEndDisplayList(),
};

// clang-format on

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_flower_obj_flower_leaf_c(void) {
    pc_load_asset("assets/flower/obj_flower_leaf_tex.bin", obj_flower_tex, 0x800, 0x3E0700, 0, 0);
    pc_load_asset("assets/flower/obj_flower_leaf_v.bin", obj_flower_leaf_v, 0x40, 0x3E0F00, 0, 2);
}
#endif
