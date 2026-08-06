#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_sao_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_sao_1_pal[] = {
#include "assets/tol_uki_12/tol_sao_1_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_sao_1_uki1_tex_txt[0x100];
#else
static u8 tol_sao_1_uki1_tex_txt[] = {
#include "assets/tol_uki_12/tol_sao_1_uki1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static Vtx tol_uki_1_v[0x180 / sizeof(Vtx)];
#else
static Vtx tol_uki_1_v[] = {
#include "assets/tol_uki_12/tol_uki_1_v.inc"
};
#endif

Gfx tol_uki1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_sao_1_uki1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_uki_1_v, 24, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 4, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 7, 6, 9, 7, 9, 10, 10, 9, 11),
    gsSPNTriangles_5b(12, 6, 8, 6, 12, 13, 6, 13, 9, 9, 13, 11),
    gsSPNTriangles_5b(14, 12, 8, 12, 14, 15, 12, 15, 13, 13, 15, 11),
    gsSPNTriangles_5b(16, 14, 8, 14, 16, 17, 14, 17, 15, 15, 17, 11),
    gsSPNTriangles_5b(18, 16, 19, 16, 18, 20, 16, 20, 17, 17, 20, 21),
    gsSPNTriangles_5b(22, 18, 19, 18, 22, 23, 18, 23, 20, 20, 23, 21),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
extern void pc_assets_pal_n64_to_gc(u16*, int);
void _pc_load_src_data_model_tol_uki_12_c(void) {
    pc_load_asset("assets/tol_uki_12/tol_sao_1_pal.bin", tol_sao_1_pal, 0x20, 0x721410, 0, 1);
    /* Palette ROM offset shared with tol_uki_1.c (N64 TLUT path = RGBA5551).
     * This model uses gsDPLoadTLUT_Dolphin which expects RGB5A3. */
    pc_assets_pal_n64_to_gc(tol_sao_1_pal, 16);
    pc_load_asset("assets/tol_uki_12/tol_sao_1_uki1_tex_txt.bin", tol_sao_1_uki1_tex_txt, 0x100, 0x721430, 0, 0);
    pc_load_asset("assets/tol_uki_12/tol_uki_1_v.bin", tol_uki_1_v, 0x180, 0x721530, 0, 2);
}
#endif
