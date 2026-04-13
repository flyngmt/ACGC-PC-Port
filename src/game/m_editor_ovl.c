#include "m_editor_ovl.h"

#include "audio.h"
#include "m_warning_ovl.h"
#include "m_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_diary.h"
#include "m_passwordChk_ovl.h"
#include "m_passwordMake_ovl.h"
#include "m_board_ovl.h"
#include "m_diary_ovl.h"
#include "m_address_ovl.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_lib.h"

static u8 mED_ornament_table[] = {
    // clang-format off
    0x21, 0x3f, 0x03, 0x04, 0x05, 0x06, 0x07, 0x41,
    0x43, 0x0a, 0x0b, 0x0c, 0x45, 0x0e, 0x0f, 0x10,
    0x49, 0x44, 0x4e, 0x14, 0x15, 0x16, 0x17, 0x4f,
    0x8d, 0x1a, 0x1b, 0x1c, 0x55, 0x1d, 0x95, 0x23,
    0x20, 0x00, 0xa4, 0x24, 0x5b, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x18, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x01,
    0x40, 0x02, 0x42, 0x08, 0x11, 0x09, 0x46, 0x47,
    0x48, 0x0d, 0x4a, 0x4b, 0x4c, 0x4d, 0x12, 0x13,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x19, 0x56, 0x57,
    0x58, 0x96, 0x5a, 0x5d, 0x5c, 0x5e, 0x61, 0x5f,
    0x63, 0x1f, 0x62, 0x60, 0x64, 0x7b, 0x66, 0x67,
    0x68, 0x81, 0x6a, 0x6b, 0x6c, 0x6d, 0x87, 0x88,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x8e, 0x76, 0x77,
    0x78, 0x93, 0x7a, 0x7c, 0x7d, 0x7e, 0x65, 0x7f,
    0x80, 0x82, 0x83, 0x84, 0x69, 0x85, 0x86, 0x6e,
    0x89, 0x8a, 0x8b, 0x8c, 0x6f, 0x30, 0x8f, 0x91,
    0x90, 0x92, 0x75, 0x94, 0x79, 0x1e, 0x59, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa3, 0xa2, 0x22, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xff, 0xd2, 0xd4, 0xd5, 0xd6, 0xd7,
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xd3
    // clang-format on
};

static void mED_open_warning_window(Submenu* submenu, mSM_MenuInfo_c* menu_info, int warning) {
    mWR_SHOW_WARNING(submenu, warning);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    sAdo_SysTrgStart(0x1003);
}

static int mED_get_code(mED_Ovl_c* editor_ovl, int col, int row) {
    static u8 letterS_table[] = {
        // clang-format off
        0x21, 0x3f, 0x22, 0x2d, 0x2a, 0x90, 0x27, 0xd0,
        0x3a, 0xd4, 0x71, 0x77, 0x65, 0x72, 0x74, 0x79,
        0x75, 0x69, 0x6f, 0x70, 0x61, 0x73, 0x64, 0x66,
        0x67, 0x68, 0x6a, 0x6b, 0x6c, 0xcd, 0x7a, 0x78,
        0x63, 0x76, 0x62, 0x6e, 0x6d, 0x2c, 0x2e, 0x20,
        // clang-format on
    };

    static u8 letterS_table2[] = {
        // clang-format off
        0x21, 0x3f, 0x22, 0x2d, 0x2a, 0x90, 0x27, 0xd0,
        0x3a, 0x85, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
        0x6f, 0x70, 0x71, 0x72, 0x73, 0xcd, 0x74, 0x75,
        0x76, 0x77, 0x78, 0x79, 0x7a, 0x2c, 0x2e, 0x20,
        // clang-format on
    };

    static u8 letterL_table[] = {
        // clang-format off
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x30, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59,
        0x55, 0x49, 0x4f, 0x50, 0x41, 0x53, 0x44, 0x46,
        0x47, 0x48, 0x4a, 0x4b, 0x4c, 0xcd, 0x5a, 0x58,
        0x43, 0x56, 0x42, 0x4e, 0x4d, 0x2c, 0x2e, 0x20,
        // clang-format on
    };

    static u8 letterL_table2[] = {
        // clang-format off
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x30, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
        0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e,
        0x4f, 0x50, 0x51, 0x52, 0x53, 0xcd, 0x54, 0x55,
        0x56, 0x57, 0x58, 0x59, 0x5a, 0x2c, 0x2e, 0x20,
        // clang-format on
    };

    static u8 sign_table[] = {
        // clang-format off
        0xd1, 0x3f, 0x22, 0x2d, 0x2a, 0x90, 0x85, 0xd0,
        0x3a, 0xa2, 0x25, 0x26, 0x40, 0x5f, 0xa0, 0xae,
        0x97, 0xc0, 0xc1, 0x3d, 0x28, 0x29, 0x3c, 0x3e,
        0xa5, 0xa6, 0xac, 0xad, 0xb4, 0xcd, 0x1d, 0x1e,
        0x86, 0x98, 0x9b, 0x9c, 0xa1, 0x2c, 0x2e, 0x20,
        // clang-format on
    };

    static u8 mark_table[] = {
        // clang-format off
        0x2b, 0xb9, 0x2f, 0x3b, 0x5c, 0xb8, 0xc6, 0xb6,
        0xb7, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xba, 0xbb,
        0xbc, 0xbd, 0xbe, 0xbf, 0xa7, 0xa8, 0xa9, 0xab,
        0xaa, 0xb5, 0xc2, 0xc3, 0xc4, 0xcd, 0xc7, 0xc8,
        0xc9, 0xca, 0xcb, 0xcc, 0xc5, 0xce, 0xcf, 0x20,
        // clang-format on
    };

    static u8* dataS_table[] = { letterS_table, sign_table, mark_table };

    static u8* dataS_table2[] = { letterS_table2, sign_table, mark_table };

    static u8* dataL_table[] = { letterL_table, sign_table, mark_table };

    static u8* dataL_table2[] = { letterL_table2, sign_table, mark_table };

    static u8** data_table[2][2] = { { dataS_table, dataL_table }, { dataS_table2, dataL_table2 } };

    u8* table = data_table[editor_ovl->arrange][editor_ovl->shift_mode][editor_ovl->input_mode];
    int idx = col + row * mED_COLUMNS;

    return table[idx];
}

static void mED_set_stick_area(mED_Ovl_c* editor_ovl) {
    u8 prev_stick_area = editor_ovl->stick_area;

    if (gamePT->mcon.adjusted_pR < 0.2f) {
        /* Stick is in deadzone */
        editor_ovl->stick_area = mED_STICK_AREA_CENTER;
    } else {
        s16 angle = gamePT->mcon.move_angle;

        /* [-180, -157.5) 22.5 degrees */
        if (angle < DEG2SHORT_ANGLE(-157.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_LEFT;
        }
        /* [-157.5, -112.5) 45 degrees */
        else if (angle >= DEG2SHORT_ANGLE(-157.5f) && angle < DEG2SHORT_ANGLE(-112.5f)) {
            editor_ovl->stick_area = prev_stick_area;
        }
        /* [-112.5, -67.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(-67.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_BOTTOM;
        }
        /* [-67.5, -22.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(-22.5f)) {
            editor_ovl->stick_area = prev_stick_area;
        }
        /* [-22.5, 22.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(22.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_RIGHT;
        }
        /* [22.5, 67.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(67.5f)) {
            editor_ovl->stick_area = prev_stick_area;
        }
        /* [67.5, 112.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(112.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_TOP;
        }
        /* [112.5, 157.5) 45 degrees */
        else if (angle < DEG2SHORT_ANGLE(157.5f)) {
            editor_ovl->stick_area = prev_stick_area;
        }
        /* [157.5, 180] 22.5 degrees */
        else {
            editor_ovl->stick_area = mED_STICK_AREA_LEFT;
        }
    }

    if (editor_ovl->stick_area != prev_stick_area) {
        editor_ovl->stick_area_changed = TRUE;
    } else {
        editor_ovl->stick_area_changed = FALSE;
    }
}

static int mED_check_pw_usable_letter_sub(u8 letter) {
    static u8 usable_str_table[] = {
        // clang-format off
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5a, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
        0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
        0x77, 0x78, 0x79, 0x7a, 0x25, 0x26, 0xd1, 0x40,
        0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        // clang-format on
    };

    int i;
    int res = FALSE;

    switch (letter) {
        case CHAR_ZERO:
            letter = CHAR_O;
            break;
        case CHAR_ONE:
            letter = CHAR_l;
            break;
    }

    for (i = 0; i < ARRAY_COUNT(usable_str_table); i++) {
        if (letter == usable_str_table[i]) {
            res = TRUE;
            break;
        }
    }

    return res;
}

static int mED_check_pw_usable_letter(mPC_Ovl_c* passwordChk_ovl) {
    u8* line;
    int i;
    int res = TRUE;

    line = passwordChk_ovl->line0;
    for (i = 0; i < ARRAY_COUNT(passwordChk_ovl->line0); i++) {
        if (mED_check_pw_usable_letter_sub(*line) == FALSE) {
            res = FALSE;
            break;
        }

        line++;
    }

    line = passwordChk_ovl->line1;
    for (i = 0; i < ARRAY_COUNT(passwordChk_ovl->line1); i++) {
        if (mED_check_pw_usable_letter_sub(*line) == FALSE) {
            res = FALSE;
            break;
        }

        line++;
    }

    return res;
}

static void mED_move_keyboard_cursor(mED_Ovl_c* editor_ovl) {
    static int add_w[mED_STICK_AREA_NUM] = { -1, 0, 0, 0, 1, 0, 0, 0, 0 };

    static int add_h[mED_STICK_AREA_NUM] = { 0, 0, -1, 0, 0, 0, 1, 0, 0 };

    int move = FALSE;
    int stick_area = editor_ovl->stick_area;

    if (stick_area != mED_STICK_AREA_CENTER) {
        if (editor_ovl->stick_area_changed == TRUE) {
            editor_ovl->stick_area_held_frames = 0;
            move = TRUE;
        } else {
            editor_ovl->stick_area_held_frames++;

            if (editor_ovl->stick_area_held_frames >= 16) {
                editor_ovl->stick_area_held_frames = 12;
                move = TRUE;
            }
        }
    }

    if (move == TRUE) {
        int move2 = TRUE;
        int next_col = editor_ovl->select_col + add_w[stick_area];
        int next_row = editor_ovl->select_row + add_h[stick_area];

        if (next_col < 0) {
            next_col = 0;
            move2 = FALSE;
        } else if (next_col >= mED_COLUMNS) {
            next_col = mED_COLUMNS - 1;
            move2 = FALSE;
        }

        if (next_row < 0) {
            next_row = 0;
            move2 = FALSE;
        } else if (next_row >= mED_ROWS) {
            next_row = mED_ROWS - 1;
            move2 = FALSE;
        }

        editor_ovl->select_col = next_col;
        editor_ovl->select_row = next_row;

        if (move2 == TRUE) {
            sAdo_SysTrgStart(0x411);
        }
    }
}

static int mED_check_move_cursol(mED_Ovl_c* editor_ovl) {
    u32 buttons = (getButton() | getTrigger()) & (BUTTON_B | BUTTON_DRIGHT | BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP);
    int res = 0;

    if (buttons == BUTTON_NONE) {
        editor_ovl->last_buttons = 0;
        editor_ovl->_10 = 30;
        editor_ovl->_0F = 26;
        editor_ovl->_0E = 0;
    } else {
        if (buttons == editor_ovl->last_buttons) {
            if (editor_ovl->_0E == 1 && editor_ovl->_0F != 0) {
                editor_ovl->_0F--;
            }

            if (editor_ovl->_10 != 0) {
                editor_ovl->_10--;
                return mED_COMMAND_9;
            }

            if (editor_ovl->_0F == 0) {
                editor_ovl->_10 = 2;
                editor_ovl->_34 = 3;
            } else {
                editor_ovl->_10 = 6;
                editor_ovl->_0E = 1;
                editor_ovl->_34 = 2;
            }
        } else {
            editor_ovl->last_buttons = buttons;
            editor_ovl->_10 = 30;
            editor_ovl->_0F = 26;
            editor_ovl->_0E = 0;
        }

        if ((buttons & BUTTON_B) != 0) {
            res = mED_COMMAND_BACKSPACE;
        } else if ((buttons & BUTTON_DLEFT) != 0) {
            res = mED_COMMAND_CURSOL_LEFT;
        } else if ((buttons & BUTTON_DDOWN) != 0) {
            res = mED_COMMAND_CURSOL_LOWER;
        } else if ((buttons & BUTTON_DUP) != 0) {
            res = mED_COMMAND_CURSOL_UPPER;
        } else if ((buttons & BUTTON_DRIGHT) != 0) {
            res = mED_COMMAND_CURSOL_RIGHT;
        }
    }

    return res;
}

static int mED_check_shift(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_L)) {
        if (editor_ovl->shift_mode == mED_SHIFT_LOWER) {
            editor_ovl->shift_mode = mED_SHIFT_UPPER;
        } else {
            editor_ovl->shift_mode = mED_SHIFT_LOWER;
        }

        res = TRUE;
    }

    return res;
}

