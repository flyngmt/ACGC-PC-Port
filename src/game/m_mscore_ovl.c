#include "m_mscore_ovl.h"

#include "m_submenu_ovl.h"
#include "audio.h"
#include "m_common_data.h"
#include "m_editEndChk_ovl.h"
#include "m_melody.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_bgm.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

#define mMS_NOTE_SPACING_X 21.0f
#define mMS_NOTE_SPACING_Y 50.0f

static mMS_Ovl_c mscore_ovl_data;

enum {
    mMS_SCALE_IN,
    mMS_SCALE_OUT,
    mMS_SCALE_WAIT,

    mMS_SCALE_NUM
};

enum {
    mMS_FRAME_NORMAL,
    mMS_FRAME_REST,
    mMS_FRAME_OFF,
    mMS_FRAME_RANDOM,
    mMS_FRAME_END,

    mMS_FRAME_NUM
};

typedef struct {
    u8* tex[2];
    Gfx* model;
    f32 offset[2];
} mMS_note_frame_c;

extern u8 onp_win_q_tex_rgb_i4[];
extern u8 onp_win_a_tex_rgb_i4[];
extern u8 onp_win_b_tex_rgb_i4[];
extern u8 onp_win_c_tex_rgb_i4[];
extern u8 onp_win_d_tex_rgb_i4[];
extern u8 onp_win_e_tex_rgb_i4[];
extern u8 onp_win_f_tex_rgb_i4[];
extern u8 onp_win_g_tex_rgb_i4[];

extern u8 onp_win_bou1_tex[];
extern u8 onp_win_shimari_tex_rgb_ia8[];
extern u8 onp_win_onpu8_tex_rgb_i4[];
extern u8 onp_win_z_tex_rgb_i4[];

extern u8 onp_win_test1_tex_rgb_ia8[];
extern u8 onp_win_test2_tex_rgb_ia8[];
extern u8 onp_win_test3_tex_rgb_ia8[];
extern u8 onp_win_test5_tex_rgb_ia8[];
extern u8 onp_win_test10_tex_rgb_ia8[];
extern u8 onp_win_test11_tex_rgb_ia8[];
extern u8 onp_win_shimari_tex_rgb_ia8[];

extern Gfx onp_hyouji_waku1T_model[];
extern Gfx onp_hyouji_waku2T_model[];
extern Gfx onp_hyouji_waku3T_model[];
extern Gfx onp_hyouji_waku4T_model[];
extern Gfx onp_hyouji_bouT_model[];
extern Gfx onp_hyouji_moji1T_model[];
extern Gfx onp_hyouji_waku_mode[];
extern Gfx onp_hyouji_moji_mode[];

// clang-format off
static mMS_note_frame_c note_frame[] = {
    {
        { onp_win_test1_tex_rgb_ia8, onp_win_test2_tex_rgb_ia8 },
        onp_hyouji_waku1T_model,
        { 0.0f, 0.0f }
    },
    {
        { onp_win_test2_tex_rgb_ia8, onp_win_test3_tex_rgb_ia8 },
        onp_hyouji_waku2T_model,
        { -1.0f, 20.0f }
    },
    {
        { onp_win_test5_tex_rgb_ia8, onp_win_shimari_tex_rgb_ia8 },
        onp_hyouji_waku3T_model,
        { 1.0f, 1.0f }
    },
    {
        { onp_win_test10_tex_rgb_ia8, onp_win_test11_tex_rgb_ia8 },
        onp_hyouji_waku4T_model,
        { -1.0f, 5.0f }
    },
};
// clang-format on

typedef struct {
    mMS_note_frame_c* frame;
    u8* tex;
    f32 ofs_y;
    int prim_color[3];
    int env_color[3];
} mMS_note_moji_c;

