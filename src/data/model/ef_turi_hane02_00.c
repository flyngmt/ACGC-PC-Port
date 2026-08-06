#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_turi_hane02_0_int_i4[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_turi_hane02_0_int_i4[] = {
#include "assets/ef_turi_hane02_0_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_turi_hane02_1_int_i4[0x200];
#else
u8 ef_turi_hane02_1_int_i4[] = {
#include "assets/ef_turi_hane02_1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_turi_hane02_2_int_i4[0x200];
#else
u8 ef_turi_hane02_2_int_i4[] = {
#include "assets/ef_turi_hane02_2_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_turi_hane02_3_int_i4[0x200];
#else
u8 ef_turi_hane02_3_int_i4[] = {
#include "assets/ef_turi_hane02_3_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_turi_hane02_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_turi_hane02_00_v[] = {
#include "assets/ef_turi_hane02_00_v.inc"
};
#endif

Gfx ef_turi_hane02_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, ENVIRONMENT, 0, 0,
                       0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 255, 255, 255),
    gsDPSetEnvColor(0, 50, 50, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_turi_hane02_00_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
