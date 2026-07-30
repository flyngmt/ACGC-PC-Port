#include "m_bgm.h"

#include "game.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_lib.h"
#include "m_melody.h"
#include "m_player_lib.h"

#define mBGMPs_FLAG_REMOVE (1 << 0)
#define mBGMPs_FLAG_UPDATE_VOLUME (1 << 1)
#define mBGMPs_FLAG_EXECUTE (1 << 2)
#define mBGMPs_FLAG_CROSSFADE (1 << 3)
#define mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR (1 << 4)
#define mBGMPs_FLAG_UPDATE_VOLUME_LEVEL (1 << 5)
#define mBGMPs_FLAG_SILENT (1 << 6)
#define mBGMPs_FLAG_FADEOUT (1 << 7)
#define mBGMPs_FLAG_LOST (1 << 8)

enum {
    mBGM_KATEGORIE_FANFARE,
    mBGM_KATEGORIE_WIPE,
    mBGM_KATEGORIE_QUIET,
    mBGM_KATEGORIE_DEMO,
    mBGM_KATEGORIE_HAPPENING,
    mBGM_KATEGORIE_QUIETROOM,
    mBGM_KATEGORIE_ROOM,
    mBGM_KATEGORIE_TIME,
    mBGM_KATEGORIE_QUIETFIELD,
    mBGM_KATEGORIE_FIELDSUDDENEV,
    mBGM_KATEGORIE_FIELDSCHEDEV,
    mBGM_KATEGORIE_FIELDNORM,

    mBGM_KATEGORIE_NUM
};

enum {
    mBGMForce_INFORM_0,
    mBGMForce_INFORM_1,
    mBGMForce_INFORM_2,
    mBGMForce_INFORM_3,
    mBGMForce_INFORM_4,
    mBGMForce_INFORM_5,
    mBGMForce_INFORM_6,
    mBGMForce_INFORM_7,

    mBGMForce_INFORM_NUM
};

typedef struct bgm_elem_s {
    u8 bgm_num;
    u8 _pad0;
    u16 _pad1;
    u16 stop_type0;
    u16 stop_type1;
} mBGMElem;

typedef struct bgm_clock_s {
    u32 now;
    u32 before;
} mBGMClock;

typedef struct bgm_demo_s {
    mBGMElem elem;
    u8 make_flag;
    u8 delete_flag;
    u16 _pad;
} mBGMDemo;

typedef struct bgm_room_s {
    mBGMElem elem;
    u8 make_flag;
    u8 delete_flag;
    u8 shop_fadeout_flag;
    u8 _pad;
    u32 shop_close_time0;
    u32 shop_close_time1;
} mBGMRoom;

typedef struct bgm_time_s mBGMTime;

typedef void (*mBGMTime_MOVE_PROC)(mBGMTime*, GAME*);

struct bgm_time_s {
    mBGMTime_MOVE_PROC move_proc;
    u8 new_year_ev_flag;
    u8 _pad;
};

typedef struct bgm_field_sudden_ev_s {
    u32 flag;
    u32 old_flag;
} mBGMFieldSuddenEv;

typedef struct bgm_field_schedule_ev_info_s {
    u32 flag;
    int attr;
    int old_attr;
} mBGMFieldSchedEv_Info;

typedef struct bgm_field_schedule_ev_s {
    mBGMFieldSchedEv_Info info[24]; // every hour has its own info
} mBGMFieldSchedEv;

typedef struct bgm_field_normal_s {
    mBGMElem elem;
    u8 make_flag;
    u8 delete_flag;
    u16 _pad;
} mBGMFieldNorm;

typedef struct bgm_ps_s {
    mBGMElem elem;
    int kategorie;
    s16 counter;
    u16 cf_flags;
    u8 priority;
    u8 _pad;
} mBGMPs;

typedef struct bgm_ps_comp_stop_s {
    u8 req_flag;
    u16 type;
    u8 _pad;
} mBGMPsComp_Stop;

typedef struct bgm_ps_comp_start_s {
    u8 req_flag;
    u8 bgm_num;
    u8 flags;
    u8 _pad;
} mBGMPsComp_Start;

typedef struct bgm_ps_comp_volume_s {
    f32 main_volume;
    u16 main_volume_move_ctr;
    u8 main_req_flag;
    u8 _pad0;

    f32 ps_volume;
    u16 ps_volume_move_ctr;
    u8 ps_req_flag;
    u8 _pad1;

    f32 fishing_volume;
    u16 fishing_volume_move_ctr;
    u8 fishing_req_flag;
    u8 _pad2;

    f32 collect_insects_volume;
    u16 collect_insects_volume_move_ctr;
    u8 collect_insects_req_flag;
    u8 _pad3;

    f32 talk_volume;
    u8 talk_req_flag;
    u8 _pad4;

    f32 boat_volume;
    u8 boat_req_flag;
    u8 _pad5;

    f32 pause_volume;
    u16 pause_volume_move_ctr;
    u8 pause_req_flag;
    u8 _pad6;
} mBGMPsComp_Volume;

typedef struct bgm_ps_comp_pause_s {
    u8 req_flag;
    u8 mode;
    u16 _pad;
} mBGMPsComp_Pause;

typedef struct bgm_ps_comp_md_player_pos_s {
    u8 req_flag;
    u8 make_flag;
    u8 delete_flag;
    u8 move_flag;
    xyz_t pos;
    u16 angle;
    u16 md_type_no;
    JaudioObjectId ongen_no;
} mBGMPsComp_MDPlayerPos;

#define mBGM_BGMPs_NUM 14

typedef struct bgm_ps_comp_arm_s {
    u8 req_flag;
    u8 arm_state;
    u16 _pad;
} mBGMPsComp_Arm;

typedef struct bgm_ps_comp_museum_s {
    u8 req_flag;
    u8 type;
    u16 _pad;
} mBGMPsComp_Museum;

typedef struct bgm_ps_comp_s {
    mBGMPs ps[mBGM_BGMPs_NUM];
    int ps_num;
    int fishing_state;
    int collect_insects_state;
    int talk_state;
    int boat_state;
    int pause_state;
    mBGMPsComp_Stop stop;
    mBGMPsComp_Start start;
    mBGMPsComp_Volume volume;
    mBGMPsComp_Pause pause;
    mBGMPsComp_MDPlayerPos md;
    mBGMPsComp_Arm arm;
    mBGMPsComp_Museum museum;
} mBGMPsComp;

typedef struct bgm_force_s {
    int inform;
    u8 flag;
    int room_nonstop;
} mBGMForce;

typedef struct bgm_s {
    mBGMClock clock;
    mBGMDemo demo;
    mBGMRoom room;
    mBGMTime time;
    mBGMFieldSuddenEv field_sudden_ev;
    mBGMFieldSchedEv field_sched_ev;
    mBGMFieldNorm field_norm;
    mBGMPsComp ps_comp;
    mBGMForce force;
} mBGM;

static mBGM M_bgm;

static int mBGM_check_MD(u8 bgm_num) {
    int res = FALSE;

    if ((bgm_num >= 0x80 && bgm_num <= 0xB3) || (bgm_num >= 0xB4 && bgm_num <= 0xB6)) {
        res = TRUE;
    }

    return res;
}

static int mBGM_check_ignore_talk_volume(u8 bgm_num) {
    /* TODO: defines/enums for these ids */
    static const u8 bgm_data[44] = { 40,  73,  68,  74,  76,  75,  49,  50,  71,  64,  66,  78,  122, 125, 92,
                                     93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107,
                                     108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121 };

    const u8* bgm_data_p = bgm_data;
    int i;

    for (i = 0; i < ARRAY_COUNT(bgm_data); i++) {
        if (bgm_num == *bgm_data_p) {
            return TRUE;
        }

        bgm_data_p++;
    }

    return FALSE;
}

static int mBGM_check_ignore_collect_insects_volume(u8 bgm_num) {
    if (bgm_num == 40) {
        return TRUE;
    }

    return FALSE;
}

static void mBGMElem_default_set(mBGMElem* elem) {
    static mBGMElem default_data = { 127, 0, 0, 0x168, 0x168 };

    bcopy(&default_data, elem, sizeof(mBGMElem));
}

/* mBGMClock */

#define mBGMClock_CHK_ss (((1 << 6) - 1) << 0)
#define mBGMClock_CHK_mm (((1 << 6) - 1) << 6)
#define mBGMClock_CHK_hh (((1 << 5) - 1) << 12)
#define mBGMClock_CHK_DD (((1 << 5) - 1) << 17)
#define mBGMClock_CHK_MM (((1 << 4) - 1) << 22)
#define mBGMClock_CHK_ALL (mBGMClock_CHK_MM | mBGMClock_CHK_DD | mBGMClock_CHK_hh | mBGMClock_CHK_mm | mBGMClock_CHK_ss)

#define mBGMClock_MONTH_TO_BGM_MONTH(month) (((month) << 22) & 0x03C00000)
#define mBGMClock_DAY_TO_BGM_DAY(day) (((day) << 17) & 0x3E0000)
#define mBGMClock_HOUR_TO_BGM_HOUR(hour) (((hour) << 12) & 0x1F000)
#define mBGMClock_MIN_TO_BGM_MIN(min) (((min) << 6) & 0xFC0)
#define mBGMClock_SEC_TO_BGM_SEC(sec) (((sec) << 0) & 0x3F)

#define mBGMClock_TIME_TO_BGM_TIME(month, day, hour, min, sec)                                                 \
    ((mBGMClock_MONTH_TO_BGM_MONTH(month) | mBGMClock_DAY_TO_BGM_DAY(day) | mBGMClock_HOUR_TO_BGM_HOUR(hour) | \
      mBGMClock_MIN_TO_BGM_MIN(min) | mBGMClock_SEC_TO_BGM_SEC(sec)))

#define mBGMClock_RTCTIME_TO_BGM_TIME(time) \
    (mBGMClock_TIME_TO_BGM_TIME((time).month, (time).day, (time).hour, (time).min, (time).sec))

#define mBGMClock_TIME_TO_SHOP_CLOSE_TIME(time)                                       \
    (mBGMClock_HOUR_TO_BGM_HOUR((time).hour) | mBGMClock_MIN_TO_BGM_MIN((time).min) | \
     mBGMClock_SEC_TO_BGM_SEC((time).sec))

static int mBGMClock_after_time_check(mBGMClock* clock, u32 check_time, u32 check_mask) {
    u32 t_now = clock->now & check_mask;
    u32 t_check = check_time & check_mask;

    if (t_now >= t_check) {
        return TRUE;
    }

    return FALSE;
}

static int mBGMClock_over_time_check(mBGMClock* clock, u32 check_time, u32 check_mask) {
    u32 t_now = clock->now & check_mask;
    u32 t_before = clock->before & check_mask;
    u32 t_check = check_time & check_mask;

    if (t_now >= t_before) {
        int res = FALSE;
        if (t_check > t_before && t_check <= t_now) {
            res = TRUE;
        }

        return res;
    } else {
        int res = FALSE;
        if (t_check > t_before || t_check <= t_now) {
            res = TRUE;
        }

        return res;
    }
}

static int mBGMClock_range_time_check(mBGMClock* clock, u32 check_time0, u32 check_time1, u32 check_mask) {
    u32 t_now = clock->now & check_mask;
    u32 t_check0 = check_time0 & check_mask;
    u32 t_check1 = check_time1 & check_mask;
    int res;

    if (t_check1 >= t_check0) {
        res = FALSE;
        if (t_now >= t_check0 && t_now < t_check1) {
            res = TRUE;
        }

        return res;
    } else {
        res = FALSE;
        if (t_now >= t_check0 || t_now < t_check1) {
            res = TRUE;
        }

        return res;
    }
}

static void mBGMClock_now_set(mBGMClock* clock) {
    clock->before = clock->now;
    clock->now = mBGMClock_RTCTIME_TO_BGM_TIME(Common_Get(time.rtc_time));
}

