#include "m_calendar_ovl.h"

#include "m_common_data.h"
#include "lb_reki.h"
#include "m_soncho.h"
#include "m_warning_ovl.h"
#include "sys_matrix.h"
#include "m_malloc.h"
#ifdef TARGET_PC
#include <math.h>
#else
#include "libc/math.h"
#endif

static f32 mCD_add_calc_dt(f32* value, f32 target, f32 rate, f32 max_step, f32 min_step) {
    /* add_calc already converts its easing rate and step limits using the graph dt. */
    return add_calc(value, target, rate, max_step, min_step);
}

static u32 mCD_visiter_chk(int player_no, int month, int day) {
    u32 ret = FALSE;

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (Common_Get(player_no) != mPr_FOREIGNER) {
        mCD_player_calendar_c* calendar_p = &Save_Get(private_data[player_no]).calendar;
        int mask = 1 << (day - 1);

        ret = mask & calendar_p->played_days[month - 1];
    }

    return ret;
}

static u32 mCD_sp_soncho_chk(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, mCD_player_calendar_c* calendar) {
    lbRTC_ymd_c harvest_moon_day;
    lbRTC_weekday_t wday;
    u16 chk = (0 << 0);
    u32 ret = FALSE;

    switch (month) {
        case lbRTC_JUNE:
#if VERSION == VER_GAFU01_00
            wday = lbRTC_Week(year, month, day);
#else
            wday = lbRTC_Week(year, month, day + 1);
#endif
            if (wday == lbRTC_SUNDAY && 1 + ((day - wday) / lbRTC_WEEK) == 3) {
                chk = (1 << 0);
            }
            break;
        case lbRTC_JULY:
            if (day == Save_Get(town_day)) {
                chk = (1 << 1);
            }
            break;
        case lbRTC_AUGUST:
            if (day == 12) {
                chk = (1 << 2);
            }

            if (day == 21) {
                chk = (1 << 3);
            }
            break;
        case lbRTC_NOVEMBER:
            if (day == 11) {
                chk = (1 << 6);
            }
            break;
        default:
            lbRk_HarvestMoonDay(&harvest_moon_day, year);
            if (month == harvest_moon_day.month && day == harvest_moon_day.day) {
                chk = (1 << 5) | (1 << 4);
            }
            break;
    }

    if (calendar->event_flags & chk) {
        ret = TRUE;
    }

    return ret;
}

static u32 mCD_soncho_chk(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, int player_no) {
    u32 ret = FALSE;

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (Common_Get(player_no) != mPr_FOREIGNER) {
        mCD_player_calendar_c* calendar = &Save_Get(private_data[player_no]).calendar;
        
        ret = mCD_sp_soncho_chk(year, month, day, calendar);
        if (!ret) {
            ret = calendar->event_days[month - 1] & (1 << (day - 1));
        }
    }

    return ret;
}

static int mCD_make_icon(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, int player_no) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int delta_months = (rtc_time->year - year) * lbRTC_MONTHS_MAX + (rtc_time->month - month);
    int ret = 0;
    
    if (delta_months >= 0 && delta_months < lbRTC_MONTHS_MAX) {
        if (mCD_soncho_chk(year, month, day, player_no)) {
            ret = 2;
        } else if (mCD_visiter_chk(player_no, month, day)) {
            ret = 1;
        }
    }

    return ret;
}

static void mDC_set_string(mCD_Ovl_c* calendar) {
    if (calendar->_1043) {
        int event_idx = calendar->_103C[calendar->_1042] & 0x7F;
        int len = 0;
        u8 string[mCD_EVENT_NAME_STR_LEN];

        mem_clear(string, sizeof(string), CHAR_SPACE);
        if (event_idx == 4) {
            mLd_CopyLandName(string, Save_Get(land_info).name);
            len = mMl_strlen(string, LAND_NAME_SIZE, CHAR_SPACE);
        }

        mSC_get_event_name_str(string + len, sizeof(string) - len, event_idx);
        mem_copy(calendar->event_name_str, string, mCD_EVENT_NAME_STR_LEN);
        calendar->_1034 = 98.0f;
        calendar->_1038 = 0.0f;
        calendar->_1054 = 0;
    }
}

