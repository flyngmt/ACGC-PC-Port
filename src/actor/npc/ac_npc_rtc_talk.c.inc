static void aNRTC_set_slot_name(int slot_id, int str_no) {
    u8 name[mIN_ITEM_NAME_LEN];

    mString_Load_StringFromRom(name, sizeof(name), 0x06CD + slot_id);
    mMsg_SET_FREE_STR(str_no, name, sizeof(name));
}

static void aNRTC_rtc_err(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    if (mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                aNRTC_change_talk_proc(rtc, aNRTC_TALK_TIMER_OPEN_MSG_WAIT);
                break;
            case mChoice_CHOICE1:
                rtc->think_idx = aNRTC_THINK_TITLE;
                aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
                break;
        }
    }
}

static void aNRTC_timer_open_msg_wait(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_TYPE_4, 9);

    if (order == 1) {
        if (mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
            mDemo_Set_OrderValue(mDemo_TYPE_4, 9, 0);
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_TIMER_OPEN_WAIT);
            mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE1();
        }
    }
}

static void aNRTC_timer_open_wait(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    Submenu* submenu = &play->submenu;

    if (mMsg_CHECK_MAIN_WAIT() == TRUE) {
        aNRTC_change_talk_proc(rtc, aNRTC_THINK_WAIT);
        mSM_open_submenu(submenu, mSM_OVL_TIMEIN, mTI_OVL_OPEN_INITIAL, 0);
        mMsg_REQUEST_MAIN_APPEAR_WAIT_TYPE1();
    }
}

static void aNRTC_timer_close_wait(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    if (play->submenu.open_flag == FALSE) {
        if (mMsg_CHECK_NOT_SERIES_MAIN_WAIT() == TRUE) {
            mMsg_SET_FORCENEXT();
            rtc->think_idx = aNRTC_THINK_DOOR;
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
        }
    }
}

static void aNRTC_delete_bf(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_TYPE_4, 9);

    if ((mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) && (order != 0)) {

        mMsg_SET_LOCKCONTINUE();
        aNRTC_change_talk_proc(rtc, aNRTC_TALK_DELETE);
    }
}

static void aNRTC_delete(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    mMsg_Window_c* window;
    int card;
    int card_ret;

    window = mMsg_Get_base_window_p();
    card_ret = mCD_EraseBrokenLand_bg(&card);

    switch (card_ret) {
        case 0:
            rtc->think_idx = aNRTC_THINK_CHECK;
            mMsg_Set_continue_msg_num(window, 0x09DE);
            break;
        case 22:
        case 2:
            rtc->think_idx = aNRTC_THINK_TITLE;
            mMsg_Set_continue_msg_num(window, 0x09DF);
            break;
        case 25:
            return;
        case 15:
            rtc->think_idx = aNRTC_THINK_CHECK;
            mMsg_Set_continue_msg_num(window, 0x09E1);
            break;
        default:
            rtc->think_idx = aNRTC_THINK_TITLE;
            mMsg_Set_continue_msg_num(window, 0x09DF);
            break;
    }

    if (card_ret != 25) {
        mMsg_Unset_LockContinue(window);
        aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
    }
}

static void aNRTC_format_chk(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    if (mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
        aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                rtc->think_idx = aNRTC_THINK_CHECK;
                break;
            case mChoice_CHOICE1:
                rtc->think_idx = aNRTC_THINK_DOOR;
                break;
            case mChoice_CHOICE2:
                rtc->think_idx = aNRTC_THINK_TITLE;
                break;
            case mChoice_CHOICE3:
                rtc->think_idx = aNRTC_THINK_CHECK;
                aNRTC_change_talk_proc(rtc, aNRTC_TALK_FORMAT);
                break;
        }
    }
}

static void aNRTC_format(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    int order;
    mMsg_Window_c* window;

    window = mMsg_Get_base_window_p();
    order = mDemo_Get_OrderValue(mDemo_TYPE_4, 9);
    switch (order) {
        case 1:
            mDemo_Set_OrderValue(mDemo_TYPE_4, 9, 2);
            mMsg_Set_LockContinue(window);
            break;
        case 2:
            switch (mCD_card_format_bg(Common_Get(memcard_slot))) {
                case mCD_RESULT_SUCCESS:
                    mMsg_Set_continue_msg_num(window, 0x09E9);
                    mMsg_Unset_LockContinue(window);
                    aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
                    rtc->think_idx = aNRTC_THINK_CHECK;
                    mDemo_Set_OrderValue(mDemo_TYPE_4, 9, 0);
                    break;
                case mCD_RESULT_ERROR:
                    mMsg_Unset_LockContinue(window);
                    aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
                    rtc->think_idx = aNRTC_THINK_TITLE;
                    mMsg_Set_continue_msg_num(window, 0x09E7);
                    mDemo_Set_OrderValue(mDemo_TYPE_4, 9, 0);
                case mCD_RESULT_BUSY:
                    break;
            }
            break;
    }
}

static void aNRTC_break_data(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    if (mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
        aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                rtc->think_idx = aNRTC_THINK_CHECK;
                break;
            case mChoice_CHOICE1:
                aNRTC_change_talk_proc(rtc, aNRTC_TALK_DELETE_BF);
                break;
        }
    }
}

