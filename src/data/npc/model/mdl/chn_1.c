#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx chn_1_v[0x1C20 / sizeof(Vtx)];
#else
static Vtx chn_1_v[] = {
#include "assets/npc/mdl/chn_1_v.inc"
};
#endif

static Gfx head_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[11], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[19], 21, 8),
    gsSPNTrianglesInit_5b(14,       // tri count
                          6, 8, 9,  // tri0
                          6, 4, 10, // tri1
                          3, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 13,  // tri0
                      1, 14, 15, // tri1
                      1, 0, 16,  // tri2
                      7, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 19,  // tri0
                      0, 20, 21, // tri1
                      0, 7, 22,  // tri2
                      2, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 25,  // tri0
                      5, 26, 27, // tri1
                      5, 3, 28,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&chn_1_v[40], 27, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 2,   // tri0
                      7, 6, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(5, 2, 7,    // tri0
                      5, 7, 11,   // tri1
                      11, 10, 12, // tri2
                      8, 1, 0     // tri3
                      ),
    gsSPNTriangles_5b(15, 11, 7, // tri0
                      4, 8, 0,   // tri1
                      7, 8, 4,   // tri2
                      14, 13, 9  // tri3
                      ),
    gsSPNTriangles_5b(14, 0, 5,  // tri0
                      11, 12, 5, // tri1
                      5, 12, 14, // tri2
                      11, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 14, // tri0
                      11, 16, 9,  // tri1
                      9, 16, 14,  // tri2
                      0, 14, 15   // tri3
                      ),
    gsSPNTriangles_5b(7, 4, 3,  // tri0
                      15, 3, 0, // tri1
                      7, 3, 15, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          17, 18, 19, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          20, 21, 22, // tri0
                          22, 21, 23, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          24, 25, 26, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&chn_1_v[67], 23, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,       // tri count
                          5, 6, 7, // tri0
                          8, 9, 6, // tri1
                          6, 10, 8 // tri2
                          ),
    gsSPNTriangles_5b(6, 9, 7,   // tri0
                      8, 10, 11, // tri1
                      12, 7, 13, // tri2
                      14, 8, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          20, 21, 22, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&chn_1_v[90], 31, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 0, 8, // tri0
                      7, 8, 9, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          10, 11, 12, // tri0
                          12, 13, 14, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(11,         // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          21, 22, 17  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      20, 15, 18, // tri1
                      26, 27, 28, // tri2
                      25, 29, 23  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 26, // tri0
                      24, 23, 26, // tri1
                      17, 18, 15, // tri2
                      17, 16, 21  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&chn_1_v[121], 24, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 3, 9,   // tri0
                      10, 11, 2, // tri1
                      12, 13, 9, // tri2
                      2, 11, 0   // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 3,   // tri0
                      15, 13, 12, // tri1
                      9, 3, 12,   // tri2
                      7, 2, 1     // tri3
                      ),
    gsSPNTriangles_5b(8, 16, 4,  // tri0
                      12, 2, 15, // tri1
                      2, 12, 10, // tri2
                      10, 12, 3  // tri3
                      ),
    gsSPNTriangles_5b(3, 14, 10, // tri0
                      15, 2, 7,  // tri1
                      4, 3, 8,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(3,          // tri count
                          17, 18, 19, // tri0
                          19, 18, 20, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[0], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[4], 7, 4),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 4, // tri0
                          2, 6, 5, // tri1
                          0, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 9,  // tri0
                      3, 0, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[176], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[180], 15, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          1, 3, 6, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 10,  // tri0
                      2, 11, 0,  // tri1
                      3, 12, 13, // tri2
                      3, 0, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          15, 16, 17, // tri0
                          18, 15, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[195], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[198], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 3, // tri0
                          2, 0, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      1, 2, 9,   // tri1
                      2, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[145], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[149], 15, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          3, 1, 6, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 9, 10,  // tri0
                      0, 11, 2,  // tri1
                      3, 12, 13, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          15, 16, 17, // tri0
                          15, 17, 18, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[164], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[167], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 0, 3, // tri0
                          0, 2, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      2, 1, 9,   // tri1
                      2, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_chn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[207], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[214], 24, 7),
    gsSPNTrianglesInit_5b(15,      // tri count
                          3, 7, 8, // tri0
                          4, 9, 1, // tri1
                          5, 0, 10 // tri2
                          ),
    gsSPNTriangles_5b(2, 11, 12, // tri0
                      1, 13, 14, // tri1
                      0, 15, 16, // tri2
                      0, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(1, 19, 20, // tri0
                      2, 21, 22, // tri1
                      2, 23, 0,  // tri2
                      3, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 26, // tri0
                      2, 6, 27, // tri1
                      6, 3, 28, // tri2
                      1, 29, 30 // tri3
                      ),
    gsSPVertex(&chn_1_v[238], 17, 7),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 7, 8, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPNTrianglesInit_5b(13,         // tri count
                          9, 10, 11,  // tri0
                          12, 13, 14, // tri1
                          15, 11, 16  // tri2
                          ),
    gsSPNTriangles_5b(17, 12, 18, // tri0
                      19, 17, 20, // tri1
                      21, 22, 23, // tri2
                      21, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 16, 21, // tri0
                      16, 23, 15, // tri1
                      18, 20, 17, // tri2
                      20, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 9,  // tri0
                      14, 18, 12, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_chn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[255], 27, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 6, // tri0
                      7, 8, 4, // tri1
                      2, 9, 7, // tri2
                      10, 7, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          11, 12, 13, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(3,          // tri count
                          14, 15, 16, // tri0
                          16, 17, 18, // tri1
                          19, 20, 18  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          24, 25, 26, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&chn_1_v[282], 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[364], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[368], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 4, 5, // tri0
                          1, 6, 3, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 9,   // tri0
                      0, 3, 10,  // tri1
                      2, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,          // tri count
                          13, 14, 15, // tri0
                          16, 17, 15, // tri1
                          15, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(15, 18, 13, // tri0
                      15, 19, 20, // tri1
                      15, 20, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[388], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[393], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          3, 4, 7, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      4, 1, 11,  // tri1
                      3, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_chn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[407], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[411], 25, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 1, // tri1
                          0, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      2, 9, 10,  // tri1
                      1, 11, 12, // tri2
                      3, 2, 13   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          16, 20, 14  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 23, 24, // tri1
                      19, 25, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          26, 27, 28, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[292], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[296], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          3, 4, 5, // tri0
                          3, 6, 1, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 9,   // tri0
                      3, 0, 10,  // tri1
                      2, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,          // tri count
                          13, 14, 15, // tri0
                          13, 16, 17, // tri1
                          18, 16, 13  // tri2
                          ),
    gsSPNTriangles_5b(15, 18, 13, // tri0
                      19, 20, 13, // tri1
                      17, 19, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_chn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[316], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[321], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          4, 3, 7, // tri1
                          4, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 10,  // tri0
                      1, 4, 11,  // tri1
                      3, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_chn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[335], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&chn_1_v[339], 25, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 0, 4, // tri0
                          1, 5, 0, // tri1
                          0, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      2, 9, 10,  // tri1
                      1, 11, 12, // tri2
                      2, 3, 13   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          16, 20, 14  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 23, 24, // tri1
                      19, 25, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          26, 27, 28, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_chn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&chn_1_v[436], 14, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      10, 2, 7, // tri1
                      10, 0, 2, // tri2
                      4, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 13,  // tri0
                      4, 12, 13, // tri1
                      3, 5, 9,   // tri2
                      9, 8, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_chn_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_chn_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-700,0 },
    /* joint 3 */ { Lfoot1_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_chn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,700,0 },
    /* joint 7 */ { Rfoot1_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_chn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,-950 },
    /* joint 11 */ { tail1_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_chn_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,-1150,0 },
    /* joint 15 */ { Larm1_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_chn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,1150,0 },
    /* joint 18 */ { Rarm1_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 999,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 750,0,850 },
    /* joint 23 */ { mouth_chn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_chn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_chn_1 = { 26, 15, cKF_je_r_chn_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_chn_1_c(void) {
    pc_load_asset("assets/npc/mdl/chn_1_v.bin", chn_1_v, 0x1C20, 0x4859E0, 0, 2);
}
#endif
