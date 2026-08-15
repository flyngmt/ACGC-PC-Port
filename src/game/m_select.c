#include "m_select.h"

#include "m_play.h"
#include "m_private.h"
#include "m_home.h"
#include "m_kabu_manager.h"
#include "m_font.h"
#include "m_time.h"
#include "m_scene_table.h"
#include "m_controller.h"
#include "m_kankyo.h"
#include "audio.h"
#include "libu64/gfxprint.h"
#include "m_name_table.h"
#include "libc64/qrand.h"
#include "m_rcp.h"
#include "main.h"
#include "m_npc.h"
#include "m_field_info.h"
#include "m_common_data.h"

static void game_next_play(GAME* game, int scene_no) {
    Save_Set(scene_no, scene_no);

    GAME_GOTO_NEXT(game, play, PLAY);
    mHm_SetNowHome();
    Common_Set(door_data.next_scene_id, 0);
    Kabu_decide_price_schedule();
    Common_Set(map_flag, TRUE);
}

typedef struct namefunc_s {
    const char* name;
    GAME_PROC next_play_proc;
    int scene_no;
} namefunc_t;

#define nf_str(s0, s1) (s0 GFXPRINT_KATAKANA_MODE_CHAR s1)
static namefunc_t nf_tbl[SCENE_NUM] = {
    { nf_str(" 1:", "ﾌｨｰﾙﾄﾞ ｺｰｽ1"), &game_next_play, SCENE_TEST1 },
    { nf_str(" 2:", "ﾌｨｰﾙﾄﾞ ｺｰｽ2"), &game_next_play, SCENE_TEST2 },
    { nf_str(" 3:", "ﾌｨｰﾙﾃﾞ ｺｰｽ3"), &game_next_play, SCENE_TEST3 },
    { nf_str(" 4:", "ｵﾐｽﾞﾃｽﾄ ｺｰｽ"), &game_next_play, SCENE_WATER_TEST },
    { nf_str(" 5:", "ｱｼｱﾄﾃｽﾄｺｰｽ"), &game_next_play, SCENE_FOOTPRINT_TEST },
    { nf_str(" 6:", "npc ﾃｽﾄｺｰｽ"), &game_next_play, SCENE_NPC_TEST },
    { nf_str(" 7:", "NPCｱﾚﾝｼﾞﾙｰﾑ"), &game_next_play, SCENE_NPC_HOUSE },
    { nf_str(" 8:", "NPCﾗﾝﾀﾞﾑｺｰｽ"), &game_next_play, SCENE_FG },
    { nf_str(" 9:", "FGﾂｰﾙ ﾌｨｰﾙﾄﾞﾖｳ"), &game_next_play, SCENE_RANDOM_NPC_TEST },
    { nf_str("10:", "ｵﾐｾ"), &game_next_play, SCENE_SHOP0 },
    { nf_str("11:", "BGﾌﾟﾚﾋﾞｭｰ ｶﾜﾅｼ"), &game_next_play, SCENE_BG_TEST_NO_RIVER },
    { nf_str("12:", "BGﾌﾟﾚﾋﾞｭｰ ｶﾜｱﾘ"), &game_next_play, SCENE_BG_TEST_RIVER },
    { nf_str("13:", "ﾔﾐﾌﾞﾛｰｶｰﾉ ｵﾐｾ"), &game_next_play, SCENE_BROKER_SHOP },
    { nf_str("14:", "FGﾂｰﾙ ﾍﾔﾉﾅｶﾖｳ"), &game_next_play, SCENE_FIELD_TOOL_INSIDE },
    { nf_str("15:", "ﾕｳﾋﾞﾝｷｮｸ"), &game_next_play, SCENE_POST_OFFICE },
    { nf_str("16:", "start demo 1"), &game_next_play, SCENE_START_DEMO },
    { nf_str("17:", "start demo 2"), &game_next_play, SCENE_START_DEMO2 },
    { nf_str("18:", "ｺｳﾊﾞﾝ"), &game_next_play, SCENE_POLICE_BOX },
    { nf_str("19:", "ﾎﾛﾊﾞｼｬ"), &game_next_play, SCENE_BUGGY },
    { nf_str("20:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ"), &game_next_play, SCENE_PLAYERSELECT },
    { nf_str("21:", "ﾏｲﾙｰﾑ size S"), &game_next_play, SCENE_MY_ROOM_S },
    { nf_str("22:", "ﾏｲﾙｰﾑ size M"), &game_next_play, SCENE_MY_ROOM_M },
    { nf_str("23:", "ﾏｲﾙｰﾑ size L"), &game_next_play, SCENE_MY_ROOM_L },
    { nf_str("24:", "ｺﾝﾋﾞﾆ"), &game_next_play, SCENE_CONVENI },
    { nf_str("25:", "ｽｰﾊﾟｰ"), &game_next_play, SCENE_SUPER },
    { nf_str("26:", "ﾃﾞﾊﾟｰﾄ1F"), &game_next_play, SCENE_DEPART },
    { nf_str("27:", "ﾃｽﾄｺｰｽ 5"), &game_next_play, SCENE_TEST5 },
    { nf_str("28:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 2"), &game_next_play, SCENE_PLAYERSELECT_2 },
    { nf_str("29:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 3"), &game_next_play, SCENE_PLAYERSELECT_3 },
    { nf_str("30:", "ﾃﾞﾊﾟｰﾄ2F"), &game_next_play, SCENE_DEPART_2 },
    { nf_str("31:", "ｲﾍﾞﾝﾄ ｺｸﾁ"), &game_next_play, SCENE_EVENT_ANNOUNCEMENT },
    { nf_str("32:", "ｶﾏｸﾗ"), &game_next_play, SCENE_KAMAKURA },
    { nf_str("33:", "for field tool"), &game_next_play, SCENE_FIELD_TOOL },
    { nf_str("34:", "ｷｬｸﾏﾁ ﾃﾞﾓ"), &game_next_play, SCENE_TITLE_DEMO },
    { nf_str("35:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 4"), &game_next_play, SCENE_PLAYERSELECT_SAVE },
    { nf_str("36:", "museum-ｴﾝﾄﾗﾝｽ"), &game_next_play, SCENE_MUSEUM_ENTRANCE },
    { nf_str("37:", "museum-ｶｲｶﾞ"), &game_next_play, SCENE_MUSEUM_ROOM_PAINTING },
    { nf_str("38:", "museum-ｶｾｷ"), &game_next_play, SCENE_MUSEUM_ROOM_FOSSIL },
    { nf_str("39:", "museum-ｲﾝｾｸﾄ"), &game_next_play, SCENE_MUSEUM_ROOM_INSECT },
    { nf_str("40:", "museum-ﾌｨｯｼｭ"), &game_next_play, SCENE_MUSEUM_ROOM_FISH },
    { nf_str("41:", "ﾏｲﾙｰﾑ size LL1"), &game_next_play, SCENE_MY_ROOM_LL1 },
    { nf_str("42:", "ﾏｲﾙｰﾑ size LL2"), &game_next_play, SCENE_MY_ROOM_LL2 },
    { nf_str("43:", "ﾏｲﾙｰﾑ ﾁｶ -> S"), &game_next_play, SCENE_MY_ROOM_BASEMENT_S },
    { nf_str("44:", "ﾏｲﾙｰﾑ ﾁｶ -> M"), &game_next_play, SCENE_MY_ROOM_BASEMENT_M },
    { nf_str("45:", "ﾏｲﾙｰﾑ ﾁｶ -> L"), &game_next_play, SCENE_MY_ROOM_BASEMENT_L },
    { nf_str("46:", "ﾏｲﾙｰﾑ ﾁｶ -> LL1"), &game_next_play, SCENE_MY_ROOM_BASEMENT_LL1 },
    { nf_str("47:", "ｼﾀﾃﾔ"), &game_next_play, SCENE_NEEDLEWORK },
    { nf_str("48:", "ｼﾏﾉﾌﾟﾚｲﾔﾉｲｴ"), &game_next_play, SCENE_COTTAGE_MY },
    { nf_str("49:", "ｼﾏﾉNPCﾉｲｴ"), &game_next_play, SCENE_COTTAGE_NPC },
    { nf_str("50:", "start demo 3"), &game_next_play, SCENE_START_DEMO3 },
    { nf_str("51:", "LIGHTHOUSE"), &game_next_play, SCENE_LIGHTHOUSE },
    { nf_str("52:", "In Tent"), &game_next_play, SCENE_TENT },
};

