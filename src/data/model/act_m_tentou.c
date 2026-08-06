#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_tentou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_tentou_pal[] = {
#include "assets/act_m_tentou/act_m_tentou_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_tentou[0x100];
#else
static u8 act_m_tentou[] = {
#include "assets/act_m_tentou/act_m_tentou.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_tentou_v[0x1D0 / sizeof(Vtx)];
#else
static Vtx act_m_tentou_v[] = {
#include "assets/act_m_tentou/act_m_tentou_v.inc"
};
#endif

Gfx act_m_tentou1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_tentou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_m_tentou),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_tentou_v, 14, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(2, 1, 7, 6, 5, 8, 9, 6, 8, 7, 1, 10),
    gsSPNTriangles_5b(9, 8, 7, 11, 9, 7, 4, 3, 12, 4, 12, 13),
    gsSPNTriangles_5b(1, 0, 4, 10, 1, 4, 11, 7, 13, 11, 13, 12),
    gsSPEndDisplayList(),
};

Gfx act_m_tentou2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_tentou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_m_tentou),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_tentou_v[14], 15, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 2, 1, 8, 9, 2, 0, 10, 3),
    gsSPNTriangles_5b(10, 11, 3, 12, 5, 4, 10, 13, 11, 13, 7, 11),
    gsSPNTriangles_5b(14, 5, 12, 13, 9, 7, 9, 8, 7, 7, 5, 14),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_tentou_c(void) {
    pc_load_asset("assets/act_m_tentou/act_m_tentou_pal.bin", act_m_tentou_pal, 0x20, 0x547EC0, 0, 1);
    pc_load_asset("assets/act_m_tentou/act_m_tentou.bin", act_m_tentou, 0x100, 0x547EE0, 0, 0);
    pc_load_asset("assets/act_m_tentou/act_m_tentou_v.bin", act_m_tentou_v, 0x1D0, 0x547FE0, 0, 2);
}
#endif
