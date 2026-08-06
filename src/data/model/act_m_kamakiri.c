#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_m_kamakiri_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_m_kamakiri_pal[] = {
#include "assets/act_m_kamakiri/act_m_kamakiri_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 act_m_kamakiri[0x200];
#else
static u8 act_m_kamakiri[] = {
#include "assets/act_m_kamakiri/act_m_kamakiri.inc"
};
#endif

#ifdef TARGET_PC
static Vtx act_m_kamakiri_v[0x120 / sizeof(Vtx)];
#else
static Vtx act_m_kamakiri_v[] = {
#include "assets/act_m_kamakiri/act_m_kamakiri_v.inc"
};
#endif

Gfx act_m_kamakiri1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kamakiri_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kamakiri),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_kamakiri_v, 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 1, 3, 5, 4),
    gsSPNTriangles_5b(1, 6, 7, 1, 8, 6, 9, 4, 5, 9, 1, 4),
    gsSPNTriangles_5b(10, 11, 1, 12, 13, 1, 13, 8, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_kamakiri2_2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, COMBINED, 0,
                       ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_kamakiri_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_m_kamakiri),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_kamakiri_v[14], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_m_kamakiri_c(void) {
    pc_load_asset("assets/act_m_kamakiri/act_m_kamakiri_pal.bin", act_m_kamakiri_pal, 0x20, 0x5429A0, 0, 1);
    pc_load_asset("assets/act_m_kamakiri/act_m_kamakiri.bin", act_m_kamakiri, 0x200, 0x5429C0, 0, 0);
    pc_load_asset("assets/act_m_kamakiri/act_m_kamakiri_v.bin", act_m_kamakiri_v, 0x120, 0x542BC0, 0, 2);
}
#endif
