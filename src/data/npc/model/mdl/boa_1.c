#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx boa_1_v[0x1C50 / sizeof(Vtx)];
#else
static Vtx boa_1_v[] = {
#include "assets/npc/mdl/boa_1_v.inc"
};
#endif

static Gfx head_boa_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[26], 28, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          4, 5, 6, // tri0
                          7, 5, 4, // tri1
                          8, 5, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          10, 11, 12, // tri0
                          12, 13, 10, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10,         // tri count
                          14, 15, 16, // tri0
                          15, 17, 18, // tri1
                          17, 15, 14  // tri2
                          ),
    gsSPNTriangles_5b(17, 14, 19, // tri0
                      17, 19, 20, // tri1
                      18, 16, 15, // tri2
                      16, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 19, // tri0
                      20, 18, 17, // tri1
                      20, 19, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPNTrianglesInit_5b(10,         // tri count
                          21, 22, 23, // tri0
                          24, 25, 22, // tri1
                          23, 22, 25  // tri2
                          ),
    gsSPNTriangles_5b(26, 23, 25, // tri0
                      27, 26, 25, // tri1
                      22, 21, 24, // tri2
                      27, 24, 21  // tri3
                      ),
    gsSPNTriangles_5b(26, 21, 23, // tri0
                      25, 24, 27, // tri1
                      21, 26, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&boa_1_v[54], 22, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      8, 1, 6, // tri1
                      5, 9, 3, // tri2
                      3, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(0, 11, 7,  // tri0
                      0, 12, 11, // tri1
                      10, 8, 3,  // tri2
                      13, 2, 14  // tri3
                      ),
    gsSPNTriangles_5b(7, 15, 16,  // tri0
                      17, 18, 1,  // tri1
                      19, 20, 21, // tri2
                      21, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 18,   // tri0
                      15, 7, 11,  // tri1
                      13, 21, 20, // tri2
                      15, 11, 19  // tri3
                      ),
    gsSPNTriangles_5b(16, 4, 7,   // tri0
                      14, 2, 18,  // tri1
                      19, 11, 20, // tri2
                      1, 8, 17    // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 0, // tri0
                      0, 6, 1, // tri1
                      6, 3, 8, // tri2
                      0, 2, 12 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&boa_1_v[76], 21, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(5, 9, 3,   // tri0
                      10, 2, 11, // tri1
                      12, 6, 13, // tri2
                      5, 8, 7    // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 5,   // tri0
                      14, 11, 2, // tri1
                      6, 12, 15, // tri2
                      1, 14, 2   // tri3
                      ),
    gsSPNTriangles_5b(6, 15, 7,   // tri0
                      3, 9, 16,   // tri1
                      17, 18, 13, // tri2
                      1, 0, 16    // tri3
                      ),
    gsSPNTriangles_5b(13, 18, 12, // tri0
                      16, 0, 19,  // tri1
                      10, 20, 17, // tri2
                      11, 20, 10  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 3, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&boa_1_v[97], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 1,  // tri1
                      14, 15, 16, // tri2
                      3, 9, 17    // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 18,   // tri0
                      19, 8, 7,   // tri1
                      20, 21, 22, // tri2
                      23, 20, 11  // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 10,   // tri0
                      20, 23, 21, // tri1
                      1, 0, 12,   // tri2
                      11, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(1, 22, 25,  // tri0
                      1, 25, 2,   // tri1
                      26, 23, 11, // tri2
                      13, 22, 1   // tri3
                      ),
    gsSPNTriangles_5b(11, 24, 9, // tri0
                      8, 27, 17, // tri1
                      17, 27, 3, // tri2
                      28, 29, 30 // tri3
                      ),
    gsSPNTriangles_5b(8, 0, 6,    // tri0
                      2, 6, 0,    // tri1
                      22, 13, 24, // tri2
                      22, 24, 20  // tri3
                      ),
    gsSPVertex(&boa_1_v[128], 27, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      11, 0, 3, // tri2
                      12, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 13, 16, // tri1
                      17, 18, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 20, // tri0
                      5, 24, 6,   // tri1
                      23, 25, 20, // tri2
                      15, 26, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[0], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[6], 20, 6),
    gsSPNTrianglesInit_5b(10,      // tri count
                          3, 4, 6, // tri0
                          5, 2, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 10,  // tri0
                      1, 11, 12, // tri1
                      0, 13, 14, // tri2
                      3, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 17,  // tri0
                      1, 18, 19, // tri1
                      1, 0, 20,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          21, 22, 23, // tri0
                          23, 24, 25, // tri1
                          23, 25, 21  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[189], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[193], 16, 4),
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

static Gfx Rarm1_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[209], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[212], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 1, // tri0
                          0, 5, 4, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      2, 0, 12,  // tri2
                      0, 1, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[155], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[159], 16, 4),
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

static Gfx Larm1_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[175], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[178], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 2, // tri0
                          0, 5, 4, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      0, 2, 12,  // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_boa_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[223], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[233], 20, 10),
    gsSPNTrianglesInit_5b(13,       // tri count
                          2, 5, 10, // tri0
                          5, 6, 11, // tri1
                          1, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(3, 14, 15, // tri0
                      3, 2, 16,  // tri1
                      4, 17, 18, // tri2
                      0, 4, 19   // tri3
                      ),
    gsSPNTriangles_5b(7, 20, 21, // tri0
                      0, 22, 23, // tri1
                      6, 8, 24,  // tri2
                      7, 1, 25   // tri3
                      ),
    gsSPNTriangles_5b(8, 26, 27, // tri0
                      5, 28, 29, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&boa_1_v[253], 4, 10),
    gsSPNTrianglesInit_5b(3,        // tri count
                          1, 9, 10, // tri0
                          9, 0, 11, // tri1
                          5, 12, 13 // tri2
                          ),
    gsSPVertex(&boa_1_v[257], 23, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 0,   // tri0
                      0, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      1, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(0, 8, 12,  // tri0
                      9, 14, 15, // tri1
                      15, 10, 9, // tri2
                      0, 12, 1   // tri3
                      ),
    gsSPNTriangles_5b(10, 16, 11, // tri0
                      11, 17, 9,  // tri1
                      11, 18, 17, // tri2
                      14, 19, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 20, 7,   // tri0
                      16, 10, 15, // tri1
                      5, 21, 22,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 24, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[280], 31, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      9, 10, 7, // tri1
                      9, 7, 6,  // tri2
                      11, 0, 5  // tri3
                      ),
    gsSPNTriangles_5b(2, 7, 10, // tri0
                      2, 10, 3, // tri1
                      2, 8, 7,  // tri2
                      1, 8, 2   // tri3
                      ),
    gsSPNTriangles_5b(8, 1, 12,  // tri0
                      13, 10, 9, // tri1
                      12, 1, 0,  // tri2
                      12, 0, 11  // tri3
                      ),
    gsSPNTriangles_5b(14, 3, 10,  // tri0
                      14, 4, 3,   // tri1
                      10, 13, 14, // tri2
                      0, 3, 4     // tri3
                      ),
    gsSPNTriangles_5b(9, 15, 13, // tri0
                      5, 16, 11, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          24, 22, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          25, 26, 27, // tri0
                          26, 25, 28, // tri1
                          26, 29, 27  // tri2
                          ),
    gsSPNTriangles_5b(29, 26, 28, // tri0
                      30, 25, 27, // tri1
                      25, 30, 28, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(30, 29, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&boa_1_v[311], 30, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 5, // tri0
                      3, 0, 2, // tri1
                      4, 1, 5, // tri2
                      1, 4, 2  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(8,         // tri count
                          6, 7, 8,   // tri0
                          9, 10, 11, // tri1
                          10, 9, 8   // tri2
                          ),
    gsSPNTriangles_5b(6, 9, 11,  // tri0
                      9, 6, 8,   // tri1
                      10, 7, 11, // tri2
                      7, 10, 8   // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 11, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          12, 13, 14, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          18, 19, 20, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          24, 25, 26, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          27, 28, 29, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[382], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[388], 14, 6),
    gsSPNTrianglesInit_5b(5,       // tri count
                          2, 4, 6, // tri0
                          0, 2, 7, // tri1
                          4, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 11, 10, // tri0
                      2, 12, 13, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,        // tri count
                          3, 5, 14, // tri0
                          5, 1, 15, // tri1
                          0, 0, 0   // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          16, 17, 18, // tri0
                          18, 17, 19, // tri1
                          16, 19, 17  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_boa_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[402], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[410], 13, 8),
    gsSPNTrianglesInit_5b(9,        // tri count
                          6, 8, 9,  // tri0
                          7, 4, 10, // tri1
                          5, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(2, 6, 13, // tri0
                      0, 2, 14, // tri1
                      3, 15, 5, // tri2
                      3, 16, 17 // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 18,  // tri0
                      2, 19, 20, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_boa_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[341], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[347], 14, 6),
    gsSPNTrianglesInit_5b(2,       // tri count
                          5, 3, 6, // tri0
                          1, 5, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,        // tri count
                          2, 8, 9,  // tri0
                          4, 2, 10, // tri1
                          2, 0, 11  // tri2
                          ),
    gsSPNTriangles_5b(4, 13, 12, // tri0
                      0, 15, 14, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          16, 17, 18, // tri0
                          19, 17, 16, // tri1
                          17, 19, 18  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_boa_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[361], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&boa_1_v[369], 13, 8),
    gsSPNTrianglesInit_5b(9,        // tri count
                          6, 8, 9,  // tri0
                          4, 2, 10, // tri1
                          4, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 13, // tri0
                      3, 6, 14, // tri1
                      2, 0, 15, // tri2
                      1, 3, 16  // tri3
                      ),
    gsSPNTriangles_5b(3, 17, 18, // tri0
                      2, 19, 20, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_boa_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&boa_1_v[423], 30, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      15, 16, 17, // tri2
                      5, 9, 3     // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 19, // tri0
                      20, 13, 12, // tri1
                      8, 7, 21,   // tri2
                      11, 3, 9    // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 15, // tri0
                      22, 15, 17, // tri1
                      20, 23, 13, // tri2
                      7, 24, 21   // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 25, // tri0
                      14, 26, 12, // tri1
                      8, 27, 6,   // tri2
                      21, 28, 8   // tri3
                      ),
    gsSPNTriangles_5b(12, 29, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_boa_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_boa_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 150,0,-850 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_boa_model, 3, cKF_JOINT_FLAG_DISP_OPA, 425,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,-500,0 },
    /* joint 15 */ { Larm1_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_boa_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,500,0 },
    /* joint 18 */ { Rarm1_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 875,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,1250 },
    /* joint 23 */ { mouth_boa_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_boa_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1245,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_boa_1 = { 26, 12, cKF_je_r_boa_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_boa_1_c(void) {
    pc_load_asset("assets/npc/mdl/boa_1_v.bin", boa_1_v, 0x1C50, 0x5586E8, 0, 2);
}
#endif
