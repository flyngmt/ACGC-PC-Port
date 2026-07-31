#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx fox_1_v[0x1700 / sizeof(Vtx)];
#else
static Vtx fox_1_v[] = {
#include "assets/npc/mdl/fox_1_v.inc"
};
#endif

static Gfx head_fox_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[22], 32, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 5,  // tri0
                      7, 5, 9,  // tri1
                      10, 2, 1, // tri2
                      1, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(0, 13, 1, // tri0
                      14, 5, 4, // tri1
                      5, 6, 3,  // tri2
                      15, 4, 3  // tri3
                      ),
    gsSPNTriangles_5b(16, 4, 15,  // tri0
                      8, 17, 18,  // tri1
                      11, 19, 20, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(17, 8, 7,   // tri0
                      24, 12, 20, // tri1
                      25, 3, 26,  // tri2
                      23, 22, 2   // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 11, // tri0
                      1, 13, 11,  // tri1
                      18, 24, 20, // tri2
                      27, 28, 8   // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 10,  // tri0
                      5, 14, 9,   // tri1
                      26, 28, 27, // tri2
                      28, 3, 6    // tri3
                      ),
    gsSPNTriangles_5b(17, 7, 29,  // tri0
                      20, 19, 27, // tri1
                      27, 19, 26, // tri2
                      15, 25, 13  // tri3
                      ),
    gsSPNTriangles_5b(2, 10, 23,  // tri0
                      23, 9, 14,  // tri1
                      30, 23, 10, // tri2
                      9, 23, 30   // tri3
                      ),
    gsSPNTriangles_5b(3, 25, 15,  // tri0
                      12, 24, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&fox_1_v[54], 29, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      4, 8, 9,   // tri1
                      7, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 1, // tri0
                      15, 1, 0,  // tri1
                      16, 3, 2,  // tri2
                      17, 8, 18  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      16, 20, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          23, 24, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          25, 26, 27, // tri0
                          27, 28, 25, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&fox_1_v[83], 20, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 3, // tri0
                      5, 0, 3, // tri1
                      4, 6, 7, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 15, 16, // tri0
                      11, 10, 17, // tri1
                      14, 15, 12, // tri2
                      17, 18, 11  // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[0], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[7], 15, 7),
    gsSPNTrianglesInit_5b(9,        // tri count
                          6, 7, 8,  // tri0
                          6, 4, 9,  // tri1
                          1, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 12, // tri0
                      4, 1, 13, // tri1
                      0, 5, 14, // tri2
                      5, 6, 15  // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 17, // tri0
                      1, 3, 18,  // tri1
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

static Gfx Rarm2_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[137], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[141], 16, 4),
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

static Gfx Rarm1_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[157], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[160], 11, 3),
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

static Gfx Larm2_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[103], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[107], 16, 4),
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

static Gfx Larm1_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[123], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[126], 11, 3),
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

static Gfx chest_fox_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[171], 11, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[182], 13, 11),
    gsSPNTrianglesInit_5b(9,         // tri count
                          7, 2, 11,  // tri0
                          2, 12, 13, // tri1
                          8, 14, 15  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 16,  // tri0
                      1, 17, 18, // tri1
                      9, 7, 19,  // tri2
                      10, 9, 20  // tri3
                      ),
    gsSPNTriangles_5b(7, 22, 21, // tri0
                      8, 10, 23, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&fox_1_v[195], 20, 11),
    gsSPNTrianglesInit_5b(8,         // tri count
                          3, 5, 11,  // tri0
                          4, 13, 12, // tri1
                          5, 14, 15  // tri2
                          ),
    gsSPNTriangles_5b(4, 16, 6,  // tri0
                      3, 17, 18, // tri1
                      4, 0, 19,  // tri2
                      6, 20, 5   // tri3
                      ),
    gsSPNTriangles_5b(0, 21, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          23, 24, 25, // tri0
                          25, 24, 26, // tri1
                          27, 28, 23  // tri2
                          ),
    gsSPNTriangles_5b(26, 29, 30, // tri0
                      25, 27, 23, // tri1
                      26, 30, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&fox_1_v[215], 12, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,  // tri0
                      1, 9, 6,  // tri1
                      3, 10, 4, // tri2
                      5, 4, 11  // tri3
                      ),
    gsSPNTriangles_5b(3, 8, 10, // tri0
                      6, 8, 3,  // tri1
                      2, 1, 5,  // tri2
                      6, 3, 1   // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_fox_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[264], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[267], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 4, // tri0
                          1, 0, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      2, 1, 10,  // tri1
                      0, 11, 12, // tri2
                      0, 2, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[227], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[231], 20, 4),
    gsSPNTrianglesInit_5b(12,      // tri count
                          2, 0, 4, // tri0
                          2, 5, 6, // tri1
                          1, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 3, 10,  // tri1
                      3, 11, 12, // tri2
                      3, 1, 13   // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 15, // tri0
                      0, 16, 17, // tri1
                      0, 18, 19, // tri2
                      2, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(3, 22, 23, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&fox_1_v[251], 13, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      6, 1, 0,  // tri1
                      8, 10, 9, // tri2
                      5, 4, 6   // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 3, // tri0
                      7, 11, 3,  // tri1
                      7, 5, 6,   // tri2
                      3, 5, 7    // tri3
                      ),
    gsSPNTriangles_5b(2, 10, 8,  // tri0
                      7, 0, 2,   // tri1
                      9, 12, 11, // tri2
                      2, 8, 7    // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[303], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[307], 14, 4),
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

static Gfx Rfoot1_fox_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[321], 7, 0),
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

static Gfx Lfoot2_fox_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[278], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fox_1_v[282], 14, 4),
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

static Gfx Lfoot1_fox_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[296], 7, 0),
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

static Gfx base_fox_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&fox_1_v[328], 26, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 2, 7, // tri0
                      7, 6, 8, // tri1
                      7, 5, 4, // tri2
                      2, 8, 0  // tri3
                      ),
    gsSPNTriangles_5b(5, 9, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(19,         // tri count
                          10, 11, 12, // tri0
                          13, 14, 15, // tri1
                          13, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      16, 20, 13, // tri1
                      21, 15, 22, // tri2
                      18, 15, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      23, 22, 24, // tri1
                      21, 23, 19, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 12, // tri0
                      14, 24, 22, // tri1
                      14, 22, 15, // tri2
                      16, 15, 18  // tri3
                      ),
    gsSPNTriangles_5b(23, 12, 19, // tri0
                      12, 23, 25, // tri1
                      12, 25, 10, // tri2
                      24, 25, 23  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&fox_1_v[354], 14, 0),
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
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_fox_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_fox_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-700 },
    /* joint 11 */ { tail1_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_fox_model, 0, cKF_JOINT_FLAG_DISP_OPA, 800,0,0 },
    /* joint 13 */ { chest_fox_model, 3, cKF_JOINT_FLAG_DISP_OPA, 425,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,-500,0 },
    /* joint 15 */ { Larm1_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_fox_model, 0, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,500,0 },
    /* joint 18 */ { Rarm1_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 875,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,1550 },
    /* joint 23 */ { mouth_fox_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_fox_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_fox_1 = { 26, 14, cKF_je_r_fox_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_fox_1_c(void) {
    pc_load_asset("assets/npc/mdl/fox_1_v.bin", fox_1_v, 0x1700, 0x465E28, 0, 2);
}
#endif
