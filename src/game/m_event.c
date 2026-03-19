#include "m_event.h"

#include "libultra/libultra.h"
#include "_mem.h"
#include "lb_reki.h"
#include "ac_aprilfool_control_h.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_play.h"
#include "m_scene_table.h"
#include "m_soncho.h"

enum {
    mEv_INIT_NO_RENEWAL,
    mEv_INIT_RENEWAL,
    mEv_INIT_FORCE_RENEWAL,

    mEv_INIT_NUM
};

typedef union ymdh {
    struct {
#ifdef TARGET_PC
        /* LE: swap so raw = (year << 24) | (month << 16) | (day << 8) | hour */
        u8 hour;
        u8 day;
        u8 month;
        u8 year;
#else
        u8 year;
        u8 month;
        u8 day;
        u8 hour;
#endif
    };
    u32 raw;
} mEv_ymdh_u;

#ifdef TARGET_PC
/* Fix schedule data after memcpy from event_schedule_data[].
 * Positional initializers put values in original field order {month,day,_2,hour}
 * but on LE with swapped struct fields, bytes map to {day,month,hour,_2}.
 * Swap paired fields to put values in the correct named fields. */
static void pc_fix_schedule_endian(mEv_schedule_c* s) {
    u8 tmp;
    int i;
    for (i = 0; i < 2; i++) {
        tmp = s->date[i].d.month;
        s->date[i].d.month = s->date[i].d.day;
        s->date[i].d.day = tmp;
        tmp = s->date[i].d._2;
        s->date[i].d._2 = s->date[i].d.hour;
        s->date[i].d.hour = tmp;
    }
}
#endif

static int update_save_area(void);

extern void mEv_ClearSpecialEvent(mEv_special_c* special_event) {
    special_event->kind = -1;
    bzero(&special_event->event, sizeof(mEv_special_u));
    bzero(Common_GetPointer(special_event_common), sizeof(mEv_event_common_u));
}

extern void mEv_ClearEventKabuPeddler(mEv_kabu_peddler_c* kabu_peddler) {
    if (kabu_peddler != NULL) {
        mPr_ClearAnyPersonalID(kabu_peddler->spoken_pids, TOTAL_PLAYER_NUM);
    }
}

extern void mEv_ClearEventSaveInfo(mEv_event_save_c* save_event) {
    mEv_ClearSpecialEvent(&save_event->special);
    mEv_ClearEventKabuPeddler(&save_event->weekly.kabu_peddler);
    save_event->flags = 0;
}

extern void mEv_ClearEventInfo() {
    mEv_event_save_c* event_save = Save_GetPointer(event_save_data);
    u32* event_flag = Common_Get(event_flags);
    int i;

    for (i = 0; i < mEv_EVENT_TYPE_NUM; i++) {
        event_flag[0] = 0;
        event_flag++;
    }

    Common_Get(event_flags[1]) = event_save->flags;
    Common_Get(event_common).fieldday_event_id = -1;
    Common_Get(event_common).fieldday_event_over_status = -1;

}

extern void mEv_EventON(u32 event_kind) {
    u32 type = mEv_GET_TYPE(event_kind);

    if (type < mEv_EVENT_TYPE_NUM) {
        u32* flag_p = Common_GetPointer(event_flags[type]);
        *flag_p |= (1 << mEv_GET_SUBTYPE(event_kind));

        if (type == mEv_SAVED_EVENT) {
            Save_Get(event_save_data).flags = *flag_p;
        }
    }
}

extern void mEv_EventOFF(u32 event_kind) {
    u32 type = mEv_GET_TYPE(event_kind);

    if (type < mEv_EVENT_TYPE_NUM) {
        u32* flag_p = Common_GetPointer(event_flags[type]);
        u32 mask = 1 << mEv_GET_SUBTYPE(event_kind);

        *flag_p &= ~mask;
        if (type == mEv_SAVED_EVENT) {
            Save_Get(event_save_data).flags = *flag_p;
        }
    }
}

extern int mEv_CheckEvent(u32 event_kind) {
    u32 type = mEv_GET_TYPE(event_kind);
    int res = FALSE;

    if (type < mEv_EVENT_TYPE_NUM) {
        u32* flags_p = Common_GetPointer(event_flags[type]);

        if (((*flags_p) >> mEv_GET_SUBTYPE(event_kind)) & 1) {
            res = TRUE;
        }
    }

    return res;
}

extern void mEv_ClearPersonalEventFlag(int player_no) {
    mEv_EventOFF(mEv_SAVED_FIRSTJOB_PLR0 + player_no);
    mEv_EventOFF(mEv_SAVED_FIRSTINTRO_PLR0 + player_no);
    mEv_EventOFF(mEv_SAVED_HRAWAIT_PLR0 + player_no);
    mEv_EventOFF(mEv_SAVED_HRATALK_PLR0 + player_no);
    mEv_EventOFF(mEv_SAVED_FJOPENQUEST_PLR0 + player_no);
    mEv_EventOFF(mEv_SAVED_GATEWAY_PLR0 + player_no);

    {
        aAPC_event_save_data_c* data = (aAPC_event_save_data_c*)mEv_get_save_area(mEv_EVENT_APRILFOOLS_DAY, 0);

        if (data != NULL) {
            data->talk_bitfield[player_no] = 0;
        }
    }
}

extern void mEv_SetFirstJob() {
    if (Common_Get(player_no) < PLAYER_NUM) {
        u32 ev = mEv_SAVED_FIRSTJOB_PLR0;

        ev += Common_Get(player_no);
        mEv_EventON(ev);
    }
}

extern int mEv_CheckRealArbeit() {
    u32 player_no = Common_Get(player_no);
    int res = FALSE;

    if (player_no < PLAYER_NUM && (mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE ||
                                   mEv_CheckEvent(mEv_SAVED_HRAWAIT_PLR0 + player_no) == TRUE)) {
        res = TRUE;
    }

    return res;
}

extern int mEv_CheckArbeit() {
    u32 player_no = Common_Get(player_no);
    int res = FALSE;

    if (player_no < PLAYER_NUM && (mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE ||
                                   mEv_CheckEvent(mEv_SAVED_HRAWAIT_PLR0 + player_no) == TRUE ||
                                   mEv_CheckEvent(mEv_SAVED_HRATALK_PLR0 + player_no) == TRUE)) {
        res = TRUE;
    }

    return res;
}

