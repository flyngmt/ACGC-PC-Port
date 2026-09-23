#include "m_notice_ovl.h"

#include "m_bgm.h"
#include "m_common_data.h"
#include "m_editor_ovl.h"
#include "m_editEndChk_ovl.h"
#include "m_event.h"
#include "m_font.h"
#include "m_quest.h"
#include "sys_matrix.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif
#ifdef TARGET_PC
#include <math.h>
#else
#include "libc/math.h"
#endif

static mNT_Ovl_c notice_ovl_data;

static f32 mNT_add_calc_dt(f32* value, f32 target, f32 rate, f32 max_step, f32 min_step) {
    f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;
    f32 dt_rate = 1.0f - powf(1.0f - rate, dt);

    return add_calc(value, target, dt_rate, max_step * dt, min_step * dt);
}

extern u8 kei_win_st1_tex_rgb_ia8[];
extern u8 kei_win_st2_tex_rgb_ia8[];
extern u8 kei_win_st3_tex_rgb_ia8[];
extern u8 kei_win_st4_tex_rgb_ia8[];
extern u8 kei_win_st5_tex_rgb_ia8[];
extern u8 kei_win_st6_tex_rgb_ia8[];

static u8* kei_win_st_tex_tbl[] = { kei_win_st5_tex_rgb_ia8, kei_win_st4_tex_rgb_ia8, kei_win_st2_tex_rgb_ia8,
                                    kei_win_st4_tex_rgb_ia8, kei_win_st5_tex_rgb_ia8, kei_win_st6_tex_rgb_ia8,
                                    kei_win_st3_tex_rgb_ia8, kei_win_st6_tex_rgb_ia8, kei_win_st1_tex_rgb_ia8 };

static int mNT_strLineCheck(u8** str_pp, u8* str_end_p, int* width, int* line) {
    u8* str_p = *str_pp;
    int res = mNT_LINE_CHECK_OK;

    if (str_p >= str_end_p) {
        res = mNT_LINE_CHECK_OVERSTRING;
    } else if (*str_p == CHAR_NEW_LINE) {
        str_pp[0] = str_p + 1;
        line[0]++;
        res = mNT_LINE_CHECK_NEWLINE;
    } else {
        width[0] += mFont_GetCodeWidth(*str_p, TRUE);

        if (*width > mNT_MAX_WIDTH) {
            res = mNT_LINE_CHECK_OVERLINE;
        } else {
            str_pp[0]++;
            line[0]++;
        }
    }

    return res;
}

static void mNT_set_init_data(mNT_Ovl_c* notice_ovl, mSM_MenuInfo_c* menu_info) {
    notice_ovl->mode = 0;
    notice_ovl->page_center = 0;
    notice_ovl->page_count = mNtc_notice_write_num();
    notice_ovl->now_page = notice_ovl->page_count - 1;
    notice_ovl->disp_page = notice_ovl->now_page;
    notice_ovl->move_time = 0;
    notice_ovl->control_position = menu_info->position[0];
}

static void mNT_finish_notice_first_job() {
    if (mEv_CheckFirstJob() == TRUE) {
        mQst_errand_c* errand_p = mQst_GetFirstJobData();

        if (errand_p != NULL && errand_p->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
            if (errand_p->base.quest_kind == mQst_ERRAND_FIRSTJOB_POST_NOTICE && errand_p->base.progress != 0) {
                errand_p->base.progress = 0;
            }
        }
    }
}

static void mNT_roll_control(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mNT_Ovl_c* notice_ovl = submenu->overlay->notice_ovl;

    if (editor_ovl != NULL) {
        int line = editor_ovl->_24;
        int dist = line - notice_ovl->page_center;
        f32 roll_pos;
        f32 abs_pos_dist;
        f32 pos_dist;

        if (dist < 0) {
            notice_ovl->page_center = line;
            menu_info->speed[1] = 1.0f;
        } else if (dist > 2) {
            notice_ovl->page_center = line - 2;
            menu_info->speed[1] = 1.0f;
        }

        roll_pos = (f32)(notice_ovl->page_center * 16);
        pos_dist = roll_pos - menu_info->position[1];
        abs_pos_dist = fabsf(pos_dist);

        if (abs_pos_dist > 0.1f) {
            if (abs_pos_dist > 9.0f) {
                menu_info->speed[1] *= 2.0f;

                if (menu_info->speed[1] > 4.0f) {
                    menu_info->speed[1] = 4.0f;
                }
            } else if (abs_pos_dist < 7.0f) {
                menu_info->speed[1] *= 0.5f;

                if (menu_info->speed[1] < 1.0f) {
                    menu_info->speed[1] = 1.0f;
                }
            }

            chase_f(&menu_info->position[1], roll_pos, menu_info->speed[1] * (f32)gamePT->graph->dt_num_60fps_frames);
        } else {
            menu_info->position[1] = roll_pos;
        }
    }
}