static u8 data2fcode(u8 data) {
    u8 fcode = CHAR_SPACE;

    if (data != 0) {
        fcode = data + 0x90;
    }

    return fcode;
}

static u8 fcode2data(u8 fcode) {
    u8 data = 0;
    if (fcode != CHAR_SPACE) {
        data = fcode - 0x90;
    }

    return data;
}

static void select_pass(GAME_SELECT* select) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    namefunc_t* nf_p;
    int field_scene = Common_Get(scene_from_title_demo);
    int sec = rtc_time->sec;
    int min_sec = rtc_time->min * mTM_SECONDS_IN_MINUTE;
    int hour_sec = rtc_time->hour * mTM_SECONDS_IN_HOUR;

    Common_Set(time.now_sec, hour_sec + min_sec + sec);
    nf_p = nf_tbl + field_scene;
    if (nf_p->next_play_proc != NULL) {
        (*nf_p->next_play_proc)((GAME*)select, nf_p->scene_no);
    }

    Common_Set(scene_from_title_demo, -1);
}

static int select_start_proc(GAME_SELECT* select) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int sec = rtc_time->sec;
    int min_sec = rtc_time->min * mTM_SECONDS_IN_MINUTE;
    int hour_sec = rtc_time->hour * mTM_SECONDS_IN_HOUR;

    Common_Set(time.now_sec, hour_sec + min_sec + sec);

    {
        namefunc_t* nf_p = nf_tbl + select->selected_course;
        if (nf_p->next_play_proc != NULL) {
            (*nf_p->next_play_proc)((GAME*)select, nf_p->scene_no);
        }
    }

    Common_Set(select_last_select_no, select->selected_course);
    Common_Set(select_last_top_no, select->top_course);

    if (rtc_time->min == 0) {
        Common_Set(time.time_signal, TRUE);
    }

    {
        int i;

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            Common_Get(now_private)->player_ID.player_name[i] = data2fcode(select->name[i]);
        }
    }

    return TRUE;
}

static int select_check_start(GAME_SELECT* select) {
    if (select->status == 0) {
        if (chkTrigger(BUTTON_START) || chkTrigger(BUTTON_A)) {
            return select_start_proc(select);
        }
    } else if (chkTrigger(BUTTON_START)) {
        return select_start_proc(select);
    }

    return FALSE;
}

