#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_k_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_k_pal[] = {
#include "assets/field/bg/yubin_k_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_k2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_k2_pal[] = {
#include "assets/field/bg/yubin_k2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_floor_pal[] = {
#include "assets/field/bg/yubin_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_hakari_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_hakari_pal[] = {
#include "assets/field/bg/yubin_hakari_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_wall_pal[] = {
#include "assets/field/bg/yubin_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_letter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_letter_pal[] = {
#include "assets/field/bg/yubin_letter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_us_bag_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_us_bag_pal[] = {
#include "assets/field/bg/yubin_us_bag_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 zzzyubin_tree_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 zzzyubin_tree_pal[] = {
#include "assets/field/bg/zzzyubin_tree_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_t_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_t_pal[] = {
#include "assets/field/bg/yubin_t_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 yubin_us_card_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 yubin_us_card_pal[] = {
#include "assets/field/bg/yubin_us_card_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta01_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta01_tex[] = {
#include "assets/field/bg/yuibn_kaunta01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta02_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta02_tex[] = {
#include "assets/field/bg/yuibn_kaunta02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yuibn_desk01_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 yuibn_desk01_tex[] = {
#include "assets/field/bg/yuibn_desk01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_ark01_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_ark01_tex[] = {
#include "assets/field/bg/yubin_ark01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta03_tex[] = {
#include "assets/field/bg/yuibn_kaunta03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta04_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 yuibn_kaunta04_tex[] = {
#include "assets/field/bg/yuibn_kaunta04_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_floor01_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_floor01_tex[] = {
#include "assets/field/bg/yubin_floor01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_floor02_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_floor02_tex[] = {
#include "assets/field/bg/yubin_floor02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_floor03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_floor03_tex[] = {
#include "assets/field/bg/yubin_floor03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari01_tex[] = {
#include "assets/field/bg/yubin_hakari01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari02_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari02_tex[] = {
#include "assets/field/bg/yubin_hakari02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_hakari03_tex[] = {
#include "assets/field/bg/yubin_hakari03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_wall04_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_wall04_tex[] = {
#include "assets/field/bg/yubin_wall04_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_letter01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_letter01_tex[] = {
#include "assets/field/bg/yubin_letter01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_window_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_window_tex[] = {
#include "assets/field/bg/yubin_window_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_us_bag_tex[0x480];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_us_bag_tex[] = {
#include "assets/field/bg/yubin_us_bag_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_tree2_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_tree2_tex[] = {
#include "assets/field/bg/yubin_tree2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_tree_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_tree_tex[] = {
#include "assets/field/bg/yubin_tree_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_tree3_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_tree3_tex[] = {
#include "assets/field/bg/yubin_tree3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_tree4_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_tree4_tex[] = {
#include "assets/field/bg/yubin_tree4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_step_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_step_tex[] = {
#include "assets/field/bg/yubin_step_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_akril_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_akril_tex[] = {
#include "assets/field/bg/rom_yubinkyoku_akril_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_shede_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_shede_tex[] = {
#include "assets/field/bg/rom_yubinkyoku_shede_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_us_card_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_us_card_tex[] = {
#include "assets/field/bg/yubin_us_card_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_us_mat_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_us_mat_tex[] = {
#include "assets/field/bg/yubin_us_mat_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_shadow_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yubinkyoku_shadow_tex[] = {
#include "assets/field/bg/rom_yubinkyoku_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 yubin_us_card2_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 yubin_us_card2_tex[] = {
#include "assets/field/bg/yubin_us_card2_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx grd_post_office_v[0x1700 / sizeof(Vtx)];
#else
static Vtx grd_post_office_v[] = {
#include "assets/field/bg/grd_post_office_v.inc"
};
#endif

