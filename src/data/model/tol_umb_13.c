#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_13_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_umb13_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_umb13_pal[] = {
#include "assets/tol_umb_13/tol_umb13_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb13_kasa1_tex_txt[0x200];
#else
static u8 tol_umb13_kasa1_tex_txt[] = {
#include "assets/tol_umb_13/tol_umb13_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb13_kasa2_tex_txt[0x40];
#else
static u8 tol_umb13_kasa2_tex_txt[] = {
#include "assets/tol_umb_13/tol_umb13_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb13_tuka_tex_txt[0x200];
#else
static u8 tol_umb13_tuka_tex_txt[] = {
#include "assets/tol_umb_13/tol_umb13_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_13_v[0x390 / sizeof(Vtx)];
#else
Vtx tol_umb_13_v[] = {
#include "assets/tol_umb_13_v.inc"
};
#endif

Gfx kasa_umb13_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb13_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb13_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_13_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb13_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb13_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb13_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_13_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb13_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_tol_umb_13_c(void) {
    pc_load_asset("assets/tol_umb_13/tol_umb13_pal.bin", tol_umb13_pal, 0x20, 0x6835E0, 0, 1);
    pc_load_asset("assets/tol_umb_13/tol_umb13_kasa1_tex_txt.bin", tol_umb13_kasa1_tex_txt, 0x200, 0x683600, 0, 0);
    pc_load_asset("assets/tol_umb_13/tol_umb13_kasa2_tex_txt.bin", tol_umb13_kasa2_tex_txt, 0x40, 0x683800, 0, 0);
    pc_load_asset("assets/tol_umb_13/tol_umb13_tuka_tex_txt.bin", tol_umb13_tuka_tex_txt, 0x200, 0x683840, 0, 0);
}
#endif
