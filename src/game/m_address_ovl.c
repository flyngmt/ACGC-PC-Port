#include "m_address_ovl.h"

#include "m_common_data.h"
#include "m_board_ovl.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "sys_matrix.h"

static mAD_Ovl_c adrs_ovl_data;

static Vtx lat_atena_v[48] = {
    // Page 0
    { {{0xFFE1, 0xFFF3, 0x0000}, 0x0001, {0x0000, 0x0200}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0xFFE1, 0xFFE2, 0x0000}, 0x0001, {0x0000, 0x0400}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0x002D, 0xFFF3, 0x0000}, 0x0001, {0x0800, 0x0200}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0x002D, 0xFFE2, 0x0000}, 0x0001, {0x0800, 0x0400}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0xFFE1, 0xFFFD, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0xFFFD, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0x000E, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFE1, 0x000E, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFDE, 0x0011, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0x0000, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0011, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0000, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0xFFF6, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFF6, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x64, 0x64, 0x64, 0x64}} },
    { {{0xFFDE, 0xFFE5, 0x0000}, 0x0001, {0x0000, 0x0400}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFE5, 0x0000}, 0x0001, {0x0800, 0x0400}, {0x64, 0x64, 0x64, 0x64}} },
    // Page 1
    { {{0xFFE1, 0xFFF3, 0x0000}, 0x0001, {0x0000, 0x0200}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0xFFE1, 0xFFE2, 0x0000}, 0x0001, {0x0000, 0x0400}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0x002D, 0xFFF3, 0x0000}, 0x0001, {0x0800, 0x0200}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0x002D, 0xFFE2, 0x0000}, 0x0001, {0x0800, 0x0400}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0xFFE1, 0xFFFD, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0xFFFD, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0x000E, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFE1, 0x000E, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFDE, 0x0011, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0x0000, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0011, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0000, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0xFFF6, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFF6, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x64, 0x64, 0x64, 0x64}} },
    { {{0xFFDE, 0xFFE5, 0x0000}, 0x0001, {0x0000, 0x0400}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFE5, 0x0000}, 0x0001, {0x0800, 0x0400}, {0x64, 0x64, 0x64, 0x64}} },
    // Page 2
    { {{0xFFE1, 0xFFF3, 0x0000}, 0x0001, {0x0000, 0x0200}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0xFFE1, 0xFFE2, 0x0000}, 0x0001, {0x0000, 0x0400}, {0xCA, 0xCA, 0xCA, 0xCA}} },
    { {{0x002D, 0xFFF3, 0x0000}, 0x0001, {0x0800, 0x0200}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0x002D, 0xFFE2, 0x0000}, 0x0001, {0x0800, 0x0400}, {0xFF, 0xFF, 0xFF, 0xFF}} },
    { {{0xFFE1, 0xFFFD, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0xFFFD, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0x002D, 0x000E, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFE1, 0x000E, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x98, 0x98, 0x98, 0x98}} },
    { {{0xFFDE, 0x0011, 0x0000}, 0x0001, {0x0000, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0x0000, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0011, 0x0000}, 0x0001, {0x0800, 0x0000}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0x002A, 0x0000, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x00, 0x00, 0x00, 0x00}} },
    { {{0xFFDE, 0xFFF6, 0x0000}, 0x0001, {0x0000, 0x0200}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFF6, 0x0000}, 0x0001, {0x0800, 0x0200}, {0x64, 0x64, 0x64, 0x64}} },
    { {{0xFFDE, 0xFFE5, 0x0000}, 0x0001, {0x0000, 0x0400}, {0x32, 0x32, 0x32, 0x32}} },
    { {{0x002A, 0xFFE5, 0x0000}, 0x0001, {0x0800, 0x0400}, {0x64, 0x64, 0x64, 0x64}} },
};

static u8 l_shop_name_str[ANIMAL_NAME_LEN] = "\x0F\x16\x06\x10  \0\0"; // たぬきち  \0\0 (Tanukichi, Tom Nook)
static u8 mAD_title_str[20] = "Choose an addressee.";
static u8 mAD_title_str2[27] = "Your address book is empty!";