static void mDC_set_disp_table(mCD_Ovl_c* calendar) {
    int entry = calendar->_1056;
    mCD_month_entry_c* entry_p = &calendar->month_entries[entry];
    int i;

    calendar->_1042 = 0;
    calendar->_1043 = 0;

    for (i = 0; i < 6; i++) {
        calendar->_103C[i] = 0;
    }

    for (i = 0; i < entry_p->_72; i++) {
        if (entry_p->_4A[i][0] == calendar->_1057) {
            if (calendar->_1043 >= 6) {
                return;
            }

            calendar->_103C[calendar->_1043] = entry_p->_4A[i][1];
            calendar->_1043++;
        }
    }

    mDC_set_string(calendar);
    calendar->day_type = (entry_p->day_data[calendar->_1057] >> 5) & 7; // probably a struct bitfield
}

static int mDC_weekly_to_day_data(mCD_month_entry_c* entry, int week, u32 days_after) {
    u8* data_p = &entry->day_data[days_after];
    int ret = 0;
    int i;

    for (i = days_after; i < 37; i += lbRTC_WEEK) {
        if ((*data_p & 0x1F) > 0) {
            week--;
        }

        if (week <= 0) {
            ret = *data_p & 0x1F;
            break;
        }

        data_p += lbRTC_WEEK;
    }

    return ret;
}

static lbRTC_day_t mDC_day_to_day_data(mCD_month_entry_c* entry, lbRTC_day_t day) {
    u8* day_p = entry->day_data;
    lbRTC_day_t i;

    for (i = 0; (*day_p & 0x1F) != day && i < 37; i++) {
        day_p++;
    }

    return i;
}

static void mDC_set_disp_event_day(mCD_month_entry_c* entry, lbRTC_day_t day, u8 event) {
    entry->_4A[entry->_72][0] = day;
    entry->_4A[entry->_72][1] = event;
    entry->_72++;
}

static u8 mDC_get_calendar_day_position(mCD_Ovl_c* calendar, lbRTC_day_t day) {
    mCD_month_entry_c* entry = &calendar->month_entries[calendar->_1056];
    lbRTC_day_t i = 0;

    while (TRUE) {
        if (i > 37 || day == (entry->day_data[i] & 0x1F)) {
            break;
        }
        
        i++;
    }

    return i;
}

static void mCD_make_calendar_event_sanka_check(lbRTC_year_t year, lbRTC_month_t month, mCD_month_entry_c* entry, int player_no) {
    lbRTC_day_t day;
    int event;
    int i;

    for (i = 0; i < entry->_72; i++) {
        day = entry->day_data[entry->_4A[i][0]] & 0x1F;
        event = entry->_4A[i][1] & 0x7F;

        if (event == 0x1C) {
            if (mCD_visiter_chk(player_no, month, day)) {
                entry->_4A[i][1] |= 0x80;
            }
        } else if (mCD_calendar_event_check(year, month, day, player_no, event) == TRUE) {
            entry->_4A[i][1] |= 0x80;
        }
    }
}

static void mDC_set_event_day_data(mCD_month_entry_c* entry, lbRTC_month_t month, lbRTC_day_t day, u8 event, u8 day_type, u8 p6) {
    mCD_month_entry_c* month_entry = &entry[month - 1];
    int chg_day = mDC_day_to_day_data(month_entry, day);
    u8* data_p = &month_entry->day_data[chg_day];

    if (p6 == TRUE && ((*data_p >> 5) & 7) == 2) {
        data_p[1] = (data_p[1] & 0x1F) | (2 << 5);
    }

    if (day_type != mCD_DAY_UNDEFINED) {
        data_p[0] = (data_p[0] & 0x1F) | (day_type << 5);
    }

    if (event != 0xFF) {
        mDC_set_disp_event_day(month_entry, chg_day, event);
    }
}

static void mCD_make_calendar_data_init(mCD_month_entry_c* entry) {
    int i;

    for (i = 0; i < 37; i++) {
        entry->day_data[i] = 0;
        entry->_25[i] = 0;
    }
}