extern int mEv_CheckFirstJob() {
    u32 player_no = Common_Get(player_no);
    int res = FALSE;

    if (player_no < PLAYER_NUM) {
        u32 ev = mEv_SAVED_FIRSTJOB_PLR0;
        ev += player_no;

        if (mEv_CheckEvent(ev) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

extern void mEv_UnSetFirstJob() {
    u32 player_no = Common_Get(player_no);

    if (player_no < PLAYER_NUM) {
        mEv_EventOFF(mEv_SAVED_FIRSTJOB_PLR0 + player_no);
        mEv_EventON(mEv_SAVED_HRAWAIT_PLR0 + player_no);
    }
}

extern void mEv_SetFirstIntro() {
    u32 player_no = Common_Get(player_no);

    if (player_no < PLAYER_NUM) {
        u32 ev = mEv_SAVED_FIRSTINTRO_PLR0;
        ev += player_no;

        mEv_EventON(ev);
    }
}

extern int mEv_CheckFirstIntro() {
    u32 player_no = Common_Get(player_no);
    int res = FALSE;

    if (player_no < PLAYER_NUM) {
        u32 ev = mEv_SAVED_FIRSTINTRO_PLR0;
        ev += player_no;

        if (mEv_CheckEvent(ev) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

extern void mEv_UnSetFirstIntro() {
    u32 player_no = Common_Get(player_no);

    if (player_no < PLAYER_NUM) {
        u32 ev = mEv_SAVED_FIRSTINTRO_PLR0;
        ev += player_no;
        mEv_EventOFF(ev);
    }
}

extern void mEv_SetGateway() {
    u32 player_no = Common_Get(player_no);

    if (player_no < TOTAL_PLAYER_NUM) {
        u32 ev = mEv_SAVED_GATEWAY_PLR0;
        ev += player_no;
        mEv_EventON(ev);
    }
}

extern int mEv_CheckGateway() {
    u32 player_no = Common_Get(player_no);
    int res = FALSE;

    if (player_no < TOTAL_PLAYER_NUM) {
        u32 ev = mEv_SAVED_GATEWAY_PLR0;
        ev += player_no;

        if (mEv_CheckEvent(ev) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

extern void mEv_UnSetGateway() {
    u32 player_no = Common_Get(player_no);

    if (player_no < TOTAL_PLAYER_NUM) {
        u32 ev = mEv_SAVED_GATEWAY_PLR0;
        ev += player_no;

        mEv_EventOFF(ev);
    }
}

static int title_demo_number = mEv_TITLEDEMO_LOGO;

extern int mEv_CheckTitleDemo() {
    return title_demo_number;
}

extern void mEv_SetTitleDemo(int demo_number) {
    title_demo_number = demo_number;
}

extern void mEv_RenewalDataEveryDay() {
    if (mTM_check_renew_time(mTM_RENEW_TIME_DAILY) == TRUE) {
        int i;

        for (i = 0; i < PLAYER_NUM; i++) {

            u32 check_event = mEv_SAVED_HRAWAIT_PLR0 + i;
            if (mEv_CheckEvent(check_event) == TRUE) {
                /* After a new day starts, turn off all players' 'wait a day' HRA event and turn on talk to Tom Nook HRA
                 * event */
                mEv_EventOFF(check_event);
                mEv_EventON(mEv_SAVED_HRATALK_PLR0 + i);
            }
        }
    }
}

extern void mEv_GetEventWeather(s16* weather, s16* intensity) {
    intensity[0] = mEnv_WEATHER_INTENSITY_HEAVY;

    if (mEv_check_schedule(mEv_EVENT_WEATHER_CLEAR)) {
        weather[0] = mEnv_WEATHER_CLEAR;
    } else if (mEv_check_schedule(mEv_EVENT_WEATHER_SNOW)) {
        weather[0] = mEnv_WEATHER_SNOW;
    } else if (mEv_check_schedule(mEv_EVENT_WEATHER_SPORTS_FAIR)) {
        weather[0] = mEnv_WEATHER_CLEAR;
    } else {
        weather[0] = -1; // no event weather
    }
}

static mEv_event_today_c event_today[mEv_TODAY_EVENT_NUM];
static int n_today_events = 0;

#include "../src/game/m_event_schedule.c_inc"

static int status_edge = 0;

static int event_rumor_table[] = {
    mEv_EVENT_RUMOR_NEW_YEARS_DAY,           mEv_EVENT_RUMOR_KAMAKURA,         mEv_EVENT_RUMOR_VALENTINES_DAY,
    mEv_EVENT_RUMOR_GROUNDHOG_DAY,           mEv_EVENT_RUMOR_APRILFOOLS_DAY,   mEv_EVENT_RUMOR_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_RUMOR_SPRING_SPORTS_FAIR,      mEv_EVENT_RUMOR_HARVEST_FESTIVAL, mEv_EVENT_76,
    mEv_EVENT_RUMOR_FISHING_TOURNEY_1,       mEv_EVENT_TALK_FISHING_TOURNEY_1, mEv_EVENT_RUMOR_MORNING_AEROBICS,
    mEv_EVENT_TALK_MORNING_AEROBICS,         mEv_EVENT_RUMOR_FIREWORKS_SHOW,   mEv_EVENT_76,
    mEv_EVENT_RUMOR_METEOR_SHOWER,           mEv_EVENT_RUMOR_HARVEST_MOON_DAY, mEv_EVENT_RUMOR_FALL_SPORTS_FAIR,
    mEv_EVENT_RUMOR_MUSHROOM_SEASON,         mEv_EVENT_TALK_MUSHROOM_SEASON,   mEv_EVENT_RUMOR_HALLOWEEN,
    mEv_EVENT_RUMOR_FISHING_TOURNEY_2,       mEv_EVENT_TALK_FISHING_TOURNEY_2, mEv_EVENT_RUMOR_TOY_DAY,
    mEv_EVENT_RUMOR_NEW_YEARS_EVE_COUNTDOWN,
};

static int n_event_rumors = ARRAY_COUNT(event_rumor_table);

static u8 index_today[mEv_EVENT_NUM];
static s16 special_event_types[] = {
    mEv_EVENT_SHOP_SALE, mEv_EVENT_DESIGNER,       mEv_EVENT_BROKER_SALE,
    mEv_EVENT_ARTIST,    mEv_EVENT_CARPET_PEDDLER, mEv_EVENT_GYPSY,
};

static int n_special_event_type = ARRAY_COUNT(special_event_types);

static int funeral = 0;
static int dead = 0;
static lbRTC_year_t weekday1st_year = 0;
static lbRTC_weekday_t weekday1st[16];
static int n_rumor;
static int rumor_table[40];

// clang-format off
BSS_ORDER_GROUP_START
    BSS_ORDER_ITEM(n_today_events)
    BSS_ORDER_ITEM(status_edge)
    BSS_ORDER_ITEM(funeral)
    BSS_ORDER_ITEM(dead)
    BSS_ORDER_ITEM(weekday1st_year)
    BSS_ORDER_ITEM(weekday1st)
    BSS_ORDER_ITEM(event_today)
    BSS_ORDER_ITEM(index_today)
    BSS_ORDER_ITEM(n_rumor)
    BSS_ORDER_ITEM(rumor_table)
BSS_ORDER_GROUP_END
// clang-format on

static int last_day_of_month(lbRTC_month_t month) {
    static lbRTC_day_t last_day[lbRTC_MONTHS_MAX] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    lbRTC_year_t year = Common_Get(time.rtc_time.year);
    lbRTC_day_t day = last_day[month - 1];

    if (month != lbRTC_FEBRUARY) {
        return day;
    } else if (lbRTC_IS_LEAPYEAR(year)) {
        return 29;
    } else {
        return 28;
    }
}

static void init_weekday1st() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_month_t month;
    lbRTC_month_t temp;
    lbRTC_month_t i;
    int weekday;

    month = rtc_time->month & 0xF;
    weekday1st_year = rtc_time->year;

    weekday = (rtc_time->weekday + (1 - rtc_time->day)) % lbRTC_WEEK;
    if (weekday < 0) {
        weekday += lbRTC_WEEK;
    }

    weekday1st[month] = weekday;

    for (i = month, temp = month + 1; temp <= lbRTC_MONTHS_MAX; i++, temp++) {
        int last = last_day_of_month(i);
        int t = (weekday1st[i] + (u8)last) % lbRTC_WEEK;

        if (t < 0) {
            t += lbRTC_WEEK;
        }

        weekday1st[temp] = t;
    }

    for (temp = month - 1, i = month; temp >= lbRTC_JANUARY; i--, temp--) {
        lbRTC_day_t last_day = last_day_of_month(temp);

        weekday = (weekday1st[i] - last_day) % lbRTC_WEEK;
        if (weekday < 0) {
            weekday += lbRTC_WEEK;
        }

        weekday1st[temp] = weekday;
    }
}

static int check_date_range(u16 date, u16 lower_bound, u16 upper_bound) {
    int res;

    if (lower_bound > upper_bound) {
        res = FALSE;
        if (lower_bound <= date || date <= upper_bound) {
            res = TRUE;
        }
    } else {
        res = FALSE;
        if (lower_bound <= date && date <= upper_bound) {
            res = TRUE;
        }
    }

    return res;
}

static int check_ymdh_range(u32 ymdh, u32 lower_bound, u32 upper_bound) {
    int res = FALSE;

    if (lower_bound <= ymdh && ymdh <= upper_bound) {
        res = TRUE;
    }

    return res;
}

static u16 after_n_day(u16 month_day, int n_day) {
    mEv_MonthDay_u after;
    u8 day;

    after.raw = month_day;

    if (n_day >= 0) {
        day = last_day_of_month(after.month);

        after.day = after.day + n_day;
        if (after.day > day) {
            if (after.month == lbRTC_DECEMBER) {
                after.month = lbRTC_JANUARY;
            } else {
                after.month++;
            }

            after.day -= day;
        }
    } else {
        after.day = after.day + n_day;
        if ((after.day & 0x80) != 0 || after.day == 0) {
            if (after.month == lbRTC_JANUARY) {
                after.month = lbRTC_DECEMBER;
            } else {
                after.month--;
            }

            day = last_day_of_month(after.month);
            after.day += day;
        }
    }

    return after.raw;
}

extern lbRTC_day_t mEv_get_next_weekday(lbRTC_weekday_t weekday) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_weekday_t next_weekday;
    lbRTC_day_t day;
    lbRTC_day_t last_day;

    if (weekday >= rtc_time->weekday) {
        day = rtc_time->day + (weekday - rtc_time->weekday);
    } else {
        day = rtc_time->day + (lbRTC_WEEK - (rtc_time->weekday - weekday));
    }

    last_day = last_day_of_month(rtc_time->month);

    if (day > last_day) {
        day -= last_day;
    }

    return day;
}

#define mEv_date_decode_weekday(day) ((day) & 0b00000111)     // 0-6 (which weekday, Sunday-Saturday)
#define mEv_date_decode_week(day) (((day) & 0b00111000) >> 3) // 0-5 (which week of the month, 1st, 2nd, 3rd, ...)

static lbRTC_day_t m_weekday2day(lbRTC_month_t month, u8 day_enc) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int week = mEv_date_decode_week(day_enc);       // get the week of the month
    int weekday = mEv_date_decode_weekday(day_enc); // get the weekday
    lbRTC_day_t day = 0;
    int last_day = last_day_of_month(month);

    if (week == mEv_SCHEDULE_EVERY_WEEK) {
        if (month > rtc_time->month) {
            week = 1; /* 1st week of this month */
        } else if (month < rtc_time->month) {
            week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH; /* last weekday of the month */
        } else {
            day = rtc_time->day - (rtc_time->weekday - weekday);

            if (day > (u8)last_day) {
                week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH;
            } else {
                week = 0; /* cleared */
            }
        }
    }

    if (week == mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH) {
        lbRTC_day_t d = last_day;
        int t_day = (-1 + d + weekday1st[month]) % lbRTC_WEEK; /* get the weekday of the first day of next month */

        if (weekday <= t_day) {
            day = d - (t_day - weekday);
        } else {
            day = (d - (t_day - weekday)) - lbRTC_WEEK;
        }
    } else if (week != 0) {
        int t_day = weekday1st[month];

        if (weekday >= t_day) {
            day = 1 + (week - 1) * lbRTC_WEEK + (weekday - t_day);
        } else {
            day = 1 + week * lbRTC_WEEK + (weekday - t_day);
        }
    }

    return day;
}

extern int mEv_weekday2day(lbRTC_month_t month, int week, int weekday) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_day_t day = 0;

    if (week == mEv_SCHEDULE_EVERY_WEEK) {
        if (month > rtc_time->month) {
            week = 1; /* 1st week of this month */
        } else if (month < rtc_time->month) {
            week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH; /* last weekday of the month */
        } else {
            day = rtc_time->day - (rtc_time->weekday - weekday);
            week = 0; /* cleared */
        }
    }

    if (week == mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH) {
        lbRTC_day_t last_day = last_day_of_month(month);
        int t_day =
            (-1 + last_day + weekday1st[month]) % lbRTC_WEEK; /* get the weekday of the first day of next month */

        if (weekday <= t_day) {
            day = last_day - (t_day - weekday);
        } else {
            day = (last_day - (t_day - weekday)) - lbRTC_WEEK;
        }
    } else if (week != 0) {
        int t_day = weekday1st[month];

        if (weekday >= t_day) {
            day = 1 + (week - 1) * lbRTC_WEEK + (weekday - t_day);
        } else {
            day = 1 + week * lbRTC_WEEK + (weekday - t_day);
        }
    }

    return day;
}

static int get_end_time(u32 active_hours) {
    int i;

    if ((active_hours & ((1 << 24) - 1)) == 0) {
        return -1; /* no active hours */
    }

    for (i = 23; i >= 0; i--) {
        if ((active_hours & (1 << 23)) != 0) {
            break;
        }

        active_hours <<= 1; /* move hours left by one bit, MSB is latest hour */
    }

    return i;
}

extern int mEv_get_end_time(int event_type) {
    u8 idx = index_today[event_type];
    mEv_event_today_c* ev_today = &event_today[idx];

    if (idx == 0xFF) {
        return -1;
    } else {
        return get_end_time(ev_today->active_hours);
    }
}

static int search_empty_event_today() {
    int i;

    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        if (event_today[i].type == -1) {
            return i;
        }
    }

    return i;
}

static int add_event_today(u16 month_day, mEv_schedule_c* schedule) {
    mEv_event_today_c* ev_today;
    u8 idx = index_today[schedule->type];
    int res = FALSE;

    if (idx != 0xFF) {
        ev_today = &event_today[idx];
        res = FALSE;
    } else {
        int idx = search_empty_event_today();

        if (idx >= mEv_TODAY_EVENT_NUM) {
            return FALSE;
        }

        index_today[schedule->type] = idx;
        ev_today = &event_today[idx];
        n_today_events++;
    }

    {
        u8 start_hour = schedule->date[0].d.hour;
        u8 end_hour = schedule->date[1].d.hour;
        u32 n;
        lbRTC_hour_t i;

        if ((start_hour & mEv_SCHEDULE_TODAY) != 0) {
            ev_today->begin_date.raw = month_day;
            ev_today->end_date.raw = month_day;
            start_hour &= ~mEv_SCHEDULE_TODAY;
            end_hour &= ~mEv_SCHEDULE_TODAY;
        } else {
            ev_today->begin_date.raw = schedule->date[0].md;
            ev_today->end_date.raw = schedule->date[1].md;
        }

        if ((start_hour & mEv_SCHEDULE_MULTIDAY) != 0) {
            start_hour &= ~mEv_SCHEDULE_MULTIDAY;
            end_hour &= ~mEv_SCHEDULE_MULTIDAY;

            if (month_day != schedule->date[0].md) {
                start_hour = 0;
            }

            if (month_day != schedule->date[1].md) {
                end_hour = 23;
            }
        }

        n = 1;
        for (i = 0; i < 24; i++) {
            if (start_hour <= i && i <= end_hour) {
                ev_today->active_hours |= n;
            }

            n <<= 1;
        }
    }

    ev_today->type = schedule->type;
    ev_today->status |= mEv_STATUS_EXIST;

    return res;
}

static int check_and_clear_event_today(Event_c* event, int type) {
    u8 idx = index_today[type];

    if (idx != 0xFF) {
        mEv_event_today_c* today_event = &event_today[idx];

        if ((today_event->status & mEv_STATUS_EXIST) == FALSE) {
            int flags = 0;
            mEv_place_data_c* place = mEv_get_common_place(today_event->type, 81);

            if (place != NULL && place->block.x == event->block_x && place->block.z == event->block_z) {
                flags |= 0b00000001; // 1, in the block the event is supposed to exist
            }

            if (mEv_check_status(today_event->type, mEv_STATUS_RUN)) {
                flags |= 0b00000010; // 2, event is currently running
                today_event->active_hours = 0x20000000;
            }

            if (type == today_event->type && flags == 0) {
                today_event->type = -1;
                today_event->active_hours = 0;
                today_event->end_date.raw = 0;
                today_event->status = 0;
                n_today_events--;
                index_today[type] = 0xFF;

                return TRUE;
            }
        }
    }

    return FALSE;
}

static int delete_too_short_event(Event_c* event, int type, u32 date) {
    u8 idx = index_today[type];

    if (idx != 0xFF) {
        mEv_event_today_c* today_event = &event_today[idx];
        mEv_schedule_date_u new_date;

        switch (today_event->type) {
            case mEv_EVENT_NEW_YEARS_DAY:
            case mEv_EVENT_GROUNDHOG_DAY:
            case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
            case mEv_EVENT_SPORTS_FAIR_AEROBICS:
            case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
            case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
            case mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL:
            case mEv_EVENT_FISHING_TOURNEY_1:
            case mEv_EVENT_FIREWORKS_SHOW:
            case mEv_EVENT_MORNING_AEROBICS:
            case mEv_EVENT_HARVEST_MOON_FESTIVAL:
            case mEv_EVENT_FISHING_TOURNEY_2:
            case mEv_EVENT_HARVEST_FESTIVAL: {
                new_date.raw = date;
                new_date.d.hour = mEv_get_end_time(today_event->type);

                break;
            }

            case mEv_EVENT_HALLOWEEN:
            case mEv_EVENT_TOY_DAY_JINGLE:
            case mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN: {
                new_date.raw = 0;
                new_date.md = today_event->end_date.raw;
                new_date.d.hour = mEv_get_end_time(today_event->type);

                break;
            }

            default: {
                return FALSE;
            }
        }

        if (new_date.raw != date) {
            return FALSE;
        }

        if (Common_Get(time.rtc_time).min < 55) {
            return FALSE;
        }

        Common_Get(event_common).too_short = type;
    }

    return TRUE;
}

static void init_today_event() {
    int i;

    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        mEv_event_today_c* ev_today = &event_today[i];

        ev_today->type = -1;
        ev_today->active_hours = 0;
        ev_today->begin_date.raw = ev_today->end_date.raw = 0;
        ev_today->status = 0;
    }

    n_today_events = 0;
    for (i = 0; i < mEv_EVENT_NUM; i++) {
        index_today[i] = 0xFF;
    }
}

static void init_time_seat() {
    int i;

    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        mEv_event_today_c* ev_today = &event_today[i];

        ev_today->active_hours = 0;
        ev_today->begin_date.raw = ev_today->end_date.raw = 0;
        ev_today->status &= ~mEv_STATUS_EXIST;
    }
}

static int get_special_event_end_time(s16 event_type) {
    int end_time = 0;

    switch (event_type) {
        case mEv_EVENT_DESIGNER:
            end_time = 5;
            break;
        case mEv_EVENT_ARTIST:
            end_time = 5;
            break;
        case mEv_EVENT_CARPET_PEDDLER:
            end_time = 5;
            break;
        case mEv_EVENT_GYPSY:
            end_time = 20;
            break;
        case mEv_EVENT_BROKER_SALE:
            end_time = 17;
            break;
        case mEv_EVENT_SHOP_SALE:
            end_time = 23;
            break;
    }

    return end_time;
}

#define mEv_MonthDay(m, d) (((u8)(m) << 8) | ((u8)(d)))
#define mEv_MonthDay_GetDay(md) ((md) & 0xFF)
#define mEv_MonthDay_GetMonth(md) (((md) >> 8) & 0xFF)
#define mEv_MonthDay_SetDay(md, d) (((md) & 0xFF00) | (u8)(d))
#define mEv_MonthDay_SetMonth(md, m) (((md) & 0xFF) | ((u8)(m) << 8))

#define mEv_YearMonthDayHour(y, m, d, h) ((u32)(((u8)(y) << 24) | ((u8)(m) << 16) | ((u8)(d) << 8) | ((u8)(h))))

static int init_special_event(int new_event) {
    s16 type;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_special_c* special_ev = &Save_Get(event_save_data).special;
    int res = FALSE;
    int next_event_day_gap;
    u16 sale_day;
    int player_id;
    int seed;
    mEv_MonthDay_u special_monthday[3];
    mEv_MonthDay_u special_end_monthday;
    mEv_schedule_date_u rtc_sched;
    mEv_ymdh_u special_ymdh;
    mEv_ymdh_u rtc_ymdh;
    mEv_ymdh_u special_end_ymdh;
    mEv_save_common_data_c* ev_save_common;
    u16* dates_p;
    s16 event_year;
    int t;

    switch (Common_Get(last_scene_no)) {
        case SCENE_BUGGY:
        case SCENE_BROKER_SHOP: {
            if (gamePT->frame_counter == 0) {
                return FALSE;
            }

            break;
        }
    }

    switch (Save_Get(scene_no)) {
        case SCENE_BUGGY:
        case SCENE_BROKER_SHOP:
            return FALSE;

        case SCENE_SHOP0:
        case SCENE_CONVENI:
        case SCENE_SUPER:
        case SCENE_DEPART:
        case SCENE_DEPART_2: {
            if (Save_Get(event_save_common).special_event.type == mEv_EVENT_SHOP_SALE) {
                return FALSE;
            }
            break;
        }
    }

    ev_save_common = Save_GetPointer(event_save_common);
    dates_p = ev_save_common->dates;
    event_year = Save_Get(event_year);
    type = ev_save_common->special_event.type;

    rtc_sched.raw = 0;
    rtc_sched.d.month = rtc_time->month;
    rtc_sched.d.day = rtc_time->day;

    special_monthday[0].raw = dates_p[mEv_SAVE_DATE_SPECIAL1];

    special_ymdh.raw = (dates_p[mEv_SAVE_DATE_SPECIAL0] << 8) & 0x000FFFF00;
    special_ymdh.year = event_year % 100;

    
    
#if VERSION >= VER_GAFU01_00
    rtc_ymdh.raw = (rtc_sched.md) << 8;
    rtc_ymdh.year = rtc_time->year % 100;
    rtc_ymdh.hour = rtc_time->hour;
    special_end_ymdh.raw = (dates_p[mEv_SAVE_DATE_SPECIAL2] << 8) & 0x000FFFF00;
    t = event_year % 100;
    if (dates_p[mEv_SAVE_DATE_SPECIAL0] > dates_p[mEv_SAVE_DATE_SPECIAL2]) {
        t++;
    }

    special_end_ymdh.year = t;
#else
    rtc_ymdh.raw = (rtc_sched.md) << 8;
    rtc_ymdh.year = rtc_time->year % 100;
    rtc_ymdh.hour = rtc_time->hour;
    special_end_ymdh.raw = (dates_p[mEv_SAVE_DATE_SPECIAL2] << 8) & 0x000FFFF00;
    special_end_ymdh.year = (event_year % 100) + ((dates_p[mEv_SAVE_DATE_SPECIAL0] > dates_p[mEv_SAVE_DATE_SPECIAL2] &&
                                                   dates_p[mEv_SAVE_DATE_SPECIAL0] > rtc_sched.md)
                                                      ? 1
                                                      : 0);
#endif

    special_end_ymdh.hour = get_special_event_end_time(type);

    if (check_ymdh_range(rtc_ymdh.raw, special_ymdh.raw, special_end_ymdh.raw) == FALSE || new_event) {
        int player_id = Common_Get(now_private)->player_ID.player_id;
        int n;
        int seed = player_id;
        int sale_weekday;

        res |= TRUE;
        mEv_ClearSpecialEvent(special_ev);

        player_id = (player_id & 0x00FFFFFF) + 1;
        seed = player_id + (rtc_time->year - rtc_time->month) + rtc_time->day + rtc_time->hour;

        /* Sale Day */
        sale_weekday = m_weekday2day(lbRTC_NOVEMBER, mEv_SCHEDULE_4TH_WEEKDAY(lbRTC_THURSDAY));
        sale_day = (((lbRTC_NOVEMBER) << 8) | sale_weekday);
        sale_day = after_n_day(sale_day, 1);

        while (TRUE) {
            /* Select a new unique random event */
            type = special_event_types[seed % n_special_event_type];
            seed++;

            if (type == Save_Get(event_save_common).special_event.type) {
                continue;
            }

            mFAs_SetFieldRank();
            next_event_day_gap = 1 + ((rtc_time->day + rtc_time->month * rtc_time->sec) %
                                      ((mFAs_FIELDRANK_SIX + 1) - mFAs_GetFieldRank()));

            if (next_event_day_gap == 1) {
                next_event_day_gap = 2; // minimum of 2 days between special events
            }

            special_monthday[0].raw = after_n_day(rtc_sched.md, next_event_day_gap);
// Aus version prevents special events from happening on the last day of the year
#if VERSION >= VER_GAFU01_00
            if (special_monthday[0].raw == mEv_MonthDay(lbRTC_DECEMBER, 31)) {
                special_monthday[0].raw = after_n_day(special_monthday[0].raw, 1);
            }
#endif
            if (rtc_sched.md <= sale_day && sale_day <= special_monthday[0].raw) {
                /* Force the next special event to be Crazy Redd since Sale Day falls between now and the rolled
                 * event date */
                special_monthday[0].raw = sale_day;
                type = mEv_EVENT_BROKER_SALE;
            }

            /* Set event start hour */
            Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3] = 6;

            switch (type) {
                case mEv_EVENT_SHOP_SALE: {
                    lbRTC_day_t last_day = last_day_of_month(special_monthday[0].month);

                    if (special_monthday[0].day != last_day &&
                        (special_monthday[0].raw < mEv_MonthDay(lbRTC_JANUARY, 1) ||
                         special_monthday[0].raw > mEv_MonthDay(lbRTC_JANUARY, 3)) &&
                        mEv_CheckEvent(mEv_SAVED_RENEWSHOP) != TRUE) {
                        /* Set shop sale starting hour randomly between 12PM and 7PM */
                        Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3] = 12 + RANDOM(8);
                        break;
                    }
                    continue;
                }

                case mEv_EVENT_BROKER_SALE: {
                    if (special_monthday[0].raw != mEv_MonthDay(lbRTC_JULY, 4)) {
                        /* Set broker sale start hour to 6PM when it's not the Fireworks Festival */
                        Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3] = 18;
                        break;
                    }
                    continue;
                }

                case mEv_EVENT_GYPSY: {
                    if (special_monthday[0].raw != mEv_MonthDay(lbRTC_DECEMBER, 31)) {
                        Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3] =
                            21; // default event start time is 9pm?
                        break;
                    }
                    continue;
                }
            }

            break;
        }

        special_end_monthday.raw = after_n_day(special_monthday[0].raw, type != mEv_EVENT_SHOP_SALE); // ??
        Save_Get(event_save_common).special_event.type = type;
        dates_p[mEv_SAVE_DATE_SPECIAL0] = rtc_sched.md;             // current date
        dates_p[mEv_SAVE_DATE_SPECIAL1] = special_monthday[0].raw;  // start date
        dates_p[mEv_SAVE_DATE_SPECIAL2] = special_end_monthday.raw; // end date
        Save_Set(event_year, rtc_time->year);
        Save_Get(post_office).leaflet_recipient_flags.event_flags =
            0b1111; // deliver leaflet to all players if necessary for event
    }

    return res;
}

