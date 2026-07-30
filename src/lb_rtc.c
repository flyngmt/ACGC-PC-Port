/*
 * lb_rtc.c
 *
 * This source file contains a set of functions for handling
 * date and time calculations and conversions in the context of the lbRTC system.
 * The lbRTC system is designed to manage timekeeping and manipulation of date-times.
 *
 * Functions in this file include (but are not limited to):
 *
 * - lbRTC_HardTime: Retrieve the hardware time.
 * - lbRTC_IsAbnormal: Check if the lbRTC system is in an abnormal state.
 * - lbRTC_Sampling: Perform a sampling operation on the lbRTC system.
 * - lbRTC_SetTime: Set the current time in the lbRTC system.
 * - lbRTC_GetTime: Get the current time from the lbRTC system.
 * - lbRTC_GetDaysByMonth: Get the number of days in a given month and year.
 * - lbRTC_IsEqualDate: Check if two dates are equal.
 * - lbRTC_IsEqualTime: Check if two times are equal.
 * - lbRTC_IsOverTime: Check if one time is greater than another time.
 * - lbRTC_IsOverRTC: Check if the given time is greater than the current time.
 * - lbRTC_IntervalTime: Calculate the interval between two times.
 * - lbRTC_GetIntervalDays: Calculate the interval between two times in days.
 * - lbRTC_GetIntervalDays2: Calculate the interval between two times (date only) in days.
 * - lbRTC_Add_YY: Add years to a time.
 * - lbRTC_Add_MM: Add months to a time.
 * - lbRTC_Add_DD: Add days to a time.
 * - lbRTC_Add_hh: Add hours to a time.
 * - lbRTC_Add_mm: Add minutes to a time.
 * - lbRTC_Add_ss: Add seconds to a time.
 * - lbRTC_Add_Date: Add a time duration to a time.
 * - lbRTC_Sub_YY: Subtract years from a time.
 * - lbRTC_Sub_MM: Subtract months from a time.
 * - lbRTC_Sub_DD: Subtract days from a time.
 * - lbRTC_Sub_hh: Subtract hours from a time.
 * - lbRTC_Sub_mm: Subtract minutes from a time.
 * - lbRTC_Sub_ss: Subtract seconds from a time.
 * - lbRTC_Week: Calculate the day of the week for a given date.
 * - lbRTC_TimeCopy: Copy one time structure to another.
 * - lbRTC_IsValidTime: Check if the given time is valid.
 * - lbRTC_time_c_save_data_check: Check if the given time from save data is valid.
 * - lbRTC_Weekly_day: Calculate the day of the week for a given date, considering weeks and the desired day of the week.
 */

#include "lb_rtc.h"

#include "m_common_data.h"
#include "m_lib.h"
#include "types.h"
#include "dolphin/os.h"

#ifdef TARGET_PC
extern int g_pc_time_override;
extern int g_pc_min_override;
extern int g_pc_sec_override;
extern int g_pc_date_month;
extern int g_pc_date_day;
extern int g_pc_date_year;
#endif

static BOOL l_lbRTC_isInitial = TRUE;
static lbRTC_time_c l_lbRTC_Time;
static BOOL l_lbRTC_IsSampled;

/**
 * @brief Get the current hardware time in ticks.
 *
 * This function retrieves the current hardware time using the OSGetTime()
 * function and returns it as OSTime.
 *
 * @return OSTime representing the current hardware time in ticks.
 */
static OSTime lbRTC_GetHardTime() {
  return OSGetTime();
}

/**
 * @brief Wrapper function for lbRTC_GetHardTime().
 *
 * This function is an external wrapper for the lbRTC_GetHardTime() function.
 * It retrieves the current hardware time and returns it as OSTime.
 *
 * @return OSTime representing the current hardware time in ticks.
 */
extern OSTime lbRTC_HardTime() {
  return lbRTC_GetHardTime();
}

/**
 * @brief Convert OSCalendarTime to lbRTC_time_c structure.
 *
 * This function converts the given OSCalendarTime structure into
 * an lbRTC_time_c structure by copying the relevant fields.
 *
 * @param calendar_time Pointer to the source OSCalendarTime structure.
 * @param datetime Pointer to the destination lbRTC_time_c structure.
 */
static void lbRTC_CalenderTimeToRTCTime(const OSCalendarTime* calendar_time, lbRTC_time_c* datetime) {
  datetime->sec = calendar_time->sec;
  datetime->min = calendar_time->min;
  datetime->hour = calendar_time->hour;
  datetime->day = calendar_time->mday;
  datetime->weekday = calendar_time->wday;
  datetime->month = calendar_time->mon + 1;
  datetime->year = calendar_time->year;
}

/* @unused ? OSTime lbRTC_NowHardRtcTime() */

