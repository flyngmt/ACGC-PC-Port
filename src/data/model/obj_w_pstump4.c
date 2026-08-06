#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_stump_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_w_palm_stump_tex[] = {
#include "assets/obj_w_pstump4/obj_w_palm_stump_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_pstump4_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_w_pstump4_v[] = {
#include "assets/obj_w_pstump4_v.inc"
};
#endif

Gfx obj_w_pstump4T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_w_palm_stump_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_pstump4T_gfx_model[] = {
    gsSPVertex(obj_w_pstump4_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 0, 2, 3, 4, 0),
    gsSPNTriangles_5b(4, 5, 0, 5, 1, 0, 3, 6, 4, 6, 5, 4),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_w_pstump4_c(void) {
    pc_load_asset("assets/obj_w_pstump4/obj_w_palm_stump_tex.bin", obj_w_palm_stump_tex, 0x400, 0x3F9760, 0, 0);
}
#endif
