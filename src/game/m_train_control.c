#include "m_train_control.h"

#include "m_common_data.h"
#include "m_play.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "sys_math.h"
#include "sys_math3d.h"
#include "audio.h"
#include "m_event.h"
#include "m_scene.h"
#include "m_lib.h"
#include "m_name_table.h"
#include "m_collision_bg.h"
#include "m_random_field.h"

#define mTRC_RTC_TIME_SECONDS(rtc_time) \
    (rtc_time->sec + (rtc_time->min + rtc_time->hour * mTM_MINUTES_IN_HOUR) * mTM_SECONDS_IN_MINUTE)

static void mTRC_SetMicPos(GAME_PLAY* play, xyz_t* mic_pos) {
    xyz_t pos;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    Door_data_c* door = Common_GetPointer(structure_exit_door_data);
    f32 z = cosf_table(0.0f) * 77.0f; // cos(0) = 1, 1.0f * 77.0f = 77.0f
    f32 x = sinf_table(0.0f) * 77.0f; // sin(0) = 0, 0.0f * 77.0f = 0.0f

    if (Common_Get(field_type) != mFI_FIELDTYPE2_FG) {
        xyz_t_move_s_xyz(&pos, &door->exit_position);
    } else {
        if (player != NULL) {
            xyz_t_move(&pos, &player->actor_class.world.position);
        } else {
            xyz_t_move(&pos, &ZeroVec);
        }
    }

    mic_pos->x = pos.x + x; // equates to pos.x + 0.0f = pos.x
    mic_pos->y = pos.y + 240.0f;
    mic_pos->z = pos.z + z; // equates to pos.z + 77.0f
}

static void mTRC_KishaStatusLevel(GAME_PLAY* play, f32 speed, xyz_t pos) {
    f32 distance;
    f32 distance2;
    f32 x;
    f32 y;
    f32 z;
    s16 angle;
    xyz_t mic_pos;
    u16 unsigned_angle;
    u16 unsigned_angle2;
    uintptr_t ongen;
    uintptr_t ongen2;

    mTRC_SetMicPos(play, &mic_pos);

    x = pos.x - mic_pos.x;
    y = pos.y - mic_pos.y;
    z = pos.z - mic_pos.z;
    angle = atans_table(z, x);
    distance = sqrtf(SQ(x) + SQ(y) + SQ(z));
    unsigned_angle = (int)angle;
    
    x = (pos.x - 250.0f) - mic_pos.x;
    y = pos.y - mic_pos.y;
    z = pos.z - mic_pos.z;
    angle = atans_table(z, x);
    distance2 = sqrtf(SQ(x) + SQ(y) + SQ(z));
    unsigned_angle2 = (int)angle;

    ongen = (uintptr_t)Common_GetPointer(train_coming_flag);
    ongen2 = (uintptr_t)Common_GetPointer(train_exists_flag);
    sAdos_KishaStatusLevel(speed, ongen, distance, unsigned_angle,
                           ongen2, distance2, unsigned_angle2);
}

static void mTRC_KishaStatusTrg(u8 state) {
    if (state == 1) {
        Common_Set(train_approaching_flag, TRUE);
    }

    sAdos_KishaStatusTrg(state);
}

static int aTRC_area_check(GAME_PLAY* play, xyz_t pos) {
    int block_x;
    int block_z;

    mFI_Wpos2BlockNum(&block_x, &block_z, pos);
    if (ABS(block_x - play->block_table.block_x) >= 2 || block_z != play->block_table.block_z) {
        return FALSE;
    }

    return TRUE;
}

static int mTRC_go_process() {
    int res = FALSE;
    int demo_no = mEv_CheckTitleDemo();

    if (((int)demo_no == mEv_TITLEDEMO_NONE || demo_no == mEv_TITLEDEMO_START1 || demo_no == mEv_TITLEDEMO_STAFFROLL) && Common_Get(field_draw_type) != FIELD_DRAW_TYPE_TRAIN &&
        Common_Get(field_draw_type) != FIELD_DRAW_TYPE_PLAYER_SELECT) {
        res = TRUE;
    }

    return res;
}

