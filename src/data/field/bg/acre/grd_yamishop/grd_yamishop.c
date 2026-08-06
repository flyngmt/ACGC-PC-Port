#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_wall_pal[] = {
#include "assets/field/bg/rom_yami_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_floor_pal[] = {
#include "assets/field/bg/rom_yami_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_box_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_box_pal[] = {
#include "assets/field/bg/rom_yami_box_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono01_pal[] = {
#include "assets/field/bg/rom_yami_mono01_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono02_pal[] = {
#include "assets/field/bg/rom_yami_mono02_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_mono03_pal[] = {
#include "assets/field/bg/rom_yami_mono03_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_qup_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_qup_pal[] = {
#include "assets/field/bg/rom_yami_qup_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_hyou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_hyou_pal[] = {
#include "assets/field/bg/rom_yami_hyou_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_step_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_step_tex_pal[] = {
#include "assets/field/bg/rom_yami_step_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_hugu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_hugu_pal[] = {
#include "assets/field/bg/rom_yami_hugu_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_yami_tama_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_yami_tama_pal[] = {
#include "assets/field/bg/rom_yami_tama_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_wall_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_wall_tex[] = {
#include "assets/field/bg/rom_yami_wall_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_floor_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_floor_tex[] = {
#include "assets/field/bg/rom_yami_floor_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_poll_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_poll_tex[] = {
#include "assets/field/bg/rom_yami_poll_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_box01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_box01_tex[] = {
#include "assets/field/bg/rom_yami_box01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_box02_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_box02_tex[] = {
#include "assets/field/bg/rom_yami_box02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono01_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono01_tex[] = {
#include "assets/field/bg/rom_yami_mono01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono02_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono02_tex[] = {
#include "assets/field/bg/rom_yami_mono02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono03_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_mono03_tex[] = {
#include "assets/field/bg/rom_yami_mono03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_qup_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_qup_tex[] = {
#include "assets/field/bg/rom_yami_qup_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hyou_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hyou_tex[] = {
#include "assets/field/bg/rom_yami_hyou_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hyou02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hyou02_tex[] = {
#include "assets/field/bg/rom_yami_hyou02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_step_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_step_tex[] = {
#include "assets/field/bg/rom_yami_step_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hugu_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_hugu_tex[] = {
#include "assets/field/bg/rom_yami_hugu_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_tama_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_tama_tex[] = {
#include "assets/field/bg/rom_yami_tama_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_yami_shadow01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_yami_shadow01_tex[] = {
#include "assets/field/bg/rom_yami_shadow01_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx grd_yamishop_v[0x10D0 / sizeof(Vtx)];
#else
static Vtx grd_yamishop_v[] = {
#include "assets/field/bg/grd_yamishop_v.inc"
};
#endif

