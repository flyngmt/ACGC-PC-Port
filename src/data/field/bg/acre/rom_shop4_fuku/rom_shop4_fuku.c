#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_floor_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_base_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_base_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_base_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_stair_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_stair_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_stair_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_table_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_table_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_table_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_wall_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_wall_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_wall_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign01_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign01_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_sign01_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_kaunta_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_kaunta_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_kaunta_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_2_sign01_us_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_2_sign01_us_tex_pal[] = {
#include "assets/field/bg/rom_shop4_2_sign01_us_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign02_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign02_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_us_sign02_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign0_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign0_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_us_sign0_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign03_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign03_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_sign03_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_reji_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_reji_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_reji_tex_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop_kouhaku_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop_kouhaku_pal[] = {
#include "assets/field/bg/rom_shop_kouhaku_pal2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor01_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor01_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_base_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_base_tex[] = {
#include "assets/field/bg/rom_shop4_1_base_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_stair01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_stair01_tex[] = {
#include "assets/field/bg/rom_shop4_1_stair01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table01_tex[] = {
#include "assets/field/bg/rom_shop4_1_table01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table02_tex[] = {
#include "assets/field/bg/rom_shop4_1_table02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall01_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall01_tex[] = {
#include "assets/field/bg/rom_shop4_1_wall01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall02_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall02_tex[] = {
#include "assets/field/bg/rom_shop4_1_wall02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign05_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign05_tex[] = {
#include "assets/field/bg/rom_shop4_1_sign05_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta01_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta01_tex[] = {
#include "assets/field/bg/rom_shop4_1_kaunta01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta02_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta02_tex[] = {
#include "assets/field/bg/rom_shop4_1_kaunta02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_2_us_sign01_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_2_us_sign01_tex[] = {
#include "assets/field/bg/rom_shop4_2_us_sign01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign02_tex[] = {
#include "assets/field/bg/rom_shop4_1_us_sign02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign0_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign0_tex[] = {
#include "assets/field/bg/rom_shop4_1_us_sign0_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign04_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign04_tex[] = {
#include "assets/field/bg/rom_shop4_1_sign04_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji01_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji01_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji01_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji02_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji03_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji03_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor02_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor02_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor03_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor03_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor03_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor04_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor04_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor04_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow02_tex[] = {
#include "assets/field/bg/rom_shop4_1_shadow02_tex2.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop_kouhaku_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop_kouhaku_tex[] = {
#include "assets/field/bg/rom_shop_kouhaku_tex2.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_shop4_fuku_v[0x1720 / sizeof(Vtx)];
#else
static Vtx rom_shop4_fuku_v[] = {
#include "assets/field/bg/rom_shop4_fuku_v.inc"
};
#endif

