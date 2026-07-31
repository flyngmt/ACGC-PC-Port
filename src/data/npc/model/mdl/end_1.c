#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx end_1_v[0x1C50 / sizeof(Vtx)];
#else
static Vtx end_1_v[] = {
#include "assets/npc/mdl/end_1_v.inc"
};
#endif

static Gfx head_end_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[0], 27, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      7, 6, 11,  // tri1
                      10, 9, 12, // tri2
                      12, 9, 13  // tri3
                      ),
    gsSPNTriangles_5b(7, 14, 15, // tri0
                      11, 14, 7, // tri1
                      10, 16, 8, // tri2
                      4, 7, 15   // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 10, // tri0
                      2, 10, 0,  // tri1
                      15, 17, 4, // tri2
                      5, 0, 12   // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 3,  // tri0
                      5, 13, 3,  // tri1
                      12, 13, 5, // tri2
                      12, 0, 10  // tri3
                      ),
    gsSPNTriangles_5b(7, 4, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          18, 19, 20, // tri0
                          21, 18, 22, // tri1
                          20, 23, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 18, // tri0
                      24, 18, 21, // tri1
                      25, 21, 22, // tri2
                      18, 24, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 26, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&end_1_v[27], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 6, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 11, 10, // tri2
                      14, 15, 1   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 5,  // tri0
                      18, 19, 20, // tri1
                      6, 5, 17,   // tri2
                      21, 8, 22   // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 8,    // tri0
                      23, 17, 16, // tri1
                      24, 25, 26, // tri2
                      27, 28, 16  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 3, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&end_1_v[58], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 13, // tri1
                      12, 14, 15, // tri2
                      2, 16, 17   // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 11, 22, // tri1
                      15, 23, 13, // tri2
                      5, 24, 3    // tri3
                      ),
    gsSPNTriangles_5b(13, 23, 25, // tri0
                      9, 12, 10,  // tri1
                      26, 27, 28, // tri2
                      29, 8, 30   // tri3
                      ),
    gsSPVertex(&end_1_v[89], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 1, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 5,  // tri0
                      8, 9, 10, // tri1
                      11, 9, 8, // tri2
                      12, 13, 3 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      12, 3, 16,  // tri1
                      17, 18, 19, // tri2
                      17, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 11, // tri0
                      19, 18, 24, // tri1
                      25, 8, 10,  // tri2
                      21, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(22, 28, 25, // tri0
                      29, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&end_1_v[121], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 3  // tri2
                          ),
    gsSPNTriangles_5b(8, 1, 9,    // tri0
                      10, 11, 12, // tri1
                      6, 13, 12,  // tri2
                      7, 6, 12    // tri3
                      ),
    gsSPNTriangles_5b(6, 3, 14,   // tri0
                      15, 16, 14, // tri1
                      4, 17, 8,   // tri2
                      12, 13, 10  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 10, 13, // tri1
                      7, 22, 20,  // tri2
                      23, 24, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 7,  // tri0
                      25, 26, 16, // tri1
                      4, 8, 9,    // tri2
                      22, 27, 18  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      28, 30, 31, // tri1
                      20, 22, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&end_1_v[153], 18, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 9,   // tri0
                      2, 7, 0,   // tri1
                      5, 8, 3,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 13, // tri0
                      14, 15, 16, // tri1
                      12, 11, 16, // tri2
                      12, 17, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 11, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[206], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[210], 17, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 4, // tri0
                          3, 1, 5, // tri1
                          2, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 7,   // tri0
                      2, 8, 9,   // tri1
                      1, 10, 11, // tri2
                      0, 12, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          14, 15, 16, // tri0
                          16, 17, 18, // tri1
                          19, 14, 20  // tri2
                          ),
    gsSPNTriangles_5b(20, 18, 19, // tri0
                      19, 18, 17, // tri1
                      15, 14, 19, // tri2
                      17, 15, 19  // tri3
                      ),
    gsSPNTriangles_5b(16, 20, 14, // tri0
                      18, 20, 16, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[227], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[230], 11, 3),
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

static Gfx Larm2_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[171], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[175], 17, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 4, // tri0
                          3, 2, 5, // tri1
                          2, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 7,   // tri0
                      2, 8, 9,   // tri1
                      1, 10, 11, // tri2
                      0, 12, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 15, // tri1
                          19, 20, 16  // tri2
                          ),
    gsSPNTriangles_5b(16, 20, 14, // tri0
                      16, 15, 18, // tri1
                      16, 18, 17, // tri2
                      17, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 19, 17, // tri0
                      17, 15, 20, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[192], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[195], 11, 3),
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

