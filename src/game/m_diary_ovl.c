#include "m_diary_ovl.h"

#include "m_submenu_ovl.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_editor_ovl.h"
#include "m_editEndChk_ovl.h"
#include "m_cpwarning_ovl.h"
#include "m_malloc.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

enum {
    mDI_MOVE_READ,
    mDI_MOVE_READ_TO_WRITE_SCROLL,
    mDI_MOVE_EDITOR_IN,
    mDI_MOVE_WRITE,
    mDI_MOVE_WRITE_TO_ENDCHK_SCROLL,
    mDI_MOVE_ENDCHK_IN,

    mDI_MOVE_NUM
};

static mDI_Ovl_c diary_ovl_data;
static rgba_t letter_color = { 60, 60, 85, 255 };

static void mDI_end_diary(Submenu* submenu, mSM_MenuInfo_c* menu_info);

static void mDI_get_col_line_width(
    mDI_Ovl_c* diary_ovl, /* */
    s16* last_line_width, /* */
    s16* line_count, /* */
    s16* last_newline_width, /* */
    s16* newline_count, /* */
    int len  /* */
) {
    u8* str_p;
    int i;
    s16 cur_newline_width;
    s16 newlines;
    s16 cur_line_count;
    s16 width;
    s16 lines;
    s16 line_width;
    s16 newline_width;

    str_p = diary_ovl->current_entry->text;
    newline_width = 0;
    line_width = 0;
    cur_newline_width = 0;
    newlines = 0;
    cur_line_count = 0;
    lines = 0;
    width = 0;
    for (i = 0; i < len; i++) {
        width += mFont_GetCodeWidth(*str_p, TRUE);

        if (width > 192 || *str_p == CHAR_NEW_LINE) {
            lines++;
            line_width = cur_line_count;
            cur_line_count = 0;
            width = 0;
            if (*str_p == CHAR_NEW_LINE) {
                newlines++;
                newline_width = cur_newline_width;
                cur_newline_width = 0;
            }
        } else {
            cur_newline_width++;
            cur_line_count++;
        }

        str_p++;
    }

    if (lines >= 31) {
        cur_line_count = line_width + 1;
        lines = 30;
    }

    if (newlines >= 31) {
        cur_newline_width = newline_width + 1;
        newlines = 30;
    }

    if (last_newline_width != NULL) {
        *last_newline_width = cur_newline_width;
    }

    if (newline_count != NULL) {
        *newline_count = newlines;
    }

    if (last_line_width != NULL) {
        *last_line_width = cur_line_count;
    }

    if (line_count != NULL) {
        *line_count = lines;
    }
}

static void mDI_move_cursol_upper(mDI_Ovl_c* diary_ovl) {
    if (diary_ovl->_18 > 0) {
        diary_ovl->_18--;
        diary_ovl->_14 = 1;
    }
}

static void mDI_move_cursol_lower(mDI_Ovl_c* diary_ovl) {
    s16 line_count;

    mDI_get_col_line_width(diary_ovl, NULL, &line_count, NULL, NULL, diary_ovl->entry_len[0]);
    if (diary_ovl->_18 < line_count - 6) {
        diary_ovl->_18++;
        diary_ovl->_14 = 1;
    }
}

static void mDI_move_cursol_upper10(mDI_Ovl_c* diary_ovl) {
    if (diary_ovl->_18 > 0) {
        if (diary_ovl->_18 - 10 > 0) {
            diary_ovl->_18 -= 10;
        } else {
            diary_ovl->_18 = 0;
        }

        diary_ovl->_14 = 1;
    }
}

static void mDI_move_cursol_lower10(mDI_Ovl_c* diary_ovl) {
    s16 line_count;

    mDI_get_col_line_width(diary_ovl, NULL, &line_count, NULL, NULL, diary_ovl->entry_len[0]);
    if (diary_ovl->_18 < line_count - 6) {
        
        if (diary_ovl->_18 + 10 < line_count - 6) {
            diary_ovl->_18 += 10;
        } else {
            diary_ovl->_18 = line_count - 6;
        }

        diary_ovl->_14 = 1;
    }
}

