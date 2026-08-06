#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 kai_sousa_button3_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 kai_sousa_button3_tex[] = {
#include "assets/pas_start/kai_sousa_button3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx pas_start_v[0xB0 / sizeof(Vtx)];
#else
Vtx pas_start_v[] = {
#include "assets/pas_start_v.inc"
};
#endif

Gfx pas_start_yaji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetPrimColor(0, 255, 205, 0, 0, 255),
    gsSPVertex(pas_start_v, 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPEndDisplayList(),
};

Gfx pas_start_buttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 235, 235, 235, 255),
    gsDPSetEnvColor(70, 70, 70, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kai_sousa_button3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pas_start_v[7], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_start_model[] = {
    gsSPDisplayList(pas_start_yaji_model),
    gsSPDisplayList(pas_start_buttonT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_pas_start_c(void) {
    pc_load_asset("assets/pas_start/kai_sousa_button3_tex.bin", kai_sousa_button3_tex, 0x100, 0x7B14C0, 0, 0);
}
#endif