static int mED_check_arrange(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_Z)) {
        if (editor_ovl->arrange == mED_ARRANGE_QWERTY) {
            editor_ovl->arrange = mED_ARRANGE_ALPHA;
        } else {
            editor_ovl->arrange = mED_ARRANGE_QWERTY;
        }

        res = TRUE;
    }

    return res;
}

static int mED_check_input_mode(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_Y)) {
        editor_ovl->input_mode++;
        editor_ovl->shift_mode = mED_SHIFT_LOWER;

        if (editor_ovl->input_mode >= mED_INPUT_MODE_NUM) {
            editor_ovl->input_mode = mED_INPUT_MODE_LETTER;
        }

        res = TRUE;
    }

    return res;
}

static int mED_check_now_code(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_A)) {
        int code = mED_get_code(editor_ovl, editor_ovl->select_col, editor_ovl->select_row);

        if (code != CHAR_SPACE_3) {
            editor_ovl->now_code = code;
            res = TRUE;
        }
    } else if (chkTrigger(BUTTON_R)) {
        editor_ovl->now_code = CHAR_SPACE;
        res = TRUE;
    }

    return res;
}

static int mED_check_output_code(mED_Ovl_c* editor_ovl) {
    int res = mED_COMMAND_NONE;

    if (mED_check_shift(editor_ovl) == TRUE) {
        if (editor_ovl->input_mode == mED_INPUT_MODE_LETTER) {
            sAdo_SysTrgStart(0x37);
        }
    } else if (mED_check_arrange(editor_ovl) == TRUE) {
        sAdo_SysTrgStart(0x37);
    } else if (mED_check_input_mode(editor_ovl) == TRUE) {
        sAdo_SysTrgStart(0x37);
    } else if (mED_check_now_code(editor_ovl) == TRUE) {
        res = mED_COMMAND_OUTPUT_CODE;
    }

    return res;
}

static void mED_set_command(mED_Ovl_c* editor_ovl) {
    if (chkTrigger(BUTTON_START)) {
        editor_ovl->command = mED_COMMAND_END_EDIT;
    } else if (chkTrigger(BUTTON_X)) {
        editor_ovl->command = mED_COMMAND_EXCHANGE_CODE;
    } else {
        editor_ovl->command = mED_check_move_cursol(editor_ovl);

        if (editor_ovl->command == mED_COMMAND_NONE) {
            editor_ovl->command = mED_check_output_code(editor_ovl);
        }
    }
}

static int mED_get_col_line_width(mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl, s16* param_3, s16* param_4,
                                  s16* param_5, int max) {
    u8* str_p = editor_ovl->input_str;
    int i;
    s16 temp0;
    s16 temp1;
    int cut;
    int res;

    temp0 = 0;
    temp1 = 0;

    cut = TRUE;
    param_4[0] = 0;
    param_3[0] = 0;
    param_5[0] = 0;
    res = mED_LINE_OK;

    if (menu_info->data0 == mED_TYPE_PASSWORDCHK) {
        cut = FALSE;
    }

    for (i = 0; i < max; i++) {
        int temp_res;

        if (*str_p == CHAR_NEW_LINE) {
            temp0 = *param_3;
            temp1 = *param_5;
            param_3[0] = 0;
            param_5[0] = 0;
            param_4[0]++;
            temp_res = mED_LINE_NEWLINE;
        } else {
            s16 width = mFont_GetCodeWidth(*str_p, cut);
            s16 t = *param_5;

            if (t + width > editor_ovl->line_width) {
                temp0 = *param_3;
                temp1 = t;
                param_3[0] = 1;
                param_5[0] = width;
                param_4[0]++;
                temp_res = mED_LINE_WIDTH_OVER;
            } else {
                param_3[0]++;
                param_5[0] += width;
                temp_res = mED_LINE_OK;
            }
        }

        if (*param_4 >= editor_ovl->max_line_no) {
            param_3[0] = temp0 + 1;
            param_4[0] = editor_ovl->max_line_no - 1;
            param_5[0] = temp1;

            if (temp_res == mED_LINE_OK) {
                res = mED_LINE_NUM_OVER;
            } else {
                res = temp_res;
            }

            break;
        }

        str_p++;
    }

    return res;
}

static void mED_check_line_over(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->max_line_no > 1 && editor_ovl->_24 < (editor_ovl->max_line_no - 1) &&
        editor_ovl->input_str[editor_ovl->cursor_idx] != CHAR_NEW_LINE) {
        s16 width = mFont_GetCodeWidth(editor_ovl->input_str[editor_ovl->cursor_idx], TRUE);

        if ((editor_ovl->_26 + width) > editor_ovl->line_width) {
            editor_ovl->_22 = 0;
            editor_ovl->_26 = 0;
            editor_ovl->_24++;
        }
    }
}

static void mED_set_idxcol_inLineWidth(mED_Ovl_c* editor_ovl) {
    u8* str_p = editor_ovl->input_str;
    int i;
    int _22;
    int _26;
    int lines;
    int r25;
    int r24;
    int r23;
    int _24;

    _22 = 0;
    lines = 0;
    _26 = 0;
    r25 = 0;
    r23 = 0;
    r24 = 0;
    _24 = editor_ovl->_24;

    for (i = 0; i < editor_ovl->now_str_len; i++) {
        if (*str_p == CHAR_NEW_LINE) {
            _26 = 0;
            _22 = 0;
            lines++;
        } else {
            int width = mFont_GetCodeWidth(*str_p, TRUE);

            if ((_26 + width) > editor_ovl->line_width) {
                r23 = lines + 1;
                _26 = width;
                r25 = 0;
                r24 = 0;
                _22 = 1;
                lines++;
            } else {
                _26 += width;
            }
        }

        if (lines > _24) {
            if (r23 == _24) {
                _26 = r24;
                _22 = r25;
            }

            break;
        } else if (lines == _24) {
            int temp = editor_ovl->_26;

            if (_26 >= temp) {
                if (r23 == _24 && (temp - r24) < (_26 - temp)) {
                    _26 = r24;
                    _22 = r25;
                    i--;
                }

                _22++;
                i++;
                break;
            }
        }

        r25 = _22;
        r23 = lines;
        r24 = _26;
        str_p++;
        _22++;
    }

    editor_ovl->_26 = _26;
    editor_ovl->cursor_idx = i;
    editor_ovl->_22 = _22;
}

