#include "m_design_ovl.h"

#include "m_debug.h"
#include "padmgr.h"

#include "libultra/libultra.h"
#include "audio.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_needlework_ovl.h"
#include "m_editEndChk_ovl.h"

#define mDE_POS_MIN 0
#define mDE_POS_MAX 31
#define mDE_DESIGN_TEXELS (mNW_ORIGINAL_DESIGN_WIDTH * mNW_ORIGINAL_DESIGN_HEIGHT)

#define mDE_POS2TEXEL(x, y) ((((x) & 7) + ((y) & 7) * 8 + ((((x) & 0x18) >> 3) + (((y) & 0x18) >> 3) * 4) * 0x40) >> 1)

u16 mDE_SinCosTBL[] = {
    0,    6,    12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,   97,   103,  109,
    115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,  181,  185,  189,  193,  197,  201,
    205,  209,  212,  216,  219,  222,  225,  228,  231,  234,  236,  238,  241,  243,  244,  246,  248,  249,  251,
    252,  253,  254,  254,  255,  255,  255,  256,  255,  255,  255,  254,  254,  253,  252,  251,  249,  248,  246,
    244,  243,  241,  238,  236,  234,  231,  228,  225,  222,  219,  216,  212,  209,  205,  201,  197,  193,  189,
    185,  181,  176,  171,  167,  162,  157,  152,  147,  142,  136,  131,  126,  120,  115,  109,  103,  97,   92,
    86,   80,   74,   68,   62,   56,   49,   43,   37,   31,   25,   18,   12,   6,    0,    -6,   -12,  -18,  -25,
    -31,  -37,  -43,  -49,  -56,  -62,  -68,  -74,  -80,  -86,  -92,  -97,  -103, -109, -115, -120, -126, -131, -136,
    -142, -147, -152, -157, -162, -167, -171, -176, -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219,
    -222, -225, -228, -231, -234, -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255,
    -255, -255, -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238, -236,
    -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185, -181, -176, -171, -167,
    -162, -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103, -97,  -92,  -86,  -80,  -74,  -68,  -62,
    -56,  -49,  -43,  -37,  -31,  -25,  -18,  -12,  -6,   0,    6,    12,   18,   25,   31,   37,   43,   49,   56,
    62,   68,   74,   80,   86,   92,   97,   103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,
    167,  171,  176,  181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
    236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255
};

// clang-format off
u8 mDE_pen_2[] = {
    1,1,
    1,1,
};

u8 mDE_pen_3[] = {
    1,1,1,
    1,1,1,
    1,1,1,
};

u8 mDE_heart[] = {
    0,1,1,1,0,0,0,0,1,1,1,0,
    1,1,1,1,1,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,1,1,1,1,0,0,
    0,0,0,1,1,1,1,1,1,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_star[] = {
    0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,1,1,1,1,0,0,
    0,0,0,1,1,1,1,1,1,0,0,0,
    0,0,1,1,1,1,1,1,1,1,0,0,
    0,0,1,1,1,0,0,1,1,1,0,0,
    0,1,1,1,0,0,0,0,1,1,1,0,
    0,1,1,0,0,0,0,0,0,1,1,0,
};

u8 mDE_circle[] = {
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,1,1,0,0,0,0,1,1,0,0,
    0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,0,0,0,0,0,0,0,0,1,0,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,0,0,0,0,0,0,0,0,1,0,
    0,0,1,1,0,0,0,0,1,1,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
};

u8 mDE_square[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,
};

u8 mDE_kao1[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,1,0,0,0,0,1,0,0,0,
    0,0,1,0,0,0,1,1,1,1,0,0,
    0,0,1,0,0,1,1,1,1,1,0,0,
    0,0,1,0,0,1,1,1,1,1,0,0,
    0,0,1,0,0,1,1,1,1,1,0,0,
    0,0,1,0,0,1,1,1,1,1,0,0,
    0,0,1,0,0,0,1,1,1,1,0,0,
    0,0,0,1,0,0,0,0,1,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_kao2[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,1,1,1,0,0,0,0,
    0,0,0,1,1,1,1,1,1,0,0,0,
    0,0,0,0,1,0,0,1,1,0,0,0,
    0,0,0,0,1,0,0,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,0,0,0,
    0,0,0,0,1,1,1,0,1,0,0,0,
    0,0,0,0,1,1,1,0,1,0,0,0,
    0,0,0,0,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_kao3[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,0,0,0,0,
    0,0,0,0,1,0,0,0,1,0,0,0,
    0,0,0,1,0,1,1,1,0,1,0,0,
    0,0,0,1,0,1,1,1,0,1,0,0,
    0,0,0,1,0,1,1,1,0,1,0,0,
    0,0,0,1,0,1,1,1,0,1,0,0,
    0,0,0,0,1,0,0,0,1,0,0,0,
    0,0,0,1,0,1,1,1,0,1,0,0,
    0,0,0,1,0,0,1,0,0,1,0,0,
    0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_kao4[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_kao5[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,0,0,0,1,0,0,
    0,0,0,1,0,0,0,0,1,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 mDE_paint_mizutama[0x100] = { 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0, 
    0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0, 
    0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 
};

u8 mDE_paint_mask_cat_mask[0x400] = {  
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1, 
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1, 
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 
};
// clang-format on

mDE_Ovl_c de_ovl_data;

#define MDE_SIN(x) (mDE_SinCosTBL[(x)])
#define MDE_COS(x) (mDE_SinCosTBL[(x) + 0x40])
#define MDE_90DEG (0x40)
enum {
    mDE_MOVE_DIR_UP,
    mDE_MOVE_DIR_DOWN,
    mDE_MOVE_DIR_LEFT,
    mDE_MOVE_DIR_RIGHT,

    mDE_MOVE_DIR_NUM
};

void mDE_setup_action(mDE_Ovl_c* design_ovl, int param_2);

#define mDE_EXTRACT_COMPONENT(c, s, b) (((c) & (((1 << (b)) - 1)) << (s)) >> (s))

static void mDE_pallet_RGB5A3_to_RGB24(mDE_Ovl_c* design_ovl) {
    int i;

    for (i = 0; i < mNW_PALETTE_COUNT; i++) {
        u16 color = design_ovl->palette_p[i];

        if (color & 0x8000) {
            // fully opaque, a1r5g5b5
            // design_ovl->rgb8_pal[i].r = (((color >> 10) & 0x1F) * 255) / 31;
            // design_ovl->rgb8_pal[i].g = (((color >> 5) & 0x1F) * 255) / 31;
            // design_ovl->rgb8_pal[i].b = (((color >> 0) & 0x1F) * 255) / 31;
            design_ovl->rgb8_pal[i].r = (mDE_EXTRACT_COMPONENT(color, 10, 5) * 255) / 31;
            design_ovl->rgb8_pal[i].g = (mDE_EXTRACT_COMPONENT(color,  5, 5) * 255) / 31;
            design_ovl->rgb8_pal[i].b = (mDE_EXTRACT_COMPONENT(color,  0, 5) * 255) / 31;
        } else {
            // transparent color, a3r4g4b4
            // design_ovl->rgb8_pal[i].r = ((color >> 8) & 0xF) * 17;
            // design_ovl->rgb8_pal[i].g = ((color >> 4) & 0xF) * 17;
            // design_ovl->rgb8_pal[i].b = ((color >> 0) & 0xF) * 17;
            design_ovl->rgb8_pal[i].r = mDE_EXTRACT_COMPONENT(color, 8, 4) * 17;
            design_ovl->rgb8_pal[i].g = mDE_EXTRACT_COMPONENT(color, 4, 4) * 17;
            design_ovl->rgb8_pal[i].b = mDE_EXTRACT_COMPONENT(color, 0, 4) * 17;
        }
    }
}

static u8 mDE_judge_stick(mDE_Ovl_c* design_ovl) {
    design_ovl->_6B8++;
    if (design_ovl->move_pR >= 0.1f && design_ovl->_6B5 == 0) {
        design_ovl->_6B5 = 1;
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->move_pR > 0.9f && design_ovl->_6C0 >= design_ovl->_6C4 && design_ovl->_6B5 &&
        design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
    }

    return FALSE;
}

static int mDE_judge_stick_full(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR >= 0.9f) {
        design_ovl->_6C0++;
        if (design_ovl->_6C0 > design_ovl->_6C4) {
            design_ovl->_6C0 = design_ovl->_6C4;
        }

        return TRUE;
    }

    return FALSE;
}

static int mDE_judge_stick_nuetral(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR < 0.1f) {
        design_ovl->_6C0 = 0;
        design_ovl->_6B4 = 0;
        design_ovl->_6B5 = 0;
        return TRUE;
    }

    design_ovl->_6B4 = 1;
    return FALSE;
}

static int mDE_cursor_move_check(mDE_Ovl_c* design_ovl, int move_dir) {
    int min = 0;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_PEN) {
        switch (design_ovl->_6A0) {
            case 1:
                min = 1;
                break;
            case 2:
                min = 2;
                break;
        }
    }

    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (gamePT->pads[PAD0].now.stick_y > 0 && design_ovl->cursor_y > min) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (gamePT->pads[PAD0].now.stick_y < 0 && design_ovl->cursor_y < mDE_POS_MAX) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (gamePT->pads[PAD0].now.stick_x < 0 && design_ovl->cursor_x > 0) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (gamePT->pads[PAD0].now.stick_x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - min)) {
                return TRUE;
            }
            break;
    }

    return FALSE;
}

static void mDE_cursor_move(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            design_ovl->cursor_y--;
            design_ovl->_654 += 5;
            break;
        case mDE_MOVE_DIR_DOWN:
            design_ovl->cursor_y++;
            design_ovl->_654 -= 5;
            break;
        case mDE_MOVE_DIR_LEFT:
            design_ovl->cursor_x--;
            design_ovl->_650 -= 5;
            break;
        case mDE_MOVE_DIR_RIGHT:
            design_ovl->cursor_x++;
            design_ovl->_650 += 5;
            break;
    }
}

static void mDE_cursor_analog_move_hosei(f32* move_x, f32* move_y, f32 corrected_val, f32 min, f32 max) {
    if (*move_y > min && *move_y < max) {
        *move_y = corrected_val;
    }

    if (*move_y > -max && *move_y < -min) {
        *move_y = -corrected_val;
    }

    if (*move_x > min && *move_x < max) {
        *move_x = corrected_val;
    }

    if (*move_x > -max && *move_x < -min) {
        *move_x = -corrected_val;
    }
}

static void mDE_cursor_analog_move(mDE_Ovl_c* design_ovl) {
    int bounds = 0;
    f32 move_x;
    f32 move_y;
    int _660;
    int _664;
    int x;
    int y;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_PEN) {
        switch (design_ovl->_6A0) {
            case 1:
                bounds = 1;
                break;
            case 2:
                bounds = 2;
                break;
        }
    }

    _660 = (int)(design_ovl->_660 / 5.0f);
    _664 = -(int)(design_ovl->_664 / 5.0f);
    move_x = gamePT->pads[PAD0].now.stick_x / 72.0f;
    move_y = gamePT->pads[PAD0].now.stick_y / 72.0f;
    // _664 = -_664;

    if (!GETREG(NMREG, 16)) {
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.5f, 0.44f, 0.56f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.75f, 0.725f, 0.775f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.25f, 0.225f, 0.275f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.8f, 0.775f, 0.825f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.2f, 0.175f, 0.225f);
    }

    if (gamePT->pads[PAD0].now.stick_y != 0) {
        move_x *= 10.0f;
    } else {
        move_x *= 5.0f;
    }

    if (gamePT->pads[PAD0].now.stick_x != 0) {
        move_y *= 10.0f;
    } else {
        move_y *= 5.0f;
    }

    if (_664 < bounds) {
        design_ovl->cursor_y = bounds;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    } else if (_664 > mDE_POS_MAX) {
        design_ovl->cursor_y = mDE_POS_MAX;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    }

    if (_660 < 0) {
        design_ovl->cursor_x = 0;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    } else if (_660 > (mDE_POS_MAX - bounds)) {
        design_ovl->cursor_x = mDE_POS_MAX - bounds;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    }

    y = gamePT->pads[PAD0].now.stick_y;
    if ((y > 0 && design_ovl->cursor_y > bounds) || (y < 0 && design_ovl->cursor_y < mDE_POS_MAX)) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (5.0f / 72.0f);
            } else {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_664 += move_y;
        }
    }

    x = gamePT->pads[PAD0].now.stick_x;
    if ((x < 0 && design_ovl->cursor_x > 0) || (x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - bounds))) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (5.0f / 72.0f);
            } else {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_660 += move_x;
        }
    }
}

