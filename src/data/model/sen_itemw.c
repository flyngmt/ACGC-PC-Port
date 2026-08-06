#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 san_itemw_waku_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 san_itemw_waku_tex[] = {
#include "assets/san_itemw_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_itemw_kage_tex[0x400];
#else
u8 sen_itemw_kage_tex[] = {
#include "assets/sen_itemw_kage_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_itemw_yaji_tex[0x80];
#else
static u8 sen_itemw_yaji_tex[] = {
#include "assets/sen_itemw/sen_itemw_yaji_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_itemw_yaji2_tex[0x100];
#else
static u8 sen_itemw_yaji2_tex[] = {
#include "assets/sen_itemw/sen_itemw_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx sen_itemw_v[0x100 / sizeof(Vtx)];
#else
Vtx sen_itemw_v[] = {
#include "assets/sen_itemw_v.inc"
};
#endif

Gfx sen_item2_DL_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx sen_itemw_kage_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 30, 20, 20, 160),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, sen_itemw_kage_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(sen_itemw_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_itemw_yajirushi_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_itemw_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_itemw_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_itemw_wakuT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, san_itemw_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_itemw_v[8], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_itemw_yajirushi2T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_itemw_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_itemw_v[12], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_sen_itemw_c(void) {
    pc_load_asset("assets/sen_itemw/sen_itemw_yaji_tex.bin", sen_itemw_yaji_tex, 0x80, 0x7B9920, 0, 0);
    pc_load_asset("assets/sen_itemw/sen_itemw_yaji2_tex.bin", sen_itemw_yaji2_tex, 0x100, 0x7B99A0, 0, 0);
}
#endif