static void mDI_make_trigger_data(mDI_Ovl_c* diary_ovl) {
    u32 button = (getButton() | getTrigger()) & (BUTTON_CRIGHT | BUTTON_CLEFT | BUTTON_CDOWN | BUTTON_CUP);
    u32 trigger = getTrigger() & (BUTTON_CRIGHT | BUTTON_CLEFT | BUTTON_CDOWN | BUTTON_CUP);

    if (gamePT->mcon.move_pR > 0.5f) {
        static u32 add_trigger[] = { BUTTON_DRIGHT, BUTTON_DUP, BUTTON_DLEFT, BUTTON_DDOWN };
        u32 last_button = diary_ovl->last_button;
        u32 trig = add_trigger[((gamePT->mcon.move_angle + DEG2SHORT_ANGLE2(45.0f)) >> 14) & 3];

        button |= trig;
        trigger |= trig & (trig ^ last_button);
        diary_ovl->last_button = trig;
    } else {
        diary_ovl->last_button = 0;
    }

    diary_ovl->trigger = trigger;
    diary_ovl->button = button;
}

static s16 mDI_Set_command_read(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;

    if ((diary_ovl->button & (BUTTON_DUP | BUTTON_DDOWN)) != 0) {
        if ((diary_ovl->button & (BUTTON_DUP | BUTTON_DDOWN)) == (diary_ovl->_0C & (BUTTON_DUP | BUTTON_DDOWN))) {
            diary_ovl->_0C = diary_ovl->button;

            if (diary_ovl->_10 == 1 && diary_ovl->_11 != 0) {
                diary_ovl->_11--;
            }

            if (diary_ovl->_12 != 0) {
                diary_ovl->_12--;
            } else if (diary_ovl->_32 == 0) {
                if (diary_ovl->_11 == 0) {
                    diary_ovl->_30 = 3;

                    if ((diary_ovl->button & BUTTON_DUP) != 0) {
                        return 2;
                    }

                    if ((diary_ovl->button & BUTTON_DDOWN) != 0) {
                        return 3;
                    }
                } else {
                    diary_ovl->_10 = 1;
                    diary_ovl->_30 = 2;

                    if ((diary_ovl->button & BUTTON_DUP) != 0) {
                        return 2;
                    }

                    if ((diary_ovl->button & BUTTON_DDOWN) != 0) {
                        return 3;
                    }
                }
            }
        } else if ((diary_ovl->trigger & (BUTTON_DUP | BUTTON_DDOWN)) != 0 && diary_ovl->_32 == 0) {
            diary_ovl->_0C = diary_ovl->trigger;
            diary_ovl->_12 = 30;
            diary_ovl->_11 = 26;
            diary_ovl->_10 = 0;
            diary_ovl->_30 = 1;

            if ((diary_ovl->button & BUTTON_DUP) != 0) {
                return 2;
            }

            if ((diary_ovl->button & BUTTON_DDOWN) != 0) {
                return 3;
            }

            diary_ovl->_32 = 0;
        }
    } else {
        if ((diary_ovl->trigger & BUTTON_CUP) != 0 && diary_ovl->_32 == 0) {
            diary_ovl->_0C = diary_ovl->trigger;
            diary_ovl->_12 = 0;
            return 8;
        }

        if ((diary_ovl->trigger & BUTTON_CDOWN) != 0 && diary_ovl->_32 == 0) {
            diary_ovl->_0C = diary_ovl->trigger;
            diary_ovl->_12 = 0;
            return 9;
        }

        diary_ovl->_0C = diary_ovl->trigger;
        diary_ovl->_30 = 1;
        diary_ovl->_0C = 0; // ???
        diary_ovl->_12 = 0;
    }

    return 0;
}

static void mDI_control_diary_read(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    s16 command = mDI_Set_command_read(submenu, menu_info);

    if (command != 0 && diary_ovl->_32 == 0) {
        diary_ovl->_14 = 0;

        switch (command) {
            case 2:
                mDI_move_cursol_upper(diary_ovl);
                diary_ovl->_32 = 3;
                break;
            case 3:
                mDI_move_cursol_lower(diary_ovl);
                diary_ovl->_32 = 4;
                break;
            case 8:
                mDI_move_cursol_upper10(diary_ovl);
                diary_ovl->_32 = 5;
                break;
            case 9:
                mDI_move_cursol_lower10(diary_ovl);
                diary_ovl->_32 = 6;
                break;
        }

        if (diary_ovl->_14 != 0) {
            sAdo_SysTrgStart(NA_SE_35);
        }
    }
}

