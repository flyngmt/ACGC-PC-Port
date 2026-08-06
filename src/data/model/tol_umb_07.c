#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_07_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_umb07_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_umb07_pal[] = {
#include "assets/tol_umb_07/tol_umb07_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb07_kasa2_tex_txt[0x100];
#else
static u8 tol_umb07_kasa2_tex_txt[] = {
#include "assets/tol_umb_07/tol_umb07_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb07_kasa1_tex_txt[0x400];
#else
static u8 tol_umb07_kasa1_tex_txt[] = {
#include "assets/tol_umb_07/tol_umb07_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb07_tuka_tex_txt[0x200];
#else
static u8 tol_umb07_tuka_tex_txt[] = {
#include "assets/tol_umb_07/tol_umb07_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_07_v[0x260 / sizeof(Vtx)];
#else
Vtx tol_umb_07_v[] = {
#include "assets/tol_umb_07_v.inc"
};
#endif

Gfx kasa_umb07_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb07_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb07_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_07_v, 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tol_umb07_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18, 6, 7, 8, 9, 10, 11, 6, 9, 12),
    gsSPNTriangles_5b(6, 8, 13, 6, 13, 9, 12, 14, 6, 6, 14, 7),
    gsSPNTriangles_5b(14, 15, 16, 8, 7, 16, 17, 10, 9, 11, 15, 14),
    gsSPNTriangles_5b(8, 18, 17, 16, 18, 8, 9, 13, 17, 14, 12, 11),
    gsSPNTriangles_5b(11, 12, 9, 17, 13, 8, 16, 7, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb07_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb07_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb07_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_07_v[19], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 2, 4, 1, 0, 5),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 8, 8, 10, 13),
    gsSPNTriangles_5b(8, 13, 14, 4, 15, 3, 2, 3, 0, 5, 6, 1),
    gsSPNTriangles_5b(14, 11, 8, 16, 17, 18, 7, 18, 6, 18, 7, 16),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_tol_umb_07_c(void) {
    pc_load_asset("assets/tol_umb_07/tol_umb07_pal.bin", tol_umb07_pal, 0x20, 0x67FD00, 0, 1);
    pc_load_asset("assets/tol_umb_07/tol_umb07_kasa2_tex_txt.bin", tol_umb07_kasa2_tex_txt, 0x100, 0x67FD20, 0, 0);
    pc_load_asset("assets/tol_umb_07/tol_umb07_kasa1_tex_txt.bin", tol_umb07_kasa1_tex_txt, 0x400, 0x67FE20, 0, 0);
    pc_load_asset("assets/tol_umb_07/tol_umb07_tuka_tex_txt.bin", tol_umb07_tuka_tex_txt, 0x200, 0x680220, 0, 0);
}
#endif
