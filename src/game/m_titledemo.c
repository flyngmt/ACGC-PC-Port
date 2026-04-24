#include "m_titledemo.h"

#include "m_player.h"
#include "m_player_lib.h"
#include "m_event.h"
#include "m_name_table.h"
#include "m_bgm.h"
#include "m_common_data.h"

#define mTD_HEADER_POSX 0
#define mTD_HEADER_POSY 1
#define mTD_HEADER_POSZ 2
#define mTD_HEADER_ROTATION 3
#define mTD_HEADER_TOOL 4
#define mTD_HEADER_SIZE 5

static int S_now_demono = mEv_TITLEDEMO_LOGO;
static int S_tdemo_frame;
static u16 S_titledemo_to_play;

static u16 get_demo_header(int titledemo_no, int key) {
    static u16* pact_data_head_pt[mTD_TITLE_DEMO_NUM] = { pact0_head_table, pact1_head_table, pact2_head_table,
                                                            pact3_head_table, pact4_head_table };

    return pact_data_head_pt[titledemo_no][key];
}

extern int mTD_demono_get() {
    if (S_now_demono == mEv_TITLEDEMO_LOGO) {
        S_now_demono = mEv_TITLEDEMO_START1;
    } else {
        S_now_demono++;
        if (S_now_demono > mTD_TITLE_DEMO_NUM) {
            S_now_demono = mEv_TITLEDEMO_START1;
        }
    }

    return S_now_demono;
}

extern void mTD_player_keydata_init(GAME_PLAY* play) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    if (mEv_IsTitleDemo()) {
        u16 angle;
        mActor_name_t tool = get_demo_header(mEv_CheckTitleDemo() - mEv_TITLEDEMO_START1, mTD_HEADER_TOOL);

        if (tool == ITM_AXE) {
            tool = ITM_AXE;
        } else if (tool == ITM_ROD) {
            tool = ITM_ROD;
        } else if (tool == ITM_UMBRELLA00) {
            tool = ITM_UMBRELLA00;
        }

        mPlib_SetData2_controller_data_for_title_demo(tool);
        angle = get_demo_header(mEv_CheckTitleDemo() - mEv_TITLEDEMO_START1, mTD_HEADER_ROTATION);

        player->actor_class.shape_info.rotation.y = angle;
        player->actor_class.world.angle.y = angle;
    }

    S_tdemo_frame = 0;
}

static u16 get_tdemo_keydata(int frame) {
    /* BUG: this was probably meant to be marked as static */
    u16* pact_data_keydata_pt[mTD_TITLE_DEMO_NUM] = { pact0_key_data, pact1_key_data, pact2_key_data, pact3_key_data,
                                                      pact4_key_data };

    return pact_data_keydata_pt[mEv_CheckTitleDemo() - mEv_TITLEDEMO_START1][frame];
}

/* @fakematch? - the weirdness with btn_a needing to be assigned to a u8 then int needs to be investigated */
static void set_player_demo_keydata(int frame) {
    u16 keydata0;
    u16 keydata1;
    s8 k0_sx;
    s8 k0_sy;
    s8 k1_sx;
    s8 k1_sy;
    f32 stick_x;
    f32 stick_y;
    u8 tmp_a;
    int btn_a;
    int btn_b;
    int f0;
    int f1;

    /* convert 60fps framerate to 30fps input */
    f0 = frame / 2;
    f1 = f0 + (frame % 2);

    if (f0 != f1 && f1 < 1800) {
        keydata0 = get_tdemo_keydata(f0);
        keydata1 = get_tdemo_keydata(f1);

        k0_sx = (s16)(keydata0 & 0xFE00) / 512;
        k0_sy = (s16)((keydata0 & 0x00FE) << 8) / 512;
        k1_sx = (s16)(keydata1 & 0xFE00) / 512;
        k1_sy = (s16)((keydata1 & 0x00FE) << 8) / 512;

        /* blend stick inputs between the current frame & next frame */
        stick_x = ((f32)(int)k0_sx + (f32)(int)k1_sx) / 2.0f;
        stick_y = ((f32)(int)k0_sy + (f32)(int)k1_sy) / 2.0f;

        tmp_a = keydata0 & 1;
        btn_a = tmp_a;
        btn_b = (u8)(keydata0 >> 8) & 1;
    } else {
        keydata0 = get_tdemo_keydata(f0);
        k0_sx = ((s16)(keydata0 & 0xFE00)) / 512;
        k0_sy = ((s16)((keydata0 & 0x00FE) << 8)) / 512;

        stick_x = (f32)(int)k0_sx;
        stick_y = (f32)(int)k0_sy;

        tmp_a = keydata0 & 1;
        btn_a = tmp_a;
        btn_b = (u8)(keydata0 >> 8) & 1;
    }
    mPlib_SetData1_controller_data_for_title_demo(btn_a, btn_b, (f32)stick_x, (f32)stick_y);
}

static void mTD_game_end_init(GAME_PLAY* play) {
    play->fb_fade_type = FADE_TYPE_SELECT_END;
    play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;

    mPlib_request_main_invade_type1((GAME*)play);
    mBGMPsComp_make_ps_wipe(0x521C); // TODO: enum/define
}

extern void title_demo_move(GAME_PLAY* play) {
    if (mEv_IsTitleDemo()) {
#ifdef TARGET_PC
        /* Hold the demo frame counter while the Options menu owns the
         * screen. Otherwise demo is broken. */
        {
            extern int pc_settings_menu_active(void);
            if (pc_settings_menu_active()) {
                mPlib_SetData1_controller_data_for_title_demo(0, 0, 0.0f, 0.0f);
                return;
            }
        }
#endif
        set_player_demo_keydata(S_tdemo_frame);
        S_tdemo_frame++;

        if (S_tdemo_frame >= 3600) {
            mTD_game_end_init(play);
        }
    }
}

extern void mTD_rtc_set() {
    if (S_titledemo_to_play == TRUE) {
        S_titledemo_to_play = FALSE;

        if (Common_Get(time.rtc_crashed) == TRUE) {
            lbRTC_TimeCopy(Common_GetPointer(time.rtc_time), Common_GetPointer(newly_set_time));
        } else {
            lbRTC_GetTime(Common_GetPointer(time.rtc_time));
        }

        Common_Set(time.rtc_enabled, TRUE);
        mTM_set_season();
    }
}

extern void mTD_rtc_reserve() {
    S_titledemo_to_play = TRUE;
}

extern int mTD_get_titledemo_no() {
    int titledemo_no = S_now_demono;
    if (titledemo_no <= mEv_TITLEDEMO_NONE) {
        titledemo_no = mEv_TITLEDEMO_START1;
    }

    return titledemo_no - mEv_TITLEDEMO_START1;
}

extern int mTD_tdemo_button_ok_check() {
    int res = TRUE;
    if (S_tdemo_frame >= 3530) {
        res = FALSE;
    }

    return res;
}
