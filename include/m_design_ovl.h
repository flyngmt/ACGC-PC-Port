#ifndef M_DESIGN_OVL_H
#define M_DESIGN_OVL_H

#include "types.h"
#include "m_mask_cat.h"
#include "m_submenu_ovl.h"
#include "m_design_ovl_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mDE_MODE_MAIN,
    mDE_MODE_PALLET,
    mDE_MODE_GRID,
    mDE_MODE_TOOL,

    mDE_MODE_NUM
};

enum {
    mDE_MAIN_MODE_PEN,
    mDE_MAIN_MODE_NURI,
    mDE_MAIN_MODE_WAKU,
    mDE_MAIN_MODE_MARK,
    mDE_MAIN_MODE_UNDO,

    mDE_MAIN_MODE_NUM
};

typedef void (*mDE_OVL_PROC)(mDE_Ovl_c* design_ovl);

struct design_ovl_s {
    u16* palette_p;
    // u8 pad[32-4]; // 32-byte align pad
    mNW_original_tex_c texture;
    mNW_original_tex_c work_texture;
    mNW_original_tex_c undo_texture;
    rgb8_t rgb8_pal[mNW_PALETTE_COUNT];
    int _650;
    int _654;
    int _658;
    int _65C;
    f32 _660;
    f32 _664;
    int cursor_x;
    int cursor_y;
    int _670;
    int _674;
    int _678;
    int _67C;
    int _680;
    int _684;
    int _688;
    int _68C;
    int _690;
    int _694;
    u8 _698;
    u8 _699;
    u8 _69A;
    u8 palette_no;
    u8 image_no;
    u8 _69D;
    u8 _69E;
    u8 _69F;
    u8 _6A0;
    u8 _6A1;
    u8 _6A2;
    u8 _6A3;
    u8 _6A4;
    u8 _6A5;
    u8 _6A6;
    u8 mode;
    u8 main_mode_act;
    // u8 pad[3];
    mDE_OVL_PROC act_proc;
    mDE_OVL_PROC main_mode_proc;
    u8 _6B4;
    u8 _6B5;
    u8 _6B6;
    u8 _6B7;
    u32 _6B8;
    u32 _6BC;
    u32 _6C0;
    u32 _6C4;
    f32 move_pR;
    u8 _6CC;
    u8 _6CD;
    u8 _6CE;
    u8 _6CF;
    u32 _6D0;
    u32 _6D4;
    u8 _6D8;
    u8 _6D9;
    u8 _6DA;
    u8 _6DB;
    u8 _6DC;
#ifdef MOUSE_INPUT
    int mouse_active;
    int centered_x;
    int centered_y;
    int mouse_tool_active;
    int mouse_tool_x;
    int mouse_tool_y;
    int prev_cursor_x;
    int prev_cursor_y;
#endif
};

extern void mDE_maskcat_init(MaskCat_c* mask_cat);

extern void mDE_design_ovl_construct(Submenu* submenu);
extern void mDE_design_ovl_destruct(Submenu* submenu);
extern void mDE_design_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
