#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx rcn_1_v[0x1650 / sizeof(Vtx)];
#else
static Vtx rcn_1_v[] = {
#include "assets/npc/mdl/rcn_1_v.inc"
};
#endif

static Gfx head_rcn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[14], 28, 0),
    gsSPNTrianglesInit_5b(39,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 9, 1,  // tri0
                      10, 5, 4, // tri1
                      5, 6, 3,  // tri2
                      0, 4, 11  // tri3
                      ),
    gsSPNTriangles_5b(0, 11, 12, // tri0
                      4, 3, 11,  // tri1
                      13, 14, 4, // tri2
                      13, 4, 0   // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 16,  // tri0
                      17, 18, 19, // tri1
                      15, 8, 7,   // tri2
                      20, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 22, // tri0
                      12, 22, 23, // tri1
                      22, 11, 3,  // tri2
                      23, 9, 12   // tri3
                      ),
    gsSPNTriangles_5b(9, 23, 18, // tri0
                      9, 18, 17, // tri1
                      1, 9, 17,  // tri2
                      16, 20, 19 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 8,  // tri0
                      24, 22, 25, // tri1
                      25, 3, 6,   // tri2
                      25, 22, 3   // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 24, // tri0
                      24, 18, 23, // tri1
                      23, 22, 24, // tri2
                      4, 14, 10   // tri3
                      ),
    gsSPNTriangles_5b(2, 13, 0,   // tri0
                      8, 16, 24,  // tri1
                      16, 19, 24, // tri2
                      8, 25, 6    // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 17, // tri0
                      26, 27, 14, // tri1
                      26, 14, 13, // tri2
                      12, 9, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rcn_1_v[42], 31, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(4,        // tri count
                          6, 7, 8,  // tri0
                          8, 9, 10, // tri1
                          8, 10, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 11, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 253, 255, 255),
    gsSPNTrianglesInit_5b(3,          // tri count
                          12, 13, 14, // tri0
                          12, 15, 16, // tri1
                          14, 15, 12  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(5,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 21, // tri1
                          19, 22, 17  // tri2
                          ),
    gsSPNTriangles_5b(19, 21, 23, // tri0
                      23, 22, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetPrimColor(0, 128, 255, 253, 255, 255),
    gsSPNTrianglesInit_5b(5,          // tri count
                          24, 25, 26, // tri0
                          26, 27, 28, // tri1
                          28, 29, 26  // tri2
                          ),
    gsSPNTriangles_5b(26, 29, 24, // tri0
                      25, 30, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[73], 24, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 6, // tri0
                      7, 4, 5, // tri1
                      4, 3, 2, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17,         // tri count
                          8, 9, 10,   // tri0
                          11, 10, 12, // tri1
                          10, 11, 8   // tri2
                          ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 17, // tri1
                      14, 17, 18, // tri2
                      11, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(20, 8, 11,  // tri0
                      17, 21, 18, // tri1
                      19, 11, 22, // tri2
                      15, 14, 18  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 12, // tri0
                      22, 18, 21, // tri1
                      12, 22, 11, // tri2
                      12, 10, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 22, 12, // tri0
                      20, 23, 8,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[5], 9, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 5, 6, // tri0
                          2, 8, 7, // tri1
                          0, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 3, // tri0
                      4, 3, 11, // tri1
                      2, 0, 12, // tri2
                      1, 2, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[131], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[135], 16, 4),
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

static Gfx Rarm1_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[151], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[154], 11, 3),
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

static Gfx Larm2_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[97], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[101], 16, 4),
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

static Gfx Larm1_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[117], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[120], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 2, // tri0
                          1, 5, 4, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      1, 2, 12,  // tri2
                      0, 1, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_rcn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[165], 11, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[176], 13, 11),
    gsSPNTrianglesInit_5b(9,         // tri count
                          1, 3, 11,  // tri0
                          2, 13, 12, // tri1
                          3, 0, 14   // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 15,  // tri0
                      5, 16, 17, // tri1
                      5, 1, 18,  // tri2
                      1, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(9, 21, 22, // tri0
                      2, 9, 23,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rcn_1_v[189], 20, 11),
    gsSPNTrianglesInit_5b(8,         // tri count
                          10, 11, 4, // tri0
                          6, 12, 13, // tri1
                          7, 6, 14   // tri2
                          ),
    gsSPNTriangles_5b(8, 15, 16, // tri0
                      7, 18, 17, // tri1
                      7, 19, 10, // tri2
                      8, 4, 20   // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          23, 24, 25, // tri0
                          25, 26, 27, // tri1
                          23, 28, 24  // tri2
                          ),
    gsSPNTriangles_5b(26, 29, 27, // tri0
                      25, 30, 23, // tri1
                      27, 30, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rcn_1_v[209], 12, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 6, // tri0
                      0, 5, 8, // tri1
                      3, 0, 8, // tri2
                      9, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 0,  // tri0
                      10, 8, 9, // tri1
                      8, 11, 3, // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(0, 6, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_rcn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[246], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[250], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 4, 5, // tri0
                          1, 0, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 10,  // tri0
                      2, 1, 11,  // tri1
                      0, 12, 13, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[221], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[225], 21, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          0, 3, 6, // tri1
                          1, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 9,   // tri0
                      1, 2, 10,  // tri1
                      0, 11, 12, // tri2
                      3, 1, 13   // tri3
                      ),
    gsSPNTriangles_5b(2, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(12,         // tri count
                          16, 17, 18, // tri0
                          19, 17, 16, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 23, 16, // tri0
                      18, 21, 16, // tri1
                      16, 23, 19, // tri2
                      23, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 22, 21, // tri0
                      16, 21, 20, // tri1
                      24, 19, 23, // tri2
                      22, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[290], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[295], 15, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 0, 5, // tri0
                          0, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 10, // tri0
                      1, 2, 11, // tri1
                      2, 4, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 16, 15, // tri1
                          19, 17, 16  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_rcn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[310], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 2  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 4, // tri0
                      7, 4, 0, // tri1
                      0, 2, 7, // tri2
                      5, 8, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_rcn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[261], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rcn_1_v[266], 15, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 5, // tri0
                          0, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10, // tri0
                      2, 1, 11, // tri1
                      4, 2, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          17, 16, 18, // tri1
                          16, 15, 19  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_rcn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[281], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 7, // tri0
                      2, 4, 7, // tri1
                      7, 0, 2, // tri2
                      5, 8, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_rcn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&rcn_1_v[319], 24, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 6,  // tri0
                      5, 9, 10, // tri1
                      5, 10, 3, // tri2
                      6, 0, 2   // tri3
                      ),
    gsSPNTriangles_5b(11, 7, 12, // tri0
                      12, 3, 10, // tri1
                      7, 11, 13, // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 0, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(8,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          20, 14, 21  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 18, // tri0
                      18, 17, 20, // tri1
                      21, 22, 20, // tri2
                      16, 21, 14  // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rcn_1_v[343], 14, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8, // tri0
                      5, 7, 6, // tri1
                      4, 9, 5, // tri2
                      5, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      0, 4, 1,   // tri1
                      3, 9, 4,   // tri2
                      9, 3, 10   // tri3
                      ),
    gsSPNTriangles_5b(11, 7, 9, // tri0
                      11, 8, 7, // tri1
                      8, 12, 6, // tri2
                      6, 13, 2  // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 12, // tri0
                      6, 2, 1,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_rcn_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_rcn_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-700 },
    /* joint 11 */ { tail1_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_rcn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_rcn_model, 3, cKF_JOINT_FLAG_DISP_OPA, 425,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,-500,0 },
    /* joint 15 */ { Larm1_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_rcn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,500,0 },
    /* joint 18 */ { Rarm1_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 875,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,0,1785 },
    /* joint 23 */ { mouth_rcn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_rcn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1050,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_rcn_1 = { 26, 14, cKF_je_r_rcn_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_rcn_1_c(void) {
    pc_load_asset("assets/npc/mdl/rcn_1_v.bin", rcn_1_v, 0x1650, 0x667CA0, 0, 2);
}
#endif
