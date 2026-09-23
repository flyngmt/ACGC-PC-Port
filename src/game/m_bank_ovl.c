#include "m_bank_ovl.h"

#include "m_name_table.h"
#include "audio.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_lib.h"
#include "m_common_data.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

static int aNSM_sack_amount[MONEY_NUM] = { 100, 1000, 10000, 30000 };

static mActor_name_t aNSM_itemNo[MONEY_NUM] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };
static u8 mBN_ok_str[] = { CHAR_O, CHAR_K };

static void mBN_now_bell_2_bell(mBN_Ovl_c* bank_ovl) {
    int diff = bank_ovl->now_bell - bank_ovl->player_bell;
    bank_ovl->bell = ABS(diff);
}

static int mBN_cursol_2_keta(int cursol) {
    int keta = 1;

    while (cursol++ < mBN_CURSOL_MAX) {
        keta *= 10;
    }

    return keta;
}

static int mBN_total_item_bell() {
    int i;
    int total_item_bell = 0;

    for (i = 0; i < MONEY_NUM; i++) {
        int possess = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        total_item_bell += possess * aNSM_sack_amount[i];
    }

    return total_item_bell;
}

static void mBN_bank_ok(Submenu* submenu, mSM_MenuInfo_c* menu, mBN_Ovl_c* bank_ovl) {
    int total_item_bell;
    int remain_item_bell;
    int sack_idx;
    int i;

    if (bank_ovl->bank_bell < 0) {
        bank_ovl->bank_bell = 0;
    }

    if (bank_ovl->bank_bell > mBN_DEPOSIT_MAX) {
        bank_ovl->bank_bell = mBN_DEPOSIT_MAX;
    }

    Common_Get(now_private)->bank_account = bank_ovl->bank_bell;

    total_item_bell = mBN_total_item_bell();
    i = 0;

    /* Replace all money sack items with EMPTY_NO */
    while (bank_ovl->now_bell < total_item_bell && i < MONEY_NUM) {
        sack_idx =
            mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);
        if (sack_idx == -1) {
            i++; /* move onto next sack amount */
        } else {
            mPr_SetPossessionItem(Common_Get(now_private), sack_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        }

        total_item_bell = mBN_total_item_bell(); /* update total bell count in sacks */
    }
    
    /* Replace non-30k bell bags with 30k bell bags */
    remain_item_bell = bank_ovl->now_bell - mBN_total_item_bell();
    i = 0;

    while (remain_item_bell > mPr_WALLET_MAX && i < MONEY_NUM - 1) {
        sack_idx =
            mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        if (sack_idx == -1) {
            i++;
        } else {
            mPr_SetPossessionItem(Common_Get(now_private), sack_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
            remain_item_bell -= 30000 - aNSM_sack_amount[i];
        }
    }

    /* Add 30k bell bags to the inventory where empty spaces are */
    i = 0;
    while (remain_item_bell > mPr_WALLET_MAX && i < 1) {
        int sack_idx = mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), EMPTY_NO, mPr_ITEM_COND_NORMAL);

        if (sack_idx == -1) {
            i++;
        } else {
            mPr_SetPossessionItem(Common_Get(now_private), sack_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
            remain_item_bell -= 30000;
        }
    }

    bank_ovl->now_bell -= mBN_total_item_bell();

    if (bank_ovl->now_bell < 0) {
        bank_ovl->now_bell = 0;
    } else if (bank_ovl->now_bell > mPr_WALLET_MAX) {
        bank_ovl->now_bell = mPr_WALLET_MAX;
    }

    Common_Get(now_private)->inventory.wallet = bank_ovl->now_bell;
    (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_TOP);
    sAdo_SysTrgStart(NA_SE_MENU_EXIT);
}

static void mBN_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_Move_proc)(submenu, menu);
}

