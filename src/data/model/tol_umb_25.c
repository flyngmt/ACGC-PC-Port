#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_umb_25_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_umb_25_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_umb_25_pal[] = {
#include "assets/tol_umb_25/tol_umb_25_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb_25_kasa_tex_txt[0x200];
#else
static u8 tol_umb_25_kasa_tex_txt[] = {
#include "assets/tol_umb_25/tol_umb_25_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_umb_25_ya_tex_txt[0x200];
#else
static u8 tol_umb_25_ya_tex_txt[] = {
#include "assets/tol_umb_25/tol_umb_25_ya_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_umb_25_v[0x350 / sizeof(Vtx)];
#else
Vtx tol_umb_25_v[] = {
#include "assets/tol_umb_25_v.inc"
};
#endif

Gfx kasa_umb25_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_25_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_25_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_umb_25_v, 9, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(5, 4, 6, 8, 7, 0, 2, 1, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb_25_ya_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_umb_25_v[9], 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 9, 7, 10, 8, 11),
    gsSPNTriangles_5b(10, 6, 8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_umb25_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_25_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_25_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_umb_25_v[37], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_tol_umb_25_c(void) {
    pc_load_asset("assets/tol_umb_25/tol_umb_25_pal.bin", tol_umb_25_pal, 0x20, 0x8B61A0, 0, 1);
    pc_load_asset("assets/tol_umb_25/tol_umb_25_kasa_tex_txt.bin", tol_umb_25_kasa_tex_txt, 0x200, 0x8B61C0, 0, 0);
    pc_load_asset("assets/tol_umb_25/tol_umb_25_ya_tex_txt.bin", tol_umb_25_ya_tex_txt, 0x200, 0x8B63C0, 0, 0);
}
#endif