/* @unused ? OSTime lbRTC_SavedHardRtcTime() */

/**
 * @brief Convert lbRTC_time_c to ticks.
 *
 * This function converts the given lbRTC_time_c structure to ticks (OSTime)
 * using OSCalendarTimeToTicks() function.
 *
 * @param time Pointer to the lbRTC_time_c structure to be converted.
 * @return OSTime representing the given lbRTC_time_c in ticks.
 */
static OSTime lbRTC_RTCTimeToTicks(const lbRTC_time_c* time)  {
  OSCalendarTime ctime;
  int i;
  int month = time->month;

  // Copy the lbRTC_time_c structure fields to OSCalendarTime fields
  ctime.sec = time->sec;
  ctime.min = time->min;
  ctime.hour = time->hour;
  ctime.mday = time->day;
  ctime.mon = month - 1;
  ctime.year = time->year;
  ctime.wday = month;
  ctime.yday = 0;
        
  // Get calendar year-day to start of current month
  for (i = 1; i < month; i++) {
    ctime.yday += lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)i);
  }

  ctime.yday += time->day;
  ctime.yday -= 1;
  ctime.msec = 0;
  ctime.usec = 0;

  // Convert the OSCalendarTime structure to ticks and return it
  return OSCalendarTimeToTicks(&ctime);
}

/**
 * @brief Get the current game time as an lbRTC_time_c structure.
 *
 * This function calculates the current game time by getting the hardware time,
 * adding the saved time delta, converting the result to an OSCalendarTime
 * structure, and finally converting it to an lbRTC_time_c structure.
 *
 * @param time Pointer to the lbRTC_time_c structure that will hold the game time.
 */
static void lbRTC_GetGameTime(lbRTC_time_c* time) {
  OSCalendarTime ctime;
  OSTime t = lbRTC_GetHardTime();
  t += Save_Get(time_delta);

  OSTicksToCalendarTime(t, &ctime);
#ifdef TARGET_PC
  /* The retired PC OS shim applied these command-line overrides while
   * constructing its synthetic hardware clock. Aurora owns OSGetTime, so
   * apply them at the game's RTC boundary and normalize weekday/year-day via
   * the SDK calendar conversion. */
  if (g_pc_date_month > 0) {
    ctime.mon = g_pc_date_month - 1;
    ctime.mday = g_pc_date_day;
    if (g_pc_date_year > 0) {
      ctime.year = g_pc_date_year;
    }
  }
  if (g_pc_time_override >= 0) ctime.hour = g_pc_time_override;
  if (g_pc_min_override >= 0) ctime.min = g_pc_min_override;
  if (g_pc_sec_override >= 0) ctime.sec = g_pc_sec_override;
  if (g_pc_date_month > 0 || g_pc_time_override >= 0) {
    OSTicksToCalendarTime(OSCalendarTimeToTicks(&ctime), &ctime);
  }
#endif
  lbRTC_CalenderTimeToRTCTime(&ctime, time);
}

/* @unused ? void lbRTC_GetSaveExpectGameTime(lbRTC_time_c* time) */

/**
 * @brief Initialize lbRTC module.
 *
 * This function initializes the lbRTC module by setting l_lbRTC_isInitial
 * to FALSE if it is TRUE.
 *
 * @return 0 after initialization.
 */
static int lbRTC_Initial() {
  if (l_lbRTC_isInitial == TRUE) {
    l_lbRTC_isInitial = FALSE;
  }

  return 0;
}

/**
 * @brief Check if the lbRTC module is initialized and get the game time.
 *
 * This function initializes the lbRTC module if it is not already
 * initialized, sets l_lbRTC_isInitial to TRUE, and gets the current game
 * time using lbRTC_GetGameTime().
 *
 * @param time Pointer to an lbRTC_time_c structure that will hold the game time.
 * @return 0 after checking and getting the game time.
 */
static int lbRTC_IsOki(lbRTC_time_c* time) {
  lbRTC_Initial();
  l_lbRTC_isInitial = TRUE;
  lbRTC_GetGameTime(time);
  return 0;
}

/**
 * @brief Check if the lbRTC module is in an abnormal state.
 *
 * This function checks if the lbRTC module is in an abnormal state by
 * comparing the current game time with the previously sampled game time.
 * It is assumed that a lot of debug code is missing in this function.
 *
 * @return 0 if the lbRTC module is in a normal state, non-zero otherwise.
 */
extern int lbRTC_IsAbnormal() {
  /* Lots of debug code missing here */
  lbRTC_time_c time;

  int res = lbRTC_IsOki(&time);
  if (res == 0 && l_lbRTC_IsSampled == TRUE) {
    if (time.sec + time.min * lbRTC_SECONDS_PER_MINUTE !=
        l_lbRTC_Time.sec + l_lbRTC_Time.min * lbRTC_SECONDS_PER_MINUTE) {
      return res;
    }
  }

  return res;
}