static void mAD_cancel_edit(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* prev_menu = &submenu->overlay->menu_info[menu_info->pre_menu_type];

    if (prev_menu->proc_status == mSM_OVL_PROC_PLAY) {
        submenu->overlay->return_func_proc(submenu, menu_info);
        submenu->overlay->move_chg_base_proc(prev_menu, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    }
}

static int mAD_get_nextIdx(mAD_Ovl_c* adrs_ovl, int idx, int add) {
    int next_idx = idx;
    
    if (adrs_ovl->page_count <= 1) {
        next_idx = -1;
    } else {
        int flags = adrs_ovl->page_bitfield;
        int i;

        for (i = 0; i < 2; i++) {
            next_idx += add;
            if (next_idx == 3) {
                next_idx = 0;
            } else if (next_idx < 0) {
                next_idx = 2;
            }

            if ((flags >> next_idx) & 1) {
                break;
            }
        }
    }

    return next_idx;
}

static void mAD_pile_init(mAD_Ovl_c* adrs_ovl, f32* pile, int idx) {
    if (adrs_ovl->page_count == 2) {
        if (idx == 0) {
            pile[0] = 0.0f;
            pile[1] = 5.0f;
            pile[2] = 0.0f;
        } else {
            pile[0] = 5.0f;
            pile[1] = 0.0f;
            pile[2] = 5.0f;
        }
    } else if (adrs_ovl->page_count == 3) {
        pile[idx] = 0.0f;
        pile[(idx + 1) % mAD_PAGE_NUM] = 5.0f;
        pile[(idx + 2) % mAD_PAGE_NUM] = 10.0f;
    } else {
        pile[0] = 0.0f;
        pile[1] = 0.0f;
        pile[2] = 0.0f;
    }
}

static void mAD_move_between(Submenu* submenu, int add) {
    int idx;
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;

    idx = mAD_get_nextIdx(adrs_ovl, adrs_ovl->curIdx, add);
    if (idx != -1) {
        adrs_ovl->proc_idx = mAD_PROC_TURN_PAGE;
        if (add == -1) {
            adrs_ovl->speed_x = 0.5f;
        } else {
            adrs_ovl->speed_x = -0.5f;
        }

        adrs_ovl->nextIdx = idx;
        mAD_pile_init(adrs_ovl, adrs_ovl->goal_pile, idx);
        sAdo_SysTrgStart(NA_SE_41C);
    }
}

static void mAD_move_cursol(Submenu* submenu) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;

    if ((trigger & BUTTON_CLEFT)) {
        mAD_move_between(submenu, -1);
    } else if ((trigger & BUTTON_CDOWN)) {
        if (adrs_ovl->selected_entry < adrs_ovl->page_entry_count[adrs_ovl->curIdx] - 1) {
            adrs_ovl->selected_entry++;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else {
            mAD_move_between(submenu, 1);
        }
    } else if ((trigger & BUTTON_CUP)) {
        if (adrs_ovl->selected_entry != 0) {
            adrs_ovl->selected_entry--;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else {
            mAD_move_between(submenu, -1);
        }
    } else if ((trigger & BUTTON_CRIGHT)) {
        mAD_move_between(submenu, 1);
    }
}

static void mAD_make_player_address(mAD_Ovl_c* adrs_ovl) {
    int player_no = Common_Get(player_no);
    Mail_nm_c* name_p = adrs_ovl->player_mail_name;
    u8* count_p = &adrs_ovl->page_entry_count[mAD_PAGE_PLAYER];
    PersonalID_c* pid;
    int i;

    *count_p = 0;
    for (i = 0; i < PLAYER_NUM; i++) {
        if (i != player_no) {
            pid = &Save_Get(private_data[i]).player_ID;

            if (mPr_NullCheckPersonalID(pid) == FALSE) {
                mPr_CopyPersonalID(&name_p->personalID, pid);
                name_p->type = mMl_NAME_TYPE_PLAYER;
                name_p++;
                (*count_p)++;
            }
        }
    }

    if (mPr_CheckMuseumAddress(Now_Private)) {
        mMsm_GetMuseumMailName(name_p);
        (*count_p)++;
        adrs_ovl->show_museum_address = TRUE;
    } else {
        adrs_ovl->show_museum_address = FALSE;
    }
}

static void mAD_make_npc_address(mAD_Ovl_c* adrs_ovl) {
    Animal_c* animal_p = Save_Get(animals);
    Mail_nm_c* name_p = adrs_ovl->animal_mail_name;
    PersonalID_c* pid = &Now_Private->player_ID;
    int i;
    int count;

    count = 0;
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal_p->id) == FALSE &&
            mNpc_GetAnimalMemoryIdx(pid, animal_p->memories, ANIMAL_MEMORY_NUM) != -1) {
            mMl_set_mail_name_npcinfo(name_p, &animal_p->id);
            name_p++;
            count++;
        }

        animal_p++;
    }

    if (count < mAD_PAGE_MAX_ENTRIES) {
        adrs_ovl->page_entry_count[mAD_PAGE_NPC0] = count;
        adrs_ovl->page_entry_count[mAD_PAGE_NPC1] = 0;
    } else {
        adrs_ovl->page_entry_count[mAD_PAGE_NPC0] = mAD_PAGE_MAX_ENTRIES;
        adrs_ovl->page_entry_count[mAD_PAGE_NPC1] = count - mAD_PAGE_MAX_ENTRIES;
    }
}

