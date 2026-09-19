#include "m_calendar.h"

#include "lb_reki.h"
#include "m_common_data.h"

static void mCD_calendar_clear_interval(mCD_player_calendar_c* calendar, int interval) {
    u8 months[lbRTC_MONTHS_MAX];
    int i;

    for (i = 0; i < lbRTC_MONTHS_MAX; i++) {
        months[i] = 0;
    }

    for (i = 0; i < interval; i++) {
        months[(calendar->month + i) % lbRTC_MONTHS_MAX] = 1;
    }

    for (i = 0; i > interval; i--) {
        months[(calendar->month + (lbRTC_MONTHS_MAX - 1) + i) % lbRTC_MONTHS_MAX] = 1;
    }

    for (i = 0; i < lbRTC_MONTHS_MAX; i++) {
        if (months[i] == 1) {
            calendar->played_days[i] = 0;
            calendar->event_days[i] = 0;
        }
    }

    if (months[lbRTC_JUNE - 1] == 1) {
        calendar->event_flags &= ~mCD_FLAG_MOTHERS_DAY; // 1
    }

    if (months[lbRTC_JULY - 1] == 1) {
        calendar->event_flags &= ~mCD_FLAG_TOWN_DAY; // 2
    }

    if (months[lbRTC_AUGUST - 1] == 1) {
        calendar->event_flags &= ~(mCD_FLAG_METEOR_SHOWER | mCD_FLAG_FOUNDERS_DAY); // 12 (4 | 8)
    }

    if (months[lbRTC_SEPTEMBER - 1] == 1) {
        calendar->event_flags &= ~mCD_FLAG_HARVEST_MOON_9; // 16
    }

    if (months[lbRTC_OCTOBER - 1] == 1) {
        calendar->event_flags &= ~mCD_FLAG_HARVEST_MOON_10; // 32
    }

    if (months[lbRTC_NOVEMBER - 1] == 1) {
        calendar->event_flags &= ~mCD_FLAG_OFFICERS_DAY; // 64
    }
}

static void mCD_calendar_clear_day(mCD_player_calendar_c* calendar, lbRTC_year_t year, lbRTC_month_t month,
                                   lbRTC_day_t day) {
    lbRTC_day_t days = lbRTC_GetDaysByMonth(year, month);
    int i;

    if (days != day) {
        u32 days_bitfield = 0;
        for (i = day; i < 31; i++) {
            days_bitfield |= (1 << i);
        }

        calendar->played_days[month - 1] &= ~days_bitfield;
        calendar->event_days[month - 1] &= ~days_bitfield;

        switch (month) {
            case lbRTC_JUNE: {
                lbRTC_weekday_t weekday = lbRTC_Week(year, month, day + 1);

                /* Calculate the current week and verify it's not the last week */
                if ((day - weekday) / lbRTC_WEEK + 1 < 3) {
                    calendar->event_flags &= ~mCD_FLAG_MOTHERS_DAY;
                }

                break;
            }

            case lbRTC_JULY: {
                if (day < Save_Get(town_day)) {
                    calendar->event_flags &= ~mCD_FLAG_TOWN_DAY;
                }

                break;
            }

            case lbRTC_AUGUST: {
                if (day < 12) {
                    calendar->event_flags &= ~mCD_FLAG_METEOR_SHOWER;
                }

                if (day < 21) {
                    calendar->event_flags &= ~mCD_FLAG_FOUNDERS_DAY;
                }

                break;
            }

            case lbRTC_SEPTEMBER: {
                lbRTC_ymd_c harvest_moon_day;

#ifdef TARGET_PC
                if (!lbRk_TryHarvestMoonDay(&harvest_moon_day, year)) {
                    break;
                }
#else
                lbRk_HarvestMoonDay(&harvest_moon_day, year);
#endif

                if (month == harvest_moon_day.month && day < harvest_moon_day.day) {
                    calendar->event_flags &= ~mCD_FLAG_HARVEST_MOON_9;
                }

                break;
            }

            case lbRTC_OCTOBER: {
                lbRTC_ymd_c harvest_moon_day;

#ifdef TARGET_PC
                if (!lbRk_TryHarvestMoonDay(&harvest_moon_day, year)) {
                    break;
                }
#else
                lbRk_HarvestMoonDay(&harvest_moon_day, year);
#endif

                if (month == harvest_moon_day.month && day < harvest_moon_day.day) {
                    calendar->event_flags &= ~mCD_FLAG_HARVEST_MOON_10;
                }

                break;
            }

            case lbRTC_NOVEMBER: {
                if (day < 11) {
                    calendar->event_flags &= ~mCD_FLAG_OFFICERS_DAY;
                }

                break;
            }
        }
    }
}

static int mCD_GetIntervalMonths(lbRTC_year_t y0, lbRTC_month_t m0, lbRTC_year_t y1, lbRTC_month_t m1) {
    return (m1 - m0) + (y1 - y0) * lbRTC_MONTHS_MAX;
}

extern void mCD_calendar_clear(int player_no) {
    Private_c* priv = Save_Get(private_data);

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (player_no != mPr_FOREIGNER) {
        mem_clear((u8*)&priv[player_no].calendar, sizeof(mCD_player_calendar_c), 0);
    }
}

