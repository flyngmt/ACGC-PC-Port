#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_s_palm_young_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_s_palm_young_tex[] = {
#include "assets/obj_s_pstump3/obj_s_palm_young_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_pstump3_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_s_pstump3_v[] = {
#include "assets/obj_s_pstump3_v.inc"
};
#endif

Gfx obj_s_pstump3T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_pstump3T_gfx_model[] = {
    gsSPVertex(obj_s_pstump3_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 1, 3, 1, 4, 3),
    gsSPNTriangles_5b(0, 5, 1, 5, 4, 1, 4, 6, 3, 4, 5, 6),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_pstump3_c(void) {
    pc_load_asset("assets/obj_s_pstump3/obj_s_palm_young_tex.bin", obj_s_palm_young_tex, 0x800, 0x3E9600, 0, 0);
}
#endif