/**
 * @brief Sample the game time using lbRTC_IsOki().
 *
 * This function samples the game time by checking if the lbRTC module
 * is in a normal state using lbRTC_IsOki() and sets l_lbRTC_IsSampled to
 * TRUE if it is not already TRUE.
 */
extern void lbRTC_Sampling() {
  lbRTC_time_c time;

  if (lbRTC_IsOki(&time) == 0 && l_lbRTC_IsSampled == FALSE) {
    l_lbRTC_Time.sec = time.sec;
    l_lbRTC_Time.min = time.min;
    /* Likely debug here */
    l_lbRTC_IsSampled = TRUE;
  }
}

/**
 * @brief Set the game time.
 *
 * This function sets the game time based on the given lbRTC_time_c structure.
 * If the RTC feature is enabled and not crashed, it updates the time delta.
 * Otherwise, it copies the given time to the appropriate rtc_time location.
 *
 * @param time Pointer to the lbRTC_time_c structure containing the time to be set.
 */
extern void lbRTC_SetTime(lbRTC_time_c* time) {
  if (Common_Get(time.rtc_enabled) == TRUE && !Common_Get(time.rtc_crashed)) {
    Save_Set(time_delta, lbRTC_RTCTimeToTicks(time) - lbRTC_GetHardTime());
  }
  else {
    lbRTC_TimeCopy(Common_GetPointer(time.rtc_time), time);
  }
}

/**
 * @brief Get the game time.
 *
 * This function gets the game time and stores it in the provided lbRTC_time_c
 * structure. If the RTC feature is enabled and not crashed, it retrieves the
 * game time using lbRTC_GetGameTime(). Otherwise, it copies the rtc_time
 * to the provided structure.
 *
 * @param time Pointer to the lbRTC_time_c structure that will hold the game time.
 */
extern void lbRTC_GetTime(lbRTC_time_c* time) {
  if (Common_Get(time.rtc_enabled) == TRUE && !Common_Get(time.rtc_crashed)) {
    lbRTC_GetGameTime(time);
  }
  else {
    lbRTC_TimeCopy(time, Common_GetPointer(time.rtc_time));
  }
}

/**
 * @brief Get the number of days in a given month for a specific year.
 *
 * This function returns the number of days in a given month for a specific
 * year, taking into account leap years.
 *
 * @param year The year in which the month occurs.
 * @param month The month for which the number of days is requested.
 * @return lbRTC_day_t representing the number of days in the given month.
 */
extern lbRTC_day_t lbRTC_GetDaysByMonth(lbRTC_year_t year, lbRTC_month_t month) {
  static const lbRTC_day_t days_month[2][lbRTC_MONTHS_MAX + 1] = {
    // Regular year
    {
      0,
      31, 28, 31, 30, 31, 30,
      31, 31, 30, 31, 30, 31
    },

    // Leap year
    {
      0,
      31, 29, 31, 30, 31, 30,
      31, 31, 30, 31, 30, 31
    }
  };

  int year_type = lbRTC_IS_LEAPYEAR(year) == TRUE ? 1 : 0;
  return days_month[year_type][month];
}

typedef union {
  int raw;
  lbRTC_ymd_c ymd;
} ymd_u;

/**
 * @brief Compare two dates to determine if they are equal, lesser, or greater.
 *
 * This function compares two given dates (year, month, day) and returns the
 * result as an RTC_EQUALITY enumeration value (lbRTC_EQUAL, lbRTC_LESS,
 * or lbRTC_OVER).
 *
 * @param y0 Year of the first date.
 * @param m0 Month of the first date.
 * @param d0 Day of the first date.
 * @param y1 Year of the second date.
 * @param m1 Month of the second date.
 * @param d1 Day of the second date.
 * @return RTC_EQUALITY value representing the comparison result.
 */
extern int lbRTC_IsEqualDate(
  lbRTC_year_t y0, lbRTC_month_t m0, lbRTC_day_t d0,
  lbRTC_year_t y1, lbRTC_month_t m1, lbRTC_day_t d1
) {
  ymd_u ymd0, ymd1;
  int res;

  ymd0.ymd.year = y0;
  ymd0.ymd.month = m0;
  ymd0.ymd.day = d0;
    
  ymd1.ymd.year = y1;
  ymd1.ymd.month = m1;
  ymd1.ymd.day = d1;

  res = ymd0.raw - ymd1.raw;
  if (res == 0) {
    return lbRTC_EQUAL;
  }

  if (res < 0) {
    return lbRTC_LESS;
  }
  return lbRTC_OVER;
}