// clang-format onff
static mMS_note_moji_c note_moji[] = {
    { &note_frame[mMS_FRAME_NORMAL], onp_win_g_tex_rgb_i4, -29.0f, { 0, 10, 0 }, { 70, 155, 255 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_a_tex_rgb_i4, -29.0f, { 0, 10, 0 }, { 0, 200, 205 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_b_tex_rgb_i4, -29.0f, { 0, 20, 0 }, { 0, 225, 150 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_c_tex_rgb_i4, -23.0f, { 0, 40, 0 }, { 20, 235, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_d_tex_rgb_i4, -23.0f, { 0, 40, 0 }, { 90, 245, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_e_tex_rgb_i4, -23.0f, { 0, 40, 0 }, { 130, 255, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_f_tex_rgb_i4, -23.0f, { 0, 50, 0 }, { 155, 255, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_g_tex_rgb_i4, -23.0f, { 0, 50, 0 }, { 175, 255, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_a_tex_rgb_i4, -23.0f, { 0, 60, 0 }, { 195, 255, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_b_tex_rgb_i4, -23.0f, { 0, 60, 0 }, { 225, 255, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_c_tex_rgb_i4, -16.0f, { 0, 60, 0 }, { 255, 235, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_d_tex_rgb_i4, -16.0f, { 0, 60, 0 }, { 255, 215, 0 } },
    { &note_frame[mMS_FRAME_NORMAL], onp_win_e_tex_rgb_i4, -16.0f, { 0, 70, 0 }, { 255, 175, 0 } },
    { &note_frame[mMS_FRAME_RANDOM], onp_win_q_tex_rgb_i4, -20.0f, { 70, 60, 30 }, { 255, 110, 110 } },
    { &note_frame[mMS_FRAME_REST], onp_win_z_tex_rgb_i4, -29.0f, { 10, 10, 0 }, { 165, 100, 255 } },
    { &note_frame[mMS_FRAME_OFF], onp_win_onpu8_tex_rgb_i4, -29.0f, { 60, 0, 60 }, { 255, 50, 255 } },
};
// clang-format on

static u8 mMS_str_title[13] = "Are you sure?";
static u8 mMS_str_ok[3] = "Yes";
static u8 mMS_str_cancel[2] = "No";

static void mMS_note_position(int idx, f32* x, f32* y) {
    *x = -91.0f + (idx % 8) * mMS_NOTE_SPACING_X + (idx / 8) * 20.0f;
    *y = 64.0f - (idx / 8) * mMS_NOTE_SPACING_Y;
}

#ifdef MOUSE_INPUT
extern Vtx onp_hyouji2_v[];
extern Vtx onp_win_v[];
extern Vtx onp_carde_v[];

static u32 mMS_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu_info, u32 trigger) {
    /* Control quads from onp_hyouji2.c and onp_win.c. */
    static const struct {
        Vtx* vertices;
        u32 trigger;
    } controls[] = {
        { &onp_hyouji2_v[0], BUTTON_Y }, { &onp_hyouji2_v[4], BUTTON_X },
        { &onp_hyouji2_v[8], BUTTON_X }, { &onp_hyouji2_v[12], BUTTON_Y },
        { &onp_hyouji2_v[16], BUTTON_X }, { &onp_hyouji2_v[20], BUTTON_Y },
        { &onp_hyouji2_v[24], BUTTON_START }, { &onp_win_v[142], BUTTON_START },
        { &onp_carde_v[0], BUTTON_R }, { &onp_carde_v[4], BUTTON_R },
        { &onp_carde_v[8], BUTTON_R }, { &onp_carde_v[12], BUTTON_R }
    };
    mMS_Ovl_c* mscore_ovl = submenu->overlay->mscore_ovl;
    f32 mouse_x, mouse_y;
    u32 pressed;
    int i;

    if (submenu->current_menu_type != mSM_OVL_MSCORE ||
        !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.move_pR > 0.5f) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return trigger;
    }

    mouse_x -= menu_info->position[0];
    mouse_y += menu_info->position[1];
    pressed = pc_mouse_button_pressed();
    if (menu_info->proc_status == mSM_OVL_PROC_OBEY) {
        if (pressed & PC_MOUSE_BUTTON_RIGHT) {
            return trigger | BUTTON_B;
        }
        for (i = 0; i < 2; i++) {
            u8* str = i == 0 ? mMS_str_ok : mMS_str_cancel;
            int len = i == 0 ? sizeof(mMS_str_ok) : sizeof(mMS_str_cancel);
            f32 y = 142.0f + i * 16.0f;
            f32 width = mFont_GetStringWidth(str, len, TRUE) * 0.875f;

            if (mouse_x >= 121.0f && mouse_x < 121.0f + width && mouse_y >= y && mouse_y < y + 16.0f) {
                if (mscore_ovl->menu_idx != i) {
                    mscore_ovl->menu_idx = i;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
                return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
            }
        }
        return trigger;
    }

    for (i = 0; i < ARRAY_COUNT(controls); i++) {
        if (mSM_mouse_over_quad(controls[i].vertices, mouse_x - 160.0f, 120.0f - mouse_y, 0.0f)) {
            if (controls[i].trigger == BUTTON_START) {
                mscore_ovl->cursor_idx = 16;
            }
            if (pressed & PC_MOUSE_BUTTON_LEFT) {
                return trigger | controls[i].trigger;
            }
            return trigger | ((pressed & PC_MOUSE_BUTTON_RIGHT) ? BUTTON_START : 0);
        }
    }

    for (i = 0; i < 16; i++) {
        f32 x, y;

        mMS_note_position(i, &x, &y);
        x += 160.0f - mMS_NOTE_SPACING_X * 0.5f;
        y = 120.0f - y;
        if (mouse_x >= x && mouse_x < x + mMS_NOTE_SPACING_X && mouse_y >= y && mouse_y < y + mMS_NOTE_SPACING_Y) {
            s32 wheel = pc_mouse_scroll_wheel();

            mscore_ovl->cursor_idx = i;
            if (wheel > 0 || (pressed & PC_MOUSE_BUTTON_LEFT)) {
                trigger |= BUTTON_CUP;
            } else if (wheel < 0 || (pressed & PC_MOUSE_BUTTON_RIGHT)) {
                trigger |= BUTTON_CDOWN;
            }
            return trigger;
        }
    }

    return trigger | ((pressed & PC_MOUSE_BUTTON_RIGHT) ? BUTTON_START : 0);
}
#endif

static void mMS_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mMS_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static u16 single_se[] = {
        NA_SE_NOTE_G_LOW,
        NA_SE_NOTE_A_LOW,
        NA_SE_NOTE_B_LOW,
        NA_SE_NOTE_C_LOW,
        NA_SE_NOTE_D_LOW,
        NA_SE_NOTE_E_LOW,
        NA_SE_NOTE_F_LOW,
        NA_SE_NOTE_G,
        NA_SE_NOTE_A,
        NA_SE_NOTE_B,
        NA_SE_NOTE_C,
        NA_SE_NOTE_D,
        NA_SE_NOTE_E,
        NA_SE_NOTE_RANDOM,
        0, // hold
        0, // off
    };
    int note_idx;
    int previous_note_idx;
    mMS_Ovl_c* mscore_ovl = submenu->overlay->mscore_ovl;
    u32 trigger;
    u8* note_p;

    if (submenu->current_menu_type != mSM_OVL_MSCORE) {
        return;
    }

    if (mscore_ovl->wait_timer > 0) {
        static float wait_accum = 0.0f;
        int old_timer = mscore_ovl->wait_timer;
        int ticks = graph_dt_60hz_ticks(gamePT, &wait_accum);
        mscore_ovl->wait_timer -= ticks;
        if (mscore_ovl->wait_timer < 0) {
            mscore_ovl->wait_timer = 0;
        }

        if (old_timer > 1 && mscore_ovl->wait_timer <= 1) {
            sAdo_Inst(0, mscore_ovl->melody);
        }

        return;
    }

    if (sAdo_InstCountGet() >= 0) {
        return;
    }

    trigger = submenu->overlay->menu_control.trigger;
    if (mscore_ovl->cursor_idx == -1) {
        mscore_ovl->cursor_idx = 0;
    }

    previous_note_idx = mscore_ovl->cursor_idx;
#ifdef MOUSE_INPUT
    trigger = mMS_mouse_trigger(submenu, menu_info, trigger);
#endif
    note_idx = mscore_ovl->cursor_idx;
    if (note_idx < 16) {
        note_p = &mscore_ovl->melody[note_idx];
    } else {
        note_p = NULL;
    }

    if ((trigger & BUTTON_X) != 0) {
        sAdo_Inst(0, mscore_ovl->melody);
    } else if ((trigger & BUTTON_Y) != 0) {
        menu_info->proc_status = mSM_OVL_PROC_OBEY;
        mscore_ovl->menu_idx = 0;
        mscore_ovl->scale = 0.0f;
        mscore_ovl->scale_dir = mMS_SCALE_IN;
        sAdo_SysTrgStart(NA_SE_33);
    } else if ((trigger & BUTTON_R) != 0) {
        submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_TOP);
        submenu->after_mode = aHOI_REQUEST_NUM;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else if ((trigger & BUTTON_START) != 0 || (note_idx == 16 && (trigger & BUTTON_A) != 0)) {
        mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_MSCORE, 0);
        menu_info->proc_status = mSM_OVL_PROC_WAIT;
        mscore_ovl->anim_frame = 0;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else if ((trigger & (BUTTON_A | BUTTON_CRIGHT)) != 0) {
        if (note_idx != 16) {
            mscore_ovl->cursor_idx++;
        }
    } else if ((trigger & (BUTTON_B | BUTTON_CLEFT)) != 0) {
        if (note_idx != 0) {
            mscore_ovl->cursor_idx--;
        }
    } else if (note_idx != 16) {
        if ((trigger & BUTTON_CDOWN) != 0) {
            if (*note_p != 14) {
                if (*note_p == 0) {
                    *note_p = 15;
                } else {
                    (*note_p)--;
                    sAdo_SysTrgStart(single_se[*note_p]);
                }
            }
        } else if ((trigger & BUTTON_CUP)) {
            if (*note_p != 13) {
                if (*note_p == 15) {
                    *note_p = 0;
                } else {
                    (*note_p)++;
                }

                if (*note_p != 14 && *note_p != 15) {
                    sAdo_SysTrgStart(single_se[*note_p]);
                }
            }
        }
    }

    if (previous_note_idx != mscore_ovl->cursor_idx) {
        mscore_ovl->anim_frame = 0;
        if (mscore_ovl->cursor_idx != 16) {
            u8 note = mscore_ovl->melody[mscore_ovl->cursor_idx];

            if (note != 14 && note != 15 &&
                (note_idx == previous_note_idx || !(trigger & (BUTTON_CUP | BUTTON_CDOWN)))) {
                sAdo_SysTrgStart(single_se[note]);
            }
        } else {
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    } else {
        mscore_ovl->anim_frame = (mscore_ovl->anim_frame + 1) % 18;
    }
}

static void mMS_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMS_Ovl_c* mscore_ovl = submenu->overlay->mscore_ovl;
    mSM_MenuInfo_c* edit_end_menu = &submenu->overlay->menu_info[mSM_OVL_EDITENDCHK];

    if (edit_end_menu->proc_status == mSM_OVL_PROC_MOVE && edit_end_menu->next_proc_status == mSM_OVL_PROC_END) {
        if (edit_end_menu->data1 == 0) {
            mMld_SetSaveMelody(mscore_ovl->melody);
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_TOP);
        } else if (edit_end_menu->data1 == 1) {
            mscore_ovl->anim_frame = 0;
            mscore_ovl->cursor_idx = 0;
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
        } else {
            mMld_SetSaveMelody((u8*)menu_info->data3);
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_TOP);
        }
    }
}

static void mMS_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMS_Ovl_c* mscore_ovl = submenu->overlay->mscore_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;
    f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;

    if (mscore_ovl->scale_dir == mMS_SCALE_IN) {
        mscore_ovl->scale += 0.25f * dt;
        if (mscore_ovl->scale >= 1.0f) {
            mscore_ovl->scale = 1.0f;
            mscore_ovl->scale_dir = mMS_SCALE_WAIT;
        }
    } else if (mscore_ovl->scale_dir == mMS_SCALE_OUT) {
        mscore_ovl->scale -= 0.25f * dt;
        if (mscore_ovl->scale < 0.0f) {
            mscore_ovl->scale = 0.0f;
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
        }
    } else {
#ifdef MOUSE_INPUT
        trigger = mMS_mouse_trigger(submenu, menu_info, trigger);
#endif
        if ((trigger & BUTTON_A) != 0) {
            if (mscore_ovl->menu_idx == 0) {
                int i;

                for (i = 0; i < 16; i++) {
                    mscore_ovl->melody[i] = 14;
                }

                sAdo_SysTrgStart(NA_SE_114);
            } else {
                sAdo_SysTrgStart(MONO(NA_SE_3));
            }

            mscore_ovl->scale_dir = mMS_SCALE_OUT;
        } else if ((trigger & BUTTON_B) != 0) {
            sAdo_SysTrgStart(MONO(NA_SE_3));
            mscore_ovl->scale_dir = mMS_SCALE_OUT;
        } else if ((trigger & BUTTON_CDOWN) != 0) {
            if (mscore_ovl->menu_idx == 0) {
                mscore_ovl->menu_idx = 1;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        } else if ((trigger & BUTTON_CUP) != 0) {
            if (mscore_ovl->menu_idx == 1) {
                mscore_ovl->menu_idx = 0;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        }
    }

    mscore_ovl->anim_frame = (mscore_ovl->anim_frame + 1) % 18;
}

static void mMS_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}
typedef void (*mMS_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mMS_mscore_ovl_move(Submenu* submenu) {
    static mMS_OVL_PROC ovl_move_proc[] = {
        &mMS_move_Move, &mMS_move_Play, &mMS_move_Wait, &mMS_move_Obey, &mMS_move_End,
    };

    mSM_Control_c* control = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MSCORE];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

static void mMS_MScore_draw_init(mSM_MenuInfo_c* menu_info) {
    // empty
}

extern u8 start2_tex_rgb_ia8[];
extern u8 start_tex_rgb_ia8[];
extern u8 onp__x2_tex_rgb_ia8[];
extern u8 onp__x_tex_rgb_ia8[];
extern u8 onp__y2_tex_rgb_ia8[];
extern u8 onp__y_tex_rgb_ia8[];
extern u8 onp_win_rbutton2_tex_rgb_ia8[];
extern u8 onp_win_rbutton_tex_rgb_ia8[];

extern Gfx onp_win_model[];
extern Gfx onp_win_mojiT_model[];
extern Gfx onp_win_zT_model[];
extern Gfx onp_win_rT_model[];
extern Gfx onp_win_sT_model[];
#if VERSION == VER_GAFE01_00
extern Gfx onp_win_rmoji_model[];
#else
extern Gfx onp_win_rmoji_model_1_data_4A4020[];
#endif
extern Gfx onp_win_owariT_model[];

extern Gfx sen_item2_DL_mode[];
extern Gfx sen_win_wakuT_model[];
extern Gfx sen_win_cursor_model[];

static void mMS_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    static rgb_t color_data[] = { { 255, 0, 0 }, { 0, 0, 255 } };
    static rgb_t sel_str_color_data[] = { { 140, 160, 205 }, { 70, 70, 225 } };
    static u8* mMS_start_button_tex_tbl[] = { start_tex_rgb_ia8, start2_tex_rgb_ia8 };
    static u8* mMS_y_button_tex_tbl[] = { onp__y_tex_rgb_ia8, onp__y2_tex_rgb_ia8 };
    static u8* mMS_x_button_tex_tbl[] = { onp__x_tex_rgb_ia8, onp__x2_tex_rgb_ia8 };
    static u8* mMS_r_button_tex_tbl[] = { onp_win_rbutton_tex_rgb_ia8, onp_win_rbutton2_tex_rgb_ia8 };
    GRAPH* graph;
    mMS_note_moji_c* note_moji_p;
    rgb_t* color_p;
    f32 base_x;
    f32 base_y;
    f32 scale;
    f32 stick_x;
    f32 stick_y;
    int i;
    int inst_count;
    int play_idx;
    int cursor_idx;
    int button_flag;
    mMS_Ovl_c* mscore_ovl;
    f32 pos_x;
    f32 pos_y;
    f32 anm_scale;
    f32 text_scale;
    int idx;

    graph = game->graph;
    mscore_ovl = submenu->overlay->mscore_ovl;
    pos_x = menu_info->position[0];
    pos_y = menu_info->position[1];
    anm_scale = mscore_ovl->scale;
    inst_count = sAdo_InstCountGet();

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 1.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    button_flag = (menu_info->proc_status == mSM_OVL_PROC_PLAY || menu_info->proc_status == mSM_OVL_PROC_OBEY ||
                   (menu_info->proc_status == mSM_OVL_PROC_WAIT &&
                    submenu->overlay->menu_info[mSM_OVL_EDITENDCHK].proc_status == mSM_OVL_PROC_MOVE));
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mMS_x_button_tex_tbl[button_flag & ((getButton() & BUTTON_X) != 0)]);
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mMS_y_button_tex_tbl[button_flag & ((getButton() & BUTTON_Y) != 0)]);
    gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, mMS_r_button_tex_tbl[button_flag & ((getButton() & BUTTON_R) != 0)]);
    idx = button_flag & ((getButton() & BUTTON_START) != 0);
    gSPSegment(POLY_OPA_DISP++, ANIME_3_TXT_SEG, mMS_start_button_tex_tbl[idx]);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_model);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_mojiT_model);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_zT_model);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_rT_model);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_sT_model);