typedef int (*SELECT_CHECK_A_BUTTON_PROC)(GAME_SELECT*);

static int select_check_A_button_rtc(GAME_SELECT* select) {
    return FALSE;
}

static int select_check_A_button_time(GAME_SELECT* select) {
    return FALSE;
}

static int select_check_A_button_step(GAME_SELECT* select) {
    return FALSE;
}

static int select_check_A_button_weather(GAME_SELECT* select) {
    u8 save_weather;
    int weather = Common_Get(weather);
    weather++;
    if (weather > mEnv_WEATHER_LEAVES || weather < mEnv_WEATHER_CLEAR) {
        weather = mEnv_WEATHER_CLEAR;
    }

    Common_Set(weather, weather);
    Common_Set(weather_intensity, mEnv_WEATHER_INTENSITY_HEAVY);

    save_weather = mEnv_WEATHER_INTENSITY_HEAVY;
    save_weather |= (u8)weather << 4;
    Save_Set(weather, save_weather);

    return FALSE;
}

static int select_check_A_button_sex(GAME_SELECT* select) {
    int sex = Common_Get(now_private)->gender;
    sex++;
    Common_Get(now_private)->gender = sex % mPr_SEX_NUM;

    return FALSE;
}

static int select_check_A_button_face_type(GAME_SELECT* select) {
    int face_type = Common_Get(now_private)->face;
    face_type++;
    Common_Get(now_private)->face = face_type % mPr_FACE_TYPE_NUM;

    return FALSE;
}

static int select_check_A_button_swell(GAME_SELECT* select) {
    int swell = Common_Get(player_bee_swell_flag);
    Common_Set(player_bee_swell_flag, !swell);

    return FALSE;
}

static int select_check_A_button_sunburn(GAME_SELECT* select) {
    lbRTC_ymd_c renew_time;
    mPr_sunburn_c sunburn = Common_Get(now_private)->sunburn;

    mTM_set_renew_time(&renew_time, Common_GetPointer(time.rtc_time));
    sunburn.last_changed_date = renew_time;

    sunburn.rank++;
    if (sunburn.rank >= mPr_SUNBURN_RANK_NUM) {
        sunburn.rank = mPr_SUNBURN_RANK0;
    }

    sunburn.rankdown_days = 2;
    Common_Get(now_private)->sunburn = sunburn;

    return FALSE;
}

static int select_check_A_button_decoy(GAME_SELECT* select) {
    Common_Set(player_decoy_flag, !Common_Get(player_decoy_flag));

    return FALSE;
}

static int select_check_A_button_cloth(GAME_SELECT* select) {
    return FALSE;
}

static int select_check_A_button_event(GAME_SELECT* select) {
    return FALSE;
}

static int select_check_A_button(GAME_SELECT* select) {
    static SELECT_CHECK_A_BUTTON_PROC process[SELECT_CHECK_A_BUTTON_NUM] = {
        &select_check_A_button_rtc,     &select_check_A_button_time,  &select_check_A_button_step,
        &select_check_A_button_weather, &select_check_A_button_sex,   &select_check_A_button_face_type,
        &select_check_A_button_swell,   &select_check_A_button_decoy, &select_check_A_button_cloth,
        &select_check_A_button_sunburn, &select_check_A_button_event,
    };

    if (chkTrigger(BUTTON_A)) {
        return (*process[select->cursor_y])(select);
    } else {
        return FALSE;
    }
}

static int select_move_cursol(GAME_SELECT* select) {
    if (chkTrigger(BUTTON_DLEFT)) {
        select->status = 0;
        return TRUE;
    } else if (chkTrigger(BUTTON_DUP)) {
        if (select->cursor_y == 0) {
            select->cursor_y = SELECT_CHECK_A_BUTTON_NUM - 1;
        } else {
            select->cursor_y--;
        }
    } else if (chkTrigger(BUTTON_DDOWN)) {
        select->cursor_y = (select->cursor_y + 1) % SELECT_CHECK_A_BUTTON_NUM;
    }

    return FALSE;
}

static int select_course_step_sub(int course) {
    if (course < 0) {
        return course + SCENE_NUM;
    } else if (course >= SCENE_NUM) {
        return course - SCENE_NUM;
    }

    return course;
}

static int select_adjust_top_no(GAME_SELECT* select, int course, int adjust) {
    int top = select->top_course;
    int new_top = (select->top_course + SELECT_COURSE_NUM_VISIBLE) % SCENE_NUM;

    if (top < new_top) {
        if (course <= top || course >= new_top) {
            top = select_course_step_sub(top + adjust);
        }
    } else if (course <= top && course >= new_top) {
        top = select_course_step_sub(top + adjust);
    }

    select->top_course = top;
    return top;
}

static void select_course_step(GAME_SELECT* select, int step_add) {
    int new_step = select->step + step_add;

    if (ABS(new_step) >= 32) {
        int course = select->selected_course;
        sAdo_SysTrgStart(NA_SE_CURSOL);

        if (new_step > 0) {
            new_step = 0;
            course = select_course_step_sub(course + 1);
            select_adjust_top_no(select, course, 1);
        } else {
            new_step = 0;
            course = select_course_step_sub(course - 1);
            select_adjust_top_no(select, course, -1);
        }

        select->step_add = 6;
        select->selected_course = course;
    }

    select->step = new_step;
}