static void mCD_make_calendar_data_holiday_and_icon(mCD_month_entry_c* entry, lbRTC_year_t year, lbRTC_month_t month, int player_no) {
    int first_weekday = lbRTC_Week(year, month, 1);
    int days = lbRTC_GetDaysByMonth(year, month);
    int end_day = first_weekday + days;
    int i;
    int day = 1;

    for (i = first_weekday; i < end_day; i++) {
        u8* data_p = &entry->day_data[i];

        *data_p = day;
        entry->_25[i] = mCD_make_icon(year, month, day, player_no);
        if ((i % lbRTC_WEEK) == lbRTC_SUNDAY) {
            *data_p = (*data_p & 0x1F) | (mCD_DAY_FIRST_OF_WEEK << 5);
        } else {
            *data_p = (*data_p & 0x1F) | (1 << 5);
        }

        day++;
    }
}

static void mCD_make_calendar_data_month(mCD_month_entry_c* entry, lbRTC_year_t year, int player_no) {
    lbRTC_month_t month;

    for (month = 0; month < lbRTC_MONTHS_MAX; month++) {
        mCD_make_calendar_data_init(entry);
        mCD_make_calendar_data_holiday_and_icon(entry, year, month + 1, player_no);
        entry++;
    }
}

typedef struct {
    lbRTC_month_t month;
    lbRTC_day_t day;
    u8 event;
} mCD_fixed_event_c;

static void mCD_make_calendar_data_fixed_day_event(mCD_month_entry_c* entry) {
    static mCD_fixed_event_c event_table[] = {
        // clang-format off
        { lbRTC_JANUARY,  1,           mSC_EVENT_NEW_YEARS_DAY},
        {lbRTC_FEBRUARY,  2,           mSC_EVENT_GROUNDHOG_DAY},
        {   lbRTC_APRIL,  1,          mSC_EVENT_APRILFOOLS_DAY},
        {   lbRTC_APRIL,  5, mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL},
        {   lbRTC_APRIL,  6, mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL},
        {   lbRTC_APRIL,  7, mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL},
        {   lbRTC_APRIL, 22,              mSC_EVENT_NATURE_DAY},
        {     lbRTC_MAY,  1,         mSC_EVENT_SPRING_CLEANING},
        {    lbRTC_JULY,  4,          mSC_EVENT_FIREWORKS_SHOW},
        {  lbRTC_AUGUST, 12,           mSC_EVENT_METEOR_SHOWER},
        {  lbRTC_AUGUST, 21,            mSC_EVENT_FOUNDERS_DAY},
        { lbRTC_OCTOBER, 31,               mSC_EVENT_HALLOWEEN},
        {lbRTC_NOVEMBER, 11,            mSC_EVENT_OFFICERS_DAY},
        {lbRTC_DECEMBER,  1,                mSC_EVENT_SNOW_DAY},
        {lbRTC_DECEMBER, 23,                 mSC_EVENT_TOY_DAY},
        {lbRTC_DECEMBER, 31, mSC_EVENT_NEW_YEARS_EVE_COUNTDOWN},
        // clang-format on
    };

    int i;

    for (i = 0; i < ARRAY_COUNT(event_table); i++) {
        mDC_set_event_day_data(entry, event_table[i].month, event_table[i].day, event_table[i].event, mCD_DAY_EVENT, 0);
    }
}

typedef struct {
    u8 month;
    u8 week;
    u8 weekday;
    u8 days_after;
    u8 event;
} mCD_fixed_data_c;