static void mAD_refuse_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (submenu->overlay->menu_control.trigger & (BUTTON_A | BUTTON_B | BUTTON_START)) {
        mAD_cancel_edit(submenu, menu_info);
    }
}

static void mAD_start_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;

    if (trigger & BUTTON_B) {
        mAD_cancel_edit(submenu, menu_info);
    } else if (trigger & (BUTTON_A | BUTTON_START)) {
        adrs_ovl->proc_idx = mAD_PROC_SELECT;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
        mAD_pile_init(adrs_ovl, adrs_ovl->pile, adrs_ovl->curIdx);
        adrs_ovl->selected_entry = 0;
    }
}

static void mAD_select_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mBD_Ovl_c* board_ovl;
    mAD_Ovl_c* adrs_ovl;
    u32 trigger;
    Mail_nm_c* name_p;

    adrs_ovl = submenu->overlay->address_ovl;
    board_ovl = submenu->overlay->board_ovl;
    trigger = submenu->overlay->menu_control.trigger;
    if (trigger & BUTTON_B) {
        if (board_ovl->first == TRUE) {
            mAD_cancel_edit(submenu, menu_info);
        } else {
            board_ovl->header_pos = 0;
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
            sAdo_SysTrgStart(MONO(NA_SE_3));
        }
    } else if (trigger & (BUTTON_A | BUTTON_START)) {
        if (adrs_ovl->curIdx == 0) {
            name_p = &adrs_ovl->player_mail_name[adrs_ovl->selected_entry];
        } else if (adrs_ovl->curIdx == 2) {
            name_p = &adrs_ovl->animal_mail_name[mAD_PAGE_MAX_ENTRIES + adrs_ovl->selected_entry];
        } else {
            name_p = &adrs_ovl->animal_mail_name[adrs_ovl->selected_entry];
        }

        mMl_copy_header_name(&board_ovl->mail.header.recipient, name_p);
        board_ovl->header_name_len = mMl_strlen(name_p->personalID.player_name, PLAYER_NAME_LEN, CHAR_SPACE);
        board_ovl->header_pos = 2;
        menu_info->proc_status = mSM_OVL_PROC_WAIT;

        if (submenu->overlay->board_ovl->first == TRUE) {
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_BOARD, MAIL_HEADER_BASE_LEN, menu_info->data2, menu_info->data3);
            submenu->overlay->board_ovl->first = FALSE;
        }

        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else {
        mAD_move_cursol(submenu);

        if (submenu->overlay->board_ovl->first == FALSE) {
            if (trigger & BUTTON_DLEFT) {
                sAdo_SysTrgStart(NA_SE_35);
                board_ovl->header_pos = 0;
                menu_info->proc_status = mSM_OVL_PROC_WAIT;
            } else if (trigger & BUTTON_DRIGHT) {
                sAdo_SysTrgStart(NA_SE_35);
                board_ovl->header_pos = 2;
                menu_info->proc_status = mSM_OVL_PROC_WAIT;
            } else if (trigger & BUTTON_DDOWN) {
                adrs_ovl->editor_move_down = TRUE;
                sAdo_SysTrgStart(NA_SE_35);
                board_ovl->header_pos = 0;
                menu_info->proc_status = mSM_OVL_PROC_WAIT;
            }
        }
    }
}