static void mNT_roll_control2(mSM_MenuInfo_c* menu_info) {
    f32 next_pos = menu_info->position[1] - menu_info->speed[1];

    if (menu_info->speed[1] < 1.0f) {
        menu_info->speed[1] = 1.0f;
    }

    if (next_pos > 0.0f) {
        menu_info->position[1] = next_pos;

        if (next_pos > -15.0f) {
            menu_info->speed[1] *= 2.0f;

            if (menu_info->speed[1] > 16.0f) {
                menu_info->speed[1] = 16.0f;
            }
        } else if (next_pos < 31.0f) {
            menu_info->speed[1] *= 0.5f;

            if (menu_info->speed[1] < 1.0f) {
                menu_info->speed[1] = 1.0f;
            }
        }
    } else {
        menu_info->position[1] = 0.0f;
        menu_info->speed[1] = 0.0f;
    }
}

#ifdef MOUSE_INPUT
extern Vtx kei_hyouji_v[];

static u32 mNT_mouse_trigger(Submenu* submenu, u32 trigger) {
    /* Quad offsets used by the control display lists in kei_hyouji.c. */
    static const struct {
        int first_vertex;
        u32 trigger;
    } controls[] = {
        { 44, BUTTON_CLEFT },
        { 48, BUTTON_CRIGHT },
        { 20, BUTTON_CDOWN },
        { 24, BUTTON_CUP },
        { 28, BUTTON_B },
        { 32, BUTTON_A }
    };
    f32 mouse_x, mouse_y;
    u32 pressed;
    s32 wheel;
    int i;

    if (submenu->current_menu_type != mSM_OVL_NOTICE ||
        !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.adjusted_pR >= 0.2f) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return trigger;
    }

    pressed = pc_mouse_button_pressed();
    if (pressed & PC_MOUSE_BUTTON_RIGHT) {
        return trigger | BUTTON_B;
    }

    wheel = pc_mouse_scroll_wheel();
    if (wheel != 0) {
        return trigger | (wheel > 0 ? BUTTON_CLEFT : BUTTON_CRIGHT);
    }

    if (pressed & PC_MOUSE_BUTTON_LEFT) {
        mouse_x -= 160.0f;
        mouse_y = 120.0f - mouse_y - submenu->overlay->notice_ovl->control_position;
        for (i = 0; i < ARRAY_COUNT(controls); i++) {
            if (mSM_mouse_over_quad(&kei_hyouji_v[controls[i].first_vertex], mouse_x, mouse_y, 2.0f)) {
                return trigger | controls[i].trigger;
            }
        }
    }

    return trigger;
}
#endif

