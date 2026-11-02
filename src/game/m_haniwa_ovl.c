#include "m_haniwa_ovl.h"

#include "m_submenu_ovl.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_tag_ovl.h"
#include "m_player_lib.h"
#include "m_inventory_ovl.h"
#include "m_hand_ovl.h"
#include "m_font.h"
#include "m_haniwaPortrait_ovl.h"

static mHW_Ovl_c haniwa_ovl_data;

static void mHW_set_interrupt_message(Submenu* submenu, mTG_tag_c* tag, int msg_idx) {
    mHW_Ovl_c* haniwa_ovl = submenu->overlay->haniwa_ovl;

    haniwa_ovl->msg_interrupt_idx = msg_idx;
    haniwa_ovl->table_idx = tag->table;
    haniwa_ovl->sub_idx = tag->tag_col;
    haniwa_ovl->msg_time = 120;
}

static void mHW_set_price(Submenu* submenu, u8** str) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HANIWA];
    u8 price_str[6];
    u32 price = Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data;
    int len;
    int found;

    submenu->overlay->haniwa_ovl->msg_price = price;
    mFont_UnintToString(price_str, sizeof(price_str), price, sizeof(price_str) - 1, TRUE, FALSE, TRUE);
    len = mMl_strlen2(&found, price_str, sizeof(price_str), CHAR_SPACE);
    if (found == TRUE) {
        len--;
    }
    mem_copy(*str, price_str, len);
    (*str)[len] = CHAR_SPACE;
    *str += len + 1;
}

typedef struct {
    u8* str;
    int len;
} mHW_msg_c;

static void mHW_make_cond_message(Submenu* submenu, int msg_idx) {
    static u8 mes_ikaga[15] = "How can I help?";
    static u8 mes_dono[11] = "Choose one.";
    static u8 mes_dono2[15] = "May I help you?";
    static u8 mes_oikura[9] = "How much?";
    static u8 mes_kasiko[7] = "Got it!";
    static u8 mes_dorewo[11] = "Choose one.";
    static u8 mes_mou[20] = "You don't have room.";
    static u8 mes_okane[22] = "You can't afford that.";
    static u8 mes_maido[20] = "Thank you very much!";
    static u8 mes_tada[11] = "That's free";
    static u8 mes_tada2[9] = "Give Away";
    static u8 mes_mise[20] = "That's display only.";
    static u8 mes_beru[5] = "It's\xD3";
    static u8 mes_beru2[5] = "Bells";

    static mHW_msg_c mes_data_tbl[] = {
        // clang-format off
        {mes_ikaga, sizeof(mes_ikaga)},
        {mes_dono, sizeof(mes_dono)},
        {mes_dono2, sizeof(mes_dono2)},
        {mes_oikura, sizeof(mes_oikura)},
        {mes_kasiko, sizeof(mes_kasiko)},
        {mes_dorewo, sizeof(mes_dorewo)},
        {mes_mou, sizeof(mes_mou)},
        {mes_okane, sizeof(mes_okane)},
        {mes_maido, sizeof(mes_maido)},
        {mes_tada, sizeof(mes_tada)},
        {mes_tada2, sizeof(mes_tada2)},
        {mes_mise, sizeof(mes_mise)},
        {mes_beru2, sizeof(mes_beru2)},
        // clang-format on
    };

    static mHW_msg_c mes_beru_data = { mes_beru, sizeof(mes_beru) };

    mHW_msg_c* msg_p = &mes_data_tbl[msg_idx];
    u8* str_p = submenu->overlay->haniwa_ovl->msg;

    mem_clear(str_p, mHW_OVL_MSG_SIZE, CHAR_SPACE);
    if (msg_idx == mHW_MSG_BERU2) {
        mem_copy(str_p, mes_beru_data.str, mes_beru_data.len);
        str_p += mes_beru_data.len;
        mHW_set_price(submenu, &str_p);
    }

    mem_copy(str_p, msg_p->str, msg_p->len);
}