static int mDE_cursor_waku_genten_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    if (design_ovl->cursor_y == design_ovl->_67C && design_ovl->cursor_x == design_ovl->_678) {
        switch (move_dir) {
            case 4:
                if (design_ovl->_6D9 == 2) {
                    design_ovl->_6D8 = 1;
                    return TRUE;
                }
                break;
            case 5:
                if (design_ovl->_6D9 == 3) {
                    design_ovl->_6D8 = 0;
                    return TRUE;
                }
                break;
            case 6:
                if (design_ovl->_6D9 == 0) {
                    design_ovl->_6D8 = 3;
                    return TRUE;
                }
                break;
            case 7:
                if (design_ovl->_6D9 == 1) {
                    design_ovl->_6D8 = 2;
                    return TRUE;
                }
                break;
        }
    }

    return FALSE;
}

static int mDE_cursor_waku_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 0 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 0:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 3;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 3)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 0;
                        break;
                    case 3:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 0)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 3;
                        break;
                    case 0:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 3 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 3:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 0;
                        break;
                }

                return TRUE;
            }
            break;
    }

    return FALSE;
}

static int mDE_get_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y) {
    int idx;

    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return 0;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        return (design_ovl->work_texture.data[idx] >> 0) & 0x0F;
    } else {
        return (design_ovl->work_texture.data[idx] >> 4) & 0x0F;
    }
}

static void mDE_set_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y, int pal) {
    int idx;

    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        design_ovl->work_texture.data[idx] &= 0xF0;
        design_ovl->work_texture.data[idx] |= (pal << 0);
    } else {
        design_ovl->work_texture.data[idx] &= 0x0F;
        design_ovl->work_texture.data[idx] |= (pal << 4);
    }
}

typedef struct design_bounds_s {
    int x0;
    int x1;
    int y0;
    int y1;
} mDE_bounds_c;

#define mDE_DESIGN_TEXELS_2 (16 * 16)

static void mDE_farbado(mDE_Ovl_c* designOvl, int startX, int startY, int fillColor) {
    mDE_bounds_c scanStack[mDE_DESIGN_TEXELS_2];
    int stackReadIdx = 0;
    int stackWriteIdx = 1;
    int targetColor;
    mDE_bounds_c* scan4;
    mDE_bounds_c* scan3;
    mDE_bounds_c* scan2;
    mDE_bounds_c* scan;
    int adjScanX3;
    int adjScanX2;
    int adjScanX; // Used as X iterator for adjacent lines, or holds lineY for new stack entry's seedLineY (for line above)
    int iterX;
    // int adjLineY;
    int lineX0;         // Current line's start X, extended left during scan
    int lineX1;         // Current line's end X, extended right during scan
    int lineY;          // Current line's Y
    int lineY2;
    int seedLineY;      // Y of the line that seeded the currentLine; reassigned in one path
    int searchBoundX0;  // lineX0 - 1, limit for leftward scan on adjacent lines
    int searchBoundX1;  // lineX1 + 1, limit for rightward scan on adjacent lines; reassigned in one path

    scanStack[0].x0 = startX;
    scanStack[0].x1 = startX;
    scanStack[0].y0 = startY;
    scanStack[0].y1 = startY; // The initial seed Y is the start Y itself
    targetColor = mDE_get_pal_on_cursor(designOvl, startX, startY);

    do {
        const mDE_bounds_c* const currentLine = &scanStack[stackReadIdx];
        lineX0 = currentLine->x0;
        lineX1 = currentLine->x1;
        lineY = currentLine->y0;
        lineY2 = currentLine->y0;
        seedLineY = currentLine->y1;      // Y of the line that generated this currentLine
        searchBoundX0 = lineX0 - 1;     // Boundary for searching left on adjacent lines
        searchBoundX1 = lineX1 + 1;     // Boundary for searching right on adjacent lines

        if (++stackReadIdx == mDE_DESIGN_TEXELS_2) {
            stackReadIdx = 0;
        }

        // Check if the original line segment still needs processing (e.g. if targetColor is what we want to change)
        // Note: The problem statement uses `pal` (fillColor) in the condition,
        // which implies it's checking if the start of the scanline is NOT the fillColor already.
        // A typical flood fill checks against targetColor.
        // Adhering to original logic:
        if (fillColor != mDE_get_pal_on_cursor(designOvl, lineX0, lineY)) {
            // Scan right to find the end of the segment of targetColor
            while (lineX1 < mDE_POS_MAX + 1) {
                lineX1++;
                if (targetColor != mDE_get_pal_on_cursor(designOvl, lineX1, lineY)) {
                    lineX1--;
                    break;
                }
            }

            // Scan left to find the start of the segment of targetColor
            while (lineX0 > 0) {
                lineX0--;
                if (targetColor != mDE_get_pal_on_cursor(designOvl, lineX0, lineY)) {
                    lineX0++;
                    break;
                }
            }

            // Fill the identified segment with the new color
            for (iterX = lineX0; iterX <= lineX1; iterX++) {
                mDE_set_pal_on_cursor(designOvl, iterX, lineY, fillColor);
            }

            // Process line above
            // adjLineY = lineY - 1;
            // adjLineY = lineY;
            if (--lineY >= mDE_POS_MIN) { // Check if line above is within bounds
                if (lineY == seedLineY) { // Came from line above, now looking further above
                    // mDE_bounds_c* scan;
                    adjScanX = lineX0; //iterX = lineX0;
                    iterX = lineY + 1; // adjScanX now effectively stores lineY (current line's Y) to be seed for new stack entry
                    
                    while (adjScanX <= searchBoundX0) { // Scan left of the original lineX0
                        for (; adjScanX < searchBoundX0; adjScanX++) {
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX, lineY)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY)) {
                            break;
                        }

                        scan = &scanStack[stackWriteIdx];
                        scan->x0 = adjScanX;
                        for (; adjScanX <= searchBoundX0; adjScanX++) { // Corrected from original r23 to searchBoundX0
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY)) {
                                break;
                            }
                        }
                        scan->x1 = adjScanX - 1;
                        scan->y0 = lineY;
                        scan->y1 = iterX; // Store lineY as the seeder Y
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }

                    // issue is here, adjScanX should be r17 and scan should be r18
                    adjScanX2 = searchBoundX1; // Start scan from right of original lineX1
                    iterX = lineY + 1; // adjScanX stores lineY

                    while (adjScanX2 <= lineX1) { // Scan right part (relative to original lineX1)
                        for (; adjScanX2 < lineX1; adjScanX2++) { // Corrected from original r26 to lineX1
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX2, lineY)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX2, lineY)) {
                            break;
                        }

                        scan = &scanStack[stackWriteIdx];
                        scan->x0 = adjScanX2;
                        for (; adjScanX2 <= lineX1; adjScanX2++) { // Corrected from original r26 to lineX1
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX2, lineY)) {
                                break;
                            }
                        }
                        scan->x1 = adjScanX2 - 1;
                        scan->y0 = lineY;
                        scan->y1 = iterX; // Store lineY
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }
                } else { // Generic scan for the line above
                    // mDE_bounds_c* scan;
                    adjScanX3 = lineX0; // adjScanX stores lineY
                    iterX = lineY + 1;

                    while (adjScanX3 <= lineX1) {
                        for (; adjScanX3 < lineX1; adjScanX3++) { // Corrected from original r26 to lineX1
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX3, lineY)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX3, lineY)) {
                            break;
                        }

                        scan = &scanStack[stackWriteIdx];
                        scan->x0 = adjScanX3;
                        for (; adjScanX3 <= lineX1; adjScanX3++) { // Corrected from original r26 to lineX1
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX3, lineY)) {
                                break;
                            }
                        }
                        scan->x1 = adjScanX3 - 1;
                        scan->y0 = lineY;
                        scan->y1 = iterX; // Store lineY
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }
                }
            }

            // Process line below
            // adjLineY = lineY + 1;
            // adjLineY = lineY2;
            if (++lineY2 <= (mDE_POS_MAX + 1)) { // Check if line below is within bounds
                if (lineY2 == seedLineY) { // Came from line below, now looking further below
                    // mDE_bounds_c* scan;
                    adjScanX = lineX0;
                    seedLineY = lineY2 - 1; // seedLineY is reassigned to lineY (current line's Y)

                    while (adjScanX <= searchBoundX0) { // Scan left of original lineX0
                        for (; adjScanX < searchBoundX0; adjScanX++) {
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                            break;
                        }
                        scan4 = &scanStack[stackWriteIdx];
                        scan4->x0 = adjScanX;
                        // Original code had r26 here, which is lineX1. Assuming scan should go up to searchBoundX0 or similar limit.
                        // Sticking to original logic as much as possible, r26 (lineX1) is used.
                        for (; adjScanX <= searchBoundX0; adjScanX++) {
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        scan4->x1 = adjScanX - 1;
                        scan4->y0 = lineY2;
                        scan4->y1 = seedLineY; // Store reassigned seedLineY (which is lineY)
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }

                    adjScanX = searchBoundX1; // Start scan from right of original lineX1
                    // searchBoundX1 (r22) is reassigned here in original code
                    searchBoundX1 = lineY2 - 1; // searchBoundX1 now effectively stores lineY

                    while (adjScanX <= lineX1) {
                        for (; adjScanX < lineX1; adjScanX++) {
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                            break;
                        }
                        
                        scan3 = &scanStack[stackWriteIdx];
                        scan3->x0 = adjScanX;
                        for (; adjScanX <= lineX1; adjScanX++) {
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        scan3->x1 = adjScanX - 1;
                        scan3->y0 = lineY2;
                        scan3->y1 = searchBoundX1; // Store reassigned searchBoundX1 (which is lineY)
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }
                } else { // Generic scan for the line below
                    // mDE_bounds_c* scan;
                    adjScanX = lineX0;
                    searchBoundX1 = lineY2 - 1; // searchBoundX1 now effectively stores lineY
                    // searchBoundX1 (r22) is reassigned here in original code for the .y1 field

                    while (adjScanX <= lineX1) {
                        for (; adjScanX < lineX1; adjScanX++) {
                            if (targetColor == mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                            break;
                        }
                        scan2 = &scanStack[stackWriteIdx];
                        scan2->x0 = adjScanX;
                        for (; adjScanX <= lineX1; adjScanX++) {
                            if (targetColor != mDE_get_pal_on_cursor(designOvl, adjScanX, lineY2)) {
                                break;
                            }
                        }
                        scan2->x1 = adjScanX - 1;
                        scan2->y0 = lineY2;
                        scan2->y1 = searchBoundX1; // Store reassigned searchBoundX1 (which is lineY)
                        stackWriteIdx++;
                        if (stackWriteIdx == mDE_DESIGN_TEXELS_2) {
                            stackWriteIdx = 0;
                        }
                    }
                }
            }
        }
    } while (stackReadIdx != stackWriteIdx);
}

void mDE_set_texture_template(mDE_Ovl_c* design_ovl, u8* param_2, int offsetX, int offsetY, int param_5, int param_6,
                              int param_7, int param_8) {
    int i;
    for (i = 0; i < param_5 * param_6; i++) {
        int y = offsetY + (i / param_5) - param_8;
        int x = offsetX + (i % param_6) - param_7;
        if (param_2[i]) {
            mDE_set_pal_on_cursor(design_ovl, x, y, design_ovl->_6A4);
        }
    }
}

void mDE_mask_cat_mask(mDE_Ovl_c* design_ovl) {
    int i;
    for (i = 0; i < ARRAY_COUNT(mDE_paint_mask_cat_mask); i++) {
        int y = i / 32;
        int x = i % 32;
        if (mDE_paint_mask_cat_mask[i]) {
            mDE_set_pal_on_cursor(design_ovl, x, y, 0);
        }
    }
}