/**
 * @brief Check if two lbRTC_time_c structures are equal based on specified flags.
 *
 * This function checks if two lbRTC_time_c structures are equal by comparing
 * their time components according to the specified flags (seconds, minutes, hours,
 * weekdays, days, months, years).
 *
 * @param t0 Pointer to the first lbRTC_time_c structure.
 * @param t1 Pointer to the second lbRTC_time_c structure.
 * @param flags Bitmask of lbRTC_check_t flags specifying which components to compare.
 * @return TRUE if all specified components are equal, FALSE otherwise.
 */
extern int lbRTC_IsEqualTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1, int flags) {
  int equal = 0;

  if (flags & lbRTC_CHECK_SECONDS) {
    if (t0->sec == t1->sec)  {
      equal |= lbRTC_CHECK_SECONDS;
    }
  }

  if (flags & lbRTC_CHECK_MINUTES) {
    if (t0->min == t1->min) {
      equal |= lbRTC_CHECK_MINUTES;
    }
  }

  if (flags & lbRTC_CHECK_HOURS) {
    if (t0->hour == t1->hour) {
      equal |= lbRTC_CHECK_HOURS;
    }
  }

  if (flags & lbRTC_CHECK_WEEKDAYS) {
    if (t0->weekday == t1->weekday) {
      equal |= lbRTC_CHECK_WEEKDAYS;
    }
  }

  if (flags & lbRTC_CHECK_DAYS) {
    if (t0->day == t1->day) {
      equal |= lbRTC_CHECK_DAYS;
    }
  }

  if (flags & lbRTC_CHECK_MONTHS) {
    if (t0->month == t1->month) {
      equal |= lbRTC_CHECK_MONTHS;
    }
  }

  if (flags & lbRTC_CHECK_YEARS) {
    if (t0->year == t1->year) {
      equal |= lbRTC_CHECK_YEARS;
    }
  }

  return (equal & flags) == flags;
}

/**
 * @brief Determine if a given time is greater (over) another time.
 *
 * This function compares two lbRTC_time_c structures to determine if the first
 * time (t0) is greater (over) the second time (t1). Returns lbRTC_LESS if the first
 * time is lesser than or equal to the second time, and lbRTC_OVER if the first time
 * is greater than the second time.
 *
 * @param t0 Pointer to the first lbRTC_time_c structure.
 * @param t1 Pointer to the second lbRTC_time_c structure.
 * @return lbRTC_LESS if t0 is lesser than or equal to t1, lbRTC_OVER if t0 is greater than t1.
 */
extern int lbRTC_IsOverTime(const lbRTC_time_c* t0, const lbRTC_time_c* t1) {
  if (t1->year < t0->year) {
    return lbRTC_LESS;
  }

  if (t1->year == t0->year) {
    if (t1->month >= t0->month) {
      if (t1->month == t0->month) {
        if (t1->day >= t0->day) {
          if (t1->day == t0->day) {
            if (t1->hour >= t0->hour) {
              if (t1->hour == t0->hour) {
                if (t1->min >= t0->min) {
                  if (t1->min == t0->min) {
                    if (t1->sec < t0->sec) {
                      return lbRTC_LESS;
                    }
                  }
                } else {
                  return lbRTC_LESS;
                }
              }
            } else {
              return lbRTC_LESS;
            }
          }
        } else {
          return lbRTC_LESS;
        }
      }
    } else {
      return lbRTC_LESS;
    }
  }

  return lbRTC_OVER;
}

/**
 * @fabricated
 * 
 * @brief Check if the current RTC time is equal to the given time based on specified flags.
 *
 * This function compares the current RTC time with the given time and returns TRUE
 * if the specified components are equal, based on the check_flags provided.
 *
 * @param time Pointer to the lbRTC_time_c structure representing the time to compare.
 * @param check_flags Bitmask of lbRTC_check_t flags specifying which components to compare.
 * @return TRUE if all specified components are equal, FALSE otherwise.
 */
/*
extern int lbRTC_IsJustAtRTC(const lbRTC_time_c* time, int check_flags) {
  lbRTC_time_c rtc_time;
  
  lbRTC_GetTime(&rtc_time);
  return lbRTC_IsEqualTime(time, &rtc_time, check_flags);
}
*/

/**
 * @brief Check if the given time is greater (over) the current RTC time.
 *
 * This function compares the given time with the current RTC time and returns
 * TRUE if the given time is greater (over) the current RTC time, and FALSE otherwise.
 *
 * @param time Pointer to the lbRTC_time_c structure representing the time to compare.
 * @return TRUE if the given time is greater than the current RTC time, FALSE otherwise.
 */