#define HOUR_MIN_SEC_TO_SECS(h, m, s) (h * 3600 + m * 60 + s)
static u32 mTRC_get_depart_time() {
    static u32 time_table[25] = {
        HOUR_MIN_SEC_TO_SECS(0, 19, 0),  HOUR_MIN_SEC_TO_SECS(1, 19, 0),  HOUR_MIN_SEC_TO_SECS(2, 19, 0),
        HOUR_MIN_SEC_TO_SECS(3, 19, 0),  HOUR_MIN_SEC_TO_SECS(4, 19, 0),  HOUR_MIN_SEC_TO_SECS(5, 19, 0),
        HOUR_MIN_SEC_TO_SECS(6, 19, 0),  HOUR_MIN_SEC_TO_SECS(7, 19, 0),  HOUR_MIN_SEC_TO_SECS(8, 19, 0),
        HOUR_MIN_SEC_TO_SECS(9, 19, 0),  HOUR_MIN_SEC_TO_SECS(10, 19, 0), HOUR_MIN_SEC_TO_SECS(11, 19, 0),
        HOUR_MIN_SEC_TO_SECS(12, 19, 0), HOUR_MIN_SEC_TO_SECS(13, 19, 0), HOUR_MIN_SEC_TO_SECS(14, 19, 0),
        HOUR_MIN_SEC_TO_SECS(15, 19, 0), HOUR_MIN_SEC_TO_SECS(16, 19, 0), HOUR_MIN_SEC_TO_SECS(17, 19, 0),
        HOUR_MIN_SEC_TO_SECS(18, 19, 0), HOUR_MIN_SEC_TO_SECS(19, 19, 0), HOUR_MIN_SEC_TO_SECS(20, 19, 0),
        HOUR_MIN_SEC_TO_SECS(21, 19, 0), HOUR_MIN_SEC_TO_SECS(22, 19, 0), HOUR_MIN_SEC_TO_SECS(23, 19, 0),
        HOUR_MIN_SEC_TO_SECS(24, 19, 0)
    };

    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    u32 now_sec = mTRC_RTC_TIME_SECONDS(rtc_time);
    u32 depart_time;
    int i = 0;

    while (TRUE) {
        if (time_table[i] >= now_sec) {
            depart_time = time_table[i] - HOUR_MIN_SEC_TO_SECS(0, 4, 10);
            break;
        }
        i++;
    }

    Common_Set(train_day, rtc_time->day);
    return depart_time;
}

static int mTRC_time_check() {
    u32 now_sec = mTRC_RTC_TIME_SECONDS(Common_GetPointer(time.rtc_time));
    return now_sec >= Common_Get(train_start_timer);
}

static void mTRC_mati_init() {
    xyz_t pos;

    Common_Set(train_action, mTRC_ACTION_WAIT_STOPPED);
    Common_Set(train_flag, TRUE);
    Common_Set(train_signal, TRUE);
    Common_Set(train_control_state, 1);
    Common_Set(train_last_control_state, 1);

    pos.x = 2367.0f;
    pos.z = 740.0f;
#if VERSION >= VER_GAFU01_00
    pos.y = mRF_CheckFieldStep3() ? 300 : 180;
#else
    pos.y = 180.0f;
#endif
    Common_Set(train_position, pos);
}

static void mTRC_demo_init() {
    xyz_t pos;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    Common_Set(train_action, mTRC_ACTION_BEGIN_SLOWDOWN);
    Common_Set(train_speed, mTRC_SLOW_SPEED);
    Common_Set(train_flag, TRUE);
    Common_Set(train_start_timer, mTRC_RTC_TIME_SECONDS(rtc_time) - HOUR_MIN_SEC_TO_SECS(0, 4, 50));
    Common_Set(train_day, Common_Get(time.rtc_time.day));
    Common_Set(train_control_state, 0);
    Common_Set(train_last_control_state, 0);

    pos.x = 2037.0f;
    pos.z = 740.0f;
#if VERSION >= VER_GAFU01_00
    pos.y = mRF_CheckFieldStep3() ? 300 : 180;
#else
    pos.y = 180.0f;
#endif
    Common_Set(train_position, pos);
}

static void mTRC_call_init() {
    xyz_t pos;

    Common_Set(train_action, mTRC_ACTION_BEGIN_SLOWDOWN);
    Common_Set(train_speed, 0.0f);
    Common_Set(train_flag, TRUE);
    Common_Set(train_control_state, 1);
    Common_Set(train_last_control_state, 1);

    pos.x = 1904.0f;
    pos.z = 740.0f;
#if VERSION >= VER_GAFU01_00
    pos.y = mRF_CheckFieldStep3() ? 300 : 180;
#else
    pos.y = 180.0f;
#endif
    Common_Set(train_position, pos);
}

static void mTRC_norm_init() {
    xyz_t pos;

    Common_Set(train_action, mTRC_ACTION_SPAWN_MOVING);
    Common_Set(train_speed, 0.0f);
    Common_Set(train_flag, TRUE);
    Common_Set(train_control_state, 0);
    Common_Set(train_last_control_state, 0);

    pos.x = 320.0f;
    pos.z = 740.0f;
#if VERSION >= VER_GAFU01_00
    pos.y = mRF_CheckFieldStep3() ? 300 : 180;
#else
    pos.y = 180.0f;
#endif
    Common_Set(train_position, pos);
}