void mDE_paint(mDE_Ovl_c* design_ovl, int pal) {
    int i;
    int j;
    switch (design_ovl->_6A1) {
        case 0: {
            mDE_farbado(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_6A4);
        } break;
        case 1: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((i / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 2: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((j / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 3: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((i / 4) % 2 == 0 || (j / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 4: {
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x10, 0x00, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00);
        } break;
        default: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                }
            }
        } break;
    }
}

void mDE_print_texture() {
    return;
}

void mDE_save_maskcat_texture(mDE_Ovl_c* design_ovl) {
    int i, j;
    for (i = 0; i < 0x20; i++) {
        for (j = 0; j < 0x20; j++) {
            if (mDE_get_pal_on_cursor(design_ovl, i, j) == 0) {
                mDE_set_pal_on_cursor(design_ovl, i, j, 0xf);
            }
        }
    }
}

void mDE_set_undo_texture(mDE_Ovl_c* design_ovl) {
    bcopy(&design_ovl->work_texture, &design_ovl->undo_texture, sizeof(design_ovl->work_texture));
}

void mDE_undo(mDE_Ovl_c* design_ovl) {
    design_ovl->_6DA = !design_ovl->_6DA;
    if (design_ovl->_6DA) {
        sAdo_SysTrgStart(0x45b);
    } else {
        sAdo_SysTrgStart(0x45c);
    }
    bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->work_texture));
    bcopy(&design_ovl->undo_texture, &design_ovl->work_texture, sizeof(design_ovl->undo_texture));
    bcopy(&design_ovl->texture, &design_ovl->undo_texture, sizeof(design_ovl->texture));
}

#ifdef MOUSE_INPUT
    #define GET_BUTTON_PRESSED(b, m) chkTrigger(b) || (pc_mouse_button_pressed() & m)
    #define GET_BUTTON_HELD(b, m) chkButton(b) || (pc_mouse_button_held() & m)
#else
    #define GET_BUTTON_PRESSED(b, m) chkTrigger(b)
    #define GET_BUTTON_HELD(b, m) chkButton(b)
#endif

void mDE_main_pen_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 0;
    design_ovl->_698 = 1;
#ifdef MOUSE_INPUT
    int current_x = design_ovl->cursor_x;
    int current_y = design_ovl->cursor_y;
#endif

    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        design_ovl->_6CC = 1;
        mDE_set_undo_texture(design_ovl);
#ifdef MOUSE_INPUT
        design_ovl->prev_cursor_x = current_x;
        design_ovl->prev_cursor_y = current_y;
#endif
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
    } else if (GET_BUTTON_HELD(BUTTON_A, 1 << 0) && design_ovl->_6CC) {
        mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
#ifndef MOUSE_INPUT
        switch (design_ovl->_6A0) {
            case 1: {
                mDE_set_texture_template(design_ovl, mDE_pen_2, design_ovl->cursor_x, design_ovl->cursor_y, 2, 2, 0, 1);
            } break;
            case 2: {
                mDE_set_texture_template(design_ovl, mDE_pen_3, design_ovl->cursor_x, design_ovl->cursor_y, 3, 3, 0, 2);
            } break;
            default: {
                mDE_set_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_6A4);
            } break;
        }
#else
        int prev_x = design_ovl->prev_cursor_x;
        int prev_y = design_ovl->prev_cursor_y;
        
        if (prev_x == -1 || prev_y == -1) {
            prev_x = current_x;
            prev_y = current_y;
        }
        
        // Calculate steps for interpolation (Manhattan)
        int dx = current_x - prev_x;
        int dy = current_y - prev_y;
        int steps = ABS(dx) + ABS(dy);

        if (steps > 1 && pc_mouse_button_held() & (1 << 0)) {
            // Interpolate between previous and current positions then draw
            for (int step = 1; step <= steps; step++) {
                int interp_x = prev_x + (dx * step) / steps;
                int interp_y = prev_y + (dy * step) / steps;

                switch (design_ovl->_6A0) {
                    case 1: {
                        mDE_set_texture_template(design_ovl, mDE_pen_2, interp_x, interp_y, 2, 2, 0, 1);
                    } break;
                    case 2: {
                        mDE_set_texture_template(design_ovl, mDE_pen_3, interp_x, interp_y, 3, 3, 0, 2);
                    } break;
                    default: {
                        mDE_set_pal_on_cursor(design_ovl, interp_x, interp_y, design_ovl->_6A4);
                    } break;
                }
            }
        } else {
            switch (design_ovl->_6A0) {
                case 1: {
                    mDE_set_texture_template(design_ovl, mDE_pen_2, current_x, current_y, 2, 2, 0, 1);
                } break;
                case 2: {
                    mDE_set_texture_template(design_ovl, mDE_pen_3, current_x, current_y, 3, 3, 0, 2);
                } break;
                default: {
                    mDE_set_pal_on_cursor(design_ovl, current_x, current_y, design_ovl->_6A4);
                } break;
            }
        }

        design_ovl->prev_cursor_x = current_x;
        design_ovl->prev_cursor_y = current_y;
#endif
    }
#ifdef MOUSE_INPUT
    else {
        if (design_ovl->_6CC) {
            design_ovl->_6CC = 0;
            design_ovl->prev_cursor_x = -1;
            design_ovl->prev_cursor_y = -1;
        }
    }
#endif

    switch (design_ovl->_6A0) {
        case 1: {
            if (design_ovl->cursor_y == mDE_POS_MIN) {
                mDE_cursor_move(design_ovl, 1);
            }
            if (design_ovl->cursor_x == mDE_POS_MAX) {
                mDE_cursor_move(design_ovl, 2);
            }
            design_ovl->_680 = design_ovl->_650;
            switch (design_ovl->cursor_x) {
                case mDE_POS_MAX: {
                    design_ovl->_688 = 1;
                } break;
                default: {
                    design_ovl->_688 = 2;
                } break;
            }
            switch (design_ovl->cursor_y) {
                case mDE_POS_MIN: {
                    design_ovl->_68C = 1;
                    design_ovl->_684 = design_ovl->_654;
                } break;
                default: {
                    design_ovl->_68C = 2;
                    design_ovl->_684 = design_ovl->_654 + 5;
                } break;
            }
        } break;
        case 2: {
            if (design_ovl->cursor_y == mDE_POS_MIN) {
                mDE_cursor_move(design_ovl, 1);
                mDE_cursor_move(design_ovl, 1);
            } else if (design_ovl->cursor_y == mDE_POS_MIN + 1) {
                mDE_cursor_move(design_ovl, 1);
            }
            if (design_ovl->cursor_x == mDE_POS_MAX) {
                mDE_cursor_move(design_ovl, 2);
                mDE_cursor_move(design_ovl, 2);
            } else if (design_ovl->cursor_x == mDE_POS_MAX - 1) {
                mDE_cursor_move(design_ovl, 2);
            }
            design_ovl->_680 = design_ovl->_650;
            switch (design_ovl->cursor_x) {
                case mDE_POS_MAX: {
                    design_ovl->_688 = 1;
                } break;
                case mDE_POS_MAX - 1: {
                    design_ovl->_688 = 2;
                } break;
                default: {
                    design_ovl->_688 = 3;
                } break;
            }
            switch (design_ovl->cursor_y) {
                case mDE_POS_MIN: {
                    design_ovl->_68C = 1;
                    design_ovl->_684 = design_ovl->_654;
                } break;
                case mDE_POS_MIN + 1: {
                    design_ovl->_68C = 2;
                    design_ovl->_684 = design_ovl->_654 + 5;
                } break;
                default: {
                    design_ovl->_68C = 3;
                    design_ovl->_684 = design_ovl->_654 + 10;
                } break;
            }
        } break;
        default: {
            design_ovl->_680 = design_ovl->_650;
            design_ovl->_684 = design_ovl->_654;
            design_ovl->_688 = 1;
            design_ovl->_68C = 1;
        } break;
    }
}

void mDE_main_nuri_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 1;
    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        sAdo_SysTrgStart(0x455);
        mDE_set_undo_texture(design_ovl);
        mDE_paint(design_ovl, design_ovl->_6A4);
    }
}

void mDE_waku_set_start(mDE_Ovl_c* design_ovl) {
    if (design_ovl->_678 > design_ovl->cursor_x) {
        design_ovl->_680 = design_ovl->_650;
    } else {
        design_ovl->_680 = design_ovl->_658;
    }
    if (design_ovl->_67C > design_ovl->cursor_y) {
        design_ovl->_684 = design_ovl->_654;
    } else {
        design_ovl->_684 = design_ovl->_65C;
    }
}

void mDE_waku_set_main_start_end(mDE_Ovl_c* design_ovl, int* x_start, int* y_start, int* x_end, int* y_end) {
    if (design_ovl->_678 > design_ovl->cursor_x) {
        *x_start = design_ovl->cursor_x;
        *x_end = design_ovl->_678;
    } else {
        *x_start = design_ovl->_678;
        *x_end = design_ovl->cursor_x;
    }

    if (design_ovl->_67C > design_ovl->cursor_y) {
        *y_start = design_ovl->cursor_y;
        *y_end = design_ovl->_67C;
    } else {
        *y_start = design_ovl->_67C;
        *y_end = design_ovl->cursor_y;
    }
}

void mDE_waku_line(mDE_Ovl_c* design_ovl, int _param_2, int _param_3, int param_4, int param_5) {
    int iVar4;
    int param_2;
    int param_3;
    int x;
    int y;
    int iVar2;
    int iVar1;
    int i;
    if (param_4 > _param_2) {
        x = param_4 - _param_2;
        iVar2 = 1;
    } else {
        iVar2 = -1;
        x = _param_2 - param_4;
    }

    if (param_5 > _param_3) {
        y = param_5 - _param_3;
        iVar1 = 1;
    } else {
        iVar1 = -1;
        y = _param_3 - param_5;
    }
    param_2 = _param_2;
    param_3 = _param_3;
    if (x >= y) {
        iVar4 = -x;
        for (i = 0; i <= x; i++) {
            mDE_set_pal_on_cursor(design_ovl, param_2, param_3, design_ovl->_6A4);
            iVar4 += y * 2;
            param_2 += iVar2;
            if (iVar4 >= 0) {
                param_3 += iVar1;
                iVar4 += -(x * 2);
            }
        }
    } else {
        iVar4 = -y;
        for (i = 0; i <= y; i++) {
            mDE_set_pal_on_cursor(design_ovl, param_2, param_3, design_ovl->_6A4);
            iVar4 += x * 2;
            param_3 += iVar1;
            if (iVar4 >= 0) {
                param_2 += iVar2;
                iVar4 += -(y * 2);
            }
        }
    }
}

void mDE_waku_circle_write(mDE_Ovl_c* design_ovl, u8 fill) {
    // stack variables
    int x_start;
    int y_start;
    int x_end;
    int y_end;

    // registers
    int v1;
    int v2;
    int x_width;
    int y_width;
    int mid_x;
    int mid_y;
    int half_x_width;
    int half_y_width;
    s16 i;

    if (GETREG(NMREG, 2)) {
        v1 = GETREG(NMREG, 2);
    } else {
        v1 = 45;
    }
    mDE_waku_set_main_start_end(design_ovl, &x_start, &y_start, &x_end, &y_end);
    x_width = ABS(x_end - x_start);
    y_width = ABS(y_end - y_start);
    half_x_width = x_width >> 1;
    half_y_width = y_width >> 1;
    mid_x = x_start + half_x_width;
    mid_y = y_start + half_y_width;
    v2 = ((half_x_width + half_y_width) >> 1) - ((half_x_width + half_y_width) >> 3) -
         (ABS(half_x_width - half_y_width) >> 1) - 1;

    if (GETREG(NMREG, 3)) {
        v2 -= GETREG(NMREG, 3);
    } else {
        v2 -= 4;
    }

    for (i = 0; i < MDE_90DEG; i += MDE_90DEG / (s16)((half_x_width + half_y_width - v2) | 1)) {
        int cos_v = (v1 + half_x_width * MDE_COS(i)) >> 8;
        int sin_v = (v1 + half_y_width * MDE_SIN(i)) >> 8;
        if (fill) {
            int j;
            for (j = mid_x - cos_v; j <= mid_x + cos_v + (x_width & 1); j++) {
                mDE_set_pal_on_cursor(design_ovl, j, mid_y - sin_v, design_ovl->_6A4);
                mDE_set_pal_on_cursor(design_ovl, j, mid_y + sin_v + (y_width & 1), design_ovl->_6A4);
            }
        } else {
            mDE_set_pal_on_cursor(design_ovl, mid_x + cos_v + (x_width & 1), mid_y + sin_v + (y_width & 1),
                                  design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x + cos_v + (x_width & 1), mid_y - sin_v, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x - cos_v, mid_y + sin_v + (y_width & 1), design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x - cos_v, mid_y - sin_v, design_ovl->_6A4);
        }
    }
}