static void mBGMClock_move(mBGMClock* clock, GAME* game) {
    mBGMClock_now_set(clock);
}

static void mBGMClock_ct(mBGMClock* clock) {
    bzero(clock, sizeof(mBGMClock));
    mBGMClock_now_set(clock);
    clock->before = clock->now;
}

/* mBGMDemo */

static void mBGMDemo_make_scene_bgm(mBGMDemo* demo) {
    if (demo->elem.bgm_num == 127 && mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();
        u8 bgm_num;

        switch (field_id) {
            case mFI_FIELD_DEMO_STARTDEMO:
            case mFI_FIELD_DEMO_STARTDEMO2:
                bgm_num = 42;
                break;

            case mFI_FIELD_DEMO_STARTDEMO3:
                bgm_num = 123;
                break;

            case mFI_FIELD_DEMO_PLAYERSELECT:
                if (Save_Get(scene_no) == SCENE_PLAYERSELECT_SAVE) {
                    bgm_num = 46;
                } else {
                    bgm_num = 43;
                }
                break;

            default:
                bgm_num = 127;
                break;
        }

        if (bgm_num != 127) {
            mBGMElem_default_set(&demo->elem);
            demo->elem.bgm_num = bgm_num;
            mBGMPsComp_make_ps_demo(bgm_num, 0x168);
        }
    }
}

static void mBGMDemo_delete_scene_bgm(mBGMDemo* demo) {
    if (demo->elem.bgm_num != 127) {
        mBGMPsComp_delete_ps_demo(demo->elem.bgm_num, 0x168);
        demo->elem.bgm_num = 127;
    }
}

static void mBGMDemo_move(mBGMDemo* demo, GAME* game) {
    if (demo->delete_flag) {
        mBGMDemo_delete_scene_bgm(demo);
    }

    if (demo->make_flag) {
        mBGMDemo_make_scene_bgm(demo);
    }

    demo->make_flag = FALSE;
    demo->delete_flag = FALSE;
}

static void mBGMDemo_scene_bgm_make_req() {
    M_bgm.demo.make_flag = TRUE;
}

static void mBGMDemo_scene_bgm_delete_req() {
    M_bgm.demo.delete_flag = TRUE;
}

static void mBGMDemo_ct(mBGMDemo* demo) {
    bzero(demo, sizeof(mBGMDemo));
    mBGMElem_default_set(&demo->elem);
}

/* mBGMRoom */

static void mBGMRoom_shop_close_time_set(mBGMRoom* room) {
    if (mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();

        if (field_id == mFI_FIELD_ROOM_SHOP0 || field_id == mFI_FIELD_ROOM_SHOP1 || field_id == mFI_FIELD_ROOM_SHOP2 ||
            field_id == mFI_FIELD_ROOM_SHOP3_1 || field_id == mFI_FIELD_ROOM_SHOP3_2) {
            lbRTC_time_c time;

            bzero(&time, sizeof(lbRTC_time_c));
            time.hour = mSP_GetShopCloseTime_Bgm();

            lbRTC_Sub_mm(&time, 5);
            room->shop_close_time1 = mBGMClock_TIME_TO_SHOP_CLOSE_TIME(time);

            lbRTC_Sub_ss(&time, 5);
            room->shop_close_time0 = mBGMClock_TIME_TO_SHOP_CLOSE_TIME(time);
        }
    }
}

static u8 mBGMRoom_make_scene_bgm_shop_get(mBGMRoom* room, mActor_name_t field_id) {
    u8 bgm_num;

    if (mEv_CheckRealArbeit() == FALSE &&
        mBGMClock_after_time_check(&M_bgm.clock, room->shop_close_time1,
                                   mBGMClock_CHK_hh | mBGMClock_CHK_mm | mBGMClock_CHK_ss)) {
        /* Play 'almost closing' music */
        if (field_id == mFI_FIELD_ROOM_SHOP0) {
            bgm_num = 79;
        } else if (field_id == mFI_FIELD_ROOM_SHOP1) {
            bgm_num = 80;
        } else if (field_id == mFI_FIELD_ROOM_SHOP2) {
            bgm_num = 81;
        } else {
            bgm_num = 82;
        }
    } else {
        /* Play normal music */
        if (field_id == mFI_FIELD_ROOM_SHOP0) {
            bgm_num = 44;
        } else if (field_id == mFI_FIELD_ROOM_SHOP1) {
            bgm_num = 37;
        } else if (field_id == mFI_FIELD_ROOM_SHOP2) {
            bgm_num = 38;
        } else {
            bgm_num = 39;
        }
    }

    return bgm_num;
}

static void mBGMRoom_make_scene_bgm(mBGMRoom* room) {
    if (room->elem.bgm_num == 127 && mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();
        u8 bgm_num;

        switch (field_id) {
            case mFI_FIELD_ROOM_SHOP0:
            case mFI_FIELD_ROOM_SHOP1:
            case mFI_FIELD_ROOM_SHOP2:
            case mFI_FIELD_ROOM_SHOP3_1:
            case mFI_FIELD_ROOM_SHOP3_2:
                bgm_num = mBGMRoom_make_scene_bgm_shop_get(room, field_id);
                break;

            case mFI_FIELD_ROOM_BROKER_SHOP:
                bgm_num = 25;
                break;

            case mFI_FIELD_ROOM_POST_OFFICE:
                if (Common_Get(post_girl_npc_type) != 0) {
                    bgm_num = 62;
                } else {
                    bgm_num = 41;
                }
                break;

            case mFI_FIELD_ROOM_POLICE_BOX:
                bgm_num = 45;
                break;

            case mFI_FIELD_ROOM_BUGGY:
                bgm_num = 26;
                break;

            case mFI_FIELD_ROOM_KAMAKURA:
                bgm_num = 77;
                break;

            case mFI_FIELD_ROOM_TENT:
                bgm_num = 254;
                break;

            case mFI_FIELD_ROOM_MUSEUM_ENTRANCE:
            case mFI_FIELD_ROOM_MUSEUM_PAINTING:
            case mFI_FIELD_ROOM_MUSEUM_FOSSIL:
            case mFI_FIELD_ROOM_MUSEUM_INSECT:
            case mFI_FIELD_ROOM_MUSEUM_FISH:
                bgm_num = 88;
                break;

            case mFI_FIELD_ROOM_NEEDLEWORK:
                bgm_num = 89;
                break;

            case mFI_FIELD_ROOM_LIGHTHOUSE:
                bgm_num = 90;
                break;

            default:
                bgm_num = 127;
                break;
        }

        if (bgm_num != 127) {
            mBGMElem_default_set(&room->elem);
            room->elem.bgm_num = bgm_num;
            mBGMPsComp_make_ps_room(bgm_num, 0x168);
        }
    }
}

static void mBGMRoom_delete_scene_bgm(mBGMRoom* room) {
    if (room->elem.bgm_num != 127) {
        mBGMPsComp_delete_ps_room(room->elem.bgm_num, 0x168);
        room->elem.bgm_num = 127;
    }
}

static void mBGMPsComp_make_ps_quietRoom(u16 stop_type);
static void mBGMPsComp_delete_ps_quietRoom();

static int mBGMRoom_shop_close_check(mBGMRoom* room) {
    int res = FALSE;
    int time1_flag = FALSE;
    int fadeout_flag = FALSE;
    int temp_flag2;

    if (mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();

        if (field_id == mFI_FIELD_ROOM_SHOP0 || field_id == mFI_FIELD_ROOM_SHOP1 || field_id == mFI_FIELD_ROOM_SHOP2 ||
            field_id == mFI_FIELD_ROOM_SHOP3_1 || field_id == mFI_FIELD_ROOM_SHOP3_2) {
            int real_arbeit = mEv_CheckRealArbeit();

            temp_flag2 = FALSE;
            if (real_arbeit == FALSE &&
                mBGMClock_range_time_check(&M_bgm.clock, room->shop_close_time0, room->shop_close_time1,
                                           mBGMClock_CHK_hh | mBGMClock_CHK_mm | mBGMClock_CHK_ss)) {
                temp_flag2 = TRUE;
            }
            fadeout_flag = temp_flag2;

            time1_flag = FALSE;
            if (real_arbeit == FALSE &&
                mBGMClock_over_time_check(&M_bgm.clock, room->shop_close_time1,
                                          mBGMClock_CHK_hh | mBGMClock_CHK_mm | mBGMClock_CHK_ss)) {
                time1_flag = TRUE;
            }

            res = time1_flag;
        }
    }

    if (fadeout_flag && room->shop_fadeout_flag == FALSE) {
        mBGMPsComp_make_ps_quietRoom(0x13DE);
        room->shop_fadeout_flag = TRUE;
    } else if (!fadeout_flag && room->shop_fadeout_flag) {
        mBGMPsComp_delete_ps_quietRoom();
        room->shop_fadeout_flag = FALSE;
    }

    return res;
}

static void mBGMRoom_move(mBGMRoom* room, GAME* game) {
    if (mBGMRoom_shop_close_check(room)) {
        room->delete_flag = TRUE;
        room->make_flag = TRUE;
    }

    if (room->delete_flag) {
        mBGMRoom_delete_scene_bgm(room);
    }

    if (room->make_flag) {
        mBGMRoom_make_scene_bgm(room);
    }

    room->make_flag = FALSE;
    room->delete_flag = FALSE;
}

static void mBGMRoom_scene_bgm_make_req() {
    M_bgm.room.make_flag = TRUE;
}

static void mBGMRoom_scene_bgm_delete_req() {
    M_bgm.room.delete_flag = TRUE;
}

static void mBGMRoom_ct(mBGMRoom* room) {
    bzero(room, sizeof(mBGMRoom));
    mBGMElem_default_set(&room->elem);
}

/* mBGMTime */

static void mBGMTime_signal_melody(mBGMTime* time, GAME* game) {
    static u8 signal_melody_buf[mMld_MELODY_LEN];

    if (mEv_CheckFirstIntro() == FALSE && mEv_CheckTitleDemo() != mEv_TITLEDEMO_STAFFROLL && mFI_CheckFieldData() &&
        mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELD_DEMO_STARTDEMO && time->new_year_ev_flag == FALSE &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETON_BOAT &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETON_BOAT_SITDOWN &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETON_BOAT_WAIT &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETON_BOAT_WADE &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETOFF_BOAT_STANDUP &&
        mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_GETOFF_BOAT) {
        mMld_GetMelody(signal_melody_buf);

        if (mFI_CheckInIsland()) {
            sAdo_Inst(0xFE, signal_melody_buf);
        } else {
            sAdo_Inst(0xFF, signal_melody_buf);
        }
    }
}

static int mBGMTime_silent_check(mBGMTime* time) {
    if (time->new_year_ev_flag) {
        return FALSE;
    }

    /* Silent between XX:59:52 and XX:00:16 */
    return mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_MIN_TO_BGM_MIN(59) | mBGMClock_SEC_TO_BGM_SEC(52),
                                      mBGMClock_MIN_TO_BGM_MIN(0) | mBGMClock_SEC_TO_BGM_SEC(16),
                                      mBGMClock_CHK_mm | mBGMClock_CHK_ss);
}

static void mBGMTime_new_year_ev_flag_set() {
    M_bgm.time.new_year_ev_flag = TRUE;
}

static void mBGMTime_new_year_ev_flag_clr() {
    M_bgm.time.new_year_ev_flag = FALSE;
}

static void mBGMTime_move_wait(mBGMTime* time, GAME* game);
static void mBGMTime_move_change(mBGMTime* time, GAME* game);
static void mBGMPsComp_make_ps_time();

static void mBGMTime_move_wait(mBGMTime* time, GAME* game) {
    if (mBGMTime_silent_check(time)) {
        mBGMPsComp_make_ps_time();
        time->move_proc = &mBGMTime_move_change;
    }
}