static void mCD_make_calendar_data_unfixed_day_event(mCD_month_entry_c* entry, lbRTC_year_t year) {
    static mCD_fixed_data_c event_table[] = {
        {      lbRTC_MAY, 2,   lbRTC_SUNDAY, 0,      mSC_EVENT_MOTHERS_DAY},
        {     lbRTC_JUNE, 2,   lbRTC_FRIDAY, 0,   mSC_EVENT_GRADUATION_DAY},
        {     lbRTC_JUNE, 3,   lbRTC_SUNDAY, 0,      mSC_EVENT_FATHERS_DAY},
        {lbRTC_SEPTEMBER, 1,   lbRTC_MONDAY, 0,        mSC_EVENT_LABOR_DAY},
        {  lbRTC_OCTOBER, 2,   lbRTC_MONDAY, 0,    mSC_EVENT_EXPLORERS_DAY},
        { lbRTC_NOVEMBER, 1,   lbRTC_MONDAY, 1,       mSC_EVENT_MAYORS_DAY},
        { lbRTC_NOVEMBER, 4, lbRTC_THURSDAY, 0, mSC_EVENT_HARVEST_FESTIVAL},
        { lbRTC_NOVEMBER, 4, lbRTC_THURSDAY, 1,         mSC_EVENT_SALE_DAY},
    };

    lbRTC_ymd_c harvest_moon_day;
    int day;
    mCD_month_entry_c* month_entry;
    int i;
    int j;
    int k;

    for (i = 0; i < ARRAY_COUNT(event_table); i++) {
        lbRTC_day_t day = mDC_weekly_to_day_data(&entry[event_table[i].month - 1], event_table[i].week, event_table[i].weekday);
        
        day += event_table[i].days_after;
        mDC_set_event_day_data(entry, event_table[i].month, day, event_table[i].event, mCD_DAY_EVENT, 0);
    }

    month_entry = &entry[lbRTC_JUNE - 1];
    for (j = 0; j < 37; j += lbRTC_WEEK) {
        int day = month_entry->day_data[j] & 0x1F;

        if (day > 0) {
            mDC_set_event_day_data(entry, lbRTC_JUNE, day, mSC_EVENT_FISHING_TOURNEY_1, mCD_DAY_EVENT, 0);
        }
    }

    month_entry = &entry[lbRTC_NOVEMBER - 1];
    for (k = 0; k < 37; k += lbRTC_WEEK) {
        int day = month_entry->day_data[k] & 0x1F;

        if (day > 0) {
            mDC_set_event_day_data(entry, lbRTC_NOVEMBER, day, mSC_EVENT_FISHING_TOURNEY_2, mCD_DAY_EVENT, 0);
        }
    }

    day = lbRk_VernalEquinoxDay(year);
    mDC_set_event_day_data(entry, lbRTC_MARCH, day, mSC_EVENT_SPRING_SPORTS_FAIR, mCD_DAY_EVENT, 0);

    day = lbRk_AutumnalEquinoxDay(year);
    mDC_set_event_day_data(entry, lbRTC_SEPTEMBER, day, mSC_EVENT_FALL_SPORTS_FAIR, mCD_DAY_EVENT, 0);

    mDC_set_event_day_data(entry, lbRTC_JULY, (lbRTC_day_t)Save_Get(town_day), mSC_EVENT_TOWN_DAY, mCD_DAY_EVENT, 0);
    
    lbRk_HarvestMoonDay(&harvest_moon_day, year);
    mDC_set_event_day_data(entry, harvest_moon_day.month, harvest_moon_day.day, mSC_EVENT_HARVEST_MOON_FESTIVAL, mCD_DAY_EVENT, 0);
}

static void mCD_make_calendar_data_year(lbRTC_year_t year, mCD_month_entry_c* entry, int player_no) {
    mPr_birthday_c* birthday;
    int i;
    
    mCD_make_calendar_data_month(entry, year, player_no);
    mCD_make_calendar_data_fixed_day_event(entry);
    mCD_make_calendar_data_unfixed_day_event(entry, year);

    birthday = &Save_Get(private_data[player_no]).birthday;
    if (birthday->month != 0xFF) {
        mDC_set_event_day_data(entry, birthday->month, birthday->day, mSC_EVENT_PLAYER_BIRTHDAY, 5, 0);
    }

    for (i = lbRTC_JANUARY; i <= lbRTC_DECEMBER; i++) {
        mCD_make_calendar_event_sanka_check(year, i, &entry[i - 1], player_no);
    }
}

