#include "bootdata.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 gam_win_moji1_tex[0x280];
ATTRIBUTE_ALIGN(32) u8 gam_win_moji2_tex[0x500];
ATTRIBUTE_ALIGN(32) u8 yes[0x100];
ATTRIBUTE_ALIGN(32) u8 no[0x80];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku1_tex[0x400];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku2_tex[0x400];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku3_tex[0x400];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku4_tex[0x400];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku5_tex[0x400];
ATTRIBUTE_ALIGN(32) static u8 att_win_waku6_tex[0x80];
#else
#include "assets/bootdata/win1/gam_win_moji1_tex.inc"
#include "assets/bootdata/win1/gam_win_moji2_tex.inc"
#include "assets/bootdata/win1/yes.inc"
#include "assets/bootdata/win1/no.inc"
#include "assets/bootdata/win1/att_win_waku1_tex.inc"
#include "assets/bootdata/win1/att_win_waku2_tex.inc"
#include "assets/bootdata/win1/att_win_waku3_tex.inc"
#include "assets/bootdata/win1/att_win_waku4_tex.inc"
#include "assets/bootdata/win1/att_win_waku5_tex.inc"
#include "assets/bootdata/win1/att_win_waku6_tex.inc"
#endif

#ifdef TARGET_PC
static Vtx gam_win1_v[0x3F0 / sizeof(Vtx)];
#else
static Vtx gam_win1_v[] = {
#include "assets/bootdata/win1/gam_win1_v.inc"
};
#endif

Gfx gam_win1_cursor_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 145, 40, 40, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win1_v[0], 3, 0),
  gsSPNTrianglesInit_5b(
    1, // tri count
    0, 1, 2, // tri0
    0, 0, 0, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win1_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 50, 50, 60, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji2_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win1_v[3], 8, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji1_tex, G_IM_FMT_I, 80, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win1_moji2_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 90, 90, 155, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(yes, G_IM_FMT_I, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win1_v[11], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win1_moji3_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 90, 90, 155, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(no, G_IM_FMT_I, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win1_v[15], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win1_winT_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 225, 255, 255, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win1_v[19], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    7, 4, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    9, 11, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    23, 20, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win1_v[47], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_static_bootdata_gam_win1_c(void) {
    pc_load_asset("assets/bootdata/win1/gam_win1_v.bin", gam_win1_v, 0x3F0, 0xB7EC0, 1, 2);
    pc_load_asset("assets/bootdata/win1/gam_win_moji1_tex.bin", gam_win_moji1_tex, 0x280, 0xB6140, 1, 0);
    pc_load_asset("assets/bootdata/win1/gam_win_moji2_tex.bin", gam_win_moji2_tex, 0x500, 0xB63C0, 1, 0);
    pc_load_asset("assets/bootdata/win1/yes.bin", yes, 0x100, 0xB68C0, 1, 0);
    pc_load_asset("assets/bootdata/win1/no.bin", no, 0x80, 0xB69C0, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku1_tex.bin", att_win_waku1_tex, 0x400, 0xB6A40, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku2_tex.bin", att_win_waku2_tex, 0x400, 0xB6E40, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku3_tex.bin", att_win_waku3_tex, 0x400, 0xB7240, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku4_tex.bin", att_win_waku4_tex, 0x400, 0xB7640, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku5_tex.bin", att_win_waku5_tex, 0x400, 0xB7A40, 1, 0);
    pc_load_asset("assets/bootdata/win1/att_win_waku6_tex.bin", att_win_waku6_tex, 0x80, 0xB7E40, 1, 0);
}
#endif