static void mAD_turn_page_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    u8 idx;
    int i;
    f32 pos;
#ifdef TARGET_PC
    f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;
#endif

    pos = fabsf(adrs_ovl->pos_x);
    if (pos < 14.0f) {
#ifdef TARGET_PC
        adrs_ovl->speed_x *= DTCONV_GRAPH(sqrtf(2.0f), gamePT->graph);
#else
        adrs_ovl->speed_x *= sqrtf(2.0f);
#endif
    } else if (pos > 30.0f) {
#ifdef TARGET_PC
        adrs_ovl->speed_x *= DTCONV_GRAPH(sqrtf(0.5f), gamePT->graph);
#else
        adrs_ovl->speed_x *= sqrtf(0.5f);
#endif

        if (fabsf(adrs_ovl->speed_x) < 0.25f) {
            idx = adrs_ovl->curIdx;
            adrs_ovl->curIdx = adrs_ovl->nextIdx;
            adrs_ovl->nextIdx = idx;
            adrs_ovl->proc_idx = mAD_PROC_TURN_PAGE2;

            if (adrs_ovl->speed_x < 0.0f) {
                adrs_ovl->selected_entry = 0;
            } else {
                adrs_ovl->selected_entry = adrs_ovl->page_entry_count[adrs_ovl->curIdx] - 1;
            }

            mAD_pile_init(adrs_ovl, adrs_ovl->pile, adrs_ovl->curIdx);
            adrs_ovl->pos_x *= -1.0f;
            return;
        }
    }

#ifdef TARGET_PC
    adrs_ovl->pos_x += adrs_ovl->speed_x * dt;
#else
    adrs_ovl->pos_x += adrs_ovl->speed_x;
#endif
    for (i = 0; i < mAD_PAGE_NUM; i++) {
        chase_f(&adrs_ovl->pile[i], adrs_ovl->goal_pile[i], 0.6f * (f32)gamePT->graph->dt_num_60fps_frames);
    }
}

static void mAD_turn_page2_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    f32 pos;
#ifdef TARGET_PC
    f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;
#endif

    pos = fabsf(adrs_ovl->pos_x);
    if (pos > 30.0f) {
#ifdef TARGET_PC
        adrs_ovl->speed_x *= DTCONV_GRAPH(sqrtf(2.0f), gamePT->graph);
#else
        adrs_ovl->speed_x *= sqrtf(2.0f);
#endif
    } else if (pos < 14.0f) {
#ifdef TARGET_PC
        adrs_ovl->speed_x *= DTCONV_GRAPH(sqrtf(0.5f), gamePT->graph);
#else
        adrs_ovl->speed_x *= sqrtf(0.5f);
#endif
    }

#ifdef TARGET_PC
    adrs_ovl->pos_x += adrs_ovl->speed_x * dt;
#else
    adrs_ovl->pos_x += adrs_ovl->speed_x;
#endif
    if (adrs_ovl->pos_x * adrs_ovl->speed_x > 0.0f) {
        adrs_ovl->pos_x = 0.0f;
        adrs_ovl->speed_x = 0.0f;
        adrs_ovl->proc_idx = mAD_PROC_SELECT;
    }
}

typedef void (*mAD_PLAY_PROC)(Submenu* submenu, mSM_MenuInfo_c* menu_info);

static void mAD_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mAD_PLAY_PROC play_process[] = {
        // clang-format off
        mAD_refuse_proc,
        mAD_start_proc,
        mAD_select_proc,
        mAD_turn_page_proc,
        mAD_turn_page2_proc,
        // clang-format on
    };

    (*play_process[submenu->overlay->address_ovl->proc_idx])(submenu, menu_info);
}

