#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx seg_1_v[0x1860 / sizeof(Vtx)];
#else
static Vtx seg_1_v[] = {
#include "assets/npc/mdl/seg_1_v.inc"
};
#endif

static Gfx head_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 24, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 92),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[21], 30, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 0, // tri0
                      7, 3, 0, // tri1
                      7, 0, 2, // tri2
                      0, 6, 1  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 4,  // tri0
                      4, 9, 6,  // tri1
                      7, 10, 3, // tri2
                      10, 5, 3  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          11, 12, 13, // tri0
                          11, 13, 14, // tri1
                          14, 15, 11  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17,         // tri count
                          16, 17, 18, // tri0
                          16, 19, 20, // tri1
                          17, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 20, 24, // tri0
                      23, 25, 26, // tri1
                      27, 23, 28, // tri2
                      24, 25, 23  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 16, // tri0
                      18, 19, 16, // tri1
                      22, 18, 17, // tri2
                      24, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 21, 25, // tri0
                      21, 17, 26, // tri1
                      26, 25, 21, // tri2
                      26, 17, 29  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 27, // tri0
                      27, 16, 23, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&seg_1_v[51], 27, 0),
    gsSPNTrianglesInit_5b(39,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 0,   // tri0
                      6, 7, 1,   // tri1
                      8, 4, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      16, 7, 6,   // tri1
                      17, 18, 19, // tri2
                      5, 17, 6    // tri3
                      ),
    gsSPNTriangles_5b(9, 4, 2,   // tri0
                      15, 14, 8, // tri1
                      4, 20, 21, // tri2
                      4, 21, 5   // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 20,  // tri0
                      9, 22, 23, // tri1
                      1, 5, 6,   // tri2
                      7, 16, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 22, // tri0
                      19, 18, 25, // tri1
                      10, 24, 16, // tri2
                      23, 24, 10  // tri3
                      ),
    gsSPNTriangles_5b(9, 23, 15, // tri0
                      3, 26, 0,  // tri1
                      21, 17, 5, // tri2
                      23, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 16, // tri0
                      19, 16, 6,  // tri1
                      11, 16, 19, // tri2
                      25, 11, 19  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 15, // tri0
                      15, 23, 12, // tri1
                      19, 6, 17,  // tri2
                      8, 9, 15    // tri3
                      ),
    gsSPNTriangles_5b(2, 22, 9, // tri0
                      5, 0, 26, // tri1
                      26, 3, 4, // tri2
                      4, 5, 26  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&seg_1_v[78], 24, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 8,  // tri0
                      5, 7, 9,  // tri1
                      4, 0, 2,  // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 5, 9,  // tri0
                      12, 1, 0,  // tri1
                      13, 10, 8, // tri2
                      7, 6, 14   // tri3
                      ),
    gsSPNTriangles_5b(13, 7, 10,  // tri0
                      10, 14, 11, // tri1
                      2, 1, 13,   // tri2
                      13, 1, 9    // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 13,  // tri0
                      14, 10, 7, // tri1
                      15, 3, 8,  // tri2
                      9, 1, 12   // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 15, // tri0
                      2, 13, 8,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          18, 19, 16, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          20, 21, 22, // tri0
                          22, 23, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*15, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[5], 16, 5),
    gsSPNTrianglesInit_5b(6,       // tri count
                          2, 4, 5, // tri0
                          3, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 10,  // tri0
                      1, 0, 11,  // tri1
                      0, 13, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          19, 18, 20  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[145], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[149], 26, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 3, 4, // tri0
                          0, 5, 6, // tri1
                          2, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      0, 1, 12,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,         // tri count
                          2, 13, 14, // tri0
                          3, 2, 15,  // tri1
                          2, 16, 17  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          18, 19, 20, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          24, 22, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(3,          // tri count
                          25, 26, 27, // tri0
                          27, 28, 25, // tri1
                          25, 29, 26  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[175], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[178], 10, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,       // tri count
                          3, 4, 5, // tri0
                          5, 6, 7, // tri1
                          8, 9, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 9, // tri0
                      4, 3, 8, // tri1
                      7, 3, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[102], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[106], 26, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          3, 1, 4, // tri0
                          0, 5, 6, // tri1
                          0, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      1, 0, 12,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,         // tri count
                          2, 13, 14, // tri0
                          2, 3, 15,  // tri1
                          2, 16, 17  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          18, 19, 20, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          23, 22, 24, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(3,          // tri count
                          25, 26, 27, // tri0
                          27, 28, 25, // tri1
                          26, 29, 27  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[132], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[135], 10, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,       // tri count
                          3, 4, 5, // tri0
                          6, 7, 3, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 6, // tri0
                      9, 5, 4, // tri1
                      3, 5, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_seg_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[188], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[197], 20, 9),
    gsSPNTrianglesInit_5b(2,        // tri count
                          2, 9, 3,  // tri0
                          5, 4, 10, // tri1
                          0, 0, 0   // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,         // tri count
                          8, 11, 12, // tri0
                          8, 5, 13,  // tri1
                          4, 3, 14   // tri2
                          ),
    gsSPNTriangles_5b(3, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,         // tri count
                          8, 17, 18, // tri0
                          6, 8, 19,  // tri1
                          2, 1, 20   // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 21,  // tri0
                      1, 23, 22, // tri1
                      0, 24, 25, // tri2
                      0, 7, 26   // tri3
                      ),
    gsSPNTriangles_5b(4, 28, 27, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&seg_1_v[217], 25, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 4, 3,    // tri0
                      9, 2, 1,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 3   // tri3
                      ),
    gsSPNTriangles_5b(2, 14, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          15, 16, 17, // tri0
                          18, 16, 19, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&seg_1_v[242], 15, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1,   // tri0
                      6, 1, 5,   // tri1
                      7, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_seg_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[270], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[273], 6, 3),
    gsSPNTrianglesInit_5b(4,       // tri count
                          1, 0, 3, // tri0
                          0, 2, 4, // tri1
                          1, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[257], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[260], 10, 3),
    gsSPNTrianglesInit_5b(4,       // tri count
                          1, 2, 3, // tri0
                          0, 4, 5, // tri1
                          2, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(2,         // tri count
                          9, 10, 11, // tri0
                          11, 12, 9, // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[326], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[329], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          1, 0, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 7,   // tri0
                      2, 8, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      16, 20, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[347], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[351], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 9,   // tri0
                      2, 10, 11, // tri1
                      2, 3, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[365], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6, // tri0
                      4, 7, 3, // tri1
                      0, 5, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[279], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[282], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 1, 5, // tri1
                          2, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      1, 2, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      17, 20, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_seg_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[300], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&seg_1_v[304], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 3, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,   // tri0
                      2, 10, 11, // tri1
                      3, 2, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[318], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 6, // tri0
                      0, 7, 4, // tri1
                      2, 6, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_seg_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&seg_1_v[373], 17, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 5,  // tri0
                      6, 7, 8,  // tri1
                      4, 7, 6,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 12, // tri0
                      10, 8, 11, // tri1
                      13, 9, 12, // tri2
                      10, 14, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 6,  // tri0
                      1, 0, 15,  // tri1
                      15, 9, 13, // tri2
                      15, 0, 14  // tri3
                      ),
    gsSPNTriangles_5b(9, 15, 14, // tri0
                      0, 6, 14,  // tri1
                      9, 14, 10, // tri2
                      15, 13, 5  // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 15,   // tri0
                      6, 0, 4,    // tri1
                      12, 16, 13, // tri2
                      5, 16, 3    // tri3
                      ),
    gsSPNTriangles_5b(16, 5, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_seg_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_seg_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_seg_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_seg_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,-650 },
    /* joint 11 */ { tail1_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_seg_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_seg_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,-500,0 },
    /* joint 15 */ { Larm1_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_seg_model, 0, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,500,0 },
    /* joint 18 */ { Rarm1_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 998,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1274,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,0,1350 },
    /* joint 23 */ { mouth_seg_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_seg_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1601,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_seg_1 = { 26, 16, cKF_je_r_seg_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_seg_1_c(void) {
    pc_load_asset("assets/npc/mdl/seg_1_v.bin", seg_1_v, 0x1860, 0x4C3DC0, 0, 2);
}
#endif
