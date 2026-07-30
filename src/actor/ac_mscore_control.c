#include "ac_mscore_control.h"

#include "m_player_lib.h"
#include "m_melody.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_mscore_ovl.h"
#include "m_msg.h"
#include "m_malloc.h"
#include "m_eappli.h"
#include "GBA2/gba2.h"

enum {
    aMSC_ACT_MENU_OPEN_WAIT,
    aMSC_ACT_MENU_CLOSE_WAIT,
    aMSC_ACT_REQUEST_FORCE_TALK,
    aMSC_ACT_SELECT_READ_PRG_OR_DATA,
    aMSC_ACT_CHECK_CONNECT_AGB_START_WAIT,
    aMSC_ACT_CHECK_CONNECT_AGB_END_WAIT,
    aMSC_ACT_READ_DATA,
    aMSC_ACT_CHECK_CONNECT_AGB_START_WAIT2,
    aMSC_ACT_CHECK_CONNECT_AGB_END_WAIT2,
    aMSC_ACT_SEND_DATA,
    aMSC_ACT_SELECT_READ_DATA_OR_NOT,
    aMSC_ACT_FORCE_MENU_OPEN_WAIT,
    aMSC_ACT_TALK_END_WAIT,

    aMSC_ACT_NUM
};

static void aMSC_actor_ct(ACTOR* actorx, GAME* game);
static void aMSC_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Mscore_Control_Profile = {
    mAc_PROFILE_MSCORE_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MSCORE_CONTROL_ACTOR),
    &aMSC_actor_ct,
    mActor_NONE_PROC1,
    &aMSC_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static void aMSC_setupAction(MSCORE_CONTROL_ACTOR* mscore_ctrl, int act_idx);

static void aMSC_actor_ct(ACTOR* actorx, GAME* game) {
    MSCORE_CONTROL_ACTOR* mscore_ctrl = (MSCORE_CONTROL_ACTOR*)actorx;

    aMSC_setupAction(mscore_ctrl, aMSC_ACT_MENU_OPEN_WAIT);
}

static void aMSC_menu_open_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    int angle_y;

    if (player != NULL) {
        Submenu* submenu = &play->submenu;

        if (player->a_btn_pressed == TRUE && !Common_Get(reset_flag) && !submenu->start_refuse &&
            submenu->start_refuse_timer == 0 && mPlib_able_submenu_type1((GAME*)play)) {
            angle_y = DEG2SHORT_ANGLE2(180.0f) + player->actor_class.shape_info.rotation.y;

            if (ABS((s16)angle_y) < DEG2SHORT_ANGLE2(45.0f)) {
                int item = player->item_in_front;

                if (!(item < (MUSIC_BOARD1 + 1) && item >= MUSIC_BOARD0)) {
                    return;
                }

                mMld_GetMelody(mscore_ctrl->melody);
                mSM_open_submenu_new2(submenu, mSM_OVL_MSCORE, 0, 0, mscore_ctrl,
                                      (mSM_param3_t)(uintptr_t)mscore_ctrl->melody);
                player->a_btn_pressed = FALSE;
                player->a_btn_triggers_submenu = TRUE;
                aMSC_setupAction(mscore_ctrl, aMSC_ACT_MENU_CLOSE_WAIT);
            }
        }
    }
}

static void aMSC_menu_close_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    Submenu* submenu = &play->submenu;

    if (!submenu->open_flag) {
        int next_action = aMSC_ACT_MENU_OPEN_WAIT;

        if (submenu->after_mode == aHOI_REQUEST_NUM) {
            next_action = aMSC_ACT_REQUEST_FORCE_TALK;
        }

        aMSC_setupAction(mscore_ctrl, next_action);
    }
}

static void aMSC_set_force_talk_info_talk_request(ACTOR* actorx) {
    mDemo_Set_msg_num(MSG_15834);
    mDemo_Set_talk_turn(FALSE);
    mDemo_Set_camera(CAMERA2_PROCESS_STOP);
    mDemo_Set_talk_display_name(FALSE);
}