static void mDI_roll_control_read(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    int _18;
    f32 aim;
    f32 dPosY;

    mDI_control_diary_read(submenu, menu_info);
    _18 = 2 + diary_ovl->_18;

    if (_18 - diary_ovl->_05 < 0) {
        menu_info->speed[1] = 1.0f;
        diary_ovl->_05 = _18;
    } else if (_18 - diary_ovl->_05 > 0) {
        menu_info->speed[1] = 1.0f;
        diary_ovl->_05 = _18;
    }

    aim = (diary_ovl->_05 - 2) * 16;
    dPosY = fabsf(aim - menu_info->position[1]);
    if (dPosY > 0.1f) {
        if (diary_ovl->_32 == 5 || diary_ovl->_32 == 6) {
            menu_info->speed[1] = 16.0f/3.0f;
        } else if (diary_ovl->_30 == 2) {
            menu_info->speed[1] = 16.0f/7.0f;
        } else if (diary_ovl->_30 == 3) {
            menu_info->speed[1] = 16.0f/3.0f;
        } else {
            if (diary_ovl->_32 != 0) {
                if (dPosY > 9.0f) {
                    menu_info->speed[1] *= 2.0f;
                    if (menu_info->speed[1] > 8.0f) {
                        menu_info->speed[1] = 8.0f;
                    }
                } else if (dPosY < 7.0f) {
                    menu_info->speed[1] *= 0.5f;
                    if (menu_info->speed[1] < 1.0f) {
                        menu_info->speed[1] = 1.0f;
                    }
                }
            }
        }

        chase_f(&menu_info->position[1], aim, menu_info->speed[1] * (f32)gamePT->graph->dt_num_60fps_frames);
        if (fabsf(aim - menu_info->position[1]) <= 0.01f) {
            menu_info->position[1] = aim;
            diary_ovl->_32 = 0;
            diary_ovl->_30 = 0;
        }
    } else {
        menu_info->position[1] = aim;
        menu_info->speed[1] = 0.0f;
        diary_ovl->_32 = 0;
        diary_ovl->_30 = 0;
    }
}

static void mDI_roll_control_read_to_write(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    f32 aim;
    f32 dPosY;

    diary_ovl->_05 = 2 + diary_ovl->_18;
    aim = (diary_ovl->_05 - 2) * 16;
    dPosY = fabsf(aim - menu_info->position[1]);
    if (dPosY > 1.0f && menu_info->speed[1] == 0.0f) {
        menu_info->speed[1] = 1.0f;
    }

    if (dPosY > 0.1f) {
        if (dPosY > 9.0f) {
            menu_info->speed[1] *= 2.0f;
            if (menu_info->speed[1] > 8.0f) {
                menu_info->speed[1] = 8.0f;
            }
        } else if (dPosY < 7.0f) {
            menu_info->speed[1] *= 0.5f;
            if (menu_info->speed[1] < 1.0f) {
                menu_info->speed[1] = 1.0f;
            }
        }

        chase_f(&menu_info->position[1], aim, menu_info->speed[1] * (f32)gamePT->graph->dt_num_60fps_frames);
    } else {
        menu_info->speed[1] = 0.0f;
        menu_info->position[1] = aim;
    }
}

static void mDI_roll_control(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;

    if (editor_ovl != NULL) {
        int col = 2 + editor_ovl->_24;
        f32 aim;
        f32 dPosY;

        if (col - diary_ovl->_05 < 0) {
            diary_ovl->_05 = col;
            menu_info->speed[1] = 1.0f;
        } else if (col - diary_ovl->_05 > 0) {
            diary_ovl->_05 = col;
            menu_info->speed[1] = 1.0f;
        }

        aim = (diary_ovl->_05 - 2) * 16;
        dPosY = fabsf(aim - menu_info->position[1]);
        if (dPosY > 0.1f) {
            if (editor_ovl->_34 == 3) {
                diary_ovl->_1E = 3;
                diary_ovl->_20 = 2;
            } else if (editor_ovl->_34 == 2) {
                diary_ovl->_1E = 2;
                diary_ovl->_20 = 6;
            }

            if (diary_ovl->_1E == 3) {
                menu_info->speed[1] = 16.0f/3.0f;
            } else if (diary_ovl->_1E == 2) {
                menu_info->speed[1] = 16.0f/7.0f;
            } else {
                if (dPosY > 9.0f) {
                    menu_info->speed[1] *= 2.0f;
                    if (menu_info->speed[1] > 2.0f) {
                        menu_info->speed[1] = 2.0f;
                    }
                } else if (dPosY < 7.0f) {
                    menu_info->speed[1] *= 0.5f;
                    if (menu_info->speed[1] < 1.0f) {
                        menu_info->speed[1] = 1.0f;
                    }
                }
            }

            chase_f(&menu_info->position[1], aim, menu_info->speed[1] * (f32)gamePT->graph->dt_num_60fps_frames);

            if (editor_ovl->_34 != 3 && editor_ovl->_34 != 2 && diary_ovl->_20 > 0) {
                diary_ovl->_20--;

                if (diary_ovl->_20 <= 0) {
                    diary_ovl->_1E = 0;
                }
            }
        } else {
            menu_info->position[1] = aim;
            menu_info->speed[1] = 0.0f;
        }
    }
}