static void aNRTC_break_data_2(NPC_RTC_ACTOR* rtc, GAME_PLAY* play) {
    if (mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
        aNRTC_change_talk_proc(rtc, aNRTC_TALK_END);
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                rtc->think_idx = aNRTC_THINK_CHECK;
                break;
            case mChoice_CHOICE1:
                rtc->think_idx = aNRTC_THINK_DOOR;
                break;
            case mChoice_CHOICE2:
                rtc->think_idx = aNRTC_THINK_TITLE;
                break;
            case mChoice_CHOICE3:
                rtc->think_idx = aNRTC_THINK_IPMENU;
                break;
        }
    }
}

static void aNRTC_change_talk_proc(NPC_RTC_ACTOR* rtc, int idx) {
    // clang-format off
    static aNRTC_PROC process[] = {
        &aNRTC_break_data,
        &aNRTC_break_data_2,
        &aNRTC_rtc_err,
        &aNRTC_timer_open_msg_wait,
        &aNRTC_timer_open_wait,
        &aNRTC_timer_close_wait,
        &aNRTC_delete_bf,
        &aNRTC_delete,
        &aNRTC_format_chk,
        &aNRTC_format,
        (aNRTC_PROC)&none_proc1,
    };
    // clang-format on

    rtc->talk_idx = idx;
    rtc->talk_proc = process[idx];
}

static void aNRTC_set_talk_info_talk_request(ACTOR* actor) {
    int msg;

    switch (Common_Get(save_error_type)) {
        case mFRm_ERROR_BAD_RTC:
            msg = 0x09CC;
            break;
        case mFRm_ERROR_DATA_CORRUPTED:
            msg = 0x09D1;
            break;
        case mFRm_ERROR_MEMCARD_INVALID:
            msg = 0x09DA;
            break;
        case mFRm_ERROR_MEMCARD_NO_SPACE:
            msg = 0x09D8;
            break;
        case mFRm_ERROR_NO_MEMCARD:
            msg = 0x09D4;
            break;
        case mFRm_ERROR_MEMCARD_TRAVELDATA_CONFLICT:
            msg = 0x09E2;
            break;
        case mFRm_ERROR_MEMCARD_DAMAGED:
            msg = 0x09E4;
            break;
        case mFRm_ERROR_MEMCARD_NO_FILES:
            msg = 0x09E3;
            break;
        case mFRm_ERROR_MEMCARD_FORMAT:
            msg = 0x09E5;
            break;
        case mFRm_ERROR_NOT_MEMCARD:
            msg = 0x09E6;
            break;
        default:
            msg = 0x09D4;
            break;
    }

    mDemo_Set_msg_num(msg);
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
}

static void aNRTC_talk_request(ACTOR* actor, GAME* game) {
    mDemo_Request(mDemo_TYPE_SPEAK, actor, &aNRTC_set_talk_info_talk_request);
}

static int aNRTC_talk_init(ACTOR* actor, GAME* game) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;

    mDemo_Set_ListenAble();
    aNRTC_set_slot_name(Common_Get(memcard_slot), mMsg_FREE_STR4);
    switch (Common_Get(save_error_type)) {
        case mFRm_ERROR_BAD_RTC:
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_RTC_ERR);
            break;
        case mFRm_ERROR_DATA_CORRUPTED:
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_BREAK_DATA);
            break;
        case mFRm_ERROR_MEMCARD_FORMAT:
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_FORMAT_CHK);
            break;
        default:
            aNRTC_change_talk_proc(rtc, aNRTC_TALK_BREAK_DATA2);
            break;
    }
    rtc->npc_class.talk_info.talk_request_proc = mActor_NONE_PROC1;
    mMsg_SET_IDLING_REQ();
    return TRUE;
}

static int aNRTC_talk_end_chk(ACTOR* actor, GAME* game) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int res = FALSE;
    mMsg_Window_c* window;

    window = mMsg_Get_base_window_p();
    (*rtc->talk_proc)(rtc, play);

    if (mMsg_Check_idling_now(window) == TRUE) {
        mMsg_request_main_disappear_wait_type1(window);
        aNRTC_think_init_proc(&rtc->npc_class, play);
        rtc->talk_flag = FALSE;
        res = TRUE;
        rtc->bgm_timer = 50;
        rtc->fade_timer = 75;
        bzero(&play->fade_color_value, sizeof(rgba8888_t));
    } else {
        f32 counter = rtc->counter;

        if ((mMsg_CHECK_MAINNORMAL() == TRUE) || (mChoice_CHECK_MAIN_NORMAL() == TRUE)) {
            counter += (f32)game->graph->dt_num_60fps_frames;
            if (counter > 600.0f) {
                counter = 600.0f;
            }
        } else {
            counter = 0.0f;
        }

        if (mDemo_Get_OrderValue(mDemo_TYPE_4, 0) == 0) {
            if (counter >= 600.0f) {
                if (rtc->npc_class.draw.animation_id != aNPC_ANIM_4HAKU_E1) {
                    mDemo_Set_OrderValue(mDemo_TYPE_4, 0, 0xFF);
                }
            } else if (rtc->npc_class.draw.animation_id == aNPC_ANIM_4HAKU_E1) {
                mDemo_Set_OrderValue(mDemo_TYPE_4, 0, 0xFD);
            }
        }
        rtc->counter = counter;
    }
    return res;
}