static void mNT_Play_page_read(Submenu* submenu, mSM_MenuInfo_c* menu_info, mNT_Ovl_c* notice_ovl) {
    int stick_area = notice_ovl->stick_area;
    int move_page = 0;
    int move_time;
    u32 trigger = getTrigger();

#ifdef MOUSE_INPUT
    trigger = mNT_mouse_trigger(submenu, trigger);
#endif

    if (notice_ovl->now_page != 0 && (stick_area == mED_STICK_AREA_LEFT || (trigger & BUTTON_CLEFT))) {
        move_page = -1;
    } else if (notice_ovl->now_page < (notice_ovl->page_count - 1) &&
               (stick_area == mED_STICK_AREA_RIGHT || (trigger & BUTTON_CRIGHT))) {
        move_page = 1;
    } else if (notice_ovl->now_page != 0 && (stick_area == mED_STICK_AREA_BOTTOM || (trigger & BUTTON_CDOWN))) {
        move_page = -notice_ovl->now_page;
    } else if (notice_ovl->now_page < (notice_ovl->page_count - 1) &&
               (stick_area == mED_STICK_AREA_TOP || (trigger & BUTTON_CUP))) {
        move_page = (notice_ovl->page_count - notice_ovl->now_page) - 1;
    } else if (trigger & BUTTON_A) {
        notice_ovl->mode = mNT_PLAY_PAGE_TO_WRITE;
        notice_ovl->now_page = mNtc_BOARD_POST_COUNT;
        menu_info->position[0] = 320.0f;
        mem_copy((u8*)&notice_ovl->post.post_time, (u8*)Common_GetPointer(time.rtc_time), sizeof(lbRTC_time_c));
        mem_clear(notice_ovl->post.message, sizeof(notice_ovl->post.message), CHAR_SPACE);
        sAdo_SysTrgStart(0x5F);
        mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_NOTICE, 32, notice_ovl->post.message,
                              sizeof(notice_ovl->post.message));
    } else if (trigger & (BUTTON_B | BUTTON_START)) {
        (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(0x17D);
    }

    if (move_page != 0) {

        move_time = ABS(move_page);
        notice_ovl->mode = mNT_PLAY_PAGE_MOVE;

        if (move_time > 3) {
            notice_ovl->move_time = 3;
        } else {
            notice_ovl->move_time = move_time;
        }

        notice_ovl->now_page += (move_page / notice_ovl->move_time);

        if (move_page > 0) {
            menu_info->position[0] = 320.0f;
        } else {
            menu_info->position[0] = -320.0f;
        }

        sAdo_SysTrgStart(0x5F);
    }
}

static void mNT_Play_page_move(Submenu* submenu, mSM_MenuInfo_c* menu_info, mNT_Ovl_c* notice_ovl) {
    int move_flag;
    int direction = 0;
    f32 tmp;

    if (notice_ovl->move_time == 1) {
        tmp = mNT_add_calc_dt(&menu_info->position[0], 0.0f, 0.4f, 74.0f, 2.5f);

        if (fabsf(tmp) < 0.1f) {
            move_flag = TRUE;
        } else {
            move_flag = FALSE;
        }
    } else {
        if (menu_info->position[0] > 0.0f) {
            direction = 1;
            menu_info->position[0] -= 74.0f * (f32)gamePT->graph->dt_num_60fps_frames;

            if (menu_info->position[0] <= 0.0f) {
                move_flag = TRUE;
            } else {
                move_flag = FALSE;
            }
        } else {
            direction = 0;
            menu_info->position[0] += 74.0f * (f32)gamePT->graph->dt_num_60fps_frames;

            if (menu_info->position[0] >= 0.0f) {
                move_flag = TRUE;
            } else {
                move_flag = FALSE;
            }
        }
    }

    if (move_flag) {
        notice_ovl->move_time--;

        if (notice_ovl->move_time == 0) {
            menu_info->position[0] = 0.0f;
            notice_ovl->disp_page = notice_ovl->now_page;
            notice_ovl->mode = mNT_PLAY_PAGE_READ;
        } else {
            sAdo_SysTrgStart(0x5F);
            notice_ovl->disp_page = notice_ovl->now_page;

            if (direction) {
                menu_info->position[0] += 320.0f;
                notice_ovl->now_page += ((notice_ovl->page_count - notice_ovl->now_page) - 1) / notice_ovl->move_time;
            } else {
                menu_info->position[0] -= 320.0f;
                notice_ovl->now_page -= notice_ovl->now_page / notice_ovl->move_time;
            }
        }
    }
}

static void mNT_Play_page_to_write(Submenu* submenu, mSM_MenuInfo_c* menu_info, mNT_Ovl_c* notice_ovl) {
    f32 c0 = mNT_add_calc_dt(&menu_info->position[0], 0.0f, 0.4f, 74.0f, 2.5f);
    f32 c1;
    int page_stopped;
    int control_stopped;

    if (fabsf(c0) < 0.1f) {
        notice_ovl->disp_page = notice_ovl->now_page;
        menu_info->position[0] = 0.0f;
        page_stopped = TRUE;
    } else {
        page_stopped = FALSE;
    }

    c1 = mNT_add_calc_dt(&notice_ovl->control_position, -100.0f, 0.4f, 74.0f, 2.5f);
    if (fabsf(c1) < 0.1f) {
        notice_ovl->control_position = -100.0f;
        control_stopped = TRUE;
    } else {
        control_stopped = FALSE;
    }

    if (page_stopped && control_stopped) {
        menu_info->proc_status = mSM_OVL_PROC_WAIT;
    }
}