static int update_special_event(mEv_schedule_c* sched) {
    s16 type = Save_Get(event_save_common).special_event.type;
    int active = TRUE;

    switch (sched->type) {
        case mEv_EVENT_ARTIST:
        case mEv_EVENT_BROKER_SALE:
        case mEv_EVENT_DESIGNER:
        case mEv_EVENT_GYPSY:
        case mEv_EVENT_SHOP_SALE:
        case mEv_EVENT_CARPET_PEDDLER: {
            if (type != sched->type) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
                active = FALSE;
            }
            break;
        }

        case mEv_EVENT_HANDBILL_SHOP_SALE: {
            if (type != mEv_EVENT_SHOP_SALE) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
                active = FALSE;
            }
            break;
        }

        case mEv_EVENT_HANDBILL_BROKER: {
            if (type != mEv_EVENT_BROKER_SALE) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
                active = FALSE;
            }
            break;
        }

        default:
            active = FALSE;
            break;
    }

    return active;
}

extern u16 mEv_get_bargain_day() {
    u16 bargain_day = 0;

    if (Save_Get(event_save_common).special_event.type == mEv_EVENT_SHOP_SALE) {
        bargain_day = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL1];
    }

    return bargain_day;
}

static int is_special_event_valid() {
    mEv_schedule_date_u date;

    date.raw = 0;
    date.d.month = Common_Get(time.rtc_time.month);
    date.d.day = Common_Get(time.rtc_time.day);

    return check_date_range(date.md, Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL0],
                            Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL2]);
}

extern u16 mEv_get_special_event_day() {
    u16 day = 0;

    if (is_special_event_valid()) {
        day = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL1];
    }

    return day;
}

extern u16 mEv_get_special_event_type() {
    u16 type = 0;

    if (is_special_event_valid()) {
        type = Save_Get(event_save_common).special_event.type;
    }

    return type;
}

extern int mEv_get_event_place(int event, int* bx, int* bz) {
    mEv_place_data_c* place;

    if (mEv_check_status(event, mEv_STATUS_RUN) != FALSE) {
        place = mEv_get_common_place(event, 81);

        if (place != NULL) {
            *bx = place->block.x;
            *bz = place->block.z;
            return TRUE;
        }
    }

    return FALSE;
}

extern int mEv_bridge_time_check() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);

    return lbRTC_IsEqualDate(Save_Get(bridge).build_date.year, Save_Get(bridge).build_date.month,
                             Save_Get(bridge).build_date.day, rtc_time.year, rtc_time.month, rtc_time.day);
}

