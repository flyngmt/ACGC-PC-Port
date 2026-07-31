#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx pgn_1_v[0x17E0 / sizeof(Vtx)];
#else
static Vtx pgn_1_v[] = {
#include "assets/npc/mdl/pgn_1_v.inc"
};
#endif

static Gfx head_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[13], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[22], 9, 9),
    gsSPNTrianglesInit_5b(6,         // tri count
                          0, 1, 9,   // tri0
                          1, 11, 10, // tri1
                          7, 0, 12   // tri2
                          ),
    gsSPNTriangles_5b(0, 14, 13, // tri0
                      1, 4, 15,  // tri1
                      4, 17, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pgn_1_v[31], 14, 9),
    gsSPNTrianglesInit_5b(9,         // tri count
                          5, 6, 9,   // tri0
                          6, 11, 10, // tri1
                          8, 13, 12  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 14,  // tri0
                      2, 8, 15,  // tri1
                      5, 16, 17, // tri2
                      2, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 20,  // tri0
                      2, 22, 21, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pgn_1_v[45], 16, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          3, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 0,  // tri0
                      6, 4, 7,  // tri1
                      6, 7, 8,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 12, // tri0
                      4, 3, 13,  // tri1
                      13, 7, 4,  // tri2
                      9, 0, 4    // tri3
                      ),
    gsSPNTriangles_5b(9, 4, 6,   // tri0
                      8, 14, 15, // tri1
                      8, 15, 6,  // tri2
                      6, 15, 10  // tri3
                      ),
    gsSPNTriangles_5b(6, 10, 9, // tri0
                      12, 1, 0, // tri1
                      12, 0, 9, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pgn_1_v[61], 31, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 7,  // tri0
                      8, 7, 9,  // tri1
                      9, 10, 8, // tri2
                      11, 0, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 1, 0,   // tri0
                      13, 14, 4,  // tri1
                      15, 14, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 0, 2,  // tri0
                      12, 0, 20, // tri1
                      13, 7, 8,  // tri2
                      13, 16, 14 // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 20, // tri0
                      20, 17, 21, // tri1
                      22, 16, 13, // tri2
                      23, 22, 13  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 24, // tri0
                      3, 7, 13,   // tri1
                      5, 18, 20,  // tri2
                      13, 4, 3    // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 20,  // tri0
                      6, 3, 2,   // tri1
                      6, 2, 1,   // tri2
                      12, 25, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 9,    // tri0
                      13, 8, 23,  // tri1
                      24, 12, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          26, 27, 28, // tri0
                          27, 26, 29, // tri1
                          30, 28, 27  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pgn_1_v[92], 23, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,         // tri count
                          8, 9, 10,  // tri0
                          11, 12, 8, // tri1
                          9, 8, 12   // tri2
                          ),
    gsSPNTriangles_5b(10, 13, 8, // tri0
                      8, 14, 11, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          15, 16, 17, // tri0
                          17, 18, 15, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          19, 20, 21, // tri0
                          21, 22, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[5], 8, 5),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 5, // tri0
                          2, 7, 6, // tri1
                          0, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 10, // tri0
                      3, 0, 11, // tri1
                      1, 4, 12, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[145], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[148], 15, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          1, 2, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      1, 10, 0,  // tri1
                      2, 11, 12, // tri2
                      2, 0, 13   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          14, 15, 16, // tri0
                          17, 14, 16, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[163], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[166], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          2, 3, 4, // tri0
                          1, 2, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,  // tri0
                      2, 0, 10, // tri1
                      0, 1, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[115], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[118], 15, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          2, 1, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      0, 10, 1,  // tri1
                      2, 11, 12, // tri2
                      0, 2, 13   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[133], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[136], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          2, 3, 4, // tri0
                          2, 1, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,  // tri0
                      0, 2, 10, // tri1
                      1, 0, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_pgn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[175], 11, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[186], 19, 11),
    gsSPNTrianglesInit_5b(13,        // tri count
                          1, 12, 11, // tri0
                          3, 0, 13,  // tri1
                          3, 14, 15  // tri2
                          ),
    gsSPNTriangles_5b(0, 17, 16, // tri0
                      0, 2, 18,  // tri1
                      9, 5, 19,  // tri2
                      7, 6, 20   // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 21,   // tri0
                      10, 23, 22, // tri1
                      6, 4, 24,   // tri2
                      6, 26, 25   // tri3
                      ),
    gsSPNTriangles_5b(5, 28, 27, // tri0
                      2, 1, 29,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&pgn_1_v[205], 5, 11),
    gsSPNTrianglesInit_5b(3,         // tri count
                          1, 9, 11,  // tri0
                          9, 13, 12, // tri1
                          4, 15, 14  // tri2
                          ),
    gsSPVertex(&pgn_1_v[210], 21, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 11, // tri2
                      1, 13, 12   // tri3
                      ),
    gsSPNTriangles_5b(14, 6, 4,  // tri0
                      1, 15, 2,  // tri1
                      4, 16, 14, // tri2
                      12, 15, 1  // tri3
                      ),
    gsSPNTriangles_5b(14, 8, 7,  // tri0
                      17, 16, 3, // tri1
                      3, 16, 4,  // tri2
                      17, 18, 16 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 19,  // tri0
                      15, 20, 19, // tri1
                      8, 10, 9,   // tri2
                      11, 13, 0   // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      7, 6, 14,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_pgn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[231], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[236], 14, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 2, 5, // tri0
                          0, 4, 6, // tri1
                          4, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 8,  // tri0
                      0, 10, 1, // tri1
                      2, 1, 11, // tri2
                      2, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[301], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[305], 18, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          2, 1, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 9,   // tri0
                      1, 0, 10,  // tri1
                      0, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          13, 14, 15, // tri0
                          16, 17, 13, // tri1
                          13, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      18, 20, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[323], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[328], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          2, 3, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      4, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_pgn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[342], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 0, 8, // tri0
                      6, 9, 4, // tri1
                      0, 7, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[250], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[254], 18, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          1, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 9,   // tri0
                      0, 1, 10,  // tri1
                      0, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          13, 14, 15, // tri0
                          15, 16, 17, // tri1
                          17, 13, 15  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      18, 20, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_pgn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[272], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pgn_1_v[277], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          3, 2, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 10,  // tri0
                      1, 4, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_pgn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[291], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 3, 8, // tri0
                      6, 9, 4, // tri1
                      2, 8, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_pgn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pgn_1_v[352], 30, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 6,   // tri0
                      9, 10, 11, // tri1
                      11, 12, 9, // tri2
                      9, 0, 10   // tri3
                      ),
    gsSPNTriangles_5b(1, 13, 8, // tri0
                      10, 0, 2, // tri1
                      7, 14, 6, // tri2
                      6, 14, 2  // tri3
                      ),
    gsSPNTriangles_5b(8, 2, 1,  // tri0
                      5, 7, 3,  // tri1
                      7, 5, 12, // tri2
                      7, 12, 11 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18,         // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          21, 22, 15  // tri2
                          ),
    gsSPNTriangles_5b(20, 23, 18, // tri0
                      24, 15, 17, // tri1
                      21, 18, 23, // tri2
                      21, 25, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 25, // tri0
                      22, 21, 26, // tri1
                      17, 27, 24, // tri2
                      15, 22, 16  // tri3
                      ),
    gsSPNTriangles_5b(22, 26, 28, // tri0
                      26, 29, 28, // tri1
                      28, 16, 22, // tri2
                      20, 29, 26  // tri3
                      ),
    gsSPNTriangles_5b(20, 26, 23, // tri0
                      15, 24, 21, // tri1
                      23, 26, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_pgn_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_pgn_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-700,0 },
    /* joint 3 */ { Lfoot1_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_pgn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,700,0 },
    /* joint 7 */ { Rfoot1_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_pgn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, -200,0,-1200 },
    /* joint 11 */ { tail1_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_pgn_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,-1650,0 },
    /* joint 15 */ { Larm1_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_pgn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,1650,0 },
    /* joint 18 */ { Rarm1_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 651,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 649,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1500,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 400,0,1300 },
    /* joint 23 */ { mouth_pgn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_pgn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 950,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_pgn_1 = { 26, 15, cKF_je_r_pgn_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_pgn_1_c(void) {
    pc_load_asset("assets/npc/mdl/pgn_1_v.bin", pgn_1_v, 0x17E0, 0x610D68, 0, 2);
}
#endif