static void mED_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static s16 edit_line[mED_TYPE_NUM] = { 6, 4, 6, 1, 1, 31, 1, 1 };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    editor_ovl->stick_area = mED_STICK_AREA_CENTER;
    editor_ovl->stick_area_changed = FALSE;
    editor_ovl->input_mode = mED_INPUT_MODE_LETTER;
    editor_ovl->shift_mode = mED_SHIFT_LOWER;
    editor_ovl->arrange = mED_ARRANGE_QWERTY;
    editor_ovl->select_col = 0;
    editor_ovl->select_row = 0;
    editor_ovl->stick_area_held_frames = 0;
    editor_ovl->command = mED_COMMAND_NONE;
    editor_ovl->now_code = 0;
    editor_ovl->max_line_no = edit_line[menu_info->data0];
    editor_ovl->input_str = (u8*)menu_info->data2;
    editor_ovl->line_width = menu_info->data3;

    if (menu_info->data1 > 0) {
        editor_ovl->input_length = menu_info->data1;

        if (menu_info->data0 == mED_TYPE_DIARY) {
            editor_ovl->now_str_len =
                mDi_strlen(editor_ovl->input_str, editor_ovl->input_length * editor_ovl->max_line_no, CHAR_SPACE);
        } else {
            editor_ovl->now_str_len =
                mMl_strlen(editor_ovl->input_str, editor_ovl->input_length * editor_ovl->max_line_no, CHAR_SPACE);
        }
    } else {
        int type = menu_info->data0;

        if (type == mED_TYPE_BOARD) {
            editor_ovl->input_length = 32;
            editor_ovl->now_str_len = submenu->overlay->board_ovl->lengths[mBD_FIELD_BODY];
        } else if (type == mED_TYPE_PASSWORDMAKE) {
            editor_ovl->input_length = LAND_NAME_SIZE;
            editor_ovl->now_str_len = submenu->overlay->passwordMake_ovl->lengths[mPM_ENTRY_TOWN];
        } else if (type == mED_TYPE_PASSWORDCHK) {
            editor_ovl->input_length = mPC_STR_SIZE;
            editor_ovl->now_str_len = mPC_STR_SIZE;
        }
    }

    if (menu_info->data0 == mED_TYPE_DIARY) {
        mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;

        if (menu_info->data1 > 0) {
            editor_ovl->cursor_idx = editor_ovl->now_str_len;
            mED_get_col_line_width(menu_info, editor_ovl, &editor_ovl->_22, &editor_ovl->_24, &editor_ovl->_26,
                                   editor_ovl->cursor_idx);
        } else {
            editor_ovl->cursor_idx = diary_ovl->cursor_idx;
            editor_ovl->_22 = diary_ovl->_48;
            editor_ovl->_24 = diary_ovl->_46;
            mED_set_idxcol_inLineWidth(editor_ovl);
        }
    } else {
        editor_ovl->cursor_idx = 0;
        editor_ovl->_22 = 0;
        editor_ovl->_24 = 0;
        editor_ovl->_26 = 0;
    }

    editor_ovl->exchange_code = -1;
}

static void mED_set_se(Submenu* submenu) {
    static u16 se_no[mED_COMMAND_NUM] = {
        0x0000, 0x0035, 0x0035, 0x0035, 0x0035, 0x005F, 0x1034, 0x0036, 0x0033, 0x0000
    };

    static u8 mED_exchange_se_list[TOTAL_CHARS] = {
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE,
        TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE
    };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    int command = editor_ovl->command;

    if (command == mED_COMMAND_OUTPUT_CODE) {
        int voice = mMsg_sound_voice_get_for_editor(editor_ovl->now_code);

        if (voice == 0x85 || voice == 0x80 || voice == 0x81 || voice == 0x82 || voice == 0x83 || voice == -1) {
            voice = 0x86;
        }

        sAdo_VoiceSe(voice, 0xFF, 0xFF, 0, 32, 1);
    } else if (command == mED_COMMAND_EXCHANGE_CODE) {
        int exchange_code = editor_ovl->exchange_code;

        if (exchange_code != -1 && mED_exchange_se_list[exchange_code] != FALSE) {
            int voice = mMsg_sound_voice_get_for_editor(exchange_code);

            sAdo_VoiceSe(voice, 0xFF, 0xFF, 0, 32, 1);
        } else {
            sAdo_SysTrgStart(0x36);
        }
    } else {
        sAdo_SysTrgStart(se_no[command]);
    }
}

static void mED_output_code(mED_Ovl_c* editor_ovl) {
    int len = editor_ovl->now_str_len;
    u8* output_p = editor_ovl->input_str + len;
    int i;

    for (i = len; i > editor_ovl->cursor_idx; i--) {
        output_p[0] = output_p[-1];
        output_p--;
    }

    editor_ovl->cursor_idx++;
    editor_ovl->now_str_len++;
    output_p[0] = editor_ovl->now_code;
    editor_ovl->command_processed = TRUE;
}

static int mED_get_single_line_width(mED_Ovl_c* editor_ovl) {
    u8* str_p = editor_ovl->input_str;
    int i;
    int width = 0;

    for (i = editor_ovl->now_str_len; i > 0; i--) {
        width += mFont_GetCodeWidth(*str_p, TRUE);

        if (*str_p == CHAR_NEW_LINE) {
            break;
        }

        str_p++;
    }

    return width;
}

static void mED_input_single_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        int line_width = mED_get_single_line_width(editor_ovl);
        int now_code_width = mFont_GetCodeWidth(editor_ovl->now_code, TRUE);
        int width = line_width + now_code_width;

        if (editor_ovl->now_str_len < editor_ovl->input_length && width <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        } else {
            mED_open_warning_window(submenu, &submenu->overlay->menu_info[mSM_OVL_EDITOR], mWR_WARNING_WORD_OVER);
        }
    }
}

static void mED_input_multi_line_R(Submenu* submenu, mED_Ovl_c* editor_ovl, u8* buf) {
    mSM_MenuInfo_c* menu_info;
    u8* input_p;
    u8* str_p;
    u8* buf_p;
    int i;
    int res;
    int total_characters;
    s16 b;
    s16 a;
    s16 c;

    menu_info = &submenu->overlay->menu_info[mSM_OVL_EDITOR];
    total_characters = editor_ovl->input_length * editor_ovl->max_line_no;

    if (total_characters <= editor_ovl->now_str_len) {
        mED_open_warning_window(submenu, menu_info, mWR_WARNING_WORD_OVER);
    } else {
        str_p = editor_ovl->input_str;
        buf_p = buf;

        /* Copy string up to cursor */
        for (i = 0; i < editor_ovl->cursor_idx; i++) {
            *buf_p++ = *str_p++;
        }

        *buf_p++ = editor_ovl->now_code; // insert character

        /* Copy the remaining string after the cursor */
        for (i; i < total_characters; i++) {
            *buf_p++ = *str_p++;
        }

        input_p = editor_ovl->input_str; // save pointer
        editor_ovl->input_str = buf;
        res = mED_get_col_line_width(menu_info, editor_ovl, &a, &b, &c, editor_ovl->now_str_len + 1);
        editor_ovl->input_str = input_p; // restore pointer

        switch (res) {
            case mED_LINE_OK:
                mED_output_code(editor_ovl);
                break;
            case mED_LINE_WIDTH_OVER:
            case mED_LINE_NUM_OVER:
                mED_open_warning_window(submenu, menu_info, mWR_WARNING_WORD_OVER);
                break;
            case mED_LINE_NEWLINE:
                if (editor_ovl->_24 != (editor_ovl->max_line_no - 1)) {
                    mED_open_warning_window(submenu, menu_info, mWR_WARNING_WORD_OVER);
                }
                break;
        }
    }
}

static void mED_input_multi_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    u8 buf[1000];

    mED_input_multi_line_R(submenu, editor_ovl, buf);
}

static void mED_input_pw_make_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        int line_width = mED_get_single_line_width(editor_ovl);
        int char_width = mFont_GetCodeWidth(editor_ovl->now_code, TRUE);
        int width = line_width + char_width;

        if (editor_ovl->now_str_len < editor_ovl->input_length && width <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        } else {
            mED_open_warning_window(submenu, &submenu->overlay->menu_info[mSM_OVL_EDITOR], mWR_WARNING_WORD_OVER);
        }
    }
}

static void mED_input_pw_chk_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        u8* str_p;
        u8* src_p;
        u8* dst_p;
        int cursor_idx;
        int size;
        int i;
        int len;

        if (editor_ovl->input_str[editor_ovl->input_length - 1] == CHAR_SPACE) {
            str_p = editor_ovl->input_str + editor_ovl->input_length;
            cursor_idx = editor_ovl->cursor_idx;

            if (cursor_idx < editor_ovl->input_length) {
                len = editor_ovl->input_length;
                src_p = str_p - 2;
                dst_p = str_p - 1;

                for (i = (len - 1) - cursor_idx; i > 0; i--) {
                    *dst_p-- = *src_p--;
                }

                editor_ovl->input_str[editor_ovl->cursor_idx] = editor_ovl->now_code;
                editor_ovl->cursor_idx++;

                if (editor_ovl->cursor_idx >= editor_ovl->input_length) {
                    mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;

                    if (passwordChk_ovl->selected_line == 0) {
                        passwordChk_ovl->selected_line = 1;
                        editor_ovl->input_str = passwordChk_ovl->line1;
                        editor_ovl->cursor_idx = 0;
                    } else {
                        editor_ovl->cursor_idx = editor_ovl->input_length;
                    }
                }

                editor_ovl->command_processed = TRUE;
                return;
            }
        }

        sAdo_SysTrgStart(0x1003);
    } else {
        sAdo_SysTrgStart(0x1003);
    }
}

static void mED_move_cursol_right(Submenu* submenu, mED_Ovl_c* editor_ovl, int line_type) {
    s16 now_str_len;
    s16 cursor_idx;

    cursor_idx = editor_ovl->cursor_idx;
    now_str_len = editor_ovl->now_str_len;

    if (cursor_idx < now_str_len && now_str_len > 0) {
        editor_ovl->cursor_idx = cursor_idx + 1;
        editor_ovl->command_processed = TRUE;
    } else if (cursor_idx == now_str_len) {
        editor_ovl->now_code = CHAR_SPACE;

        switch (line_type) {
            case mED_LINETYPE_MULTI:
                mED_input_multi_line(submenu, editor_ovl);
                break;
            case mED_LINETYPE_SINGLE:
                mED_input_single_line(submenu, editor_ovl);
                break;
            case mED_LINETYPE_PW:
                mED_input_pw_make_line(submenu, editor_ovl);
                break;
        }

        if (editor_ovl->command_processed != FALSE) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_move_cursol_left(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->cursor_idx > 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->command_processed = TRUE;
    }
}

static void mED_move_cursol_upper(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->_24 > 0) {
        editor_ovl->_24--;
        mED_set_idxcol_inLineWidth(editor_ovl);
        editor_ovl->command_processed = TRUE;
    }
}