static void mDI_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mDI_Play_editor_in(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];

    if (editor_menu->proc_status == editor_menu->next_proc_status) {
        diary_ovl->move_proc = mDI_MOVE_WRITE;
    }
}

#ifdef MOUSE_INPUT
extern Vtx dia_hyouji_v[];

static u32 mDI_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu_info, u32 trigger) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    f32 mouse_x, mouse_y;
    u32 pressed;
    s32 wheel;

    if (submenu->current_menu_type != mSM_OVL_DIARY ||
        !pc_mouse_update_owner(FALSE, pc_mouse_pad_active()) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return trigger;
    }

    pressed = pc_mouse_button_pressed();
    if (pressed & PC_MOUSE_BUTTON_RIGHT) {
        return trigger | BUTTON_B;
    }
    if (pressed & PC_MOUSE_BUTTON_LEFT) {
        if (menu_info->data0 == 1) {
            return trigger | BUTTON_B;
        }

        mouse_x -= 160.0f;
        mouse_y = 120.0f - mouse_y - menu_info->position[0];
        if (mSM_mouse_over_quad(&dia_hyouji_v[0], mouse_x, mouse_y, 2.0f) ||
            mSM_mouse_over_quad(&dia_hyouji_v[8], mouse_x, mouse_y, 2.0f)) {
            return trigger | BUTTON_A;
        }
        if (mSM_mouse_over_quad(&dia_hyouji_v[4], mouse_x, mouse_y, 2.0f) ||
            mSM_mouse_over_quad(&dia_hyouji_v[12], mouse_x, mouse_y, 2.0f)) {
            return trigger | BUTTON_B;
        }
    }

    wheel = pc_mouse_scroll_wheel();
    if (wheel != 0) {
        u32 direction = wheel > 0 ? BUTTON_DUP : BUTTON_DDOWN;
        diary_ovl->trigger |= direction;
        diary_ovl->button |= direction;
    }
    return trigger;
}
#endif

static void mDI_Play_read(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    u32 trigger = getTrigger();

    mDI_make_trigger_data(diary_ovl);
#ifdef MOUSE_INPUT
    trigger = mDI_mouse_trigger(submenu, menu_info, trigger);
#endif
    mDI_roll_control_read(submenu, menu_info);

    if ((trigger & (BUTTON_A | BUTTON_B | BUTTON_START)) != 0) {
        if ((trigger & BUTTON_B) != 0 || menu_info->data0 == 1) {
            if (menu_info->data0 == 1) {
                sAdo_SysTrgStart(NA_SE_5F);
            } else {
                sAdo_SysTrgStart(MONO(NA_SE_3));
            }

            mDI_end_diary(submenu, menu_info);
        } else {
            diary_ovl->_18 = diary_ovl->_24;
            diary_ovl->move_proc = mDI_MOVE_READ_TO_WRITE_SCROLL;
            diary_ovl->_28 = 0.0f;
            diary_ovl->_2C = 0;
            sAdo_SysTrgStart(NA_SE_5F);
        }
    }
}

static void mDI_Play_read_to_write_scroll(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    mDI_roll_control_read_to_write(submenu, menu_info);

    if (diary_ovl->_42 == 0) {
        if (diary_ovl->_28 > -100.0f) {
            diary_ovl->_28 = diary_ovl->_2C * -0.6f * diary_ovl->_2C;
            diary_ovl->_2C++;
        } else {
            diary_ovl->_28 = -100.0f;
        }

        if (menu_info->speed[1] == 0.0f && diary_ovl->_28 == -100.0f) {
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_DIARY, 32, diary_ovl->current_entry->text, 192);
            diary_ovl->move_proc = mDI_MOVE_EDITOR_IN;
        }
    } else {
        mSM_MenuInfo_c* editEndChk_menu = &submenu->overlay->menu_info[mSM_OVL_EDITENDCHK];

        if (menu_info->speed[1] == 0.0f && editEndChk_menu->proc_status != mSM_OVL_PROC_END) {
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_DIARY, 0, diary_ovl->current_entry->text, 192);
            diary_ovl->move_proc = mDI_MOVE_EDITOR_IN;
        }
    }
}

