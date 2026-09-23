#include "m_editEndChk_ovl.h"

#include "audio.h"
#include "m_common_data.h"
#include "m_font.h"
#include "sys_matrix.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

typedef struct editEndChk_win_data_s {
    int answer_num;
    Gfx* win_model;
    Gfx* char_model;
    f32 char_x;
    f32 char_y;
    f32 answer_x;
    f32 answer_y;
    f32 question_x;
    f32 question_y;
} mEE_win_data_c;

extern Gfx lat_sentaku2_winT_model[];
extern Gfx lat_sentaku2_c_model[];

extern Gfx lat_sentaku_winT_model[];
extern Gfx lat_sentaku_c_model[];

static mEE_win_data_c win_data[] = {
    { 2, lat_sentaku2_winT_model, lat_sentaku2_c_model, -45.0f, 43.0f, 65.0f, -74.0f, 0.0f, 0.0f },
    { 3, lat_sentaku_winT_model, lat_sentaku_c_model, -81.0f, 58.0f, 60.0f, -71.0f, 1.0f, -4.0f },
    { 3, lat_sentaku_winT_model, lat_sentaku_c_model, -81.0f, 58.0f, 42.0f, -55.0f, 1.0f, 15.0f },
    { 3, lat_sentaku_winT_model, lat_sentaku_c_model, -81.0f, 58.0f, 60.0f, -71.0f, 0.0f, 0.0f },
    { 3, lat_sentaku_winT_model, lat_sentaku_c_model, -81.0f, 58.0f, 60.0f, -71.0f, 1.0f, -4.0f },
};

static u8 mEE_str_table[11] = "Is this OK?";
static u8 mEE_str_data0[3] = "Yes";
static u8 mEE_str_data1[7] = "Rewrite";
static u8 mEE_str_data2[12] = "Throw it out";

typedef struct editEndChk_str_s {
    u8* str;
    int len;
} mEE_str_c;

static mEE_str_c mEE_answer_strings[] = {
    { mEE_str_data0, sizeof(mEE_str_data0) },
    { mEE_str_data1, sizeof(mEE_str_data1) },
    { mEE_str_data2, sizeof(mEE_str_data2) },
};

#ifdef MOUSE_INPUT
static u32 mEE_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu_info, u32 trigger) {
    mEE_Ovl_c* editEndChk_ovl = submenu->overlay->editEndChk_ovl;
    mEE_win_data_c* data = &win_data[menu_info->data0];
    f32 mouse_x, mouse_y;
    u32 pressed;
    f32 x, y;
    int i;

    if (submenu->current_menu_type != mSM_OVL_EDITENDCHK ||
        !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.move_pR > 0.5f) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return trigger;
    }

    pressed = pc_mouse_button_pressed();
    if (pressed & PC_MOUSE_BUTTON_RIGHT) {
        return trigger | BUTTON_B;
    }
    if (!editEndChk_ovl->moving_in) {
        return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
    }
    if (editEndChk_ovl->scale < 1.0f) {
        return trigger;
    }

    x = 160.0f + menu_info->position[0] + data->answer_x + data->char_x;
    y = 120.0f - menu_info->position[1] - data->answer_y - data->char_y;
    for (i = 0; i < data->answer_num; i++, y += 16.0f) {
        mEE_str_c* answer = &mEE_answer_strings[i];
        f32 width = mFont_GetStringWidth(answer->str, answer->len, TRUE);
        if (mouse_x >= x && mouse_x < x + width && mouse_y >= y && mouse_y < y + 16.0f) {
            if (editEndChk_ovl->selected_answer != i) {
                editEndChk_ovl->selected_answer = i;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
            if (pressed & PC_MOUSE_BUTTON_LEFT) {
                trigger |= BUTTON_A;
            }
            break;
        }
    }
    return trigger;
}
#endif

static void mEE_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mEE_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mEE_win_data_c* data = &win_data[menu_info->data0];
    mEE_Ovl_c* editEndChk_ovl = submenu->overlay->editEndChk_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;
    int max_answer_no = data->answer_num - 1;
    f32 dt = gamePT->graph->dt_num_60fps_frames;

