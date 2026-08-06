#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_sightmap_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_sightmap_pal[] = {
#include "assets/obj_s_sightmap/obj_sightmap_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_sightmap_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_sightmap_tex[] = {
#include "assets/obj_s_sightmap_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_sightmap_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_s_sightmap_v[] = {
#include "assets/obj_s_sightmap_v.inc"
};
#endif

Gfx obj_s_sightmapT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_sightmap_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_sightmap_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_sightmapT_gfx_model[] = {
    gsSPVertex(obj_s_sightmap_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_sightmap_c(void) {
    pc_load_asset("assets/obj_s_sightmap/obj_sightmap_pal.bin", obj_sightmap_pal, 0x20, 0x3EA840, 0, 1);
}
#endif