extern Gfx grd_yamishop_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_yamishop_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_hugu_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_hugu_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&grd_yamishop_v[226], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_tama_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_tama_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[232], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_hyou_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_hyou02_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[238], 12, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_hyou_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,        // tri count
                          6, 7, 8,  // tri0
                          6, 8, 9,  // tri1
                          7, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(7, 11, 8, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_qup_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_qup_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[250], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono01_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_mono01_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[255], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono02_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_mono02_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[260], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono03_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_mono03_tex, G_IM_FMT_CI, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[265], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_step_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_step_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[0], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_wall_tex, G_IM_FMT_CI, 32, 48, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[5], 32, 0),
    gsSPNTrianglesInit_5b(35,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      6, 8, 2, // tri1
                      0, 2, 8, // tri2
                      6, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 2,   // tri0
                      10, 11, 3, // tri1
                      10, 9, 11, // tri2
                      9, 2, 11   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 11, // tri0
                      9, 12, 6, // tri1
                      12, 4, 6, // tri2
                      9, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 4, 12,  // tri0
                      14, 15, 16, // tri1
                      17, 14, 16, // tri2
                      16, 15, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 18, // tri0
                      19, 4, 20,  // tri1
                      17, 19, 20, // tri2
                      13, 17, 20  // tri3
                      ),
    gsSPNTriangles_5b(13, 20, 4,  // tri0
                      17, 18, 19, // tri1
                      18, 21, 22, // tri2
                      23, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(18, 22, 19, // tri0
                      24, 21, 18, // tri1
                      15, 24, 18, // tri2
                      5, 4, 19    // tri3
                      ),
    gsSPNTriangles_5b(23, 5, 19,  // tri0
                      25, 26, 27, // tri1
                      26, 28, 27, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_yamishop_v[37], 13, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 3, // tri0
                      6, 2, 4, // tri1
                      7, 8, 9, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(6, 4, 8,  // tri0
                      4, 9, 8,  // tri1
                      6, 10, 2, // tri2
                      10, 11, 2 // tri3
                      ),
    gsSPNTriangles_5b(6, 12, 10,  // tri0
                      12, 11, 10, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_floor_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_yamishop_v[50], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,   // tri0
                      6, 7, 1,   // tri1
                      8, 9, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      14, 17, 15, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 13, // tri0
                      13, 17, 14, // tri1
                      22, 23, 2,  // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      25, 12, 23, // tri1
                      26, 24, 22, // tri2
                      25, 24, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 5,  // tri0
                      28, 30, 29, // tri1
                      28, 31, 30, // tri2
                      28, 16, 31  // tri3
                      ),
    gsSPVertex(&grd_yamishop_v[82], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 7,   // tri0
                      5, 9, 6,   // tri1
                      10, 6, 11, // tri2
                      5, 7, 12   // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 13,   // tri0
                      14, 15, 9,  // tri1
                      16, 14, 17, // tri2
                      16, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 15, // tri0
                      19, 20, 12, // tri1
                      0, 2, 21,   // tri2
                      22, 0, 21   // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 21, // tri0
                      24, 25, 11, // tri1
                      26, 27, 28, // tri2
                      24, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 24, 28, // tri0
                      13, 30, 4,  // tri1
                      31, 3, 4,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_yamishop_v[114], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_poll_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[118], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 6, 7, // tri1
                      4, 7, 5, // tri2
                      8, 9, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 1, 0,  // tri0
                      9, 10, 4, // tri1
                      9, 4, 1,  // tri2
                      10, 11, 6 // tri3
                      ),
    gsSPNTriangles_5b(10, 6, 4,   // tri0
                      12, 13, 14, // tri1
                      12, 14, 15, // tri2
                      13, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 14, // tri0
                      16, 18, 19, // tri1
                      16, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      21, 24, 25, // tri1
                      21, 25, 22, // tri2
                      26, 20, 23  // tri3
                      ),
    gsSPNTriangles_5b(26, 23, 27, // tri0
                      28, 29, 30, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_yamishop_v[150], 24, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      9, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 10,  // tri0
                      14, 8, 11,  // tri1
                      14, 11, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      17, 20, 21, // tri1
                      17, 21, 18, // tri2
                      22, 16, 19  // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_box_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_box02_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_yamishop_v[174], 8, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_box01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[182], 28, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 0,   // tri0
                      6, 7, 8,   // tri1
                      6, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 13, // tri0
                      14, 15, 16, // tri1
                      14, 16, 17, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      22, 23, 19, // tri1
                      22, 19, 18, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 150, 10, 10, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_yami_shadow01_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_yamishop_v[210], 16, 0),
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
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_grd_yamishop_grd_yamishop_c(void) {
    pc_load_asset("assets/field/bg/rom_yami_wall_pal.bin", rom_yami_wall_pal, 0x20, 0x8EA080, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_floor_pal.bin", rom_yami_floor_pal, 0x20, 0x8EA0A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_box_pal.bin", rom_yami_box_pal, 0x20, 0x8EA0C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_mono01_pal.bin", rom_yami_mono01_pal, 0x20, 0x8EA0E0, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_mono02_pal.bin", rom_yami_mono02_pal, 0x20, 0x8EA100, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_mono03_pal.bin", rom_yami_mono03_pal, 0x20, 0x8EA120, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_qup_pal.bin", rom_yami_qup_pal, 0x20, 0x8EA140, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_hyou_pal.bin", rom_yami_hyou_pal, 0x20, 0x8EA160, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_step_tex_pal.bin", rom_yami_step_tex_pal, 0x20, 0x8EA180, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_hugu_pal.bin", rom_yami_hugu_pal, 0x20, 0x8EA1A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_tama_pal.bin", rom_yami_tama_pal, 0x20, 0x8EA1C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_yami_wall_tex.bin", rom_yami_wall_tex, 0x300, 0x8EA1E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_floor_tex.bin", rom_yami_floor_tex, 0x800, 0x8EA4E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_poll_tex.bin", rom_yami_poll_tex, 0x80, 0x8EACE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_box01_tex.bin", rom_yami_box01_tex, 0x100, 0x8EAD60, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_box02_tex.bin", rom_yami_box02_tex, 0x80, 0x8EAE60, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_mono01_tex.bin", rom_yami_mono01_tex, 0x200, 0x8EAEE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_mono02_tex.bin", rom_yami_mono02_tex, 0x200, 0x8EB0E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_mono03_tex.bin", rom_yami_mono03_tex, 0x200, 0x8EB2E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_qup_tex.bin", rom_yami_qup_tex, 0x300, 0x8EB4E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_hyou_tex.bin", rom_yami_hyou_tex, 0x100, 0x8EB7E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_hyou02_tex.bin", rom_yami_hyou02_tex, 0x100, 0x8EB8E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_step_tex.bin", rom_yami_step_tex, 0x400, 0x8EB9E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_hugu_tex.bin", rom_yami_hugu_tex, 0x300, 0x8EBDE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_tama_tex.bin", rom_yami_tama_tex, 0x300, 0x8EC0E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_yami_shadow01_tex.bin", rom_yami_shadow01_tex, 0x100, 0x8EC3E0, 0, 0);
    pc_load_asset("assets/field/bg/grd_yamishop_v.bin", grd_yamishop_v, 0x10D0, 0x8EC4E0, 0, 2);
}
#endif