static void init_weekly_event() {
    u16 sched_date;
    lbRTC_time_c* rtc_time = &Common_Get(time.rtc_time);
    mEv_kabu_peddler_c* kabu_peddler_data = &Save_Get(event_save_data).weekly.kabu_peddler;
    mEv_MonthDay_u today_date;
    u8 flag = 0;
    u16 ghost_date;
    u16 ghost_date2;
    u16 monday_date;
    u16 friday_date;
    u16* event_dates = Save_Get(event_save_common).dates;

    today_date.month = rtc_time->month;
    today_date.day = rtc_time->day;
    sched_date = event_dates[mEv_SAVE_DATE_WEEKLY];

    switch (rtc_time->weekday) {
        case lbRTC_SUNDAY: {
            /* Update Joan's data */
            if (today_date.raw != sched_date) {
                mEv_ClearEventKabuPeddler(kabu_peddler_data);
                sched_date = today_date.raw;
                event_dates[mEv_SAVE_DATE_WEEKLY] = sched_date;
                Save_Get(event_save_common).weekly_event.type = mEv_EVENT_KABU_PEDDLER;
                flag = 1;
            }
            break;
        }

        case lbRTC_SATURDAY: {
            /* Update K.K. Slider's data */
            if (today_date.raw != sched_date) {
                sched_date = today_date.raw;
                event_dates[mEv_SAVE_DATE_WEEKLY] = sched_date;
                Save_Get(event_save_common).weekly_event.type = mEv_EVENT_KK_SLIDER;
                flag = 1;
            }
            break;
        }

        default: {
            monday_date = after_n_day(today_date.raw, lbRTC_MONDAY - rtc_time->weekday);
            friday_date = after_n_day(today_date.raw, lbRTC_FRIDAY - rtc_time->weekday);

            /* Check if we should reschedule Gulliver */
            if (sched_date == 0 || check_date_range(sched_date, monday_date, friday_date) == FALSE) {
                u8 ofs = 1 + (today_date.raw + rtc_time->hour) % 5;
                /* Schedule a new date for the event between Monday & Friday */
                sched_date = after_n_day(today_date.raw, ofs - rtc_time->weekday);
                event_dates[mEv_SAVE_DATE_WEEKLY] = sched_date;
                Save_Get(event_save_common).weekly_event.type = mEv_EVENT_DOZAEMON; // Gulliver
                Save_Get(event_save_common).dozaemon_completed = FALSE;
            }

            /* Check if Guillver should spawn today */
            if (sched_date == today_date.raw) {
                flag = mEv_EVENT_DOZAEMON;
            }

            break;
        }
    }

    /* Check if we should schedule Tortimer's 3rd bridge event */
    if (rtc_time->weekday == lbRTC_SATURDAY || (rtc_time->weekday != lbRTC_SUNDAY && sched_date != today_date.raw)) {
        /* Gulliver wasn't scheduled today, so check the criteria is met */
        if (Common_Get(player_no) != mPr_FOREIGNER && Save_Get(now_npc_max) >= ANIMAL_NUM_MAX &&
            Save_Get(bridge).exists != TRUE && mSC_LightHouse_travel_check() == FALSE) {
            flag = mEv_EVENT_SONCHO_BRIDGE_MAKE;
        }

        /* Update bridge location seed and date */
        if (flag == mEv_EVENT_SONCHO_BRIDGE_MAKE && Save_Get(event_save_common).bridge_day != today_date.raw) {
            Save_Get(event_save_common).bridge_day = today_date.raw;
            Save_Get(event_save_common).bridge_flags.raw++;
        }
    }

    /* Check if Blanca should spawn */
    if (flag != mEv_EVENT_DOZAEMON && flag != mEv_EVENT_SONCHO_BRIDGE_MAKE &&
        (mGH_check_birth2() || mMC_check_birth())) {
        flag = mEv_EVENT_MASK_NPC;
    }

    /* Initialize Wisp */
    Save_Get(event_save_common).weekly_event.flags = flag;
    Save_Get(event_save_common).ghost_event_type = mEv_EVENT_NUM; // Wisp is not set to spawn
    ghost_date = Save_Get(event_save_common).ghost_day;
    monday_date = after_n_day(today_date.raw, -lbRTC_WEEK);
    friday_date = after_n_day(today_date.raw, 4);

    /* Check if we should refresh Wisp's spawn date */
    if (ghost_date == 0 || check_date_range(ghost_date, monday_date, friday_date) == FALSE) {
        ghost_date = after_n_day(today_date.raw, 2 + RANDOM(3));
        Save_Get(event_save_common).ghost_day = ghost_date;
    }

    /* Spawn Wisp if his scheduled appearance date is within [today-7, today] */
    if (check_date_range(ghost_date, monday_date, today_date.raw)) {
        Save_Get(event_save_common).ghost_event_type = mEv_EVENT_GHOST;
    }
}

static void update_soncho_event(mEv_schedule_c* sched) {
    switch (sched->type) {
        case mEv_EVENT_SONCHO_VACATION_JANUARY:
        case mEv_EVENT_SONCHO_VACATION_FEBRUARY: {
            if (mSC_LightHouse_Event_Start() == FALSE) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_SONCHO_FISHING_TOURNEY_1: {
            if (Save_Get(event_save_common).soncho_event_type != 0xFF) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_SONCHO_FISHING_TOURNEY_2: {
            if (Save_Get(event_save_common).soncho_event_type != 0xFF) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }
    }
}

static void update_soncho_event2(mEv_schedule_c* sched) {
    switch (sched->type) {
        case mEv_EVENT_SONCHO_VACATION_JANUARY:
        case mEv_EVENT_SONCHO_VACATION_FEBRUARY:
        case mEv_EVENT_SONCHO_NEW_YEARS_DAY:
        case mEv_EVENT_SONCHO_GROUNDHOG_DAY:
        case mEv_EVENT_SONCHO_SPRING_SPORTS_FAIR:
        case mEv_EVENT_SONCHO_APRILFOOLS_DAY:
        case mEv_EVENT_SONCHO_CHERRY_BLOSSOM_FESTIVAL:
        case mEv_EVENT_SONCHO_NATURE_DAY:
        case mEv_EVENT_SONCHO_SPRING_CLEANING:
        case mEv_EVENT_SONCHO_MOTHERS_DAY:
        case mEv_EVENT_SONCHO_GRADUATION_DAY:
        case mEv_EVENT_SONCHO_FATHERS_DAY:
        case mEv_EVENT_SONCHO_FISHING_TOURNEY_1:
        case mEv_EVENT_SONCHO_TOWN_DAY:
        case mEv_EVENT_SONCHO_FIREWORKS_SHOW:
        case mEv_EVENT_SONCHO_METEOR_SHOWER:
        case mEv_EVENT_SONCHO_FOUNDERS_DAY:
        case mEv_EVENT_SONCHO_LABOR_DAY:
        case mEv_EVENT_SONCHO_FALL_SPORTS_FAIR:
        case mEv_EVENT_SONCHO_HARVEST_MOON_FESTIVAL:
        case mEv_EVENT_SONCHO_EXPLORERS_DAY:
        case mEv_EVENT_SONCHO_HALLOWEEN:
        case mEv_EVENT_SONCHO_MAYORS_DAY:
        case mEv_EVENT_SONCHO_OFFICERS_DAY:
        case mEv_EVENT_SONCHO_FISHING_TOURNEY_2:
        case mEv_EVENT_SONCHO_HARVEST_FESTIVAL:
        case mEv_EVENT_SONCHO_SALE_DAY:
        case mEv_EVENT_SONCHO_SNOW_DAY:
        case mEv_EVENT_SONCHO_TOY_DAY:
        case mEv_EVENT_TALK_NEW_YEARS_COUNTDOWN: {
            if (Save_Get(event_save_common).weekly_event.flags == mEv_EVENT_SONCHO_BRIDGE_MAKE) {
                Save_Get(event_save_common).weekly_event.flags = 0;
            }

            break;
        }
    }

    /* Update the event type to prefer these events over the fishing tourney event if they coincide */
    switch (sched->type) {
        case mEv_EVENT_SONCHO_FATHERS_DAY:
        case mEv_EVENT_SONCHO_OFFICERS_DAY:
            Save_Get(event_save_common).soncho_event_type = sched->type;
            break;
    }
}

static void update_sports_fair(mEv_schedule_c* sched, lbRTC_day_t* equinox_day) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    switch (sched->type) {
        case mEv_EVENT_SPRING_EQUINOX:
        case mEv_EVENT_SONCHO_SPRING_SPORTS_FAIR: {
            if (rtc_time->month != lbRTC_MARCH || rtc_time->day != lbRk_VernalEquinoxDay(rtc_time->year)) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            } else {
                sched->date[0].d.day = rtc_time->day;
                sched->date[1].d.day = rtc_time->day;
                *equinox_day = rtc_time->day;
            }

            break;
        }

        case mEv_EVENT_RUMOR_SPRING_SPORTS_FAIR: {
            int vernal_day = lbRk_VernalEquinoxDay(rtc_time->year);

            sched->date[0].d.day = vernal_day - 10;
            sched->date[1].d.day = vernal_day - 1;
            break;
        }

        case mEv_EVENT_AUTUMN_EQUINOX:
        case mEv_EVENT_SONCHO_FALL_SPORTS_FAIR: {
            if (rtc_time->month != lbRTC_SEPTEMBER || rtc_time->day != lbRk_AutumnalEquinoxDay(rtc_time->year)) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            } else {
                sched->date[0].d.day = rtc_time->day;
                sched->date[1].d.day = rtc_time->day;
                *equinox_day = rtc_time->day;
            }

            break;
        }

        case mEv_EVENT_RUMOR_FALL_SPORTS_FAIR: {
            int autumnal_day = lbRk_AutumnalEquinoxDay(rtc_time->year);

            sched->date[0].d.day = autumnal_day - 10;
            sched->date[1].d.day = autumnal_day - 1;
            break;
        }

        case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
        case mEv_EVENT_SPORTS_FAIR_AEROBICS:
        case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
        case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
        case mEv_EVENT_SPORTS_FAIR:
        case mEv_EVENT_WEATHER_SPORTS_FAIR: {
            if (*equinox_day == 0) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            } else {
                sched->date[0].d.day = *equinox_day;
                sched->date[1].d.day = *equinox_day;
            }

            break;
        }
    }
}

static void update_event_rumor(mEv_schedule_c* sched) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int equinox_day;

    switch (sched->type) {
        case mEv_EVENT_RUMOR_SPRING_SPORTS_FAIR: {
            equinox_day = lbRk_VernalEquinoxDay(rtc_time->year);
            sched->date[0].d.day = equinox_day - 10;
            sched->date[1].d.day = equinox_day - 1;
            break;
        }

        case mEv_EVENT_TALK_FISHING_TOURNEY_1:
            sched->date[1].d.day =
                lbRTC_Weekly_day(rtc_time->year, lbRTC_JUNE, mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH, lbRTC_SUNDAY);
            break;

        case mEv_EVENT_RUMOR_HARVEST_MOON_DAY: {
            lbRTC_ymd_c harvest_moon_ymd;
            lbRTC_time_c harvest_moon_day;
            lbRTC_day_t beg_day;
            lbRTC_month_t beg_month;
            lbRTC_day_t end_day;
            lbRTC_month_t end_month;

            lbRk_HarvestMoonDay(&harvest_moon_ymd, rtc_time->year);
            harvest_moon_day.year = harvest_moon_ymd.year;
            harvest_moon_day.month = harvest_moon_ymd.month;
            harvest_moon_day.day = harvest_moon_ymd.day;

            /* Calculate rumor end date */
            lbRTC_Sub_DD(&harvest_moon_day, 1);
            end_month = harvest_moon_day.month;
            end_day = harvest_moon_day.day;

            /* Calculate rumor start date */
            lbRTC_Sub_DD(&harvest_moon_day, lbRTC_WEEK - 1);

            beg_month = harvest_moon_day.month;
            beg_day = harvest_moon_day.day;
            sched->date[0].d.month = beg_month;
            sched->date[0].d.day = beg_day;
            sched->date[1].d.month = end_month;
            sched->date[1].d.day = end_day;
            break;
        }

        case mEv_EVENT_RUMOR_FALL_SPORTS_FAIR: {
            equinox_day = lbRk_AutumnalEquinoxDay(rtc_time->year);
            sched->date[0].d.day = equinox_day - 10;
            sched->date[1].d.day = equinox_day - 1;
            break;
        }

        case mEv_EVENT_TALK_FISHING_TOURNEY_2:
            sched->date[1].d.day =
                lbRTC_Weekly_day(rtc_time->year, lbRTC_NOVEMBER, mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH, lbRTC_SUNDAY);
            break;

        case mEv_EVENT_RUMOR_HARVEST_FESTIVAL:
            sched->date[1].d.day =
                lbRTC_Weekly_day(rtc_time->year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) - 1; // 4th Thursday in November
            break;
    }
}