static void mCD_make_calendar_data(mCD_Ovl_c* calendar, int player_no) {
    int i;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mCD_month_entry_c* entry;
    int day_pos;


    for (i = 0; i < mCD_YEARS_SHOWN; i++) {
        mCD_make_calendar_data_year(rtc_time->year + i - 1, &calendar->month_entries[i * lbRTC_MONTHS_MAX], player_no);
    }

    calendar->_1056 = rtc_time->month + lbRTC_MONTHS_MAX - 1;
    calendar->_1059 = calendar->_1056;
    day_pos = mDC_get_calendar_day_position(calendar, rtc_time->day);


    entry = calendar->month_entries + calendar->_1056;
    entry->day_data[day_pos] = (entry->day_data[day_pos] & 0x1F) | (mCD_DAY_CURRENT << 5);
}

static void mCD_stick_area_check(Submenu* submenu) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;

    if (gamePT->mcon.adjusted_pR < 0.2f) {
        calendar->stick_area = mCD_STICK_AREA_CENTER;
    } else {
        s16 angle = gamePT->mcon.move_angle;

        if (angle < DEG2SHORT_ANGLE2(-157.5f)) {
            calendar->stick_area = mCD_STICK_AREA_LEFT;
        } else if (angle < DEG2SHORT_ANGLE2(-112.5f)) {
            calendar->stick_area = mCD_STICK_AREA_CENTER;
        } else if (angle < DEG2SHORT_ANGLE2(-67.5f)) {
            calendar->stick_area = mCD_STICK_AREA_BOTTOM;
        } else if (angle < DEG2SHORT_ANGLE2(-22.5f)) {
            calendar->stick_area = mCD_STICK_AREA_CENTER;
        } else if (angle < DEG2SHORT_ANGLE2(22.5f)) {
            calendar->stick_area = mCD_STICK_AREA_RIGHT;
        } else if (angle < DEG2SHORT_ANGLE2(67.5f)) {
            calendar->stick_area = mCD_STICK_AREA_CENTER;
        } else if (angle < DEG2SHORT_ANGLE2(112.5f)) {
            calendar->stick_area = mCD_STICK_AREA_TOP;
        } else if (angle < DEG2SHORT_ANGLE2(157.5f)) {
            calendar->stick_area = mCD_STICK_AREA_CENTER;
        } else {
            calendar->stick_area = mCD_STICK_AREA_LEFT;
        }
    }

    switch (calendar->stick_area) {
        case mCD_STICK_AREA_TOP_LEFT:
        case mCD_STICK_AREA_LEFT:
        case mCD_STICK_AREA_BOTTOM_LEFT:
            submenu->overlay->calendar_ovl->_105C = mCD_STICK_AREA_LEFT;
            break;
        case mCD_STICK_AREA_TOP_RIGHT:
        case mCD_STICK_AREA_RIGHT:
        case mCD_STICK_AREA_BOTTOM_RIGHT:
            submenu->overlay->calendar_ovl->_105C = mCD_STICK_AREA_RIGHT;
            break;
        default:
            submenu->overlay->calendar_ovl->_105C = mCD_STICK_AREA_CENTER;
            break;
    }
}

