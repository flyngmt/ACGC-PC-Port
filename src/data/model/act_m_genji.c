#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_m_genji_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_m_genji_pal[] = {
#include "assets/act_m_genji_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_m_genji[0x100];
#else
u8 act_m_genji[] = {
#include "assets/act_m_genji.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_m_genji_v[0x60 / sizeof(Vtx)];
#else
Vtx act_m_genji_v[] = {
#include "assets/act_m_genji_v.inc"
};
#endif

Gfx act_m_mu_genji_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_genji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_m_genji),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_m_genji_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