static int mTRC_schedule(GAME_PLAY* play) {
    int res = -1;

    if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_START1) {
        if (Common_Get(train_action) == mTRC_ACTION_NONE) {
            mTRC_mati_init();
        }

        return -1;
    } else {
        switch (Common_Get(train_coming_flag)) {
            case 3: {
                Common_Set(train_coming_flag, 0);
                mTRC_demo_init();
                res = 0;
                break;
            }

            case 2: {
                if (!aTRC_area_check(play, Common_Get(train_position)) &&
                    Common_Get(train_action) >= mTRC_ACTION_SIGNAL_STARTING) {
                    mTRC_call_init();
                    res = 1;
                    break;
                }

                if (Common_Get(train_action) < mTRC_ACTION_SIGNAL_STARTING &&
                    Common_Get(train_action) != mTRC_ACTION_NONE) {
                    Common_Set(train_coming_flag, FALSE);
                    Common_Set(train_control_state, 1);
                    Common_Set(train_last_control_state, 1);
                    break;
                }

                if (Common_Get(train_action) == mTRC_ACTION_NONE) {
                    mTRC_call_init();
                    res = 1;
                    break;
                }
                break;
            }

            case 4: {
                break;
            }

            default: {
                if (Common_Get(train_action) == mTRC_ACTION_NONE && mEv_CheckArbeit() == FALSE && mTRC_time_check()) {
                    mTRC_norm_init();
                    res = 1;
                }
                break;
            }
        }
    }

    return res;
}

static void mTRC_trainControl(GAME_PLAY* play, int state) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    u8 signal = Common_Get(train_signal);
    u8 action = Common_Get(train_action);
    u8 timer = Common_Get(train_timer);
    u32 start_timer = Common_Get(train_start_timer);
    f32 speed = Common_Get(train_speed);
    xyz_t pos = Common_Get(train_position);
    int block_x;
    int block_z;
    int now_state = state;

    if (Common_Get(train_day) != rtc_time->day) {
        if (start_timer >= mTM_SECONDS_IN_DAY) {
            start_timer -= mTM_SECONDS_IN_DAY;
        }

        Common_Set(train_day, rtc_time->day);
    }

    switch (action) {
        case 0:
            break;
        case mTRC_ACTION_SPAWN_MOVING: {
            speed = mTRC_FAST_SPEED;
            mFI_Wpos2BlockNum(&block_x, &block_z, pos);

            if (block_x >= 2) {
                action = mTRC_ACTION_BEGIN_SLOWDOWN;
            }
            break;
        }

        case mTRC_ACTION_BEGIN_SLOWDOWN: {
            chase_f(&speed, mTRC_SLOW_SPEED, mTRC_SLOW_RATE);
            if (pos.x > 2165.0f) {
                action = mTRC_ACTION_BEGIN_STOP;
                speed = mTRC_SLOW_SPEED;
            }
            break;
        }

        case mTRC_ACTION_BEGIN_STOP: {
            chase_f(&speed, 0.0f, mTRC_STOP_RATE);
            if (fabsf(speed) < 0.008f) {
                signal = TRUE;
                timer = 48;
                action = mTRC_ACTION_SIGNAL_STOPPED;
                now_state = 2;
                speed = 0.0f;
            }
            break;
        }

        case mTRC_ACTION_SIGNAL_STOPPED: {
            if (timer == 0) {
                action = mTRC_ACTION_WAIT_STOPPED;
                start_timer += 310;
            } else {
                timer--;
            }
            break;
        }

        case mTRC_ACTION_WAIT_STOPPED: {
            if (Common_Get(train_control_state) != Common_Get(train_last_control_state)) {
                Common_Set(train_control_state, Common_Get(train_last_control_state));
                signal = FALSE;
                Common_Set(train_signal, FALSE);
            } else if (Common_Get(train_control_state) == 0 && mTRC_time_check()) {
                signal = FALSE;
                Common_Set(train_signal, FALSE);
            }

            if (signal == FALSE) {
                timer = 84;
                action = mTRC_ACTION_SIGNAL_STARTING;
            }
            break;
        }

        case mTRC_ACTION_SIGNAL_STARTING: {
            if (timer == 0) {
                timer = 180;
                action = mTRC_ACTION_BEGIN_PULL_OUT;
                now_state = 3;
            } else {
                timer--;
            }
            break;
        }

        case mTRC_ACTION_BEGIN_PULL_OUT: {
            chase_f(&speed, mTRC_SLOW_SPEED, mTRC_START_RATE);

            if (timer == 0) {
                action = mTRC_ACTION_SPEED_UP;
            } else {
                timer--;
            }
            break;
        }

        case mTRC_ACTION_SPEED_UP: {
            chase_f(&speed, mTRC_FAST_SPEED, mTRC_SPEEDUP_RATE);
            if (pos.x > 4400.0f) {
                start_timer = mTRC_get_depart_time();
                action = mTRC_ACTION_NONE;
                Common_Set(train_flag, FALSE);
                now_state = 4;
            }
            break;
        }
    }

    if (action != mTRC_ACTION_NONE) {
        ACTOR* train_actor = Actor_info_fgName_search(&play->actor_info, TRAIN0, ACTOR_PART_ITEM);
        if (Common_Get(train_flag) == FALSE && train_actor == NULL) {
            Common_Set(train_flag, TRUE);
        }

        pos.x += 0.5f * speed;
        mTRC_KishaStatusLevel(play, speed, pos);
    }

    if (now_state >= 0) {
        mTRC_KishaStatusTrg(now_state);
    }

    Common_Set(train_signal, signal);
    Common_Set(train_action, action);
    Common_Set(train_timer, timer);
    Common_Set(train_start_timer, start_timer);
    Common_Set(train_speed, speed);
    Common_Set(train_position, pos);
}

