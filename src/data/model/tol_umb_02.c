#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_umb02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_umb02_pal[] = {
#include "assets/tol_umb_02/tol_umb02_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb02_kasa2_tex_txt[0x200];
#else
static u8 tol_umb02_kasa2_tex_txt[] = {
#include "assets/tol_umb_02/tol_umb02_kasa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb02_kasa1_tex_txt[0x200];
#else
static u8 tol_umb02_kasa1_tex_txt[] = {
#include "assets/tol_umb_02/tol_umb02_kasa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb02_tuka_tex_txt[0x200];
#else
static u8 tol_umb02_tuka_tex_txt[] = {
#include "assets/tol_umb_02/tol_umb02_tuka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_02_v[0x3E0 / sizeof(Vtx)];
#else
Vtx tol_umb_02_v[] = {
#include "assets/tol_umb_02_v.inc"
};
#endif

Gfx kasa_umb02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb02_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_02_v, 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 0, 9, 10, 11, 12, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb02_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_umb_02_v[13], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb02_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_02_v[43], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 2, 4, 1, 0, 5),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 8, 8, 10, 13),
    gsSPNTriangles_5b(8, 13, 14, 4, 15, 3, 2, 3, 0, 5, 6, 1),
    gsSPNTriangles_5b(14, 11, 8, 16, 17, 18, 7, 18, 6, 18, 7, 16),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_tol_umb_02_c(void) {
    pc_load_asset("assets/tol_umb_02/tol_umb02_pal.bin", tol_umb02_pal, 0x20, 0x67CC00, 0, 1);
    pc_load_asset("assets/tol_umb_02/tol_umb02_kasa2_tex_txt.bin", tol_umb02_kasa2_tex_txt, 0x200, 0x67CC20, 0, 0);
    pc_load_asset("assets/tol_umb_02/tol_umb02_kasa1_tex_txt.bin", tol_umb02_kasa1_tex_txt, 0x200, 0x67CE20, 0, 0);
    pc_load_asset("assets/tol_umb_02/tol_umb02_tuka_tex_txt.bin", tol_umb02_tuka_tex_txt, 0x200, 0x67D020, 0, 0);
}
#endif
