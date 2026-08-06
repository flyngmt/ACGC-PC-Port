#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_ink_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_ink_tex[]= {
#include "assets/kai_sousa_ink_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_inkmoji_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_inkmoji_tex[]= {
#include "assets/kai_sousa_inkmoji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_ink2_tex_rgb_i4[0x200];
#else
u8 kai_sousa_ink2_tex_rgb_i4[] = {
#include "assets/kai_sousa_ink2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_ink3_tex_rgb_i4[0x200];
#else
u8 kai_sousa_ink3_tex_rgb_i4[] = {
#include "assets/kai_sousa_ink3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx sousa_ink_v[0xC0 / sizeof(Vtx)];
#else
Vtx sousa_ink_v[] = {
#include "assets/sousa_ink_v.inc"
};
#endif

Gfx kai_sousa_ink_mode[] = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};

Gfx kai_sousa_ink_model[] = {
gsDPSetCycleType(G_CYC_2CYCLE),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_CLD_SURF2),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 55, 40, 105, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kai_sousa_ink2_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kai_sousa_ink3_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPDisplayList(anime_1_txt),
gsSPVertex(sousa_ink_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsSPEndDisplayList(),
};

Gfx kai_sousa_inktuboT_model[] = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 235, 235, 255),
gsDPSetEnvColor(40, 50, 50, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kai_sousa_ink_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&sousa_ink_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kai_sousa_inkmojiT_model[] = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 215, 255, 255),
gsDPSetEnvColor(70, 0, 155, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, kai_sousa_inkmoji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&sousa_ink_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