static int mCD_calendar_check_harvest_moon_viewing(mCD_player_calendar_c* calendar, lbRTC_month_t month) {
    int res = FALSE;

    switch (month) {
        case lbRTC_SEPTEMBER: {
            if ((calendar->event_flags & mCD_FLAG_HARVEST_MOON_9) != 0) {
                res = TRUE;
            }

            break;
        }

        case lbRTC_OCTOBER: {
            if ((calendar->event_flags & mCD_FLAG_HARVEST_MOON_10) != 0) {
                res = TRUE;
            }

            break;
        }
    }

    return res;
}

extern void mCD_calendar_check_delete(int player_no, lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day) {
    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (player_no != mPr_FOREIGNER) {
        mCD_player_calendar_c* calendar = &Save_Get(private_data[player_no]).calendar;

        if (calendar->year == 0) {
            mCD_calendar_clear(-1);
        } else {
            int interval = mCD_GetIntervalMonths(calendar->year, calendar->month, year, month);

            if (interval >= lbRTC_MONTHS_MAX || interval <= -lbRTC_MONTHS_MAX) {
                mCD_calendar_clear(-1); // clear entire calendar since interval is >= 1 year
            } else {
                if (interval != 0) {
                    mCD_calendar_clear_interval(calendar, interval); // clear only interval months
                }

                mCD_calendar_clear_day(calendar, year, month, day); // clear days
            }
        }
    }
}

extern void mCD_calendar_wellcome_on() {
    mCD_player_calendar_c* calendar = &Common_Get(now_private)->calendar;

    if (Common_Get(player_no) != mPr_FOREIGNER) {
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        mCD_calendar_check_delete(-1, rtc_time->year, rtc_time->month, rtc_time->day);
        calendar->played_days[rtc_time->month - 1] |= (1 << (rtc_time->day - 1));
        calendar->year = rtc_time->year;
        calendar->month = rtc_time->month;
    }
}

extern void mCD_calendar_event_on(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, u8 event) {
    if (Common_Get(player_no) != mPr_FOREIGNER) {
        mCD_player_calendar_c* calendar;

        mCD_calendar_check_delete(-1, year, month, day);
        calendar = &Save_Get(private_data[Common_Get(player_no)]).calendar;

        switch (event) {
            case 11: {
                calendar->event_flags |= mCD_FLAG_MOTHERS_DAY;

                break;
            }

            case 4: {
                calendar->event_flags |= mCD_FLAG_TOWN_DAY;

                break;
            }

            case 16: {
                calendar->event_flags |= mCD_FLAG_METEOR_SHOWER;

                break;
            }

            case 1: {
                calendar->event_flags |= mCD_FLAG_FOUNDERS_DAY;

                break;
            }

            case 17: {
                switch (month) {
                    case lbRTC_SEPTEMBER: {
                        calendar->event_flags |= mCD_FLAG_HARVEST_MOON_9;

                        break;
                    }

                    case lbRTC_OCTOBER: {
                        calendar->event_flags |= mCD_FLAG_HARVEST_MOON_10;

                        break;
                    }
                }

                break;
            }

            case 19: {
                calendar->event_flags |= mCD_FLAG_OFFICERS_DAY;

                break;
            }

            case 255: {
                break;
            }

            default: {
                calendar->event_days[month - 1] |= (1 << (day - 1));

                break;
            }
        }
    }
}

extern int mCD_calendar_event_check(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, int player_no, u8 event) {
    int res = FALSE;

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (player_no != mPr_FOREIGNER) {
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        int interval = (rtc_time->month - month) + (rtc_time->year - year) * lbRTC_MONTHS_MAX;

        if (interval >= 0 && interval < lbRTC_MONTHS_MAX) {
            mCD_player_calendar_c* calendar = &Save_Get(private_data[player_no]).calendar;

            switch (event) {
                case 11: {
                    if (calendar->event_flags & mCD_FLAG_MOTHERS_DAY) {
                        res = TRUE;
                    }

                    break;
                }

                case 4: {
                    if (calendar->event_flags & mCD_FLAG_TOWN_DAY) {
                        res = TRUE;
                    }

                    break;
                }

                case 16: {
                    if (calendar->event_flags & mCD_FLAG_METEOR_SHOWER) {
                        res = TRUE;
                    }

                    break;
                }

                case 1: {
                    if (calendar->event_flags & mCD_FLAG_FOUNDERS_DAY) {
                        res = TRUE;
                    }

                    break;
                }

                case 17: {
                    if (mCD_calendar_check_harvest_moon_viewing(calendar, month) == TRUE) {
                        res = TRUE;
                    }

                    break;
                }

                case 19: {
                    if (calendar->event_flags & mCD_FLAG_OFFICERS_DAY) {
                        res = TRUE;
                    }

                    break;
                }

                case 255: {
                    break;
                }

                default: {
                    if (calendar->event_days[month - 1] & (1 << (day - 1))) {
                        res = TRUE;
                    }

                    break;
                }
            }
        }
    }

    return res;
}