#if VERSION == VER_GAFE01_00
    gSPDisplayList(POLY_OPA_DISP++, onp_win_rmoji_model);
#else
    gSPDisplayList(POLY_OPA_DISP++, onp_win_rmoji_model_1_data_4A4020);
#endif
    color_p = (mscore_ovl->cursor_idx == 16) ? &color_data[0] : &color_data[1];
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, color_p->r, color_p->g, color_p->b, 255);
    gSPDisplayList(POLY_OPA_DISP++, onp_win_owariT_model);

    if (inst_count >= 0) {
        cursor_idx = -1;
        play_idx = inst_count;
    } else {
        cursor_idx = mscore_ovl->cursor_idx;
        play_idx = cursor_idx < 0 ? 0 : cursor_idx;
    }

    if (cursor_idx != 16) {
        stick_x = -91.0f + 21.2f * (play_idx % 8) + ((play_idx < 8) ? 0.0f : 19.0f);
        stick_y = 20.0f + ((play_idx < 8) ? 0.0f : -50.0f);

        Matrix_translate(stick_x, stick_y, 0.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, onp_hyouji_moji_mode);
        gSPDisplayList(POLY_OPA_DISP++, onp_hyouji_bouT_model);
    }

    if (inst_count < 0) {
        play_idx = -1;
    }

    gSPDisplayList(POLY_OPA_DISP++, onp_hyouji_waku_mode);

    scale = 1.0f + (1.0f - cosf_table((f32)mscore_ovl->anim_frame * ((f32)M_PI / 9.0f))) * 0.075f;

    for (i = 0; i < 16; i++) {
        mMS_note_position(i, &base_x, &base_y);
        base_x += pos_x;
        base_y += pos_y;
        note_moji_p = &note_moji[mscore_ovl->melody[i]];
        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(base_x, base_y + note_moji_p->ofs_y, 0.0f, MTX_MULT);
        if (i == cursor_idx) {
            Matrix_scale(scale, scale, 1.0f, MTX_MULT);
        }

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, note_moji_p->prim_color[0], note_moji_p->prim_color[1],
                        note_moji_p->prim_color[2], 255);
        gDPSetEnvColor(POLY_OPA_DISP++, note_moji_p->env_color[0], note_moji_p->env_color[1], note_moji_p->env_color[2],
                       255);
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, note_moji_p->frame->tex[i == play_idx]);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, note_moji_p->frame->model);
    }

    gSPDisplayList(POLY_OPA_DISP++, onp_hyouji_moji_mode);

    for (i = 0; i < 16; i++) {
        mMS_note_position(i, &base_x, &base_y);
        base_x += pos_x;
        base_y += pos_y;
        if (i != play_idx) {
            note_moji_p = &note_moji[mscore_ovl->melody[i]];
            Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
            Matrix_translate(base_x + note_moji_p->frame->offset[0],
                             base_y + note_moji_p->frame->offset[1] + note_moji_p->ofs_y, 0.0f, MTX_MULT);

            if (i == cursor_idx) {
                Matrix_scale(scale, scale, 1.0f, MTX_MULT);
                color_p = &color_data[0];
            } else {
                color_p = &color_data[1];
            }

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, color_p->r, color_p->g, color_p->b, 255);
            gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, note_moji_p->tex);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, onp_hyouji_moji1T_model);
        }
    }

    CLOSE_POLY_OPA_DISP(graph);

    if (menu_info->proc_status == mSM_OVL_PROC_OBEY && !F32_IS_ZERO(anm_scale)) {
        OPEN_POLY_OPA_DISP(graph);

        gSPDisplayList(POLY_OPA_DISP++, sen_item2_DL_mode);
        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
        gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);

        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(-17.0f + pos_x, -65.0f + pos_y, 140.0f, MTX_MULT);
        Matrix_scale(anm_scale, anm_scale, 1.0f, MTX_MULT);
        Matrix_push();

        Matrix_translate(16.0f, 35.0f, 0.0f, MTX_MULT);
        Matrix_scale(0.897059f, 0.708333f, 1.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 225, 255, 175, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 255, 40, 255);
        gSPDisplayList(POLY_OPA_DISP++, sen_win_wakuT_model);
        Matrix_pull();

        Matrix_translate(-26.0f, 51.0f - (mscore_ovl->menu_idx + 1) * 16, 0.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 235, 60, 60, 255);
        gSPDisplayList(POLY_OPA_DISP++, sen_win_cursor_model);

        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
        gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 8);

        CLOSE_POLY_OPA_DISP(graph);

        base_x = 160.0f + (-17.0f + pos_x + -22.0f * anm_scale);
        base_y = 120.0f - (-65.0f + pos_y + 59.0f * anm_scale);
        text_scale = anm_scale * 0.875f;

        submenu->overlay->set_char_matrix_proc(graph);
        mFont_SetLineStrings(game, mMS_str_title, sizeof(mMS_str_title), base_x, base_y, 255, 60, 60, 255, FALSE, TRUE,
                             text_scale, text_scale, mFont_MODE_POLY);
        color_p = &sel_str_color_data[mscore_ovl->menu_idx == 0];
        base_y += 16.0f * anm_scale;
        mFont_SetLineStrings(game, mMS_str_ok, sizeof(mMS_str_ok), base_x, base_y, color_p->r, color_p->g, color_p->b,
                             255, FALSE, TRUE, text_scale, text_scale, mFont_MODE_POLY);
        color_p = &sel_str_color_data[mscore_ovl->menu_idx == 1];
        base_y += 16.0f * anm_scale;
        mFont_SetLineStrings(game, mMS_str_cancel, sizeof(mMS_str_cancel), base_x, base_y, color_p->r, color_p->g,
                             color_p->b, 255, FALSE, TRUE, text_scale, text_scale, mFont_MODE_POLY);
    }
}

