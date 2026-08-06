#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_s_palm_young_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_s_palm_young_tex[] = {
#include "assets/obj_s_palm2/obj_s_palm_young_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_palm2_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_s_palm2_v[] = {
#include "assets/obj_s_palm2_v.inc"
};
#endif

Gfx obj_s_palm2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_palm2T_gfx_model[] = {
    gsSPVertex(obj_s_palm2_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 2, 1, 0, 6, 3, 6, 4, 3),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_palm2_c(void) {
    pc_load_asset("assets/obj_s_palm2/obj_s_palm_young_tex.bin", obj_s_palm_young_tex, 0x800, 0x3E4AA0, 0, 0);
}
#endif