static void mCD_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mCD_MVPL_select(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;

    if ((trigger & BUTTON_B) || (trigger & BUTTON_START)) {
        (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(NA_SE_17D);
    } else {
        if (calendar->_105C == mCD_STICK_AREA_LEFT) {
            if (calendar->_1056 > calendar->_1059 - 11) {
                calendar->_105A = 1;
                menu_info->position[0] = -320.0f;
                calendar->move_proc_idx = mCD_MVPL_MV1;
                calendar->_1056--;
                sAdo_SysTrgStart(NA_SE_5F);
            }
        } else if (calendar->_105C == mCD_STICK_AREA_RIGHT) {
            if (calendar->_1056 < calendar->_1059 + 11) {
                calendar->_105A = 1;
                menu_info->position[0] = 320.0f;
                calendar->move_proc_idx = mCD_MVPL_MV0;
                calendar->_1056++;
                sAdo_SysTrgStart(NA_SE_5F);
            }
        } else if ((trigger & BUTTON_CUP) && calendar->_105C == mCD_STICK_AREA_CENTER) {
            if (calendar->_1059 > calendar->_1056) {
                calendar->_105A = calendar->_1059 - calendar->_1056;
                menu_info->position[0] = 320.0f;
                calendar->move_proc_idx = mCD_MVPL_MV0;
                calendar->_1056++;
                sAdo_SysTrgStart(NA_SE_5F);
            } else if (calendar->_1059 < calendar->_1056) {
                calendar->_105A = calendar->_1056 - calendar->_1059;
                menu_info->position[0] = -320.0f;
                calendar->move_proc_idx = mCD_MVPL_MV1;
                calendar->_1056--;
                sAdo_SysTrgStart(NA_SE_5F);
            }
        } else if ((trigger & BUTTON_A)) {
            calendar->move_proc_idx = mCD_MVPL_CHG0;
            sAdo_SysTrgStart(NA_SE_5F);
            calendar->_102C = 0.0f;
            calendar->_1030 = -100.0f;
        }
    }
}

static void mCD_MVPL_mv(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    int flag;

    if (calendar->_105A == 1) {
        f32 val = mCD_add_calc_dt(&menu_info->position[0], 0.0f, 0.4f, 37.0f, 1.25f);

        if (fabsf(val) < 0.1f) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
    } else if (menu_info->position[0] > 0.0f) {
        menu_info->position[0] -= 37.0f * (f32)gamePT->graph->dt_num_60fps_frames;
        if (menu_info->position[0] <= 0.0f) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
    } else {
        menu_info->position[0] += 37.0f * (f32)gamePT->graph->dt_num_60fps_frames;
        if (menu_info->position[0] >= 0.0f) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
    }

    if (flag) {
        calendar->_105A--;
        if (calendar->_105A == 0) {
            menu_info->position[0] = 0.0f;
            calendar->move_proc_idx = mCD_MVPL_SELECT;
        } else {
            sAdo_SysTrgStart(NA_SE_5F);
            if (calendar->move_proc_idx == mCD_MVPL_MV1) {
                menu_info->position[0] -= 320.0f;
                calendar->_1056--;
            } else {
                menu_info->position[0] += 320.0f;
                calendar->_1056++;
            }
        }
    }
}

static void mCD_MVPL_chg(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    f32* target1;
    f32* target0;
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    int done1;
    int done0;
    f32 adj0;
    f32 adj1;

    if (calendar->move_proc_idx == mCD_MVPL_CHG0) {
        target0 = &calendar->_102C;
        target1 = &calendar->_1030;
    } else {
        target0 = &calendar->_1030;
        target1 = &calendar->_102C;
    }

    adj1 = fabsf(mCD_add_calc_dt(target1, 0.0f, 0.4f, 37.0f, 1.25f));
    if (adj1 < 0.1f) {
        *target1 = 0.0f;
        done1 = TRUE;
    } else {
        done1 = FALSE;
    }

    adj0 = fabsf(mCD_add_calc_dt(target0, -100.0f, 0.4f, 37.0f, 1.25f));
    if (adj0 < 0.1f) {
        *target0 = -100.0f;
        done0 = TRUE;
    } else {
        done0 = FALSE;
    }

    if (done1 && done0) {
        if (calendar->move_proc_idx == mCD_MVPL_CHG0) {
            calendar->move_proc_idx = mCD_MVPL_DAY;

            if (calendar->_1056 == calendar->_1059) {
                calendar->_1057 = mDC_get_calendar_day_position(calendar, Common_Get(time.rtc_time.day));
            } else {
                calendar->_1057 = mDC_get_calendar_day_position(calendar, 1);
            }

            mDC_set_disp_table(calendar);
        } else {
            calendar->move_proc_idx = mCD_MVPL_SELECT;
        }
    }
}

static void mCD_MVPL_day(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    u32 trigger = submenu->overlay->menu_control.trigger;
    mCD_month_entry_c* entry = &calendar->month_entries[calendar->_1056];
    int days = entry->day_data[calendar->_1057] & 0x1F;

    if ((trigger & BUTTON_B)) {
        calendar->move_proc_idx = mCD_MVPL_CHG1;
        sAdo_SysTrgStart(MONO(NA_SE_3));
        calendar->_1030 = 0.0f;
        calendar->_102C = -100.0f;
    } else if ((trigger & BUTTON_A)) {
        int arg0 = -1;

        if (menu_info->data1 == Common_Get(player_no)) {
            arg0 = 0;
            calendar->move_proc_idx = mCD_MVPL_ESCAPE;
        } else if (Save_Get(private_data[menu_info->data1]).calendar.edit) {
            mWR_SHOW_WARNING(submenu, mWR_WARNING_LOCK_DIARY);
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
        } else {
            arg0 = 1;
            calendar->move_proc_idx = mCD_MVPL_ESCAPE;
        }

        if (arg0 != -1) {
            mSM_open_submenu_new2(submenu, mSM_OVL_DIARY, arg0, menu_info->data1, NULL, calendar->_1056 % lbRTC_MONTHS_MAX);
        }
    } else if ((trigger & BUTTON_CLEFT) && days > 1) {
        calendar->_1057--;
        mDC_set_disp_table(calendar);
        sAdo_SysTrgStart(NA_SE_CURSOL);
    } else if ((trigger & BUTTON_CRIGHT)) {
        if (calendar->_1057 < 36 && (entry->day_data[calendar->_1057 + 1] & 0x1F) > 0) {
            calendar->_1057++;
            mDC_set_disp_table(calendar);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    } else if ((trigger & BUTTON_CUP)) {
        if (calendar->_1043 > 1 && calendar->_1042 != 0) {
            calendar->_1042--;
            mDC_set_string(calendar);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if (days > lbRTC_WEEK) {
            calendar->_1057 -= lbRTC_WEEK;
            mDC_set_disp_table(calendar);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    } else if ((trigger & BUTTON_CDOWN)) {
        if (calendar->_1043 > 1 && calendar->_1042 + 1 < calendar->_1043) {
            calendar->_1042++;
            mDC_set_string(calendar);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if (calendar->_1057 < 30 && (entry->day_data[calendar->_1057 + lbRTC_WEEK] & 0x1F) > 0) {
            calendar->_1057 += lbRTC_WEEK;
            mDC_set_disp_table(calendar);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    }

    calendar->_1038 += (f32)gamePT->graph->dt_num_60fps_frames;
    while (calendar->_1038 >= 60.0f) {
        calendar->_1038 -= 60.0f;
    }

    {
        f32 t0 = (calendar->_1038 - 30.0f) / 30.0f;
        f32 t1;
        f32 t2;

        if (t0 <= 0.0f) {
            t1 = 1.0f + t0;
        } else {
            t1 = 1.0f - t0;
        }

        if (t1 < 0.0f) {
            t1 = 0.0f;
        } else if (t1 > 1.0f) {
            t1 = 1.0f;
        }

        calendar->_1054 = (u8)(int)(255 * t1);
    }
}

static void mCD_MVPL_escape(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;

    if (fabsf(mCD_add_calc_dt(&menu_info->position[1], 300.0f, 0.4f, 37.0f, 1.25f)) < 0.1f) {
        menu_info->position[1] = 300.0f;
        menu_info->proc_status = mSM_OVL_PROC_OBEY;
        calendar->move_proc_idx = mCD_MVPL_DAY;
    }
}

static void mCD_MVPL_entrance(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;

    if (fabsf(mCD_add_calc_dt(&menu_info->position[1], 0.0f, 0.4f, 37.0f, 1.25f)) < 0.1f) {
        menu_info->position[1] = 0.0f;
        calendar->move_proc_idx = mCD_MVPL_DAY;
    }
}

typedef void (*mCD_MVPL_PROC)(Submenu* submenu, mSM_MenuInfo_c* menu_info);

static void mCD_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mCD_MVPL_PROC mCD_play_proc[] = {
        // clang-format off
        mCD_MVPL_select,
        mCD_MVPL_mv,
        mCD_MVPL_mv,
        mCD_MVPL_chg,
        mCD_MVPL_chg,
        mCD_MVPL_day,
        mCD_MVPL_escape,
        mCD_MVPL_entrance,
        // clang-format on
    };

    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;

    (*mCD_play_proc[calendar->move_proc_idx])(submenu, menu_info);
}

static void mCD_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    mSM_MenuInfo_c* obey_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (obey_info->proc_status == mSM_OVL_PROC_MOVE && obey_info->next_proc_status == mSM_OVL_PROC_END) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
        menu_info->position[1] = 300.0f;
        calendar->move_proc_idx = mCD_MVPL_ENTRANCE;
    }
}

static void mCD_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* obey_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (obey_info->proc_status == mSM_OVL_PROC_MOVE && obey_info->next_proc_status == mSM_OVL_PROC_END) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    }
}

static void mCD_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mCD_calendar_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mCD_move_Move,
        mCD_move_Play,
        mCD_move_Wait,
        mCD_move_Obey,
        mCD_move_End,
        // clang-format on
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CALENDAR];

    mCD_stick_area_check(submenu);
    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