static void update_weekly_event(mEv_schedule_c* sched) {
    s16 type = Save_Get(event_save_common).weekly_event.type;

    switch (sched->type) {
        case mEv_EVENT_KK_SLIDER:
        case mEv_EVENT_KABU_PEDDLER: {
            if (type != sched->type) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_DOZAEMON: {
            if (Save_Get(event_save_common).weekly_event.flags == mEv_EVENT_SONCHO_BRIDGE_MAKE || type != sched->type) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_SONCHO_BRIDGE_MAKE:
        case mEv_EVENT_MASK_NPC: {
            if (Save_Get(event_save_common).weekly_event.flags != sched->type) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_BRIDGE_MAKE: {
            if (Save_Get(bridge).pending != TRUE || Save_Get(bridge).exists || mEv_bridge_time_check() == lbRTC_OVER) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }

        case mEv_EVENT_GHOST: {
            if (Save_Get(event_save_common).ghost_event_type != mEv_EVENT_GHOST) {
                sched->date[1].raw = 0;
                sched->date[0].raw = 0;
            }

            break;
        }
    }
}

// forward declarations
static int clear_active(int type);
static int set_active(int type);

static void update_active(Event_c* event) {
    mEv_place_data_c* place_data;
    mEv_event_today_c* today_event;
    int hour = Common_Get(time.rtc_time.hour);
    int i;

    /* Update active events */
    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        today_event = &event_today[i];

        if (today_event->type != -1 && index_today[today_event->type] != 0xFF) {
            if (mEv_check_status(today_event->type, mEv_STATUS_ERROR) != FALSE) {
                continue;
            }

            if (today_event->type == mEv_EVENT_SPORTS_FAIR &&
                Common_Get(event_common).fieldday_event_over_status != today_event->type) {
                if (clear_active(today_event->type)) {
                    event->changed_num++;
                }

                continue;
            }

            if ((today_event->active_hours & mEv_EVENT_HOUR_START_EVENT)) {
                if (set_active(today_event->type)) {
                    event->changed_num++;
                }

                today_event->active_hours &= ~mEv_EVENT_HOUR_START_EVENT;
            } else if (today_event->type >= mEv_EVENT_ARTIST && today_event->type <= mEv_EVENT_CARPET_PEDDLER &&
                       today_event->type == Save_Get(event_save_common).delete_event_id) {
                if (clear_active(today_event->type)) {
                    event->changed_num++;
                }

                Save_Get(event_save_common).delete_event_id = 0;
                today_event->active_hours = mEv_EVENT_HOUR_CLEAR_EVENT;
            } else if ((today_event->active_hours & (1 << hour))) {
                if (Common_Get(event_common).fieldday_event_over_status != -1 &&
                    (today_event->type == mEv_EVENT_SPORTS_FAIR_BALL_TOSS ||
                     today_event->type == mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR ||
                     today_event->type == mEv_EVENT_SPORTS_FAIR_FOOT_RACE)) {
                    if (clear_active(today_event->type)) {
                        event->changed_num++;
                    }

                    continue;
                }
                if (today_event->type != 0 && today_event->type == Common_Get(event_common).too_short) {
                    today_event->active_hours |= mEv_EVENT_HOUR_TOO_SHORT_EVENT;
                } else if (set_active(today_event->type)) {
                    event->changed_num++;
                }
            } else {
                place_data = mEv_get_common_place(today_event->type, 81);

                if (today_event->type != 0 && today_event->type == Common_Get(event_common).too_short) {
                    Common_Get(event_common).too_short = 0;
                } else if (place_data != NULL) {
                    if (place_data->block.x != event->block_x || place_data->block.z != event->block_z) {
                        if (clear_active(today_event->type)) {
                            event->changed_num++;
                        }
                    }
                } else {
                    if (clear_active(today_event->type)) {
                        event->changed_num++;
                    }
                }
            }
        }

        if ((today_event->active_hours & mEv_EVENT_HOUR_CLEAR_EVENT) &&
            mEv_check_status(today_event->type, mEv_STATUS_RUN) == FALSE) {
            today_event->active_hours = 0;
        }
    }

    /* Update active rumors */
    mEv_clear_rumor();
    for (i = 0; i < n_event_rumors; i++) {
        if (mEv_check_status(event_rumor_table[i], mEv_STATUS_ACTIVE)) {
            mEv_spread_rumor(i);
        }
    }
}

static u32 decode_date(u32 d) {
    mEv_schedule_date_u date;
    mEv_save_common_data_c* ev_common = Save_GetPointer(event_save_common);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int month;
    int day;
    int hour;

    date.raw = d;

    /* Process month */
    month = date.d.month;
    if ((month & mEv_SCHEDULE_USE_SAVE_MONTH)) {
        date.md = Save_Get(event_save_common).dates[month & 0xF];
    } else if ((month & mEv_SCHEDULE_NOW_MONTH)) {
        date.d.month = rtc_time->month;
    } else if ((month & mEv_SCHEDULE_HARVEST_MOON_DATE)) {
        lbRTC_ymd_c harvest_moon_ymd;

        lbRk_HarvestMoonDay(&harvest_moon_ymd, rtc_time->year);
        date.d.month = harvest_moon_ymd.month;
        date.d.day = harvest_moon_ymd.day;
    }

    /* Process day */
    day = date.d.day;
    if ((day & mEv_SCHEDULE_WEEKLY)) {
        date.d.day = m_weekday2day(date.d.month, day & ~mEv_SCHEDULE_DAY_AFTER);

        if ((day & mEv_SCHEDULE_DAY_AFTER)) {
            date.md = after_n_day(date.md, 1);
        }
    } else if ((day & mEv_SCHEDULE_LAST_DAY_OF_MONTH)) {
        date.d.day = last_day_of_month(date.d.month);
    } else if ((day & mEv_SCHEDULE_TOWN_DAY)) {
        date.d.day = (date.d.day & ~mEv_SCHEDULE_TOWN_DAY) | Save_Get(town_day);
    }

    /* Process hour */
    hour = date.d.hour;
    if ((hour & mEv_SCHEDULE_USE_SAVE_SLOT_VALUE)) {
        date.d.hour = Save_Get(event_save_common).dates[(hour & 0x1F) % 8] | (hour & 0xC0);
    }

    return date.raw;
}

static int set_one_time_active(int event) {
    u8 idx = index_today[event];

    if (idx != 0xFF) {
        mEv_event_today_c* ev_today = &event_today[idx];
        ev_today->active_hours |= mEv_EVENT_HOUR_START_EVENT;
        return TRUE;
    }

    return FALSE;
}

static int first_enter_check() {
    switch (Common_Get(last_scene_no)) {
        case SCENE_START_DEMO:
        case SCENE_START_DEMO2:
        case SCENE_PLAYERSELECT:
        case SCENE_PLAYERSELECT_2:
        case SCENE_PLAYERSELECT_3:
        case SCENE_PLAYERSELECT_SAVE:
        case SCENE_START_DEMO3:
            return TRUE;

        default:
            return FALSE;
    }
}

static int effective_scene() {
    switch (Save_Get(scene_no)) {
        case SCENE_START_DEMO:
        case SCENE_START_DEMO2:
        case SCENE_PLAYERSELECT:
        case SCENE_PLAYERSELECT_2:
        case SCENE_PLAYERSELECT_3:
        case SCENE_PLAYERSELECT_SAVE:
        case SCENE_START_DEMO3:
            return FALSE;

        default:
            return TRUE;
    }
}

static void update_schedule_today(Event_c* event) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    // int month;
    u8 equinox_day = 0;
    mEv_schedule_date_u today_date;
    mEv_MonthDay_u birthday_date;
    mEv_schedule_c sched;
    mEv_schedule_c* sched_p = &sched;
    Private_c* priv = &Save_Get(private_data[Common_Get(player_no)]);
    int i;
    int type;

    if (mEv_ArbeitPlayer_kari(Common_Get(player_no)) == FALSE) {
        // month = rtc_time->month;

        today_date.d.month = rtc_time->month;
        today_date.d.day = rtc_time->day;
        today_date.d.hour = rtc_time->hour;
        today_date.d._2 = 0;
        Save_Get(event_save_common).dates[mEv_SAVE_DATE_TODAY] = today_date.md;

        birthday_date.month = priv->birthday.month;
        birthday_date.day = priv->birthday.day;
        Save_Get(event_save_common).dates[mEv_SAVE_DATE_BIRTHDAY] = birthday_date.raw;

        Save_Get(event_save_common).soncho_event_type = 0xFF;

        /* Process every event */
        for (i = 0; i < ARRAY_COUNT(event_schedule_data); i++) {
            memcpy(sched_p, &event_schedule_data[i], sizeof(mEv_schedule_c));
#ifdef TARGET_PC
            pc_fix_schedule_endian(sched_p);
#endif

            /* Perform necessary adjustments */
            update_soncho_event(sched_p);
            update_sports_fair(sched_p, &equinox_day);
            update_event_rumor(sched_p);
            update_special_event(sched_p);
            update_weekly_event(sched_p);

            if (sched.type == mEv_EVENT_SUMMER_CAMPER) {
                mEv_MonthDay_u camper_date;

                switch (today_date.d.month) {
                    case lbRTC_JUNE:
                    case lbRTC_JULY:
                    case lbRTC_AUGUST:
                        sched.date[0].d.month = today_date.d.month;
                        break;
                }

                sched.date[0].raw = decode_date(sched.date[0].raw);
                camper_date.month = sched.date[0].d.month;
                camper_date.day = sched.date[0].d.day;

                /* Move back to the previous week if processing on Sunday */
                if (rtc_time->weekday == lbRTC_SUNDAY) {
                    camper_date.raw = after_n_day(camper_date.raw, -lbRTC_WEEK);
                    sched.date[0].d.month = camper_date.month;
                    sched.date[0].d.day = camper_date.day;
                }

                /* Summer campers only stick around for one day */
                camper_date.raw = after_n_day(camper_date.raw, 1);
                sched.date[1].d.month = camper_date.month;
                sched.date[1].d.day = camper_date.day;
            } else {
                sched.date[0].raw = decode_date(sched.date[0].raw);
                sched.date[1].raw = decode_date(sched.date[1].raw);
            }

            /* Check & add event if it is currently active */
            if (check_date_range(today_date.md, sched.date[0].md, sched.date[1].md)) {
                update_soncho_event2(sched_p);
                add_event_today(today_date.md, sched_p);
            }
        }

        type = 0;
        switch (Common_Get(last_scene_no)) {
            case SCENE_KAMAKURA:
                type = mEv_EVENT_KAMAKURA;
                break;
            case SCENE_BROKER_SHOP:
                type = mEv_EVENT_BROKER_SALE;
                break;
            case SCENE_BUGGY:
                type = mEv_EVENT_GYPSY;
                break;
            case SCENE_SHOP0:
            case SCENE_CONVENI:
            case SCENE_SUPER:
            case SCENE_DEPART:
            case SCENE_DEPART_2:
                if (mEv_CheckEvent(mEv_SPNPC_EVENT)) {
                    type = mEv_EVENT_SHOP_SALE;
                }
                break;
            case SCENE_TENT:
                type = mEv_EVENT_SUMMER_CAMPER;
                break;
        }

        if (type != 0 && gamePT->frame_counter == 0) {
            mEv_schedule_c new_ev_sched = {
                {
                    { 100, 0, 0, 23 },
                    { 100, 0, 0, 0 },
                },
                0,
                0,
            };

            new_ev_sched.type = type;
            new_ev_sched.date[1].d.month = rtc_time->month;
            new_ev_sched.date[0].d.month = rtc_time->month;
            new_ev_sched.date[1].d.day = rtc_time->day;
            new_ev_sched.date[0].d.day = rtc_time->day;
            add_event_today(today_date.md, &new_ev_sched);
            set_one_time_active(type);
        }

        type = 0;
        switch (Save_Get(scene_no)) {
            case SCENE_KAMAKURA:
                type = mEv_EVENT_KAMAKURA;
                break;
            case SCENE_BROKER_SHOP:
                type = mEv_EVENT_BROKER_SALE;
                break;
            case SCENE_BUGGY:
                type = mEv_EVENT_GYPSY;
                break;
            case SCENE_SHOP0:
            case SCENE_CONVENI:
            case SCENE_SUPER:
            case SCENE_DEPART:
            case SCENE_DEPART_2:
                if (mEv_CheckEvent(mEv_SPNPC_EVENT)) {
                    type = mEv_EVENT_SHOP_SALE;
                }
                break;
            case SCENE_TENT:
                type = mEv_EVENT_SUMMER_CAMPER;
                break;
        }

        if (type != 0) {
            mEv_schedule_c new_ev_sched = {
                {
                    { 100, 0, 0, 0 },
                    { 100, 0, 0, 23 },
                },
                0,
                0,
            };

            new_ev_sched.type = type;
            new_ev_sched.date[1].d.month = rtc_time->month;
            new_ev_sched.date[0].d.month = rtc_time->month;
            new_ev_sched.date[1].d.day = rtc_time->day;
            new_ev_sched.date[0].d.day = rtc_time->day;
            add_event_today(today_date.md, &new_ev_sched);
        }

        if (first_enter_check()) {
            for (i = 0; i < mEv_EVENT_NUM; i++) {
                delete_too_short_event(event, i, today_date.raw);
            }
        }

        for (i = 0; i < mEv_EVENT_NUM; i++) {
            check_and_clear_event_today(event, i);
        }
    }
}

static void calc_start_block(int* bx, int* bz) {
    if (Common_Get(door_data).next_scene_id == 0) {
        *bx = 3;
        *bz = 2;

        if (Common_Get(clip).demo_clip != NULL && Common_Get(clip).demo_clip->type == mDemo_CLIP_TYPE_RIDE_OFF_DEMO) {
            *bz = 1;
        }
    } else if (Common_Get(door_data).next_scene_id == SCENE_RANDOM_NPC_TEST) {
        *bx = Common_Get(door_data).exit_position.x / mFI_BK_WORLDSIZE_X;
        *bz = Common_Get(door_data).exit_position.z / mFI_BK_WORLDSIZE_Z;
    }
}

static void init_event(Event_c* event, int renewal_flag) {
    event->month = 99;
    event->day = 99;
    event->hour = 99;
    event->state = 0;
    event->_02 = 0;
    event->changed_num = 0;
    event->block_z = 0;
    event->block_x = 0;

    calc_start_block(&event->block_x, &event->block_z);
    funeral = FALSE;
    dead = FALSE;
    init_today_event();

    if (renewal_flag != mEv_INIT_NO_RENEWAL) {
        mEv_RenewalDataEveryDay();
        init_weekday1st();

        if (init_special_event(FALSE)) {
            Save_Get(event_save_common).special_event.flags = 1;
        }

        init_weekly_event();

        if (mEv_LivePlayer(Common_Get(player_no)) && mEv_LiveSonchoPresent() == FALSE) {
            update_schedule_today(event);
            event->month = Common_Get(time.rtc_time.month);
            event->day = Common_Get(time.rtc_time.day);
            event->hour = Common_Get(time.rtc_time.hour);
            update_active(event);
            update_save_area();
        }
    }
}

extern void mEv_init(Event_c* event) {
    int renewal_flag = mEv_INIT_NO_RENEWAL;

    if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_NONE && effective_scene()) {
        renewal_flag = mEv_INIT_RENEWAL;
    }

    init_event(event, renewal_flag);
}