static void mBGMPsComp_delete_ps_time();

static void mBGMTime_move_change(mBGMTime* time, GAME* game) {
    /* Wait until XX:00:00 and then play the town tune melody */
    if (mBGMClock_over_time_check(&M_bgm.clock, 0, mBGMClock_CHK_mm | mBGMClock_CHK_ss)) {
        mBGMTime_signal_melody(time, game);
    }

    if (mBGMTime_silent_check(time) == FALSE) {
        mBGMPsComp_delete_ps_time();
        time->move_proc = &mBGMTime_move_wait;
    }
}

static void mBGMTime_move(mBGMTime* time, GAME* game) {
    (*time->move_proc)(time, game);
}

static void mBGMTime_ct(mBGMTime* time) {
    bzero(time, sizeof(mBGMTime));
    time->move_proc = &mBGMTime_move_wait;
}

/* mBGMFieldSuddenEv */

static int mBGMFieldSuddenEv_flag_check_island(mBGMFieldSuddenEv* field_sudden_ev, GAME* game) {
    return mFI_CheckInJustIslandOutdoor();
}

static int mBGMFieldSuddenEv_flag_check_arbeit(mBGMFieldSuddenEv* field_sudden_ev, GAME* game) {
    return mEv_CheckFirstJob();
}

typedef int (*mBGMFieldSuddenEv_EV_CHK_PROC)(mBGMFieldSuddenEv*, GAME*);

static void mBGMFieldSuddenEv_flag_set(mBGMFieldSuddenEv* field_sudden_ev, GAME* game) {
    static mBGMFieldSuddenEv_EV_CHK_PROC ev_chk[] = { &mBGMFieldSuddenEv_flag_check_island, NULL,
                                                      &mBGMFieldSuddenEv_flag_check_arbeit };

    field_sudden_ev->old_flag = field_sudden_ev->flag;
    field_sudden_ev->flag = 0;

    if (mFI_CheckFieldData() && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG) {
        int i = 0;
        u32 mask = 1;

        for (i; i < 3; i++) {
            if (ev_chk[i] != NULL && (*ev_chk[i])(field_sudden_ev, game) != FALSE) {
                field_sudden_ev->flag |= mask;
            }

            mask <<= 1;
        }
    }
}

static void mBGMFieldSuddenEv_ps_compose(mBGMFieldSuddenEv* field_sudden_ev, GAME* game) {
    static u8 bgm_num_data[3] = { 91, 127, 52 };
    int now;
    int old;
    int i = 0;
    int mask = 1;

    for (i; i < 3; i++) {
        now = (field_sudden_ev->flag & mask) != 0;
        old = (field_sudden_ev->old_flag & mask) != 0;

        if (!now && old) {
            mBGMPsComp_delete_ps_fieldSuddenEv(bgm_num_data[i], 0x168);
        }

        if (now && !old) {
            mBGMPsComp_make_ps_fieldSuddenEv(bgm_num_data[i], 0x168, i);
        }

        mask <<= 1;
    }
}

static void mBGMFieldSuddenEv_move(mBGMFieldSuddenEv* field_sudden_ev, GAME* game) {
    mBGMFieldSuddenEv_flag_set(field_sudden_ev, game);
    mBGMFieldSuddenEv_ps_compose(field_sudden_ev, game);
}

static void mBGMFieldSuddenEv_ct(mBGMFieldSuddenEv* field_sudden_ev) {
    bzero(field_sudden_ev, sizeof(mBGMFieldSuddenEv));
}

/* mBGMFieldSchedEv */

static int mbgm_pattern_data[3][3] = { { 2, 2, 2 }, { 0, 1, 2 }, { 0, 0, 2 } };

#define mBGMEventArea_ALL 0   /* Happens everywhere */
#define mBGMEventArea_BLOCK 1 /* Happens at a specific block */

enum {
    mBGMFieldSchedEv_EVENT_SILENCE_0,
    mBGMFieldSchedEv_EVENT_FIREWORKS,
    mBGMFieldSchedEv_EVENT_HALLOWEEN,
    mBGMFieldSchedEv_EVENT_TOY_DAY,
    mBGMFieldSchedEv_EVENT_CHERRY_BLOSSOM_FESTIVAL,
    mBGMFieldSchedEv_EVENT_MORNING_AEROBICS,
    mBGMFieldSchedEv_EVENT_HARVEST_MOON_13,
    mBGMFieldSchedEv_EVENT_HARVEST_FESTIVAL,
    mBGMFieldSchedEv_EVENT_SPORTS_FAIR_AEROBICS,
    mBGMFieldSchedEv_EVENT_SPORTS_FAIR_FOOT_RACE,
    mBGMFieldSchedEv_EVENT_SPORTS_FAIR_BALL_TOSS,
    mBGMFieldSchedEv_EVENT_SPORTS_FAIR_TUG_OF_WAR,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_1,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_2,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_3,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_4,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_5,
    mBGMFieldSchedEv_EVENT_COUNTDOWN_6,
    mBGMFieldSchedEv_EVENT_NEW_YEARS,
    mBGMFieldSchedEv_EVENT_HOTARU,
    mBGMFieldSchedEv_EVENT_NEWYEAR01,
    mBGMFieldSchedEv_EVENT_NEWYEAR02,
    mBGMFieldSchedEv_EVENT_GROUNDHOG_DAY,
    mBGMFieldSchedEv_EVENT_METEOR_SHOWER,

    mBGMFieldSchedEv_EVENT_NUM
};

typedef struct bgm_event_data_s {
    s16 event_type;
    u8 bgm_num;
    u8 event_area;
    u32 block_type;
} mBGMEventData;

static mBGMEventData mbgm_event_data[mBGMFieldSchedEv_EVENT_NUM] = {
    { -1, 127, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { mEv_EVENT_FIREWORKS_SHOW, 55, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { mEv_EVENT_HALLOWEEN, 53, mBGMEventArea_ALL, mRF_BLOCKKIND_NONE },
    { mEv_EVENT_TALK_TOY_DAY, 54, mBGMEventArea_ALL, mRF_BLOCKKIND_NONE },
    { mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL, 56, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_MORNING_AEROBICS, 27, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_HARVEST_MOON_FESTIVAL, 30, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { mEv_EVENT_HARVEST_FESTIVAL, 253, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_SPORTS_FAIR_AEROBICS, 27, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 28, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_SPORTS_FAIR_BALL_TOSS, 29, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 60, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, 31, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { -1, 32, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { -1, 33, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { -1, 34, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { -1, 35, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { -1, 57, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL },
    { mEv_EVENT_NEW_YEARS_DAY, 59, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { -1, 255, mBGMEventArea_ALL, mRF_BLOCKKIND_NONE },
    { -1, 36, mBGMEventArea_ALL, mRF_BLOCKKIND_NONE },
    { -1, 61, mBGMEventArea_ALL, mRF_BLOCKKIND_NONE },
    { mEv_EVENT_GROUNDHOG_DAY, 251, mBGMEventArea_BLOCK, mRF_BLOCKKIND_SHRINE },
    { mEv_EVENT_METEOR_SHOWER, 250, mBGMEventArea_BLOCK, mRF_BLOCKKIND_POOL }
};

enum {
    mBGM_BL_ATTR_INACTIVE,
    mBGM_BL_ATTR_NEARBY,
    mBGM_BL_ATTR_ACTIVE,

    mBGM_BL_ATTR_NUM
};

static int mBGMFieldSchedEv_bl_attr_get(int bx, int bz, int area, u32 block_type) {
    int attr = mBGM_BL_ATTR_INACTIVE;

    if (area == mBGMEventArea_ALL) {
        attr = mBGM_BL_ATTR_ACTIVE;
    } else if (block_type != mRF_BLOCKKIND_NONE) {
        int ev_bx;
        int ev_bz;

        if (mFI_BlockKind2BkNum(&ev_bx, &ev_bz, block_type)) {
            int d_bx = ev_bx - bx;
            int d_bz = ev_bz - bz;

            if (d_bx == 0 && d_bz == 0) {
                attr = mBGM_BL_ATTR_ACTIVE;
            } else if (area == mBGMEventArea_BLOCK) {
                d_bx = ABS(d_bx);
                d_bz = ABS(d_bz);

                if ((d_bx == 0 && d_bz == 1) || (d_bx == 1 && d_bz == 0)) {
                    attr = mBGM_BL_ATTR_NEARBY;
                }
            }
        }
    }

    return attr;
}

static int mBGMFieldSchedEv_bl_attr_evdata_get(mBGMEventData* data, GAME* game) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
    int attr = mBGM_BL_ATTR_NUM;

    if (player != NULL) {
        int not_wading = mFI_CheckPlayerWade(mFI_WADE_NONE) || mFI_CheckPlayerWade(mFI_WADE_END);
        int pos_valid;
        int bx;
        int bz;

        if (not_wading) {
            int inform = M_bgm.force.inform;

            if (inform == mBGMForce_INFORM_3 || inform == mBGMForce_INFORM_4 || inform == mBGMForce_INFORM_5 ||
                inform == mBGMForce_INFORM_6) {
                xyz_t original_pos;

                xyz_t_move_s_xyz(&original_pos, &Common_Get(event_door_data).exit_position);
                pos_valid = mFI_Wpos2BlockNum(&bx, &bz, original_pos);
            } else {
                pos_valid = mFI_Wpos2BlockNum(&bx, &bz, player->actor_class.world.position);
            }
        } else {
            pos_valid = mFI_GetNextBlockNum(&bx, &bz);
        }

        if (pos_valid) {
            attr = mBGMFieldSchedEv_bl_attr_get(bx, bz, data->event_area, data->block_type);
        }
    }

    return attr;
}

static void mBGMFieldSchedEv_Info_old_copy(mBGMFieldSchedEv_Info* sched_ev_info) {
    if ((sched_ev_info->flag & 1)) {
        sched_ev_info->flag |= 2;
    } else {
        sched_ev_info->flag &= ~2;
    }

    if ((sched_ev_info->flag & 4)) {
        sched_ev_info->flag |= 8;
    } else {
        sched_ev_info->flag &= ~8;
    }

    sched_ev_info->old_attr = sched_ev_info->attr;
}

static void mBGMFieldSchedEv_Info_ev_now_set_standard(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                      GAME* game, int ev_start_flag) {
    if (ev_start_flag || (sched_ev_info->flag & 1)) {
        if (mEv_check_status(data->event_type, mEv_STATUS_ACTIVE)) {
            sched_ev_info->flag |= 1;
        } else {
            sched_ev_info->flag &= ~1;
        }
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_Silence_0(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                       GAME* game, int ev_start_flag) {
    int event_now = FALSE;

    if ((sched_ev_info->flag & 4) &&
        mBGMClock_over_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 59, 0),
                                  mBGMClock_CHK_ALL) &&
        mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[mBGMFieldSchedEv_EVENT_SILENCE_0], game) ==
            mBGM_BL_ATTR_ACTIVE) {
        sched_ev_info->flag |= 0x10;
    }

    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 59, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0), mBGMClock_CHK_ALL)) {
        if ((sched_ev_info->flag & 0x10)) {
            if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_PLAYSOUND)) {
                event_now = TRUE;
            }
        } else {
            event_now = TRUE;
        }
    } else {
        sched_ev_info->flag &= ~0x10;
    }

    if (event_now) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_1(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE) &&
        mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 30, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_2(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE) &&
        mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 30, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 50, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_3(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE) &&
        mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 50, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 55, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_4(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE) &&
        mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 55, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_5(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    int event_now = FALSE;

    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0), mBGMClock_CHK_ALL)) {
        if ((sched_ev_info->flag & 4) &&
            mBGMClock_over_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                      mBGMClock_CHK_MM | mBGMClock_CHK_DD | mBGMClock_CHK_hh | mBGMClock_CHK_mm |
                                          mBGMClock_CHK_ss) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[mBGMFieldSchedEv_EVENT_COUNTDOWN_5], game) !=
                mBGM_BL_ATTR_INACTIVE) {
            sched_ev_info->flag |= 0x20;
        }

        if ((sched_ev_info->flag & 0x20) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[mBGMFieldSchedEv_EVENT_COUNTDOWN_5], game) ==
                mBGM_BL_ATTR_INACTIVE) {
            sched_ev_info->flag &= ~0x20;
        }

        if ((sched_ev_info->flag & 0x20) && mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE)) {
            event_now = TRUE;
        }
    } else {
        sched_ev_info->flag &= ~0x20;
    }

    if (event_now) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_CountDown_6(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                         GAME* game, int ev_start_flag) {
    int event_now = FALSE;

    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0), mBGMClock_CHK_ALL)) {
        if ((sched_ev_info->flag & 4) &&
            mBGMClock_over_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                      mBGMClock_CHK_MM | mBGMClock_CHK_DD | mBGMClock_CHK_hh | mBGMClock_CHK_mm |
                                          mBGMClock_CHK_ss) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[mBGMFieldSchedEv_EVENT_COUNTDOWN_6], game) !=
                mBGM_BL_ATTR_INACTIVE) {
            sched_ev_info->flag |= 0x20;
        }

        if ((sched_ev_info->flag & 0x20) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[mBGMFieldSchedEv_EVENT_COUNTDOWN_6], game) ==
                mBGM_BL_ATTR_INACTIVE) {
            sched_ev_info->flag &= ~0x20;
        }

        if ((sched_ev_info->flag & 0x20) == 0 &&
            mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE)) {
            event_now = TRUE;
        }
    } else {
        sched_ev_info->flag &= ~0x20;
    }

    if (event_now) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_Hotaru(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                    GAME* game, int ev_start_flag) {
    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_NewYear01(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                       GAME* game, int ev_start_flag) {
    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 18, 0, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_ev_now_set_NewYear02(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data,
                                                       GAME* game, int ev_start_flag) {
    if (mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 18, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 2, 0, 0, 0), mBGMClock_CHK_ALL)) {
        sched_ev_info->flag |= 1;
    } else {
        sched_ev_info->flag &= ~1;
    }
}

