#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx elp_1_v[0x17C0 / sizeof(Vtx)];
#else
static Vtx elp_1_v[] = {
#include "assets/npc/mdl/elp_1_v.inc"
};
#endif

static Gfx head_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[27], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[33], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          5, 6, 3, // tri0
                          1, 7, 8, // tri1
                          0, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(2, 11, 12, // tri0
                      3, 13, 2,  // tri1
                      3, 14, 15, // tri2
                      2, 16, 0   // tri3
                      ),
    gsSPNTriangles_5b(0, 17, 1, // tri0
                      1, 18, 4, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&elp_1_v[46], 26, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      12, 10, 9, // tri1
                      0, 13, 1,  // tri2
                      2, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(12, 9, 16,  // tri0
                      17, 18, 19, // tri1
                      18, 20, 21, // tri2
                      18, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 23, 20, // tri0
                      24, 9, 25,  // tri1
                      5, 6, 8,    // tri2
                      11, 25, 9   // tri3
                      ),
    gsSPNTriangles_5b(8, 3, 5,    // tri0
                      2, 15, 0,   // tri1
                      21, 22, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&elp_1_v[72], 24, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 0, 3, // tri0
                      9, 7, 6, // tri1
                      5, 6, 3, // tri2
                      5, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 6,  // tri0
                      11, 12, 1, // tri1
                      11, 1, 13, // tri2
                      2, 4, 0    // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 2, // tri0
                      3, 0, 4,  // tri1
                      3, 7, 8,  // tri2
                      8, 13, 0  // tri3
                      ),
    gsSPNTriangles_5b(13, 1, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          19, 18, 20  // tri2
                          ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      16, 22, 14, // tri1
                      16, 21, 20, // tri2
                      20, 22, 16  // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPVertex(&elp_1_v[96], 21, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 6,  // tri0
                      7, 8, 6,  // tri1
                      9, 7, 10, // tri2
                      4, 11, 5  // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 11,  // tri0
                      6, 8, 4,   // tri1
                      12, 7, 6,  // tri2
                      13, 11, 14 // tri3
                      ),
    gsSPNTriangles_5b(10, 15, 9, // tri0
                      6, 16, 12, // tri1
                      8, 7, 9,   // tri2
                      8, 9, 14   // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 11,  // tri0
                      15, 17, 9,  // tri1
                      17, 18, 14, // tri2
                      1, 16, 6    // tri3
                      ),
    gsSPNTriangles_5b(9, 17, 14,  // tri0
                      14, 18, 13, // tri1
                      19, 20, 1,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&elp_1_v[117], 16, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 0  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 3,  // tri0
                      9, 3, 10, // tri1
                      4, 3, 9,  // tri2
                      3, 11, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 12, 1,  // tri0
                      5, 1, 11,  // tri1
                      11, 1, 13, // tri2
                      13, 1, 0   // tri3
                      ),
    gsSPNTriangles_5b(3, 8, 10,  // tri0
                      14, 10, 8, // tri1
                      1, 12, 15, // tri2
                      3, 5, 11   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 2, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[5], 22, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 2, 5, // tri0
                          0, 1, 6, // tri1
                          4, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(4, 8, 3,   // tri0
                      0, 9, 10,  // tri1
                      0, 11, 12, // tri2
                      2, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(6,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 22, // tri1
                          21, 23, 22  // tri2
                          ),
    gsSPNTriangles_5b(22, 24, 20, // tri0
                      25, 20, 24, // tri1
                      23, 21, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[169], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[174], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 6, // tri0
                          0, 1, 7, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 10,  // tri0
                      1, 4, 11,  // tri1
                      3, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 0, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[190], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[194], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 1, 4, // tri0
                          2, 5, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 9, 10,  // tri0
                      1, 0, 11,  // tri1
                      1, 13, 12, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[133], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[138], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 6, // tri0
                          1, 0, 7, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 10,  // tri0
                      4, 1, 11,  // tri1
                      3, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[154], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[158], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 2, 4, // tri0
                          2, 5, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 9,   // tri0
                      0, 1, 10,  // tri1
                      1, 12, 11, // tri2
                      0, 13, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_elp_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[205], 28, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 7,  // tri0
                      2, 7, 8,  // tri1
                      9, 10, 3, // tri2
                      9, 3, 11  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 10, // tri0
                      8, 10, 9, // tri1
                      11, 3, 5, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(14,         // tri count
                          12, 13, 14, // tri0
                          12, 15, 13, // tri1
                          16, 14, 13  // tri2
                          ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      13, 18, 16, // tri1
                      20, 21, 15, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      19, 23, 22, // tri1
                      24, 25, 22, // tri2
                      26, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(20, 27, 26, // tri0
                      22, 17, 19, // tri1
                      15, 12, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&elp_1_v[233], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 2, // tri0
                      2, 6, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_elp_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[266], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 2, // tri0
                      6, 4, 5, // tri1
                      7, 0, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[240], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[244], 22, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,   // tri0
                      3, 2, 10,  // tri1
                      3, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(11,         // tri count
                          13, 14, 15, // tri0
                          15, 16, 13, // tri1
                          17, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 15, 21, // tri0
                      22, 19, 18, // tri1
                      21, 15, 14, // tri2
                      16, 15, 23  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 24, // tri0
                      18, 25, 22, // tri1
                      21, 14, 25, // tri2
                      25, 18, 21  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[315], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[320], 17, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          0, 7, 8, // tri1
                          2, 10, 9 // tri2
                          ),
    gsSPNTriangles_5b(1, 11, 0, // tri0
                      4, 2, 12, // tri1
                      1, 4, 13, // tri2
                      1, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 3, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          20, 18, 17, // tri1
                          17, 21, 20  // tri2
                          ),
    gsSPNTriangles_5b(19, 18, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_elp_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[337], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[343], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          1, 3, 6, // tri0
                          2, 1, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 9,   // tri0
                      0, 5, 10,  // tri1
                      1, 12, 11, // tri2
                      0, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      5, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_elp_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[274], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[279], 17, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          2, 8, 7, // tri1
                          0, 9, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 10,  // tri0
                      4, 1, 11,  // tri1
                      1, 12, 13, // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 16, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          19, 18, 20, // tri1
                          20, 21, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 18, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_elp_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[296], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&elp_1_v[302], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 3, 6, // tri0
                          3, 1, 7, // tri1
                          1, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10,  // tri0
                      2, 11, 12, // tri1
                      0, 13, 14, // tri2
                      1, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 17, // tri0
                      2, 5, 18, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_elp_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&elp_1_v[356], 24, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      8, 7, 10, // tri1
                      9, 3, 7,  // tri2
                      3, 1, 7   // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 4, // tri0
                      10, 6, 5, // tri1
                      10, 5, 8, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(10,         // tri count
                          12, 13, 14, // tri0
                          15, 14, 13, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(14, 19, 12, // tri0
                      14, 17, 19, // tri1
                      20, 21, 22, // tri2
                      23, 22, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 23, 15, // tri0
                      22, 23, 20, // tri1
                      19, 17, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_elp_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_elp_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-375,0 },
    /* joint 3 */ { Lfoot1_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,375,0 },
    /* joint 7 */ { Rfoot1_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 50,0,-625 },
    /* joint 11 */ { tail1_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_elp_model, 0, cKF_JOINT_FLAG_DISP_OPA, 475,0,0 },
    /* joint 13 */ { chest_elp_model, 3, cKF_JOINT_FLAG_DISP_OPA, 501,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,-700,0 },
    /* joint 15 */ { Larm1_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_elp_model, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,700,0 },
    /* joint 18 */ { Rarm1_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1076,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,1800 },
    /* joint 23 */ { mouth_elp_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_elp_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1323,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_elp_1 = { 26, 14, cKF_je_r_elp_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_elp_1_c(void) {
    pc_load_asset("assets/npc/mdl/elp_1_v.bin", elp_1_v, 0x17C0, 0x4D5670, 0, 2);
}
#endif
