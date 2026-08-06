#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 ef_tamaire01_r_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 ef_tamaire01_r_pal[] = {
#include "assets/ef_tamaire01_r2/ef_tamaire01_r_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_tamaire01_r_tex[0x200];
#else
u8 ef_tamaire01_r_tex[] = {
#include "assets/ef_tamaire01_r_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx ef_tamaire01_r_v[0x40 / sizeof(Vtx)];
#else
static Vtx ef_tamaire01_r_v[] = {
#include "assets/ef_tamaire01_r2/ef_tamaire01_r_v.inc"
};
#endif

Gfx ef_tamaire01_r_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_tamaire01_r_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_tamaire01_r_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_tamaire01_r_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 ef_tamaire01_w_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 ef_tamaire01_w_pal[] = {
#include "assets/ef_tamaire01_w_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_tamaire01_w_tex[0x200];
#else
u8 ef_tamaire01_w_tex[] = {
#include "assets/ef_tamaire01_w_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_tamaire01_w_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_tamaire01_w_v[] = {
#include "assets/ef_tamaire01_w_v.inc"
};
#endif

Gfx ef_tamaire01_w_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_tamaire01_w_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_tamaire01_w_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_tamaire01_w_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx ef_tama_shadow_in_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_tama_shadow_in_v[] = {
#include "assets/ef_tama_shadow_in_v.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_tama_shadow_in_0[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 ef_tama_shadow_in_0[] = {
#include "assets/ef_tama_shadow_in_0.inc"
};
#endif

Gfx ef_tamaire_shadow_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, ef_tama_shadow_in_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_tama_shadow_in_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ef_tamaire01_r2_c(void) {
    pc_load_asset("assets/ef_tamaire01_r2/ef_tamaire01_r_pal.bin", ef_tamaire01_r_pal, 0x20, 0x950500, 0, 1);
    pc_load_asset("assets/ef_tamaire01_r2/ef_tamaire01_r_v.bin", ef_tamaire01_r_v, 0x40, 0x950720, 0, 2);
}
#endif