#ifdef MOUSE_INPUT
    trigger = mEE_mouse_trigger(submenu, menu_info, trigger);
#endif

    if ((trigger & BUTTON_B)) {
        sAdo_SysTrgStart(0x1003);
        menu_info->proc_status = mSM_OVL_PROC_MOVE;
        menu_info->move_drt = mSM_MOVE_OUT_BOTTOM;
        menu_info->next_proc_status = mSM_OVL_PROC_END;
        menu_info->data1 = 1;
    } else if ((trigger & (BUTTON_A | BUTTON_START))) {
        if (editEndChk_ovl->moving_in == FALSE) {
            editEndChk_ovl->moving_in = TRUE;
            editEndChk_ovl->scale = 0.0f;
        } else {
            menu_info->proc_status = mSM_OVL_PROC_MOVE;
            menu_info->move_drt = mSM_MOVE_OUT_BOTTOM;
            menu_info->next_proc_status = mSM_OVL_PROC_END;
            menu_info->data1 = editEndChk_ovl->selected_answer;
        }

        if (menu_info->data1 == 2) {
            sAdo_SysTrgStart(0x1003);
        } else {
            sAdo_SysTrgStart(NA_SE_MENU_EXIT);
        }
    } else if (editEndChk_ovl->moving_in == TRUE) {
        if (editEndChk_ovl->scale < 1.0f) {
            editEndChk_ovl->scale += 0.2f * dt;
            if (editEndChk_ovl->scale > 1.0f) {
                editEndChk_ovl->scale = 1.0f;
            }
        } else {
            editEndChk_ovl->scale = 1.0f;

            if ((trigger & BUTTON_CUP)) {
                if (editEndChk_ovl->selected_answer != 0) {
                    editEndChk_ovl->selected_answer--;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            } else if ((trigger & BUTTON_CDOWN)) {
                if (editEndChk_ovl->selected_answer < max_answer_no) {
                    editEndChk_ovl->selected_answer++;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            }
        }

        editEndChk_ovl->question_alpha_step = 0;
        editEndChk_ovl->question_alpha = 0;
        editEndChk_ovl->question_alpha_accum = 0.0f;
    } else {
        int step;

        editEndChk_ovl->question_alpha_accum += dt;
        while (editEndChk_ovl->question_alpha_accum >= 1.0f) {
            editEndChk_ovl->question_alpha_step = (editEndChk_ovl->question_alpha_step + 1) % 30;
            editEndChk_ovl->question_alpha_accum -= 1.0f;
        }

        step = editEndChk_ovl->question_alpha_step;
        editEndChk_ovl->question_alpha_step = step;
        if (step < 15) {
            editEndChk_ovl->question_alpha = ((f32)step * 255.0f) / 15.0f;
        } else {
            editEndChk_ovl->question_alpha = ((f32)(30 - step) * 255.0f) / 15.0f;
        }
    }
}

static void mEE_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mEE_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mEE_editEndChk_ovl_move(Submenu* submenu) {
    static mEE_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = { &mEE_move_Move, &mEE_move_Play,
                                                                 (mEE_OVL_MOVE_PROC)&none_proc1,
                                                                 (mEE_OVL_MOVE_PROC)&none_proc1, mEE_move_End };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITENDCHK];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx lat_kakunin_DL_mode[];
extern Gfx lat_kakunin_wakuT_model[];
extern Gfx lat_kakunin_c_model[];

static void mEE_set_question_field(Submenu* submenu, GRAPH* graph, f32 x, f32 y) {
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_kakunin_DL_mode);
    gSPDisplayList(gfx++, lat_kakunin_wakuT_model);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 255, 0, 0, 255, submenu->overlay->editEndChk_ovl->question_alpha);
    gSPDisplayList(gfx++, lat_kakunin_c_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mEE_set_answer_field(Submenu* submenu, GRAPH* graph, mEE_win_data_c* data, f32 x, f32 y) {
    f32 scale = submenu->overlay->editEndChk_ovl->scale;
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_kakunin_DL_mode);
    gSPDisplayList(gfx++, data->win_model);

    if (scale == 1.0f) {
        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(x, y - ((f32)submenu->overlay->editEndChk_ovl->selected_answer * 16.0f), 140.0f, MTX_MULT);
        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, data->char_model);
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mEE_set_question_character(Submenu* submenu, GRAPH* graph, GAME* game, f32 x, f32 y) {
    (*submenu->overlay->set_char_matrix_proc)(graph);
    mFont_SetLineStrings(game, mEE_str_table, sizeof(mEE_str_table), 107.0f + x, 194.0f - y, 80, 80, 230, 255, FALSE,
                         TRUE, 1.0f, 1.0f, mFont_MODE_POLY);
}

static void mEE_set_answer_character(Submenu* submenu, GRAPH* graph, GAME* game, mEE_win_data_c* data, f32 x, f32 y) {
    static int col_table[2][3] = { { 165, 185, 185 }, { 100, 130, 245 } };

    mEE_Ovl_c* editEndChk_ovl = submenu->overlay->editEndChk_ovl;
    mEE_str_c* str_p = mEE_answer_strings;
    f32 scale = editEndChk_ovl->scale;
    int max = data->answer_num;
    int i;

    (*submenu->overlay->set_char_matrix_proc)(graph);
    x = (160.0f + x) + (data->char_x * scale);
    y = (120.0f - y) - (data->char_y * scale);

    for (i = 0; i < max; i++, str_p++) {
        int idx = i == editEndChk_ovl->selected_answer ? 1 : 0;
        int* col = col_table[idx];

        mFont_SetLineStrings(game, str_p->str, str_p->len, x, y, col[0], col[1], col[2], 255, FALSE, TRUE, scale, scale,
                             mFont_MODE_POLY);

        y += scale * 16.0f;
    }
}

static void mEE_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mEE_win_data_c* data = &win_data[menu_info->data0];
    GRAPH* graph = game->graph;
    f32 x;
    f32 y;

    x = menu_info->position[0] + data->question_x;
    y = menu_info->position[1] + data->question_y;

    mEE_set_question_field(submenu, graph, x, y);
    mEE_set_question_character(submenu, graph, game, x, y);

    if (submenu->overlay->editEndChk_ovl->moving_in == TRUE) {
        x = menu_info->position[0] + data->answer_x;
        y = menu_info->position[1] + data->answer_y;

        mEE_set_answer_field(submenu, graph, data, x, y);
        mEE_set_answer_character(submenu, graph, game, data, x, y);
    }
}

