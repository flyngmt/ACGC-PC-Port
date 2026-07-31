#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx pla_1_v[0x1CB0 / sizeof(Vtx)];
#else
static Vtx pla_1_v[] = {
#include "assets/npc/mdl/pla_1_v.inc"
};
#endif

static Gfx head_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[0], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[7], 23, 7),
    gsSPNTrianglesInit_5b(12,       // tri count
                          1, 7, 8,  // tri0
                          6, 9, 10, // tri1
                          3, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(0, 13, 14, // tri0
                      4, 15, 16, // tri1
                      6, 17, 18, // tri2
                      0, 19, 2   // tri3
                      ),
    gsSPNTriangles_5b(2, 20, 21, // tri0
                      6, 22, 23, // tri1
                      6, 24, 25, // tri2
                      6, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(6, 29, 28, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&pla_1_v[30], 22, 7),
    gsSPNTrianglesInit_5b(6,       // tri count
                          2, 7, 1, // tri0
                          3, 1, 8, // tri1
                          0, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 10,  // tri0
                      6, 3, 11,  // tri1
                      2, 12, 13, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,         // tri count
                          5, 15, 14, // tri0
                          0, 0, 0,   // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12,         // tri count
                          16, 17, 18, // tri0
                          19, 20, 16, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(16, 20, 24, // tri0
                      25, 26, 21, // tri1
                      27, 17, 16, // tri2
                      21, 23, 28  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 21, // tri0
                      25, 28, 16, // tri1
                      16, 28, 23, // tri2
                      18, 25, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 23, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[52], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      4, 3, 11,   // tri1
                      12, 13, 14, // tri2
                      15, 16, 4   // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      15, 20, 21, // tri1
                      22, 23, 24, // tri2
                      12, 25, 13  // tri3
                      ),
    gsSPNTriangles_5b(26, 25, 12, // tri0
                      19, 18, 27, // tri1
                      23, 28, 29, // tri2
                      30, 10, 31  // tri3
                      ),
    gsSPVertex(&pla_1_v[84], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      10, 11, 12, // tri1
                      13, 4, 14,  // tri2
                      15, 16, 9   // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 4,   // tri0
                      4, 13, 17, // tri1
                      18, 6, 4,  // tri2
                      15, 9, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      23, 24, 25, // tri1
                      26, 0, 20,  // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(20, 30, 26, // tri0
                      22, 30, 20, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&pla_1_v[115], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      1, 0, 13,   // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      18, 13, 19, // tri1
                      20, 21, 16, // tri2
                      9, 22, 23   // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 28, 29, // tri1
                      30, 9, 8,   // tri2
                      12, 31, 10  // tri3
                      ),
    gsSPVertex(&pla_1_v[147], 23, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[170], 21, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 8,   // tri0
                      0, 8, 9,   // tri1
                      10, 11, 6, // tri2
                      10, 6, 12  // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 8,   // tri0
                      11, 14, 15, // tri1
                      4, 8, 2,    // tri2
                      6, 11, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 1,  // tri0
                      15, 7, 6, // tri1
                      12, 6, 5, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          16, 17, 18, // tri0
                          16, 19, 17, // tri1
                          20, 19, 16  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[191], 24, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 2,  // tri0
                      5, 9, 3,  // tri1
                      2, 10, 0, // tri2
                      4, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(3, 13, 14, // tri0
                      4, 3, 11,  // tri1
                      8, 7, 15,  // tri2
                      2, 8, 10   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 16,   // tri0
                      1, 16, 17,  // tri1
                      18, 19, 14, // tri2
                      18, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(1, 17, 20, // tri0
                      1, 20, 21, // tri1
                      2, 1, 21,  // tri2
                      18, 13, 9  // tri3
                      ),
    gsSPNTriangles_5b(18, 9, 22, // tri0
                      4, 23, 5,  // tri1
                      9, 13, 3,  // tri2
                      2, 21, 6   // tri3
                      ),
    gsSPNTriangles_5b(14, 11, 3, // tri0
                      12, 23, 4, // tri1
                      15, 10, 8, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[215], 29, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          13, 14, 15, // tri0
                          15, 16, 13, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13,         // tri count
                          17, 18, 19, // tri0
                          17, 20, 21, // tri1
                          22, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 17, 19, // tri0
                      18, 26, 27, // tri1
                      25, 22, 17, // tri2
                      17, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 25, // tri0
                      19, 18, 28, // tri1
                      27, 28, 18, // tri2
                      24, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 26, 18, // tri0
                      21, 18, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[279], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[283], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          1, 6, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      0, 2, 12,  // tri1
                      0, 13, 1,  // tri2
                      2, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 15, // tri0
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

static Gfx Rarm1_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[299], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[303], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 2, 4, // tri0
                          0, 3, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      1, 13, 12, // tri2
                      0, 14, 2   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[244], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[248], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          1, 6, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      2, 0, 12,  // tri1
                      1, 13, 0,  // tri2
                      3, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 15, // tri0
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

static Gfx Larm1_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[264], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[268], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 1, 4, // tri0
                          3, 0, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      1, 13, 12, // tri2
                      2, 14, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_pla_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[314], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[323], 11, 9),
    gsSPNTrianglesInit_5b(7,        // tri count
                          0, 1, 9,  // tri0
                          1, 6, 10, // tri1
                          2, 0, 11  // tri2
                          ),
    gsSPNTriangles_5b(0, 13, 12, // tri0
                      1, 15, 14, // tri1
                      6, 16, 17, // tri2
                      2, 18, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[334], 17, 9),
    gsSPNTrianglesInit_5b(8,        // tri count
                          7, 9, 10, // tri0
                          4, 8, 11, // tri1
                          4, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 14,  // tri0
                      7, 3, 15,  // tri1
                      7, 16, 17, // tri2
                      5, 4, 18   // tri3
                      ),
    gsSPNTriangles_5b(4, 19, 20, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          24, 25, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pla_1_v[351], 15, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      2, 9, 0,  // tri1
                      6, 11, 7, // tri2
                      9, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 6,  // tri0
                      10, 13, 8, // tri1
                      5, 7, 3,   // tri2
                      14, 8, 7   // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 14, // tri0
                      14, 0, 9, // tri1
                      7, 5, 14, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_pla_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[366], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[369], 16, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 3, // tri0
                          2, 4, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,  // tri0
                      0, 9, 10, // tri1
                      2, 1, 11, // tri2
                      1, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 16, // tri1
                          16, 15, 17  // tri2
                          ),
    gsSPNTriangles_5b(16, 18, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[410], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[414], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 4, 5, // tri0
                          2, 3, 6, // tri1
                          1, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 8,   // tri0
                      3, 0, 9,   // tri1
                      0, 11, 10, // tri2
                      2, 13, 12  // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          17, 16, 15  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_pla_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[428], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 3, // tri0
                      6, 3, 0, // tri1
                      0, 2, 6, // tri2
                      4, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_pla_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[385], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pla_1_v[389], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 4, 5, // tri0
                          3, 2, 6, // tri1
                          2, 1, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,   // tri0
                      0, 3, 9,   // tri1
                      0, 11, 10, // tri2
                      2, 13, 12  // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          17, 14, 16, // tri1
                          15, 14, 17  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_pla_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[403], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          0, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 6, // tri0
                      2, 4, 6, // tri1
                      6, 0, 2, // tri2
                      1, 5, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_pla_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pla_1_v[435], 24, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 0, // tri0
                      0, 2, 7, // tri1
                      5, 8, 9, // tri2
                      10, 3, 2 // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 10, // tri0
                      9, 1, 5,  // tri1
                      5, 11, 8, // tri2
                      8, 3, 10  // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 9, // tri0
                      7, 2, 4,  // tri1
                      11, 5, 6, // tri2
                      7, 12, 0  // tri3
                      ),
    gsSPNTriangles_5b(0, 12, 6, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12,         // tri count
                          13, 14, 15, // tri0
                          16, 15, 17, // tri1
                          17, 15, 14  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 22, 23, // tri1
                      20, 16, 18, // tri2
                      23, 14, 21  // tri3
                      ),
    gsSPNTriangles_5b(14, 23, 17, // tri0
                      21, 14, 13, // tri1
                      17, 18, 16, // tri2
                      13, 16, 20  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_pla_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_pla_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-400,0 },
    /* joint 3 */ { Lfoot1_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,400,0 },
    /* joint 7 */ { Rfoot1_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,-900 },
    /* joint 11 */ { tail1_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_pla_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,-1100,0 },
    /* joint 15 */ { Larm1_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_pla_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,1100,0 },
    /* joint 18 */ { Rarm1_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1201,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,1250 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_pla_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_pla_1 = { 26, 12, cKF_je_r_pla_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_pla_1_c(void) {
    pc_load_asset("assets/npc/mdl/pla_1_v.bin", pla_1_v, 0x1CB0, 0x627AE0, 0, 2);
}
#endif
