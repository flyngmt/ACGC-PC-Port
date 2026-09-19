#ifndef M_TIME_H
#define M_TIME_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif


/* TODO: this might have a better header to live in */
#define mTM_FIELD_RENEW_HOUR 6 /* hour which daily things 'reset' */

#define mTM_MIN_YEAR 2001
#ifdef TARGET_PC
#define mTM_MAX_YEAR (GAME_YEAR_MAX - 1)
#else
#define mTM_MAX_YEAR 2030
#endif

enum {
  mTM_SEASON_BEGIN = 0,
  mTM_SEASON_SPRING = mTM_SEASON_BEGIN,
  mTM_SEASON_SUMMER,
  mTM_SEASON_AUTUMN,
  mTM_SEASON_WINTER,
  mTM_SEASON_NUM
};

enum {
  mTM_TERM_BEGIN = 0,
  mTM_TERM_0 = mTM_TERM_BEGIN,
  mTM_TERM_1,
  mTM_TERM_2,
  mTM_TERM_3,
  mTM_TERM_4,
  mTM_TERM_5,
  mTM_TERM_6,
  mTM_TERM_7,
  mTM_TERM_8,
  mTM_TERM_9,
  mTM_TERM_10,
  mTM_TERM_11,
  mTM_TERM_12,
  mTM_TERM_13,
  mTM_TERM_14,
  mTM_TERM_15,
  mTM_TERM_16,
  mTM_TERM_17,
  mTM_TERM_NUM
};

#define mTM_RENEW_TIME_NONE 0
#define mTM_RENEW_TIME_ALL 0xFF

enum {
  mTM_RENEW_TIME_BEGIN = 0,
  mTM_RENEW_TIME_WEATHER = mTM_RENEW_TIME_BEGIN,
  mTM_RENEW_TIME_DAILY
};

#define mTM_SECONDS_IN_MINUTE 60
#define mTM_SECONDS_IN_HOUR (60*60)
#define mTM_SECONDS_IN_HALFDAY (12*60*60)
#define mTM_SECONDS_IN_DAY (24*60*60)

#define mTM_MINUTES_IN_HOUR 60

#define mTM_TIME2SEC(h, m, s) ((h) * mTM_SECONDS_IN_HOUR + (m) * mTM_SECONDS_IN_MINUTE + (s))

typedef struct time_calendar_term_s {
  lbRTC_month_t month;
  lbRTC_day_t day;
  u16 season;
  s16 bgitem_profile;
  s16 bgitem_bank;
} mTM_calendar_term_t;

extern void mTM_set_season_com(int term_idx);
extern void mTM_set_season();
extern int mTM_check_renew_time(u8 renew_flag);
extern void mTM_off_renew_time(u8 renew_flag);
extern void mTM_set_renew_is();
extern void mTM_set_renew_time(lbRTC_ymd_c* renew_time, lbRTC_time_c* time);
extern void mTM_ymd_2_time(lbRTC_time_c* time, lbRTC_ymd_c* ymd);
extern void mTM_renewal_renew_time();
extern void mTM_clear_renew_is();
extern void mTM_rtcTime_limit_check();
extern void mTM_time();
extern void mTM_time_init();

extern const lbRTC_time_c mTM_rtcTime_clear_code;
extern const lbRTC_ymd_c mTM_rtcTime_ymd_clear_code;
extern const lbRTC_time_c mTM_rtcTime_default_code;

#define mTM_IsTimeCleared(time) (lbRTC_IsEqualTime((time), &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == TRUE)
#define mTM_AreTimesEqual(t0, t1) (lbRTC_IsEqualTime(t0, t1, lbRTC_CHECK_ALL))

#define mTM_CheckCmpYMDEqual(ymd0, ymd1) ((ymd0)->year == (ymd1)->year && (ymd0)->month == (ymd1)->month && (ymd0)->day == (ymd1)->day)
#define mTM_CheckCmpYMDClear(ymd0) ((ymd0)->year == mTM_rtcTime_ymd_clear_code.year || (ymd0)->month == mTM_rtcTime_ymd_clear_code.month || (ymd0)->day == mTM_rtcTime_ymd_clear_code.day)

#ifdef __cplusplus
}
#endif

#endif