extern void mEv_init_force(Event_c* event) {
    int renewal_flag = mEv_INIT_NO_RENEWAL;

    if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_NONE) {
        renewal_flag = mEv_INIT_FORCE_RENEWAL;
    }

    init_event(event, renewal_flag);
}

// Aus checks if the save weather is set to rain, not the current weather.
// This would prevent a bug where Morning Aerobics could be scheduled
// in the rain because the previous weather was clear.
#if VERSION >= VER_GAFU01_00
extern void mEv_2nd_init(Event_c* event) {
    /* Disable morning aerobics if it is scheduled and the weather is rain */
    u8 index = index_today[mEv_EVENT_MORNING_AEROBICS];

    if (index != 0xFF && mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather)) == mEnv_WEATHER_RAIN) {
        mEv_event_today_c* ev_today = &event_today[index];

        mEv_clear_status(mEv_EVENT_MORNING_AEROBICS, mEv_STATUS_ACTIVE);
        ev_today->type = -1;
        index_today[mEv_EVENT_MORNING_AEROBICS] = 0xFF;
    }
}
#else
extern void mEv_2nd_init(Event_c* event) {
    /* Disable morning aerobics if it is scheduled and the weather is rain */
    if (Common_Get(weather) == mEnv_WEATHER_RAIN) {
        u8 index = index_today[mEv_EVENT_MORNING_AEROBICS];

        if (index != 0xFF) {
            mEv_event_today_c* ev_today = &event_today[index];

            mEv_clear_status(mEv_EVENT_MORNING_AEROBICS, mEv_STATUS_ACTIVE);
            ev_today->type = -1;
            index_today[mEv_EVENT_MORNING_AEROBICS] = 0xFF;
        }
    }
}
#endif

extern int mEv_PlayerOK() {
    int res = FALSE;

    if (mPlib_able_player_warp_forEvent() && mPlib_Get_unable_wade() == FALSE) {
        res = TRUE;
    }

    return res;
}

extern void mEv_run(Event_c* event) {
    status_edge = 0;

    if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_NONE) {
        if (Save_Get(scene_no) == SCENE_START_DEMO || Save_Get(scene_no) == SCENE_START_DEMO2 ||
            Save_Get(scene_no) == SCENE_START_DEMO3 || Save_Get(scene_no) == SCENE_PLAYERSELECT ||
            Save_Get(scene_no) == SCENE_PLAYERSELECT_2 || Save_Get(scene_no) == SCENE_PLAYERSELECT_3 ||
            Save_Get(scene_no) == SCENE_PLAYERSELECT_SAVE) {
            return;
        }

        /* If the player is transitioning acres update the event's acre */
        if (mFI_CheckPlayerWade(mFI_WADE_START) == TRUE) {
            mFI_GetNextBlockNum(&event->block_x, &event->block_z);
        }

        if (mDemo_CheckDemo() == FALSE && mEv_PlayerOK() && mEv_LivePlayer(Common_Get(player_no)) &&
            mEv_LiveSonchoPresent() == FALSE) {
            lbRTC_day_t hour = (u32)Common_Get(time.rtc_time.hour);
            lbRTC_day_t day = Common_Get(time.rtc_time.day);

            if (event->day != day) {
                mEv_RenewalDataEveryDay();
                event->state = 2;
                init_time_seat();
                init_weekly_event();
                update_schedule_today(event);
                event->month = Common_Get(time.rtc_time.month);
                event->day = day;
                event->hour = hour;
                update_active(event);
                mEv_2nd_init(event);
                mCD_calendar_wellcome_on();
            } else if ((event->hour != hour)) {
                event->hour = hour;
                event->state = 1;
                update_active(event);
            } else if (mFI_CheckPlayerWade(mFI_WADE_END) == TRUE) {
                update_active(event);
            }

            if (funeral) {
                funeral = FALSE;
                update_save_area();
            }
        }

        if (dead != 0) {
            dead--;

            if (dead < 0 || dead > 4) {
                dead = 0;
            }
        }
    }
}

static mActor_name_t l_ev_structure_table[] = { BROKER_TENT,
                                                FORTUNE_TENT,
                                                DESIGNER_CAR,
                                                KAMAKURA,
                                                SAKURA_TABLE0,
                                                AEROBICS_RADIO,
                                                FIREWORKS_STALL0,
                                                FIREWORKS_STALL1,
                                                NEWYEAR_SHRINE0,
                                                NEWYEAR_SHRINE1,
                                                NEWYEAR_TABLE,
                                                NEWYEAR_COUNTDOWN0,
                                                NEWYEAR_COUNTDOWN1,
                                                SPORTSFAIR_BALLS_RED,
                                                SPORTSFAIR_BALLS_WHITE,
                                                SPORTSFAIR_BASKET_RED,
                                                SPORTSFAIR_BASKET_WHITE,
                                                FISHCHECK_STAND0,
                                                FISHCHECK_STAND1,
                                                GHOG,
                                                TENT,
                                                SAKURA_TABLE1 };

static int num_of_l_ev_structure = ARRAY_COUNT(l_ev_structure_table);

extern void mEv_finish(Event_c* event) {
    int ut_x;
    int ut_z;
    int bx;
    int bz;
    int i;
    int bx_max = mFI_GetBlockXMax() - 1;
    int bz_max = mFI_GetBlockZMax() - 1;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG) {

        for (i = 0; i < num_of_l_ev_structure; i++) {
            for (bx = 1; bx < bx_max; bx++) {
                for (bz = 1; bz < bz_max; bz++) {
                    int ut;
                    mActor_name_t structure = l_ev_structure_table[i];

                    for (ut = 0; mFI_SearchFGInBlock(&ut_x, &ut_z, structure, bx, bz); ut) {
                        mFI_SetFGStructure_common(structure, bx, bz, ut_x, ut_z, mFI_SET_STRUCTURE_REMOVE);
                        ut++;
                        if (ut > UT_TOTAL_NUM) {
                            break;
                        }
                    }
                }
            }
        }
    }
}

extern int mEv_check_schedule(int event) {
    int hour = Common_Get(time.rtc_time.hour);
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];

    if (index == 0xFF) {
        return FALSE;
    }

    if ((ev_today->status & mEv_STATUS_STOP)) {
        return FALSE;
    }

    if ((ev_today->active_hours & mEv_EVENT_HOUR_TOO_SHORT_EVENT)) {
        return FALSE;
    }

    if ((ev_today->active_hours & (1 << hour)) != 0) {
        return TRUE;
    }

    return FALSE;
}

extern int mEv_check_run_today(int event) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];

    if (index == 0xFF) {
        return FALSE;
    }

    if ((ev_today->status & mEv_STATUS_STOP)) {
        return FALSE;
    }

    if (ev_today->active_hours != 0) {
        return TRUE;
    }

    return FALSE;
}

extern void mEv_set_status(int event, s16 status) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];

    if (index != 0xFF) {
        if (status == mEv_STATUS_ERROR) {
            ev_today->status = 0;
        }

        status_edge |= status;
        ev_today->status |= status;
    }
}

static int set_active(int event) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];
    int res = FALSE;

    if (index != 0xFF) {
        if ((ev_today->status & mEv_STATUS_ACTIVE) == 0) {
            res = TRUE; // status updated
        }

        status_edge |= mEv_STATUS_ACTIVE;
        ev_today->status |= mEv_STATUS_ACTIVE;
    }

    return res;
}

extern void mEv_clear_status(int event, s16 status) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];

    if (index != 0xFF) {
        ev_today->status &= ~status;
    }
}

static int clear_active(int event) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];
    int res = FALSE;

    if (index != 0xFF) {
        if ((ev_today->status & mEv_STATUS_ACTIVE) != 0) {
            res = TRUE; // status updated
        }

        ev_today->status &= ~mEv_STATUS_ACTIVE;
    }

    return res;
}

extern int mEv_check_status(int event, s16 status) {
    u8 index = index_today[event];
    mEv_event_today_c* ev_today = &event_today[index];

    if (index == 0xFF) {
        return FALSE;
    }

    /* Default to 'false' if the event is in an error state */
    if (status != mEv_STATUS_ERROR && (ev_today->status & mEv_STATUS_ERROR)) {
        return FALSE;
    }

    return (ev_today->status & status) != 0;
}