static void mAD_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;

    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    if (board_ovl->header_pos == 1) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
        menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
        adrs_ovl->proc_idx = mAD_PROC_SELECT;
        adrs_ovl->selected_entry = 0;

        if (adrs_ovl->page_entry_count[mAD_PAGE_PLAYER] != 0) {
            adrs_ovl->curIdx = mAD_PAGE_PLAYER;
        } else if (adrs_ovl->page_entry_count[mAD_PAGE_NPC0] != 0) {
            adrs_ovl->curIdx = mAD_PAGE_NPC0;
        }

        mAD_pile_init(adrs_ovl, adrs_ovl->pile, adrs_ovl->curIdx);
    }
}

static void mAD_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mAD_address_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        (mSM_MOVE_PROC)none_proc1,
        mAD_move_Play,
        mAD_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mAD_move_End,
        // clang-format on
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ADDRESS];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

static void mAD_address_draw_init(Submenu* submenu) {
    Vtx* vtx_p;
    int i;
    int count;
    int ofs;

    for (i = 0; i < mAD_PAGE_NUM; i++) {
        count = submenu->overlay->address_ovl->page_entry_count[i] - 1;
        
        if (count >= 0) {
            vtx_p = &lat_atena_v[i * 16];

            if (i == mAD_PAGE_PLAYER && submenu->overlay->address_ovl->show_museum_address && count > 0) {
                count++;
            }

            // ofs = (int)(count * 12.857142f);
            ofs = (int)(count * (90.0f / (mAD_PAGE_MAX_ENTRIES - 1)));
            vtx_p[12].v.ob[1] = vtx_p[9].v.ob[1] - ofs;
            vtx_p[13].v.ob[1] = vtx_p[11].v.ob[1] - ofs;
            vtx_p[14].v.ob[1] = vtx_p[12].v.ob[1] - 17;
            vtx_p[15].v.ob[1] = vtx_p[13].v.ob[1] - 17;
            
            vtx_p[0].v.ob[1] = vtx_p[4].v.ob[1] - ofs;
            vtx_p[2].v.ob[1] = vtx_p[5].v.ob[1] - ofs;
            vtx_p[1].v.ob[1] = vtx_p[0].v.ob[1] - 17;
            vtx_p[3].v.ob[1] = vtx_p[2].v.ob[1] - 17;
        }
    }
}

extern Gfx lat_mes_winT_model[];

static void mAD_set_first_tag(Submenu* submenu, GAME* game, GRAPH* graph, f32 pos_x, f32 pos_y) {
    static u8* title_table[] = { mAD_title_str, mAD_title_str2 };
    static int title_length[] = { sizeof(mAD_title_str), sizeof(mAD_title_str2) };
    static f32 offset[][2] = { { -66.0f, 8.0f }, { -90.0f, 8.0f } };
    u8* title_p;
    int len;
    f32* ofs_p;
    int idx;

    idx = 0;
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, lat_mes_winT_model);

    CLOSE_POLY_OPA_DISP(graph);

    
    (*submenu->overlay->set_char_matrix_proc)(graph);
    if (submenu->overlay->address_ovl->proc_idx == mAD_PROC_REFUSE) {
        idx = 1;
    }

    title_p = title_table[idx];
    len = title_length[idx];
    mFont_SetLineStrings(game, title_p, len, 160.0f + (pos_x + offset[idx][0]), 120.0f - (pos_y + offset[idx][1]), 80, 80, 230, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_POLY);
}

extern Gfx lat_atena_model[];
extern Gfx lat_atena_winT_model[];