static void mED_move_cursol_lower(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    s16 a;
    s16 b;
    s16 c;

    mED_get_col_line_width(&submenu->overlay->menu_info[mSM_OVL_EDITOR], editor_ovl, &a, &b, &c,
                           editor_ovl->now_str_len);

    if (editor_ovl->_24 < b) {
        editor_ovl->_24++;
        mED_set_idxcol_inLineWidth(editor_ovl);
        editor_ovl->command_processed = TRUE;
    } else if (editor_ovl->cursor_idx == editor_ovl->now_str_len) {
        editor_ovl->now_code = CHAR_NEW_LINE;
        mED_input_multi_line(submenu, editor_ovl);

        if (editor_ovl->command_processed == TRUE) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_end_edit_func(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_BOTTOM); // transition off the bottom of the screen
    submenu->overlay->editor_ovl->command_processed = TRUE;
}

static void mED_backspace_func(mED_Ovl_c* editor_ovl) {
    u8* str_p;
    int i;

    if (editor_ovl->cursor_idx != 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->now_str_len--;

        str_p = editor_ovl->input_str + editor_ovl->cursor_idx;

        for (i = editor_ovl->cursor_idx; i < editor_ovl->now_str_len; i++) {
            str_p[0] = str_p[1];
            str_p++;
        }

        str_p[0] = CHAR_SPACE;
        editor_ovl->command_processed = TRUE;
    }
}

static void mED_backspace_func_pw_chk(mED_Ovl_c* editor_ovl, mPC_Ovl_c* passwordChk_ovl) {
    if (editor_ovl->cursor_idx != 0) {
        editor_ovl->cursor_idx--;
        mem_copy(editor_ovl->input_str + editor_ovl->cursor_idx, editor_ovl->input_str + editor_ovl->cursor_idx + 1,
                 (editor_ovl->input_length - editor_ovl->cursor_idx) - 1);
        editor_ovl->input_str[editor_ovl->input_length - 1] = CHAR_SPACE;
        editor_ovl->command_processed = TRUE;
    } else if (passwordChk_ovl->selected_line == 1) {
        passwordChk_ovl->selected_line = 0;
        editor_ovl->input_str = passwordChk_ovl->line0;
        editor_ovl->cursor_idx = editor_ovl->input_length - 1;
        editor_ovl->input_str[editor_ovl->cursor_idx] = CHAR_SPACE;
        editor_ovl->command_processed = TRUE;
    }
}

static int mED_get_exchange_code(mED_Ovl_c* editor_ovl) {
    int exchange_code = -1;

    if (editor_ovl->cursor_idx != 0) {
        int ornament = mED_ornament_table[editor_ovl->input_str[editor_ovl->cursor_idx - 1]];
        int exchange = editor_ovl->input_str[editor_ovl->cursor_idx - 1];

        if (exchange != ornament) {
            exchange_code = ornament;
        }
    }

    return exchange_code;
}

static int mED_exchange_code_func(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->exchange_code != -1) {
        editor_ovl->command_processed = TRUE;
        editor_ovl->input_str[editor_ovl->cursor_idx - 1] = editor_ovl->exchange_code;
    }

    return editor_ovl->command_processed;
}

static void mED_clear_input_data(mED_Ovl_c* editor_ovl) {
    u8* str_p = editor_ovl->input_str;
    int i;

    for (i = 0; i < editor_ovl->input_length; i++) {
        *str_p++ = CHAR_SPACE;
    }

    editor_ovl->now_str_len = 0;
    editor_ovl->_22 = 0;
    editor_ovl->cursor_idx = 0;
    editor_ovl->_26 = 0;
}

static int mED_all_space_check(Submenu* submenu, mED_Ovl_c* editor_ovl, mSM_MenuInfo_c* menu_info) {
    if (menu_info->data0 != mED_TYPE_LEDIT) {
        return FALSE;
    } else {
        u8* str_p = editor_ovl->input_str;
        int res;

        if (submenu->overlay->menu_info[mSM_OVL_LEDIT].data0 == 2) {
            if (mem_cmp(submenu->overlay->menu_info[mSM_OVL_LEDIT].data2, str_p, editor_ovl->input_length) == 0) {
                res = FALSE;
            } else {
                res = TRUE;
            }
        } else {
            res = FALSE;
        }

        if (res == FALSE) {
            u8* t_str_p = str_p;
            int i;

            for (i = 0; i < editor_ovl->now_str_len; i++) {
                if (*t_str_p != CHAR_SPACE) {
                    return FALSE;
                }

                t_str_p++;
            }
        }

        mED_clear_input_data(editor_ovl);
        return TRUE;
    }
}

static int mED_ng_word_check(mED_Ovl_c* editor_ovl, mSM_MenuInfo_c* menu_info) {
    static int ng_word_length[mED_NG_WORD_NUM] = { 4, 4, 4, 4, 4, 5, 5, 7, 7, 7, 7, 7, 9, 10 };

    if (menu_info->data0 == mED_TYPE_LEDIT) {
        u8 ng_word[10];
        int len;
        u8* str_p;
        int i;
        int j;
        int idx = mED_NG_WORD_START;

        for (i = 0; i < mED_NG_WORD_NUM; i++) {
            len = ng_word_length[i];
            mString_Load_StringFromRom(ng_word, sizeof(ng_word), idx);
            str_p = editor_ovl->input_str;

            for (j = (editor_ovl->input_length - len) + 1; j >= 0; j--) {
                if (mem_cmp(str_p, ng_word, len) == TRUE) {
                    mED_clear_input_data(editor_ovl);
                    return TRUE;
                }

                str_p++;
            }

            idx++;
        }
    }
    return FALSE;
}

static void mED_edit_func_multi_line(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            mED_move_cursol_lower(submenu, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_UPPER:
            mED_move_cursol_upper(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_MULTI);
            break;
        case mED_COMMAND_END_EDIT:
            mED_end_edit_func(submenu, menu_info);
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_multi_line(submenu, editor_ovl);
            break;
    }
}

static void mED_edit_func_single_line(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            break;
        case mED_COMMAND_CURSOL_UPPER:
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_SINGLE);
            break;
        case mED_COMMAND_END_EDIT:
            if (mED_all_space_check(submenu, editor_ovl, menu_info) != FALSE) {
                sAdo_SysTrgStart(0x1003);
            } else if (mED_ng_word_check(editor_ovl, menu_info) != FALSE) {
                sAdo_SysTrgStart(0x1003);
            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_single_line(submenu, editor_ovl);
            break;
    }
}

static void mED_edit_func_letter_header_kill_space(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mED_Ovl_c* editor_ovl = overlay->editor_ovl;
    mBD_Ovl_c* board_ovl = overlay->board_ovl;

    if (overlay->menu_info[mSM_OVL_BOARD].data0 == 3) {
        s16 len = mMl_strlen(editor_ovl->input_str, editor_ovl->input_length, CHAR_SPACE);
        s16 _22 = editor_ovl->_22;

        if (_22 > len) {
            len = _22;
        }

        editor_ovl->now_str_len = len;
    } else {
        s16 len = mMl_strlen(editor_ovl->input_str, editor_ovl->input_length, CHAR_SPACE);
        int header_back_start = board_ovl->mail.content.header_back_start;
        int min_len = editor_ovl->_22;
        int res;

        if (len > header_back_start) {
            res = len;
        } else {
            res = header_back_start;
        }

        if (res > min_len) {
            res = header_back_start;

            if (len > header_back_start) {
                res = len;
            }
        } else {
            res = min_len;
        }

        editor_ovl->now_str_len = res;
    }
}

static void mED_edit_func_letter_header(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mED_Ovl_c* editor_ovl = overlay->editor_ovl;
    mBD_Ovl_c* board_ovl = overlay->board_ovl;

    if (overlay->menu_info[mSM_OVL_BOARD].data0 == 3) {
        mED_edit_func_single_line(submenu, menu_info);
    } else if (board_ovl->header_pos != mBD_HEADER_POS_ON_NAME) {
        s16 len = editor_ovl->now_str_len;

        if (board_ovl->mail.content.header_back_start == editor_ovl->cursor_idx &&
            ((board_ovl->header_pos == mBD_HEADER_POS_PRE_NAME && editor_ovl->command == mED_COMMAND_CURSOL_RIGHT) ||
             (board_ovl->header_pos == mBD_HEADER_POS_POST_NAME &&
              (editor_ovl->command == mED_COMMAND_CURSOL_LEFT || editor_ovl->command == mED_COMMAND_BACKSPACE)))) {
            board_ovl->header_pos = mBD_HEADER_POS_ON_NAME;
            editor_ovl->command_processed = TRUE;
        } else {
            mED_edit_func_single_line(submenu, menu_info);

            if (board_ovl->header_pos == mBD_HEADER_POS_PRE_NAME) {
                if (len > editor_ovl->now_str_len) {
                    board_ovl->mail.content.header_back_start--;
                } else if (len < editor_ovl->now_str_len) {
                    board_ovl->mail.content.header_back_start++;
                }
            }
        }
    }

    mED_edit_func_letter_header_kill_space(submenu);
}