#ifdef MOUSE_INPUT
static u32 mBN_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu, u32 trigger) {
    mBN_Ovl_c* bank_ovl = submenu->overlay->bank_ovl;
    f32 mouse_x, mouse_y;
    u32 pressed;
    s32 wheel;
    int selected = -1;

    if (submenu->current_menu_type != mSM_OVL_BANK ||
        !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.move_pR > 0.5f) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return trigger;
    }

    pressed = pc_mouse_button_pressed();
    if (pressed & PC_MOUSE_BUTTON_RIGHT) {
        return trigger | BUTTON_B;
    }

    mouse_x -= menu->position[0];
    mouse_y += menu->position[1];
    if (mouse_y >= 124.0f && mouse_y < 140.0f) {
        u8 amount_str[7];
        f32 x;
        int i;

        mFont_UnintToString(amount_str, sizeof(amount_str), bank_ovl->bell, 6, FALSE, TRUE, TRUE);
        x = 211.0f - mFont_GetStringWidth(amount_str, sizeof(amount_str), TRUE);
        for (i = 0; i < 7; i++) {
            int width = mFont_GetCodeWidth(amount_str[i], TRUE);

            if (i != 3 && mouse_x >= x && mouse_x < x + width) {
                selected = i < 3 ? i : i - 1;
                break;
            }
            x += width;
        }
    } else if (mouse_y >= 140.0f && mouse_y < 156.0f && mouse_x >= 206.0f &&
               mouse_x < 210.0f + mFont_GetStringWidth(mBN_ok_str, sizeof(mBN_ok_str), TRUE) * 0.875f) {
        selected = mBN_CUSROL_OK;
    }

    if (selected < 0) {
        return trigger;
    }
    if (bank_ovl->cursol != selected) {
        bank_ovl->cursol = selected;
        sAdo_SysTrgStart(NA_SE_CURSOL);
    }

    if (selected == mBN_CUSROL_OK) {
        return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
    }
    wheel = pc_mouse_scroll_wheel();
    if (wheel > 0 || (pressed & PC_MOUSE_BUTTON_LEFT)) {
        trigger |= BUTTON_CUP;
    } else if (wheel < 0) {
        trigger |= BUTTON_CDOWN;
    }
    return trigger;
}
#endif

static void mBN_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    int trigger = overlay->menu_control.trigger;
    mBN_Ovl_c* bank_ovl = overlay->bank_ovl;

#ifdef MOUSE_INPUT
    trigger = mBN_mouse_trigger(submenu, menu, trigger);