static void mAD_set_addressSel_tag_field(GRAPH* graph, f32 pos_x, f32 pos_y, int idx, int col_idx) {
    static rgba_t prim_color[2][3] = {
        // clang-format off
        { { 215, 225,  70, 255 }, { 205, 205,  80, 255 }, { 150, 150,  40, 255 } },
        { { 145, 255, 100, 255 }, { 115, 225,  80, 255 }, { 100, 190,  60, 255 } },
        // clang-format on
    };

    rgba_t* color_p = &prim_color[idx != 0][col_idx];

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, &lat_atena_v[idx * 16] + 8);
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, &lat_atena_v[idx * 16] + 0);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, lat_atena_model);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, color_p->r, color_p->g, color_p->b, 255);
    gSPDisplayList(POLY_OPA_DISP++, lat_atena_winT_model);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mAD_set_addressSel_tag_character(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y, int idx) {
    static rgba_t address_color[5] = {
        // clang-format off
        { 110, 115,  50, 255 },
        {   0, 135,  20, 255 },
        { 150, 120,  20, 255 },
        {  55,  30,  50, 255 },
        {  75,  60,   0, 255 },
        // clang-format on
    };

    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    int flag = idx == adrs_ovl->curIdx && adrs_ovl->proc_idx == mAD_PROC_SELECT;
    int count;
    Mail_nm_c* name_p;
    int i;
    f32 ofs_y;
    rgba_t* color_p;

    count = adrs_ovl->page_entry_count[idx];
    ofs_y = (11.0f + (count - 1) * (3.0f / (mAD_PAGE_MAX_ENTRIES - 1)));
    pos_x = 160.0f + ((pos_x + 7.0f) + -34.0f);
    pos_y = 120.0f - ((pos_y - ofs_y) + 17.0f);
    if (idx == mAD_PAGE_PLAYER) {
        name_p = adrs_ovl->player_mail_name;
    } else if (idx == mAD_PAGE_NPC0) {
        name_p = &adrs_ovl->animal_mail_name[0];
    } else {
        name_p = &adrs_ovl->animal_mail_name[mAD_PAGE_MAX_ENTRIES];
    }

    for (i = 0; i < count; i++, name_p++) {
        if (flag == TRUE && i == adrs_ovl->selected_entry) {
            if (idx == mAD_PAGE_PLAYER && adrs_ovl->show_museum_address && i == count - 1) {
                color_p = &address_color[4];
            } else {
                color_p = &address_color[3];
            }
        } else if (idx == mAD_PAGE_PLAYER) {
            if (adrs_ovl->show_museum_address && i == count - 1) {
                color_p = &address_color[2];
            } else {
                color_p = &address_color[0];
            }
        } else {
            color_p = &address_color[1];
        }

        mFont_SetLineStrings(
            // clang-format off
            game,
            name_p->personalID.player_name, PLAYER_NAME_LEN,
            pos_x, pos_y,
            color_p->r, color_p->g, color_p->b, 255,
            FALSE, TRUE,
            0.75f, 0.75f,
            mFont_MODE_POLY
            // clang--format on
        );

        if (adrs_ovl->show_museum_address && i == count - 2 && idx == mAD_PAGE_PLAYER) {
            pos_y += 24.0f;
        } else {
            pos_y += 12.0f;
        }
    }
}

static void mAD_set_addressSel_tag(Submenu* submenu, GRAPH* graph, GAME* game) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    int page_bitfield = adrs_ovl->page_bitfield;
    int idx = adrs_ovl->curIdx;
    f32 pos_x;
    f32 pos_y;
    f32 x;
    f32 y;
    int i;
    int col = 2;

    if (board_ovl != NULL) {
        pos_x = board_ovl->ofs_x + 4.0f;
        pos_y = board_ovl->ofs_y - 20.0f;
    } else {
        pos_x = 0.0f;
        pos_y = 0.0f;
    }

    for (i = 0; i < 3; i++) {
        if (idx == mAD_PAGE_PLAYER) {
            idx = mAD_PAGE_NPC1;
        } else {
            idx--;
        }

        if ((page_bitfield >> idx) & 1) {
            if (idx == adrs_ovl->curIdx) {
                x = pos_x + adrs_ovl->pos_x;
            } else if (idx == adrs_ovl->nextIdx) {
                x = pos_x - adrs_ovl->pos_x;
            } else if ((adrs_ovl->proc_idx == mAD_PROC_TURN_PAGE && adrs_ovl->speed_x < 0.0f) ||
                       (adrs_ovl->proc_idx == mAD_PROC_TURN_PAGE2 && adrs_ovl->speed_x > 0.0f)) {
                x = pos_x - adrs_ovl->pos_x;
            } else {
                x = pos_x + adrs_ovl->pos_x;
            }

            x += adrs_ovl->pile[idx];
            y = pos_y - adrs_ovl->pile[idx];
            mAD_set_addressSel_tag_field(graph, x, y, idx, col);

            (*submenu->overlay->set_char_matrix_proc)(graph);
            mAD_set_addressSel_tag_character(submenu, game, x, y, idx);
        }

        col--;
    }
}