void mDE_waku_square_write(mDE_Ovl_c* design_ovl, u8 fill) {
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    int j;
    int i;
    mDE_waku_set_main_start_end(design_ovl, &x_start, &y_start, &x_end, &y_end);
    if (x_start > x_end || y_start > y_end) {
        return;
    }
    if (fill) {
        for (j = y_start; j <= y_end; j++) {
            for (i = x_start; i <= x_end; i++) {
                mDE_set_pal_on_cursor(design_ovl, i, j, design_ovl->_6A4);
            }
        }
    } else {
        for (i = x_start; i <= x_end; i++) {
            mDE_set_pal_on_cursor(design_ovl, i, y_start, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, i, y_end, design_ovl->_6A4);
        }
        for (j = y_start; j <= y_end; j++) {
            mDE_set_pal_on_cursor(design_ovl, x_start, j, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, x_end, j, design_ovl->_6A4);
        }
    }
}

void mDE_main_waku_move(mDE_Ovl_c* design_ovl) {
    if (design_ovl->_6A2 == 4) {
        design_ovl->_699 = 9;
    } else {
        design_ovl->_699 = 2;
    }
    if (design_ovl->_69A) {
        mDE_waku_set_start(design_ovl);
        design_ovl->_688 = ABS(design_ovl->_678 - design_ovl->cursor_x) + 1;
        design_ovl->_68C = ABS(design_ovl->_67C - design_ovl->cursor_y) + 1;
    }
    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        if (design_ovl->_69A == 0) {
            design_ovl->_658 = design_ovl->_650;
            design_ovl->_65C = design_ovl->_654;
            design_ovl->_678 = design_ovl->cursor_x;
            design_ovl->_67C = design_ovl->cursor_y;
            sAdo_SysTrgStart(0x454);
            design_ovl->_698 = 1;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
        } else {
            mDE_set_undo_texture(design_ovl);
            design_ovl->_6D8 = 0;
            design_ovl->_6D9 = 0;
            switch (design_ovl->_6A2) {
                case 0: {
                    mDE_waku_square_write(design_ovl, 0);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 2: {
                    mDE_waku_square_write(design_ovl, 1);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 1: {
                    mDE_waku_circle_write(design_ovl, 0);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 3: {
                    mDE_waku_circle_write(design_ovl, 1);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 4: {
                    mDE_waku_line(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_678,
                                  design_ovl->_67C);
                    sAdo_SysTrgStart(0x455);
                } break;
            }
            design_ovl->_698 = 0;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
        }
        design_ovl->_69A = !design_ovl->_69A;
    }

    if (GET_BUTTON_PRESSED(BUTTON_B, 1 << 2) && design_ovl->_69A == TRUE) {
        design_ovl->_69A = 0;
        design_ovl->_698 = 0;
        design_ovl->_680 = 0;
        design_ovl->_684 = 0;
        design_ovl->_688 = 0;
        design_ovl->_68C = 0;
        sAdo_SysTrgStart(0x460);
    }
}

void mDE_main_mark_move(mDE_Ovl_c* design_ovl) {
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        switch (design_ovl->_6A3) {
            case 0: {
                design_ovl->_699 = 0xa;
            } break;
            case 1: {
                design_ovl->_699 = 0xb;
            } break;
            case 2: {
                design_ovl->_699 = 0xc;
            } break;
            case 3: {
                design_ovl->_699 = 0xd;
            } break;
            case 4: {
                design_ovl->_699 = 0xe;
            } break;
        }
    } else {
        switch (design_ovl->_6A3) {
            case 0: {
                design_ovl->_699 = 3;
            } break;
            case 1: {
                design_ovl->_699 = 4;
            } break;
            case 2: {
                design_ovl->_699 = 5;
            } break;
            case 3: {
                design_ovl->_699 = 6;
            } break;
        }
    }
    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        mDE_set_undo_texture(design_ovl);
        sAdo_SysTrgStart(0x455);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            switch (design_ovl->_6A3) {
                case 0: {
                    mDE_set_texture_template(design_ovl, mDE_kao1, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 1: {
                    mDE_set_texture_template(design_ovl, mDE_kao2, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 2: {
                    mDE_set_texture_template(design_ovl, mDE_kao3, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 3: {
                    mDE_set_texture_template(design_ovl, mDE_kao4, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 4: {
                    mDE_set_texture_template(design_ovl, mDE_kao5, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
            }
        } else {
            switch (design_ovl->_6A3) {
                case 0: {
                    mDE_set_texture_template(design_ovl, mDE_heart, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
                case 1: {
                    mDE_set_texture_template(design_ovl, mDE_star, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 2: {
                    mDE_set_texture_template(design_ovl, mDE_circle, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
                case 3: {
                    mDE_set_texture_template(design_ovl, mDE_square, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
            }
        }
    }
}

void mDE_main_undo_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 7;
    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        mDE_undo(design_ovl);
    }
}

BOOL mDE_mode_tool_check(mDE_Ovl_c* design_ovl, int param_2, int param_3, int param_4, int param_5) {
    u8 x_values[5];
    u8 y_values[5];
    BOOL moved = FALSE;
    x_values[0] = design_ovl->_6A0;
    y_values[0] = 3;
    x_values[1] = design_ovl->_6A1;
    y_values[1] = 6;
    x_values[2] = design_ovl->_6A2;
    y_values[2] = 5;
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        x_values[3] = design_ovl->_6A3;
        y_values[3] = 5;
    } else {
        x_values[3] = design_ovl->_6A3;
        y_values[3] = 4;
    }
    x_values[4] = 0;
    y_values[4] = 1;
    if (design_ovl->mode == 3) {
        if (gamePT->pads[PAD0].now.stick_x < 0 && design_ovl->_69E > param_2) {
            moved = TRUE;
            design_ovl->_69E--;
        }
        if (gamePT->pads[PAD0].now.stick_x > 0 && design_ovl->_69E < param_3 - 1) {
            moved = TRUE;
            design_ovl->_69E++;
        }
        if (gamePT->pads[PAD0].now.stick_y > 0) {
            if (design_ovl->_69F) {
                if (design_ovl->_69E < param_4) {
                    moved = TRUE;
                    design_ovl->_69F--;
                }
            } else if (design_ovl->_69E == 0) {
                moved = TRUE;
                design_ovl->_69F = 4;
            }
        }
        if (gamePT->pads[PAD0].now.stick_y < 0) {
            if (design_ovl->_69F < 4) {
                if (design_ovl->_69E < param_5) {
                    moved = TRUE;
                    design_ovl->_69F++;
                }
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
                design_ovl->_69F = 0;
            }
        }
    } else if (design_ovl->mode == 0) {
        if (chkTrigger(BUTTON_DLEFT)) {
            if (design_ovl->_69E > param_2) {
                moved = TRUE;
                design_ovl->_69E--;
            } else {
                moved = TRUE;
                design_ovl->_69E = y_values[design_ovl->_69F] - 1;
            }
        }
        if (chkTrigger(BUTTON_DRIGHT)) {
            if (design_ovl->_69E < param_3 - 1) {
                moved = TRUE;
                design_ovl->_69E++;
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
            }
        }
        if (chkTrigger(BUTTON_DUP)) {
            if (design_ovl->_69F) {
                moved = TRUE;
                design_ovl->_69F--;
                design_ovl->_69E = x_values[design_ovl->_69F];
            } else {
                design_ovl->_69E = 0;
                moved = TRUE;
                design_ovl->_69F = 4;
            }
        }
        if (chkTrigger(BUTTON_DDOWN)) {
            if (design_ovl->_69F < 4) {
                moved = TRUE;
                design_ovl->_69F++;
                design_ovl->_69E = x_values[design_ovl->_69F];
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
                design_ovl->_69F = 0;
            }
        }
    }
    return moved;
}

void mDE_main_mode_setup_action(mDE_Ovl_c* design_ovl, int mode) {
    static mDE_OVL_PROC process[] = {
        mDE_main_pen_move,
        mDE_main_nuri_move,
        mDE_main_waku_move,
        mDE_main_mark_move,
        mDE_main_undo_move,
    };

    if (mode != mDE_MAIN_MODE_WAKU) {
        design_ovl->_69A = 0;
        design_ovl->_698 = 0;
        design_ovl->_680 = 0;
        design_ovl->_684 = 0;
        design_ovl->_688 = 0;
        design_ovl->_68C = 0;
    }
    design_ovl->_6DA = 0;
    design_ovl->main_mode_act = mode;
    design_ovl->main_mode_proc = process[mode];
}

void mde_main_move_sound(mDE_Ovl_c* design_ovl) {
    if (chkButton(BUTTON_A) && design_ovl->main_mode_act == mDE_MAIN_MODE_PEN) {
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
    } else {
        sAdo_SysTrgStart(0x453);
    }
}

void mDE_mode_main_shortcut_tool(mDE_Ovl_c* design_ovl, int param_2) {
    int prevAction = param_2 - 1;
    int nextAction = param_2 + 1;
    switch (param_2) {
        case 0: {
            prevAction = 4;
        } break;
        case 4: {
            nextAction = 0;
        } break;
    }

    if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
        mDE_main_mode_setup_action(design_ovl, param_2);
    } else if (chkTrigger(BUTTON_DUP)) {
        mDE_main_mode_setup_action(design_ovl, prevAction);
    } else if (chkTrigger(BUTTON_DDOWN)) {
        mDE_main_mode_setup_action(design_ovl, nextAction);
    }
}

void mDE_cursor_waku(mDE_Ovl_c* design_ovl, int param_2) {
    if (mDE_cursor_waku_rotate(design_ovl, param_2) == FALSE) {
        mDE_cursor_move(design_ovl, param_2);
    }
    mde_main_move_sound(design_ovl);
}

void mDE_cursor_waku_naname(mDE_Ovl_c* design_ovl, int param_2, int param_3, int param_4) {
    if (mDE_cursor_waku_genten_rotate(design_ovl, param_2)) {
        mDE_cursor_move(design_ovl, param_3);
        mDE_cursor_move(design_ovl, param_4);
    } else if (mDE_cursor_waku_rotate(design_ovl, param_3) == FALSE &&
               mDE_cursor_waku_rotate(design_ovl, param_4) == FALSE) {
        mDE_cursor_move(design_ovl, param_3);
        mDE_cursor_move(design_ovl, param_4);
    }
    mde_main_move_sound(design_ovl);
}

void mDE_mode_stick_control_waku(mDE_Ovl_c* design_ovl) {
    if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku_naname(design_ovl, 4, 3, 0);
    } else if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku_naname(design_ovl, 5, 3, 1);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku_naname(design_ovl, 6, 2, 0);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku_naname(design_ovl, 7, 2, 1);
    } else if (mDE_cursor_move_check(design_ovl, 3)) {
        mDE_cursor_waku(design_ovl, 3);
    } else if (mDE_cursor_move_check(design_ovl, 2)) {
        mDE_cursor_waku(design_ovl, 2);
    } else if (mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku(design_ovl, 1);
    }
}

void mDE_mode_stick_control(mDE_Ovl_c* design_ovl) {
    if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
        mDE_cursor_move(design_ovl, 1);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
        mDE_cursor_move(design_ovl, 1);
    } else if (mDE_cursor_move_check(design_ovl, 3)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
    } else if (mDE_cursor_move_check(design_ovl, 2)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
    } else if (mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 1);
    }
}

void mDE_mode_stick_control_analog(mDE_Ovl_c* design_ovl) {
    int oldCursorX = design_ovl->cursor_x;
    if (oldCursorX != (int)(design_ovl->_660 / 5.f) || design_ovl->cursor_y != -(int)(design_ovl->_664 / 5.f)) {
        int oldCursorY = design_ovl->cursor_y;
        design_ovl->cursor_x = (int)(design_ovl->_660) / 5;
        design_ovl->cursor_y = -(int)(design_ovl->_664) / 5;
        design_ovl->_650 = design_ovl->cursor_x * 5;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
        mDE_waku_line(design_ovl, oldCursorX, oldCursorY, design_ovl->cursor_x, design_ovl->cursor_y);
    }
    mDE_cursor_analog_move(design_ovl);
}

#ifdef MOUSE_INPUT
// Checks if a point (px, py) is inside a rectangle defined in these coordinates.
// min_x = left edge - min_y = bottom edge - max_x = right edge - max_y = top edge
static int mDE_point_in_rect(f32 px, f32 py, f32 min_x, f32 min_y, f32 max_x, f32 max_y) {
    return (px >= min_x && px <= max_x && py >= min_y && py <= max_y);
}

void mDE_mode_main_mouse_move(mDE_Ovl_c* design_ovl) {
    // Mouse center position to grid area
    const f32 design_area = 77.5f; // 75 + 2.5
    int new_cursor_x = (int)((design_ovl->centered_x + design_area) / 5.0f);
    int new_cursor_y = (int)(-(design_ovl->centered_y - design_area) / 5.0f);

    // Pen grid max bounds check
    int min = 0;
    if (design_ovl->main_mode_act == mDE_MAIN_MODE_PEN) {
        switch (design_ovl->_6A0) {
            case 1:
                min = 1;
                break;
            case 2:
                min = 2;
                break;
        }
    }

    // Clamp to valid grid range
    if (new_cursor_x < mDE_POS_MIN) new_cursor_x = mDE_POS_MIN;
    if (new_cursor_x > mDE_POS_MAX - min) new_cursor_x = mDE_POS_MAX - min;
    if (new_cursor_y < mDE_POS_MIN) new_cursor_y = mDE_POS_MIN;
    if (new_cursor_y > mDE_POS_MAX - min) new_cursor_y = mDE_POS_MAX - min;
    
    // Update cursor position
    if (new_cursor_x != design_ovl->cursor_x || new_cursor_y != design_ovl->cursor_y) {
        design_ovl->cursor_x = new_cursor_x;
        design_ovl->cursor_y = new_cursor_y;
        design_ovl->_650 = design_ovl->cursor_x * 5;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
        design_ovl->_660 = design_ovl->_650 + 2.5f;
        design_ovl->_664 = design_ovl->_654 - 2.5f;
        
        sAdo_SysTrgStart(0x453);
    }

    // Waku cursor orientation check    
    if (pc_mouse_moved() && design_ovl->main_mode_act == mDE_MAIN_MODE_WAKU) {
        if (design_ovl->_69A && design_ovl->_699 != 9) {
            // Calculate orientation based on cursor position relative to start point
            if (design_ovl->cursor_x >= design_ovl->_678 && design_ovl->cursor_y <= design_ovl->_67C) {
                design_ovl->_6D8 = 1; // right-top
            } else if (design_ovl->cursor_x >= design_ovl->_678 && design_ovl->cursor_y >= design_ovl->_67C) {
                design_ovl->_6D8 = 0; // right-bottom
            } else if (design_ovl->cursor_x <= design_ovl->_678 && design_ovl->cursor_y <= design_ovl->_67C) {
                design_ovl->_6D8 = 3; // left-top
            } else if (design_ovl->cursor_x <= design_ovl->_678 && design_ovl->cursor_y >= design_ovl->_67C) {
                design_ovl->_6D8 = 2; // left-bottom
            }
            design_ovl->_6D9 = design_ovl->_6D8;

            // Update selection box dimensions for visual feedback
            int x_start, y_start, x_end, y_end;
            if (design_ovl->_678 > design_ovl->cursor_x) {
                x_start = design_ovl->cursor_x;
                x_end = design_ovl->_678;
            } else {
                x_start = design_ovl->_678;
                x_end = design_ovl->cursor_x;
            }
            
            if (design_ovl->_67C > design_ovl->cursor_y) {
                y_start = design_ovl->cursor_y;
                y_end = design_ovl->_67C;
            } else {
                y_start = design_ovl->_67C;
                y_end = design_ovl->cursor_y;
            }
            
            design_ovl->_680 = x_start * 5;
            design_ovl->_684 = -y_start * 5;
            design_ovl->_688 = (x_end - x_start) + 1;
            design_ovl->_68C = (y_end - y_start) + 1;
        }
    }
}
#endif

void mDE_mode_main_move(mDE_Ovl_c* design_ovl) {
    design_ovl->move_pR = gamePT->mcon.move_pR;
    design_ovl->_6C4 = 1;
 
#ifdef MOUSE_INPUT
    if (design_ovl->mouse_active) {
        mDE_mode_main_mouse_move(design_ovl);
    }
#endif

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_PEN && chkButton(BUTTON_A)) {
        design_ovl->_6C4 = 3;
        if (GETREG(NMREG, 0x13)) {
            if (GETREG(NMREG, 0x12)) {
                design_ovl->_6BC = 5;
            } else if (GETREG(NMREG, 0x11)) {
                design_ovl->_6BC = 4;
            } else {
                design_ovl->_6BC = GETREG(NMREG, 0x15);
            }
        } else if (gamePT->pads[PAD0].now.stick_x || gamePT->pads[PAD0].now.stick_y) {
            design_ovl->_6BC = 5;
        } else {
            design_ovl->_6BC = 4;
        }
        if (gamePT->pads[PAD0].now.stick_y == 0 && gamePT->pads[PAD0].now.stick_x == 0) {
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
            design_ovl->_6DC = 0;
        }
    } else {
        if (design_ovl->move_pR > 0.9f) {
            design_ovl->_6BC = 3;
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
        } else {
            design_ovl->_6BC = 4;
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
        }
    }
    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (design_ovl->_69A && design_ovl->_699 != 9) {
            mDE_mode_stick_control_waku(design_ovl);
            design_ovl->_6D9 = design_ovl->_6D8;
        } else if (design_ovl->main_mode_act == mDE_MAIN_MODE_PEN && chkButton(BUTTON_A)) {
            if (design_ovl->_6DC) {
                mDE_mode_stick_control_analog(design_ovl);
            } else {
                design_ovl->_6DC = 1;
                mDE_mode_stick_control(design_ovl);
                design_ovl->_660 = design_ovl->_650 + 2.5f;
                design_ovl->_664 = design_ovl->_654 - 2.5f;
            }
        } else {
            mDE_mode_stick_control(design_ovl);
        }
    }

    if (GET_BUTTON_PRESSED(BUTTON_B, 1 << 2) && design_ovl->_69A == 0) {
        design_ovl->_6CD = 1;
        design_ovl->_6A4 = mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
    } else if (GET_BUTTON_HELD(BUTTON_B, 1 << 2) && design_ovl->_69A == 0 && design_ovl->_6CD) {
        design_ovl->_6DB = 1;
        design_ovl->_6A4 = mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
    } else if (design_ovl->_6DB) {
        design_ovl->_6DB = 0;
        sAdo_SysTrgStart(0x45d);
    }
    design_ovl->_6D4 = 4;
    if (chkTrigger(BUTTON_CDOWN)) {
        design_ovl->_6CE = 1;
        design_ovl->_6A4++;
        design_ovl->_6D0 = 0;
        sAdo_SysTrgStart(0x459);
    } else if (chkButton(BUTTON_CDOWN) && design_ovl->_6CE) {
        if (design_ovl->_6D0 > design_ovl->_6D4) {
            design_ovl->_6A4++;
            design_ovl->_6D0 = 0;
            sAdo_SysTrgStart(0x459);
        } else {
            design_ovl->_6D0++;
        }
    } else {
        design_ovl->_6CE = 0;
    }

    if (chkTrigger(BUTTON_CUP)) {
        design_ovl->_6CF = 1;
        design_ovl->_6A4--;
        design_ovl->_6D0 = 0;
        sAdo_SysTrgStart(0x459);
    } else if (chkButton(BUTTON_CUP) && design_ovl->_6CF) {
        if (design_ovl->_6D0 > design_ovl->_6D4) {
            design_ovl->_6A4--;
            design_ovl->_6D0 = 0;
            sAdo_SysTrgStart(0x459);
        } else {
            design_ovl->_6D0++;
        }
    } else {
        design_ovl->_6CF = 0;
    }

    design_ovl->_6A5 = design_ovl->_6A4;

    if (design_ovl->_6A4 >= 0x10) {
        design_ovl->_6A4 = 1;
    }

    if (design_ovl->_6A4 < 1) {
        design_ovl->_6A4 = 0xf;
    }

    if (design_ovl->_69F == 0) {
        if (mDE_mode_tool_check(design_ovl, 0, 3, 0, 6)) {
            sAdo_SysTrgStart(NA_SE_32);
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A0 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 0);
    } else if (design_ovl->_69F == 1) {
        if (mDE_mode_tool_check(design_ovl, 0, 6, 3, 5)) {
            sAdo_SysTrgStart(NA_SE_32);
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A1 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 1);
    } else if (design_ovl->_69F == 2) {
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 5)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        } else {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 4)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A2 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 2);
    } else if (design_ovl->_69F == 3) {
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 5, 1)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        } else {
            if (mDE_mode_tool_check(design_ovl, 0, 4, 5, 1)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A3 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 3);
    } else if (design_ovl->_69F == 4) {
        if (mDE_mode_tool_check(design_ovl, 0, 1, 5, 1) &&
            (chkTrigger(BUTTON_DLEFT) == 0 && chkTrigger(BUTTON_DRIGHT) == 0)) {
            sAdo_SysTrgStart(NA_SE_32);
        }
        mDE_mode_main_shortcut_tool(design_ovl, 4);
    }
    if (GET_BUTTON_PRESSED(BUTTON_X, 1 << 1)) {
        design_ovl->_69D = !design_ovl->_69D;
        if (design_ovl->_69D == FALSE) {
            sAdo_SysTrgStart(0x457);
        } else {
            sAdo_SysTrgStart(0x456);
        }
    }
    if (chkTrigger(BUTTON_Y)) {
        mDE_undo(design_ovl);
    }
    if (chkButton(BUTTON_Z)) {
        mDE_print_texture(design_ovl);
    }
    design_ovl->main_mode_proc(design_ovl);
    if (GET_BUTTON_HELD(BUTTON_B, 1 << 2) && design_ovl->_69A == 0 && design_ovl->_6CD) {
        design_ovl->_699 = 8;
    }
}

#ifdef MOUSE_INPUT
void mDE_mode_pallet_mouse_move(mDE_Ovl_c* design_ovl) {
    int color_index = -1;

    const f32 cx   = 110.0f;
    const f32 step = 10.0f;

    for (int i = 0; i < 16; i++) {
        f32 cy = (i == 0) ? 63.0f : 63.0f - i * step;

        f32 half_h = (i == 0) ? 12.0f : 5.0f;

        if (mDE_point_in_rect(design_ovl->centered_x, design_ovl->centered_y,
                              cx - 15.0f, cy - half_h,
                              cx + 15.0f, cy + half_h)) {
            color_index = i;
            break;
        }
    }

    if (color_index >= 0 && color_index <= 15) {
        u32 mouse_pressed = pc_mouse_button_pressed();

        if (design_ovl->_6A5 != color_index) {
            design_ovl->_6A5 = color_index;
            sAdo_SysTrgStart(0x459);
        }

        if (design_ovl->_6A5 == 0) {
            if (mouse_pressed & (1 << 0)) {
                // Left click cycles palette forwards
                sAdo_SysTrgStart(0x458);
                design_ovl->palette_no++;
                if (design_ovl->palette_no >= 0x10) {
                    design_ovl->palette_no = 0;
                }
                design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
                mDE_pallet_RGB5A3_to_RGB24(design_ovl);
            }
            if (mouse_pressed & (1 << 2)) {
                // Right click cycles palette backwards
                sAdo_SysTrgStart(0x458);
                if (design_ovl->palette_no == 0) {
                    design_ovl->palette_no = 0xf;
                } else {
                    design_ovl->palette_no--;
                }
                design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
                mDE_pallet_RGB5A3_to_RGB24(design_ovl);
            }
        } else {
            if (mouse_pressed & (1 << 0)) {
                // Click to select color
                sAdo_SysTrgStart(0x45a);
                design_ovl->_6A4 = design_ovl->_6A5;
            }
        }
    }
}
#endif

void mDE_mode_pallet_move(mDE_Ovl_c* design_ovl) {
    int old6A5 = design_ovl->_6A5;
    design_ovl->move_pR = gamePT->mcon.move_pR;
    if (GETREG(NMREG, 0x10)) {
        design_ovl->_6C4 = GETREG(NMREG, 0x10);
    } else {
        design_ovl->_6C4 = 0x18;
    }
    if (GETREG(NMREG, 0x11)) {
        design_ovl->_6BC = GETREG(NMREG, 0x11);
    } else {
        design_ovl->_6BC = 4;
    }

#ifdef MOUSE_INPUT
    if (design_ovl->mouse_active) {
        mDE_mode_pallet_mouse_move(design_ovl);
        return;
    }
#endif

    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (gamePT->pads[PAD0].now.stick_y < 0) {
            sAdo_SysTrgStart(0x459);
            old6A5++;
        }
        if (gamePT->pads[PAD0].now.stick_y > 0) {
            sAdo_SysTrgStart(0x459);
            old6A5--;
        }
    }
    design_ovl->_6A5 = old6A5;
    if (old6A5 >= 0x10) {
        design_ovl->_6A5 = 0;
    }
    if (old6A5 < 0) {
        design_ovl->_6A5 = 0xf;
    }
    if (design_ovl->_6A5 == 0 && chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x458);
        design_ovl->palette_no++;
        if (design_ovl->palette_no >= 0x10) {
            design_ovl->palette_no = 0;
        }
        design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
        mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    }
    if (design_ovl->_6A5 == 0 && chkTrigger(BUTTON_B)) {
        sAdo_SysTrgStart(0x458);
        if (design_ovl->palette_no == 0) {
            design_ovl->palette_no = 0xf;
        } else {
            design_ovl->palette_no--;
        }
        design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
        mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    }
    if (design_ovl->_6A5 && chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x45a);
        design_ovl->_6A4 = design_ovl->_6A5;
        mDE_setup_action(design_ovl, 0);
    }
}

void mDE_mode_grid_move(mDE_Ovl_c* design_ovl) {
    if (GET_BUTTON_PRESSED(BUTTON_A, 1 << 0)) {
        design_ovl->_69D = !design_ovl->_69D;
        if (design_ovl->_69D == FALSE) {
            sAdo_SysTrgStart(0x457);
        } else {
            sAdo_SysTrgStart(0x456);
        }
    }
}

#ifdef MOUSE_INPUT
void mDE_mode_tool_mouse_move(mDE_Ovl_c* design_ovl) {   
    int index_x = -1;
    int index_y = -1;
    f32 min_x_d, min_y_d, max_x_d, max_y_d = 0;
    
    const f32 base_y = 6.0f;
    const f32 base_x = -122.0f;
    const f32 step   = 24.0f;
    
    // Number of slots per row based on context
    int slots_per_row[5];
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        slots_per_row[0] = 3;  // Pen sizes
        slots_per_row[1] = 6;  // Fill patterns
        slots_per_row[2] = 5;  // Shape tools
        slots_per_row[3] = 5;  // Stamps (kao 1-5)
        slots_per_row[4] = 1;  // Undo
    } else {
        slots_per_row[0] = 3;  // Pen sizes
        slots_per_row[1] = 6;  // Fill patterns
        slots_per_row[2] = 5;  // Shape tools
        slots_per_row[3] = 4;  // Stamps (heart, star, circle, square)
        slots_per_row[4] = 1;  // Undo
    }
    
    // Find which tool slot the mouse is over
    for (int y = 0; y < 5; y++) {
        f32 min_y = base_y - y * step;
        f32 max_y = min_y + step;
        
        for (int x = 0; x < slots_per_row[y]; x++) {
            f32 min_x = base_x + x * step;
            f32 max_x = min_x + step;
            
            if (mDE_point_in_rect(design_ovl->centered_x, design_ovl->centered_y, 
                                  min_x, min_y, max_x, max_y)) {
                index_x = x;
                index_y = y;
                min_x_d = min_x;
                min_y_d = min_y;
                max_x_d = max_x;
                max_y_d = max_y;
                break;
            }
        }
    }

    // Update tool selection based on mouse hover
    if (index_y != -1) {
        u32 mouse_pressed = pc_mouse_button_pressed();

        design_ovl->mouse_tool_active = 1;
        if (design_ovl->mouse_tool_y != index_y || design_ovl->mouse_tool_x != index_x) {
            design_ovl->mouse_tool_x = index_x;
            design_ovl->mouse_tool_y = index_y;
            sAdo_SysTrgStart(NA_SE_32);
        }

        // Handle click to select/activate tool
        if (mouse_pressed & (1 << 0)) {
            if (index_x > 0) design_ovl->mouse_tool_active = 0;
            sAdo_SysTrgStart(NA_SE_33);
            design_ovl->_69E = design_ovl->mouse_tool_x;
            design_ovl->_69F = design_ovl->mouse_tool_y;
            switch (index_y) {
                case 0: // Pen tools
                    design_ovl->_6A0 = index_x;
                    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_PEN);
                    if (index_x > 0) mDE_setup_action(design_ovl, mDE_MODE_MAIN);
                    break;
                case 1: // Fill/Nuri tools
                    design_ovl->_6A1 = index_x;
                    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_NURI);
                    if (index_x > 0) mDE_setup_action(design_ovl, mDE_MODE_MAIN);
                    break;
                case 2: // Shape/Waku tools
                    design_ovl->_6A2 = index_x;
                    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_WAKU);
                    if (index_x > 0) mDE_setup_action(design_ovl, mDE_MODE_MAIN);
                    break;
                case 3: // Stamp/Mark tools
                    design_ovl->_6A3 = index_x;
                    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_MARK);
                    if (index_x > 0) mDE_setup_action(design_ovl, mDE_MODE_MAIN);
                    break;
                case 4: // Undo
                    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_UNDO);
                    if (index_x > 0) mDE_setup_action(design_ovl, mDE_MODE_MAIN);
                    break;
            }
        }
    } else {
        design_ovl->mouse_tool_active = 0;
    }
}
#endif