static void mDI_Play_write(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];

    if (editor_menu->next_proc_status == mSM_OVL_PROC_END) {
        s16 lines;
        
        mDI_get_col_line_width(diary_ovl, NULL, &lines, NULL, NULL, diary_ovl->entry_len[0]);
        diary_ovl->cursor_idx = editor_ovl->cursor_idx;
        diary_ovl->_48 = editor_ovl->_22;
        diary_ovl->_46 = editor_ovl->_24;

        if (lines < diary_ovl->_24) {
            diary_ovl->_18 = lines;
        } else {
            diary_ovl->_18 = diary_ovl->_24;
        }

        diary_ovl->move_proc = mDI_MOVE_WRITE_TO_ENDCHK_SCROLL;
        diary_ovl->_40 = 0;
    } else {
        mDI_roll_control(submenu, menu_info);
    }
}

static void mDI_roll_control_write_to_endchk(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    int _18;
    f32 aim;
    f32 dPosY;

    _18 = 2 + diary_ovl->_18;
    if (_18 < 8) {
        _18 = 8;
    }

    diary_ovl->_05 = _18;
    aim = (diary_ovl->_05 - 8) * 16;
    dPosY = fabsf(aim - menu_info->position[1]);
    if (dPosY > 0.1f && menu_info->speed[1] == 0.0f) {
        menu_info->speed[1] = 1.0f;
    }

    if (dPosY > 0.1f) {
        if (dPosY > 9.0f) {
            menu_info->speed[1] *= 2.0f;
            if (menu_info->speed[1] > 8.0f) {
                menu_info->speed[1] = 8.0f;
            }
        } else if (dPosY < 7.0f) {
            menu_info->speed[1] *= 0.5f;
            if (menu_info->speed[1] < 1.0f) {
                menu_info->speed[1] = 1.0f;
            }
        }

        chase_f(&menu_info->position[1], aim, menu_info->speed[1] * (f32)gamePT->graph->dt_num_60fps_frames);
    } else {
        menu_info->speed[1] = 0.0f;
        menu_info->position[1] = aim;
    }
}

static void mDI_Play_write_to_endchk_scroll(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];

    mDI_roll_control_write_to_endchk(submenu, menu_info);
    if (diary_ovl->_40 != 0 && menu_info->speed[1] == 0.0f) {
        menu_info->proc_status = mSM_OVL_PROC_OBEY;
        mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_BOARD, 0);
    }

    if (diary_ovl->_40 == 0 && editor_menu->proc_status == mSM_OVL_PROC_END) {
        diary_ovl->_40 = 1;
    }
}

static void mDI_Play_endchk_in(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl) {
    // nothing
}

static void mDI_end_diary(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_LEFT);
}

typedef void (*mDI_MOVE_PROC)(Submenu* submenu, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl);

static void mDI_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    // clang-format off
    static mDI_MOVE_PROC move_proc[mDI_MOVE_NUM] = {
        mDI_Play_read,
        mDI_Play_read_to_write_scroll,
        mDI_Play_editor_in,
        mDI_Play_write,
        mDI_Play_write_to_endchk_scroll,
        mDI_Play_endchk_in,
    };
    // clang-format on
    
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;

    (*move_proc[diary_ovl->move_proc])(submenu, menu_info, diary_ovl);
}

static void mDI_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    mSM_MenuInfo_c* endEditChk_menu = &submenu->overlay->menu_info[mSM_OVL_EDITENDCHK];

    if (endEditChk_menu->proc_status == mSM_OVL_PROC_MOVE && endEditChk_menu->next_proc_status == mSM_OVL_PROC_END) {
        mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

        if (endEditChk_menu->data1 == 0) {
            mCD_save_data_main_to_aram(diary_ovl->data, mCD_KEEP_DIARY_SIZE, mCD_ARAM_DATA_DIARY);
            mSM_open_submenu(submenu, mSM_OVL_CPWARNING, 0, 0);
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
        } else if (endEditChk_menu->data1 == 1) {
            diary_ovl->_42 = 1;
            diary_ovl->_18 = diary_ovl->_46;
            diary_ovl->field = mDI_FIELD_BODY;
            diary_ovl->move_proc = mDI_MOVE_READ_TO_WRITE_SCROLL;
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
        }

        if (editor_ovl != NULL) {
            editor_ovl->cursor_idx = 0;
            editor_ovl->_22 = 0;
            editor_ovl->_24 = 0;
        }
    }
}

