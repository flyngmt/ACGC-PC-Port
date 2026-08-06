#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_tonosama_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_tonosama_pal[] = {
#include "assets/act_m_tonosama/act_m_tonosama_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_tonosama[0x200];
#else
static u8 act_m_tonosama[] = {
#include "assets/act_m_tonosama/act_m_tonosama.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_tonosama_v[0x120 / sizeof(Vtx)];
#else
static Vtx act_m_tonosama_v[] = {
#include "assets/act_m_tonosama/act_m_tonosama_v.inc"
};
#endif

Gfx act_m_tonosama1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_tonosama_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_tonosama),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_tonosama_v, 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_tonosama2_2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, COMBINED, 0,
                       ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 170),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_tonosama_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_tonosama),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_tonosama_v[14], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_tonosama_c(void) {
    pc_load_asset("assets/act_m_tonosama/act_m_tonosama_pal.bin", act_m_tonosama_pal, 0x20, 0x5482A0, 0, 1);
    pc_load_asset("assets/act_m_tonosama/act_m_tonosama.bin", act_m_tonosama, 0x200, 0x5482C0, 0, 0);
    pc_load_asset("assets/act_m_tonosama/act_m_tonosama_v.bin", act_m_tonosama_v, 0x120, 0x5484C0, 0, 2);
}
#endif