static int mHW_make_message_interrupt(Submenu* submenu) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    mHW_Ovl_c* haniwa_ovl = submenu->overlay->haniwa_ovl;
    int timer = haniwa_ovl->msg_time;
    int msg_idx = haniwa_ovl->msg_interrupt_idx;

    if (timer - 1 < 0) {
        haniwa_ovl->msg_interrupt_idx = -1;
    }

    haniwa_ovl->msg_time = timer - 1;
    if (msg_idx != mHW_MSG_DOREWO) {
        if (tag_ovl->sel_tag_idx == 0) {
            if (tag->table != haniwa_ovl->table_idx || tag->tag_col != haniwa_ovl->sub_idx) {
                haniwa_ovl->msg_interrupt_idx = -1;
            }
            
        } else if (tag_ovl->ret_tag_idx == tag_ovl->sel_tag_idx) {
            haniwa_ovl->msg_interrupt_idx = -1;
        }
    } else {
        if (tag_ovl->sel_tag_idx != -1) {
            if (tag->table != haniwa_ovl->table_idx || tag->tag_col != haniwa_ovl->sub_idx) {
                haniwa_ovl->msg_interrupt_idx = -1;
            }
        }
    }

    return msg_idx;
}

static int mHW_make_message_normal(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int msg_idx = submenu->overlay->haniwa_ovl->msg_idx;

    switch (tag->type) {
        case mTG_TYPE_NONE:
        case mTG_TYPE_HANIWA_PUT_ITEM:
            if (tag->table == mTG_TABLE_HANIWA) {
                Haniwa_Item_c* item = &Save_Get(homes[menu_info->data1]).haniwa.items[tag_ovl->tags[0].tag_col];
                
                if (item->item != EMPTY_NO) {
                    switch (item->exchange_type) {
                        case mHm_HANIWA_TRADE_0:
                            if (menu_info->data0 == 0) {
                                msg_idx = mHW_MSG_TADA;
                            } else {
                                msg_idx = mHW_MSG_TADA2;
                            }
                            break;
                        case mHm_HANIWA_TRADE_1:
                            msg_idx = mHW_MSG_MISE;
                            break;
                        case mHm_HANIWA_TRADE_2:
                            msg_idx = mHW_MSG_BERU2;
                            break;
                        default:
                            msg_idx = mHW_MSG_MISE;
                            break;
                    }
                } else {
                    if (menu_info->data0 == 0) {
                        msg_idx = mHW_MSG_IKAGA;
                    } else {
                        msg_idx = mHW_MSG_DONO2;
                    }
                }
            } else {
                msg_idx = mHW_MSG_IKAGA;
            }
            break;
        case mTG_TYPE_HANIWA_ITEM:
        case mTG_TYPE_CATCH_ITEM:
            msg_idx = mHW_MSG_DONO;
            break;
        case mTG_TYPE_HANIWA_PRICE:
            msg_idx = mHW_MSG_OIKURA;
            break;
    }

    return msg_idx;
}

static void mHW_make_message(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    mHW_Ovl_c* haniwa_ovl = submenu->overlay->haniwa_ovl;
    int msg_idx;
    int msg_idx_bak;
    int ctr;

    ctr = haniwa_ovl->msg_counter;
    ctr++;
    if (ctr > mHW_OVL_MSG_SIZE) {
        ctr = mHW_OVL_MSG_SIZE;
    }

    haniwa_ovl->msg_counter = ctr;
    msg_idx_bak = haniwa_ovl->msg_idx;
    if (haniwa_ovl->msg_interrupt_idx != -1) {
        msg_idx = mHW_make_message_interrupt(submenu);
    } else {
        msg_idx = mHW_make_message_normal(submenu, menu_info);
    }

    if (msg_idx != msg_idx_bak || (msg_idx == mHW_MSG_BERU2 &&
        haniwa_ovl->msg_price != Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data)) {
        mHW_make_cond_message(submenu, msg_idx);
        haniwa_ovl->msg_idx = msg_idx;
        haniwa_ovl->msg_counter = 0;
    }
}

static void mHW_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mHW_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (!menu_info->open_flag) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_HANIWA, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
        menu_info->open_flag = TRUE;
    }
    
    submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
}

static void mHW_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mHW_haniwa_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mHW_move_Move,
        mHW_move_Play,
        (mSM_MOVE_PROC)none_proc1,
        (mSM_MOVE_PROC)none_proc1,
        mHW_move_End,
        // clang-format on
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HANIWA];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

#ifdef TARGET_PC
    if (submenu->overlay->haniwa_ovl == NULL) {
        return;
    }
#endif

    mHW_make_message(submenu, menu_info);

    switch (menu_info->proc_status) {
        case mSM_OVL_PROC_PLAY:
            submenu->overlay->hanwiaPortrait_ovl->haniwaPortrait_shape_move_proc(submenu);
            submenu->overlay->menu_control.animation_flag = TRUE;
            break;
        case mSM_OVL_PROC_MOVE:
            submenu->overlay->menu_control.animation_flag = FALSE;
            break;
    }
}

extern Gfx hni_win_mode[];
extern Gfx hni_win_modelT[];