static void mNT_Play_page_to_read(Submenu* submenu, mSM_MenuInfo_c* menu_info, mNT_Ovl_c* notice_ovl) {
    f32 c0 = mNT_add_calc_dt(&menu_info->position[0], 0.0f, 0.4f, 74.0f, 2.5f);
    f32 c1;
    int page_stopped;
    int control_stopped;

    if (fabsf(c0) < 0.1f) {
        menu_info->position[0] = 0.0f;
        notice_ovl->disp_page = notice_ovl->now_page;
        page_stopped = TRUE;
    } else {
        page_stopped = FALSE;
    }

    c1 = mNT_add_calc_dt(&notice_ovl->control_position, 0.0f, 0.4f, 74.0f, 2.5f);
    if (fabsf(c1) < 0.1f) {
        notice_ovl->control_position = 0.0f;
        control_stopped = TRUE;
    } else {
        control_stopped = FALSE;
    }

    if (page_stopped && control_stopped) {
        notice_ovl->mode = mNT_PLAY_PAGE_READ;
    }
}

static void mNT_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
    submenu->overlay->notice_ovl->control_position = -menu_info->position[1];
}

typedef void (*mNT_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*, mNT_Ovl_c*);

static void mNT_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mNT_MOVE_PROC move_proc[mNT_PLAY_PAGE_NUM] = { &mNT_Play_page_read, &mNT_Play_page_move,
                                                          &mNT_Play_page_to_write, &mNT_Play_page_to_read };

    mNT_Ovl_c* notice_ovl = submenu->overlay->notice_ovl;

    (*move_proc[notice_ovl->mode])(submenu, menu_info, notice_ovl);
}

static void mNT_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];

    if (editor_menu->next_proc_status == mSM_OVL_PROC_END) {
        menu_info->proc_status = mSM_OVL_PROC_OBEY;
        mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_NOTICE, 0);
    } else {
        mNT_roll_control(submenu, menu_info);
    }
}

static void mNT_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* editEndChk_menu = &submenu->overlay->menu_info[mSM_OVL_EDITENDCHK];
    mNT_Ovl_c* notice_ovl = submenu->overlay->notice_ovl;

    mNT_roll_control2(menu_info);
    if (editEndChk_menu->proc_status == mSM_OVL_PROC_MOVE && editEndChk_menu->next_proc_status == mSM_OVL_PROC_END) {
        if (editEndChk_menu->data1 == 0) {
            mNtc_notice_write(&notice_ovl->post);
            (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
            mNT_finish_notice_first_job();
        } else if (editEndChk_menu->data1 == 1) {
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_NOTICE, 0, notice_ovl->post.message,
                                  sizeof(notice_ovl->post.message));
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
        } else {
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            notice_ovl->mode = mNT_PLAY_PAGE_TO_READ;
            notice_ovl->now_page = notice_ovl->page_count - 1;
            menu_info->position[0] = -320.0f;
        }
    }
}

static void mNT_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
    mBGMPsComp_pause(5);
}

static void mNT_stick_area_check(Submenu* submenu) {
    u8* stick_area_p = &submenu->overlay->notice_ovl->stick_area;

    if (gamePT->mcon.adjusted_pR < 0.2f) {
        stick_area_p[0] = mED_STICK_AREA_CENTER;
    } else {
        s16 angle = gamePT->mcon.move_angle;

        if (angle < -0x7000) {
            stick_area_p[0] = mED_STICK_AREA_LEFT;
        } else if (angle >= -0x7000 && angle < -0x5000) {
            stick_area_p[0] = mED_STICK_AREA_BOTTOM_LEFT;
        } else if (angle < -0x3000) {
            stick_area_p[0] = mED_STICK_AREA_BOTTOM;
        } else if (angle < -0x1000) {
            stick_area_p[0] = mED_STICK_AREA_BOTTOM_RIGHT;
        } else if (angle < 0x1000) {
            stick_area_p[0] = mED_STICK_AREA_RIGHT;
        } else if (angle < 0x3000) {
            stick_area_p[0] = mED_STICK_AREA_TOP_RIGHT;
        } else if (angle < 0x5000) {
            stick_area_p[0] = mED_STICK_AREA_TOP;
        } else if (angle < 0x7000) {
            stick_area_p[0] = mED_STICK_AREA_TOP_LEFT;
        } else {
            stick_area_p[0] = mED_STICK_AREA_LEFT;
        }
    }
}