static void mEE_editEndChk_ovl_draw(Submenu* submenu, GAME* game) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITENDCHK];

    (*menu_info->pre_draw_func)(submenu, game);
    mEE_set_dl(submenu, game, menu_info);
}

extern void mEE_editEndChk_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mEE_editEndChk_ovl_move;
    overlay->menu_control.menu_draw_func = &mEE_editEndChk_ovl_draw;
}

static void mEE_editEndChk_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITENDCHK];

    overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mSM_MOVE_IN_BOTTOM;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
}

static mEE_Ovl_c ee_ovl_data;

extern void mEE_editEndChk_ovl_construct(Submenu* submenu) {
    if (submenu->overlay->editEndChk_ovl == NULL) {
        submenu->overlay->editEndChk_ovl = &ee_ovl_data;
    }

    ee_ovl_data.moving_in = FALSE;
    ee_ovl_data.selected_answer = 0;
    ee_ovl_data.question_alpha_step = 0;
    ee_ovl_data.question_alpha = 0;
    ee_ovl_data.question_alpha_accum = 0.0f;

    mEE_editEndChk_ovl_init(submenu);
    mEE_editEndChk_ovl_set_proc(submenu);
}

extern void mEE_editEndChk_ovl_destruct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->editEndChk_ovl = NULL;
}