#endif

    if (trigger & BUTTON_B) {
        (*overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else if (trigger & BUTTON_START) {
        mBN_bank_ok(submenu, menu, bank_ovl);
    } else {
        int cursol = bank_ovl->cursol;

        if (cursol == mBN_CUSROL_OK) {
            if (trigger & BUTTON_A) {
                mBN_bank_ok(submenu, menu, bank_ovl);
            } else if (trigger & (BUTTON_CLEFT | BUTTON_CUP)) {
                bank_ovl->cursol = cursol - 1;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        } else if ((trigger & BUTTON_CLEFT) && cursol > 0) {
            bank_ovl->cursol = cursol - 1;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if (trigger & BUTTON_CRIGHT) {
            bank_ovl->cursol += 1;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if ((trigger & BUTTON_CDOWN) || (trigger & BUTTON_CUP)) {
            int keta = mBN_cursol_2_keta(cursol);

            if (trigger & BUTTON_CUP) {
                if (bank_ovl->now_bell < keta) {
                    keta = bank_ovl->now_bell;
                }

                if (keta + bank_ovl->bank_bell > mBN_DEPOSIT_MAX) {
                    keta = mBN_DEPOSIT_MAX - bank_ovl->bank_bell;
                }

                if (keta == 0) {
                    sAdo_SysTrgStart(MONO(3));
                    return;
                }

                if (bank_ovl->now_bell > bank_ovl->player_bell && (bank_ovl->now_bell - keta) < bank_ovl->player_bell) {
                    keta = bank_ovl->now_bell - bank_ovl->player_bell;
                }

                bank_ovl->bank_bell += keta;
                bank_ovl->now_bell -= keta;
            } else {
                if (bank_ovl->bank_bell < keta) {
                    keta = bank_ovl->bank_bell;
                }

                if ((bank_ovl->now_bell + keta) > bank_ovl->player_max_bell) {
                    keta = bank_ovl->player_max_bell - bank_ovl->now_bell;
                }

                if (keta == 0) {
                    sAdo_SysTrgStart(MONO(3));
                    return;
                }

                if (bank_ovl->now_bell < bank_ovl->player_bell && (bank_ovl->now_bell + keta) > bank_ovl->player_bell) {
                    keta = bank_ovl->player_bell - bank_ovl->now_bell;
                }

                bank_ovl->bank_bell -= keta;
                bank_ovl->now_bell += keta;
            }

            mBN_now_bell_2_bell(bank_ovl);
            sAdo_SysTrgStart(0x426);
        }
    }
}

static void mBN_move_End(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_End_proc)(submenu, menu);
}

static void mBN_bank_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[5] = {
        &mBN_move_Move, &mBN_move_Play, (mSM_MOVE_PROC)&none_proc1, (mSM_MOVE_PROC)&none_proc1, &mBN_move_End,
    };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_BANK];

    (*menu->pre_move_func)(submenu);
    (*ovl_move_proc[menu->proc_status])(submenu, menu);
}

extern Gfx tyo_win_mode[];
extern Gfx tyo_win_model[];
extern Gfx tyo_win_moji2T_model[];
extern Gfx tyo_win_moji3T_model[];

static void mBN_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    GRAPH* g = game->graph;
    mBN_Ovl_c* bank_ovl = submenu->overlay->bank_ovl;
    Gfx* gfx;
    u8 s;
    u8 t;

    Matrix_translate(menu->position[0] * 16.0f, menu->position[1] * 16.0f, 140.0f, MTX_LOAD);
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_MULT);

    OPEN_DISP(g);
    gfx = NOW_POLY_OPA_DISP;

    gSPDisplayList(gfx++, tyo_win_mode);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    s = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    t = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gDPSetTileSize_Dolphin(gfx++, 0, s, t, 32, 32);
    gSPDisplayList(gfx++, tyo_win_model);

    if (bank_ovl->now_bell <= bank_ovl->player_bell) {
        gDPSetPrimColor(gfx++, 0, 255, 165, 50, 50, 255);
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gfx++, 0, 255, 100, 80, 80, 255);
        gDPSetEnvColor(gfx++, 165, 155, 155, 255);
    }

    gSPDisplayList(gfx++, tyo_win_moji2T_model);

    if (bank_ovl->now_bell >= bank_ovl->player_bell) {
        gDPSetPrimColor(gfx++, 0, 255, 20, 205, 20, 255);
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gfx++, 0, 255, 70, 95, 70, 255);
        gDPSetEnvColor(gfx++, 155, 165, 155, 255);
    }

    gSPDisplayList(gfx++, tyo_win_moji3T_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(g);
}

static void mBN_set_num_str(f32 x, f32 y, GAME* game, u32 num, f32 scale, rgba_t* color) {
    u8 str[11];
    f32 width;

    mFont_UnintToString(str, 11, num, 9, FALSE, FALSE, TRUE);
    width = mFont_GetStringWidth(str, 11, TRUE);
    x -= scale * width;

    mFont_SetLineStrings(game, str, 11, x, y, color->r, color->g, color->b, 255, FALSE, TRUE, scale, scale,
                         mFont_MODE_POLY);
}