static void mBGMFieldSchedEv_Info_attr_now_set(mBGMFieldSchedEv_Info* sched_ev_info, GAME* game, mBGMEventData* data) {
    sched_ev_info->attr = mBGM_BL_ATTR_INACTIVE;

    if ((sched_ev_info->flag & (4 | 1)) == (4 | 1)) {
        int attr = mBGMFieldSchedEv_bl_attr_evdata_get(data, game);

        if (attr < mBGM_BL_ATTR_NUM) {
            sched_ev_info->attr = attr;
        }
    }
}

typedef void (*mBGMFieldSchedEv_INFO_CHK_PROC)(mBGMFieldSchedEv_Info*, mBGMEventData*, GAME*, int);

static void mBGMFieldSchedEv_info_set(mBGMFieldSchedEv* sched_ev, GAME* game) {
    static mBGMFieldSchedEv_INFO_CHK_PROC ev_chk[mBGMFieldSchedEv_EVENT_NUM] = {
        &mBGMFieldSchedEv_Info_ev_now_set_Silence_0,   &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard,
        &mBGMFieldSchedEv_Info_ev_now_set_CountDown_1, &mBGMFieldSchedEv_Info_ev_now_set_CountDown_2,
        &mBGMFieldSchedEv_Info_ev_now_set_CountDown_3, &mBGMFieldSchedEv_Info_ev_now_set_CountDown_4,
        &mBGMFieldSchedEv_Info_ev_now_set_CountDown_5, &mBGMFieldSchedEv_Info_ev_now_set_CountDown_6,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_Hotaru,
        &mBGMFieldSchedEv_Info_ev_now_set_NewYear01,   &mBGMFieldSchedEv_Info_ev_now_set_NewYear02,
        &mBGMFieldSchedEv_Info_ev_now_set_standard,    &mBGMFieldSchedEv_Info_ev_now_set_standard
    };

    mBGMFieldSchedEv_Info* info;
    mBGMEventData* data;
    int i;
    const int event_active_on_edge = mEv_check_status_edge(mEv_STATUS_ACTIVE);
    const int valid_field = mFI_CheckFieldData() && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG;

    info = sched_ev->info;
    data = mbgm_event_data;

    for (i = 0; i < ARRAY_COUNT(mbgm_event_data); i++, info++, data++) {
        mBGMFieldSchedEv_Info_old_copy(info);
        info->flag &= ~4;

        if (valid_field) {
            info->flag |= 4;
        }

        (*ev_chk[i])(info, data, game, event_active_on_edge);
        mBGMFieldSchedEv_Info_attr_now_set(info, game, data);
    }
}

static void mBGMPsComp_delete_ps_fieldSchedEv(u8 bgm_num, u16 stop_type);
static void mBGMPsComp_search_cf_set_field(u8 bgm_num, int kategorie);

static void mBGMFieldSchedEv_Info_ps_delete(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data, int flag) {
    mBGMPsComp_delete_ps_fieldSchedEv(data->bgm_num, 0x168);

    if (flag && data->bgm_num == mBGMPsComp_execute_bgm_num_get()) {
        mBGMPsComp_search_cf_set_field(data->bgm_num, 10);
    }
}

static void mBGMPsComp_make_ps_fieldSchedEv(u8 bgm_num, int update_volume_move_ctr, int update_volume_level,
                                            int cf_flag, u16 stop_type, u8 priority);

static void mBGMFieldSchedEv_Info_ps_make(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data, int priority) {
    int update_volume_move_ctr =
        sched_ev_info->attr != mBGM_BL_ATTR_INACTIVE && sched_ev_info->old_attr == mBGM_BL_ATTR_INACTIVE;
    int update_volume_level = mbgm_pattern_data[data->event_area][sched_ev_info->attr] == 1;
    int crossfade = mBGMPsComp_execute_bgm_num_get() < 0 ? FALSE : TRUE;
    u16 stop_type = priority == 0 ? (u16)0xA8C : (u16)0x168;

    mBGMPsComp_make_ps_fieldSchedEv(data->bgm_num, update_volume_move_ctr, update_volume_level, crossfade, stop_type,
                                    priority);
}

static void mBGMPsComp_volume_change_fieldSchedEv(u8 bgm_num, int update_volume_move_ctr, int update_volume_level);

static void mBGMFieldSchedEv_Info_ps_volume_change(mBGMFieldSchedEv_Info* sched_ev_info, mBGMEventData* data) {
    int flag = mbgm_pattern_data[data->event_area][sched_ev_info->attr] == 1;

    mBGMPsComp_volume_change_fieldSchedEv(data->bgm_num, TRUE, flag);
}

static void mBGMFieldSchedEv_ps_compose(mBGMFieldSchedEv* sched_ev, GAME* game) {
    mBGMFieldSchedEv_Info* info = sched_ev->info;
    mBGMEventData* data = mbgm_event_data;
    int i;
    int flag = TRUE;
    int now_flag;
    int old_flag;

    for (i = 0; i < ARRAY_COUNT(mbgm_event_data); i++) {
        now_flag = (info->flag & (4 | 1)) == (4 | 1) && info->attr != mBGM_BL_ATTR_INACTIVE;
        old_flag = (info->flag & (8 | 2)) == (8 | 2) && info->old_attr != mBGM_BL_ATTR_INACTIVE;

        if (!now_flag && old_flag) {
            mBGMFieldSchedEv_Info_ps_delete(info, data, flag);
        }

        if (now_flag && !old_flag) {
            mBGMFieldSchedEv_Info_ps_make(info, data, i);
        }

        if (now_flag && old_flag) {
            int now_vol = mbgm_pattern_data[data->event_area][info->attr];
            int old_vol = mbgm_pattern_data[data->event_area][info->old_attr];

            if (now_vol != old_vol && now_vol != 0 && old_vol != 0 && data->bgm_num != 127) {
                mBGMFieldSchedEv_Info_ps_volume_change(info, data);
            }
        }

        if (flag && old_flag) {
            flag = FALSE;
        }

        info++;
        data++;
    }
}

static void mBGMFieldSchedEv_sp_flag(mBGMFieldSchedEv* sched_ev) {
    mBGMFieldSchedEv_Info* info0 = &sched_ev->info[mBGMFieldSchedEv_EVENT_COUNTDOWN_5];
    mBGMFieldSchedEv_Info* info1 = &sched_ev->info[mBGMFieldSchedEv_EVENT_COUNTDOWN_6];

    if ((((info0->flag & (4 | 1)) == (4 | 1) && info0->attr != mBGM_BL_ATTR_INACTIVE) ||
         ((info1->flag & (4 | 1)) == (4 | 1) && info1->attr != mBGM_BL_ATTR_INACTIVE)) &&
        mBGMClock_range_time_check(&M_bgm.clock, mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   mBGMClock_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 1, 0), mBGMClock_CHK_ALL)) {
        mBGMTime_new_year_ev_flag_set();
    } else {
        mBGMTime_new_year_ev_flag_clr();
    }
}

static void mBGMFieldSchedEv_move(mBGMFieldSchedEv* sched_ev, GAME* game) {
    mBGMFieldSchedEv_info_set(sched_ev, game);
    mBGMFieldSchedEv_ps_compose(sched_ev, game);
    mBGMFieldSchedEv_sp_flag(sched_ev);
}

static void mBGMFieldSchedEv_ct(mBGMFieldSchedEv* sched_ev) {
    int i;

    bzero(sched_ev, sizeof(mBGMFieldSchedEv));
    for (i = 0; i < ARRAY_COUNT(sched_ev->info); i++) {
        sched_ev->info[i].old_attr = mBGM_BL_ATTR_INACTIVE;
        sched_ev->info[i].attr = mBGM_BL_ATTR_INACTIVE;
    }
}

/* mBGMFieldNorm */

static u8 mBGMFieldNorm_bgm_num_get(int hour) {
    static u8 bgm_table[24] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

    return bgm_table[hour];
}

static void mBGMFieldNorm_elem_set(mBGMFieldNorm* norm) {
    int hour = Common_Get(time.rtc_time.hour) % 24;

    mBGMElem_default_set(&norm->elem);
    norm->elem.bgm_num = mBGMFieldNorm_bgm_num_get(hour);
}

static void mBGMPsComp_make_ps_fieldNorm(u8 bgm_num, u16 stop_type);

static void mBGMFieldNorm_make_bgm(mBGMFieldNorm* norm, GAME* game) {
    if (norm->elem.bgm_num == 127) {
        mBGMFieldNorm_elem_set(norm);
        mBGMPsComp_make_ps_fieldNorm(norm->elem.bgm_num, 0x168);
    }
}

static void mBGMPsComp_delete_ps_fieldNorm(u8 bgm_num, u16 stop_type);

static void mBGMFieldNorm_delete_bgm(mBGMFieldNorm* norm) {
    if (norm->elem.bgm_num != 127) {
        mBGMPsComp_delete_ps_fieldNorm(norm->elem.bgm_num, norm->elem.stop_type0);
        norm->elem.bgm_num = 127;
    }
}

static void mBGMFieldNorm_move(mBGMFieldNorm* norm, GAME* game) {
    if (mBGMClock_over_time_check(&M_bgm.clock, 0, mBGMClock_CHK_mm | mBGMClock_CHK_ss) && mFI_CheckFieldData() &&
        mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG) {
        norm->delete_flag = TRUE;
        norm->make_flag = TRUE;
    }

    if (norm->delete_flag) {
        mBGMFieldNorm_delete_bgm(norm);
    }

    if (norm->make_flag) {
        mBGMFieldNorm_make_bgm(norm, game);
    }

    norm->make_flag = FALSE;
    norm->delete_flag = FALSE;
}