void mDE_mode_tool_move(mDE_Ovl_c* design_ovl) {
    design_ovl->move_pR = gamePT->mcon.move_pR;
    if (GETREG(NMREG, 0x12)) {
        design_ovl->_6C4 = GETREG(NMREG, 0x12);
    } else {
        design_ovl->_6C4 = 0x18;
    }
    if (GETREG(NMREG, 0x13)) {
        design_ovl->_6BC = GETREG(NMREG, 0x13);
    } else {
        design_ovl->_6BC = 8;
    }
    
#ifdef MOUSE_INPUT
    if (design_ovl->mouse_active) {
        mDE_mode_tool_mouse_move(design_ovl);
        return;
    }
    if (design_ovl->mouse_tool_active) {
        design_ovl->_69E = design_ovl->mouse_tool_x;
        design_ovl->_69F = design_ovl->mouse_tool_y;
        design_ovl->mouse_tool_active = 0;
    }
#endif
    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (design_ovl->_69F == 0) {
            if (mDE_mode_tool_check(design_ovl, 0, 3, 0, 6)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        } else if (design_ovl->_69F == 1) {
            if (mDE_mode_tool_check(design_ovl, 0, 6, 3, 5)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        } else if (design_ovl->_69F == 2) {
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 5)) {
                    sAdo_SysTrgStart(NA_SE_32);
                }
            } else {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 4)) {
                    sAdo_SysTrgStart(NA_SE_32);
                }
            }
        } else if (design_ovl->_69F == 3) {
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 5, 1)) {
                    sAdo_SysTrgStart(NA_SE_32);
                }
            } else {
                if (mDE_mode_tool_check(design_ovl, 0, 4, 5, 1)) {
                    sAdo_SysTrgStart(NA_SE_32);
                }
            }
        } else if (design_ovl->_69F == 4) {
            if (mDE_mode_tool_check(design_ovl, 0, 1, 5, 1)) {
                sAdo_SysTrgStart(NA_SE_32);
            }
        }
    }

    if (chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(NA_SE_33);
        switch (design_ovl->_69F) {
            case 0: {
                design_ovl->_6A0 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_PEN);
                mDE_setup_action(design_ovl, mDE_MODE_MAIN);
            } break;
            case 1: {
                design_ovl->_6A1 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_NURI);
                mDE_setup_action(design_ovl, mDE_MODE_MAIN);
            } break;
            case 2: {
                design_ovl->_6A2 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_WAKU);
                mDE_setup_action(design_ovl, mDE_MODE_MAIN);
            } break;
            case 3: {
                design_ovl->_6A3 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_MARK);
                mDE_setup_action(design_ovl, mDE_MODE_MAIN);
            } break;
            case 4: {
                mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_UNDO);
                mDE_setup_action(design_ovl, mDE_MODE_MAIN);
            } break;
        }
    }
}

