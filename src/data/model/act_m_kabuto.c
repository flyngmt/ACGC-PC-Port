#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_kabuto_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_kabuto_pal[] = {
#include "assets/act_m_kabuto/act_m_kabuto_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_kabuto[0x200];
#else
static u8 act_m_kabuto[] = {
#include "assets/act_m_kabuto/act_m_kabuto.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_kabuto_v[0xE0 / sizeof(Vtx)];
#else
static Vtx act_m_kabuto_v[] = {
#include "assets/act_m_kabuto/act_m_kabuto_v.inc"
};
#endif

Gfx act_m_kabuto1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kabuto_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kabuto),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_kabuto_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 6, 4, 6, 1, 6, 2, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_kabuto2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kabuto_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kabuto),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_kabuto_v[7], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(5, 3, 4, 5, 6, 0, 5, 0, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_kabuto_c(void) {
    pc_load_asset("assets/act_m_kabuto/act_m_kabuto_pal.bin", act_m_kabuto_pal, 0x20, 0x5425E0, 0, 1);
    pc_load_asset("assets/act_m_kabuto/act_m_kabuto.bin", act_m_kabuto, 0x200, 0x542600, 0, 0);
    pc_load_asset("assets/act_m_kabuto/act_m_kabuto_v.bin", act_m_kabuto_v, 0xE0, 0x542800, 0, 2);
}
#endif