static void mDI_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* cpwarning_menu = &submenu->overlay->menu_info[mSM_OVL_CPWARNING];

    if (cpwarning_menu->proc_status == mSM_OVL_PROC_MOVE && cpwarning_menu->next_proc_status == mSM_OVL_PROC_END) {
        sAdo_SysTrgStart(NA_SE_5F);
        mDI_end_diary(submenu, menu_info);
    }
}

static void mDI_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mDI_diary_ovl_move(Submenu* submenu) {
    // clang-format off
    static mSM_MOVE_PROC ovl_move_proc[] = {
        mDI_move_Move,
        mDI_move_Play,
        mDI_move_Wait,
        mDI_move_Obey,
        mDI_move_End,
    };
    // clang-format on

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_DIARY];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

#if VERSION == VER_GAFE01_00
extern Gfx dia_init_mode[];
// extern Gfx kei_win_b2_model[];
extern Gfx kei_win_b2_model_1_data_4075A0[];
// extern Gfx kei_win_amojiT_model[];
extern Gfx kei_win_amojiT_model_1_data_407620[];
extern Gfx dia_win_bb_model[];
extern Gfx dia_win_mojiT_model[];

static void mDI_set_button_dl(GRAPH* graph, f32 pos_x, f32 pos_y) {
    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_init_mode);
    gSPDisplayList(POLY_OPA_DISP++, kei_win_b2_model_1_data_4075A0);
    gSPDisplayList(POLY_OPA_DISP++, kei_win_amojiT_model_1_data_407620);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_bb_model);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_mojiT_model);

    CLOSE_POLY_OPA_DISP(graph);
}
#else
extern Gfx dia_init_mode[];
// extern Gfx kei_win_b2_model[];
extern Gfx kei_win_b2_model_1_data_407600[];
// extern Gfx kei_win_amojiT_model[];
extern Gfx kei_win_amojiT_model_1_data_407680[];
extern Gfx dia_win_bb_model[];
extern Gfx dia_win_mojiT_model[];

static void mDI_set_button_dl(GRAPH* graph, f32 pos_x, f32 pos_y) {
    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_init_mode);
    gSPDisplayList(POLY_OPA_DISP++, kei_win_b2_model_1_data_407600);
    gSPDisplayList(POLY_OPA_DISP++, kei_win_amojiT_model_1_data_407680);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_bb_model);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_mojiT_model);

    CLOSE_POLY_OPA_DISP(graph);
}
#endif

extern Gfx dia_init_mode_letter[];
extern Gfx dia_win_wT_model[];
extern Gfx dia_win_fusenT_model[];
extern Gfx dia_win_tukiT_model[];
extern Gfx dia_win_moji_model[];
extern Gfx dia_win2_wT_model[];
extern Gfx dia_win2_fusenT_model[];
extern Gfx dia_win3_wT_model[];
extern Gfx dia_win3_fusenT_model[];

extern u8 dia_win_april_tex_rgb_ia8[];
extern u8 dia_win_august_tex_rgb_ia8[];
extern u8 dia_win_december_tex_rgb_ia8[];
extern u8 dia_win_february_tex_rgb_ia8[];
extern u8 dia_win_january_tex_rgb_ia8[];
extern u8 dia_win_july_tex_rgb_ia8[];
extern u8 dia_win_june_tex_rgb_ia8[];
extern u8 dia_win_march_tex_rgb_ia8[];
extern u8 dia_win_may_tex_rgb_ia8[];
extern u8 dia_win_november_tex_rgb_ia8[];
extern u8 dia_win_october_tex_rgb_ia8[];
extern u8 dia_win_september_tex_rgb_ia8[];