static void mED_break_space_code(u8* str) {
    u8 buf[32];

    mem_copy(buf, str + 1, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = CHAR_SPACE;
    mem_copy(str, buf, sizeof(buf));
}

static void mED_input_footer_line_sub(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    int now_code_width = mFont_GetCodeWidth(editor_ovl->now_code, TRUE);
    int str_width = mFont_GetStringWidth(editor_ovl->input_str, editor_ovl->now_str_len, TRUE);
    int width = str_width + now_code_width;

    if ((editor_ovl->now_str_len + 1) <= editor_ovl->input_length) {
        if (width <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        } else if (editor_ovl->input_str[0] == CHAR_SPACE &&
                   width - mFont_GetCodeWidth(CHAR_SPACE, TRUE) < editor_ovl->line_width) {
            mED_break_space_code(editor_ovl->input_str);
            editor_ovl->now_str_len--;
            mED_output_code(editor_ovl);
        } else {
            mED_open_warning_window(submenu, menu_info, mWR_WARNING_WORD_OVER);
        }
    } else if (editor_ovl->input_str[0] == CHAR_SPACE &&
               width - mFont_GetCodeWidth(CHAR_SPACE, TRUE) < editor_ovl->line_width) {
        mED_break_space_code(editor_ovl->input_str);
        editor_ovl->now_str_len--;
        mED_output_code(editor_ovl);
    } else {
        mED_open_warning_window(submenu, menu_info, mWR_WARNING_WORD_OVER);
    }
}

static void mED_input_footer_line(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    switch (editor_ovl->now_code) {
        case CHAR_NEW_LINE:
            break;
        case CHAR_SPACE:
            if (editor_ovl->cursor_idx != 0) {
                mED_input_footer_line_sub(submenu, menu_info, editor_ovl);
            }
            break;
        default:
            mED_input_footer_line_sub(submenu, menu_info, editor_ovl);
            break;
    }
}

static void mED_move_footer_cursol_right(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    s16 str_len;
    s16 cursor_idx;

    cursor_idx = editor_ovl->cursor_idx;
    str_len = editor_ovl->now_str_len;

    if (cursor_idx < str_len && str_len > 0) {
        if (cursor_idx == 0 && editor_ovl->input_str[0] == CHAR_SPACE) {
            u8* str_p = editor_ovl->input_str;
            int i;

            editor_ovl->now_str_len = str_len - 1;
            for (i = 0; i < editor_ovl->now_str_len; i++) {
                str_p[0] = str_p[1];
                str_p++;
            }

            str_p[0] = CHAR_SPACE;
            editor_ovl->command_processed = TRUE;
        } else {
            editor_ovl->cursor_idx++;
            editor_ovl->command_processed = TRUE;
        }
    } else if (cursor_idx == str_len) {
        editor_ovl->now_code = CHAR_SPACE;
        mED_input_footer_line(submenu, menu_info, editor_ovl);

        if (editor_ovl->command_processed) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_move_footer_cursol_left(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->cursor_idx > 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->command_processed = TRUE;
    } else if (editor_ovl->now_str_len < editor_ovl->input_length) {
        editor_ovl->now_code = CHAR_SPACE;
        mED_input_footer_line(submenu, menu_info, editor_ovl);
        editor_ovl->cursor_idx = 0;

        if (editor_ovl->command_processed) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_edit_func_letter_footer(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_footer_cursol_left(submenu, menu_info, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_footer_cursol_right(submenu, menu_info, editor_ovl);
            break;
        case mED_COMMAND_END_EDIT:
            if (mED_all_space_check(submenu, editor_ovl, menu_info)) {
                sAdo_SysTrgStart(0x1003);
            } else if (mED_ng_word_check(editor_ovl, menu_info)) {
                sAdo_SysTrgStart(0x1003);
            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_footer_line(submenu, menu_info, editor_ovl);
            break;
    }
}

static void mED_move_letter_table(mED_Ovl_c* editor_ovl, mBD_Ovl_c* board_ovl, Submenu* submenu) {
    static s16 letter_table_col[mBD_FIELD_NUM] = { MAIL_HEADER_LEN, MAIL_BODY_LEN / mBD_BODY_LINE_NUM,
                                                   MAIL_FOOTER_LEN };
    static s16 letter_table_width[mBD_FIELD_NUM] = { 112, 192, 192 };

    u8 field = board_ovl->field;
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];
    int next_field;
    int upper;

    if (field == mBD_FIELD_HEADER && board_ovl->header_pos == mBD_HEADER_POS_ON_NAME) {
        return;
    }

    if (editor_ovl->command == mED_COMMAND_CURSOL_UPPER) {
        next_field = field - 1;
        upper = TRUE;
    } else if (editor_ovl->command == mED_COMMAND_CURSOL_LOWER) {
        next_field = field + 1;
        upper = FALSE;
    } else {
        return;
    }

    if (next_field < 0 || next_field >= mBD_FIELD_NUM) {
        return;
    }

    editor_ovl->command_processed = TRUE;
    board_ovl->field = next_field;
    board_ovl->header_pos = mBD_HEADER_POS_PRE_NAME;
    editor_ovl->input_length = letter_table_col[next_field];
    editor_ovl->line_width = letter_table_width[next_field];
    menu_info->data3 = letter_table_width[next_field];

    if (next_field == mBD_FIELD_BODY) {
        editor_ovl->max_line_no = mBD_BODY_LINE_NUM;
        editor_ovl->input_str = board_ovl->mail.content.body;

        if (upper == TRUE) {
            editor_ovl->cursor_idx = -1;
        } else {
            editor_ovl->cursor_idx = 0;
        }
    } else {
        editor_ovl->max_line_no = 1;
        editor_ovl->cursor_idx = 0;

        if (next_field == mBD_FIELD_HEADER) {
            editor_ovl->input_str = board_ovl->mail.content.header;
        } else {
            editor_ovl->input_str = board_ovl->mail.content.footer;
        }
    }

    editor_ovl->now_str_len = board_ovl->lengths[next_field];

    if (editor_ovl->cursor_idx == -1) {
        editor_ovl->cursor_idx = editor_ovl->now_str_len;
    }
}

typedef void (*mED_BASE_FUNC)(Submenu*, mSM_MenuInfo_c*);

static void mED_edit_func_letter(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mED_BASE_FUNC letter_base_func[mBD_FIELD_NUM] = { &mED_edit_func_letter_header, &mED_edit_func_multi_line,
                                                             &mED_edit_func_letter_footer };

    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    int field = board_ovl->field;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    (*letter_base_func[field])(submenu, menu_info);
    board_ovl->lengths[field] = editor_ovl->now_str_len;

    if (editor_ovl->command_processed == FALSE) {
        mED_move_letter_table(editor_ovl, board_ovl, submenu);
    }
}

static void mED_edit_func_diary(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    /* @unused */
    static mED_BASE_FUNC letter_base_func[mBD_FIELD_NUM] = { &mED_edit_func_letter_header, &mED_edit_func_multi_line,
                                                             &mED_edit_func_single_line };

    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    int field = diary_ovl->field;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            mED_move_cursol_lower(submenu, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_UPPER:
            mED_move_cursol_upper(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_MULTI);
            break;
        case mED_COMMAND_END_EDIT:
            mED_end_edit_func(submenu, menu_info);
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_multi_line(submenu, editor_ovl);
            break;
    }

    diary_ovl->entry_len[field] = editor_ovl->now_str_len;
}

static void mED_move_pw_make_table(mED_Ovl_c* editor_ovl, mPM_Ovl_c* passwordMake_ovl) {
    static s16 pm_make_table_col[mPM_ENTRY_NUM] = { LAND_NAME_SIZE, PLAYER_NAME_LEN };
    int next_idx;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LOWER: {
            if (passwordMake_ovl->selected_idx == mPM_ENTRY_TOWN) {
                editor_ovl->now_str_len = mMl_strlen(editor_ovl->input_str, editor_ovl->input_length, CHAR_SPACE);
                editor_ovl->cursor_idx = editor_ovl->now_str_len;
                passwordMake_ovl->lengths[mPM_ENTRY_TOWN] = editor_ovl->now_str_len;

                if (editor_ovl->now_str_len == 0) {
                    sAdo_SysTrgStart(0x1003);
                    return;
                }
            }

            next_idx = passwordMake_ovl->selected_idx + 1;
            break;
        }

        case mED_COMMAND_CURSOL_UPPER:
        case mED_COMMAND_BACKSPACE:
            next_idx = passwordMake_ovl->selected_idx - 1;
            break;

        default:
            return;
    }

    if (next_idx < 0 || next_idx >= mPM_ENTRY_NUM) {
        return;
    }

    editor_ovl->command_processed = TRUE;
    passwordMake_ovl->selected_idx = (u8)next_idx;
    editor_ovl->input_length = pm_make_table_col[next_idx];
    editor_ovl->line_width = editor_ovl->input_length * 10;

    switch (next_idx) {
        case mPM_ENTRY_TOWN:
            editor_ovl->input_str = passwordMake_ovl->town_name;
            break;
        case mPM_ENTRY_PLAYER:
            editor_ovl->input_str = passwordMake_ovl->player_name;
            break;
    }

    editor_ovl->max_line_no = 1;
    editor_ovl->now_str_len = passwordMake_ovl->lengths[next_idx];

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_UPPER:
        case mED_COMMAND_CURSOL_LOWER:
            mED_set_idxcol_inLineWidth(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT: // ??
            editor_ovl->cursor_idx = 0;
            break;
        case mED_COMMAND_CURSOL_LEFT: // ??
        default:                      // ??
            editor_ovl->cursor_idx = editor_ovl->now_str_len;
            break;
    }
}

static void mED_edit_func_pw_make(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int selected_idx;
    mPM_Ovl_c* passwordMake_ovl = submenu->overlay->passwordMake_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    selected_idx = passwordMake_ovl->selected_idx;
    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_PW);
            break;
        case mED_COMMAND_END_EDIT:
            if (selected_idx == mPM_ENTRY_TOWN) {
                editor_ovl->command = mED_COMMAND_CURSOL_LOWER;
            } else if (mMl_strlen(editor_ovl->input_str, editor_ovl->input_length, CHAR_SPACE) == 0) {
                editor_ovl->cursor_idx = 0;
                editor_ovl->now_str_len = 0;
                sAdo_SysTrgStart(0x1003);
            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_pw_make_line(submenu, editor_ovl);
            break;
    }

    passwordMake_ovl->lengths[selected_idx] = editor_ovl->now_str_len;

    if (editor_ovl->command_processed == FALSE) {
        mED_move_pw_make_table(editor_ovl, passwordMake_ovl);
    }
}

static void mED_move_pw_chk_table(mED_Ovl_c* editor_ovl, mPC_Ovl_c* passwordChk_ovl) {
    int next_line;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LOWER:
            next_line = passwordChk_ovl->selected_line + 1;
            break;
        case mED_COMMAND_CURSOL_UPPER:
            next_line = passwordChk_ovl->selected_line - 1;
            break;
        default:
            return;
    }

    if (next_line < 0 || next_line >= mPC_LINE_COUNT) {
        return;
    }

    editor_ovl->command_processed = TRUE;
    passwordChk_ovl->selected_line = (u8)next_line;

    switch (next_line) {
        case 0:
            editor_ovl->input_str = passwordChk_ovl->line0;
            break;
        case 1:
            editor_ovl->input_str = passwordChk_ovl->line1;
            break;
    }
}

static void mED_edit_func_pw_chk(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int selected_idx;
    mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    selected_idx = passwordChk_ovl->selected_line;
    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            if (editor_ovl->cursor_idx > 0) {
                editor_ovl->cursor_idx--;
                editor_ovl->command_processed = TRUE;
            } else {
                sAdo_SysTrgStart(0x1003);
            }
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            if (editor_ovl->cursor_idx < editor_ovl->input_length) {
                editor_ovl->cursor_idx++;
                editor_ovl->command_processed = TRUE;
            } else {
                sAdo_SysTrgStart(0x1003);
            }
            break;
        case mED_COMMAND_END_EDIT:
            if (passwordChk_ovl->line1[mPC_STR_SIZE - 1] != CHAR_SPACE &&
                mED_check_pw_usable_letter(passwordChk_ovl) == FALSE) {
                mED_open_warning_window(submenu, menu_info, mWR_WARNING_PW_CHK);
            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func_pw_chk(editor_ovl, passwordChk_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_pw_chk_line(submenu, editor_ovl);
            break;
    }

    if (editor_ovl->command_processed == FALSE) {
        mED_move_pw_chk_table(editor_ovl, passwordChk_ovl);
    }
}

static void mED_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

typedef void (*mED_EDIT_FUNC)(Submenu*, mSM_MenuInfo_c*);

static void mED_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mED_EDIT_FUNC mED_edit_func[mED_TYPE_NUM] = { &mED_edit_func_letter,      &mED_edit_func_multi_line,
                                                         &mED_edit_func_multi_line,  &mED_edit_func_single_line,
                                                         &mED_edit_func_single_line, &mED_edit_func_diary,
                                                         &mED_edit_func_pw_make,     &mED_edit_func_pw_chk };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mBD_Ovl_c* board_ovl;

    editor_ovl->command_processed = FALSE;
    if (submenu->overlay->address_ovl != NULL &&
        submenu->overlay->menu_info[mSM_OVL_ADDRESS].next_proc_status == mSM_OVL_PROC_WAIT) {
        editor_ovl->stick_area = mED_STICK_AREA_CENTER;
        editor_ovl->command = mED_COMMAND_NONE;
        editor_ovl->last_buttons =
            (getButton() | getTrigger()) & (BUTTON_B | BUTTON_DRIGHT | BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP);
        editor_ovl->_10 = 30;
        editor_ovl->_0F = 26;
        editor_ovl->_0E = 0;

        if (submenu->overlay->address_ovl->editor_move_down) {
            board_ovl = submenu->overlay->board_ovl;

            if (board_ovl != NULL) {
                submenu->overlay->address_ovl->editor_move_down = FALSE;
                editor_ovl->command = mED_COMMAND_CURSOL_LOWER;
                mED_move_letter_table(editor_ovl, board_ovl, submenu);
                editor_ovl->exchange_code = mED_get_exchange_code(editor_ovl);
            }
        }
    } else {
        editor_ovl->cursol_opacity_step++;

        if (editor_ovl->cursol_opacity_step == 35) {
            editor_ovl->cursol_opacity_step = 0;
        }

#if defined(TARGET_PC) && defined(KEYBOARD_TYPING)
        {
            extern int g_pc_editor_active;
            extern int g_pc_typing_mode;
            extern int pc_typing_queue_pop(int*);
            int pc_typed_char = 0;
            int typed;
            g_pc_editor_active = 1;

            if (g_pc_typing_mode && pc_typing_queue_pop(&typed)) {
                pc_typed_char = 1;
                if (typed == 256) {
                    editor_ovl->command = mED_COMMAND_BACKSPACE;
                } else if (typed == 257) {
                    editor_ovl->command = mED_COMMAND_CURSOL_LEFT;
                } else if (typed == 258) {
                    editor_ovl->command = mED_COMMAND_CURSOL_RIGHT;
                } else if (typed == 259) {
                    editor_ovl->command = mED_COMMAND_CURSOL_UPPER;
                } else if (typed == 260) {
                    editor_ovl->command = mED_COMMAND_CURSOL_LOWER;
                } else if (typed == 261) {
                    if (editor_ovl->max_line_no <= 1) {
                        editor_ovl->command = mED_COMMAND_END_EDIT;
                    } else {
                        editor_ovl->now_code = CHAR_NEW_LINE;
                        editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
                    }
                } else {
                    editor_ovl->now_code = (u8)typed;
                    editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
                }
            }

            if (!pc_typed_char) {
#endif
                mED_set_stick_area(editor_ovl);
                mED_move_keyboard_cursor(editor_ovl);
                mED_set_command(editor_ovl);
#if defined(TARGET_PC) && defined(KEYBOARD_TYPING)
            }
        }
#endif
        (*mED_edit_func[menu_info->data0])(submenu, menu_info);

        if (editor_ovl->command_processed) {
            mED_set_se(submenu);
            editor_ovl->exchange_code = mED_get_exchange_code(editor_ovl);

            if (editor_ovl->command == mED_COMMAND_CURSOL_RIGHT || editor_ovl->command == mED_COMMAND_CURSOL_LEFT ||
                editor_ovl->command == mED_COMMAND_CURSOL_UPPER || editor_ovl->command == mED_COMMAND_CURSOL_LOWER ||
                editor_ovl->command == mED_COMMAND_BACKSPACE || editor_ovl->command == mED_COMMAND_OUTPUT_CODE) {
                editor_ovl->cursol_opacity_step = 0;
            }
        }
    }

    mED_get_col_line_width(menu_info, editor_ovl, &editor_ovl->_22, &editor_ovl->_24, &editor_ovl->_26,
                           editor_ovl->cursor_idx);
    mED_check_line_over(editor_ovl);
}

static void mED_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (submenu->menu_type != menu_info->next_menu_type) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    }
}