static Gfx chest_end_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[241], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[246], 21, 5),
    gsSPNTrianglesInit_5b(11,      // tri count
                          2, 5, 6, // tri0
                          0, 2, 7, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 10, 11, // tri0
                      1, 12, 3,  // tri1
                      1, 13, 14, // tri2
                      3, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 18, // tri0
                      4, 0, 19,  // tri1
                      1, 4, 20,  // tri2
                      2, 3, 21   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          22, 23, 24, // tri0
                          24, 25, 22, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx tail1_end_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[267], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 3, 4, // tri0
                      8, 2, 1, // tri1
                      1, 3, 8, // tri2
                      2, 4, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[332], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[335], 13, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 4, 3, // tri0
                          2, 5, 0, // tri1
                          2, 1, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 7,   // tri0
                      0, 9, 1,   // tri1
                      0, 11, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          12, 13, 14, // tri0
                          14, 13, 15, // tri1
                          15, 13, 12  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[348], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[352], 10, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 1, 4, // tri0
                          1, 0, 5, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 8,   // tri0
                      2, 10, 0,  // tri1
                      0, 12, 11, // tri2
                      2, 3, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_end_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[362], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[367], 23, 5),
    gsSPNTrianglesInit_5b(10,      // tri count
                          2, 0, 5, // tri0
                          3, 2, 6, // tri1
                          4, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      2, 10, 11, // tri1
                      1, 4, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 15,  // tri0
                      0, 16, 17, // tri1
                      1, 18, 19, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(7,          // tri count
                          20, 21, 22, // tri0
                          23, 24, 21, // tri1
                          23, 25, 24  // tri2
                          ),
    gsSPNTriangles_5b(24, 22, 21, // tri0
                      26, 25, 23, // tri1
                      24, 25, 27, // tri2
                      27, 22, 24  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[276], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[282], 14, 6),
    gsSPNTrianglesInit_5b(2,       // tri count
                          2, 6, 0, // tri0
                          0, 7, 5, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          1, 9, 8,   // tri0
                          4, 11, 10, // tri1
                          3, 4, 12   // tri2
                          ),
    gsSPNTriangles_5b(3, 14, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          17, 16, 18, // tri1
                          18, 16, 19  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_end_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[296], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[300], 14, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 5, 4, // tri0
                          2, 1, 6, // tri1
                          1, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 8,   // tri0
                      1, 11, 10, // tri1
                      0, 3, 12,  // tri2
                      3, 2, 13   // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 15, // tri0
                      2, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_end_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[314], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&end_1_v[319], 13, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          1, 5, 6, // tri0
                          2, 7, 8, // tri1
                          0, 2, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10, // tri0
                      2, 3, 11, // tri1
                      3, 4, 12, // tri2
                      4, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(4, 1, 15,  // tri0
                      3, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_end_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 92),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[390], 28, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 32, 40, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 28),
    gsSPNTrianglesInit_5b(4,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          20, 21, 22, // tri0
                          20, 22, 23, // tri1
                          24, 25, 26  // tri2
                          ),
    gsSPNTriangles_5b(24, 26, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&end_1_v[418], 21, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          4, 5, 6, // tri0
                          6, 7, 8, // tri1
                          6, 8, 4  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      9, 11, 12, // tri1
                      10, 8, 7,  // tri2
                      10, 7, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 5, 14,  // tri0
                      13, 14, 15, // tri1
                      16, 17, 18, // tri2
                      18, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 16,  // tri0
                      9, 16, 19,  // tri1
                      17, 20, 18, // tri2
                      15, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 13, // tri0
                      4, 14, 5,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&end_1_v[439], 14, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      9, 10, 7, // tri1
                      11, 2, 5, // tri2
                      5, 8, 3   // tri3
                      ),
    gsSPNTriangles_5b(2, 11, 0, // tri0
                      7, 3, 8,  // tri1
                      4, 11, 5, // tri2
                      6, 10, 9  // tri3
                      ),
    gsSPNTriangles_5b(6, 12, 13, // tri0
                      6, 13, 10, // tri1
                      9, 1, 6,   // tri2
                      12, 4, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_end_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_end_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_end_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_end_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { tail1_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_end_model, 3, cKF_JOINT_FLAG_DISP_OPA, 599,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,-500,0 },
    /* joint 15 */ { Larm1_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_end_model, 0, cKF_JOINT_FLAG_DISP_OPA, 700,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,500,0 },
    /* joint 18 */ { Rarm1_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 701,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 699,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 701,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 100,0,700 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_end_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_end_1 = { 26, 14, cKF_je_r_end_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_end_1_c(void) {
    pc_load_asset("assets/npc/mdl/end_1_v.bin", end_1_v, 0x1C50, 0x8D5848, 0, 2);
}
#endif