static void mBGMFieldNorm_make_req() {
    M_bgm.field_norm.make_flag = TRUE;
}

static void mBGMFieldNorm_delete_req() {
    M_bgm.field_norm.delete_flag = TRUE;
}

static void mBGMFieldNorm_ct(mBGMFieldNorm* norm) {
    bzero(norm, sizeof(mBGMFieldNorm));
    mBGMElem_default_set(&norm->elem);
}

/* mBGMPs[Comp] */

static void mBGMPs_counter_dec(mBGMPs* ps) {
    if (ps->counter > 0) {
        ps->counter--;

        if (ps->counter == 0) {
            ps->cf_flags |= mBGMPs_FLAG_REMOVE;
        }
    }
}

static void mBGMPsComp_ps_remove(mBGMPsComp* ps_comp, int remove_pos) {
    if (remove_pos >= 0 && remove_pos < mBGM_BGMPs_NUM) {

        if (remove_pos < ps_comp->ps_num && ps_comp->ps_num > 0) {
            int max = ps_comp->ps_num - 1;
            int i;

            for (i = remove_pos; i < max; i++) {
                ps_comp->ps[i] = ps_comp->ps[i + 1];
            }

            bzero(&ps_comp->ps[max], sizeof(mBGMPs));
            ps_comp->ps_num = max;
        }
    }
}

static int mBGMPsComp_search_insert_pos_kategorie(mBGMPsComp* ps_comp, int kategorie, u8 priority) {
    mBGMPs* ps = ps_comp->ps;
    int max = ps_comp->ps_num;
    int i;
    int res;

    if (max < mBGM_BGMPs_NUM) {
        res = max;
        for (i = 0; i < max; i++, ps++) {
            if ((kategorie == ps->kategorie && priority < ps->priority) || kategorie < ps->kategorie) {
                res = i;
                break;
            }
        }
    } else {
        res = -1;
    }

    return res;
}

static int mBGMPsComp_search_pos_kategorie_bgm_num(mBGMPsComp* ps_comp, int kategorie, u8 bgm_num, int counter_flag,
                                                   int del_pass) {
    int kategorie_valid = kategorie < mBGM_KATEGORIE_NUM;
    int bgm_is_reset = bgm_num != 127;
    int res = -1;
    u8 delete_mask = del_pass == 0;

    if (kategorie_valid || bgm_is_reset) {
        mBGMPs* ps = ps_comp->ps;
        int i = 0;
        int max = ps_comp->ps_num;

        for (i; i < max; i++, ps++) {
            if ((!kategorie_valid || ps->kategorie == kategorie) && (!bgm_is_reset || ps->elem.bgm_num == bgm_num) &&
                (counter_flag == FALSE || (ps->counter < 0 && (ps->cf_flags & mBGMPs_FLAG_FADEOUT) == 0)) &&
                ((ps->cf_flags & delete_mask) == 0)) {
                res = i;
                break;
            }
        }
    }

    return res;
}

static void mBGMPsComp_shift_behind(mBGMPsComp* ps_comp, int shift_idx) {
    if (ps_comp->ps_num != 0) {
        int i;

        for (i = ps_comp->ps_num - 1; i >= shift_idx; i--) {
            bcopy(&ps_comp->ps[i], &ps_comp->ps[i + 1], sizeof(mBGMPs));
        }
    }

    bzero(&ps_comp->ps[shift_idx], sizeof(mBGMPs));
    ps_comp->ps_num++;
}

static void mBGMPsComp_all_ps_bitclr(mBGMPsComp* ps_comp, u8 bits) {
    mBGMPs* ps = ps_comp->ps;
    int max = ps_comp->ps_num;
    int i;

    for (i = 0; i < max; i++, ps++) {
        ps->cf_flags &= ~bits;
    }
}

static int mBGMPsComp_execute_ps_pos_get(mBGMPsComp* ps_comp) {
    mBGMPs* ps = ps_comp->ps;
    int max = ps_comp->ps_num;
    int i;
    int idx = -1;

    for (i = 0; i < max; i++, ps++) {
        if ((ps->cf_flags & mBGMPs_FLAG_EXECUTE)) {
            idx = i;
            break;
        }
    }

    return idx;
}

static mBGMPs* mBGMPsComp_high_ps_not_delete(mBGMPsComp* ps_comp, int max_pos) {
    mBGMPs* ps = ps_comp->ps;
    mBGMPs* high_ps = NULL;
    int i;

    for (i = 0; i < max_pos; i++, ps++) {
        if ((ps->cf_flags & mBGMPs_FLAG_REMOVE) == 0) {
            high_ps = ps;
            break;
        }
    }

    return high_ps;
}

static void mBGMPsComp_main_req_stop(mBGMPsComp* ps_comp) {
    mBGMPs* ps = ps_comp->ps;
    int execute_pos = mBGMPsComp_execute_ps_pos_get(ps_comp);

    if (execute_pos >= 0) {
        ps += execute_pos;

        if ((ps->cf_flags & mBGMPs_FLAG_SILENT) == 0) {
            if (execute_pos > 0) {
                mBGMPs* high_ps = mBGMPsComp_high_ps_not_delete(ps_comp, execute_pos);

                if (high_ps != NULL) {
                    ps_comp->stop.req_flag = TRUE;
                    ps_comp->stop.type = high_ps->elem.stop_type1;
                    return;
                }
            }

            if ((ps->cf_flags & mBGMPs_FLAG_REMOVE) && (ps->cf_flags & mBGMPs_FLAG_LOST) == 0) {
                ps_comp->stop.req_flag = TRUE;
                ps_comp->stop.type = ps->elem.stop_type0;
            }
        }
    }
}

static void mBGMPsComp_main_remove(mBGMPsComp* ps_comp) {
    mBGMPs* ps;
    int i;

    for (i = ps_comp->ps_num - 1, ps = &ps_comp->ps[i]; i >= 0; i--, ps--) {
        if ((ps->cf_flags & mBGMPs_FLAG_REMOVE)) {
            ps->cf_flags &= ~mBGMPs_FLAG_REMOVE;
            mBGMPsComp_ps_remove(ps_comp, i);
        }
    }
}

static void mBGMPsComp_main_req_start(mBGMPsComp* ps_comp) {
    if (ps_comp->ps_num > 0) {
        if ((ps_comp->ps[0].cf_flags & mBGMPs_FLAG_EXECUTE) == 0) {
            if ((ps_comp->ps[0].cf_flags & mBGMPs_FLAG_SILENT) == 0) {
                ps_comp->start.req_flag = TRUE;
                ps_comp->start.flags = (ps_comp->ps[0].cf_flags >> 3) & 1; // crossfade (mBGMPs_FLAG_CROSSFADE)
                ps_comp->start.bgm_num = ps_comp->ps[0].elem.bgm_num;

                if (mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
                    ps_comp->ps[0].cf_flags |= mBGMPs_FLAG_UPDATE_VOLUME;
                }
            }

            mBGMPsComp_all_ps_bitclr(ps_comp, mBGMPs_FLAG_EXECUTE);
            ps_comp->ps[0].cf_flags |= mBGMPs_FLAG_EXECUTE;
        }

        mBGMPsComp_all_ps_bitclr(ps_comp, mBGMPs_FLAG_CROSSFADE);
    }
}

static void mBGMPsComp_main_req_pause(mBGMPsComp* ps_comp) {
    if (ps_comp->pause_state == 1 || ps_comp->pause_state == 3) {
        ps_comp->pause.mode = 1;
        ps_comp->pause.req_flag = TRUE;
    } else if (ps_comp->pause_state == 2) {
        ps_comp->pause.mode = 2;
        ps_comp->pause.req_flag = TRUE;
    } else if (ps_comp->pause_state == 5) {
        ps_comp->pause.mode = 0;
        ps_comp->pause.req_flag = TRUE;
    }
}

static void mBGMPsComp_main_req_md(mBGMPsComp* ps_comp) {
    if (ps_comp->md.move_flag) {
        ps_comp->md.req_flag = TRUE;
    }
}

static void mBGMPsComp_main_md_move(mBGMPsComp* ps_comp) {
    if (ps_comp->md.delete_flag) {
        ps_comp->md.move_flag = FALSE;
        ps_comp->md.delete_flag = FALSE;
    }

    if (ps_comp->md.make_flag) {
        ps_comp->md.move_flag = TRUE;
        ps_comp->md.make_flag = FALSE;
    }
}

static void mBGMPsComp_main_req_volume_ps(mBGMPsComp* ps_comp) {
    if (ps_comp->ps_num > 0) {
        if ((ps_comp->ps[0].cf_flags & mBGMPs_FLAG_UPDATE_VOLUME)) {
            if ((ps_comp->ps[0].cf_flags & mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR)) {
                ps_comp->volume.ps_volume_move_ctr = 90;
            } else {
                ps_comp->volume.ps_volume_move_ctr = 0;
            }

            if ((ps_comp->ps[0].cf_flags & mBGMPs_FLAG_UPDATE_VOLUME_LEVEL)) {
                ps_comp->volume.ps_volume = 0.5f;
            } else {
                ps_comp->volume.ps_volume = 1.0f;
            }

            ps_comp->volume.ps_req_flag = TRUE;
        }

        mBGMPsComp_all_ps_bitclr(ps_comp, mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR | mBGMPs_FLAG_UPDATE_VOLUME);
    }

    if (mBGMPsComp_execute_bgm_num_get() < 0) {
        ps_comp->volume.ps_volume = -1.0f;
    }
}

static void mBGMPsComp_main_req_volume_fishing(mBGMPsComp* ps_comp) {
    if (ps_comp->fishing_state == 1) {
        ps_comp->fishing_state = 2;
        ps_comp->volume.fishing_volume = 0.6f;
        ps_comp->volume.fishing_volume_move_ctr = 300;
        ps_comp->volume.fishing_req_flag = TRUE;
    } else if (ps_comp->fishing_state == 3) {
        ps_comp->fishing_state = 0;
        ps_comp->volume.fishing_volume = -1.0f;
        ps_comp->volume.fishing_volume_move_ctr = 35;

        if (ps_comp->ps_num <= 0 || mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
            ps_comp->volume.fishing_req_flag = TRUE;
        }
    }
}

static void mBGMPsComp_main_req_volume_collect_insects(mBGMPsComp* ps_comp) {
    if (ps_comp->collect_insects_state == 1) {
        ps_comp->collect_insects_state = 2;
        ps_comp->volume.collect_insects_volume = 0.65f;
        ps_comp->volume.collect_insects_volume_move_ctr = 100;
        ps_comp->volume.collect_insects_req_flag = TRUE;
    } else if (ps_comp->collect_insects_state == 3) {
        ps_comp->collect_insects_state = 0;
        ps_comp->volume.collect_insects_volume = -1.0f;
        ps_comp->volume.collect_insects_volume_move_ctr = 17;

        if (ps_comp->ps_num <= 0 || mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
            ps_comp->volume.collect_insects_req_flag = TRUE;
        }
    }
}

static void mBGMPsComp_main_req_volume_talk(mBGMPsComp* ps_comp) {
    if (ps_comp->talk_state == 1) {
        ps_comp->talk_state = 2;
        ps_comp->volume.talk_volume = 0.7f;
        ps_comp->volume.talk_req_flag = TRUE;
    } else if (ps_comp->talk_state == 3) {
        ps_comp->talk_state = 0;
        ps_comp->volume.talk_volume = -1.0f;

        if (ps_comp->ps_num <= 0 || mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
            ps_comp->volume.talk_req_flag = TRUE;
        }
    }
}

