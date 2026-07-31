#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx wip_1_v[0x1700 / sizeof(Vtx)];
#else
static Vtx wip_1_v[] = {
#include "assets/npc/mdl/wip_1_v.inc"
};
#endif

static Gfx head_wip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[0], 15, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 7, // tri0
                      6, 7, 8, // tri1
                      1, 0, 7, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 12,  // tri0
                      13, 11, 10, // tri1
                      3, 6, 4,    // tri2
                      12, 4, 6    // tri3
                      ),
    gsSPNTriangles_5b(14, 9, 8, // tri0
                      14, 8, 7, // tri1
                      7, 0, 14, // tri2
                      11, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 11, // tri0
                      7, 3, 1,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&wip_1_v[15], 27, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      5, 4, 12,   // tri1
                      13, 14, 15, // tri2
                      16, 14, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      20, 3, 5,   // tri1
                      6, 8, 11,   // tri2
                      15, 21, 13  // tri3
                      ),
    gsSPNTriangles_5b(2, 12, 0,   // tri0
                      22, 23, 24, // tri1
                      19, 1, 16,  // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 19,  // tri0
                      23, 3, 20, // tri1
                      25, 5, 2,  // tri2
                      7, 6, 21   // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 26,  // tri0
                      10, 9, 22,  // tri1
                      22, 24, 10, // tri2
                      20, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(11, 8, 9,   // tri0
                      21, 6, 13,  // tri1
                      17, 14, 13, // tri2
                      2, 5, 12    // tri3
                      ),
    gsSPNTriangles_5b(19, 25, 2,  // tri0
                      13, 26, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&wip_1_v[42], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,  // tri0
                      7, 8, 4,  // tri1
                      5, 3, 2,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 8, // tri0
                      5, 2, 6,  // tri1
                      7, 9, 8,  // tri2
                      11, 12, 9 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&wip_1_v[55], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      11, 3, 6, // tri1
                      6, 7, 12, // tri2
                      8, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 7, 16, // tri0
                      12, 17, 6, // tri1
                      18, 9, 8,  // tri2
                      2, 4, 11   // tri3
                      ),
    gsSPNTriangles_5b(2, 11, 0,   // tri0
                      19, 20, 21, // tri1
                      22, 23, 24, // tri2
                      5, 25, 26   // tri3
                      ),
    gsSPNTriangles_5b(25, 5, 4,   // tri0
                      27, 28, 29, // tri1
                      29, 30, 27, // tri2
                      20, 19, 27  // tri3
                      ),
    gsSPNTriangles_5b(27, 30, 20, // tri0
                      26, 29, 5,  // tri1
                      23, 22, 26, // tri2
                      23, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(1, 24, 23, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&wip_1_v[86], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 0,  // tri0
                      10, 5, 4, // tri1
                      4, 1, 10, // tri2
                      5, 11, 3  // tri3
                      ),
    gsSPNTriangles_5b(6, 12, 7,  // tri0
                      7, 12, 13, // tri1
                      0, 8, 14,  // tri2
                      15, 16, 13 // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 9,  // tri0
                      19, 20, 21, // tri1
                      21, 22, 19, // tri2
                      8, 18, 6    // tri3
                      ),
    gsSPNTriangles_5b(7, 14, 8,   // tri0
                      20, 23, 21, // tri1
                      24, 25, 14, // tri2
                      26, 19, 5   // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 6,  // tri0
                      21, 29, 30, // tri1
                      6, 18, 27,  // tri2
                      1, 0, 10    // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 29, // tri0
                      2, 31, 9,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&wip_1_v[118], 30, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 3  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      13, 12, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18,         // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 21, // tri0
                      21, 17, 18, // tri1
                      18, 25, 21, // tri2
                      26, 15, 24  // tri3
                      ),
    gsSPNTriangles_5b(27, 22, 25, // tri0
                      21, 24, 17, // tri1
                      18, 28, 19, // tri2
                      16, 29, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 25, 22, // tri0
                      25, 20, 27, // tri1
                      17, 24, 15, // tri2
                      24, 23, 26  // tri3
                      ),
    gsSPNTriangles_5b(20, 25, 18, // tri0
                      17, 29, 28, // tri1
                      17, 28, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&wip_1_v[148], 20, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 1,   // tri0
                      11, 10, 12, // tri1
                      13, 14, 11, // tri2
                      2, 3, 15    // tri3
                      ),
    gsSPNTriangles_5b(16, 14, 17, // tri0
                      8, 16, 18,  // tri1
                      4, 7, 19,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[202], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[206], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          3, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 10,  // tri0
                      1, 3, 11,  // tri1
                      0, 12, 13, // tri2
                      2, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[222], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[225], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 3, // tri0
                          2, 5, 4, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      1, 0, 9,   // tri1
                      0, 10, 11, // tri2
                      2, 12, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[168], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[172], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          3, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10,  // tri0
                      3, 1, 11,  // tri1
                      0, 12, 13, // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 15, // tri0
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

static Gfx Larm1_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[188], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[191], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 0, 3, // tri0
                          2, 5, 4, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      0, 1, 9,   // tri1
                      0, 10, 11, // tri2
                      2, 12, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_wip_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[236], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[244], 24, 8),
    gsSPNTrianglesInit_5b(16,        // tri count
                          0, 8, 9,   // tri0
                          0, 10, 11, // tri1
                          4, 2, 12   // tri2
                          ),
    gsSPNTriangles_5b(3, 13, 14, // tri0
                      7, 15, 16, // tri1
                      3, 6, 17,  // tri2
                      7, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 20,  // tri0
                      1, 0, 21,  // tri1
                      3, 22, 23, // tri2
                      7, 4, 24   // tri3
                      ),
    gsSPNTriangles_5b(2, 25, 26, // tri0
                      0, 5, 27,  // tri1
                      5, 3, 28,  // tri2
                      6, 7, 29   // tri3
                      ),
    gsSPNTriangles_5b(2, 30, 31, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&wip_1_v[268], 15, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8,   // tri0
                      3, 5, 2,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 0  // tri3
                      ),
    gsSPNTriangles_5b(13, 9, 11,  // tri0
                      11, 10, 14, // tri1
                      14, 10, 8,  // tri2
                      4, 1, 0     // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 7, // tri0
                      4, 8, 3,  // tri1
                      0, 11, 4, // tri2
                      4, 11, 14 // tri3
                      ),
    gsSPNTriangles_5b(2, 12, 0, // tri0
                      2, 1, 3,  // tri1
                      14, 8, 4, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[283], 19, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      7, 9, 10, // tri1
                      2, 1, 11, // tri2
                      4, 0, 2   // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 0,  // tri0
                      11, 1, 14,  // tri1
                      15, 16, 13, // tri2
                      9, 14, 16   // tri3
                      ),
    gsSPNTriangles_5b(14, 1, 16,  // tri0
                      8, 11, 14,  // tri1
                      17, 15, 12, // tri2
                      17, 12, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 1, 13,  // tri0
                      10, 9, 15,  // tri1
                      10, 15, 17, // tri2
                      18, 12, 4   // tri3
                      ),
    gsSPNTriangles_5b(18, 4, 3, // tri0
                      13, 1, 0, // tri1
                      5, 2, 11, // tri2
                      11, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(14, 9, 8,   // tri0
                      16, 15, 9,  // tri1
                      13, 12, 15, // tri2
                      0, 4, 12    // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 4, // tri0
                      6, 5, 8, // tri1
                      6, 8, 7, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[327], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[331], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 0, 4, // tri0
                          0, 6, 5, // tri1
                          2, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,  // tri0
                      1, 2, 10, // tri1
                      2, 3, 11, // tri2
                      1, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          17, 15, 14, // tri1
                          17, 16, 15  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_wip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[345], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6, // tri0
                      2, 1, 4, // tri1
                      2, 6, 0, // tri2
                      3, 2, 4  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_wip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[302], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&wip_1_v[306], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          0, 6, 5, // tri1
                          2, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,  // tri0
                      2, 1, 10, // tri1
                      3, 2, 11, // tri2
                      1, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          16, 15, 17, // tri1
                          15, 14, 17  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_wip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[320], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 2, 3, // tri0
                      4, 1, 0, // tri1
                      2, 6, 0, // tri2
                      4, 0, 5  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_wip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&wip_1_v[352], 16, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,    // tri0
                      4, 8, 9,    // tri1
                      10, 11, 12, // tri2
                      4, 9, 5     // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 13,  // tri0
                      11, 6, 0,  // tri1
                      11, 0, 12, // tri2
                      1, 5, 9    // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 9,  // tri0
                      9, 13, 3, // tri1
                      0, 6, 5,  // tri2
                      0, 5, 1   // tri3
                      ),
    gsSPNTriangles_5b(8, 4, 14,  // tri0
                      14, 4, 7,  // tri1
                      7, 15, 14, // tri2
                      11, 10, 15 // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 7, // tri0
                      11, 7, 6,  // tri1
                      2, 12, 0,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_wip_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,800,0 },
    /* joint 1 */ { base_wip_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 355,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 343,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 355,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 343,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,-500 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_wip_model, 3, cKF_JOINT_FLAG_DISP_OPA, 497,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 400,-500,0 },
    /* joint 15 */ { Larm1_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_wip_model, 0, cKF_JOINT_FLAG_DISP_OPA, 399,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 400,500,0 },
    /* joint 18 */ { Rarm1_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 401,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 398,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 803,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,1150 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_wip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1582,0,11 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_wip_1 = { 26, 11, cKF_je_r_wip_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_wip_1_c(void) {
    pc_load_asset("assets/npc/mdl/wip_1_v.bin", wip_1_v, 0x1700, 0x65C020, 0, 2);
}
#endif