void mDE_setup_action(mDE_Ovl_c* design_ovl, int mode) {
    static mDE_OVL_PROC process[] = {
        mDE_mode_main_move,
        mDE_mode_pallet_move,
        mDE_mode_grid_move,
        mDE_mode_tool_move,
    };

    if (mode >= mDE_MODE_NUM) {
        mode = mDE_MODE_MAIN;
    }

    if (mode < mDE_MODE_MAIN) {
        mode = mDE_MODE_TOOL;
    }
    design_ovl->_6CC = 0;
    design_ovl->_6CD = 0;
    design_ovl->_698 = 0;
    design_ovl->_680 = 0;
    design_ovl->_684 = 0;
    design_ovl->_688 = 0;
    design_ovl->_68C = 0;
    design_ovl->mode = mode;
    design_ovl->act_proc = process[mode];
}

void mDE_move_Move(Submenu* submenu, mSM_MenuInfo_c* info) {
    submenu->overlay->move_Move_proc(submenu, info);
}

void mDE_move_tool_decide(mDE_Ovl_c* design_ovl) {
    switch (design_ovl->_69F) {
        case 0: {
            design_ovl->_6A0 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_PEN);
        } break;
        case 1: {
            design_ovl->_6A1 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_NURI);
        } break;
        case 2: {
            design_ovl->_6A2 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_WAKU);
        } break;
        case 3: {
            design_ovl->_6A3 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_MARK);
        } break;
        case 4: {
            mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_UNDO);
        } break;
    }
}

void mDE_move_Play(Submenu* submenu, mSM_MenuInfo_c* info) {
    u32 trigger = submenu->overlay->menu_control.trigger;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;

#ifdef MOUSE_INPUT
    // Handle mouse movement for cursor
    s32 mouse_x, mouse_y;
    pc_mouse_get_native_position(&mouse_x, &mouse_y);
    
    // Set half position for interface
    f32 ui_x = (f32)mouse_x * 0.5f;
    f32 ui_y = (f32)mouse_y * 0.5f;
    
    // Convert from top-left origin (0,0) to centered origin (0,0 at center)
    f32 centered_x = ui_x - 160.0f;
    f32 centered_y = 120.0f - ui_y;
    design_ovl->centered_x = centered_x;
    design_ovl->centered_y = centered_y;

    if (trigger) {
        design_ovl->mouse_active = 0;
    }
    if (pc_mouse_active()) {
        design_ovl->mouse_active = 1;
    }

    // Mode switching with mouse
    if (design_ovl->mouse_active) {
        u32 mouse_held = pc_mouse_button_held();
        int holding_mouse = (
            (((mouse_held >> 0) & 1 || (mouse_held >> 2) & 1) && design_ovl->mode == mDE_MODE_MAIN) || // Holding left/right click while drawing
            ((design_ovl->_69A && design_ovl->_699 != 9) && design_ovl->mode == mDE_MAIN_MODE_WAKU) // Waku active selection
        );

        int new_mode = -1;
        // Check each mode area (prioritize smaller areas first - tool and grid)
        // Tool menu area (left side, tool selection)
        if (mDE_point_in_rect(centered_x, centered_y, -122.0f, -93.0f, -97.0f, 27.0f) || design_ovl->mouse_tool_active) {
            if (!holding_mouse) new_mode = mDE_MODE_TOOL;
        }
        // Grid toggle area
        else if (mDE_point_in_rect(centered_x, centered_y, -126.0f, 47.0f, -92.0f, 80.0f)) {
            if (!holding_mouse) new_mode = mDE_MODE_GRID;
        }
        // Palette area (right side)
        else if (mDE_point_in_rect(centered_x, centered_y, 95.0f, -92.0f, 120.0f, 85.0f)) {
            if (!holding_mouse) new_mode = mDE_MODE_PALLET;
        }
        // Main design area
        else if (mDE_point_in_rect(centered_x, centered_y, -80.0f, -80.0f, 80.0f, 80.0f)) {
            if (!holding_mouse) new_mode = mDE_MODE_MAIN;
        }

        // Switch mode if changed
        if (new_mode != -1 && new_mode != design_ovl->mode) {
            mDE_setup_action(design_ovl, new_mode);
            sAdo_SysTrgStart(NA_SE_37);
        }
    }
#endif

    if (submenu->current_menu_type == mSM_OVL_DESIGN) {
        if (trigger & BUTTON_START) {
            design_ovl->_698 = 0;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
            design_ovl->_6CC = 0;
            design_ovl->_6CD = 0;
            mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_ORIGINAL_DESIGN, 0);
            info->proc_status = mSM_OVL_PROC_WAIT;
            sAdo_SysTrgStart(NA_SE_MENU_EXIT);
        } else if (chkTrigger(BUTTON_R)) {
            if (design_ovl->_6A5) {
                design_ovl->_6A4 = design_ovl->_6A5;
            }
            sAdo_SysTrgStart(NA_SE_37);
            mDE_move_tool_decide(design_ovl);
            mDE_setup_action(design_ovl, design_ovl->mode + 1);
        } else if (chkTrigger(BUTTON_L)) {
            if (design_ovl->_6A5) {
                design_ovl->_6A4 = design_ovl->_6A5;
            }
            sAdo_SysTrgStart(NA_SE_37);
            mDE_move_tool_decide(design_ovl);
            mDE_setup_action(design_ovl, design_ovl->mode - 1);
        } else {
            design_ovl->act_proc(design_ovl);
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                mDE_mask_cat_mask(design_ovl);
            }
            bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->work_texture));
            osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->work_texture));
        }
    }
}