static void mDI_set_frame_dl(GRAPH* graph, mSM_MenuInfo_c* menu_info, mDI_Ovl_c* diary_ovl, f32 pos_x, f32 pos_y, int month) {
    // clang-format off
    static u8* month_tex_table[lbRTC_MONTHS_MAX] = {
        dia_win_january_tex_rgb_ia8,
        dia_win_february_tex_rgb_ia8,
        dia_win_march_tex_rgb_ia8,
        dia_win_april_tex_rgb_ia8,
        dia_win_may_tex_rgb_ia8,
        dia_win_june_tex_rgb_ia8,
        dia_win_july_tex_rgb_ia8,
        dia_win_august_tex_rgb_ia8,
        dia_win_september_tex_rgb_ia8,
        dia_win_october_tex_rgb_ia8,
        dia_win_november_tex_rgb_ia8,
        dia_win_december_tex_rgb_ia8,
    };
    // clang-format on

    // clang-format off
    static f32 month_tex_adjust[lbRTC_MONTHS_MAX] = {
        -26.0f,
        -16.0f,
        -40.0f,
        -52.0f,
        -57.0f,
        -52.0f,
        -57.0f,
        -32.0f,
        0.0f,
        -23.0f,
        -6.0f,
        -6.0f,
    };
    // clang-format on

    Matrix_push();

    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_init_mode_letter);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_wT_model);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_fusenT_model);
    gDPLoadTextureBlock_8b_Dolphin(POLY_OPA_DISP++, month_tex_table[month], G_IM_FMT_IA, 16, 64, 0, GX_MIRROR, GX_MIRROR, 0, 0);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_tukiT_model);

    Matrix_push();
    Matrix_translate(month_tex_adjust[month], 0.0f, 0.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_win_moji_model);

    Matrix_pull();

    Matrix_translate(0.0f, -194.0f, 0.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_win2_wT_model);
    gSPDisplayList(POLY_OPA_DISP++, dia_win2_fusenT_model);
    
    Matrix_translate(0.0f, -164.0f, 0.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_win3_wT_model);
    gSPDisplayList(POLY_OPA_DISP++, dia_win3_fusenT_model);

    CLOSE_POLY_OPA_DISP(graph);

    Matrix_pull();
}

static int mDI_strLineCheck(u8** str_pp, u8* str_end_p, int* width, int* line_len) {
    u8* cur_str_p = *str_pp;
    int ret = 0;

    if (cur_str_p >= str_end_p) {
        ret = 3;
    } else if (*cur_str_p == CHAR_NEW_LINE) {
        *str_pp = cur_str_p + 1;
        (*line_len)++;
        ret = 1;
    } else {
        (*width) += mFont_GetCodeWidth(*cur_str_p, TRUE);
        if (*width > 192) {
            ret = 2;
        } else {
            (*str_pp)++;
            (*line_len)++;
        }
    }

    return ret;
}

static void mDI_set_writing_body(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, f32 pos_x, f32 pos_y, f32* o_pos_x, f32* o_pos_y, rgba_t* color) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    u8* str_p = diary_ovl->current_entry->text;
    u8* str_end_p = str_p + diary_ovl->entry_len[0];
    int i;

    for (i = 0; i < 31; i++) {
        u8* start_str_p = str_p;
        int width = 0;
        int line_len = 0;
        int cmd;

        while (TRUE) {
            cmd = mDI_strLineCheck(&str_p, str_end_p, &width, &line_len);
            
            if (cmd == 3) {
                if (i != 30 && ((str_p != start_str_p && str_p[-1] == CHAR_NEW_LINE) || width + mFont_GetCodeWidth(*str_p, TRUE) > 192)) {
                    *o_pos_x = (pos_x + 1.0f) - 160.0f;
                    *o_pos_y = 120.0f - (pos_y + 16.0f);
                } else {
                    *o_pos_x = (pos_x + width + 1.0f) - 160.0f;
                    *o_pos_y = 120.0f - pos_y;
                }

                if ((menu_info->proc_status != mSM_OVL_PROC_PLAY || diary_ovl->move_proc != 3) && str_p[-1] == CHAR_NEW_LINE) {
                    line_len--;
                }

                if (line_len != 0) {
                    // clang-format off
                    mFont_SetLineStrings(
                        game,
                        start_str_p, line_len,
                        pos_x, pos_y,
                        color->r, color->g, color->b, 255,
                        FALSE, TRUE,
                        1.0f, 1.0f,
                        mFont_MODE_POLY
                    );
                    // clang-format on
                }

                return;
            } else if (cmd != 0) {
                break;
            }
        }

        if (cmd == 1 && (menu_info->proc_status != mSM_OVL_PROC_PLAY || diary_ovl->move_proc != 3)) {
            line_len--;
        }

        if (line_len != 0 && (pos_y - 36.0f) >= -48.0f && (pos_y - 36.0f) < 192.0f) {
            // clang-format off
            mFont_SetLineStrings(
                game,
                start_str_p, line_len,
                pos_x, pos_y,
                color->r, color->g, color->b, 255,
                FALSE, TRUE,
                1.0f, 1.0f,
                mFont_MODE_POLY
            );
            // clang-format on
        }

        pos_y += 16.0f;
    }
}