static void mED_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
#if defined(TARGET_PC) && defined(KEYBOARD_TYPING)
    { extern int g_pc_editor_active; g_pc_editor_active = 0; }
#endif
    submenu->overlay->editor_ovl->_22 = 0;
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mED_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mED_editor_ovl_move(Submenu* submenu) {
    static mED_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = { &mED_move_Move, &mED_move_Play, &mED_move_Wait,
                                                                 (mED_OVL_MOVE_PROC)&none_proc1, &mED_move_End };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern u8 kai_sousa_button1a_tex_rgb_ia8[];
extern u8 kai_sousa_button1b_tex_rgb_ia8[];
extern Gfx kai_sousa_abuttonT_model[];

static void mED_KeyDraw_A_button(GRAPH* graph) {
    static u8* tex[] = { kai_sousa_button1a_tex_rgb_ia8, kai_sousa_button1b_tex_rgb_ia8 };

    int key = 0;
    Gfx* gfx;

    if (chkButton(BUTTON_A)) {
        key = 1;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[key]);
    gSPDisplayList(gfx++, kai_sousa_abuttonT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_button2a_tex_rgb_ia8[];
extern u8 kai_sousa_button2b_tex_rgb_ia8[];
extern Gfx kai_sousa_bbuttonT_model[];
extern Gfx kai_sousa_cancelT_model[];

static void mED_KeyDraw_B_button(GRAPH* graph) {
    static u8* tex[] = { kai_sousa_button2a_tex_rgb_ia8, kai_sousa_button2b_tex_rgb_ia8 };

    int key = 0;
    Gfx* gfx;

    if (chkButton(BUTTON_B)) {
        key = 1;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[key]);
    gSPDisplayList(gfx++, kai_sousa_bbuttonT_model);
    gSPDisplayList(gfx++, kai_sousa_cancelT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_xbutton_tex_rgb_ia8[];
extern u8 kai_sousa_xbutton2_tex_rgb_ia8[];
extern Gfx kai_sousa_xbuttonT_model[];
extern Gfx kai_sousa_henkan_model[];
extern Gfx kai_sousa_yajirushi_model[];

static void mED_KeyDraw_X_button(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8* tex[] = { kai_sousa_xbutton_tex_rgb_ia8, kai_sousa_xbutton2_tex_rgb_ia8 };

    int key = 0;
    Gfx* gfx;

    if (chkButton(BUTTON_X)) {
        key = 1;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[key]);
    gSPDisplayList(gfx++, kai_sousa_henkan_model);

    if (editor_ovl->exchange_code != -1) {
        gSPDisplayList(gfx++, kai_sousa_yajirushi_model);
    }

    gSPDisplayList(gfx++, kai_sousa_xbuttonT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_ybutton_tex_rgb_ia8[];
extern u8 kai_sousa_ybutton2_tex_rgb_ia8[];
extern Gfx kai_sousa_ybuttonT_model[];
extern Gfx kai_sousa_kirikae_model[];
extern Gfx kai_sousa_letter_model[];
extern Gfx kai_sousa_sign_model[];
extern Gfx kai_sousa_mark_model[];

static void mED_KeyDraw_Y_button(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8* tex[] = { kai_sousa_ybutton_tex_rgb_ia8, kai_sousa_ybutton2_tex_rgb_ia8 };

    static Gfx* dl[mED_INPUT_MODE_NUM] = { kai_sousa_letter_model, kai_sousa_sign_model, kai_sousa_mark_model };

    /* r, g, b, a, l */
    static u8 prim[2][5] = { { 155, 155, 160, 255, 255 }, { 225, 255, 255, 255, 255 } };

    int mode = editor_ovl->input_mode;
    int key = 0;
    Gfx* gfx;
    int i;

    if (chkButton(BUTTON_Y)) {
        key = 1;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[key]);
    gSPDisplayList(gfx++, kai_sousa_kirikae_model);

    for (i = 0; i < mED_INPUT_MODE_NUM; i++) {
        u8* col;

        if (i == mode) {
            col = prim[1];
        } else {
            col = prim[0];
        }

        gDPSetPrimColor(gfx++, 0, col[4], col[0], col[1], col[2], col[3]);
        gSPDisplayList(gfx++, dl[i]);
    }

    gSPDisplayList(gfx++, kai_sousa_ybuttonT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx kai_sousa_startbuttonT_model[];
extern Gfx kai_sousa_endT_model[];

static void mED_KeyDraw_START_button(GRAPH* graph) {
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPDisplayList(gfx++, kai_sousa_startbuttonT_model);
    gSPDisplayList(gfx++, kai_sousa_endT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

typedef struct l_button_info_s {
    u8* tex;
    int prim;
} mED_L_button_info_c;

extern u8 kai_sousa_caps_tex_rgb_i4[];
extern u8 kai_sousa_small_tex_rgb_i4[];
extern u8 kai_sousa_lbutton_tex_rgb_ia8[];
extern u8 kai_sousa_lbutton2_tex_rgb_ia8[];
extern Gfx kai_sousa_lwaku_model[];
extern Gfx kai_sousa_lmoji_model[];
extern Gfx kai_sousa_lbuttonT_model[];

static void mED_KeyDraw_L_button(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static mED_L_button_info_c data[mED_INPUT_MODE_NUM][mED_SHIFT_NUM] = { { { kai_sousa_caps_tex_rgb_i4, 0 },
                                                                             { kai_sousa_small_tex_rgb_i4, 1 } },
                                                                           { { NULL, 0 }, { NULL, 0 } },
                                                                           { { NULL, 0 }, { NULL, 0 } } };

    static u8* btn_tex[] = { kai_sousa_lbutton_tex_rgb_ia8, kai_sousa_lbutton2_tex_rgb_ia8 };

    /* r, g, b, a, l */
    static u8 prim[2][5] = { { 30, 30, 215, 255, 255 }, { 215, 30, 30, 255, 255 } };

    int key = 0;
    Gfx* gfx;
    int prim_idx;
    u8* col;
    int i;
    int mode;
    int shift;
    mED_L_button_info_c* button_info;

    if (chkButton(BUTTON_L)) {
        key = 1;
    }

    mode = editor_ovl->input_mode;
    shift = editor_ovl->shift_mode;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    button_info = &data[mode][shift];
    col = prim[button_info->prim];

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, col[4], col[0], col[1], col[2], col[3]);
    gSPDisplayList(gfx++, kai_sousa_lwaku_model);

    if (data[mode][shift].tex != NULL) {
        gSPSegment(gfx++, G_MWO_SEGMENT_8, button_info->tex);
        gSPDisplayList(gfx++, kai_sousa_lmoji_model);
    }

    gSPSegment(gfx++, G_MWO_SEGMENT_8, btn_tex[key]);
    gSPDisplayList(gfx++, kai_sousa_lbuttonT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_rbutton_tex_rgb_ia8[];
extern u8 kai_sousa_rbutton2_tex_rgb_ia8[];
extern Gfx kai_sousa_rbuttonT_model[];
extern Gfx kai_sousa_spaceT_model[];

static void mED_KeyDraw_R_button(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8* btn_tex[] = { kai_sousa_rbutton_tex_rgb_ia8, kai_sousa_rbutton2_tex_rgb_ia8 };

    int key = 0;
    Gfx* gfx;

    if (chkButton(BUTTON_R)) {
        key = 1;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, btn_tex[key]);
    gSPDisplayList(gfx++, kai_sousa_rbuttonT_model);
    gSPDisplayList(gfx++, kai_sousa_spaceT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Vtx kai_sousa2_v[];
extern u8 testbutton[];

static void mED_KeyDraw_keyboard(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8 model_type[mED_COLUMNS * mED_ROWS] = { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
                                                     1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 };

    static rgba_t sel_col[2] = { { 205, 0, 0, 255 }, { 0, 0, 205, 255 } };

    Vtx* vert = &kai_sousa2_v[0];
    u8* mtype = &model_type[0];
    int selected_col;
    int selected_row;
    rgba_t* color;
    int selected = TRUE;
    int col_idx = 0;
    int col;
    int row;
    Gfx* gfx;

    if (editor_ovl->input_mode == mED_INPUT_MODE_LETTER && editor_ovl->shift_mode == mED_SHIFT_UPPER) {
        col_idx = 1;
    }

    selected_col = editor_ovl->select_col;
    selected_row = editor_ovl->select_row;
    color = &sel_col[col_idx];

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPTexture(gfx++, 0, 0, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (row = 0; row < mED_ROWS; row++) {
        for (col = 0; col < mED_COLUMNS; col++) {
            if (col == selected_col && row == selected_row) {
                gDPSetPrimColor(gfx++, 0, 255, color->r, color->g, color->b, 255);
                selected = TRUE;
            } else if (selected == TRUE) {
                gDPSetPrimColor(gfx++, 0, 255, 255, 255, 255, 255);
                selected = FALSE;
            }

            gDPSetTextureImage_Dolphin(gfx++, G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, testbutton);
            gDPSetTile_Dolphin(gfx++, G_DOLPHIN_TLUT_DEFAULT_MODE, G_TX_RENDERTILE, 15, GX_MIRROR, GX_MIRROR, GX_CLAMP,
                               GX_CLAMP);
            gSPVertex(gfx++, vert, 4, 0);

            if (*mtype != 0) {
                gSPNTrianglesInit_5b(gfx++,
                                     2,       // tri count
                                     0, 1, 2, // tri0
                                     3, 0, 2, // tri1
                                     0, 0, 0  // tri2
                );
            } else {
                gSPNTrianglesInit_5b(gfx++,
                                     2,       // tri count
                                     0, 1, 2, // tri0
                                     1, 3, 2, // tri1
                                     0, 0, 0  // tri2
                );
            }

            vert += 4;
            mtype++;
        }
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_controllpad1_tex_rgb_ia8[];
extern u8 kai_sousa_controllpad2_tex_rgb_ia8[];
extern u8 kai_sousa_controllpad3_tex_rgb_ia8[];
extern u8 kai_sousa_controllpad4_tex_rgb_ia8[];
extern u8 kai_sousa_controllpad5_tex_rgb_ia8[];

extern Gfx kai_sousa_controllpadT_model[];
extern Gfx kai_sousa_cursorT_model[];

static void mED_KeyDraw_J_key(GRAPH* graph) {
    static u8* tex[5] = { kai_sousa_controllpad1_tex_rgb_ia8, kai_sousa_controllpad3_tex_rgb_ia8,
                          kai_sousa_controllpad4_tex_rgb_ia8, kai_sousa_controllpad5_tex_rgb_ia8,
                          kai_sousa_controllpad2_tex_rgb_ia8 };

    int tex_idx = 0;
    Gfx* gfx;

    if (chkButton(BUTTON_DLEFT)) {
        tex_idx = 2;
    } else if (chkButton(BUTTON_DDOWN)) {
        tex_idx = 1;
    } else if (chkButton(BUTTON_DUP)) {
        tex_idx = 4;
    } else if (chkButton(BUTTON_DRIGHT)) {
        tex_idx = 3;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[tex_idx]);
    gSPDisplayList(gfx++, kai_sousa_controllpadT_model);
    gSPDisplayList(gfx++, kai_sousa_cursorT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern u8 kai_sousa_3Dst_tex_rgb_ia8[];
extern u8 kai_sousa_3Dst2_tex_rgb_ia8[];
extern u8 kai_sousa_3Dst3_tex_rgb_ia8[];
extern u8 kai_sousa_3Dst4_tex_rgb_ia8[];
extern u8 kai_sousa_3Dst5_tex_rgb_ia8[];
extern u8 kai_sousa_3Dst6_tex_rgb_ia8[];

extern Gfx kai_sousa_3DT_model[];
extern Gfx kai_sousa_3DstT_model[];

static void mED_KeyDraw_3D_stick(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8* tex[mED_STICK_AREA_NUM] = { kai_sousa_3Dst4_tex_rgb_ia8, kai_sousa_3Dst3_tex_rgb_ia8,
                                           kai_sousa_3Dst2_tex_rgb_ia8, kai_sousa_3Dst3_tex_rgb_ia8,
                                           kai_sousa_3Dst4_tex_rgb_ia8, kai_sousa_3Dst5_tex_rgb_ia8,
                                           kai_sousa_3Dst6_tex_rgb_ia8, kai_sousa_3Dst5_tex_rgb_ia8,
                                           kai_sousa_3Dst_tex_rgb_ia8 };

    int stick_area = editor_ovl->stick_area;
    Gfx* gfx;

    Matrix_push();

    if (stick_area >= mED_STICK_AREA_TOP_RIGHT && stick_area <= mED_STICK_AREA_BOTTOM_RIGHT) {
        Matrix_translate(-111.0f, -50.0f, 0.0f, MTX_MULT);
        Matrix_RotateY(DEG2SHORT_ANGLE(-180.0f), MTX_MULT);
    } else {
        Matrix_translate(-110.0f, -50.0f, 0.0f, MTX_MULT);
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPDisplayList(gfx++, kai_sousa_3DT_model);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex[stick_area]);
    gSPDisplayList(gfx++, kai_sousa_3DstT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    Matrix_pull();
}

extern Gfx kai_sousa_mode[];
extern Gfx kai_sousa_shitaT_model[];
extern Gfx kai_sousa_controllerT_model[];
extern Gfx kai_sousa_controller2T_model[];
extern Gfx kai_sousa_mojibanT_model[];

static void mED_KeyDraw(mED_Ovl_c* editor_ovl, GRAPH* graph, f32 x, f32 y) {
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 0.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kai_sousa_mode);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    mED_KeyDraw_L_button(graph, editor_ovl);
    mED_KeyDraw_R_button(graph, editor_ovl);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPDisplayList(gfx++, kai_sousa_shitaT_model);
    gSPDisplayList(gfx++, kai_sousa_controllerT_model);
    gSPDisplayList(gfx++, kai_sousa_controller2T_model);
    gSPDisplayList(gfx++, kai_sousa_mojibanT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    mED_KeyDraw_A_button(graph);
    mED_KeyDraw_B_button(graph);
    mED_KeyDraw_X_button(graph, editor_ovl);
    mED_KeyDraw_Y_button(graph, editor_ovl);
    mED_KeyDraw_START_button(graph);
    mED_KeyDraw_J_key(graph);
    mED_KeyDraw_3D_stick(graph, editor_ovl);
    mED_KeyDraw_keyboard(graph, editor_ovl);
}

extern Gfx kai_sousa_ink_mode[];
extern Gfx kai_sousa_ink_model[];
extern Gfx kai_sousa_inktuboT_model[];
extern Gfx kai_sousa_inkmojiT_model[];

static void mED_InkPotDraw(Submenu* submenu, mED_Ovl_c* editor_ovl, GRAPH* graph, f32 x, f32 y) {
    f32 line_y;
    f32 single_line_y;
    Gfx* gfx;
    Gfx* scroll_gfx;

    /* Filter out editors without the inkpot */
    switch (submenu->overlay->menu_info[mSM_OVL_EDITOR].data0) {
        case mED_TYPE_BOARD:
            break;
        case mED_TYPE_NOTICE:
            break;
        case mED_TYPE_DIARY:
            break;
        default:
            return;
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 0.0f, MTX_MULT);
    single_line_y = 0.0f;
    line_y = ((f32)editor_ovl->now_str_len * 15.0f) / (f32)(editor_ovl->input_length * editor_ovl->max_line_no);

    if (line_y > 15.0f) {
        line_y = 15.0f;
    }

    if (editor_ovl->max_line_no == 1) {
        single_line_y = ((f32)mED_get_single_line_width(editor_ovl) * 15.0f) / (f32)editor_ovl->line_width;

        if (single_line_y > 15.0f) {
            single_line_y = 15.0f;
        }
    }

    if (line_y < single_line_y) {
        line_y = single_line_y;
    }

    scroll_gfx = two_tex_scroll_dolphin(graph, 0, 0, 0, 32, 32, 1, 0, line_y * 8.0f, 32, 32);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, G_MWO_SEGMENT_8, scroll_gfx);
    gSPDisplayList(gfx++, kai_sousa_ink_mode);
    gSPDisplayList(gfx++, kai_sousa_ink_model);
    gSPDisplayList(gfx++, kai_sousa_inktuboT_model);
    gSPDisplayList(gfx++, kai_sousa_inkmojiT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx lat_sousa_spT_model[];

static void mED_StringsDraw_spaceCode(GAME* game, rgba_t* color, f32 x, f32 y) {
    GRAPH* graph = game->graph;
    Gfx* gfx;

    x = 6.5f + (x - 160.0f);
    y = -(8.5f + (y - 120.0f));

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 0.0f, MTX_MULT);
    Matrix_scale(0.75f, 1.0f, 1.0f, MTX_MULT);

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(gfx++, 0, 255, color->r, color->g, color->b, 255);
    gSPDisplayList(gfx++, lat_sousa_spT_model);
    gSPMatrix(gfx++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(gfx);
}

static void mED_StringsDraw_keyboard(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    static f32 offset_posX[mED_COLUMNS] = {
        60.0f, 76.0f, 92.0f, 108.0f, 124.0f, 140.0f, 156.0f, 172.0f, 188.0f, 204.0f
    };

    static f32 offset_posY[mED_ROWS] = { 133.0f, 149.0f, 165.0f, 181.0f };

    static f32 slide_posX[mED_ROWS] = { 0.0f, 3.0f, 7.0f, 10.0f };

    static rgba_t col[2] = { { 35, 30, 55, 255 }, { 255, 255, 255, 255 } };

    int column;
    int row;
    int sel_col = editor_ovl->select_col;
    int sel_row = editor_ovl->select_row;

    for (row = 0; row < mED_ROWS; row++) {
        for (column = 0; column < mED_COLUMNS; column++) {
            u8 code = mED_get_code(editor_ovl, column, row);

            if (code != CHAR_SPACE_3) {
                rgba_t* color;
                f32 text_x;
                f32 text_y;

                if (column == sel_col && row == sel_row) {
                    color = &col[1];
                } else {
                    color = &col[0];
                }

                text_x = x + offset_posX[column] + slide_posX[row] + 2.0f;
                text_y = -y + offset_posY[row];

                switch (code) {
                    case CHAR_SPACE:
                        mED_StringsDraw_spaceCode(game, color, text_x, text_y);
                        break;
                    default:
                        mFont_SetLineStrings(game, &code, 1, text_x, text_y, color->r, color->g, color->b, 255, FALSE,
                                             FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
                        break;
                }
            }
        }
    }
}

static void mED_StringsDraw_select(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    static rgba_t sp_col = { 255, 255, 255, 255 };
    u8 code = mED_get_code(editor_ovl, editor_ovl->select_col, editor_ovl->select_row);

    if (code != CHAR_SPACE_3) {
        f32 text_x = (237.0f + x) + 5.0f;
        f32 text_y = (177.0f - y) + 3.0f;

        if (chkButton(BUTTON_A)) {
            text_y += 1.0f;
        }

        switch (code) {
            case CHAR_SPACE:
                mED_StringsDraw_spaceCode(game, &sp_col, text_x, text_y);
                break;
            default:
                mFont_SetLineStrings(game, &code, 1, text_x, text_y, 255, 255, 255, 255, FALSE, FALSE, 1.0f, 1.0f,
                                     mFont_MODE_POLY);
                break;
        }
    }
}

static void mED_StringsDraw_ornament(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    if (editor_ovl->exchange_code != -1) {
        u8 code = editor_ovl->exchange_code;
        f32 text_x = 259.0f + x;
        f32 text_y = 190.0f - y;
        int cursor_idx = editor_ovl->cursor_idx;
        u8* str_p = &editor_ovl->input_str[cursor_idx];

        mFont_SetLineStrings(game, &str_p[-1], 1, text_x + 2.0f, text_y, 225, 195, 195, 255, FALSE, FALSE, 1.0f, 1.0f,
                             mFont_MODE_POLY);
        text_x = 281.0f + x;
        mFont_SetLineStrings(game, &code, 1, text_x + 2.0f, text_y, 255, 255, 255, 255, FALSE, FALSE, 1.0f, 1.0f,
                             mFont_MODE_POLY);
    }
}

static void mED_StringsDraw(Submenu* submenu, mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    (*submenu->overlay->set_char_matrix_proc)(game->graph);
    mED_StringsDraw_keyboard(editor_ovl, game, x, y);
    mED_StringsDraw_select(editor_ovl, game, x, y);
    mED_StringsDraw_ornament(editor_ovl, game, x, y);
}

static void mED_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    GRAPH* graph = game->graph;

    mED_KeyDraw(editor_ovl, graph, menu_info->position[0], menu_info->position[1]);
    mED_InkPotDraw(submenu, editor_ovl, graph, menu_info->position[0], menu_info->position[1]);
    mED_StringsDraw(submenu, editor_ovl, game, menu_info->position[0], menu_info->position[1]);
}

extern Gfx lat_end_cordT_model[];

static void mED_endCode_draw(Submenu* submenu, GAME* game, f32 x, f32 y) {
    GRAPH* graph = game->graph;
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_end_cordT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_cursol_draw(Submenu* submenu, GAME* game, f32 x, f32 y) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    int cursol_opacity_step = editor_ovl->cursol_opacity_step;
    int a;

    if (cursol_opacity_step > 17) {
        cursol_opacity_step = 35 - cursol_opacity_step;
    }

    a = ((17 - cursol_opacity_step) * 255) / 17;
    mFont_SetMarkChar(game, mFont_MARKTYPE_CURSOR, x, y, 195, 80, 80, a, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
}

static void mED_editor_ovl_draw(Submenu* submenu, GAME* game) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    (*menu_info->pre_draw_func)(submenu, game);
    mED_set_dl(submenu, menu_info, game);

    if (menu_info->pre_menu_type == mSM_OVL_ADDRESS && submenu->overlay->address_ovl->display_list != NULL) {
        OPEN_DISP(game->graph);

        gSPDisplayList(NOW_POLY_OPA_DISP++, submenu->overlay->address_ovl->display_list);

        CLOSE_DISP(game->graph);
    }

#if defined(TARGET_PC) && defined(KEYBOARD_TYPING)
    {
        extern int g_pc_typing_mode;
        static u8 str_on[]  = "Keyboard Typing (Tab): On";
        static u8 str_off[] = "Keyboard Typing (Tab): Off";
        u8* str = g_pc_typing_mode ? str_on  : str_off;
        int len = (g_pc_typing_mode ? sizeof(str_on) : sizeof(str_off)) - 1; /* drop NUL */
        f32 scale = 0.6f;
        f32 x = 80.0f;

        (*overlay->set_char_matrix_proc)(game->graph);
        mFont_SetLineStrings(game, str, len, x, 8.0f, 255, 255, 255, 180, FALSE, FALSE, scale, scale,
                             mFont_MODE_POLY);
    }
#endif
}

extern void mED_editor_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mED_editor_ovl_move;
    overlay->menu_control.menu_draw_func = &mED_editor_ovl_draw;
}

static void mED_editor_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    (*overlay->move_chg_base_proc)(menu_info, mSM_MOVE_IN_BOTTOM);

    if (menu_info->data0 == mED_TYPE_CP_TITLE || menu_info->data0 == mED_TYPE_LEDIT ||
        menu_info->data0 == mED_TYPE_HBOARD) {
        sAdo_SysTrgStart(0x59);
    }
}

static mED_Ovl_c edit_ovl_data;

extern void mED_editor_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    if (overlay->editor_ovl == NULL) {
        mem_clear((u8*)&edit_ovl_data, sizeof(mED_Ovl_c), 0);
        overlay->editor_ovl = &edit_ovl_data;
    }

    mED_init(submenu, menu_info);
    mED_editor_ovl_init(submenu);
    mED_editor_ovl_set_proc(submenu);
    submenu->overlay->editor_ovl->end_code_draw = &mED_endCode_draw;
    submenu->overlay->editor_ovl->cursol_draw = &mED_cursol_draw;
}

extern void mED_editor_ovl_destruct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->editor_ovl = NULL;
}