static void select_course(GAME_SELECT* select) {
    int step_add;
    int joystick_y;
    if (chkTrigger(BUTTON_DUP)) {
        if (select->step > 0) {
            select->step = 0;
        }

        select_course_step(select, -32);
        select->step_add = 1;
    } else if (chkButton(BUTTON_DUP)) {
        select_course_step(select, -select->step_add);
    } else if (chkTrigger(BUTTON_DDOWN)) {
        if (select->step < 0) {
            select->step = 0;
        }

        select_course_step(select, 32);
        select->step_add = 1;
    } else if (chkButton(BUTTON_DDOWN)) {
        select_course_step(select, select->step_add);
    } else {
        joystick_y = -getJoystick_Y();
        step_add = select->step_add;

        if (step_add == 0) {
            if (joystick_y < 0) {
                if (select->step > 0) {
                    select->step = 0;
                }

                select_course_step(select, -32);
                select->step_add = 1;
            } else if (joystick_y > 0) {
                if (select->step < 0) {
                    select->step = 0;
                }

                select_course_step(select, 32);
                select->step_add = 1;
            }
        } else {
            if (joystick_y == 0) {
                select->step_add = 0;
            } else if (joystick_y < 0) {
                select_course_step(select, -step_add * 2);
            } else if (joystick_y > 0) {
                select_course_step(select, step_add * 2);
            }
        }
    }
}

typedef void (*SELECT_MOVE_PROC)(GAME_SELECT*);

static void select_move_main(GAME_SELECT* select) {
    if (select_check_start(select) != TRUE) {
        if (chkTrigger(BUTTON_DRIGHT)) {
            select->status = 1;
        } else {
            select_course(select);
        }
    }
}

static void select_move_setup(GAME_SELECT* select) {
    if (select_check_start(select) != TRUE && select_move_cursol(select) != TRUE) {
        if (select_check_A_button(select) == TRUE) {
            return; /* stubbed code */
        }
    }
}

typedef void (*SELECT_MOVE_TIME_PROC)(int);

static int select_advance_button_step(GAME_SELECT* select, int step) {
    int repeats = 0;

#ifdef TARGET_PC
    select->button_step_accum += (f32)select->game.graph->dt_num_60fps_frames;
    while (select->button_step_accum >= 1.0f) {
#endif
        select->button_step += step;
        if (select->button_step == step * 6) {
            repeats++;
            select->button_step = 0;
        }
#ifdef TARGET_PC
        select->button_step_accum -= 1.0f;
    }
#endif

    return repeats;
}

static void select_move_time_year_set(int adjust) {
    int year = Common_Get(time.rtc_time.year);
    year += adjust;

    if (year > lbRTC_YEAR_MAX) {
        year -= ((lbRTC_YEAR_MAX - lbRTC_YEAR_MIN) + 1);
    } else if (year < lbRTC_YEAR_MIN) {
        year = lbRTC_YEAR_MAX - ((lbRTC_YEAR_MIN - 1) - year);
    }

    Common_Set(time.rtc_time.year, year);
}

static void select_move_time_month_set(int adjust) {
    static int season_table[lbRTC_MONTHS_MAX] = {
        mTM_SEASON_WINTER, mTM_SEASON_WINTER, mTM_SEASON_SPRING, mTM_SEASON_SPRING,
        mTM_SEASON_SPRING, mTM_SEASON_SUMMER, mTM_SEASON_SUMMER, mTM_SEASON_SUMMER,
        mTM_SEASON_AUTUMN, mTM_SEASON_AUTUMN, mTM_SEASON_AUTUMN, mTM_SEASON_WINTER,
    };

    int month = Common_Get(time.rtc_time.month) - 1;
    u8 day;
    month = (month + adjust) % lbRTC_MONTHS_MAX;
    Common_Set(time.rtc_time.month, month + 1);

    day = lbRTC_GetDaysByMonth(Common_Get(time.rtc_time.year), month + 1);
    if (Common_Get(time.rtc_time.day) > day) {
        Common_Set(time.rtc_time.day, day);
    }

    Common_Set(time.season, season_table[month]);
}

static void select_move_time_day_set(int adjust) {
    int max_day = lbRTC_GetDaysByMonth(Common_Get(time.rtc_time.year), Common_Get(time.rtc_time.month));
    int day = (Common_Get(time.rtc_time.day) + adjust) % (max_day + 1);

    if (day == 0) {
        if (adjust > 0) {
            day = 1;
        } else {
            day = max_day;
        }
    }

    Common_Set(time.rtc_time.day, day);
}

static void select_move_time_hour_set(int adjust) {
    int hour = Common_Get(time.rtc_time.hour);
    if (hour == 0 && adjust < 0) {
        hour = lbRTC_HOURS_PER_DAY - 1;
    } else {
        hour = (hour + adjust) % lbRTC_HOURS_PER_DAY;
    }

    Common_Set(time.rtc_time.hour, hour);
}

static void select_move_time_min_set(int adjust) {
    int min = Common_Get(time.rtc_time.min);

    if (min == 0 && adjust < 0) {
        min = lbRTC_MINUTES_PER_HOUR - 1;
    } else {
        min = (min + adjust) % lbRTC_MINUTES_PER_HOUR;
    }

    Common_Set(time.rtc_time.min, min);
}

