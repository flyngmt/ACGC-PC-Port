#ifndef LB_RTC_H
#define LB_RTC_H

#include "types.h"
#include "dolphin/os/OSTime.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: do these have a better header? */
#define GAME_YEAR_MIN 2000 /* Minimum year supported by the game */
#ifdef TARGET_PC
#define GAME_YEAR_MAX 3000 /* Calendar padding year; playable through 2999. */
#else
#define GAME_YEAR_MAX 2032 /* Maximum year supported by the game */
#endif

#define lbRTC_YEAR_MIN 1901
#ifdef TARGET_PC
#define lbRTC_YEAR_MAX (GAME_YEAR_MAX - 1)
#else
#define lbRTC_YEAR_MAX 2099
#endif

typedef struct OSRTCTime { // from lbrtc library in N64
  u8 sec;
  u8 min;
  u8 hour;
  u8 day;
  u8 weekday;
  u8 month;
  u16 year;
} OSRTCTime; 

typedef u8 lbRTC_sec_t;
typedef u8 lbRTC_min_t;
typedef u8 lbRTC_hour_t;
typedef u8 lbRTC_day_t;
typedef u8 lbRTC_weekday_t;
typedef u8 lbRTC_month_t;
typedef u16 lbRTC_year_t;

typedef OSRTCTime lbRTC_time_c; /* Name leaked in lbRTC_time_c_save_data_check */

typedef struct lbRTC_ymd_s {
  lbRTC_year_t year;
  lbRTC_month_t month;
  lbRTC_day_t day;
} lbRTC_ymd_c; /* Name leaked in mTM_ymd_2_time */

enum WEEKDAYS {
  lbRTC_WEEKDAYS_BEGIN = 0,
  lbRTC_SUNDAY = lbRTC_WEEKDAYS_BEGIN,
  lbRTC_MONDAY,
  lbRTC_TUESDAY,
  lbRTC_WEDNESDAY,
  lbRTC_THURSDAY,
  lbRTC_FRIDAY,
  lbRTC_SATURDAY,
  lbRTC_WEEK,
  lbRTC_WEEKDAYS_MAX = lbRTC_WEEK
};

enum MONTHS {
  lbRTC_MONTHS_BEGIN = 0,
  lbRTC_JANUARY = 1,
  lbRTC_FEBRUARY,
  lbRTC_MARCH,
  lbRTC_APRIL,
  lbRTC_MAY,
  lbRTC_JUNE,
  lbRTC_JULY,
  lbRTC_AUGUST,
  lbRTC_SEPTEMBER,
  lbRTC_OCTOBER,
  lbRTC_NOVEMBER,
  lbRTC_DECEMBER,
  lbRTC_MONTHS_MAX = lbRTC_DECEMBER
};

enum RTC_EQUALITY {
  lbRTC_LESS = -1,
  lbRTC_EQUAL = 0,
  lbRTC_OVER = 1
};

enum RTC_EQUALITY_FLAGS {
  lbRTC_CHECK_NONE = 0,           /* 0x00 */

  lbRTC_CHECK_SECONDS = 1 << 0,   /* 0x01 */
  lbRTC_CHECK_MINUTES = 1 << 1,   /* 0x02 */
  lbRTC_CHECK_HOURS = 1 << 2,     /* 0x04 */
  lbRTC_CHECK_WEEKDAYS = 1 << 3,  /* 0x08 */
  lbRTC_CHECK_DAYS = 1 << 4,      /* 0x10 */
  lbRTC_CHECK_MONTHS = 1 << 5,    /* 0x20 */
  lbRTC_CHECK_YEARS = 1 << 6,     /* 0x40 */

  /* 0x7F */
  lbRTC_CHECK_ALL = lbRTC_CHECK_SECONDS |
                    lbRTC_CHECK_MINUTES |
                    lbRTC_CHECK_HOURS |
                    lbRTC_CHECK_WEEKDAYS |
                    lbRTC_CHECK_DAYS |
                    lbRTC_CHECK_MONTHS |
                    lbRTC_CHECK_YEARS
};

extern OSTime lbRTC_HardTime();
extern int lbRTC_IsAbnormal();
extern void lbRTC_Sampling();
extern void lbRTC_SetTime(lbRTC_time_c* time);
extern void lbRTC_GetTime(lbRTC_time_c* time);
extern lbRTC_day_t lbRTC_GetDaysByMonth(lbRTC_year_t year, lbRTC_month_t month);
extern int lbRTC_IsEqualDate(
  lbRTC_year_t y0, lbRTC_month_t m0, lbRTC_day_t d0,
  lbRTC_year_t y1, lbRTC_month_t m1, lbRTC_day_t d1
);
extern int lbRTC_IsEqualTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1, int flags);
extern int lbRTC_IsOverTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1);
// extern int lbRTC_IsJustAtRTC(const lbRTC_time_c* time, int check_flags);
extern int lbRTC_IsOverRTC(const lbRTC_time_c* time);
extern int lbRTC_IntervalTime(const lbRTC_time_c* time0, const lbRTC_time_c* time1);
extern int lbRTC_GetIntervalDays(const lbRTC_time_c* t0, const lbRTC_time_c* t1);
extern int lbRTC_GetIntervalDays2(lbRTC_ymd_c* ymd0, lbRTC_ymd_c* ymd1);
extern void lbRTC_Add_YY(lbRTC_time_c* time, int year);
extern void lbRTC_Add_MM(lbRTC_time_c* time, int month);
extern void lbRTC_Add_DD(lbRTC_time_c* time, int day);
extern void lbRTC_Add_hh(lbRTC_time_c* time, int hour);
extern void lbRTC_Add_mm(lbRTC_time_c* time, int min);
extern void lbRTC_Add_ss(lbRTC_time_c* time, int sec);
extern void lbRTC_Add_Date(lbRTC_time_c* time, const lbRTC_time_c* add_time);
extern void lbRTC_Sub_YY(lbRTC_time_c* time, int year);
extern void lbRTC_Sub_MM(lbRTC_time_c* time, int month);
extern void lbRTC_Sub_DD(lbRTC_time_c* time, int days);
extern void lbRTC_Sub_hh(lbRTC_time_c* time, int hour);
extern void lbRTC_Sub_mm(lbRTC_time_c* time, int min);
extern void lbRTC_Sub_ss(lbRTC_time_c* time, int sec);
// extern void lbRTC_Sub_Date(lbRTC_time_c* time, const lbRTC_time_c* sub_time)
extern lbRTC_weekday_t lbRTC_Week(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day);
extern void lbRTC_TimeCopy(lbRTC_time_c* dst, const lbRTC_time_c* src);
extern int lbRTC_IsValidTime(const lbRTC_time_c* time);
extern int lbRTC_time_c_save_data_check(const lbRTC_time_c* time);
extern int lbRTC_Weekly_day(lbRTC_year_t year, lbRTC_month_t month, int weeks, int weekday);

#define lbRTC_HOURS_PER_DAY 24
#define lbRTC_MINUTES_PER_HOUR 60
#define lbRTC_SECONDS_PER_MINUTE 60

#define lbRTC_IS_LEAPYEAR(year) \
  (((year % 4) == 0 && ((year % 100) != 0)) || ((year % 400) == 0))

#ifdef __cplusplus
}
#endif

#endif