extern Gfx grd_post_office_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 120),
    gsDPSetEnvColor(0x00, 0x64, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yubinkyoku_akril_tex, G_IM_FMT_I, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[197], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx grd_post_office_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_window_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&grd_post_office_v[217], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yuibn_kaunta04_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[225], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, zzzyubin_tree_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_tree_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[229], 20, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_tree2_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k2_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_ark01_tex, G_IM_FMT_CI, 32, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[249], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 6, 7, // tri1
                      4, 7, 5, // tri2
                      6, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 7,   // tri0
                      8, 10, 11, // tri1
                      8, 11, 9,  // tri2
                      10, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      12, 14, 15, // tri1
                      12, 15, 13, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      20, 0, 3,   // tri1
                      20, 3, 21,  // tri2
                      22, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 21, // tri0
                      24, 25, 3,  // tri1
                      24, 3, 26,  // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 30, // tri0
                      27, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_post_office_v[281], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 5, 6, // tri1
                      0, 6, 7, // tri2
                      0, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      9, 11, 12,  // tri1
                      11, 13, 14, // tri2
                      11, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      16, 18, 19, // tri1
                      17, 20, 1,  // tri2
                      17, 1, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 24, 25, // tri1
                      26, 27, 28, // tri2
                      26, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 30, 3, // tri0
                      27, 3, 31, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_post_office_v[313], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_bag_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_us_bag_tex, G_IM_FMT_CI, 48, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[317], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      7, 8, 9, // tri1
                      5, 7, 9, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_floor03_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_post_office_v[327], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_hakari_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_hakari03_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[331], 8, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_hakari02_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_letter_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_letter01_tex, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[339], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 3, // tri0
                      2, 1, 6, // tri1
                      2, 6, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_us_mat_tex, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[346], 22, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_card_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_us_card_tex, G_IM_FMT_CI, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          4, 5, 6, // tri0
                          5, 7, 6, // tri1
                          8, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(8, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      15, 16, 13, // tri2
                      17, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 17, 13, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_t_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_step_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[0], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_wall04_tex, G_IM_FMT_CI, 32, 48, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[6], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          1, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 2, // tri0
                      3, 6, 5, // tri1
                      7, 4, 8, // tri2
                      4, 0, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 11, // tri0
                      9, 11, 17,  // tri1
                      15, 16, 17, // tri2
                      18, 4, 7    // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 7, // tri0
                      14, 13, 6, // tri1
                      3, 14, 6,  // tri2
                      20, 21, 22 // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      20, 22, 24, // tri1
                      20, 24, 25, // tri2
                      20, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 25, // tri0
                      28, 29, 30, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_post_office_v[38], 32, 0),
    gsSPNTrianglesInit_5b(34,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      8, 5, 9,  // tri2
                      5, 7, 9   // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 9,  // tri0
                      5, 11, 6,  // tri1
                      11, 12, 6, // tri2
                      5, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 11, // tri0
                      14, 15, 16, // tri1
                      17, 14, 16, // tri2
                      16, 15, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 18, // tri0
                      19, 12, 20, // tri1
                      17, 19, 20, // tri2
                      13, 17, 20  // tri3
                      ),
    gsSPNTriangles_5b(13, 20, 12, // tri0
                      17, 21, 19, // tri1
                      17, 22, 21, // tri2
                      17, 18, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 3, 2,   // tri0
                      23, 2, 24,  // tri1
                      23, 24, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 23, 27, // tri0
                      23, 25, 27, // tri1
                      25, 28, 27, // tri2
                      23, 29, 3   // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 3,  // tri0
                      23, 31, 29, // tri1
                      31, 30, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_floor01_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_post_office_v[70], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6, // tri0
                      5, 7, 2, // tri1
                      4, 6, 8, // tri2
                      9, 4, 10 // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 10,   // tri0
                      11, 12, 13, // tri1
                      3, 14, 15,  // tri2
                      16, 3, 0    // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 20, 18, // tri1
                      20, 21, 18, // tri2
                      21, 22, 18  // tri3
                      ),
    gsSPNTriangles_5b(23, 20, 17, // tri0
                      21, 20, 24, // tri1
                      25, 17, 19, // tri2
                      26, 25, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 17, 25, // tri0
                      26, 23, 17, // tri1
                      21, 28, 22, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 31, // tri0
                      30, 21, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_floor02_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_post_office_v[102], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      4, 8, 7, // tri1
                      9, 0, 2, // tri2
                      9, 8, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 8,  // tri0
                      9, 11, 10, // tri1
                      12, 8, 10, // tri2
                      13, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 14, // tri0
                      11, 15, 10, // tri1
                      13, 14, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 18, // tri0
                      21, 22, 23, // tri1
                      22, 19, 23, // tri2
                      19, 18, 23  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 22, // tri0
                      21, 25, 24, // tri1
                      21, 26, 25, // tri2
                      27, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_post_office_v[133], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yuibn_kaunta03_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_post_office_v[136], 28, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(yuibn_desk01_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(yuibn_kaunta02_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(yuibn_kaunta01_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, zzzyubin_tree_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_tree4_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_post_office_v[164], 14, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_tree3_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6,        // tri count
                          6, 7, 8,  // tri0
                          6, 8, 9,  // tri1
                          7, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(7, 11, 8,   // tri0
                      10, 12, 13, // tri1
                      10, 13, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_hakari_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_hakari01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[178], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 5, // tri0
                      6, 3, 2, // tri1
                      6, 2, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_card_pal),
    gsDPLoadTextureBlock_4b_Dolphin(yubin_us_card2_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[185], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&grd_post_office_v[189], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 120, 10, 0, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yubinkyoku_shadow_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[201], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yubinkyoku_shede_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_post_office_v[209], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_grd_post_office_grd_post_office_c(void) {
    pc_load_asset("assets/field/bg/yubin_k_pal.bin", yubin_k_pal, 0x20, 0x8ED9E0, 0, 1);
    pc_load_asset("assets/field/bg/yubin_k2_pal.bin", yubin_k2_pal, 0x20, 0x8EDA00, 0, 1);
    pc_load_asset("assets/field/bg/yubin_floor_pal.bin", yubin_floor_pal, 0x20, 0x8EDA20, 0, 1);
    pc_load_asset("assets/field/bg/yubin_hakari_pal.bin", yubin_hakari_pal, 0x20, 0x8EDA40, 0, 1);
    pc_load_asset("assets/field/bg/yubin_wall_pal.bin", yubin_wall_pal, 0x20, 0x8EDA60, 0, 1);
    pc_load_asset("assets/field/bg/yubin_letter_pal.bin", yubin_letter_pal, 0x20, 0x8EDA80, 0, 1);
    pc_load_asset("assets/field/bg/yubin_us_bag_pal.bin", yubin_us_bag_pal, 0x20, 0x8EDAA0, 0, 1);
    pc_load_asset("assets/field/bg/zzzyubin_tree_pal.bin", zzzyubin_tree_pal, 0x20, 0x8EDAC0, 0, 1);
    pc_load_asset("assets/field/bg/yubin_t_pal.bin", yubin_t_pal, 0x20, 0x8EDAE0, 0, 1);
    pc_load_asset("assets/field/bg/yubin_us_card_pal.bin", yubin_us_card_pal, 0x20, 0x8EDB00, 0, 1);
    pc_load_asset("assets/field/bg/yuibn_kaunta01_tex.bin", yuibn_kaunta01_tex, 0x200, 0x8EDB20, 0, 0);
    pc_load_asset("assets/field/bg/yuibn_kaunta02_tex.bin", yuibn_kaunta02_tex, 0x200, 0x8EDD20, 0, 0);
    pc_load_asset("assets/field/bg/yuibn_desk01_tex.bin", yuibn_desk01_tex, 0x200, 0x8EDF20, 0, 0);
    pc_load_asset("assets/field/bg/yubin_ark01_tex.bin", yubin_ark01_tex, 0x400, 0x8EE120, 0, 0);
    pc_load_asset("assets/field/bg/yuibn_kaunta03_tex.bin", yuibn_kaunta03_tex, 0x100, 0x8EE520, 0, 0);
    pc_load_asset("assets/field/bg/yuibn_kaunta04_tex.bin", yuibn_kaunta04_tex, 0x200, 0x8EE620, 0, 0);
    pc_load_asset("assets/field/bg/yubin_floor01_tex.bin", yubin_floor01_tex, 0x800, 0x8EE820, 0, 0);
    pc_load_asset("assets/field/bg/yubin_floor02_tex.bin", yubin_floor02_tex, 0x800, 0x8EF020, 0, 0);
    pc_load_asset("assets/field/bg/yubin_floor03_tex.bin", yubin_floor03_tex, 0x100, 0x8EF820, 0, 0);
    pc_load_asset("assets/field/bg/yubin_hakari01_tex.bin", yubin_hakari01_tex, 0x100, 0x8EF920, 0, 0);
    pc_load_asset("assets/field/bg/yubin_hakari02_tex.bin", yubin_hakari02_tex, 0x80, 0x8EFA20, 0, 0);
    pc_load_asset("assets/field/bg/yubin_hakari03_tex.bin", yubin_hakari03_tex, 0x100, 0x8EFAA0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_wall04_tex.bin", yubin_wall04_tex, 0x300, 0x8EFBA0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_letter01_tex.bin", yubin_letter01_tex, 0x100, 0x8EFEA0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_window_tex.bin", yubin_window_tex, 0x80, 0x8EFFA0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_us_bag_tex.bin", yubin_us_bag_tex, 0x480, 0x8F0020, 0, 0);
    pc_load_asset("assets/field/bg/yubin_tree2_tex.bin", yubin_tree2_tex, 0x300, 0x8F04A0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_tree_tex.bin", yubin_tree_tex, 0x100, 0x8F07A0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_tree3_tex.bin", yubin_tree3_tex, 0x80, 0x8F08A0, 0, 0);
    pc_load_asset("assets/field/bg/yubin_tree4_tex.bin", yubin_tree4_tex, 0x80, 0x8F0920, 0, 0);
    pc_load_asset("assets/field/bg/yubin_step_tex.bin", yubin_step_tex, 0x100, 0x8F09A0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yubinkyoku_akril_tex.bin", rom_yubinkyoku_akril_tex, 0x80, 0x8F0AA0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yubinkyoku_shede_tex.bin", rom_yubinkyoku_shede_tex, 0x100, 0x8F0B20, 0, 0);
    pc_load_asset("assets/field/bg/yubin_us_card_tex.bin", yubin_us_card_tex, 0x400, 0x8F0C20, 0, 0);
    pc_load_asset("assets/field/bg/yubin_us_mat_tex.bin", yubin_us_mat_tex, 0x300, 0x8F1020, 0, 0);
    pc_load_asset("assets/field/bg/rom_yubinkyoku_shadow_tex.bin", rom_yubinkyoku_shadow_tex, 0x100, 0x8F1320, 0, 0);
    pc_load_asset("assets/field/bg/yubin_us_card2_tex.bin", yubin_us_card2_tex, 0x100, 0x8F1420, 0, 0);
    pc_load_asset("assets/field/bg/grd_post_office_v.bin", grd_post_office_v, 0x1700, 0x8F1520, 0, 2);
}
#endif
