#include "m_titledemo.h"

#include "m_player.h"
#include "m_player_lib.h"
#include "m_event.h"
#include "m_name_table.h"
#include "m_bgm.h"
#include "m_common_data.h"

#define mTD_LENGTH_SECONDS 60
#define mTD_LENGTH_FRAMES_30FPS (mTD_LENGTH_SECONDS * 30)
#define mTD_LENGTH_FRAMES_60FPS (mTD_LENGTH_SECONDS * 60)
#define mTD_START_END_FRAME (mTD_LENGTH_FRAMES_60FPS - 70) // 3530 frames

#define mTD_HEADER_POSX 0
#define mTD_HEADER_POSY 1
#define mTD_HEADER_POSZ 2
#define mTD_HEADER_ROTATION 3
#define mTD_HEADER_TOOL 4
#define mTD_HEADER_SIZE 5

static int S_now_demono = mEv_TITLEDEMO_LOGO;
static int S_tdemo_frame;
static float S_tdemo_time = 0.0f;
static u16 S_titledemo_to_play;
static float S_tdemo_frame_accum;

static u16 get_demo_header(int titledemo_no, int key) {
    static const u16* pact_data_head_pt[mTD_TITLE_DEMO_NUM] = {
        pact0_head_table, // 0
        pact1_head_table, // 1
        pact2_head_table, // 2
        pact3_head_table, // 3
        pact4_head_table, // 4
    };

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
    S_tdemo_time = 0.0f;
    S_tdemo_frame_accum = 0.0f;
}

static u16 get_tdemo_keydata(int frame) {
    static const u16* pact_data_keydata_pt[mTD_TITLE_DEMO_NUM] = {
        pact0_key_data, // 0
        pact1_key_data, // 1
        pact2_key_data, // 2
        pact3_key_data, // 3
        pact4_key_data, // 4
    };

    return pact_data_keydata_pt[mEv_CheckTitleDemo() - mEv_TITLEDEMO_START1][frame];
}

#if 0
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
    // int f0;
    // int f1;

    // We have 1800 frames at 30fps, so we need to pull out our current frame AND the next frame using delta time
    float progress = S_tdemo_time / mTD_LENGTH_SECONDS;
    float frame_progress = progress * mTD_LENGTH_FRAMES_30FPS;
    int current_frame = (int)frame_progress;
    int next_frame = current_frame + 1;
    float percent = frame_progress - (float)current_frame; // 0.0f to 1.0f

    // TODO: how can we interpolate between the two frames

    keydata0 = get_tdemo_keydata(current_frame);
    keydata1 = get_tdemo_keydata(next_frame);

    k0_sx = (s16)(keydata0 & 0xFE00) / 512;
    k0_sy = (s16)((keydata0 & 0x00FE) << 8) / 512;
    k1_sx = (s16)(keydata1 & 0xFE00) / 512;
    k1_sy = (s16)((keydata1 & 0x00FE) << 8) / 512;

    // blend stick inputs
    stick_x = k0_sx * (1.0f - percent) + k1_sx * percent;
    stick_y = k0_sy * (1.0f - percent) + k1_sy * percent;

    tmp_a = keydata0 & 1;
    btn_a = tmp_a;
    btn_b = (u8)(keydata0 >> 8) & 1;
    
#if 0
    /* convert 60fps framerate to 30fps input */
    f0 = frame / 2;
    f1 = f0 + (frame % 2);

    if (f0 != f1 && f1 < mTD_LENGTH_FRAMES_30FPS) {
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

#endif
    mPlib_SetData1_controller_data_for_title_demo(btn_a, btn_b, (f32)stick_x, (f32)stick_y);
}
#endif

/* Zero-order hold version that keeps recorded 30fps magnitude when running at higher FPS.
   This avoids triangle-shaped stick pulses that can underflow acre transitions. */
static void set_player_demo_keydata_hold(float delta_time) {
    u16 keydata;
    s8 stick_x;
    s8 stick_y;
    int btn_a;
    int btn_b;
    int frame_index = S_tdemo_frame;

    /* Clamp delta_time to prevent large jumps on first frame or frame spikes */
    if (delta_time > (1.0f / 30.0f)) {
        delta_time = 1.0f / 30.0f;
    }

    /* Clamp so we never read past recorded data; caller handles end-of-demo. */
    if (frame_index < 0) {
        frame_index = 0;
    } else if (frame_index >= mTD_LENGTH_FRAMES_30FPS) {
        frame_index = mTD_LENGTH_FRAMES_30FPS - 1;
    }

    keydata = get_tdemo_keydata(frame_index);
    stick_x = (s16)(keydata & 0xFE00) / 512;
    stick_y = (s16)((keydata & 0x00FE) << 8) / 512;
    btn_a = keydata & 1;
    btn_b = (u8)(keydata >> 8) & 1;

    /* Hold last recorded sample so magnitude matches the original 30fps capture. */
    mPlib_SetData1_controller_data_for_title_demo(btn_a, btn_b, (f32)stick_x, (f32)stick_y);

    /* Advance the 30fps sample index using accumulated fractional frames.
       Sampling happens before advancing so we never skip the initial samples even if the first delta is large. */
    if (delta_time < 0.0f) {
        delta_time = 0.0f;
    }

    S_tdemo_frame_accum += delta_time * 30.0f; /* convert time to 30fps frames */
    if (S_tdemo_frame_accum >= 1.0f) {
        int whole_frames = (int)S_tdemo_frame_accum;
        S_tdemo_frame += whole_frames;
        S_tdemo_frame_accum -= (float)whole_frames;

        if (S_tdemo_frame >= mTD_LENGTH_FRAMES_30FPS) {
            S_tdemo_frame = mTD_LENGTH_FRAMES_30FPS - 1;
        }
    }
}

static void mTD_game_end_init(GAME_PLAY* play) {
    play->fb_fade_type = FADE_TYPE_SELECT_END;
    play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;

    mPlib_request_main_invade_type1((GAME*)play);
    mBGMPsComp_make_ps_wipe(0x521C); // TODO: enum/define
}

extern void title_demo_move(GAME_PLAY* play) {
    if (mEv_IsTitleDemo()) {
        float delta_time = play->game.graph->dt;

        set_player_demo_keydata_hold(delta_time);
        S_tdemo_time += delta_time;

        // if (S_tdemo_frame >= 3600) {
        if (S_tdemo_time >= mTD_LENGTH_SECONDS) {
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
    if (S_tdemo_frame >= mTD_START_END_FRAME) {
        res = FALSE;
    }

    return res;
}