extern int lbRTC_IsOverRTC(const lbRTC_time_c* time) {
  lbRTC_time_c rtc_time;
  
  lbRTC_GetTime(&rtc_time);
  return lbRTC_IsOverTime(time, &rtc_time) == lbRTC_OVER;
}

/* @unused extern int lbRTC_IsOverWeekRTC(lbRTC_time_c* time) */

/**
 * @brief Calculate the interval of time between two given lbRTC_time_c structures in minutes.
 *
 * This function calculates the interval of time between two given lbRTC_time_c
 * structures. It returns the interval in minutes as an integer. If time0 is earlier than
 * time1, the interval will be negative.
 *
 * @note This function is intended to be used internally by lbRTC_IntervalTime().
 *
 * @param time0 Pointer to the first lbRTC_time_c structure.
 * @param time1 Pointer to the second lbRTC_time_c structure.
 * @return Number of minutes between the two given times, negative if time0 is earlier than time1.
 */
static int lbRTC_IntervalTime_sub(const lbRTC_time_c* time0, const lbRTC_time_c* time1) {
  OSTime osTime1 = lbRTC_RTCTimeToTicks(time1);
  OSTime osTime0 = lbRTC_RTCTimeToTicks(time0);
  
  return OSTicksToSeconds(osTime0 - osTime1) / lbRTC_SECONDS_PER_MINUTE;
}

/**
 * @brief Calculate the interval of time between two given lbRTC_time_c structures in minutes.
 *
 * This function calculates the interval of time between two given lbRTC_time_c
 * structures. It returns the interval in minutes as an integer. If time0 is earlier than
 * time1, the interval will be negative.
 *
 * @param time0 Pointer to the first lbRTC_time_c structure.
 * @param time1 Pointer to the second lbRTC_time_c structure.
 * @return Number of minutes between the two given times, negative if time0 is earlier than time1.
 */
extern int lbRTC_IntervalTime(const lbRTC_time_c* time0, const lbRTC_time_c* time1) {
  return lbRTC_IntervalTime_sub(time0, time1);
}

/**
 * @brief Calculate the number of days between two dates.
 *
 * This function calculates the number of days between two given lbRTC_time_c
 * structures. It returns the interval in days as an integer.
 *
 * @param t0 Pointer to the lbRTC_time_c structure representing the first date.
 * @param t1 Pointer to the lbRTC_time_c structure representing the second date.
 * @return Number of days between the two given dates.
 */