static void mTRC_trainSet(GAME_PLAY* play) {
    ACTOR* train_actor;
    ACTOR* caboose_actor;
    xyz_t pos = Common_Get(train_position);
    xyz_t xz_pos;
    xyz_t xyz_pos;

    if (Common_Get(field_type) != mFI_FIELDTYPE2_FG || !Common_Get(train_flag)) {
        return;
    } else if (Common_Get(clip).structure_clip != NULL) {
        f32 x = pos.x;
        xz_pos.x = pos.x;
        xz_pos.z = 740.0f;
        xz_pos.y = 0.0f;

        if (aTRC_area_check(play, xz_pos)) {
            train_actor = Actor_info_fgName_search(&play->actor_info, TRAIN0, ACTOR_PART_ITEM);
            if (train_actor == NULL) {
                /* spawn train actor since it doesn't exist */
                train_actor =
                    (ACTOR*)Common_Get(clip.structure_clip)->setup_actor_proc(&play->game, TRAIN0, -1, x, 740.0f);
                fflush(stdout);

                /* for whatever reason, train actor didn't spawn, so exit */
                if (train_actor == NULL) {
                    return;
                }
            } else {
                xyz_pos.x = xz_pos.x;
                xyz_pos.z = xz_pos.z;
                xyz_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(xyz_pos, 0.0f);

                xyz_t_move(&train_actor->world.position, &xyz_pos);
            }

            x -= 250.0f;
            caboose_actor = Actor_info_fgName_search(&play->actor_info, TRAIN1, ACTOR_PART_ITEM);
            if (caboose_actor == NULL) {
                caboose_actor =
                    (ACTOR*)Common_Get(clip.structure_clip)->setup_actor_proc(&play->game, TRAIN1, -1, x, 740.0f);
                if (caboose_actor == NULL) {
                    Actor_delete(train_actor);
                    return;
                }
            } else {
                xyz_pos.x = x;
                xyz_pos.z = 740.0f;
                xyz_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(xyz_pos, 0.0f);

                xyz_t_move(&caboose_actor->world.position, &xyz_pos);
            }

            Common_Set(train_flag, FALSE);

            train_actor->block_x = -1;
            train_actor->block_z = -1;
            train_actor->child_actor = caboose_actor;

            caboose_actor->block_x = -1;
            caboose_actor->block_z = -1;
            caboose_actor->parent_actor = train_actor;
        }
    }
}

extern void mTRC_init(GAME* game) {
    Common_Set(train_start_timer, mTRC_get_depart_time());
    Common_Set(train_coming_flag, 0);
    Common_Set(train_exists_flag, FALSE);
    Common_Set(train_control_state, 0);
    Common_Set(train_last_control_state, 0);
    Common_Set(train_signal, FALSE);
    Common_Set(train_action, 0);
    Common_Set(train_timer, 0);
    Common_Set(train_speed, 0.0f);
    Common_Set(train_position, ZeroVec);
    Common_Set(train_approaching_flag, FALSE);
    Common_Set(train_flag, FALSE);
}

extern void mTRC_move(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    int state;
    Common_Set(train_approaching_flag, FALSE);

    if (!mTRC_go_process() || player == NULL) {
        return;
    }

    state = mTRC_schedule(play);
    mTRC_trainControl(play, state);
    mTRC_trainSet(play);
}