static void mDI_set_character(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, f32 pos_x, f32 pos_y) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    f32 char_pos_x;
    f32 char_pos_y;
    f32 endcode_pos_x;
    f32 endcode_pos_y;
    
    char_pos_x = pos_x + 64.0f;
    char_pos_y = 36.0f - pos_y;

    char_pos_y += 28.0f;
    endcode_pos_x = char_pos_x - 160.0f;
    endcode_pos_y = 120.0f - char_pos_y;
    mDI_set_writing_body(submenu, menu_info, game, char_pos_x, char_pos_y, &endcode_pos_x, &endcode_pos_y, &letter_color);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY && diary_ovl->move_proc == 3 && editor_ovl != NULL) {
        submenu->overlay->editor_ovl->cursol_draw(submenu, game, char_pos_x + editor_ovl->_26 + -7.0f, char_pos_y + editor_ovl->_24 * 16.0f);
        submenu->overlay->editor_ovl->end_code_draw(submenu, game, endcode_pos_x, endcode_pos_y);
    }
}

static void mDI_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    GRAPH* graph = game->graph;
    f32 pos_x = menu_info->position[0];
    f32 pos_y = menu_info->position[1];

    mDI_set_frame_dl(graph, menu_info, diary_ovl, pos_x, pos_y, (int)menu_info->data3);
    submenu->overlay->set_char_matrix_proc(graph);
    mDI_set_character(submenu, game, menu_info, pos_x, pos_y);

    if (menu_info->data0 == 0 && (menu_info->proc_status == mSM_OVL_PROC_MOVE || menu_info->proc_status == mSM_OVL_PROC_PLAY)) {
        // @BUG - shouldn't these use pos_y instead of pos_x ??
        if (diary_ovl->move_proc == 1) {
            mDI_set_button_dl(graph, 0.0f, pos_x + diary_ovl->_28);
        } else if (diary_ovl->move_proc == 0) {
            mDI_set_button_dl(graph, 0.0f, pos_x);
        }
    }
}

static void mDI_diary_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_DIARY];

    menu_info->pre_draw_func(submenu, game);
    mDI_set_dl(submenu, game, menu_info);
}

extern void mDI_diary_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;

    ctrl->menu_move_func = mDI_diary_ovl_move;
    ctrl->menu_draw_func = mDI_diary_ovl_draw;
}

static void mDI_diary_ovl_init(Submenu* submenu) {
    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_DIARY];

    ctrl->animation_flag = FALSE;
    menu_info->move_drt = mSM_MOVE_IN_LEFT;
    submenu->overlay->move_chg_base_proc(menu_info, menu_info->move_drt);
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    diary_ovl->field = mDI_FIELD_BODY;
    diary_ovl->_05 = 2;
    mCD_save_data_aram_to_main(diary_ovl->data, mCD_KEEP_DIARY_SIZE, mCD_ARAM_DATA_DIARY);
    diary_ovl->current_entry = diary_ovl->data->entries[menu_info->data1] + menu_info->data3;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    diary_ovl->entry_len[mDI_FIELD_BODY] = mDi_strlen(diary_ovl->current_entry->text, mDI_ENTRY_SIZE, CHAR_SPACE);
    diary_ovl->_18 = 0;
    mDI_get_col_line_width(diary_ovl, &diary_ovl->_22, &diary_ovl->_24, NULL, NULL, diary_ovl->entry_len[mDI_FIELD_BODY]);
    diary_ovl->move_proc = mDI_MOVE_READ;
    sAdo_SysTrgStart(NA_SE_5F);
}

extern void mDI_diary_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    if (ovl->diary_ovl == NULL) {
        mem_clear((u8*)&diary_ovl_data, sizeof(diary_ovl_data), 0);
        ovl->diary_ovl = &diary_ovl_data;
        ovl->diary_ovl->data = (mCD_keep_diary_c*)zelda_malloc_align(mCD_KEEP_DIARY_SIZE, 32);
        mem_clear((u8*)ovl->diary_ovl->data, mCD_KEEP_DIARY_SIZE, 0);
    } else {
        mCD_keep_diary_c* tmp = ovl->diary_ovl->data;

        mem_clear((u8*)&diary_ovl_data, sizeof(diary_ovl_data), 0);
        ovl->diary_ovl->data = tmp;
    }

    mDI_diary_ovl_init(submenu);
    mDI_diary_ovl_set_proc(submenu);
}

extern void mDI_diary_ovl_destruct(Submenu* submenu) {
    if (diary_ovl_data.data != NULL) {
        zelda_free(diary_ovl_data.data);
        diary_ovl_data.data = NULL;
    }

    submenu->overlay->diary_ovl = NULL;
}
