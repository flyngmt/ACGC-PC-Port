#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_koorogi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_koorogi_pal[] = {
#include "assets/act_m_koorogi/act_m_koorogi_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_koorogi[0x180];
#else
static u8 act_m_koorogi[] = {
#include "assets/act_m_koorogi/act_m_koorogi.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_koorogi_v[0xA0 / sizeof(Vtx)];
#else
static Vtx act_m_koorogi_v[] = {
#include "assets/act_m_koorogi/act_m_koorogi_v.inc"
};
#endif

Gfx act_m_koorogi1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_koorogi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, act_m_koorogi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_koorogi_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_koorogi_c(void) {
    pc_load_asset("assets/act_m_koorogi/act_m_koorogi_pal.bin", act_m_koorogi_pal, 0x20, 0x543AE0, 0, 1);
    pc_load_asset("assets/act_m_koorogi/act_m_koorogi.bin", act_m_koorogi, 0x180, 0x543B00, 0, 0);
    pc_load_asset("assets/act_m_koorogi/act_m_koorogi_v.bin", act_m_koorogi_v, 0xA0, 0x543C80, 0, 2);
}
#endif
