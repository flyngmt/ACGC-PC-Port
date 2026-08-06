#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ef_ase01_0[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 ef_ase01_0[] = {
#include "assets/ef_ase01_00/ef_ase01_0.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_ase01_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_ase01_00_v[] = {
#include "assets/ef_ase01_00_v.inc"
};
#endif

Gfx ef_ase01_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 0, 255, 255, 155),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, ef_ase01_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_ase01_00_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ef_ase01_00_c(void) {
    pc_load_asset("assets/ef_ase01_00/ef_ase01_0.bin", ef_ase01_0, 0x100, 0x93D2E0, 0, 0);
}
#endif