extern int mEv_check_status_edge(s16 status) {
/* @BUG - developers almost certainly meant to use & here instead of | */
#ifndef BUGFIXES
    if ((status_edge | status) != 0) {
#else
    if ((status_edge & status) != 0) {
#endif
        return TRUE;
    }

    return FALSE;
}

extern void mEv_set_keep(int event) {
    int flags = Common_Get(event_keep_flags[event >> 5]);
    flags |= (1 << (event & 0x1F));
    Common_Set(event_keep_flags[event >> 5], flags);
}

extern void mEv_clear_keep(int event) {
    int flags = Common_Get(event_keep_flags[event >> 5]);
    flags &= ~(1 << (event & 0x1F));
    Common_Set(event_keep_flags[event >> 5], flags);
}

extern int mEv_check_keep(int event) {
    if ((Common_Get(event_keep_flags[event >> 5]) & (1 << (event & 0x1F)))) {
        return TRUE;
    }

    return FALSE;
}

extern u8* mEv_reserve_save_area(int type, u8 id) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int index = index_today[type];
    mEv_event_today_c* ev_today = &event_today[index];
    mEv_save_common_data_c* ev_save_common = Save_GetPointer(event_save_common);
    int i;
    int free_slot_idx = -1;
    u8* data;
    u8* ret;
    int exist_slot = -1;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_save_common->area_use_bitfield) == 0) {
            free_slot_idx = i;
            continue;
        } else if (id != mEv_EVENT_NUM && ev_save_common->area[i].info.id == mEv_EVENT_NUM) {
            exist_slot = i;
        }

        if (type == ev_save_common->area[i].info.type && id == ev_save_common->area[i].info.id) {
            free_slot_idx = i;
            break;
        }
    }

    if (free_slot_idx == -1 && exist_slot != -1) {
        free_slot_idx = exist_slot;
    }

    if (free_slot_idx != -1) {
        mEv_area_c* const area = &ev_save_common->area[free_slot_idx];
        mEv_info_c* const info = &area->info;
        ev_save_common->area_use_bitfield |= (1 << free_slot_idx);
        ev_save_common->area[free_slot_idx].info.type = type;
        ev_save_common->area[free_slot_idx].info.id = id;

        // issue seems to stem from ev_today->begin_date.month being used twice which promotes it to r11?
        if ((u16)ev_today->begin_date.month > (u32)ev_today->end_date.month &&
            (u16)ev_today->begin_date.month > (u32)rtc_time->month) {
            ev_save_common->area[free_slot_idx].info.year = rtc_time->year - 1;
        } else {
            ev_save_common->area[free_slot_idx].info.year = rtc_time->year;
        }

        data = (u8*)ev_save_common->area[free_slot_idx].data;
        ev_save_common->area[free_slot_idx].info.year = rtc_time->year; // ????
        ev_save_common->area[free_slot_idx].info.start_date.month = ev_today->begin_date.month;
        ev_save_common->area[free_slot_idx].info.start_date.day = ev_today->begin_date.day;
        ev_save_common->area[free_slot_idx].info.end_date.month = ev_today->end_date.month;
        ev_save_common->area[free_slot_idx].info.end_date.day = ev_today->end_date.day;
        memset(data, 0, sizeof(ev_save_common->area[free_slot_idx].data));
        ret = data;
    } else {
        ret = NULL;
    }

    return ret;
}

extern u8* mEv_get_save_area(int type, u8 id) {
    mEv_save_common_data_c* ev_save_common = Save_GetPointer(event_save_common);
    int i;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_save_common->area_use_bitfield) != 0) {
            if (type == ev_save_common->area[i].info.type && id == ev_save_common->area[i].info.id) {
                return (u8*)ev_save_common->area[i].data;
            }
        }
    }

    return NULL;
}

extern int mEv_clear_save_area(int type, u8 id) {
    mEv_save_common_data_c* ev_save_common = Save_GetPointer(event_save_common);
    int i;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_save_common->area_use_bitfield) != 0) {
            if (type == ev_save_common->area[i].info.type && id == ev_save_common->area[i].info.id) {
                ev_save_common->area_use_bitfield &= ~(1 << i);
                return sizeof(ev_save_common->area[i].data);
            }
        }
    }

    return 0;
}

static int update_save_area() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_save_common_data_c* ev_save_common = Save_GetPointer(event_save_common);
    int i;
    int num_updated = 0;
    u16 today_date;
    u16 year;
    u16 begin_date;
    u16 end_date;

    mEv_area_c* area;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        area = &ev_save_common->area[i];
        if (((1 << i) & ev_save_common->area_use_bitfield) != 0) {
            if (area->info.start_date.month > area->info.end_date.month &&
                area->info.start_date.month > rtc_time->month) {
                year = rtc_time->year - 1;
            } else {
                year = rtc_time->year;
            }

            today_date = (rtc_time->month << 8) | rtc_time->day;
            begin_date = (area->info.start_date.month << 8) | area->info.start_date.day;
            end_date = (area->info.end_date.month << 8) | area->info.end_date.day;

            if ((mEv_check_status(area->info.type, mEv_STATUS_ACTIVE) == FALSE &&
                 mEv_check_status(area->info.type, mEv_STATUS_RUN) == FALSE &&
                 mEv_ArbeitPlayer(Common_Get(player_no)) == FALSE) ||
                check_date_range(today_date, begin_date, end_date) == FALSE || year != area->info.year) {
                ev_save_common->area_use_bitfield &= ~(1 << i);
                num_updated++;
            }
        }
    }

    return num_updated;
}

extern u8* mEv_reserve_common_area(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;
    int exist_slot = -1;
    u8* data;
    u8* res;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_common->area_use_bitfield) == 0) {
            exist_slot = i;
        } else if (type == ev_common->area[i].info.type && id == ev_common->area[i].info.id) {
            exist_slot = i;
            break;
        }
    }

    if (exist_slot != -1) {
        ev_common->area_use_bitfield |= (1 << exist_slot);
        data = (u8*)ev_common->area[exist_slot].data;
        ev_common->area[exist_slot].info.type = type;
        ev_common->area[exist_slot].info.id = id;
        memset(data, 0, sizeof(ev_common->area[exist_slot].data));
        res = data;
    } else {
        res = NULL;
    }

    return res;
}

extern u8* mEv_get_common_area(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_common->area_use_bitfield) != 0) {
            if (type == ev_common->area[i].info.type && id == ev_common->area[i].info.id) {
                return (u8*)ev_common->area[i].data;
            }
        }
    }

    return NULL;
}

extern int mEv_clear_common_area(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_AREA_NUM; i++) {
        if (((1 << i) & ev_common->area_use_bitfield) != 0) {
            if (type == ev_common->area[i].info.type && id == ev_common->area[i].info.id) {
                ev_common->area_use_bitfield &= ~(1 << i);
                return sizeof(ev_common->area[i].data);
            }
        }
    }

    return 0;
}

extern mEv_place_data_c* mEv_reserve_common_place(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;
    int exist_slot = -1;
    mEv_place_data_c* data;
    mEv_place_data_c* res;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) == 0) {
            exist_slot = i;
        } else if (type == ev_common->place[i].info.type && id == ev_common->place[i].info.id) {
            exist_slot = i;
            break;
        }
    }

    if (exist_slot != -1) {
        ev_common->place_use_bitfield |= (1 << exist_slot);
        data = &ev_common->place[exist_slot].data;
        ev_common->place[exist_slot].info.type = type;
        ev_common->place[exist_slot].info.id = id;
        memset(data, 0, sizeof(ev_common->place[exist_slot].data));
        res = data;
    } else {
        res = NULL;
    }

    return res;
}

extern mEv_place_data_c* mEv_get_common_place(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) != 0) {
            if (type == ev_common->place[i].info.type && id == ev_common->place[i].info.id) {
                return &ev_common->place[i].data;
            }
        }
    }

    return NULL;
}

extern int mEv_clear_common_place(int type, u8 id) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) != 0) {
            if (type == ev_common->place[i].info.type && id == ev_common->place[i].info.id) {
                ev_common->place_use_bitfield &= ~(1 << i);
                return sizeof(ev_common->place[i].data);
            }
        }
    }

    return 0;
}

extern int mEv_use_block_by_other_event(int type, BlockOrUnit_c block) {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) != 0) {
            if (ev_common->place[i].data.block.x == block.x && ev_common->place[i].data.block.z == block.z &&
                ev_common->place[i].info.type != type) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern void mEv_erase_FG_all_in_common_place() {
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) != 0) {
            mEv_place_data_c* place_data = &ev_common->place[i].data;

            if (ITEM_NAME_GET_TYPE(place_data->actor_name) == NAME_TYPE_STRUCT) {
                mFI_SetFGStructure_common(place_data->actor_name, place_data->block.x, place_data->block.z,
                                          place_data->unit.x, place_data->unit.z, mFI_SET_STRUCTURE_REMOVE);
            }
        }
    }
}

extern void mEv_clear_rumor() {
    n_rumor = 0;
}

extern int mEv_spread_rumor(int type) {
    rumor_table[n_rumor++] = type;
    return n_rumor;
}

extern int mEv_get_rumor() {
    if (n_rumor != 0) {
        return rumor_table[gamePT->frame_counter % n_rumor] | mEv_SET(mEv_TYPE_RUMOR, 0);
    }

    return 0;
}

extern void mEv_actor_dying_message(int type, ACTOR* actor) {
    xyz_t pos = actor->world.position;
    mActor_name_t actor_name = actor->npc_id;
    mEv_common_data_c* ev_common = Common_GetPointer(event_common);
    int i;

    for (i = 0; i < mEv_PLACE_NUM; i++) {
        if (((1 << i) & ev_common->place_use_bitfield) != 0) {
            mEv_place_data_c* place_data = &ev_common->place[i].data;

            if (ev_common->place[i].info.type == type && place_data->actor_name == actor_name) {
                /* Check if the actor world position should be transferred to event data */
                if (place_data->flag & 1) {
                    mFI_Wpos2BlockNum(&place_data->block.x, &place_data->block.z, pos);
                    mFI_Wpos2UtNum_inBlock(&place_data->unit.x, &place_data->unit.z, pos);
                }

                funeral = TRUE;
                break;
            }
        }
    }

    mEv_set_status(type, mEv_STATUS_STOP);
    dead = 3;
}

extern int mEv_LiveSonchoPresent() {
    if (Common_Get(demo_profiles[1]) == mAc_PROFILE_PRESENT_DEMO) {
        return TRUE;
    }

    if (Common_Get(clip).demo_clip2 != NULL && Common_Get(clip).demo_clip2->type == mDemo_CLIP_TYPE_PRESENT_DEMO) {
        return TRUE;
    }

    return FALSE;
}

extern int mEv_LivePlayer(u32 player_no) {
    if (mEv_CheckTitleDemo() != mEv_TITLEDEMO_NONE) {
        return FALSE;
    }

    if (Common_Get(reset_flag) != 0) {
        return FALSE;
    }

    if (player_no < mPr_FOREIGNER) {
        if (mEv_CheckEvent(mEv_SAVED_GATEWAY_PLR0 + player_no) == TRUE ||
            mEv_CheckEvent(mEv_SAVED_FIRSTINTRO_PLR0 + player_no) == TRUE) {
            return FALSE;
        }
    } else if (player_no < mPr_PLAYER_NUM) {
        if (mEv_CheckEvent(mEv_SAVED_GATEWAY_PLR0 + player_no) == TRUE) {
            return FALSE;
        }
    } else {
        return FALSE;
    }

    return TRUE;
}

extern int mEv_ArbeitPlayer_kari(u32 player_no) {
    if (player_no < mPr_FOREIGNER && mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE) {
        return TRUE;
    }

    return FALSE;
}

extern int mEv_ArbeitPlayer(u32 player_no) {
    if (player_no < mPr_FOREIGNER && (mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE ||
                                      mEv_CheckEvent(mEv_SAVED_HRAWAIT_PLR0 + player_no) == TRUE)) {
        return TRUE;
    }

    return FALSE;
}

extern void mEv_make_new_special_event() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_schedule_c sched;
    mEv_schedule_date_u today_date;
    mEv_schedule_c* sched_p = &sched;

    today_date.d.month = rtc_time->month;
    today_date.d.day = rtc_time->day;
    today_date.d._2 = 0;
    today_date.d.hour = rtc_time->hour;

    if (init_special_event(TRUE)) {
        int i;

        Save_Get(event_save_common).special_event.flags = 1;
        for (i = 0; i < ARRAY_COUNT(event_schedule_data); i++) {
            memcpy(sched_p, &event_schedule_data[i], sizeof(mEv_schedule_c));
#ifdef TARGET_PC
            pc_fix_schedule_endian(sched_p);
#endif

            if (update_special_event(sched_p)) {
                sched.date[0].raw = decode_date(sched.date[0].raw);
                sched.date[1].raw = decode_date(sched.date[1].raw);

                if (check_date_range(today_date.md, sched.date[0].md, sched.date[1].md)) {
                    add_event_today(today_date.md, sched_p);
                }
            }
        }
    }
}

