#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_notice_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_notice_pal[] = {
#include "assets/obj_s_notice/obj_notice_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_notice_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_notice_tex[] = {
#include "assets/obj_s_notice_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_notice_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_s_notice_v[] = {
#include "assets/obj_s_notice_v.inc"
};
#endif

Gfx obj_s_noticeT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_notice_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_notice_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_noticeT_gfx_model[] = {
    gsSPVertex(obj_s_notice_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_notice_c(void) {
    pc_load_asset("assets/obj_s_notice/obj_notice_pal.bin", obj_notice_pal, 0x20, 0x3E30C0, 0, 1);
}
#endif