static void select_move_time_week_set(int adjust) {
    static lbRTC_time_c base = {
        0,
        0,
        0, // 00:00:00
        1,
        lbRTC_SATURDAY,
        lbRTC_JANUARY, // Sunday Jan 1st
        2000,
    };

    if (adjust != 0) {
        u32 interval = lbRTC_IntervalTime(Common_GetPointer(time.rtc_time), &base);
        /* minutes -> days */
        interval = interval / (lbRTC_HOURS_PER_DAY * lbRTC_MINUTES_PER_HOUR) + (lbRTC_WEEK - 1);
        Common_Set(time.rtc_time.weekday, interval % lbRTC_WEEK);
    }
}

static void select_move_time_set(GAME_SELECT* select) {
    if (chkTrigger(BUTTON_A) || chkTrigger(BUTTON_START)) {
        select->status = 1;
        if (Common_Get(time.rtc_enabled) == TRUE) {
            lbRTC_SetTime(Common_GetPointer(time.rtc_time));
        }
    } else if (chkTrigger(BUTTON_DLEFT)) {
        if (select->cursor_x == 0) {
            select->cursor_x = 4;
        } else {
            select->cursor_x--;
        }
    } else if (chkTrigger(BUTTON_DRIGHT)) {
        select->cursor_x = (select->cursor_x + 1) % 5;
    } else {
        int adjust = 0;

        if (chkButton(BUTTON_DDOWN)) {
            if (chkTrigger(BUTTON_DDOWN)) {
                adjust = -1;
                select->button_step = -16;
#ifdef TARGET_PC
                select->button_step_accum = 0.0f;
#endif
            }

            adjust -= select_advance_button_step(select, 1);
        }

        if (chkButton(BUTTON_DUP)) {
            if (chkTrigger(BUTTON_DUP)) {
                adjust = 1;
                select->button_step = 16;
#ifdef TARGET_PC
                select->button_step_accum = 0.0f;
#endif
            }

            adjust += select_advance_button_step(select, -1);
        }

        if (chkButton(BUTTON_B)) {
            adjust *= 10;
        }

        {
            static SELECT_MOVE_TIME_PROC process[5] = {
                &select_move_time_year_set, &select_move_time_month_set, &select_move_time_day_set,
                &select_move_time_hour_set, &select_move_time_min_set,
            };

            int i;

            for (i = 0; i < 5; i++) {
                if (i == select->cursor_x) {
                    (*process[i])(adjust);
                    select_move_time_week_set(adjust);
                }
            }

            if (adjust != 0 && Common_Get(time.rtc_enabled) == TRUE) {
                lbRTC_SetTime(Common_GetPointer(time.rtc_time));
            }
        }
    }
}

static void select_move_cloth_sel(GAME_SELECT* select) {
    if (chkTrigger(BUTTON_A) || chkTrigger(BUTTON_START)) {
        select->status = 1;
    } else {
        int cloth = Common_Get(now_private)->cloth.item - ITM_CLOTH001; // shouldn't this be CLOTH000?
        int adjust = (chkButton(BUTTON_B)) ? 10 : 1;

        if (chkButton(BUTTON_DDOWN)) {
            if (chkTrigger(BUTTON_DDOWN)) {
                cloth += adjust;
                select->button_step = -16;
#ifdef TARGET_PC
                select->button_step_accum = 0.0f;
#endif
            }

            cloth += adjust * select_advance_button_step(select, 1);
        }

        if (chkButton(BUTTON_DUP)) {
            if (chkTrigger(BUTTON_DUP)) {
                cloth -= adjust;
                select->button_step = 16;
#ifdef TARGET_PC
                select->button_step_accum = 0.0f;
#endif
            }

            cloth -= adjust * select_advance_button_step(select, -1);
        }

        while (cloth < 0) {
            cloth += CLOTH_NUM;
        }

        while (cloth > CLOTH_NUM - 1) {
            cloth -= CLOTH_NUM;
        }

        Common_Get(now_private)->cloth.item = ITM_CLOTH001 + cloth;
    }
}

static void select_move(GAME_SELECT* select) {
    static SELECT_MOVE_PROC process[SELECT_STATUS_NUM] = {
        &select_move_main,
        &select_move_setup,
        &select_move_time_set,
        &select_move_cloth_sel,
    };

    if (Common_Get(scene_from_title_demo) >= 0) {
        select_pass(select);
    } else {
        (*process[select->status])(select);
    }
}

typedef void (*SELECT_PRINT_PROC)(gfxprint_t*, GAME_SELECT*);

