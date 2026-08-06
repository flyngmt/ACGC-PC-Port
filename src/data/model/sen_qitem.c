#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sen_qitem_kage_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 sen_qitem_kage_tex[] = {
#include "assets/sen_qitem_kage_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_win_yaji2_tex[0x100];
#else
static u8 sen_win_yaji2_tex[] = {
#include "assets/sen_qitem/sen_win_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_qitem_waku_tex[0x800];
#else
u8 sen_qitem_waku_tex[] = {
#include "assets/sen_qitem_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_itemw_yaji2_tex[0x100];
#else
static u8 sen_itemw_yaji2_tex[] = {
#include "assets/sen_qitem/sen_itemw_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_qitem_yajirushi[0x80];
#else
u8 sen_qitem_yajirushi[] = {
#include "assets/sen_qitem_yajirushi.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_qitem_yajirushi2[0x100];
#else
u8 sen_qitem_yajirushi2[] = {
#include "assets/sen_qitem_yajirushi2.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_itemw_yaji_tex[0x80];
#else
static u8 sen_itemw_yaji_tex[] = {
#include "assets/sen_qitem/sen_itemw_yaji_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_item2_yaji_tex[0x80];
#else
static u8 sen_item2_yaji_tex[] = {
#include "assets/sen_qitem/sen_item2_yaji_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx sen_qitem_v[0x200 / sizeof(Vtx)];
#else
Vtx sen_qitem_v[] = {
#include "assets/sen_qitem_v.inc"
};
#endif

Gfx sen_qitem_kage_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 30, 20, 20, 160),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, sen_qitem_kage_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(sen_qitem_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi3_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 210, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_itemw_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi5_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_qitem_yajirushi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[8], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_wakuT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 245, 140, 255),
    gsDPSetEnvColor(215, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, sen_qitem_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[12], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushiT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_item2_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[16], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi2T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_win_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[20], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi4T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_itemw_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[24], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi6T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_qitem_yajirushi2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[28], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_sen_qitem_c(void) {
    pc_load_asset("assets/sen_qitem/sen_win_yaji2_tex.bin", sen_win_yaji2_tex, 0x100, 0x7BA0C0, 0, 0);
    pc_load_asset("assets/sen_qitem/sen_itemw_yaji2_tex.bin", sen_itemw_yaji2_tex, 0x100, 0x7BA9C0, 0, 0);
    pc_load_asset("assets/sen_qitem/sen_itemw_yaji_tex.bin", sen_itemw_yaji_tex, 0x80, 0x7BAC40, 0, 0);
    pc_load_asset("assets/sen_qitem/sen_item2_yaji_tex.bin", sen_item2_yaji_tex, 0x80, 0x7BACC0, 0, 0);
}
#endif