extern int mEv_GetMonth(Event_c* event) {
    return event->month;
}

extern int mEv_GetDay(Event_c* event) {
    return event->day;
}

extern int mEv_GetHour(Event_c* event) {
    return event->hour;
}

extern void mEv_debug_print4f(gfxprint_t* gfxprint) {
    int i;
    int event_idx = 0;

    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        mEv_event_today_c* ev = &event_today[i];

        if (ev->type != -1 && mEv_check_status(ev->type, mEv_STATUS_ACTIVE)) {
            gfxprint_color(gfxprint, 245, 200, 170, 255);
            gfxprint_locate8x8(gfxprint, 3 + event_idx * 3, 5);
            gfxprint_printf(gfxprint, "%3d", ev->type);
            event_idx++;

            if (event_idx >= 9) {
                if (mEv_check_status(ev->type, mEv_STATUS_ERROR) == FALSE) {
                    gfxprint_color(gfxprint, 245, 150, 120, 255);
                } else if (mEv_check_status(ev->type, mEv_STATUS_RUN)) {
                    gfxprint_color(gfxprint, 180, 150, 160, 255);
                } else {
                    gfxprint_color(gfxprint, 140, 120, 120, 255);
                }

                gfxprint_locate8x8(gfxprint, 9 + event_idx * 3, 5);
                gfxprint_printf(gfxprint, "+");
                break;
            }
        }
    }
}

extern void mEv_sp_debug_print4f(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 245, 200, 170, 255);
    gfxprint_locate8x8(gfxprint, 3, 11);
    gfxprint_printf(gfxprint, "%3d %02d-%02d-%02d", Save_Get(event_save_common).special_event.type,
                    Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL0] & 0xFF, // event rtc (current) day
                    Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL1] & 0xFF, // event begin day
                    Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL2] & 0xFF  // event end day
    );

    gfxprint_locate8x8(gfxprint, 30, 11);
    gfxprint_printf(gfxprint, "%c%c%c%c%c%c%c%c", mEv_CheckTitleDemo() != mEv_TITLEDEMO_NONE ? 'T' : '.', mEv_CheckFirstIntro() ? 'F' : '.',
                    mEv_CheckGateway() ? 'G' : '.', mEv_CheckRealArbeit() ? 'R' : '.', mEv_CheckArbeit() ? 'A' : '.',
                    mDemo_CheckDemo() ? 'D' : '.', !mEv_PlayerOK() ? 'P' : '.',
                    !mEv_LivePlayer(Common_Get(player_no)) ? 'L' : '.');
}

extern int mEv_change(Event_c* event) {
    return event->changed_num;
}

extern int mEv_get_special_event_state() {
    int special_events[] = { mEv_EVENT_SHOP_SALE, mEv_EVENT_DESIGNER,       mEv_EVENT_BROKER_SALE,
                             mEv_EVENT_ARTIST,    mEv_EVENT_CARPET_PEDDLER, mEv_EVENT_GYPSY };

    int active = FALSE;
    int res = mEv_SPECIAL_STATE_UNSCHEDULED;
    mEv_ymdh_u event_date_start;
    mEv_ymdh_u today_date;
    mEv_ymdh_u event_date;
    mEv_ymdh_u today_date_start;
    int event_type;

    if (Save_Get(event_save_data).special.kind <= mEv_SPNPC_END) {
        event_type = special_events[Save_Get(event_save_data).special.kind];
    } else {
        return FALSE;
    }

    today_date.year = 0;
    today_date.month = Common_Get(time.rtc_time.month);
    today_date.day = Common_Get(time.rtc_time.day);
    today_date.hour = Common_Get(time.rtc_time.hour);

    event_date.year = 0;
    event_date.month = Save_Get(event_save_data).special.scheduled.month;
    event_date.day = Save_Get(event_save_data).special.scheduled.day;
    event_date.hour = Save_Get(event_save_data).special.scheduled.hour;

    event_date_start.raw = event_date.raw;
    today_date_start.raw = today_date.raw;

    today_date_start.hour = 0;
    event_date_start.hour = 0;

    if (event_type == mEv_EVENT_SHOP_SALE) {
        if (event_date.raw == today_date.raw) {
            active = TRUE;
        }
    } else if (mEv_check_status(event_type, mEv_STATUS_ACTIVE)) {
        active = TRUE;
    }

    if (active) {
        res = mEv_SPECIAL_STATE_ACTIVE;
    } else if (check_ymdh_range(today_date.raw, event_date_start.raw, event_date.raw)) {
        res = mEv_SPECIAL_STATE_SCHEDULED_TODAY;
    } else if (Save_Get(event_save_data).special.kind != 0xFFFFFFFF && event_date_start.raw > today_date_start.raw) {
        res = mEv_SPECIAL_STATE_SCHEDULED_LATER;
    }

    return res;
}

extern int mEv_snowman_born_check() {
    mEv_ymdh_u snowman_date;
    mEv_ymdh_u today_date;
    mEv_ymdh_u snowman_date_end;

    today_date.year = Common_Get(time.rtc_time).year % 100;
    today_date.month = Common_Get(time.rtc_time).month;
    today_date.day = Common_Get(time.rtc_time).day;
    today_date.hour = Common_Get(time.rtc_time).hour;

    snowman_date.year = Save_Get(snowman_year);
    snowman_date.month = Save_Get(snowman_month);
    snowman_date.day = Save_Get(snowman_day);
    snowman_date.hour = Save_Get(snowman_hour);

    snowman_date_end.raw = snowman_date.raw;
    snowman_date_end.hour = 5;

    if (snowman_date.hour >= 6) {
        mEv_MonthDay_u snowman_monthday;
        mEv_MonthDay_u next_monthday;

        snowman_monthday.month = snowman_date.month;
        snowman_monthday.day = snowman_date.day;
        next_monthday.raw = after_n_day(snowman_monthday.raw, 1);

        if (next_monthday.raw == mEv_MonthDay(lbRTC_JANUARY, 1)) {
            snowman_date_end.year = (snowman_date_end.year + 1) % 100;
        }

        snowman_date_end.month = next_monthday.month;
        snowman_date_end.day = next_monthday.day;
    }

    if (check_ymdh_range(today_date.raw, snowman_date.raw, snowman_date_end.raw)) {
        return FALSE;
    }

    return TRUE;
}

extern int mEv_someone_died() {
    return dead;
}

extern void mEv_special_event_soldout(int type) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    mEv_event_today_c* ev_today = event_today;
    int i;

    for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
        ev_today = &event_today[i];

        if (ev_today->type != -1 && index_today[ev_today->type] != 0xFF &&
            mEv_check_status(ev_today->type, mEv_STATUS_ERROR) == FALSE && ev_today->type == type) {
            if (clear_active(ev_today->type)) {
                play->event.changed_num++;
            }

            ev_today->active_hours = mEv_EVENT_HOUR_CLEAR_EVENT;
        }
    }
}

extern void mEv_toland_clear_common() {
    int* keep_flags = Common_Get(event_keep_flags);
    int i;

    for (i = 0; i < ARRAY_COUNT(Common_Get(event_keep_flags)); i++) {
        keep_flags[i] = 0;
    }

    mem_clear((u8*)Common_GetPointer(event_common), sizeof(Common_Get(event_common)), 0);
    mem_clear((u8*)Common_GetPointer(special_event_common), sizeof(Common_Get(special_event_common)), 0);
}

extern void mGH_animal_return_init() {
    mem_clear((u8*)Save_GetPointer(return_animal), sizeof(Save_Get(return_animal)), 0);
    Save_Get(return_animal).npc_id = EMPTY_NO; // ??
}

extern int mGH_check_birth2() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    Anmret_c* return_animal = Save_GetPointer(return_animal);
    lbRTC_time_c time;

    if (return_animal->npc_id == EMPTY_NO) {
        return FALSE;
    }

    /* Check that it's been less than 1 week since go home event was scheduled */
    lbRTC_TimeCopy(&time, &return_animal->renew_time);
    lbRTC_Add_DD(&time, lbRTC_WEEK);

    if (lbRTC_IsEqualDate(time.year, time.month, time.day, rtc_time->year, rtc_time->month, rtc_time->day) ==
        lbRTC_LESS) {
        return TRUE;
    }

    return FALSE;
}

extern int mGH_check_birth() {
    if ((Save_Get(return_animal).talk_bit & (1 << Common_Get(player_no))) != 0) {
        return FALSE;
    }

    return mGH_check_birth2();
}

extern void mGH_check_delete() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    Anmret_c* return_animal = Save_GetPointer(return_animal);
    Private_c* priv = Save_Get(private_data);

    if (return_animal->npc_id != EMPTY_NO) {
        if (Save_Get(npc_force_go_home) == TRUE) {
            mGH_animal_return_init();
        } else {
            lbRTC_time_c time;

            lbRTC_TimeCopy(&time, &return_animal->renew_time);
            /* Devs did this to fix a 'bug' with lbRTC_Add_DD which only allows going at most one month in the future */
            lbRTC_Add_DD(&time, 20);
            lbRTC_Add_DD(&time, 20);
            lbRTC_Add_DD(&time, 20);

            if (lbRTC_IsEqualDate(time.year, time.month, time.day, rtc_time->year, rtc_time->month, rtc_time->day) !=
                lbRTC_OVER) {
                mGH_animal_return_init();
            } else {
                int i;

                if (mNpc_SearchAnimalinfo(Save_Get(animals), return_animal->npc_id, ANIMAL_NUM_MAX) != -1) {
                    mGH_animal_return_init(); // don't allow this animal to visit if a "version" of it lives in town
                }

                for (i = 0; i < PLAYER_NUM; i++) {
                    if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
                        (return_animal->talk_bit & (1 << i)) == 0) {
                        return;
                    }

                    priv++;
                }

                mGH_animal_return_init();
            }
        }
    }
}

extern void mMC_mask_cat_init() {
    MaskCat_c* mask_cat = Save_GetPointer(mask_cat);
    u8 cloth_no = mask_cat->cloth_no;

    mem_clear((u8*)mask_cat, sizeof(Save_Get(mask_cat)), 0);
    mPr_ClearPersonalID(&mask_cat->design.creator_pid);
    Save_Get(mask_cat).cloth_no = cloth_no;
}

extern int mMC_check_birth() {
    if (Save_Get(mask_cat).design.creator_pid.player_id == 0xFFFF) {
        return FALSE;
    }

    if (Save_Get(mask_cat).talk_idx >= mMC_TALK_IDX_MAX) {
        /* Talked more than the maximum amount of times allowed */
        mMC_mask_cat_init();
        return FALSE;
    }

    return TRUE;
}

extern int mMC_check_birth_day() {
    switch (Common_Get(time.rtc_time.weekday)) {
        case lbRTC_SUNDAY:
        case lbRTC_MONDAY:
        case lbRTC_WEDNESDAY:
        case lbRTC_FRIDAY:
            return FALSE;

        default:
            return mMC_check_birth();
    }
}

extern void mMC_check_delete() {
    MaskCat_c* mask_cat = Save_GetPointer(mask_cat);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (mask_cat->design.creator_pid.player_id != 0xFFFF) {
        lbRTC_time_c max_time;
        lbRTC_time_c min_time;

        lbRTC_TimeCopy(&max_time, &mask_cat->time);
        lbRTC_TimeCopy(&min_time, &mask_cat->time);

        lbRTC_Add_DD(&max_time, lbRTC_WEEK);
        lbRTC_Sub_DD(&min_time, lbRTC_WEEK);

        if (mask_cat->talk_idx >= mMC_TALK_IDX_MAX ||
            lbRTC_IsEqualDate(max_time.year, max_time.month, max_time.day, rtc_time->year, rtc_time->month,
                              rtc_time->day) != lbRTC_OVER ||
            lbRTC_IsEqualDate(min_time.year, min_time.month, min_time.day, rtc_time->year, rtc_time->month,
                              rtc_time->day) != lbRTC_LESS) {
            mMC_mask_cat_init();
        }
    }
}

extern void mMC_set_time() {
    MaskCat_c* mask_cat = Save_GetPointer(mask_cat);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    lbRTC_TimeCopy(&mask_cat->time, rtc_time);
}