static void mMS_mscore_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MSCORE];

    menu_info->pre_draw_func(submenu, game);
    mMS_set_dl(submenu, menu_info, game);
}

extern void mMS_mscore_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mMS_mscore_ovl_move;
    control->menu_draw_func = &mMS_mscore_ovl_draw;
}

static void mMS_mscore_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MSCORE];
    mMS_Ovl_c* mscore_ovl = submenu->overlay->mscore_ovl;

    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_TOP);
    submenu->overlay->menu_control.animation_flag = FALSE;
    mscore_ovl->anim_frame = 0;
    mscore_ovl->wait_timer = 10;
    mscore_ovl->cursor_idx = -1;
    mMld_GetMelody(mscore_ovl->melody);
}

extern void mMS_mscore_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->mscore_ovl == NULL) {
        mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_MSCORE];

        mem_clear((u8*)&mscore_ovl_data, sizeof(mscore_ovl_data), 0);
        overlay->mscore_ovl = &mscore_ovl_data;
        mMS_MScore_draw_init(menu_info);
    }

    mMS_mscore_ovl_init(submenu);
    mMS_mscore_ovl_set_proc(submenu);
    mBGMPsComp_pause(mBGM_PAUSE_MSCORE);
}

extern void mMS_mscore_ovl_destruct(Submenu* submenu) {
    submenu->overlay->mscore_ovl = NULL;
    mBGMPsComp_pause(mBGM_PAUSE_STOP);
}
