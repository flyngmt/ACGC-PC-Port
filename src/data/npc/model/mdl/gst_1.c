#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx gst_1_v[0x1110 / sizeof(Vtx)];
#else
static Vtx gst_1_v[] = {
#include "assets/npc/mdl/gst_1_v.inc"
};
#endif

static Gfx head_gst_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, ENVIRONMENT, 0, COMBINED, 0, PRIM_LOD_FRAC, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 127, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gst_1_v[0], 13, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[13], 19, 13),
    gsSPNTrianglesInit_5b(13,         // tri count
                          10, 13, 14, // tri0
                          9, 1, 15,   // tri1
                          0, 7, 16    // tri2
                          ),
    gsSPNTriangles_5b(0, 18, 17, // tri0
                      6, 4, 19,  // tri1
                      2, 5, 20,  // tri2
                      3, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(2, 23, 1,   // tri0
                      0, 24, 4,   // tri1
                      11, 25, 26, // tri2
                      3, 6, 27    // tri3
                      ),
    gsSPNTriangles_5b(1, 29, 28, // tri0
                      5, 30, 31, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&gst_1_v[32], 15, 13),
    gsSPNTrianglesInit_5b(9,          // tri count
                          6, 13, 14,  // tri0
                          12, 15, 16, // tri1
                          8, 17, 18   // tri2
                          ),
    gsSPNTriangles_5b(8, 11, 19,  // tri0
                      12, 10, 20, // tri1
                      1, 21, 22,  // tri2
                      0, 23, 24   // tri3
                      ),
    gsSPNTriangles_5b(5, 3, 25,  // tri0
                      3, 26, 27, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[47], 13, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 4, // tri0
                      5, 6, 2, // tri1
                      3, 7, 8, // tri2
                      8, 9, 4  // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 8,  // tri0
                      4, 9, 5,  // tri1
                      2, 6, 10, // tri2
                      10, 11, 0 // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      0, 11, 12, // tri1
                      4, 5, 2,   // tri2
                      12, 7, 3   // tri3
                      ),
    gsSPNTriangles_5b(3, 0, 12, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[60], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      2, 8, 9,   // tri1
                      10, 11, 4, // tri2
                      11, 12, 5  // tri3
                      ),
    gsSPNTriangles_5b(5, 12, 13,  // tri0
                      14, 15, 16, // tri1
                      17, 18, 10, // tri2
                      11, 10, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      19, 21, 0,  // tri1
                      15, 14, 22, // tri2
                      22, 23, 15  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 25, // tri0
                      5, 4, 11,   // tri1
                      26, 16, 15, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      2, 30, 18,  // tri1
                      2, 18, 0,   // tri2
                      21, 20, 8   // tri3
                      ),
    gsSPVertex(&gst_1_v[91], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      5, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(12, 6, 5,  // tri0
                      7, 6, 12,  // tri1
                      3, 12, 11, // tri2
                      3, 11, 0   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 18, 20, // tri1
                      7, 12, 3,   // tri2
                      7, 21, 22   // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      23, 25, 26, // tri1
                      23, 15, 14, // tri2
                      27, 2, 28   // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 29, // tri0
                      30, 31, 16, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&gst_1_v[123], 21, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 5, // tri0
                      7, 8, 1, // tri1
                      4, 8, 7, // tri2
                      9, 10, 4 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 9, // tri0
                      12, 6, 11, // tri1
                      13, 14, 1, // tri2
                      15, 16, 17 // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[144], 19, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 2,  // tri0
                      9, 10, 4, // tri1
                      2, 8, 11, // tri2
                      12, 13, 0 // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 4, // tri0
                      2, 15, 0, // tri1
                      3, 8, 6,  // tri2
                      16, 15, 2 // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 6,  // tri0
                      11, 8, 3, // tri1
                      5, 11, 3, // tri2
                      2, 11, 16 // tri3
                      ),
    gsSPNTriangles_5b(17, 12, 15, // tri0
                      18, 4, 3,   // tri1
                      0, 15, 12,  // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(4, 10, 14, // tri0
                      4, 18, 9,  // tri1
                      3, 7, 18,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[163], 15, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 7,  // tri0
                      9, 2, 1,  // tri1
                      4, 3, 6,  // tri2
                      10, 11, 6 // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 4, // tri0
                      7, 6, 3,  // tri1
                      2, 10, 0, // tri2
                      6, 0, 10  // tri3
                      ),
    gsSPNTriangles_5b(5, 12, 3,  // tri0
                      7, 13, 0,  // tri1
                      12, 5, 14, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx feel_gst_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, ENVIRONMENT, 0, COMBINED, 0, PRIM_LOD_FRAC, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 20, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gst_1_v[178], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx chest_gst_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, ENVIRONMENT, 0, COMBINED, 0, PRIM_LOD_FRAC, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 127, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gst_1_v[182], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[192], 22, 10),
    gsSPNTrianglesInit_5b(14,        // tri count
                          8, 2, 10,  // tri0
                          6, 11, 12, // tri1
                          7, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 15, // tri0
                      5, 0, 16, // tri1
                      1, 9, 17, // tri2
                      3, 4, 18  // tri3
                      ),
    gsSPNTriangles_5b(3, 19, 20, // tri0
                      2, 3, 21,  // tri1
                      2, 22, 23, // tri2
                      4, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(3, 26, 27, // tri0
                      9, 28, 29, // tri1
                      1, 30, 31, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&gst_1_v[214], 6, 10),
    gsSPNTrianglesInit_5b(4,         // tri count
                          6, 5, 10,  // tri0
                          5, 11, 12, // tri1
                          8, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_gst_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, ENVIRONMENT, 0, COMBINED, 0, PRIM_LOD_FRAC, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 127, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gst_1_v[220], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gst_1_v[228], 20, 8),
    gsSPNTrianglesInit_5b(14,       // tri count
                          1, 0, 8,  // tri0
                          1, 9, 10, // tri1
                          6, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(4, 13, 14, // tri0
                      6, 7, 15,  // tri1
                      2, 1, 16,  // tri2
                      0, 6, 17   // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 18, // tri0
                      2, 19, 3, // tri1
                      5, 20, 7, // tri2
                      3, 21, 22 // tri3
                      ),
    gsSPNTriangles_5b(5, 23, 24, // tri0
                      4, 25, 26, // tri1
                      4, 3, 27,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&gst_1_v[248], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 4, // tri0
                      3, 6, 2, // tri1
                      2, 6, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_gst_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, PRIMITIVE, 0, ENVIRONMENT, 0, COMBINED, 0, PRIM_LOD_FRAC, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 127, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gst_1_v[255], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      9, 8, 6,  // tri1
                      1, 7, 2,  // tri2
                      10, 1, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 13, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      16, 4, 17   // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 13, // tri0
                      6, 3, 9,    // tri1
                      9, 2, 7,    // tri2
                      17, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 10, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_gst_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,1000,0 },
    /* joint 1 */ { base_gst_model, 4, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,-400,0 },
    /* joint 3 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 4 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,400,0 },
    /* joint 7 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 8 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 200,0,-800 },
    /* joint 11 */ { tail1_gst_model, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 650,0,0 },
    /* joint 13 */ { chest_gst_model, 3, cKF_JOINT_FLAG_DISP_XLU, 700,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 600,-1100,1050 },
    /* joint 15 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 16 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 500,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 600,1100,1050 },
    /* joint 18 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 19 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 501,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 499,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_XLU, 1200,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, 300,0,800 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 24 */ { head_gst_model, 1, cKF_JOINT_FLAG_DISP_XLU, 0,0,0 },
    /* joint 25 */ { feel_gst_model, 0, cKF_JOINT_FLAG_DISP_XLU, 1102,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_gst_1 = { 26, 5, cKF_je_r_gst_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_gst_1_c(void) {
    pc_load_asset("assets/npc/mdl/gst_1_v.bin", gst_1_v, 0x1110, 0x4FC948, 0, 2);
}
#endif