static void select_print_wait(gfxprint_t* gfxprint) {
    static const char* msgs[12] = {
        GFXPRINT_HIRAGANA_MODE_CHAR "ｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ", /* (しばらくお待ち下さい) "Please wait for a bit" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾁｮｯﾄ ﾏｯﾃﾈ",     /* (ちょっと 待ってね) "Wait a minute" */
        GFXPRINT_KATAKANA_MODE_CHAR "ｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",  /* "Wait a moment" */
        GFXPRINT_KATAKANA_MODE_CHAR "ﾛｰﾄﾞ" GFXPRINT_HIRAGANA_MODE_CHAR "ﾁｭｳ", /* (ロード中) "Loading" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾅｳ ﾜｰｷﾝｸﾞ",                              /* "Now working" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ｲﾏ ﾂｸｯﾃﾏｽ",                              /* (今つくってます) "Now making" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ｺｼｮｳｼﾞｬﾅｲﾖ",     /* (故障じゃないよ) "It's not faulty" */
        GFXPRINT_KATAKANA_MODE_CHAR "ｺｰﾋｰ ﾌﾞﾚｲｸ",     /* "coffee break" */
        GFXPRINT_KATAKANA_MODE_CHAR "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ", /* (Bメンヲ セットしてください) "Please set the B menu" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ｼﾞｯﾄ" GFXPRINT_KATAKANA_MODE_CHAR "ｶﾞﾏﾝ" GFXPRINT_HIRAGANA_MODE_CHAR
                                    "ﾉ" GFXPRINT_KATAKANA_MODE_CHAR "ｺ" GFXPRINT_HIRAGANA_MODE_CHAR
                                    "ﾃﾞｱｯﾀ",           /* (ジっと我慢のこであった) "I am patient" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ", /* (今しばらくお待ちください) "Please wait a moment now" */
        GFXPRINT_HIRAGANA_MODE_CHAR "ｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡", /* (あわてないあわてない｡ ひとやすみひとやすみ｡) "Don't
                                                                rush, don't rush. Take a break, take a break." */
    };

    int msg_no;

    gfxprint_locate8x8(gfxprint, 10, 15);
    gfxprint_color(gfxprint, 255, 255, 255, 255);

    msg_no = fqrand() * 12.0f;
    gfxprint_printf(gfxprint, "%s", msgs[msg_no]);
}

static void select_print_course_name(GAME_SELECT* select, gfxprint_t* gfxprint) {
    const char* name;
    int i;

    gfxprint_color(gfxprint, 255, 155, 150, 255);
    gfxprint_locate8x8(gfxprint, 12, 2);
    gfxprint_printf(gfxprint, "FOREST MAP SELECT");

    gfxprint_color(gfxprint, 255, 255, 255, 255);
    for (i = 0; i < 15; i++) {
        int course;

        gfxprint_locate8x8(gfxprint, 5, i + 4);
        course = (select->top_course + i + SCENE_NUM) % SCENE_NUM;
        if (course == select->selected_course) {
            if (select->status != 0) {
                gfxprint_color(gfxprint, 255, 120, 120, 255);

            } else {
                gfxprint_color(gfxprint, 255, 20, 20, 255);
            }
        } else {
            gfxprint_color(gfxprint, 200, 200, 55, 255);
        }

        name = nf_tbl[course].name;
        if (name == NULL) {
            name = "**Null**";
        }

        gfxprint_printf(gfxprint, "%s", name);
    }
}

static void select_print_rtc(gfxprint_t* gfxprint, GAME_SELECT* select) {
    gfxprint_locate8x8(gfxprint, 23, 6);
    gfxprint_printf(gfxprint, "RTC  Z:USE");
}

static void select_print_time_sub(gfxprint_t* gfxprint, GAME_SELECT* select, lbRTC_time_c* time) {
    const char* weekday_name;

    gfxprint_locate8x8(gfxprint, 23, 7);
    gfxprint_printf(gfxprint, "%04d/%02d/%02d", time->year, time->month, time->day);

    gfxprint_locate8x8(gfxprint, 33, 7);
    switch (time->weekday) {
        case lbRTC_SUNDAY:
            weekday_name = "SUN";
            break;

        case lbRTC_MONDAY:
            weekday_name = "MON";
            break;

        case lbRTC_TUESDAY:
            weekday_name = "TUE";
            break;

        case lbRTC_WEDNESDAY:
            weekday_name = "WED";
            break;

        case lbRTC_THURSDAY:
            weekday_name = "THU";
            break;

        case lbRTC_FRIDAY:
            weekday_name = "FRI";
            break;

        case lbRTC_SATURDAY:
            weekday_name = "SAT";
            break;

        default:
            weekday_name = "---";
            break;
    }

    gfxprint_printf(gfxprint, "<%s>", weekday_name);

    gfxprint_locate8x8(gfxprint, 28, 8);
    gfxprint_printf(gfxprint, "%02d:%02d", time->hour, time->min);

    if (select->status == SELECT_STATUS_TIME_SET) {
        gfxprint_color(gfxprint, 255, 180, 180, 255);

        switch (select->cursor_x) {
            case 0: {
                gfxprint_locate8x8(gfxprint, 23, 7);
                gfxprint_printf(gfxprint, "%04d", time->year);
                break;
            }

            case 1: {
                gfxprint_locate8x8(gfxprint, 28, 7);
                gfxprint_printf(gfxprint, "%02d", time->month);
                break;
            }

            case 2: {
                gfxprint_locate8x8(gfxprint, 31, 7);
                gfxprint_printf(gfxprint, "%02d", time->day);
                break;
            }

            case 3: {
                gfxprint_locate8x8(gfxprint, 28, 8);
                gfxprint_printf(gfxprint, "%02d", time->hour);
                break;
            }

            case 4: {
                gfxprint_locate8x8(gfxprint, 31, 8);
                gfxprint_printf(gfxprint, "%02d", time->min);
                break;
            }
        }
    }
}

static void select_print_time(gfxprint_t* gfxprint, GAME_SELECT* select) {
    lbRTC_time_c time;

    lbRTC_GetTime(&time);
    select_print_time_sub(gfxprint, select, &time);
}

static void select_print_step_sub2(gfxprint_t* gfxprint) {
    gfxprint_locate8x8(gfxprint, 23, 9);
    gfxprint_printf(gfxprint, GFXPRINT_KATAKANA_MODE_CHAR "ｽﾃｯﾌﾟ :**m**s");
}