static void aMSC_request_force_talk(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    if (mDemo_Check(mDemo_TYPE_SPEAK, (ACTOR*)mscore_ctrl) == TRUE && !mDemo_Check_ListenAble()) {
        mDemo_Set_ListenAble();
        aMSC_setupAction(mscore_ctrl, aMSC_ACT_SELECT_READ_PRG_OR_DATA);
    } else {
        mDemo_Request(mDemo_TYPE_SPEAK, (ACTOR*)mscore_ctrl, &aMSC_set_force_talk_info_talk_request);
    }
}

static void aMSC_select_read_prg_or_data(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);
    int next_act_idx;

    if (order != 0 && mMsg_Check_MainNormalContinue(msg_p)) {
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                next_act_idx = aMSC_ACT_CHECK_CONNECT_AGB_START_WAIT;
                break;
            case mChoice_CHOICE1:
                next_act_idx = aMSC_ACT_CHECK_CONNECT_AGB_START_WAIT2;
                break;
            default:
                mMsg_Set_CancelNormalContinue(msg_p);
                mMsg_Unset_LockContinue(msg_p);
                next_act_idx = aMSC_ACT_TALK_END_WAIT;
                break;
        }

        if (next_act_idx != -1) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);
            aMSC_setupAction(mscore_ctrl, next_act_idx);
        }
    }
}

static void aMSC_check_connect_agb_start_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);

    if (order != 0 && mMsg_Check_MainNormalContinue(msg_p)) {
        mGcgba_InitVar();
        mscore_ctrl->counter = 0;
        mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);
        mMsg_Set_LockContinue(msg_p);
        aMSC_setupAction(mscore_ctrl, mscore_ctrl->action + 1);
    }
}

// Aus version sets force next flag when connection fails
static void aMSC_check_connect_agb_end_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    int next_act_idx = -1;

    switch (mGcgba_ConnectEnabled()) {
        case GBA2_GBA_STATE_TRANSMITTING:
            break;
        case GBA2_GBA_STATE_SUCCESS:
            next_act_idx = mscore_ctrl->action + 1;
            break;
    }

    mscore_ctrl->counter++;
    if (next_act_idx != -1) {
        mGcgba_InitVar();
        sAdo_SysLevStart(NA_SE_47);
        if (next_act_idx == aMSC_ACT_READ_DATA) {
            mscore_ctrl->readbuf_p = (u8*)zelda_malloc_align(sizeof(mscore_ctrl->melody), 32);
        }
        aMSC_setupAction(mscore_ctrl, next_act_idx);
    } else if (mscore_ctrl->counter > 60) {
        mMsg_Window_c* msg_p = mMsg_Get_base_window_p();

        mMsg_Set_continue_msg_num(msg_p, 0x3DDF);
        mMsg_Unset_LockContinue(msg_p);
#if VERSION >= VER_GAFU01_00
        mMsg_SET_FORCENEXT();
#endif
        mGcgba_EndComm();
        aMSC_setupAction(mscore_ctrl, aMSC_ACT_TALK_END_WAIT);
    }
}

static void aMSC_read_data(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();

    switch (mGcgba_Read(mscore_ctrl->readbuf_p, sizeof(mscore_ctrl->melody), GBA2_EAPPLI_TYPE_MUSICSCORE)) {
        case GBA2_GBA_STATE_TRANSMITTING:
            break;
        case GBA2_GBA_STATE_SUCCESS:
            mMld_SetSaveMelody(mscore_ctrl->readbuf_p);
            zelda_free(mscore_ctrl->readbuf_p);
            mGcgba_EndComm();
            sAdo_SysLevStop(NA_SE_47);
            mMsg_Set_CancelNormalContinue(msg_p);
            mMsg_Unset_LockContinue(msg_p);
            mMsg_Set_ForceNext(msg_p);
            aMSC_setupAction(mscore_ctrl, aMSC_ACT_FORCE_MENU_OPEN_WAIT);
            break;
        default:
            mGcgba_EndComm();
            sAdo_SysLevStop(NA_SE_47);
            mMsg_Set_continue_msg_num(msg_p, 0x3DDC);
            mMsg_Unset_LockContinue(msg_p);
            mMsg_Set_ForceNext(msg_p);
            aMSC_setupAction(mscore_ctrl, aMSC_ACT_TALK_END_WAIT);
            break;
    }
}