#include "../src/game/m_calendar_ovl_draw.c_inc"

static void mCD_calendar_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CALENDAR];
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;

    (*menu_info->pre_draw_func)(submenu, game);

    if (menu_info->proc_status != mSM_OVL_PROC_OBEY) {
        if (calendar->move_proc_idx == mCD_MVPL_MV0) {
            mCD_set_base_dl(submenu, game, menu_info->position[0] - 320.0f, menu_info->position[1], calendar->_1056 - 1);
        }

        if (calendar->move_proc_idx == mCD_MVPL_MV1) {
            mCD_set_base_dl(submenu, game, menu_info->position[0] + 320.0f, menu_info->position[1], calendar->_1056 + 1);
        }

        mCD_set_base_dl(submenu, game, menu_info->position[0], menu_info->position[1], calendar->_1056);

        if (calendar->move_proc_idx <= mCD_MVPL_CHG1) {
            mCD_set_hyoji_dl(submenu, game, 0.0f, calendar->_102C - menu_info->position[1]);
        }

        if (calendar->move_proc_idx >= mCD_MVPL_CHG0) {
            mCD_set_hyoji2_dl(submenu, game, 0.0f, calendar->_1030 - menu_info->position[1]);
        }

        if (calendar->move_proc_idx == mCD_MVPL_DAY) {
            mCD_disp_event_dl(submenu, game);
        }
    }
}