static void select_print_step(gfxprint_t* gfxprint, GAME_SELECT* select) {
    select_print_step_sub2(gfxprint);
}

static void select_print_weather(gfxprint_t* gfxprint, GAME_SELECT* select) {
    static const char* Weather_type[mEnv_WEATHER_NUM] = {
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾊﾚ",    // 晴れ (clear/fine)
        GFXPRINT_HIRAGANA_MODE_CHAR "ｱﾒ",    // 雨 (rain)
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾕｷ",    // 雪 (snow)
        GFXPRINT_HIRAGANA_MODE_CHAR "ｻｸﾗ",   // 桜 (cherry blossoms)
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾗﾝﾀﾞﾑ", // "random" (should be leaves seen in K.K. Slider demo)
    };

    gfxprint_locate8x8(gfxprint, 23, 10);
    gfxprint_printf(gfxprint, GFXPRINT_HIRAGANA_MODE_CHAR "ﾃﾝｷ   :%s", Weather_type[Common_Get(weather)]);
}

static void select_print_sex(gfxprint_t* gfxprint, GAME_SELECT* select) {
    static const char* Distinction[mPr_SEX_NUM] = {
        GFXPRINT_HIRAGANA_MODE_CHAR "ｵﾄｺﾉｺ", // 男の子 (boy)
        GFXPRINT_HIRAGANA_MODE_CHAR "ｵﾝﾅﾉｺ"  // 女の子 (girl)
    };

    gfxprint_locate8x8(gfxprint, 23, 11);
    gfxprint_printf(gfxprint, "ｾｲﾍﾞﾂ :%s", Distinction[Common_Get(now_private)->gender]);
}

static void select_print_cloth(gfxprint_t* gfxprint, GAME_SELECT* select) {
    gfxprint_locate8x8(gfxprint, 23, 15);
    if (select->status == SELECT_STATUS_CLOTH_SEL) {
        gfxprint_color(gfxprint, 255, 180, 180, 255);
    }

    gfxprint_printf(gfxprint, "ﾌｸ    :%03d", Common_Get(now_private)->cloth.item - ITM_CLOTH_START);
}

static void select_print_swell(gfxprint_t* gfxprint, GAME_SELECT* select) {
    int swell = Common_Get(player_bee_swell_flag);
    gfxprint_locate8x8(gfxprint, 23, 13);

    if (swell == FALSE) {
        gfxprint_printf(gfxprint, "ﾑｼｻｻﾚ :ｲﾀｸﾅｲ"); // 虫刺され: 痛くない (sting: painless)
    } else {
        gfxprint_printf(gfxprint, "ﾑｼｻｻﾚ :ｲﾀｿｳ"); // 虫刺され: 痛そう (sting: painful)
    }
}

static void select_print_decoy(gfxprint_t* gfxprint, GAME_SELECT* select) {
    int decoy = Common_Get(player_decoy_flag);
    gfxprint_locate8x8(gfxprint, 23, 14);

    if (decoy == FALSE) {
        gfxprint_printf(gfxprint, "ﾃﾞｰﾀ  :ﾓﾉﾎﾝ"); // (data: genuine)
    } else {
        gfxprint_printf(gfxprint, "ﾃﾞｰﾀ  :ｶｹﾞﾑｼｬ"); // (data: double) [double meaning body double/puppet master]
    }
}

static void select_print_face_type(gfxprint_t* gfxprint, GAME_SELECT* select) {
    static const char* Distinction[mPr_FACE_TYPE_NUM] = {
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ1", GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ2", GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ3",
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ4", GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ5", GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ6",
        GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ7", GFXPRINT_HIRAGANA_MODE_CHAR "ﾀｲﾌﾟ8",
    };

    gfxprint_locate8x8(gfxprint, 23, 12);
    gfxprint_printf(gfxprint, "ｶｵ    :%s", Distinction[Common_Get(now_private)->face]);
}

static void select_print_sunburn(gfxprint_t* gfxprint, GAME_SELECT* select) {
    mPr_sunburn_c* sunburn = &Common_Get(now_private)->sunburn;
    int rank = sunburn->rank;

    gfxprint_locate8x8(gfxprint, 23, 16);
    gfxprint_printf(gfxprint, "ﾋﾔｹ   :%d %d/%d", rank, sunburn->last_changed_date.month,
                    sunburn->last_changed_date.day);
}

static void select_print_event(gfxprint_t* gfxprint, GAME_SELECT* select) {
    static const char* event_kind[] = {
        GFXPRINT_KATAKANA_MODE_CHAR "---",
        GFXPRINT_KATAKANA_MODE_CHAR "ｻﾞｯｶﾔ",   // (雑貨屋) (general store/shop)
        GFXPRINT_KATAKANA_MODE_CHAR "ﾃﾞｻﾞｲﾅ-", // designer
        GFXPRINT_KATAKANA_MODE_CHAR "ﾌﾞﾛ-ｶ-",  // broker
        GFXPRINT_KATAKANA_MODE_CHAR "ｶﾞﾊｸ",    // (画伯) artist
        GFXPRINT_KATAKANA_MODE_CHAR "ｼﾞｭｳﾀﾝ",  // (絨毯) carpet
        GFXPRINT_KATAKANA_MODE_CHAR "ｸﾛﾋｮｳ",   // (黒豹) black panther
    };

    gfxprint_locate8x8(gfxprint, 23, 17);
    gfxprint_printf(gfxprint, GFXPRINT_KATAKANA_MODE_CHAR "ｲﾍﾞﾝﾄ :%s", event_kind[0]);
}

