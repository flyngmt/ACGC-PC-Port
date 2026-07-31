#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx xct_1_v[0x13B0 / sizeof(Vtx)];
#else
static Vtx xct_1_v[] = {
#include "assets/npc/mdl/xct_1_v.inc"
};
#endif

static Gfx head_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[0], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 92),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[6], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          1, 0, 6, // tri0
                          1, 7, 8, // tri1
                          3, 1, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 11, 10, // tri0
                      5, 4, 12,  // tri1
                      5, 13, 0,  // tri2
                      0, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(5, 16, 17, // tri0
                      4, 2, 18,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPVertex(&xct_1_v[19], 22, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      2, 4, 8, // tri1
                      3, 2, 9, // tri2
                      9, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      4, 1, 11,  // tri1
                      4, 11, 12, // tri2
                      13, 8, 4   // tri3
                      ),
    gsSPNTriangles_5b(4, 12, 13, // tri0
                      5, 10, 14, // tri1
                      8, 14, 10, // tri2
                      10, 7, 9   // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 5,  // tri0
                      9, 15, 16, // tri1
                      7, 6, 15,  // tri2
                      16, 3, 9   // tri3
                      ),
    gsSPNTriangles_5b(17, 0, 18, // tri0
                      19, 3, 16, // tri1
                      18, 3, 19, // tri2
                      18, 0, 3   // tri3
                      ),
    gsSPNTriangles_5b(20, 0, 17, // tri0
                      1, 21, 11, // tri1
                      20, 1, 0,  // tri2
                      20, 21, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 14, // tri0
                      7, 15, 9,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 60),
    gsSPVertex(&xct_1_v[41], 21, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 3, // tri0
                      6, 7, 5, // tri1
                      0, 8, 1, // tri2
                      6, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 7,   // tri0
                      8, 10, 11, // tri1
                      8, 0, 10,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(7,          // tri count
                          12, 13, 14, // tri0
                          15, 13, 12, // tri1
                          13, 16, 14  // tri2
                          ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      13, 17, 16, // tri1
                      19, 18, 17, // tri2
                      17, 20, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 60),
    gsSPVertex(&xct_1_v[62], 15, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 4, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 2, // tri0
                      4, 2, 7, // tri1
                      8, 3, 5, // tri2
                      4, 9, 6  // tri3
                      ),
    gsSPNTriangles_5b(4, 7, 9,  // tri0
                      6, 10, 5, // tri1
                      7, 2, 1,  // tri2
                      10, 11, 5 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      0, 13, 1,   // tri1
                      5, 11, 8,   // tri2
                      14, 0, 2    // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 14, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[113], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[119], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 6, 4, // tri0
                          1, 5, 7, // tri1
                          2, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 9,  // tri0
                      2, 0, 1,   // tri1
                      2, 11, 12, // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 0,  // tri0
                      3, 2, 15, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[132], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[136], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 4, // tri0
                          0, 5, 6, // tri1
                          1, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 10, // tri0
                      3, 1, 11, // tri1
                      1, 0, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[77], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[82], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          4, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 11,  // tri0
                      4, 2, 12,  // tri1
                      0, 13, 14, // tri2
                      0, 3, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 4, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          18, 17, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[98], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[102], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          2, 6, 7, // tri1
                          2, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,   // tri0
                      1, 11, 10, // tri1
                      0, 13, 12, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_xct_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[147], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 92),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[156], 22, 9),
    gsSPNTrianglesInit_5b(14,        // tri count
                          2, 10, 9,  // tri0
                          5, 11, 12, // tri1
                          6, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      8, 17, 18, // tri1
                      2, 19, 20, // tri2
                      7, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(3, 8, 23, // tri0
                      7, 0, 24, // tri1
                      5, 3, 25, // tri2
                      8, 4, 26  // tri3
                      ),
    gsSPNTriangles_5b(1, 7, 27,  // tri0
                      2, 28, 4,  // tri1
                      8, 29, 30, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&xct_1_v[178], 18, 9),
    gsSPNTrianglesInit_5b(3,         // tri count
                          1, 9, 2,   // tri0
                          7, 10, 11, // tri1
                          0, 6, 12   // tri2
                          ),
    gsSPNTrianglesInit_5b(6,          // tri count
                          13, 14, 15, // tri0
                          16, 17, 18, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(21, 15, 22, // tri0
                      23, 24, 16, // tri1
                      25, 14, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_xct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[220], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 3, // tri0
                      5, 7, 2, // tri1
                      2, 4, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[196], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[200], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 10, // tri0
                      2, 1, 11, // tri1
                      0, 3, 12, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          13, 14, 15, // tri0
                          16, 14, 17, // tri1
                          18, 17, 19  // tri2
                          ),
    gsSPNTriangles_5b(17, 14, 13, // tri0
                      13, 19, 17, // tri1
                      17, 18, 20, // tri2
                      21, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 22, 13, // tri0
                      19, 23, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[262], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[267], 20, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 6, 5, // tri0
                          0, 8, 7, // tri1
                          3, 2, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 10,  // tri0
                      0, 11, 12, // tri1
                      1, 0, 13,  // tri2
                      2, 1, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 22, // tri1
                          18, 23, 21  // tri2
                          ),
    gsSPNTriangles_5b(21, 24, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_xct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[287], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 3, // tri0
                      4, 7, 6, // tri1
                      7, 8, 5, // tri2
                      2, 3, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_xct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[228], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&xct_1_v[233], 20, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 0, 5, // tri0
                          2, 7, 6, // tri1
                          2, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 9,   // tri0
                      2, 10, 11, // tri1
                      0, 13, 12, // tri2
                      0, 4, 14   // tri3
                      ),
    gsSPNTriangles_5b(0, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 18, // tri1
                          20, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(18, 24, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_xct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[253], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 1, // tri0
                      4, 7, 3, // tri1
                      1, 0, 5, // tri2
                      4, 8, 7  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_xct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&xct_1_v[296], 19, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,    // tri0
                      8, 9, 6,    // tri1
                      10, 11, 12, // tri2
                      10, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 6,    // tri0
                      12, 11, 14, // tri1
                      9, 7, 6,    // tri2
                      15, 12, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      7, 9, 17,   // tri1
                      1, 6, 2,    // tri2
                      5, 16, 12   // tri3
                      ),
    gsSPNTriangles_5b(18, 10, 12, // tri0
                      6, 1, 8,    // tri1
                      17, 16, 7,  // tri2
                      12, 15, 18  // tri3
                      ),
    gsSPNTriangles_5b(7, 16, 5, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_xct_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_xct_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-475 },
    /* joint 11 */ { tail1_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_xct_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_xct_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_xct_model, 0, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_xct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1200,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_xct_1 = { 26, 13, cKF_je_r_xct_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_xct_1_c(void) {
    pc_load_asset("assets/npc/mdl/xct_1_v.bin", xct_1_v, 0x13B0, 0x512240, 0, 2);
}
#endif