void mDE_move_Wait(Submenu* submenu, mSM_MenuInfo_c* info) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mDE_Ovl_c* design_ovl = overlay->design_ovl;
    if (overlay->menu_info[mSM_OVL_EDITENDCHK].proc_status == mSM_OVL_PROC_MOVE &&
        overlay->menu_info[mSM_OVL_EDITENDCHK].next_proc_status == mSM_OVL_PROC_END) {
        switch (overlay->menu_info[mSM_OVL_EDITENDCHK].data1) {
            case 0: {
                overlay->move_chg_base_proc(info, mSM_MOVE_OUT_BOTTOM);
                if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                    mDE_save_maskcat_texture(design_ovl);
                    if (GETREG(NMREG, 0x5f)) {
                        mDE_print_texture(design_ovl);
                    }
                    Save_Get(mask_cat.palette_no) = design_ovl->palette_no;
                    bcopy(&design_ovl->work_texture, Save_GetPointer(mask_cat.design.design),
                          sizeof(design_ovl->work_texture));
                    osWritebackDCache(Save_GetPointer(mask_cat.design.design),
                                      sizeof(Save_Get(mask_cat.design.design)));
                } else {
                    mNW_original_design_c* my_design = &Now_Private->my_org[design_ovl->image_no & 7];
                    my_design->palette = design_ovl->palette_no;
                    mNW_OverWriteOriginalTexture(my_design, design_ovl->texture.data);
                }
                submenu->item_p->slot_no = 1;
            } break;
            case 1: {
                info->proc_status = mSM_OVL_PROC_PLAY;
            } break;
            default: {
                overlay->move_chg_base_proc(info, mSM_MOVE_OUT_BOTTOM);
            } break;
        }
    }
}

void mDE_move_End(Submenu* submenu, mSM_MenuInfo_c* info) {
    submenu->overlay->move_End_proc(submenu, info);
}

void mDE_design_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        &mDE_move_Move,
        &mDE_move_Play,
        &mDE_move_Wait,
        (mSM_MOVE_PROC)&none_proc1,
        &mDE_move_End,
    };

    mSM_MenuInfo_c* overlay = &submenu->overlay->menu_info[mSM_OVL_DESIGN];
    overlay->pre_move_func(submenu);
    ovl_move_proc[overlay->proc_status](submenu, overlay);
}

extern Gfx des_sen_waku_model[], des_win_before[], des_win_before_model[], des_win_before_model_2[],
    des_win_waku_model[], des_win_waku2_model[], des_win_color_model[], des_win_toubai_model[], des_win_main_model[],
    des_win_color_before_model[], des_win_grid_model[], des_win_grid2_model[], des_cursor_waku2T_model[],
    des_tool_pen_all_model[], des_tool_nuri_all_model[], des_tool_waku_all_model[], des_tool_kao_all_model[],
    des_tool_mark_all_model[], des_tool_pen1T_model[], des_tool_nuriT_model[], des_tool_waku1T_model[],
    des_tool_mark1T_model[], des_tool_undoT_model[], des_tool_pen1_tex_rgb_ia8[], des_tool_pen2_tex_rgb_ia8[],
    des_tool_pen3_tex_rgb_ia8[], des_tool_nuri1_tex_rgb_ia8[], des_tool_nuri2_tex_rgb_ia8[],
    des_tool_nuri3_tex_rgb_ia8[], des_tool_nuri4_tex_rgb_ia8[], des_tool_nuri5_tex_rgb_ia8[],
    des_tool_nuri6_tex_rgb_ia8[], des_tool_waku1_tex_rgb_ia8[], des_tool_waku2_tex_rgb_ia8[],
    des_tool_waku3_tex_rgb_ia8[], des_tool_waku4_tex_rgb_ia8[], des_tool_waku5_tex_rgb_ia8[],
    des_tool_mark1_tex_rgb_ia8[], des_tool_mark2_tex_rgb_ia8[], des_tool_mark3_tex_rgb_ia8[],
    des_tool_mark4_tex_rgb_ia8[], des_tool_kao1_tex[], des_tool_kao2_tex[], des_tool_kao3_tex[], des_tool_kao4_tex[],
    des_tool_kao5_tex[], des_win_suuji0_tex_rgb_i4[], des_win_suuji1_tex_rgb_i4[], des_win_suuji2_tex_rgb_i4[],
    des_win_suuji3_tex_rgb_i4[], des_win_suuji4_tex_rgb_i4[], des_win_suuji5_tex_rgb_i4[], des_win_suuji6_tex_rgb_i4[],
    des_win_suuji7_tex_rgb_i4[], des_win_suuji8_tex_rgb_i4[], des_win_suuji9_tex_rgb_i4[], des_cursor_penT_model[],
    des_cursor_nuriT_model[], des_cursor_waku1T_model[], des_cursor_mark1_model[], des_cursor_mark2_model[],
    des_cursor_mark3_model[], des_cursor_mark4_model[], des_cursor_undo_model[], des_cursor_spT_model[],
    des_cursor_wakuT_model[], des_cursor_kao1T_model[], des_cursor_kao2T_model[], des_cursor_kao3T_model[],
    des_cursor_kao4_model[], des_cursor_kao5_model[], des_win_area1_model[], des_win_area2_model[],
    des_win_area4_model[], des_win_area3_model[], des_win_shikiri_model[], des_win_suuji_before[],
    des_win_suuji3_model[], des_win_suuji4_model[], des_win_suuji2_model[], des_win_suuji1_model[],
    des_win_marking_model[], des_win_marking2T_model[];

void mDE_set_frame_tool_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {

    static Gfx* tool_pen_table[] = { des_tool_pen1_tex_rgb_ia8, des_tool_pen2_tex_rgb_ia8, des_tool_pen3_tex_rgb_ia8 };
    static Gfx* tool_nuri_table[] = { des_tool_nuri1_tex_rgb_ia8, des_tool_nuri2_tex_rgb_ia8,
                                      des_tool_nuri3_tex_rgb_ia8, des_tool_nuri4_tex_rgb_ia8,
                                      des_tool_nuri5_tex_rgb_ia8, des_tool_nuri6_tex_rgb_ia8 };
    static Gfx* tool_waku_table[] = { des_tool_waku1_tex_rgb_ia8, des_tool_waku2_tex_rgb_ia8,
                                      des_tool_waku3_tex_rgb_ia8, des_tool_waku4_tex_rgb_ia8,
                                      des_tool_waku5_tex_rgb_ia8 };
    static Gfx* tool_mark_table[] = { des_tool_mark1_tex_rgb_ia8, des_tool_mark2_tex_rgb_ia8,
                                      des_tool_mark3_tex_rgb_ia8, des_tool_mark4_tex_rgb_ia8 };
    static Gfx* tool_kao_table[] = { des_tool_kao1_tex, des_tool_kao2_tex, des_tool_kao3_tex, des_tool_kao4_tex,
                                     des_tool_kao5_tex };
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, MTX_MULT);
    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before);
    if (design_ovl->mode == mDE_MODE_TOOL) {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, tool_pen_table[0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tool_nuri_table[0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_3_TXT_SEG, tool_waku_table[0]);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_kao_table[0]);
        } else {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_mark_table[0]);
        }
        gSPDisplayList(POLY_OPA_DISP++, des_tool_pen_all_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_nuri_all_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_waku_all_model);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPDisplayList(POLY_OPA_DISP++, des_tool_kao_all_model);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, des_tool_mark_all_model);
        }
    } else {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, tool_pen_table[design_ovl->_6A0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tool_nuri_table[design_ovl->_6A1]);
        gSPSegment(POLY_OPA_DISP++, ANIME_3_TXT_SEG, tool_waku_table[design_ovl->_6A2]);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_kao_table[design_ovl->_6A3]);
        } else {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_mark_table[design_ovl->_6A3]);
        }
        gSPDisplayList(POLY_OPA_DISP++, des_tool_pen1T_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_nuriT_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_waku1T_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_mark1T_model);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_tool_undoT_model);

    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_suuji_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {

    static Gfx* suuji_table[] = { des_win_suuji0_tex_rgb_i4, des_win_suuji1_tex_rgb_i4, des_win_suuji2_tex_rgb_i4,
                                  des_win_suuji3_tex_rgb_i4, des_win_suuji4_tex_rgb_i4, des_win_suuji5_tex_rgb_i4,
                                  des_win_suuji6_tex_rgb_i4, des_win_suuji7_tex_rgb_i4, des_win_suuji8_tex_rgb_i4,
                                  des_win_suuji9_tex_rgb_i4 };

    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    GRAPH* graph = game->graph;
    int pal = design_ovl->palette_no + 1;
    Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, MTX_MULT);
    OPEN_POLY_OPA_DISP(graph);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (design_ovl->mode == mDE_MODE_PALLET) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 215, 30, 30, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 245, 215, 180);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_shikiri_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji_before);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji3_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji4_model);
    if (pal >= ARRAY_COUNT(suuji_table)) {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, suuji_table[1]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji1_model);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, suuji_table[pal % ARRAY_COUNT(suuji_table)]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji2_model);
    } else {
        Matrix_push();
        Matrix_translate(-2.f, 0.f, 0.f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, suuji_table[pal]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji2_model);
        Matrix_pull();
    }

    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_mark_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before);
    Matrix_push();
    if (design_ovl->mode == mDE_MODE_TOOL) {
#ifdef MOUSE_INPUT
        if (design_ovl->mouse_tool_active) { // Visual hover on mouse rather than actual selection
            Matrix_translate(-112.f + design_ovl->mouse_tool_x * 0x18, 16.f - design_ovl->mouse_tool_y * 0x18, 0.f, MTX_MULT);
        } else
#endif
        {
            Matrix_translate(-112.f + design_ovl->_69E * 0x18, 16.f - design_ovl->_69F * 0x18, 0.f, MTX_MULT);
        }
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 185, 50, 50, 255);
    } else {
        Matrix_translate(-112.f, 16.f - design_ovl->_69F * 0x18, 0.f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 215, 195, 195, 255);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_marking_model);
    Matrix_pull();
    Matrix_push();
    Matrix_translate(110.f, 0x3f - design_ovl->_6A4 * 10, 0.f, MTX_MULT);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (design_ovl->mode != mDE_MODE_PALLET) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0xcd, 0xb9, 0xb9, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 105, 85, 115, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 235, 235, 235, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 105, 85, 115, 255);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_marking2T_model);
    Matrix_pull();
    if (design_ovl->mode == mDE_MODE_PALLET) {
        Matrix_push();
        if (design_ovl->_6A5 == 0) {
            Matrix_translate(110.f, 71.f, 0.f, MTX_MULT);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 185, 50, 50, 255);
            gSPDisplayList(POLY_OPA_DISP++, des_win_marking_model);
        } else {
            Matrix_translate(110.f, 0x3f - design_ovl->_6A5 * 10, 0.f, MTX_MULT);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 80, 80, 255);
            gDPSetEnvColor(POLY_OPA_DISP++, 30, 30, 30, 255);
            gSPDisplayList(POLY_OPA_DISP++, des_win_marking2T_model);
        }
        Matrix_pull();
    }
    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_waku_right_top(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_3 = param_1;
    *param_4 = DEG2SHORT_ANGLE2(90);
}