static void mBGMPsComp_main_req_volume_boat(mBGMPsComp* ps_comp) {
    if (ps_comp->boat_state == 1) {
        ps_comp->boat_state = 2;
        ps_comp->volume.boat_volume = 0.7f;
        ps_comp->volume.boat_req_flag = TRUE;
    } else if (ps_comp->boat_state == 3) {
        ps_comp->boat_state = 0;
        ps_comp->volume.boat_volume = -1.0f;

        if (ps_comp->ps_num <= 0 || mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
            ps_comp->volume.boat_req_flag = TRUE;
        }
    }
}

static void mBGMPsComp_main_req_volume_pause(mBGMPsComp* ps_comp) {
    if (ps_comp->pause_state == 1) {
        ps_comp->pause_state = 4;
        ps_comp->volume.pause_volume = 0.5f;
        ps_comp->volume.pause_volume_move_ctr = 2;
        ps_comp->volume.pause_req_flag = TRUE;
    } else if (ps_comp->pause_state == 2) {
        ps_comp->pause_state = 4;
        ps_comp->volume.pause_volume = 0.0f;
        ps_comp->volume.pause_volume_move_ctr = 2;
        ps_comp->volume.pause_req_flag = TRUE;
    } else if (ps_comp->pause_state == 3) {
        ps_comp->pause_state = 4;
        ps_comp->volume.pause_volume = 0.5f;
        ps_comp->volume.pause_volume_move_ctr = 2;
        ps_comp->volume.pause_req_flag = TRUE;
    } else if (ps_comp->pause_state == 5) {
        ps_comp->pause_state = 0;
        ps_comp->volume.pause_volume = -1.0f;
        ps_comp->volume.pause_volume_move_ctr = 2;

        if (ps_comp->ps_num <= 0 || mBGM_check_MD(ps_comp->ps[0].elem.bgm_num) == FALSE) {
            ps_comp->volume.pause_req_flag = TRUE;
        }
    }
}

static void mBGMPsComp_main_req_volume(mBGMPsComp* ps_comp) {
    f32 t_ps_vol;
    f32 t_talk_vol;
    f32 t_pause_vol;
    f32 t_collect_insects_vol;
    f32 t_fishing_vol;
    f32 t_boat_vol;
    f32 final_vol;
    u16 final_vol_move_ctr;
    mBGMPs* ps = &ps_comp->ps[0];
    int ignore_talk = ps_comp->ps_num > 0 ? mBGM_check_ignore_talk_volume(ps->elem.bgm_num) : FALSE;
    int ignore_collect_insects =
        ps_comp->ps_num > 0 ? mBGM_check_ignore_collect_insects_volume(ps->elem.bgm_num) : FALSE;

    mBGMPsComp_main_req_volume_ps(ps_comp);
    mBGMPsComp_main_req_volume_fishing(ps_comp);
    mBGMPsComp_main_req_volume_collect_insects(ps_comp);
    mBGMPsComp_main_req_volume_talk(ps_comp);
    mBGMPsComp_main_req_volume_boat(ps_comp);
    mBGMPsComp_main_req_volume_pause(ps_comp);

    t_ps_vol = ps_comp->volume.ps_volume;
    if (t_ps_vol < 0.0f) {
        t_fishing_vol = -1.0f;
        t_collect_insects_vol = -1.0f;
        t_talk_vol = -1.0f;
        t_boat_vol = -1.0f;
        t_pause_vol = -1.0f;
    } else {
        t_fishing_vol = (ps_comp->volume.fishing_volume < 0.0f || ps_comp->volume.fishing_volume > t_ps_vol ||
                         ignore_collect_insects)
                            ? t_ps_vol
                            : ps_comp->volume.fishing_volume;
        t_collect_insects_vol = (ps_comp->volume.collect_insects_volume < 0.0f ||
                                 ps_comp->volume.collect_insects_volume > t_fishing_vol || ignore_collect_insects)
                                    ? t_fishing_vol
                                    : ps_comp->volume.collect_insects_volume;
        t_talk_vol =
            (ps_comp->volume.talk_volume < 0.0f || ps_comp->volume.talk_volume > t_collect_insects_vol || ignore_talk)
                ? t_collect_insects_vol
                : ps_comp->volume.talk_volume;
        t_boat_vol = (ps_comp->volume.boat_volume < 0.0f || ps_comp->volume.boat_volume > t_talk_vol)
                         ? t_talk_vol
                         : ps_comp->volume.boat_volume;
        t_pause_vol = (ps_comp->volume.pause_volume < 0.0f || ps_comp->volume.pause_volume > t_boat_vol)
                          ? t_boat_vol
                          : ps_comp->volume.pause_volume;
    }

    final_vol = -1.0f;
    final_vol_move_ctr = 0;

    if (ps_comp->volume.ps_req_flag) {
        final_vol = t_ps_vol;
        final_vol_move_ctr = ps_comp->volume.ps_volume_move_ctr;
    }

    if (ps_comp->volume.fishing_req_flag && !ignore_collect_insects) {
        final_vol = t_fishing_vol;
        final_vol_move_ctr = ps_comp->volume.fishing_volume_move_ctr;
    }

    if (ps_comp->volume.collect_insects_req_flag && !ignore_collect_insects) {
        final_vol = t_collect_insects_vol;
        final_vol_move_ctr = ps_comp->volume.collect_insects_volume_move_ctr;
    }

    if (ps_comp->volume.talk_req_flag && !ignore_talk) {
        final_vol = t_talk_vol;
        final_vol_move_ctr = 30;
    }

    if (ps_comp->volume.boat_req_flag) {
        final_vol = t_boat_vol;
        final_vol_move_ctr = 30;
    }

    if (ps_comp->volume.pause_req_flag) {
        final_vol = t_pause_vol;
        final_vol_move_ctr = ps_comp->volume.pause_volume_move_ctr;
    }

    if (ps_comp->pause_state == 4) {
        if ((final_vol < 0.0f) == FALSE) {
            final_vol = t_pause_vol;
        }
    } else if (ps_comp->boat_state == 2) {
        if ((final_vol < 0.0f) == FALSE) {
            final_vol = t_boat_vol;
        }
    } else if (ps_comp->talk_state == 2) {
        if ((final_vol < 0.0f) == FALSE) {
            final_vol = t_talk_vol;
        }
    } else if (ps_comp->collect_insects_state == 2) {
        if ((final_vol < 0.0f) == FALSE) {
            final_vol = t_collect_insects_vol;
        }
    } else if (ps_comp->fishing_state == 2) {
        if ((final_vol < 0.0f) == FALSE) {
            final_vol = t_fishing_vol;
        }
    }

    if ((final_vol < 0.0f) == FALSE) {
        ps_comp->volume.main_volume = final_vol;
        ps_comp->volume.main_volume_move_ctr = final_vol_move_ctr;
        ps_comp->volume.main_req_flag = TRUE;
    }

    ps_comp->volume.ps_req_flag = FALSE;
    ps_comp->volume.fishing_req_flag = FALSE;
    ps_comp->volume.collect_insects_req_flag = FALSE;
    ps_comp->volume.talk_req_flag = FALSE;
    ps_comp->volume.boat_req_flag = FALSE;
    ps_comp->volume.pause_req_flag = FALSE;
}

static void mBGMPsComp_MDPlayerPos_main_inform_sound(mBGMPsComp_MDPlayerPos* md) {
    if (md->req_flag) {
        sAdo_MDPlayerPos(&md->pos, md->angle, md->md_type_no, md->ongen_no);
        md->req_flag = FALSE;
    }
}

static void mBGMPsComp_arm_delete();

static void mBGMPsComp_Arm_main_inform_sound(mBGMPsComp_Arm* arm) {
    if (arm->req_flag) {
        if (mBGMPsComp_execute_bgm_num_get() == 43) {
            sAdos_TTKK_ARM(arm->arm_state);

            if (arm->arm_state == 0) {
                mBGMPsComp_arm_delete();
            }
        } else {
            mBGMPsComp_arm_delete();
        }
    }
}

static void mBGMPsComp_Stop_main_inform_sound(mBGMPsComp_Stop* stop) {
    if (stop->req_flag) {
        sAdo_BgmStop(stop->type);
        stop->req_flag = FALSE;
    }
}

static void mBGMPsComp_arm_make(u8 state);

static void mBGMPsComp_Start_main_inform_sound(mBGMPsComp_Start* start) {
    if (start->req_flag) {
        if (start->flags != 0) {
            sAdo_BgmCrossfadeStart(start->bgm_num);
        } else {
            sAdo_BgmStart(start->bgm_num);

            if (start->bgm_num == 43) {
                if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
                    mBGMPsComp_arm_make(1);
                } else {
                    mBGMPsComp_arm_make(0);
                }
            }
        }

        start->req_flag = FALSE;
    }
}

static void mBGMPsComp_Volume_main_inform_sound(mBGMPsComp_Volume* volume) {
    if (volume->main_req_flag) {
        sAdo_BGMVolume(volume->main_volume, volume->main_volume_move_ctr);
        volume->main_req_flag = FALSE;
    }
}

static void mBGMPsComp_Pause_main_inform_sound(mBGMPsComp_Pause* pause) {
    if (pause->req_flag) {
        sAdo_Pause(pause->mode);
        pause->req_flag = FALSE;
    }
}

static void mBGMPsComp_Museum_main_inform_sound(mBGMPsComp_Museum* museum) {
    if (museum->req_flag) {
        museum->req_flag--;

        if (museum->req_flag == 0) {
            sAdo_Museum(museum->type);
        }
    }
}

static void mBGMPsComp_main_inform_sound(mBGMPsComp* ps_comp) {
    mBGMPsComp_MDPlayerPos_main_inform_sound(&ps_comp->md);
    mBGMPsComp_Arm_main_inform_sound(&ps_comp->arm);
    mBGMPsComp_Stop_main_inform_sound(&ps_comp->stop);
    mBGMPsComp_Start_main_inform_sound(&ps_comp->start);
    mBGMPsComp_Pause_main_inform_sound(&ps_comp->pause);
    mBGMPsComp_Volume_main_inform_sound(&ps_comp->volume);
    mBGMPsComp_Museum_main_inform_sound(&ps_comp->museum);
}

static void mBGMPsComp_main_counter_dec(mBGMPsComp* ps_comp) {
    mBGMPs* ps = ps_comp->ps;
    int i;
    int max = ps_comp->ps_num;

    for (i = 0; i < max; i++, ps++) {
        mBGMPs_counter_dec(ps);
    }
}

static void mBGMPsComp_main_fo_check(mBGMPsComp* ps_comp) {
    mBGMPs* ps = ps_comp->ps;
    int i;
    int max = ps_comp->ps_num;

    for (i = 0; i < max; i++, ps++) {
        if (ps->cf_flags & mBGMPs_FLAG_FADEOUT) {
            int execute_pos = mBGMPsComp_execute_ps_pos_get(ps_comp);

            if ((execute_pos >= i || execute_pos < 0) || (ps_comp->ps[execute_pos].elem.bgm_num == 127) ||
                (ps_comp->ps[execute_pos].cf_flags & mBGMPs_FLAG_SILENT)) {
                if (sAdo_BgmFadeoutCheck() == FALSE) {
                    continue; /* don't clear the fadeout flag */
                }
            }

            ps->cf_flags &= ~mBGMPs_FLAG_FADEOUT;
            ps->cf_flags |= mBGMPs_FLAG_REMOVE;
        }
    }
}

static void mBGMPsComp_main_lost(mBGMPsComp* ps_comp) {
    mBGMPs* ps = ps_comp->ps;
    int i;
    int max = ps_comp->ps_num;

    for (i = 0; i < max; i++, ps++) {
        if ((ps->cf_flags & mBGMPs_FLAG_LOST)) {
            ps->cf_flags |= mBGMPs_FLAG_REMOVE;
        }
    }
}