extern void mCD_calendar_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;

    ctrl->menu_move_func = mCD_calendar_ovl_move;
    ctrl->menu_draw_func = mCD_calendar_ovl_draw;
}

static void mCD_calendar_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CALENDAR];
    mCD_Ovl_c* calendar = submenu->overlay->calendar_ovl;
    lbRTC_time_c* rtc_time;
    int player_no;

    sAdo_SysTrgStart(NA_SE_17C);
    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    menu_info->move_drt = mSM_MOVE_IN_TOP;

    player_no = submenu->param1;
    mem_clear((u8*)calendar, sizeof(mCD_Ovl_c), 0);
    rtc_time = Common_GetPointer(time.rtc_time);
    mCD_calendar_check_delete(player_no, rtc_time->year, rtc_time->month, rtc_time->day);
    mCD_calendar_wellcome_on();
    mCD_make_calendar_data(calendar, player_no);
    calendar->move_proc_idx = mCD_MVPL_SELECT;
    calendar->_102C = 0.0f;
    calendar->_1030 = -100.0f;
}

extern void mCD_calendar_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    if (ovl->calendar_ovl == NULL) {
        ovl->calendar_ovl = (mCD_Ovl_c*)zelda_malloc(sizeof(mCD_Ovl_c));
        mem_clear((u8*)ovl->calendar_ovl, sizeof(mCD_Ovl_c), 0);
    }

    mCD_calendar_ovl_init(submenu);
    mCD_calendar_ovl_set_proc(submenu);
}

extern void mCD_calendar_ovl_destruct(Submenu* submenu) {
    if (submenu->overlay->calendar_ovl != NULL) {
        zelda_free(submenu->overlay->calendar_ovl);
    }

    submenu->overlay->calendar_ovl = NULL;
}