static void mBN_set_character_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    static u8 kingaku_str[] = { CHAR_Y, CHAR_o, CHAR_u, CHAR_r, CHAR_SPACE, CHAR_A,
                                CHAR_c, CHAR_c, CHAR_o, CHAR_u, CHAR_n,     CHAR_t };
    static rgba_t normal_col = { 0, 50, 255, 255 };
    static rgba_t select_col = { 195, 20, 20, 255 };
    static rgba_t bank_bell_col = { 170, 60, 145, 255 };
    static rgba_t now_bell_col = { 115, 50, 215, 255 };

    mBN_Ovl_c* bank_ovl;
    int cursol;
    f32 width;
    f32 digit_x;
    int i;
    u8 str[7];
    f32 pos_x = menu->position[0];
    f32 pos_y = menu->position[1];

    bank_ovl = submenu->overlay->bank_ovl;

    (*submenu->overlay->set_char_matrix_proc)(game->graph);
    mFont_SetLineStrings(game, kingaku_str, sizeof(kingaku_str), 145.0f + pos_x, 65.0f - pos_y, 255, 255, 255, 255,
                         FALSE, TRUE, 0.875f, 0.875f, mFont_MODE_POLY);

    mBN_set_num_str(211.0f + pos_x, 157.0f - pos_y, game, bank_ovl->bank_bell, 0.875f, &bank_bell_col);
    mBN_set_num_str(211.0f + pos_x, 98.0f - pos_y, game, bank_ovl->now_bell, 0.875f, &now_bell_col);

    cursol = bank_ovl->cursol;

    if (cursol >= 3) {
        cursol++;
    }

    mFont_UnintToString(str, 7, bank_ovl->bell, 6, FALSE, TRUE, TRUE);
    width = mFont_GetStringWidth(str, 7, TRUE);

    /* Draw each digit one by one */
    digit_x = 211.0f + (pos_x - width);
    for (i = 0; i < 7; i++) {
        rgba_t* color = cursol == i ? &select_col : &normal_col;

        mFont_SetLineStrings(game, str + i, 1, digit_x, 124.0f - pos_y, color->r, color->g, color->b, 255, FALSE, TRUE,
                             1.0f, 1.0f, mFont_MODE_POLY);

        width = mFont_GetStringWidth(str + i, 1, TRUE);
        digit_x += width;
    }

    {
        rgba_t* color = bank_ovl->cursol < mBN_CUSROL_OK ? &normal_col : &select_col;

        mFont_SetLineStrings(game, mBN_ok_str, sizeof(mBN_ok_str), 208.0f + pos_x, 140.0f - pos_y, color->r, color->g,
                             color->b, 255, FALSE, TRUE, 0.875f, 0.875f, mFont_MODE_POLY);
    }
}

static void mBN_bank_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[mSM_OVL_BANK];

    (*menu->pre_draw_func)(submenu, game);
    mBN_set_frame_dl(submenu, game, menu);
    mBN_set_character_dl(submenu, game, menu);
}

extern void mBN_bank_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mBN_bank_ovl_move;
    overlay->menu_control.menu_draw_func = &mBN_bank_ovl_draw;
}

static void mBN_bank_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mBN_Ovl_c* bank_ovl = overlay->bank_ovl;
    int i;

    overlay->menu_control.animation_flag = FALSE;
    overlay->menu_info[mSM_OVL_BANK].proc_status = 0;
    overlay->menu_info[mSM_OVL_BANK].next_proc_status = 1;
    overlay->menu_info[mSM_OVL_BANK].move_drt = 5;

    bank_ovl->now_bell = Common_Get(now_private)->inventory.wallet;
    bank_ovl->now_bell += mBN_total_item_bell();
    bank_ovl->player_bell = bank_ovl->now_bell;

    mBN_now_bell_2_bell(bank_ovl);
    bank_ovl->player_max_bell = mPr_WALLET_MAX;

    for (i = 0; i < MONEY_NUM; i++) {
        int sack_sum = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        bank_ovl->player_max_bell += sack_sum * aNSM_sack_amount[3];
    }

    {
        int sack_sum = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), EMPTY_NO, mPr_ITEM_COND_NORMAL);

        bank_ovl->player_max_bell += sack_sum * aNSM_sack_amount[3];
    }
    bank_ovl->bank_bell = Common_Get(now_private)->bank_account;
    bank_ovl->cursol = 0;
}

static mBN_Ovl_c bn_ovl_data;

extern void mBN_bank_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->bank_ovl == NULL) {
        mem_clear((u8*)&bn_ovl_data, sizeof(mBN_Ovl_c), 0);
        overlay->bank_ovl = &bn_ovl_data;
    }

    mBN_bank_ovl_init(submenu);
    mBN_bank_ovl_set_proc(submenu);
}

extern void mBN_bank_ovl_destruct(Submenu* submenu) {
    submenu->overlay->bank_ovl = NULL;
}
