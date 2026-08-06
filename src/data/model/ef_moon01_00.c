#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

ATTRIBUTE_ALIGN(32) EVW_ANIME_SCROLL ef_moon01_00_evw_anime_2[] = { { 0, 0, 64, 64 }, { 1, -1, 32, 32 } };

EVW_ANIME_DATA ef_moon01_00_evw_anime[] = { { -1, EVW_ANIME_TYPE_SCROLL2, ef_moon01_00_evw_anime_2 } };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_moon01_0_int_i4[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 ef_moon01_0_int_i4[] = {
#include "assets/ef_moon01_0_int_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 ef_moon01_1_int_i4[0x200];
#else
static u8 ef_moon01_1_int_i4[] = {
#include "assets/ef_moon01_00/ef_moon01_1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_moon01_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_moon01_00_v[] = {
#include "assets/ef_moon01_00_v.inc"
};
#endif

Gfx ef_moon01_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, TEXEL1, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0,
                       0, 0, COMBINED),
    gsDPSetEnvColor(0, 255, 200, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, ef_moon01_0_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_moon01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 4, 3),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_moon01_00_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ef_moon01_00_c(void) {
    pc_load_asset("assets/ef_moon01_00/ef_moon01_1_int_i4.bin", ef_moon01_1_int_i4, 0x200, 0x94A900, 0, 0);
}
#endif
