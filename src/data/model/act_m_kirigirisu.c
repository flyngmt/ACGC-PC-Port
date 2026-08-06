#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_kirigirisu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_kirigirisu_pal[] = {
#include "assets/act_m_kirigirisu/act_m_kirigirisu_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_kirigirisu[0x200];
#else
static u8 act_m_kirigirisu[] = {
#include "assets/act_m_kirigirisu/act_m_kirigirisu.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_kirigirisu_v[0x130 / sizeof(Vtx)];
#else
static Vtx act_m_kirigirisu_v[] = {
#include "assets/act_m_kirigirisu/act_m_kirigirisu_v.inc"
};
#endif

Gfx act_m_kirigirisu1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kirigirisu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kirigirisu),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_kirigirisu_v, 15, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 1, 5, 6, 1, 6, 4, 1, 7, 8, 9),
    gsSPNTriangles_5b(7, 9, 10, 11, 12, 13, 11, 13, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_kirigirisu2_2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, COMBINED, 0,
                       ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kirigirisu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kirigirisu),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_kirigirisu_v[15], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_kirigirisu_c(void) {
    pc_load_asset("assets/act_m_kirigirisu/act_m_kirigirisu_pal.bin", act_m_kirigirisu_pal, 0x20, 0x5436C0, 0, 1);
    pc_load_asset("assets/act_m_kirigirisu/act_m_kirigirisu.bin", act_m_kirigirisu, 0x200, 0x5436E0, 0, 0);
    pc_load_asset("assets/act_m_kirigirisu/act_m_kirigirisu_v.bin", act_m_kirigirisu_v, 0x130, 0x5438E0, 0, 2);
}
#endif
