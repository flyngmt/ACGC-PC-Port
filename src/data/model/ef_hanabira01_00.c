#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_hanabira01_0[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 ef_hanabira01_0[] = {
#include "assets/ef_hanabira01_0.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_hanabira01_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_hanabira01_00_v[] = {
#include "assets/ef_hanabira01_00_v.inc"
};
#endif

Gfx ef_hanabira01_00_setmode[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, SHADE, PRIM_LOD_FRAC, SHADE, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                       ENVIRONMENT, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 60, 250, 200, 230, 180),
    gsDPSetEnvColor(150, 0, 150, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, ef_hanabira01_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx ef_hanabira01_00_modelT[] = {
    gsSPVertex(ef_hanabira01_00_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
