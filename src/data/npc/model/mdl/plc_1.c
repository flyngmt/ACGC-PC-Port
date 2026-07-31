#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx plc_1_v[0x1730 / sizeof(Vtx)];
#else
static Vtx plc_1_v[] = {
#include "assets/npc/mdl/plc_1_v.inc"
};
#endif

static Gfx head_plc_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[0], 29, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8, // tri0
                      4, 8, 5, // tri1
                      7, 0, 3, // tri2
                      7, 3, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 4, 6,   // tri0
                      10, 11, 6, // tri1
                      10, 6, 5,  // tri2
                      10, 5, 12  // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 9, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          13, 14, 15, // tri0
                          15, 16, 13, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 22, // tri1
                          23, 21, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 19, 26, // tri0
                      27, 19, 25, // tri1
                      21, 20, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[29], 21, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 0,   // tri0
                      7, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(8, 3, 6,   // tri0
                      2, 16, 14, // tri1
                      3, 8, 10,  // tri2
                      2, 1, 17   // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 19, // tri0
                      10, 20, 3,  // tri1
                      2, 13, 0,   // tri2
                      10, 8, 7    // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 2, // tri0
                      15, 6, 5,  // tri1
                      0, 13, 15, // tri2
                      5, 6, 3    // tri3
                      ),
    gsSPNTriangles_5b(15, 5, 0,   // tri0
                      19, 12, 11, // tri1
                      11, 18, 19, // tri2
                      12, 20, 10  // tri3
                      ),
    gsSPNTriangles_5b(16, 2, 17,  // tri0
                      17, 18, 16, // tri1
                      12, 10, 9,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[50], 30, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 1, // tri0
                      5, 4, 6, // tri1
                      5, 6, 7, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 11, // tri0
                      5, 12, 13, // tri1
                      1, 14, 4,  // tri2
                      4, 3, 2    // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 7,   // tri0
                      11, 16, 15, // tri1
                      15, 8, 11,  // tri2
                      8, 7, 6     // tri3
                      ),
    gsSPNTriangles_5b(14, 9, 6,   // tri0
                      12, 5, 7,   // tri1
                      16, 17, 15, // tri2
                      13, 3, 5    // tri3
                      ),
    gsSPNTriangles_5b(3, 13, 0,  // tri0
                      7, 17, 12, // tri1
                      6, 4, 14,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14,         // tri count
                          18, 19, 20, // tri0
                          19, 21, 22, // tri1
                          18, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 19, 18, // tri0
                      26, 23, 18, // tri1
                      18, 20, 26, // tri2
                      20, 22, 27  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 19, // tri0
                      20, 27, 28, // tri1
                      28, 26, 20, // tri2
                      29, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 29, // tri0
                      29, 19, 25, // tri1
                      18, 24, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[80], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          3, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      7, 8, 5, // tri1
                      2, 9, 0, // tri2
                      4, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[127], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[131], 13, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 1, 4, // tri0
                          2, 5, 0, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,  // tri0
                      3, 0, 10, // tri1
                      1, 3, 11, // tri2
                      2, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[144], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[148], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 4, 5, // tri0
                          1, 0, 6, // tri1
                          2, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      2, 12, 13, // tri2
                      3, 1, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          17, 16, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[90], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[94], 13, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          3, 1, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      0, 12, 2,  // tri2
                      1, 2, 13   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[107], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[111], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          0, 2, 6, // tri1
                          2, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      1, 10, 3,  // tri1
                      3, 11, 12, // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx chest_plc_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[164], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[174], 18, 10),
    gsSPNTrianglesInit_5b(12,       // tri count
                          1, 0, 10, // tri0
                          3, 4, 11, // tri1
                          4, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(1, 14, 15, // tri0
                      2, 16, 17, // tri1
                      2, 18, 19, // tri2
                      4, 8, 20   // tri3
                      ),
    gsSPNTriangles_5b(3, 21, 22, // tri0
                      0, 23, 24, // tri1
                      6, 1, 25,  // tri2
                      2, 3, 26   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 27, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[192], 10, 10),
    gsSPNTrianglesInit_5b(6,         // tri count
                          5, 10, 11, // tri0
                          7, 9, 12,  // tri1
                          7, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(7, 15, 16, // tri0
                      5, 17, 18, // tri1
                      9, 5, 19,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[202], 22, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          2, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 2, // tri0
                      7, 4, 1, // tri1
                      6, 5, 8, // tri2
                      9, 6, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 2, 6,  // tri0
                      2, 9, 0,  // tri1
                      2, 11, 5, // tri2
                      4, 11, 2  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9,          // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          15, 18, 16  // tri2
                          ),
    gsSPNTriangles_5b(15, 17, 19, // tri0
                      15, 14, 18, // tri1
                      12, 14, 15, // tri2
                      12, 15, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 15, // tri0
                      17, 16, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_plc_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[249], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      2, 6, 4, // tri1
                      4, 6, 1, // tri2
                      0, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[224], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[228], 21, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          0, 6, 7, // tri1
                          3, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 10,  // tri0
                      2, 11, 12, // tri1
                      2, 3, 13,  // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(12,         // tri count
                          16, 17, 18, // tri0
                          19, 17, 20, // tri1
                          18, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 22, 21, // tri0
                      23, 21, 20, // tri1
                      20, 21, 19, // tri2
                      20, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 16, 23, // tri0
                      21, 18, 19, // tri1
                      19, 18, 17, // tri2
                      18, 24, 16  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[297], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[302], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 4, 5, // tri0
                          3, 6, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      2, 3, 12,  // tri1
                      1, 2, 13,  // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 16,  // tri0
                      2, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_plc_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[319], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[325], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 6, 7, // tri0
                          3, 4, 8, // tri1
                          5, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 11, // tri0
                      0, 2, 12, // tri1
                      1, 13, 5, // tri2
                      1, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 16,  // tri0
                      2, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_plc_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[256], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[261], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 5, 6, // tri0
                          3, 7, 8, // tri1
                          2, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(0, 11, 12, // tri0
                      0, 4, 13,  // tri1
                      2, 1, 14,  // tri2
                      3, 2, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 16, 17, // tri0
                      4, 3, 18,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_plc_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[278], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plc_1_v[284], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 6, 7, // tri0
                          1, 8, 9, // tri1
                          0, 1, 10 // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 11,  // tri0
                      1, 4, 12,  // tri1
                      3, 13, 14, // tri2
                      3, 2, 15   // tri3
                      ),
    gsSPNTriangles_5b(4, 16, 17, // tri0
                      3, 18, 5,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_plc_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plc_1_v[338], 25, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      0, 9, 8,   // tri1
                      10, 4, 11, // tri2
                      2, 9, 0    // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 2,    // tri0
                      8, 12, 6,   // tri1
                      11, 13, 10, // tri2
                      3, 11, 4    // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          14, 15, 16, // tri0
                          16, 17, 14, // tri1
                          14, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(19, 15, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          20, 21, 22, // tri0
                          23, 24, 20, // tri1
                          20, 24, 21  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plc_1_v[363], 8, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      6, 1, 5, // tri1
                      6, 5, 7, // tri2
                      1, 0, 4  // tri3
                      ),
    gsSPNTriangles_5b(1, 4, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_plc_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_plc_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 150,0,-500 },
    /* joint 11 */ { tail1_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_plc_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_plc_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,-900,0 },
    /* joint 15 */ { Larm1_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_plc_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,900,0 },
    /* joint 18 */ { Rarm1_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1201,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,1250 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_plc_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_plc_1 = { 26, 13, cKF_je_r_plc_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_plc_1_c(void) {
    pc_load_asset("assets/npc/mdl/plc_1_v.bin", plc_1_v, 0x1730, 0x62A158, 0, 2);
}
#endif