static void mHW_set_frame_dl(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y) {
    int tex_x;
    int tex_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, -809.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, hni_win_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPTileSync(POLY_OPA_DISP++);
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 8;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 8;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (u8)tex_x, (u8)tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, hni_win_modelT);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx inv_item_mode[];

static void mHW_set_item(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 pos_x, f32 pos_y) {
    Haniwa_Item_c* item = Save_Get(homes[menu_info->data1]).haniwa.items;
    f32 pos[2];
    int i;

    OPEN_POLY_OPA_DISP(graph);
    
    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);
    
    CLOSE_POLY_OPA_DISP(graph);

    for (i = 0; i < HANIWA_ITEM_HOLD_NUM; i++) {
        if (item->item != EMPTY_NO) {
            submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, mTG_TABLE_HANIWA, i);
            submenu->overlay->draw_item_proc(graph, pos_x + pos[0], pos_y + pos[1], 1.0f, item->item, FALSE, TRUE, 0, FALSE, FALSE);
        }

        item++;
    }
}

static void mHW_set_message(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    GRAPH* graph = game->graph;
    mHW_Ovl_c* haniwa_ovl = submenu->overlay->haniwa_ovl;

    submenu->overlay->set_char_matrix_proc(graph);
    // clang-format off
    mFont_SetLineStrings(
        game,
        haniwa_ovl->msg, haniwa_ovl->msg_counter,
        160.0f + (26.0f + (menu_info->position[0] - 89.0f)), 120.0f - ((97.0f + menu_info->position[1]) - 11.0f),
        45, 50, 0, 255,
        FALSE, TRUE,
        0.875f, 0.875f,
        mFont_MODE_POLY
    );
    // clang-format on
}

static void mHW_set_dl(mSM_MenuInfo_c* menu_info, Submenu* submenu, GAME* game) {
    GRAPH* graph = game->graph;
    f32 pos_x = menu_info->position[0];
    f32 pos_y = menu_info->position[1];

    mHW_set_frame_dl(submenu, graph, pos_x, pos_y);
    mHW_set_item(submenu, graph, menu_info, pos_x, pos_y);
    submenu->overlay->hanwiaPortrait_ovl->set_haniwaPortrait_proc(submenu, menu_info, graph, game, 39.0f + pos_x, 19.0f - pos_y);
    mHW_set_message(submenu, game, menu_info);
    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_HANIWA);
}

static void mHW_haniwa_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HANIWA];

    menu_info->pre_draw_func(submenu, game);
    mHW_set_dl(menu_info, submenu, game);
}

extern void mHW_haniwa_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HANIWA];

    ctrl->menu_move_func = mHW_haniwa_ovl_move;
    ctrl->menu_draw_func = mHW_haniwa_ovl_draw;
    if (submenu->overlay->hand_ovl != NULL) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mHW_haniwa_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HANIWA];
    mHW_Ovl_c* haniwa_ovl = submenu->overlay->haniwa_ovl;

    submenu->overlay->menu_control.animation_flag = FALSE;

    switch (menu_info->data0) {
        case 0:
            haniwa_ovl->msg_interrupt_idx = -1;
            haniwa_ovl->msg_time = 0;
            break;
        case 1:
            haniwa_ovl->msg_interrupt_idx = mHW_MSG_DOREWO;
            haniwa_ovl->table_idx = mTG_TABLE_HANIWA;
            haniwa_ovl->sub_idx = 0;
            haniwa_ovl->msg_time = 120;
            break;
    }

    mem_clear(haniwa_ovl->msg, mHW_OVL_MSG_SIZE, CHAR_SPACE);
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mSM_MOVE_IN_LEFT;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
}

extern void mHW_haniwa_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mHW_Ovl_c* haniwa_ovl = ovl->haniwa_ovl;

    if (haniwa_ovl == NULL) {
        mem_clear((u8*)&haniwa_ovl_data, sizeof(haniwa_ovl_data), 0);
        ovl->haniwa_ovl = &haniwa_ovl_data;
        submenu->overlay->haniwa_ovl->set_interrupt_message_proc = mHW_set_interrupt_message;
        haniwa_ovl_data.msg_idx = -1;
        haniwa_ovl_data.table_idx = mTG_TABLE_ITEM;
        haniwa_ovl_data.sub_idx = 0;
    }

    mHW_haniwa_ovl_init(submenu);
    mHW_haniwa_ovl_set_proc(submenu);
}

extern void mHW_haniwa_ovl_destruct(Submenu* submenu) {
    submenu->overlay->haniwa_ovl = NULL;
}