static void aMSC_send_prg(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    static int next_act_idx[] = { aMSC_ACT_SELECT_READ_DATA_OR_NOT, aMSC_ACT_TALK_END_WAIT };
    static int next_msg_num[] = { 0x3DE0, 0x3DDD };

    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int idx = -1;

    switch (mGcgba_send_eAppri(mEA_dl_carde_program_p(), mEA_dl_carde_program_size())) {
        case GBA2_EAPPLI_SUCCESS:
            idx = 0;
            break;
        case GBA2_EAPPLI_FAILURE_XFER_ERROR:
        case GBA2_EAPPLI_FAILURE_NO_GBA:
            idx = 1;
            break;
    }

    if (idx != -1) {
        mGcgba_EndComm();
        sAdo_SysLevStop(NA_SE_47);
        mMsg_Set_continue_msg_num(msg_p, next_msg_num[idx]);
        mMsg_Unset_LockContinue(msg_p);
        mMsg_Set_ForceNext(msg_p);
        aMSC_setupAction(mscore_ctrl, next_act_idx[idx]);
    }
}

static void aMSC_select_read_data_or_not(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);

    if (order != 0 && mMsg_Check_MainNormalContinue(msg_p)) {
        int next_act_idx = -1;

        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                next_act_idx = aMSC_ACT_CHECK_CONNECT_AGB_START_WAIT;
                break;
            case mChoice_CHOICE1:
                next_act_idx = aMSC_ACT_TALK_END_WAIT;
                mMsg_Set_CancelNormalContinue(msg_p);
                break;
        }

        if (next_act_idx != -1) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);
            aMSC_setupAction(mscore_ctrl, next_act_idx);
        }
    }
}

static void aMSC_force_menu_open_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    if (!mDemo_Check(mDemo_TYPE_SPEAK, (ACTOR*)mscore_ctrl)) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

        if (player != NULL) {
            Submenu* submenu = &play->submenu;

            mSM_open_submenu_new2(submenu, mSM_OVL_MSCORE, 0, 0, mscore_ctrl,
                                  (mSM_param3_t)(uintptr_t)mscore_ctrl->melody);
            player->a_btn_pressed = FALSE;
            player->a_btn_triggers_submenu = TRUE;
            aMSC_setupAction(mscore_ctrl, aMSC_ACT_MENU_CLOSE_WAIT);
        }
    }
}

static void aMSC_talk_end_wait(MSCORE_CONTROL_ACTOR* mscore_ctrl, GAME_PLAY* play) {
    if (!mDemo_Check(mDemo_TYPE_SPEAK, (ACTOR*)mscore_ctrl)) {
        aMSC_setupAction(mscore_ctrl, aMSC_ACT_MENU_OPEN_WAIT);
    }
}

static void aMSC_setupAction(MSCORE_CONTROL_ACTOR* mscore_ctrl, int act_idx) {
    // clang-format off
    static aMSC_ACTION_PROC process[] = {
        &aMSC_menu_open_wait,
        &aMSC_menu_close_wait,
        &aMSC_request_force_talk,
        &aMSC_select_read_prg_or_data,
        &aMSC_check_connect_agb_start_wait,
        &aMSC_check_connect_agb_end_wait,
        &aMSC_read_data,
        &aMSC_check_connect_agb_start_wait,
        &aMSC_check_connect_agb_end_wait,
        &aMSC_send_prg,
        &aMSC_select_read_data_or_not,
        &aMSC_force_menu_open_wait,
        &aMSC_talk_end_wait,
    };
    // clang-format on

    mscore_ctrl->action_proc = process[act_idx];
    mscore_ctrl->action = act_idx;
}

static void aMSC_actor_move(ACTOR* actorx, GAME* game) {
    MSCORE_CONTROL_ACTOR* mscore_ctrl = (MSCORE_CONTROL_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    (*mscore_ctrl->action_proc)(mscore_ctrl, play);
}