static void mAD_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    GRAPH* graph = game->graph;
    f32 pos_x = menu_info->position[0];
    f32 pos_y = menu_info->position[1];

    if (adrs_ovl->proc_idx == mAD_PROC_REFUSE || adrs_ovl->proc_idx == mAD_PROC_START) {
        mAD_set_first_tag(submenu, game, graph, pos_x, pos_y);
    } else {
        mAD_set_addressSel_tag(submenu, graph, game);
    }
}

static void mAD_address_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ADDRESS];

    (*menu_info->pre_draw_func)(submenu, game);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        Gfx* gfx = NULL;

        if (menu_info->next_menu_type == mSM_OVL_EDITOR) {
            OPEN_DISP(game->graph);

            gfx = NOW_POLY_OPA_DISP;
            NEXT_POLY_OPA_DISP;
            submenu->overlay->address_ovl->display_list = NOW_POLY_OPA_DISP;

            CLOSE_DISP(game->graph);

        }

        mAD_set_dl(submenu, game, menu_info);

        if (gfx != NULL) {
            OPEN_DISP(game->graph);

            gSPEndDisplayList(NEXT_POLY_OPA_DISP);
            gSPBranchList(gfx, NOW_POLY_OPA_DISP);

            CLOSE_DISP(game->graph);
        }
    } else {
        submenu->overlay->address_ovl->display_list = NULL;
    }
}

extern void mAD_address_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* ctrl_p = &submenu->overlay->menu_control;

    ctrl_p->menu_move_func = mAD_address_ovl_move;
    ctrl_p->menu_draw_func = mAD_address_ovl_draw;
}

static void mAD_address_ovl_init(Submenu* submenu) {
    mAD_Ovl_c* adrs_ovl = submenu->overlay->address_ovl;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ADDRESS];
    int page_bitfield = 0;
    int i;
    u8 count = 0;

    submenu->overlay->menu_control.animation_flag = FALSE;
    switch (menu_info->data0) {
        case mAD_OPEN_ADDRESS:
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            break;
        case mAD_OPEN_WAIT:
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_BOARD, MAIL_HEADER_BASE_LEN, menu_info->data2, menu_info->data3);
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
            break;
        default:
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
            break;
    }

    mAD_make_player_address(adrs_ovl);
    mAD_make_npc_address(adrs_ovl);
    if (adrs_ovl->page_entry_count[mAD_PAGE_PLAYER] != 0) {
        adrs_ovl->curIdx = mAD_PAGE_PLAYER;
    } else if (adrs_ovl->page_entry_count[mAD_PAGE_NPC0] != 0) {
        adrs_ovl->curIdx = mAD_PAGE_NPC0;
    }

    for (i = mAD_PAGE_NUM - 1; i >= 0; i--) {
        page_bitfield <<= 1;
        if (adrs_ovl->page_entry_count[i] != 0) {
            page_bitfield |= 1;
            count++;
        }
    }

    adrs_ovl->page_bitfield = page_bitfield;
    adrs_ovl->page_count = count;

    if (adrs_ovl->page_count == 0) {
        adrs_ovl->proc_idx = mAD_PROC_REFUSE;
    } else {
        adrs_ovl->proc_idx = mAD_PROC_START;
    }
}

extern void mAD_address_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    int flag = FALSE;
    
    if (ovl->address_ovl == NULL) {
        mem_clear((u8*)&adrs_ovl_data, sizeof(adrs_ovl_data), 0);
        ovl->address_ovl = &adrs_ovl_data;
        flag = TRUE;
    }

    mAD_address_ovl_init(submenu);
    mAD_address_ovl_set_proc(submenu);

    if (flag) {
        mAD_address_draw_init(submenu);
    }
}

extern void mAD_address_ovl_destruct(Submenu* submenu) {
    submenu->overlay->address_ovl = NULL;
}