static void select_draw_main(GAME_SELECT* select) {
    static SELECT_PRINT_PROC print_process[11] = {
        &select_print_rtc,   &select_print_time,      &select_print_step,  &select_print_weather,
        &select_print_sex,   &select_print_face_type, &select_print_swell, &select_print_decoy,
        &select_print_cloth, &select_print_sunburn,   &select_print_event,
    };

    rect screen;
    GRAPH* g = select->game.graph;

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);

    DisplayList_initialize(g, 0, 0, 0, NULL);

    {
        screen.top = 0;
        screen.bottom = SCREEN_HEIGHT;
        screen.l = 0;
        screen.r = SCREEN_WIDTH;

        setScissorView(&select->view, &screen);
        showView(&select->view, VIEW_UPDATE_ALL);
    }

    rect_moji(g);

    {
        gfxprint_t* gfxprint_p = __alloca(sizeof(gfxprint_t));
        int i;
        gfxprint_init(gfxprint_p);
        gfxprint_open(gfxprint_p, NOW_POLY_OPA_DISP);

        select_print_course_name(select, gfxprint_p);

        gfxprint_color(gfxprint_p, 200, 200, 55, 255);
        gfxprint_locate8x8(gfxprint_p, 26, 4);
        gfxprint_printf(gfxprint_p, GFXPRINT_HIRAGANA_MODE_CHAR "-ｾｯﾃｲ-"); // -settings-

        for (i = 0; i < 11; i++) {
            if (select->cursor_y == i) {
                if (select->status == SELECT_STATUS_MAIN) {
                    gfxprint_color(gfxprint_p, 180, 180, 255, 255);
                } else {
                    gfxprint_color(gfxprint_p, 120, 120, 255, 255);
                }
            } else {
                gfxprint_color(gfxprint_p, 255, 255, 55, 255);
            }

            (*print_process[i])(gfxprint_p, select);
        }

        SET_POLY_OPA_DISP(gfxprint_close(gfxprint_p));

        gfxprint_cleanup(gfxprint_p);
    }
    CLOSE_DISP(g);
}

static void select_draw_wait(GAME_SELECT* select) {
    GRAPH* g = select->game.graph;

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);

    DisplayList_initialize(g, 0, 0, 0, NULL);

    {
        rect screen;

        screen.top = 0;
        screen.bottom = SCREEN_HEIGHT;
        screen.l = 0;
        screen.r = SCREEN_WIDTH;

        setScissorView(&select->view, &screen);
        showView(&select->view, VIEW_UPDATE_ALL);
    }

    rect_moji(g);
    {
        gfxprint_t* gfxprint_p = __alloca(sizeof(gfxprint_t));

        gfxprint_init(gfxprint_p);
        gfxprint_open(gfxprint_p, NOW_POLY_OPA_DISP);

        select_print_wait(gfxprint_p);

        SET_POLY_OPA_DISP(gfxprint_close(gfxprint_p));

        gfxprint_cleanup(gfxprint_p);
    }
    CLOSE_DISP(g);
}

static void select_draw(GAME_SELECT* select) {
    GRAPH* g = select->game.graph;
    rect screen;

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);

    DisplayList_initialize(g, 0, 0, 0, NULL);

    screen.top = 0;
    screen.bottom = SCREEN_HEIGHT;
    screen.l = 0;
    screen.r = SCREEN_WIDTH;

    setScissorView(&select->view, &screen);
    showView(&select->view, VIEW_UPDATE_ALL);

    if (select->game.doing == FALSE) {
        select_draw_wait(select);
    } else {
        select_draw_main(select);
    }

    CLOSE_DISP(g);
}

static void select_main(GAME* game) {
    GAME_SELECT* select = (GAME_SELECT*)game;

    select_move(select);
    select_draw(select);

    {
        GRAPH* g = game->graph;
        game_debug_draw_last(game, g);
        game_draw_last(g);
    }
}

extern void select_cleanup(GAME* game) {
}

extern void select_init(GAME* game) {
    GAME_SELECT* select = (GAME_SELECT*)game;
    int i;

    game->exec = &select_main;
    game->cleanup = &select_cleanup;

    select->status = SELECT_STATUS_MAIN;
    select->cursor_y = 10;
    select->step = 0;
    select->step_add = 0;
#ifdef TARGET_PC
    select->button_step_accum = 0.0f;
#endif

    initView(&select->view, game->graph);
    select->view.flag = VIEW_UPDATE_SCISSOR | VIEW_UPDATE_ORTHOGRAPHIC;

    select->unk_228[0] = 0;
    select->unk_228[1] = 0;
    select->unk_228[2] = 0;
    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        select->name[i] = fcode2data(Common_Get(now_private)->player_ID.player_name[i]);
    }

    select->selected_course = Common_Get(select_last_select_no);
    select->top_course = Common_Get(select_last_top_no);

    SetGameFrame(1);
    Common_Set(last_scene_no, Save_Get(scene_no));
    Common_Set(submenu_disabled, 0);
    Common_Set(now_private->inventory.loan, 1000);
    mNpc_ClearEventNpc();
    mNpc_ClearMaskNpc();
    mFI_SetClimate(mFI_CLIMATE_0);
    Common_Set(last_scene_no, 0);
}