extern int lbRTC_GetIntervalDays(const lbRTC_time_c* t0, const lbRTC_time_c* t1) {
  static const int total_days[2][lbRTC_MONTHS_MAX + 1] = {
    // Standard year
    {
      0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
    },
    // Leap year (flawed leap year calculation)
    {
      0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366
    }
  };

  int year_leap_period = (t1->year - t0->year) / 4; /* Total 'leap years' (missing extra not divisible by 100, except when divisible by 400 rule) */
  int extra_years = (t1->year - t0->year) % 4; /* Non-leap year remainder */
  int less_leap = (t0->year % 4) == 0; /* Is the lesser year a leap year? */
  int over_leap = (t1->year % 4) == 0; /* Is the greater year a leap year? */
  int leap_add = ((4 - (t0->year % 4)) % 4) < extra_years; /* Add leap day when leap day occurs during 'extra years' */

  int days;

  if (t0->year > t1->year) {
    return 0;
  }
  else {
    if (t0->year == t1->year) {
      if (t0->month > t1->month) {
        return 0;
      }
      else {
        if (t0->month == t1->month) {
          if (t0->day > t1->day) {
            return 0;
          }
          else {
            if (t0->day == t1->day) {
              if (t0->hour > t1->hour) {
                return 0;
              }
              else {
                if (t0->hour == t1->hour) {
                  if (t0->min > t1->min) {
                    return 0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  /***
   * Every four years (incorrect) has 365 * 3 + 366 * 1 days (1461).
   * The remaining years will be 365 * years, plus 1 if leap year occurs in range.
   ***/
  days = year_leap_period * 1461 + extra_years * 365 + leap_add;

  /* Add up through t1 day */
  days += t1->day - 1;
  days += total_days[over_leap][t1->month - 1];

  /* Remove through t0 day */
  days -= t0->day - 1;
  days -= total_days[less_leap][t0->month - 1];

  return days;
}

/**
 * @brief Calculate the number of days between two dates using lbRTC_ymd_c structures.
 *
 * This function calculates the number of days between two given lbRTC_ymd_c
 * structures. It returns the interval in days as an integer. If ymd0 is greater than
 * ymd1, the interval will be negative.
 *
 * @param ymd0 Pointer to the first lbRTC_ymd_c structure.
 * @param ymd1 Pointer to the second lbRTC_ymd_c structure.
 * @return Number of days between the two given dates, negative if ymd0 is greater than ymd1.
 */
extern int lbRTC_GetIntervalDays2(lbRTC_ymd_c* ymd0, lbRTC_ymd_c* ymd1) {
  lbRTC_time_c t0, t1;
  int equality;

  mTM_ymd_2_time(&t0, ymd0);
  mTM_ymd_2_time(&t1, ymd1);

  equality = lbRTC_IsEqualDate(t0.year, t0.month, t0.day, t1.year, t1.month, t1.day);
  if (equality > lbRTC_EQUAL) {
    return lbRTC_GetIntervalDays(&t1, &t0) * -1;
  }
  if (equality < lbRTC_EQUAL) {
    return lbRTC_GetIntervalDays(&t0, &t1);
  }

  return 0;
}

/**
 * @brief Add a specified number of years to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param year Integer value representing the number of years to add.
 */
extern void lbRTC_Add_YY(lbRTC_time_c* time, int year) {
  time->year += (lbRTC_year_t)year;
}

/**
 * @brief Add a specified number of months to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param month Integer value representing the number of months to add.
 */
extern void lbRTC_Add_MM(lbRTC_time_c* time, int month) {
  int current_mo = time->month;
  current_mo += month;
  if (current_mo > lbRTC_DECEMBER) {
    lbRTC_Add_YY(time, current_mo / lbRTC_MONTHS_MAX);
    current_mo %= lbRTC_MONTHS_MAX;
  }

  time->month = (lbRTC_month_t)current_mo;
}

/**
 * @brief Add a specified number of days to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param day Integer value representing the number of days to add.
 */
extern void lbRTC_Add_DD(lbRTC_time_c* time, int day) {
  int month_days = lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)time->month);
  int days = time->day;
  days += day;

  /* This could lead to a bug if adding days rolls over more than one month. */
  if (days > month_days) {
    days -= month_days;
    lbRTC_Add_MM(time, 1);
  }

  time->day = (lbRTC_day_t)days;
}

/**
 * @brief Add a specified number of hours to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param hour Integer value representing the number of hours to add.
 */
extern void lbRTC_Add_hh(lbRTC_time_c* time, int hour) {
  int curr_hr = time->hour;

  curr_hr += hour;
  if (curr_hr >= lbRTC_HOURS_PER_DAY) {
    lbRTC_Add_DD(time, curr_hr / lbRTC_HOURS_PER_DAY);
    curr_hr %= lbRTC_HOURS_PER_DAY;
  }

  time->hour = (lbRTC_hour_t)curr_hr;
}

/**
 * @brief Add a specified number of minutes to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param min Integer value representing the number of minutes to add.
 */
extern void lbRTC_Add_mm(lbRTC_time_c* time, int min) {
  int curr_min = time->min;

  curr_min += min;
  if (curr_min >= lbRTC_MINUTES_PER_HOUR) {
    lbRTC_Add_hh(time, curr_min / lbRTC_MINUTES_PER_HOUR);
    curr_min %= lbRTC_MINUTES_PER_HOUR;
  }

  time->min = (lbRTC_min_t)curr_min;
}

/**
 * @brief Add a specified number of seconds to an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param sec Integer value representing the number of seconds to add.
 */
extern void lbRTC_Add_ss(lbRTC_time_c* time, int sec) {
  int curr_sec = time->sec;

  curr_sec += sec;
  if (curr_sec >= lbRTC_SECONDS_PER_MINUTE) {
    lbRTC_Add_mm(time, curr_sec / lbRTC_SECONDS_PER_MINUTE);
    curr_sec %= lbRTC_SECONDS_PER_MINUTE;
  }

  time->sec = (lbRTC_sec_t)curr_sec;
}

/**
 * @brief Add the values of an lbRTC_time_c structure to another lbRTC_time_c structure.
 *
 * This function adds the values of one lbRTC_time_c structure (add_time) to another
 * lbRTC_time_c structure (time). The values are added in the order of least to most
 * significant time unit: seconds, minutes, hours, days, months, years.
 *
 * @param time Pointer to an lbRTC_time_c structure, which will be modified.
 * @param add_time Pointer to an lbRTC_time_c structure containing the values to add.
 */
extern void lbRTC_Add_Date(lbRTC_time_c* time, const lbRTC_time_c* add_time) {
  lbRTC_Add_ss(time, add_time->sec);
  lbRTC_Add_mm(time, add_time->min);
  lbRTC_Add_hh(time, add_time->hour);
  lbRTC_Add_DD(time, add_time->day);
  lbRTC_Add_MM(time, add_time->month);
  lbRTC_Add_YY(time, add_time->year);
}

/**
 * @brief Subtract a specified number of years from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param year Integer value representing the number of years to subtract.
 */
extern void lbRTC_Sub_YY(lbRTC_time_c* time, int year) {
  time->year -= (lbRTC_year_t)year;
}

/**
 * @brief Subtract a specified number of months from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param month Integer value representing the number of months to subtract.
 */
extern void lbRTC_Sub_MM(lbRTC_time_c* time, int month) {
  int mo = time->month - month;
  if (mo < lbRTC_JANUARY) {
    int t_mo = mo;
    int sub_year;

    if (mo == 0) {
      mo = lbRTC_DECEMBER;
      sub_year = 1;
    }
    else {
      t_mo = ABS(mo);
      sub_year = t_mo / lbRTC_MONTHS_MAX + 1; /* Years to subtract */
      mo = lbRTC_MONTHS_MAX - (t_mo % lbRTC_MONTHS_MAX); /* Final month we end on */
    }

    lbRTC_Sub_YY(time, sub_year);
  }

  time->month = (lbRTC_month_t)mo;
}

/**
 * @brief Subtract a specified number of days from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param days Integer value representing the number of days to subtract.
 */
extern void lbRTC_Sub_DD(lbRTC_time_c* time, int days) {
  int day = time->day;
  int month_days;

  if (time->month == lbRTC_JANUARY) {
    month_days = lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)lbRTC_DECEMBER);
  }
  else {
    month_days = lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)(time->month - 1));
  }

  day -= days;

  /* Check if day rolled back to previous month */
  if (day <= 0) {
    if (day == 0) {
      day = month_days; /* Landed on last day of the month */
    }
    else {
      day += month_days; /* Bring day positive */
    }

    /* Another 'bug' here. If more than 1 month of days is subtracted, month will be wrong */
    lbRTC_Sub_MM(time, 1);
  }

  time->day = (lbRTC_day_t)day;
}

/**
 * @brief Subtract a specified number of hours from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param hour Integer value representing the number of hours to subtract.
 */
extern void lbRTC_Sub_hh(lbRTC_time_c* time, int hour) {
  int h = time->hour;
  h -= hour;

  if (h < 0) {
    int temp_h = h;
    int sub_days;

    temp_h = ABS(h);
    sub_days = temp_h / lbRTC_HOURS_PER_DAY + 1;
    h = lbRTC_HOURS_PER_DAY - (temp_h % lbRTC_HOURS_PER_DAY);

    /* Check if we're rolling over the day */
    if (h == lbRTC_HOURS_PER_DAY) {
      h = 0;
      sub_days--;
    }

    lbRTC_Sub_DD(time, sub_days);
  }

  time->hour = (lbRTC_hour_t)h;
}

/**
 * @brief Subtract a specified number of minutes from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param min Integer value representing the number of minutes to subtract.
 */
extern void lbRTC_Sub_mm(lbRTC_time_c* time, int min) {
  int t_min = time->min;
  t_min -= min;

  if (t_min < 0) {
    int temp_min = t_min;
    int sub_hours;

    temp_min = ABS(t_min);
    sub_hours = temp_min / lbRTC_MINUTES_PER_HOUR + 1;
    t_min = lbRTC_MINUTES_PER_HOUR - (temp_min % lbRTC_MINUTES_PER_HOUR);

    /* Check if we're rolling over the hour */
    if (t_min == lbRTC_MINUTES_PER_HOUR) {
      t_min = 0;
      sub_hours--;
    }

    lbRTC_Sub_hh(time, sub_hours);
  }

  time->min = (lbRTC_min_t)t_min;
}

/**
 * @brief Subtract a specified number of seconds from an lbRTC_time_c structure.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @param sec Integer value representing the number of seconds to subtract.
 */
extern void lbRTC_Sub_ss(lbRTC_time_c* time, int sec) {
  int t_sec = time->sec;
  t_sec -= sec;

  if (t_sec < 0) {
    int temp_sec = t_sec;
    int sub_mins;

    temp_sec = ABS(t_sec);
    sub_mins = temp_sec / lbRTC_SECONDS_PER_MINUTE + 1;
    t_sec = lbRTC_SECONDS_PER_MINUTE - (temp_sec % lbRTC_SECONDS_PER_MINUTE);

    /* Check if we're rolling over the minute */
    if (t_sec == lbRTC_SECONDS_PER_MINUTE) {
      t_sec = 0;
      sub_mins--;
    }

    lbRTC_Sub_mm(time, sub_mins);
  }

  time->sec = (lbRTC_sec_t)t_sec;
}

/**
 * @fabricated
 * 
 * @brief Subtract the values of an lbRTC_time_c structure from another lbRTC_time_c structure.
 *
 * This function subtracts the values of one lbRTC_time_c structure (sub_time) from another
 * lbRTC_time_c structure (time). The values are subtracted in the order of least to most
 * significant time unit: seconds, minutes, hours, days, months, years.
 *
 * @param time Pointer to an lbRTC_time_c structure, which will be modified.
 * @param sub_time Pointer to an lbRTC_time_c structure containing the values to subtract.
 */
/*
extern void lbRTC_Sub_Date(lbRTC_time_c* time, const lbRTC_time_c* sub_time) {
  lbRTC_Sub_ss(time, sub_time->sec);
  lbRTC_Sub_mm(time, sub_time->min);
  lbRTC_Sub_hh(time, sub_time->hour);
  lbRTC_Sub_DD(time, sub_time->day);
  lbRTC_Sub_MM(time, sub_time->month);
  lbRTC_Sub_YY(time, sub_time->year);
}
*/

/**
 * @brief Calculate the day of the week for a given date.
 *
 * @param year Year value.
 * @param month Month value.
 * @param day Day value.
 * @return The day of the week as an lbRTC_weekday_t value.
 */
extern lbRTC_weekday_t lbRTC_Week(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day) {
  /* 00:00:00 @ January 1st, 1901 */
  static const lbRTC_time_c a_time = {
    0, 0, 0,
    1, 0, 1,
    1901
  };

  /* This initialization is required lmao */
  lbRTC_time_c b_time = {
    0, 0, 0,
    0, 0, 0,
    0000
  };

  b_time.year = year;
  b_time.month = month;
  b_time.day = day;

  return (lbRTC_weekday_t)((lbRTC_GetIntervalDays(&a_time, &b_time) + 2) % lbRTC_WEEK);
}

/**
 * @brief Copy the values of one lbRTC_time_c structure to another.
 *
 * @param dst Pointer to the destination lbRTC_time_c structure.
 * @param src Pointer to the source lbRTC_time_c structure.
 */
extern void lbRTC_TimeCopy(lbRTC_time_c* dst, const lbRTC_time_c* src) {
  *dst = *src;
}

/**
 * @brief Check if the given time is valid.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @return Non-zero (TRUE) if the time is valid, zero (FALSE) otherwise.
 */
extern int lbRTC_IsValidTime(const lbRTC_time_c* time) {
  static const u8 day_tbl[] = {
    00,
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
  };

  int res;

  if (
    (time->year < lbRTC_YEAR_MIN ||  time->year > lbRTC_YEAR_MAX) ||
    (time->month == lbRTC_MONTHS_BEGIN || time->month > lbRTC_MONTHS_MAX) ||
    (time->day == 0) ||
    (time->hour > 23) ||
    (time->min > 59) ||
    (time->sec > 59)
  ) {
    res = FALSE;
  }
  else {
    if (time->day == 29 && time->month == 2) {
      res = lbRTC_IS_LEAPYEAR(time->year);
    }
    else if (time->day > day_tbl[time->month]) {
      res = FALSE;
    }
    else {
      res = TRUE;
    }
  }

  return res;
}

/**
 * @brief Check if the given time is valid for save data.
 *
 * @param time Pointer to an lbRTC_time_c structure.
 * @return Non-zero (TRUE) if the time is invalid, zero (FALSE) otherwise.
 */
extern int lbRTC_time_c_save_data_check(const lbRTC_time_c* time) {
  int res = FALSE;

  if (
    (time->sec < 60) &&
    (time->min < 60) &&
    (time->hour < 24) &&
    (time->day >= 1 && time->day <= 31) &&
    (time->weekday < 7) &&
    (time->month >= 1 && time->month <= 12) &&
    (time->year >= GAME_YEAR_MIN + 1 && time->year <= GAME_YEAR_MAX - 1)
  ) {
      res = TRUE;
    }

  return !res;
}

/**
 * @brief Calculate the day of the month for a given week and weekday.
 *
 * @param year Year value.
 * @param month Month value.
 * @param weeks Integer representing the week number in the month.
 * @param weekday Integer representing the day of the week.
 * @return The day of the month as an integer.
 */
extern int lbRTC_Weekly_day(lbRTC_year_t year, lbRTC_month_t month, int weeks, int weekday) {
  int t_weekday;
  
  int month_first_weekday = lbRTC_Week(year, month, 1);
  lbRTC_day_t month_days = lbRTC_GetDaysByMonth(year, month);

  weeks--;
  t_weekday = (int)(((weekday - month_first_weekday) + lbRTC_WEEK) % lbRTC_WEEK) + 1;

  while (weeks > 0) {
    t_weekday += 7;
    if (t_weekday > month_days) {
      t_weekday -= 7;
      break;
    }

    weeks--;
  }

  return t_weekday;
}