void mDE_waku_right_bottom(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    // nothing;
}

void mDE_waku_left_top(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_3 = param_1;
    *param_2 = -1.f * param_1;
    *param_4 = DEG2SHORT_ANGLE2(180);
}

void mDE_waku_left_bottom(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_2 = -1.f * param_1;
    *param_4 = DEG2SHORT_ANGLE2(270);
}

void mDE_set_cursor_waku_rotate(mDE_Ovl_c* design_ovl, u32 param_2, f32* param_3, f32* param_4, s16* param_5) {
    f32 v = 1.f;
    if (param_2) {
        v = -1.f;
    }
    switch (design_ovl->_6D8) {
        case 0: {
            mDE_waku_right_bottom(v, param_3, param_4, param_5);
        } break;
        case 1: {
            mDE_waku_right_top(v, param_3, param_4, param_5);
        } break;
        case 2: {
            mDE_waku_left_bottom(v, param_3, param_4, param_5);
        } break;
        case 3: {
            mDE_waku_left_top(v, param_3, param_4, param_5);
        } break;
    }
}

void mDE_set_frame_cursor_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    static Gfx* cursor_table[] = { des_cursor_penT_model,  des_cursor_nuriT_model, des_cursor_waku1T_model,
                                   des_cursor_mark1_model, des_cursor_mark2_model, des_cursor_mark3_model,
                                   des_cursor_mark4_model, des_cursor_undo_model,  des_cursor_spT_model,
                                   des_cursor_wakuT_model, des_cursor_kao1T_model, des_cursor_kao2T_model,
                                   des_cursor_kao3T_model, des_cursor_kao4_model,  des_cursor_kao5_model };
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    if (design_ovl->mode == 0) {
        if (design_ovl->_698 != 0) {
            if (design_ovl->_699 != 9) {
                int a, b;
                design_ovl->_680 -= 0x52;
                design_ovl->_684 += 0x4f;
                design_ovl->_690 = design_ovl->_680 + design_ovl->_688 * 5;
                design_ovl->_694 = design_ovl->_684 + design_ovl->_68C * 5;
                a = ABS(design_ovl->_680 - design_ovl->_690);
                b = ABS(design_ovl->_684 - design_ovl->_694);
                design_ovl->_684 -= b;
                design_ovl->_694 -= b;

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
                Matrix_translate(design_ovl->_680, design_ovl->_684, 0.f, MTX_MULT);
                Matrix_scale(a, 2.f, 1.f, MTX_MULT);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
                Matrix_translate(design_ovl->_680, design_ovl->_694, 0.f, MTX_MULT);
                if (a) {
                    a += 2.f;
                }
                Matrix_scale(a, 2.f, 1.f, MTX_MULT);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
                Matrix_translate(design_ovl->_680, design_ovl->_684, 0.f, MTX_MULT);
                Matrix_scale(2.f, b, 1.f, MTX_MULT);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
                Matrix_translate(design_ovl->_690, design_ovl->_684, 0.f, MTX_MULT);
                Matrix_scale(2.f, b, 1.f, MTX_MULT);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();
            }
        }
        Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
        Matrix_translate(menu->position[0], menu->position[1], 140.f, MTX_MULT);
        OPEN_POLY_OPA_DISP(graph);
        gSPDisplayList(POLY_OPA_DISP++, des_win_before);
        if (design_ovl->_69A && design_ovl->_699 != 9) {
            float f1, f2;
            s16 s1;
            s1 = 0;
            f1 = 0.f;
            f2 = 0.f;
            mDE_set_cursor_waku_rotate(design_ovl, 1, &f1, &f2, &s1);
            Matrix_push();
            Matrix_translate(design_ovl->_658 - 3.f - 75.f - f1, design_ovl->_65C + 2.f - (-75.f) - f2, 0.f, MTX_MULT);
            Matrix_RotateZ(s1, MTX_MULT);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_waku1T_model);
            Matrix_pull();
        } else if (design_ovl->_69A && design_ovl->_699 == 9) {
            Matrix_push();
            Matrix_translate(design_ovl->_658 - 3.f - 75.f, (design_ovl->_65C + 10.f) - (-75.f), 0.f, MTX_MULT);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_wakuT_model);
            Matrix_pull();
        }
        if (design_ovl->_699 == 1) {
            Matrix_translate(design_ovl->_650 + 1.f - 75.f, design_ovl->_654 + 11.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 2) {
            if (design_ovl->_69A) {
                float f1, f2;
                s16 s1;
                s1 = 0;
                f1 = 0.f;
                f2 = 0.f;
                mDE_set_cursor_waku_rotate(design_ovl, 0, &f1, &f2, &s1);
                Matrix_translate(design_ovl->_650 - 4.f - 75.f - f1, design_ovl->_654 + 3.f - (-75.f) - f2, 0.f, MTX_MULT);
                Matrix_RotateZ(s1, MTX_MULT);
            } else {
                Matrix_translate(design_ovl->_650 - 3.f - 75.f, design_ovl->_654 + 2.f - (-75.f), 0.f, MTX_MULT);
            }
        } else if (design_ovl->_699 == 3) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 4) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 5) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 6) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 7) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 9) {
            Matrix_translate(design_ovl->_650 - 3.f - 75.f, design_ovl->_654 + 10.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 10) {
            Matrix_translate(design_ovl->_650 - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 11) {
            Matrix_translate(design_ovl->_650 - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 12) {
            Matrix_translate(design_ovl->_650 + 2.f - 75.f, design_ovl->_654 + 7.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 13) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, MTX_MULT);
        } else if (design_ovl->_699 == 14) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, MTX_MULT);
        } else {
            Matrix_translate(design_ovl->_650 + 8.f - 75.f, design_ovl->_654 + 13.f - (-75.f), 0.f, MTX_MULT);
        }
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (design_ovl->_69A && design_ovl->_699 == 2) {
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_waku2T_model);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, cursor_table[design_ovl->_699]);
        }
        CLOSE_POLY_OPA_DISP(graph);
    }
}

void mDE_set_frame_main_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    int i;
    static Gfx* area_table[] = { des_win_area1_model, des_win_area2_model, des_win_area4_model, des_win_area3_model };

    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, MTX_LOAD);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, MTX_MULT);
    OPEN_POLY_OPA_DISP(graph);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before_model);
    for (i = 0; i < ARRAY_COUNT(area_table); i++) {
        if (i == design_ovl->mode) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0x28, 0xeb, 0xa0, 0xb4);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0x5a, 0x46, 0x28, 0xb4);
        }
        gSPDisplayList(POLY_OPA_DISP++, area_table[i]);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_before_model_2);
    gSPDisplayList(POLY_OPA_DISP++, des_win_waku_model);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
    gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, design_ovl->palette_p);
    gDPLoadTextureBlock_4b_Dolphin(POLY_OPA_DISP++, design_ovl->texture.data, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR,
                                   GX_MIRROR, 0, 0);
    gSPDisplayList(POLY_OPA_DISP++, des_win_toubai_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_main_model);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);
    gSPDisplayList(POLY_OPA_DISP++, des_win_color_before_model);
    Matrix_push();
    for (i = 0; i < ARRAY_COUNT(design_ovl->rgb8_pal) - 1; i++) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[i + 1].r, design_ovl->rgb8_pal[i + 1].g,
                        design_ovl->rgb8_pal[i + 1].b, 255);
        gSPDisplayList(POLY_OPA_DISP++, des_win_color_model);
        Matrix_translate(0.f, -10.f, 0.f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    Matrix_pull();
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_waku2_model);
    if (design_ovl->_69D) {
        gSPDisplayList(POLY_OPA_DISP++, des_win_grid_model);
        gSPDisplayList(POLY_OPA_DISP++, des_win_grid2_model);
    }
    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    mDE_set_frame_main_dl(submenu, game, menu);
    mDE_set_frame_tool_dl(submenu, game, menu);
    mDE_set_frame_suuji_dl(submenu, game, menu);
    mDE_set_frame_mark_dl(submenu, game, menu);
    mDE_set_frame_cursor_dl(submenu, game, menu);
}
void mDE_design_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[mSM_OVL_DESIGN];
    menu->pre_draw_func(submenu, game);
    mDE_set_frame_dl(submenu, game, menu);
}

void mDE_design_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    ovl->menu_control.menu_move_func = mDE_design_ovl_move;
    ovl->menu_control.menu_draw_func = mDE_design_ovl_draw;
}

void mDE_design_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_DESIGN];

    ovl->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    menu_info->move_drt = mSM_MOVE_IN_TOP;
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        MaskCat_c* cat = Save_GetPointer(mask_cat);
        design_ovl->palette_no = 15;
        mDE_maskcat_init(cat);
        bcopy(&cat->design.design, &design_ovl->texture, sizeof(design_ovl->texture));
    } else {
        mNW_original_design_c* p;

        design_ovl->image_no = (u8)mNW_get_image_no(submenu, submenu->param0);
        p = &Now_Private->my_org[design_ovl->image_no & 7];

        design_ovl->palette_no = p->palette;
        mNW_CopyOriginalTexture(&design_ovl->texture, p);
    }
    osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->texture));
    design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
    mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    design_ovl->_69D = 1;
    design_ovl->mode = 0;
    design_ovl->_6A4 = 1;
    design_ovl->_6A5 = 1;
    design_ovl->_6CC = 0;
    design_ovl->_6CD = 0;
    design_ovl->_6B4 = 0;
    design_ovl->_6B8 = 0;
    design_ovl->_6C0 = 0;
    design_ovl->_6D8 = 0;
    design_ovl->_6D9 = 0;
    design_ovl->_6DA = 0;
    mDE_setup_action(design_ovl, mDE_MODE_MAIN);
    mDE_main_mode_setup_action(design_ovl, mDE_MAIN_MODE_PEN);
    design_ovl->_650 = 75;
    design_ovl->_654 = -75;
    design_ovl->_660 = 77.5f;
    design_ovl->_664 = -77.5f;
    design_ovl->cursor_x = 15;
    design_ovl->cursor_y = 15;
#ifdef MOUSE_INPUT
    design_ovl->mouse_active = 0;
    design_ovl->centered_x = 0;
    design_ovl->centered_y = 0;
    design_ovl->mouse_tool_active = 0;
    design_ovl->mouse_tool_x = 0;
    design_ovl->mouse_tool_y = 0;
    design_ovl->prev_cursor_x = -1;
    design_ovl->prev_cursor_y = -1;
#endif
    bcopy(&design_ovl->texture, &design_ovl->work_texture, sizeof(design_ovl->work_texture));
    osWritebackDCache(&design_ovl->work_texture, sizeof(design_ovl->work_texture));
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        mDE_mask_cat_mask(design_ovl);
        osWritebackDCache(&design_ovl->work_texture, sizeof(design_ovl->work_texture));
        bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->texture));
        osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->texture));
    }
    bcopy(&design_ovl->texture, &design_ovl->undo_texture, sizeof(design_ovl->undo_texture));
    osWritebackDCache(&design_ovl->undo_texture, sizeof(design_ovl->undo_texture));
}

void mDE_maskcat_init(MaskCat_c* mask_cat) {
    int i;
    mask_cat->palette_no = 15;
    for (i = 0; i < ARRAY_COUNT(mask_cat->design.design.data); i++) {
        mask_cat->design.design.data[i] = 0xff;
    }
}

void mDE_design_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    if (ovl->design_ovl == NULL) {
        mem_clear((u8*)&de_ovl_data, sizeof(de_ovl_data), 0);
        ovl->design_ovl = &de_ovl_data;
    }
    mDE_design_ovl_init(submenu);
    mDE_design_ovl_set_proc(submenu);
}

void mDE_design_ovl_destruct(Submenu* submenu) {
    submenu->overlay->design_ovl = NULL;
}