static int mBGMPsComp_make_ps(mBGMPsComp* ps_comp, mBGMElem* elem, int kategorie, s16 counter, u16 cf_flags,
                              u8 priority) {
    int pos = mBGMPsComp_search_insert_pos_kategorie(ps_comp, kategorie, priority);

    if (pos >= 0) {
        mBGMPs* dst_ps = &ps_comp->ps[pos];

        mBGMPsComp_shift_behind(ps_comp, pos);
        bcopy(elem, &dst_ps->elem, sizeof(mBGMElem));
        dst_ps->kategorie = kategorie;
        dst_ps->counter = counter;
        dst_ps->cf_flags = cf_flags;
        dst_ps->priority = priority;
    }

    return pos;
}

static void _mBGMPsComp_make_ps_fanfare(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_FANFARE, -1, 0, 0xFF);
}

extern void mBGMPsComp_make_ps_fanfare(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_make_ps_fanfare(bgm_num, stop_type);
}

static void _mBGMPsComp_make_ps_lost_fanfare(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_FANFARE, -1, mBGMPs_FLAG_LOST, 0xFF);
}

extern void mBGMPsComp_make_ps_lost_fanfare(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_make_ps_lost_fanfare(bgm_num, stop_type);
}

static int mBGMForce_wipe_ps_make_permit(mBGMForce* force);

static void _mBGMPsComp_make_ps_wipe(u16 stop_type) {
    mBGMForce* force = &M_bgm.force;
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;
    mBGMElem elem;

    if (mBGMForce_wipe_ps_make_permit(force) &&
        mBGMPsComp_search_pos_kategorie_bgm_num(ps_comp, mBGM_KATEGORIE_WIPE, 127, FALSE, FALSE) < 0) {
        mBGMElem_default_set(&elem);
        elem.stop_type1 = stop_type;
        mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_WIPE, -1, mBGMPs_FLAG_SILENT, 0xFF);
    }
}

extern void mBGMPsComp_make_ps_wipe(u16 stop_type) {
    _mBGMPsComp_make_ps_wipe(stop_type);
}

static void _mBGMPsComp_make_ps_quiet(u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIET, -1, mBGMPs_FLAG_SILENT, 0xFF);
}

extern void mBGMPsComp_make_ps_quiet(u16 stop_type) {
    _mBGMPsComp_make_ps_quiet(stop_type);
}

static void _mBGMPsComp_make_ps_co_quiet(u16 stop_type, s16 counter) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIET, counter, mBGMPs_FLAG_SILENT, 0xFF);
}

extern void mBGMPsComp_make_ps_co_quiet(u16 stop_type, s16 counter) {
    _mBGMPsComp_make_ps_co_quiet(stop_type, counter);
}

static void _mBGMPsComp_make_ps_fc_quiet(u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIET, -1, mBGMPs_FLAG_SILENT | mBGMPs_FLAG_FADEOUT, 0xFF);
}

extern void mBGMPsComp_make_ps_fc_quiet(u16 stop_type) {
    _mBGMPsComp_make_ps_fc_quiet(stop_type);
}

static void _mBGMPsComp_make_ps_demo(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_DEMO, -1, 0, 0xFF);
}

extern void mBGMPsComp_make_ps_demo(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_make_ps_demo(bgm_num, stop_type);
}

static void _mBGMPsComp_make_ps_happening(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_HAPPENING, -1, 0, 0xFF);
}

extern void mBGMPsComp_make_ps_happening(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_make_ps_happening(bgm_num, stop_type);
}

static void mBGMPsComp_make_ps_quietRoom(u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIETROOM, -1, mBGMPs_FLAG_SILENT, 0xFF);
}

static void _mBGMPsComp_make_ps_room(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_ROOM, -1, 0, 0xFF);
}

extern void mBGMPsComp_make_ps_room(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_make_ps_room(bgm_num, stop_type);
}

static void mBGMPsComp_make_ps_time() {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = 0x870;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_TIME, -1, mBGMPs_FLAG_SILENT, 0xFF);
}

static void _mBGMPsComp_make_ps_quietField(u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIETFIELD, -1, mBGMPs_FLAG_SILENT, 0xFF);
}

extern void mBGMPsComp_make_ps_quietField(u16 stop_type) {
    _mBGMPsComp_make_ps_quietField(stop_type);
}

static void _mBGMPsComp_make_ps_fc_quietField(u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_QUIETFIELD, -1, mBGMPs_FLAG_SILENT | mBGMPs_FLAG_FADEOUT,
                       0xFF);
}

extern void mBGMPsComp_make_ps_fc_quietField(u16 stop_type) {
    _mBGMPsComp_make_ps_fc_quietField(stop_type);
}

static void _mBGMPsComp_make_ps_fieldSuddenEv(u8 bgm_num, u16 stop_type, u8 priority) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_FIELDSUDDENEV, -1, 0, priority);
}

extern void mBGMPsComp_make_ps_fieldSuddenEv(u8 bgm_num, u16 stop_type, u8 priority) {
    _mBGMPsComp_make_ps_fieldSuddenEv(bgm_num, stop_type, priority);
}

static void mBGMPsComp_make_ps_fieldSchedEv(u8 bgm_num, int update_volume_move_ctr, int update_volume_level,
                                            int cf_flag, u16 stop_type, u8 priority) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;
    mBGMElem elem;
    u16 flags;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    flags = 0;

    if (update_volume_move_ctr) {
        flags |= mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR;
    }

    if (update_volume_level) {
        flags |= mBGMPs_FLAG_UPDATE_VOLUME_LEVEL;
    }

    if (cf_flag) {
        flags |= mBGMPs_FLAG_CROSSFADE;
    }

    if (bgm_num == 127) {
        flags |= mBGMPs_FLAG_SILENT;
    }

    mBGMPsComp_make_ps(ps_comp, &elem, mBGM_KATEGORIE_FIELDSCHEDEV, -1, flags, priority);
}

static void mBGMPsComp_make_ps_fieldNorm(u8 bgm_num, u16 stop_type) {
    mBGMElem elem;

    mBGMElem_default_set(&elem);
    elem.bgm_num = bgm_num;
    elem.stop_type1 = stop_type;
    mBGMPsComp_make_ps(&M_bgm.ps_comp, &elem, mBGM_KATEGORIE_FIELDNORM, -1, 0, 255);
}

static void mBGMPsComp_delete_ps(mBGMPsComp* ps_comp, int kategorie, u8 bgm_num, u16 stop_type, int counter_flag) {
    int num = mBGMPsComp_search_pos_kategorie_bgm_num(ps_comp, kategorie, bgm_num, counter_flag, FALSE);

    if (num >= 0 && num < ps_comp->ps_num) {
        ps_comp->ps[num].cf_flags |= mBGMPs_FLAG_REMOVE;
        ps_comp->ps[num].elem.stop_type0 = stop_type;
    }
}

static void _mBGMPsComp_delete_ps_fanfare(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_FANFARE, bgm_num, stop_type, FALSE);
}

extern void mBGMPsComp_delete_ps_fanfare(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_delete_ps_fanfare(bgm_num, stop_type);
}

static void mBGMPsComp_delete_ps_wipe() {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_WIPE, 127, 0x168, FALSE);
}

static void _mBGMPsComp_delete_ps_quiet() {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_QUIET, 127, 0x168, TRUE);
}

extern void mBGMPsComp_delete_ps_quiet() {
    _mBGMPsComp_delete_ps_quiet();
}

static void _mBGMPsComp_delete_ps_demo(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_DEMO, bgm_num, stop_type, FALSE);
}

extern void mBGMPsComp_delete_ps_demo(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_delete_ps_demo(bgm_num, stop_type);
}

static void _mBGMPsComp_delete_ps_happening(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_HAPPENING, bgm_num, stop_type, FALSE);
}

extern void mBGMPsComp_delete_ps_happening(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_delete_ps_happening(bgm_num, stop_type);
}

static void mBGMPsComp_delete_ps_quietRoom() {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_QUIETROOM, 127, 0x168, TRUE);
}

static void _mBGMPsComp_delete_ps_room(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_ROOM, bgm_num, stop_type, FALSE);
}

extern void mBGMPsComp_delete_ps_room(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_delete_ps_room(bgm_num, stop_type);
}

static void mBGMPsComp_delete_ps_time() {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_TIME, 127, 0x168, FALSE);
}

static void _mBGMPsComp_delete_ps_quietField() {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_QUIETFIELD, 127, 0x168, TRUE);
}

extern void mBGMPsComp_delete_ps_quietField() {
    _mBGMPsComp_delete_ps_quietField();
}

static void _mBGMPsComp_delete_ps_fieldSuddenEv(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_FIELDSUDDENEV, bgm_num, stop_type, FALSE);
}

extern void mBGMPsComp_delete_ps_fieldSuddenEv(u8 bgm_num, u16 stop_type) {
    _mBGMPsComp_delete_ps_fieldSuddenEv(bgm_num, stop_type);
}

static void mBGMPsComp_delete_ps_fieldSchedEv(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_FIELDSCHEDEV, bgm_num, stop_type, FALSE);
}

static void mBGMPsComp_delete_ps_fieldNorm(u8 bgm_num, u16 stop_type) {
    mBGMPsComp_delete_ps(&M_bgm.ps_comp, mBGM_KATEGORIE_FIELDNORM, bgm_num, stop_type, FALSE);
}

static void mBGMPsComp_volume_change_fieldSchedEv(u8 bgm_num, int update_volume_move_ctr, int update_volume_level) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;
    int idx = mBGMPsComp_search_pos_kategorie_bgm_num(ps_comp, mBGM_KATEGORIE_FIELDSCHEDEV, bgm_num, FALSE, FALSE);

    if (idx >= 0) {
        mBGMPs* ps = &ps_comp->ps[idx];

        if (update_volume_move_ctr) {
            ps->cf_flags |= mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR;
        }

        if (update_volume_level) {
            ps->cf_flags |= mBGMPs_FLAG_UPDATE_VOLUME_LEVEL;
        } else {
            ps->cf_flags &= ~mBGMPs_FLAG_UPDATE_VOLUME_LEVEL;
        }

        ps->cf_flags |= mBGMPs_FLAG_UPDATE_VOLUME;
    }
}

static void mBGMPsComp_search_cf_set_field(u8 bgm_num, int kategorie) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;
    int pos = mBGMPsComp_search_pos_kategorie_bgm_num(ps_comp, kategorie, bgm_num, FALSE, TRUE);

    if (pos >= 0) {
        int i;

        for (i = pos + 1; i < ps_comp->ps_num; i++) {
            if (ps_comp->ps[i].kategorie == mBGM_KATEGORIE_FIELDSUDDENEV ||
                ps_comp->ps[i].kategorie == mBGM_KATEGORIE_FIELDSCHEDEV ||
                ps_comp->ps[i].kategorie == mBGM_KATEGORIE_FIELDNORM) {
                ps_comp->ps[i].cf_flags |= (mBGMPs_FLAG_UPDATE_VOLUME_MOVE_CTR | mBGMPs_FLAG_CROSSFADE);
            }
        }
    }
}

extern void mBGMPsComp_volume_fishing_start() {
    M_bgm.ps_comp.fishing_state = 1;
}

extern void mBGMPsComp_volume_fishing_end() {
    M_bgm.ps_comp.fishing_state = 3;
}

extern void mBGMPsComp_volume_collect_insects_start() {
    M_bgm.ps_comp.collect_insects_state = 1;
}

extern void mBGMPsComp_volume_collect_insects_end() {
    M_bgm.ps_comp.collect_insects_state = 3;
}

extern void mBGMPsComp_volume_talk_start() {
    M_bgm.ps_comp.talk_state = 1;
}

extern void mBGMPsComp_volume_talk_end() {
    if (M_bgm.ps_comp.talk_state != 0) {
        M_bgm.ps_comp.talk_state = 3;
    }
}

