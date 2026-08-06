#include "bootdata.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 gam_win_moji3_tex[0x500];
ATTRIBUTE_ALIGN(32) u8 gam_win_moji5_tex[0x380];
#else
#include "assets/bootdata/win3/gam_win_moji3_tex.inc"
#include "assets/bootdata/win3/gam_win_moji5_tex.inc"
#endif

#ifdef TARGET_PC
static Vtx gam_win3_v[0x340 / sizeof(Vtx)];
#else
static Vtx gam_win3_v[] = {
#include "assets/bootdata/win3/gam_win3_v.inc"
};
#endif

Gfx gam_win3_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 50, 50, 60, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji5_tex, G_IM_FMT_I, 112, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win3_v[0], 8, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji3_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_static_bootdata_gam_win3_c(void) {
    pc_load_asset("assets/bootdata/win3/gam_win3_v.bin", gam_win3_v, 0x340, 0xBB0A0, 1, 2);
    pc_load_asset("assets/bootdata/win3/gam_win_moji3_tex.bin", gam_win_moji3_tex, 0x500, 0xBA820, 1, 0);
    pc_load_asset("assets/bootdata/win3/gam_win_moji5_tex.bin", gam_win_moji5_tex, 0x380, 0xBAD20, 1, 0);
}
#endif