typedef void (*mNT_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mNT_notice_ovl_move(Submenu* submenu) {
    static mNT_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = { &mNT_move_Move, &mNT_move_Play, &mNT_move_Wait,
                                                                 &mNT_move_Obey, &mNT_move_End };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NOTICE];

    mNT_stick_area_check(submenu);
    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

#if VERSION >= VER_GAFU01_00
static void mNT_notice_draw_init(mSM_MenuInfo_c* menu_info) {
    // stubbed
}
#else
static u8** mNT_notice_draw_init(mSM_MenuInfo_c* menu_info) {
    u8** tex_p = kei_win_st_tex_tbl;
    int i;

    for (i = 0; i < ARRAY_COUNT(kei_win_st_tex_tbl); i++) {
        tex_p++;
    }

    return tex_p;
}
#endif

extern Gfx kei_win_model[];

static void mNT_set_frame_dl(GRAPH* graph, f32 x, f32 y) {
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kei_win_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx kei_hyouji_model[];
extern Gfx kei_win_yaji1T_mode[];
extern Gfx kei_win_yaji1T_model[];
extern Gfx kei_win_yaji2T_model[];
extern Gfx kei_win_stT_model[];

static void mNT_set_key_dl(mNT_Ovl_c* notice_ovl, GRAPH* graph, f32 y) {
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(0.0f, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kei_hyouji_model);

    if (notice_ovl->mode == mNT_PLAY_PAGE_READ) {
        gSPDisplayList(gfx++, kei_win_yaji1T_mode);

        if (notice_ovl->now_page < (notice_ovl->page_count - 1)) {
            gSPDisplayList(gfx++, kei_win_yaji1T_model);
        }

        if (notice_ovl->now_page != 0) {
            gSPDisplayList(gfx++, kei_win_yaji2T_model);
        }
    }

    Matrix_translate(3.0f, 0.0f, 0.0f, MTX_MULT);

    if (notice_ovl->stick_area >= mED_STICK_AREA_TOP_RIGHT && notice_ovl->stick_area <= mED_STICK_AREA_BOTTOM_RIGHT) {
        Matrix_translate(-0.5f, 0.0f, 0.0f, MTX_MULT);
        Matrix_RotateY(DEG2SHORT_ANGLE(-180.0f), MTX_MULT);
    }

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, G_MWO_SEGMENT_8, kei_win_st_tex_tbl[notice_ovl->stick_area]);
    gSPDisplayList(gfx++, kei_win_stT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mNT_set_num_strings_dl(GAME* game, int page_no, f32 x, f32 y) {
    static u8 num_str[8] = "entry   ";

    mFont_UnintToString(&num_str[6], 2, page_no, 2, TRUE, FALSE, TRUE);
    mFont_SetLineStrings(game, num_str, sizeof(num_str), x + 63.0f, -y + 46.0f, 0, 0, 255, 255, FALSE, TRUE, 0.75f,
                         0.75f, mFont_MODE_POLY);
}

u8 january_str[7] = "January";
u8 february_str[8] = "February";
u8 march_str[5] = "March";
u8 april_str[5] = "April";
u8 may_str[3] = "May";
u8 june_str[4] = "June";
u8 july_str[4] = "July";
u8 august_str[6] = "August";
u8 september_str[9] = "September";
u8 october_str[7] = "October";
u8 november_str[8] = "November";
u8 december_str[8] = "December";
u8 qqq_str[3] = "???";

typedef struct {
    u8* str;
    int len;
} mNT_month_str_c;

#define mNT_MONTH_STR(str) \
    { str, sizeof(str) }

static void mNT_set_day_strings_dl(GAME* game, lbRTC_time_c* time_p, f32 x, f32 y) {
    static mNT_month_str_c month_str[lbRTC_MONTHS_MAX + 1] = {
        mNT_MONTH_STR(january_str), mNT_MONTH_STR(february_str), mNT_MONTH_STR(march_str),
        mNT_MONTH_STR(april_str),   mNT_MONTH_STR(may_str),      mNT_MONTH_STR(june_str),
        mNT_MONTH_STR(july_str),    mNT_MONTH_STR(august_str),   mNT_MONTH_STR(september_str),
        mNT_MONTH_STR(october_str), mNT_MONTH_STR(november_str), mNT_MONTH_STR(december_str),
        mNT_MONTH_STR(qqq_str)
    };
    static u8 comma_str[1] = ",";

    u8 day_str[2];
    u8 year_str[4];
    mNT_month_str_c* str_p;
    f32 month_width;

    if (time_p->month < lbRTC_JANUARY || time_p->month > lbRTC_DECEMBER) {
        time_p->month = 13;
    }

    str_p = &month_str[time_p->month - 1];
    month_width = (f32)mFont_GetStringWidth(str_p->str, str_p->len, TRUE) * 0.75f;

    mFont_SetLineStrings(game, str_p->str, str_p->len, (x + 213.0f) - month_width, -y + 46, 0, 0, 255, 255, FALSE, TRUE,
                         0.75f, 0.75f, mFont_MODE_POLY);

    mFont_UnintToString(day_str, 2, time_p->day, 2, FALSE, TRUE, TRUE);
    mFont_SetLineStrings(game, day_str, sizeof(day_str), x + 215.0f, -y + 46, 0, 0, 255, 255, FALSE, TRUE, 0.75f, 0.75f,
                         mFont_MODE_POLY);

    mFont_SetLineStrings(game, comma_str, sizeof(comma_str), x + 227.0f, -y + 46, 0, 0, 255, 255, FALSE, TRUE, 0.75f,
                         0.75f, mFont_MODE_POLY);

    mFont_UnintToString(&year_str[0], 2, time_p->year / 100, 2, FALSE, TRUE, FALSE);
    mFont_UnintToString(&year_str[2], 2, time_p->year % 100, 2, FALSE, TRUE, FALSE);
    mFont_SetLineStrings(game, year_str, sizeof(year_str), x + 233.0f, -y + 46, 0, 0, 255, 255, FALSE, TRUE, 0.75f,
                         0.75f, mFont_MODE_POLY);
}

static void mNT_set_strings_dl(mSM_MenuInfo_c* menu_info, GAME* game, u8* str_p, int body_len, f32 x, f32 y, f32* end_x,
                               f32* end_y) {
    u8* end_p;
    int i;
    int j;
    int width;
    int disp_chars;
    u8* now_str_p = str_p;
    int line_chk;

    end_x[0] = x;
    end_y[0] = y;
    end_p = str_p + body_len;

    for (i = 0; i < mNT_MAX_LINES; i++) {
        u8* original_str_p = now_str_p;

        width = 0;
        disp_chars = 0;

        do {
            line_chk = mNT_strLineCheck(&now_str_p, end_p, &width, &disp_chars);

            if (line_chk == mNT_LINE_CHECK_OVERSTRING) {
                if (i != (mNT_MAX_LINES - 1) && ((now_str_p != original_str_p && now_str_p[-1] == CHAR_NEW_LINE) ||
                                                 width + mFont_GetCodeWidth(*now_str_p, TRUE) > mNT_MAX_WIDTH)) {
                    end_x[0] = (x + 1.0f) - 160.0f;
                    end_y[0] = -(y + 16.0f) + 120.0f;
                } else {
                    end_x[0] = (x + (f32)width + 1.0f) - 160.0f;
                    end_y[0] = -y + 120.0f;
                }

                if (menu_info->proc_status != mSM_OVL_PROC_WAIT && now_str_p[-1] == CHAR_NEW_LINE) {
                    disp_chars--;
                }

                if (disp_chars != 0) {
                    mFont_SetLineStrings(game, original_str_p, disp_chars, x, y, 30, 0, 0, 255, FALSE, TRUE, 1.0f, 1.0f,
                                         mFont_MODE_POLY);
                }

                return;
            }
        } while (line_chk == mNT_LINE_CHECK_OK);

        if (line_chk == mNT_LINE_CHECK_NEWLINE && menu_info->proc_status != mSM_OVL_PROC_WAIT) {
            disp_chars--;
        }

        if (disp_chars != 0) {
            mFont_SetLineStrings(game, original_str_p, disp_chars, x, y, 30, 0, 0, 255, FALSE, TRUE, 1.0f, 1.0f,
                                 mFont_MODE_POLY);
        }

        y += 16.0f;
    }
}

static void mNT_set_page_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, GRAPH* graph, f32 x, f32 y,
                            int page_no) {
    mNT_Ovl_c* notice_ovl = submenu->overlay->notice_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mNtc_board_post_c* post_p;
    u32 now_post;
    int body_len;
    f32 end_x;
    f32 end_y;

    mNT_set_frame_dl(graph, x, y);
    (*submenu->overlay->set_char_matrix_proc)(graph);

    if (page_no == mNtc_BOARD_POST_COUNT) {
        now_post = notice_ovl->page_count + 1;

        if (now_post > mNtc_BOARD_POST_COUNT) {
            now_post = mNtc_BOARD_POST_COUNT;
        }

        post_p = &notice_ovl->post;

        if (editor_ovl != NULL) {
            body_len = editor_ovl->now_str_len;
        } else {
            body_len = 0;
        }
    } else {
        now_post = page_no + 1;
        post_p = Save_GetPointer(noticeboard[page_no]);
        body_len = mMl_strlen(post_p->message, mNT_MAX_WIDTH, CHAR_SPACE);
    }

    mNT_set_num_strings_dl(game, now_post, x, y);
    mNT_set_day_strings_dl(game, &post_p->post_time, x, y);
    x += 63.0f;
    y = -y + 63.0f;
    mNT_set_strings_dl(menu_info, game, post_p->message, body_len, x, y, &end_x, &end_y);

    if (menu_info->proc_status == mSM_OVL_PROC_WAIT && editor_ovl != NULL) {
        (*submenu->overlay->editor_ovl->cursol_draw)(submenu, game, x + (f32)editor_ovl->_26 + -7.0f,
                                                     y + editor_ovl->_24 * 16.0f);
        (*submenu->overlay->editor_ovl->end_code_draw)(submenu, game, end_x, end_y);
    }
}

static void mNT_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mNT_Ovl_c* notice_ovl = submenu->overlay->notice_ovl;
    GRAPH* graph = game->graph;
    f32 x = menu_info->position[0];
    f32 y = menu_info->position[1];

    mNT_set_page_dl(submenu, menu_info, game, graph, x, y, notice_ovl->now_page);
    if (notice_ovl->disp_page != notice_ovl->now_page) {
        if (notice_ovl->now_page > notice_ovl->disp_page) {
            x -= 320.0f;
        } else {
            x += 320.0f;
        }

        mNT_set_page_dl(submenu, menu_info, game, graph, x, y, notice_ovl->disp_page);
    }

    if (menu_info->proc_status != mSM_OVL_PROC_WAIT && menu_info->proc_status != mSM_OVL_PROC_OBEY) {
        mNT_set_key_dl(notice_ovl, graph, notice_ovl->control_position);
    }
}

static void mNT_notice_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NOTICE];

    (*menu_info->pre_draw_func)(submenu, game);
    mNT_set_dl(submenu, game, menu_info);
}

extern void mNT_notice_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mNT_notice_ovl_move;
    control->menu_draw_func = &mNT_notice_ovl_draw;
}

static void mNT_notice_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NOTICE];

    submenu->overlay->menu_control.animation_flag = FALSE;
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_IN_TOP);
    sAdo_SysTrgStart(0x17C);
    mNT_set_init_data(submenu->overlay->notice_ovl, menu_info);
    submenu->overlay->notice_ovl->stick_area = mED_STICK_AREA_CENTER;
    mBGMPsComp_pause(3);
}

extern void mNT_notice_ovl_construct(Submenu* submenu) {

    if (submenu->overlay->notice_ovl == NULL) {
        mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NOTICE];

        submenu->overlay->notice_ovl = &notice_ovl_data;
        mNT_notice_draw_init(menu_info);
    }

    mNT_notice_ovl_init(submenu);
    mNT_notice_ovl_set_proc(submenu);
}

extern void mNT_notice_ovl_destruct(Submenu* submenu) {
    submenu->overlay->notice_ovl = NULL;
}