/* @unused */
extern void mBGMPsComp_volume_boat_start() {
    M_bgm.ps_comp.boat_state = 1;
}

extern void mBGMPsComp_volume_boat_end() {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;

    if (ps_comp->boat_state != 0) {
        ps_comp->boat_state = 3;
    }
}

extern void mBGMPsComp_pause(int state) {
    M_bgm.ps_comp.pause_state = state;
}

extern void mBGMPsComp_MDPlayerPos_make() {
    M_bgm.ps_comp.md.make_flag = TRUE;
}

extern void mBGMPsComp_MDPlayerPos_delete() {
    M_bgm.ps_comp.md.delete_flag = TRUE;
}

extern void mBGMPsComp_MDPlayerPos_param_set(const xyz_t* pos, u16 angle, u16 md_type, JaudioObjectId ongen_no) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;

    xyz_t_move(&ps_comp->md.pos, pos);
    ps_comp->md.angle = angle;
    ps_comp->md.md_type_no = md_type;
    ps_comp->md.ongen_no = ongen_no;
}

extern void mBGMPsComp_scene_mode(u8 mode) {
    sAdo_SceneMode(mode);
}

static void mBGMPsComp_arm_make(u8 state) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;

    ps_comp->arm.req_flag = TRUE;
    ps_comp->arm.arm_state = state;
}

static void mBGMPsComp_arm_delete() {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;

    ps_comp->arm.req_flag = FALSE;
    ps_comp->arm.arm_state = 0;
}

extern void mBGMPsComp_museum_status(u8 status) {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;

    if (status == 0) {
        ps_comp->museum.req_flag = 1;
    } else {
        ps_comp->museum.req_flag = 2;
    }

    ps_comp->museum.type = status;
}

extern int mBGMPsComp_execute_bgm_num_get() {
    mBGMPsComp* ps_comp = &M_bgm.ps_comp;
    int pos = mBGMPsComp_execute_ps_pos_get(ps_comp);

    if (pos >= 0 && ps_comp->ps[pos].elem.bgm_num != 127 && (ps_comp->ps[pos].cf_flags & mBGMPs_FLAG_SILENT) == 0) {
        return ps_comp->ps[pos].elem.bgm_num;
    }

    return -1;
}

static void mBGMPsComp_ct(mBGMPsComp* ps_comp) {
    bzero(ps_comp, sizeof(mBGMPsComp));

    ps_comp->volume.main_volume = -1.0f;
    ps_comp->volume.main_volume_move_ctr = 0;
    ps_comp->volume.ps_volume = -1.0f;
    ps_comp->volume.ps_volume_move_ctr = 0;
    ps_comp->volume.fishing_volume = -1.0f;
    ps_comp->volume.fishing_volume_move_ctr = 100;
    ps_comp->volume.collect_insects_volume = -1.0f;
    ps_comp->volume.collect_insects_volume_move_ctr = 100;
    ps_comp->volume.talk_volume = -1.0f;
    ps_comp->volume.boat_volume = -1.0f;
    ps_comp->volume.pause_volume = -1.0f;
    ps_comp->volume.pause_volume_move_ctr = 2;
}

/* mBGMForce */

static int mBGMForce_wipe_ps_make_permit(mBGMForce* force) {
    if (force->room_nonstop != 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static void mBGMForce_move_inform(mBGMForce* force) {
    if (force->inform == mBGMForce_INFORM_1) {
        int field_ok = mFI_CheckFieldData();

        if (field_ok == FALSE || (field_ok != FALSE && mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELD_FG)) {
            force->flag = TRUE;
            mBGMPsComp_make_ps_wipe(0x195);
        }

        force->inform = mBGMForce_INFORM_2;
    } else if (force->inform == mBGMForce_INFORM_3) {
        force->inform = mBGMForce_INFORM_4;
    } else if (force->inform == mBGMForce_INFORM_5) {
        if (force->flag) {
            mBGMPsComp_make_ps_wipe(0x249);
        }

        force->inform = mBGMForce_INFORM_6;
    } else if (force->inform == mBGMForce_INFORM_7) {
        force->inform = mBGMForce_INFORM_0;
        force->flag = FALSE;
    }
}

static void mBGMForce_move_room_nonstop(mBGMForce* force) {
    if (force->room_nonstop == 1) {
        force->room_nonstop = 2;
    } else if (force->room_nonstop == 3) {
        force->room_nonstop = 0;
    }
}

static void mBGMForce_move(mBGMForce* force) {
    mBGMForce_move_inform(force);
    mBGMForce_move_room_nonstop(force);
}

static void mBGMForce_ct(mBGMForce* force) {
    bzero(force, sizeof(mBGMForce));
}

static void mBGMForce_inform_cleanup(mBGMForce* force) {
    if (force->inform == mBGMForce_INFORM_2) {
        force->inform = mBGMForce_INFORM_3;
    } else if (force->inform == mBGMForce_INFORM_6) {
        force->inform = mBGMForce_INFORM_7;
    }
}

static void mBGMForce_room_nonstop_cleanup(mBGMForce* force) {
    if (force->room_nonstop == 2) {
        force->room_nonstop = 3;
    }
}

static void mBGMForce_cleanup(mBGMForce* force) {
    mBGMForce_inform_cleanup(force);
    mBGMForce_room_nonstop_cleanup(force);
}

extern void mBGMForce_inform_start() {
    M_bgm.force.inform = mBGMForce_INFORM_1;
}

extern void mBGMForce_inform_end() {
    M_bgm.force.inform = mBGMForce_INFORM_5;
}

static void _mBGMForce_room_nonstop_start() {
    M_bgm.force.room_nonstop = 1;
}

extern void mBGMForce_room_nonstop_start() {
    _mBGMForce_room_nonstop_start();
}

static void mBGM_main_control(mBGM* bgm) {
    mBGMPsComp* ps_comp = &bgm->ps_comp;

    mBGMPsComp_main_req_md(ps_comp);
    mBGMPsComp_main_req_stop(ps_comp);
    mBGMPsComp_main_remove(ps_comp);
    mBGMPsComp_main_req_start(ps_comp);
    mBGMPsComp_main_req_pause(ps_comp);
    mBGMPsComp_main_req_volume(ps_comp);
    mBGMPsComp_main_inform_sound(ps_comp);
    mBGMPsComp_main_md_move(ps_comp);
    mBGMPsComp_main_counter_dec(ps_comp);
    mBGMPsComp_main_fo_check(ps_comp);
    mBGMPsComp_main_lost(ps_comp);
}

static void mBGM_weather_set() {
    s16 weather = Common_Get(weather);

    if (weather >= mEnv_WEATHER_LEAVES) {
        weather = mEnv_WEATHER_SAKURA;
    } else if (weather < 0) {
        weather = mEnv_WEATHER_CLEAR;
    }

    sAdo_Tenki(weather);
}

extern void mBGM_main(GAME* game) {
    mBGMClock_move(&M_bgm.clock, game);
    mBGMDemo_move(&M_bgm.demo, game);
    mBGMRoom_move(&M_bgm.room, game);
    mBGMFieldSuddenEv_move(&M_bgm.field_sudden_ev, game);
    mBGMFieldSchedEv_move(&M_bgm.field_sched_ev, game);
    mBGMFieldNorm_move(&M_bgm.field_norm, game);
    mBGMTime_move(&M_bgm.time, game);
    mBGM_main_control(&M_bgm);
    mBGMForce_move(&M_bgm.force);
    mBGM_weather_set();
}

extern void mBGM_ct() {
    mBGMClock_ct(&M_bgm.clock);
    mBGMDemo_ct(&M_bgm.demo);
    mBGMRoom_ct(&M_bgm.room);
    mBGMTime_ct(&M_bgm.time);
    mBGMFieldSuddenEv_ct(&M_bgm.field_sudden_ev);
    mBGMFieldSchedEv_ct(&M_bgm.field_sched_ev);
    mBGMFieldNorm_ct(&M_bgm.field_norm);
    mBGMPsComp_ct(&M_bgm.ps_comp);
    mBGMForce_ct(&M_bgm.force);
}

extern void mBGM_init() {
    mBGMPsComp_delete_ps_wipe();

    if (mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();
        mActor_name_t field_type = mFI_GET_TYPE(field_id);
        mBGMForce* force = &M_bgm.force;

        if (field_type == mFI_FIELD_FG) {
            if (mEv_IsTitleDemo()) {
                mBGMPsComp_make_ps_demo(70, 0x168); // Play title music
            } else {
                if ((force->inform != mBGMForce_INFORM_3 && force->inform != mBGMForce_INFORM_7) || force->flag) {
                    mBGMFieldNorm_make_req();
                }

                if (force->inform == mBGMForce_INFORM_3 && force->flag) {
                    mBGMPsComp_make_ps_quiet(0x168);
                }
            }
        } else if (field_type == mFI_FIELD_ROOM0 || field_type == mFI_FIELD_NPCROOM0 ||
                   field_type == mFI_FIELD_PLAYER0_ROOM) {
            if (force->room_nonstop != 3) {
                mBGMRoom_shop_close_time_set(&M_bgm.room);
                mBGMRoom_scene_bgm_make_req();
            }
        } else {
            mBGMDemo_scene_bgm_make_req();
        }
    }
}

extern void mBGM_cleanup() {
    mBGMForce* force = &M_bgm.force;

    mBGMForce_cleanup(force);
    if (mFI_CheckFieldData()) {
        mActor_name_t field_id = mFI_GetFieldId();
        mActor_name_t field_type = mFI_GET_TYPE(field_id);

        if (field_type == mFI_FIELD_FG) {
            if (mEv_IsTitleDemo()) {
                mBGMPsComp_delete_ps_demo(70, 0x168); // Stop title music
            } else {
                if ((force->inform != mBGMForce_INFORM_3 && force->inform != mBGMForce_INFORM_7) || force->flag) {
                    mBGMFieldNorm_delete_req();
                }

                if (force->inform == mBGMForce_INFORM_7 && force->flag) {
                    mBGMPsComp_delete_ps_quiet();
                }
            }
        } else if (field_type == mFI_FIELD_ROOM0 || field_type == mFI_FIELD_NPCROOM0 ||
                   field_type == mFI_FIELD_PLAYER0_ROOM) {
            if (force->room_nonstop != 3) {
                mBGMRoom_scene_bgm_delete_req();
            }
        } else {
            mBGMDemo_scene_bgm_delete_req();
        }
    }
}

extern void mBGM_reset() {
    mBGM* bgm = &M_bgm;
    mBGMPsComp* ps_comp = &bgm->ps_comp;
    mBGMPs* ps = ps_comp->ps;
    int i;
    int max = ps_comp->ps_num;

    for (i = 0; i < max; i++, ps++) {
        ps->cf_flags |= mBGMPs_FLAG_REMOVE;
        ps->elem.stop_type0 = 0x168;
    }

    if (ps_comp->fishing_state != 0) {
        mBGMPsComp_volume_fishing_end();
    }

    if (ps_comp->collect_insects_state != 0) {
        mBGMPsComp_volume_collect_insects_end();
    }

    if (ps_comp->talk_state != 0) {
        mBGMPsComp_volume_talk_end();
    }

    if (ps_comp->boat_state != 0) {
        mBGMPsComp_volume_boat_end();
    }

    if (ps_comp->pause_state != 0) {
        mBGMPsComp_pause(mBGM_PAUSE_STOP);
    }

    mBGMDemo_ct(&bgm->demo);
    mBGMRoom_ct(&bgm->room);
    mBGMTime_ct(&bgm->time);
    mBGMFieldSuddenEv_ct(&bgm->field_sudden_ev);
    mBGMFieldSchedEv_ct(&bgm->field_sched_ev);
    mBGMFieldNorm_ct(&bgm->field_norm);
    mBGMForce_ct(&bgm->force);
}