extern Gfx rom_shop4_fuku_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 140, 50, 0, 40, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_shadow02_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_fuku_v[346], 24, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
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
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx rom_shop4_fuku_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_sign01_us_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_2_us_sign01_tex, G_IM_FMT_CI, 32, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_fuku_v[278], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign0_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_us_sign0_tex, G_IM_FMT_CI, 48, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[282], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign03_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_sign04_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[286], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_kaunta01_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[290], 6, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop_kouhaku_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop_kouhaku_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[296], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          3, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 4,  // tri0
                      6, 7, 8,  // tri1
                      6, 8, 9,  // tri2
                      7, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 8,   // tri0
                      10, 12, 13, // tri1
                      10, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 14, // tri0
                      15, 16, 14, // tri1
                      16, 17, 14, // tri2
                      9, 18, 6    // tri3
                      ),
    gsSPNTriangles_5b(9, 19, 18,  // tri0
                      19, 20, 18, // tri1
                      19, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      24, 25, 26, // tri1
                      24, 27, 25, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 25, // tri0
                      28, 30, 31, // tri1
                      28, 31, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_shop4_fuku_v[328], 14, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      9, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      11, 10, 12, // tri1
                      11, 12, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji03_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[342], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_base_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_base_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[0], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 2, // tri0
                      6, 0, 2, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_stair_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_stair01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[7], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 3, // tri0
                      1, 6, 5, // tri1
                      5, 7, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_floor_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor01_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[15], 23, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          3, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 1,   // tri0
                      6, 7, 8,   // tri1
                      7, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      15, 14, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      20, 19, 22, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor02_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[38], 25, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      9, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 11, // tri0
                      15, 16, 17, // tri1
                      18, 15, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      24, 22, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor03_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[63], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      5, 11, 10, // tri2
                      9, 5, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      13, 15, 14, // tri1
                      13, 16, 15, // tri2
                      15, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(12, 18, 19, // tri0
                      20, 21, 22, // tri1
                      20, 22, 23, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor04_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[87], 26, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,    // tri0
                      8, 7, 9,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 14, // tri0
                      16, 17, 11, // tri1
                      18, 19, 20, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      23, 24, 21, // tri1
                      22, 25, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_wall_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_wall01_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[113], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      5, 8, 6,   // tri1
                      5, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      14, 15, 12, // tri1
                      16, 17, 14, // tri2
                      16, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      19, 21, 20, // tri1
                      18, 22, 19, // tri2
                      18, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(18, 25, 23, // tri0
                      26, 27, 28, // tri1
                      27, 29, 28, // tri2
                      29, 30, 28  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_shop4_fuku_v[145], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      5, 9, 7, // tri2
                      9, 0, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 10, 9, // tri0
                      10, 0, 9, // tri1
                      10, 3, 0, // tri2
                      11, 12, 8 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 8, // tri0
                      13, 4, 8,  // tri1
                      4, 6, 8,   // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      17, 18, 16, // tri1
                      18, 19, 16, // tri2
                      15, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 17, // tri0
                      21, 22, 18, // tri1
                      23, 24, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 28, // tri0
                      30, 31, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_shop4_fuku_v[177], 13, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 5, // tri0
                      4, 3, 5, // tri1
                      5, 6, 7, // tri2
                      4, 5, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 4, 7,  // tri0
                      2, 1, 9,  // tri1
                      2, 9, 10, // tri2
                      11, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 5, // tri0
                      10, 12, 5, // tri1
                      2, 10, 5,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_wall02_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[190], 16, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 5, // tri0
                      6, 7, 4, // tri1
                      6, 4, 5, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 11,  // tri0
                      10, 12, 13, // tri1
                      10, 13, 11, // tri2
                      13, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_table_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_table01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[206], 12, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_table02_tex, G_IM_FMT_CI, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[218], 20, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
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
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign01_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_sign05_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[238], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji01_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[242], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji02_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[252], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_kaunta02_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[258], 16, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
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
                      5, 12, 15,  // tri1
                      5, 15, 6,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign02_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_us_sign02_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_fuku_v[274], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_shop4_fuku_rom_shop4_fuku_c(void) {
    pc_load_asset("assets/field/bg/rom_shop4_1_floor_tex_pal2.bin", rom_shop4_1_floor_tex_pal, 0x20, 0xC36240, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_base_tex_pal2.bin", rom_shop4_1_base_tex_pal, 0x20, 0xC36260, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_stair_tex_pal2.bin", rom_shop4_1_stair_tex_pal, 0x20, 0xC36280, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_table_tex_pal2.bin", rom_shop4_1_table_tex_pal, 0x20, 0xC362A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall_tex_pal2.bin", rom_shop4_1_wall_tex_pal, 0x20, 0xC362C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign01_tex_pal2.bin", rom_shop4_1_sign01_tex_pal, 0x20, 0xC362E0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta_tex_pal2.bin", rom_shop4_1_kaunta_tex_pal, 0x20, 0xC36300, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_2_sign01_us_tex_pal.bin", rom_shop4_2_sign01_us_tex_pal, 0x20, 0xC36320, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign02_tex_pal2.bin", rom_shop4_1_us_sign02_tex_pal, 0x20, 0xC36340, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign0_tex_pal.bin", rom_shop4_1_us_sign0_tex_pal, 0x20, 0xC36360, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign03_tex_pal2.bin", rom_shop4_1_sign03_tex_pal, 0x20, 0xC36380, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji_tex_pal2.bin", rom_shop4_1_reji_tex_pal, 0x20, 0xC363A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop_kouhaku_pal2.bin", rom_shop_kouhaku_pal, 0x20, 0xC363C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor01_tex2.bin", rom_shop4_1_floor01_tex, 0x800, 0xC363E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_base_tex2.bin", rom_shop4_1_base_tex, 0x200, 0xC36BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_stair01_tex2.bin", rom_shop4_1_stair01_tex, 0x100, 0xC36DE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_table01_tex2.bin", rom_shop4_1_table01_tex, 0x100, 0xC36EE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_table02_tex2.bin", rom_shop4_1_table02_tex, 0x100, 0xC36FE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall01_tex2.bin", rom_shop4_1_wall01_tex, 0x800, 0xC370E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall02_tex2.bin", rom_shop4_1_wall02_tex, 0x200, 0xC378E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign05_tex2.bin", rom_shop4_1_sign05_tex, 0x80, 0xC37AE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta01_tex2.bin", rom_shop4_1_kaunta01_tex, 0x200, 0xC37B60, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta02_tex2.bin", rom_shop4_1_kaunta02_tex, 0x80, 0xC37D60, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_2_us_sign01_tex.bin", rom_shop4_2_us_sign01_tex, 0x400, 0xC37DE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign02_tex2.bin", rom_shop4_1_us_sign02_tex, 0x100, 0xC381E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign0_tex.bin", rom_shop4_1_us_sign0_tex, 0x600, 0xC382E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign04_tex2.bin", rom_shop4_1_sign04_tex, 0x100, 0xC388E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji01_tex2.bin", rom_shop4_1_reji01_tex, 0x300, 0xC389E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji02_tex2.bin", rom_shop4_1_reji02_tex, 0x100, 0xC38CE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji03_tex2.bin", rom_shop4_1_reji03_tex, 0x100, 0xC38DE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor02_tex2.bin", rom_shop4_1_floor02_tex, 0x800, 0xC38EE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor03_tex2.bin", rom_shop4_1_floor03_tex, 0x800, 0xC396E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor04_tex2.bin", rom_shop4_1_floor04_tex, 0x800, 0xC39EE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_shadow02_tex2.bin", rom_shop4_1_shadow02_tex, 0x100, 0xC3A6E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop_kouhaku_tex2.bin", rom_shop_kouhaku_tex, 0x800, 0xC3A7E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_fuku_v.bin", rom_shop4_fuku_v, 0x1720, 0xC3AFE0, 0, 2);
}
#endif
