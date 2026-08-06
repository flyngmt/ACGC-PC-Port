#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_otikomi_us1_int_i4[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 ef_otikomi_us1_int_i4[] = {
#include "assets/ef_otikomi_us1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_otikomi_us2_int_i4[0x80];
#else
u8 ef_otikomi_us2_int_i4[] = {
#include "assets/ef_otikomi_us2_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_otikomi_us2_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_otikomi_us2_v[] = {
#include "assets/ef_otikomi_us2_v.inc"
};
#endif

Gfx ef_otikomi_us2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                       ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_otikomi_us2_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, ef_otikomi_us1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_otikomi_us2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
