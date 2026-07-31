/**
 * @file m_time.c
 * @brief Time management functions for handling various time-related operations.
 *
 * This file contains functions to manage and manipulate time values, including
 * - Getting the term index
 * - Checking and setting renewal time flags
 * - Converting date and time structures
 * - Updating renewal time values
 * - Displaying debug time information
 * - Controlling time steps
 * - Initializing and updating time-related values
 * - Checking and adjusting RTC time limits
 *
 * Functions in this file are used to perform operations on time values,
 * handle debug displays, and manage the real-time clock (RTC) time.
 *
 * Functions:
 * - mTM_get_termIdx(): Get the term index based on the current date
 * - mTM_check_renew_time(): Check if the renewal time flag is set
 * - mTM_off_renew_time(): Clear the renewal time flag
 * - mTM_set_renew_is(): Set all renewal time flags
 * - mTM_set_renew_time(): Update the renewal time values
 * - mTM_ymd_2_time(): Convert YMD date structure to time structure
 * - mTM_renewal_renew_time(): Update renewal time if the current date is different from the saved date
 * - mTM_disp_time(): Display the current time in debug mode
 * - mTM_TimeStepControl(): Control the time step based on input conditions
 * - mTM_time_init(): Initialize time-related values
 * - mTM_time(): Update time-related values and handle debug display
 * - mTM_rtcTime_limit_check(): Check if the RTC time is within the allowed limits and adjust if necessary
 */


#include "m_time.h"

#include "game.h"
#include "gfxalloc.h"
#include "libu64/gfxprint.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_field_info.h"
#include "m_kabu_manager.h"
#include "zurumode.h"

static int debug_disp = 0;
static u8 l_renew_is = 0;


const lbRTC_time_c mTM_rtcTime_clear_code = {
  0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF,
  0xFFFF
};

const lbRTC_ymd_c mTM_rtcTime_ymd_clear_code = {
  0xFFFF,
  0xFF, 0xFF
};

const lbRTC_time_c mTM_rtcTime_default_code = {
  0, 0, 12,
  1, 6, 1,
  2000
};

static mTM_calendar_term_t mTM_calender[mTM_TERM_NUM] = {
  {
    2, 3,
    mTM_SEASON_WINTER,
    0x0050, 0x0025
  },
  {
    2, 17,
    mTM_SEASON_WINTER,
    0x0050, 0x0025
  },
    {
    2, 24,
    mTM_SEASON_WINTER,
    0x0050, 0x0025
  },
  {
    3, 31,
    mTM_SEASON_SPRING,
    0x0001, 0x0004
  },
  {
    4, 8,
    mTM_SEASON_SPRING,
    0x004f, 0x0024
  },
  {
    5, 25,
    mTM_SEASON_SPRING,
    0x0001, 0x0004
  },
  {
    7, 22,
    mTM_SEASON_SUMMER,
    0x0001, 0x0004
  },
  {
    8, 31,
    mTM_SEASON_SUMMER,
    0x0001, 0x0004
  },
  {
    9, 15,
    mTM_SEASON_SUMMER,
    0x0001, 0x0004
  },
  {
    9, 30,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    10, 15,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    10, 29,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    11, 12,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    11, 28,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    12, 9,
    mTM_SEASON_AUTUMN,
    0x0001, 0x0004
  },
  {
    12, 17,
    mTM_SEASON_WINTER,
    0x0051, 0x0026
  },
  {
    12, 25,
    mTM_SEASON_WINTER,
    0x0051, 0x0026
  },
  {
    12, 31,
    mTM_SEASON_WINTER,
    0x0050, 0x0025
  }
};

/**
 * Get the index of the current term based on the current date and climate.
 *
 * @return The index of the current term.
 */
static int mTM_get_termIdx() {
  lbRTC_month_t month = Common_Get(time.rtc_time.month);
  lbRTC_day_t day = Common_Get(time.rtc_time.day);
  mTM_calendar_term_t* term_info = mTM_calender;
  int term;


  if (mFI_GetClimate() == mFI_CLIMATE_ISLAND) {
    return mTM_TERM_7;
  }
  
  for (term = 0; term < mTM_TERM_NUM; term_info++, term++) {
    if (month < term_info->month || (month == term_info->month && day <= term_info->day)) {
      return term;
    }
  }

  return -1;
}

/**
 * Set the season, term index, and background item properties based on the term index provided.
 *
 * @param term_idx The index of the term used to set the season and associated properties.
 */
extern void mTM_set_season_com(int term_idx) {
  const mTM_calendar_term_t* term_info = mTM_calender + term_idx;

  Common_Set(time.season, term_info->season);
  Common_Set(time.term_idx, term_idx);
  Common_Set(time.bgitem_profile, term_info->bgitem_profile);
  Common_Set(time.bgitem_bank, term_info->bgitem_bank);
}

/**
 * Set the season and associated properties based on the current date and climate.
 */
extern void mTM_set_season() {
  mTM_set_season_com(mTM_get_termIdx());
}

/**
 * Clear the renewal flags.
 */
extern void mTM_clear_renew_is() {
  l_renew_is = 0;
}

/**
 * Check if a given renew_flag is set.
 *
 * @param renew_flag The flag to check for renewal status.
 * @return TRUE if the renew_flag is set, FALSE otherwise.
 */
extern int mTM_check_renew_time(u8 renew_flag) {
  int renew = FALSE;
    
  if (((l_renew_is >> renew_flag) & 1) == 1) {
    renew = TRUE;
  }

  return renew;
}

/**
 * Turn off a given renew_flag.
 *
 * @param renew_flag The flag to be turned off.
 */
extern void mTM_off_renew_time(u8 renew_flag) {
    l_renew_is &= ~(1 << renew_flag);
}

/**
 * Set all the renewal flags.
 */
extern void mTM_set_renew_is() {
    l_renew_is = mTM_RENEW_TIME_ALL;
}


/**
 * Set the renewal time based on the given lbRTC_time_c struct.
 *
 * @param renew_time Pointer to the lbRTC_ymd_c struct where the renewal time will be stored.
 * @param time Pointer to the lbRTC_time_c struct from which the renewal time will be taken.
 */
extern void mTM_set_renew_time(lbRTC_ymd_c* renew_time, lbRTC_time_c* time) {
  renew_time->year = time->year;
  renew_time->month = time->month;
  renew_time->day = time->day;
}

/**
 * Convert lbRTC_ymd_c to lbRTC_time_c, setting time to midnight and calculating the weekday.
 *
 * @param time Pointer to the lbRTC_time_c struct where the converted time will be stored.
 * @param ymd Pointer to the lbRTC_ymd_c struct containing the date to be converted.
 */
extern void mTM_ymd_2_time(lbRTC_time_c* time, lbRTC_ymd_c* ymd) {
  time->year = ymd->year;
  time->month = ymd->month;
  time->day = ymd->day;
  time->hour = 0;
  time->min = 0;
  time->sec = 0;
  time->weekday = lbRTC_Week(ymd->year, ymd->month, ymd->day);
}

/**
 * Check if the renewal time has changed, and if so, update the renewal time and set renewal flags.
 */
extern void mTM_renewal_renew_time() {
  lbRTC_ymd_c* renew_time = Save_GetPointer(renew_time);
  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

#ifdef TARGET_PC
  if (rtc_time->year == 0) return;
#endif

  // Check if the renewal time has changed
  if (
    (renew_time->year != rtc_time->year) ||
    (renew_time->month != rtc_time->month) ||
    (renew_time->day != rtc_time->day)
  ) {
    // If the renewal time has changed, update the renewal time and set renewal flags
    mTM_set_renew_time(renew_time, rtc_time);
    mTM_set_renew_is();
  }
}

/**
 * Display the current time in debug mode if certain conditions are met.
 *
 * @param unused An unused parameter.
 */
static void mTM_disp_time(int unused) {
  static int disp;

  // Check if debug mode is enabled and the appropriate button is pressed
  if (Common_Get(time.add_idx) != 1 && zurumode_flag != 0 && (gamePT->pads[1].on.button & BUTTON_A) == BUTTON_A) {
    disp ^= TRUE;
    Common_Set(time.disp, disp);
  }

  // If the display flag is set, draw the time on screen
  if (Common_Get(time.disp) == TRUE) {
    gfxprint_t gfxprint;
    GRAPH* g;
    Gfx* poly_opaque;
    Gfx* line_opa;
    Gfx* gfx_temp;

    g = gamePT->graph;
    gfxprint_init(&gfxprint);
    
    OPEN_DISP(g);

    poly_opaque = NOW_POLY_OPA_DISP;
    gfx_temp = gfxopen(poly_opaque);
    
    gSPDisplayList(NOW_OVERLAY_DISP++, gfx_temp);

    /* Debug mode draw time in format: YYYY MM/DD hh:mm ss */
    gfxprint_open(&gfxprint, gfx_temp);
    gfxprint_color(&gfxprint, 255, 255, 255, 255); /* White */
    gfxprint_locate8x8(&gfxprint, 3, 3);
    gfxprint_printf(&gfxprint, "%04d", Common_Get(time.rtc_time.year));
    gfxprint_locate8x8(&gfxprint, 8, 3);
    gfxprint_printf(&gfxprint, "%02d/", Common_Get(time.rtc_time.month));
    gfxprint_locate8x8(&gfxprint, 11, 3);
    gfxprint_printf(&gfxprint, "%02d", Common_Get(time.rtc_time.day));
    gfxprint_locate8x8(&gfxprint, 14, 3);
    gfxprint_printf(&gfxprint, "%02d:", Common_Get(time.rtc_time.hour));
    gfxprint_locate8x8(&gfxprint, 17, 3);
    gfxprint_printf(&gfxprint, "%02d", Common_Get(time.rtc_time.min));
    gfxprint_locate8x8(&gfxprint, 20, 3);
    gfxprint_printf(&gfxprint, "%02d", Common_Get(time.rtc_time.sec));

    gfx_temp = gfxprint_close(&gfxprint);
    gSPEndDisplayList(gfx_temp++);
    gfxclose(poly_opaque, gfx_temp);
    SET_POLY_OPA_DISP(gfx_temp);
    gfxprint_cleanup(&gfxprint);

    CLOSE_DISP(g);
  }
}

#define mTM_TIMESTEP_NUM 4

/**
 * Control the time step based on certain input conditions.
 *
 * @return TRUE if the time step control is active, FALSE otherwise.
 */
static int mTM_TimestepControl() {
  // Define time step values and an index for tracking the current time step
  static int timestep[mTM_TIMESTEP_NUM] = {2, 4, 120, 240};
  static int id;

  int add_sec;
  int tstep;

#if VERSION < VER_GAFU01_00
  // Check if certain input conditions are met, and if so, adjust the time step and flags accordingly
  if (zurumode_flag >= 2 && debug_disp == 1 && (gamePT->pads[1].on.button & BUTTON_R) == BUTTON_R) {
    if (id < mTM_TIMESTEP_NUM) {
      Common_Set(time.rtc_crashed, TRUE);

      tstep = timestep[id];
      Common_Set(time.add_sec, tstep);

      add_sec = tstep - 1;
      if (add_sec > 10) {
        add_sec = 10;
      }

      SETREG(SREG, 3, add_sec);
      id++;
    } else {
      Common_Set(time.rtc_crashed, FALSE);
      Common_Set(time.add_idx, 0);
      lbRTC_SetTime(Common_GetPointer(time.rtc_time));

      SETREG(SREG, 3, 0);
      id = 0;
    }
  }
#endif

  return id != 0;
}

#define mTM_SECONDS_IN_HOUR_F 3600.0f
#define mTM_SECONDS_IN_HALFDAY_F 43200.0f
#define SHORT_ANGLE_MAX 65536.0f

/**
 * Initialize time-related values.
 */
extern void mTM_time_init() {
  u8 day;
  int add_sec;
  int add_min;
  int time_add_sec;
  int temp;;

  day = Common_Get(time.rtc_time.day);
  if (Common_Get(time.rtc_enabled) == TRUE && Common_Get(time.rtc_crashed) == FALSE) {
    // If the RTC is enabled and not crashed, get the current time
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
  }
  else {
    // Else, calculate the time based on the stored values
    add_sec = Common_Get(time.under_sec);
    add_sec += Common_Get(time.add_sec);
    add_min = add_sec / mTM_SECONDS_IN_MINUTE;

    for (time_add_sec = 0; add_sec >= 60; add_min--) {
      add_sec -= mTM_SECONDS_IN_MINUTE;
      time_add_sec++;
    }


    lbRTC_Add_ss(Common_GetPointer(time.rtc_time), time_add_sec);
    Common_Set(time.rtc_time.weekday, lbRTC_Week(Common_Get(time.rtc_time.year), Common_Get(time.rtc_time.month), Common_Get(time.rtc_time.day)));
    Common_Set(time.under_sec, add_sec);
  }

  // Update current time and trigger Stalk Market change if the day changed
  Common_Set(time.now_sec, Common_Get(time.rtc_time.sec) + Common_Get(time.rtc_time.min) * mTM_SECONDS_IN_MINUTE + Common_Get(time.rtc_time.hour) * mTM_SECONDS_IN_HOUR);
  if (Common_Get(time.rtc_time.day) != day) {
    Kabu_manager();
  }

  // Calculate rad_hour and rad_min values for clock hands
  temp = Common_Get(time.rtc_time.sec) + Common_Get(time.rtc_time.min) * mTM_SECONDS_IN_MINUTE;
  Common_Set(time.rad_min, F32_TO_S16((temp / mTM_SECONDS_IN_HOUR_F) * SHORT_ANGLE_MAX));
  Common_Set(time.rad_hour, F32_TO_S16(((temp + Common_Get(time.rtc_time.hour) * mTM_SECONDS_IN_HOUR) /
                                       mTM_SECONDS_IN_HALFDAY_F) * SHORT_ANGLE_MAX));
}

/**
 * Update time-related values and handle debug display.
 */
extern void mTM_time() {
  lbRTC_day_t day;
  int add_sec;
  int add_min;
  int time_add_sec;
  int temp;

  day = Common_Get(time.rtc_time.day);

  // Control the time step based on certain input conditions
  mTM_TimestepControl();

  if (Common_Get(time.rtc_enabled) == TRUE && Common_Get(time.rtc_crashed) == FALSE) {
    // If the RTC is enabled and not crashed, get the current time and handle debug display
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
    if (zurumode_flag != 0 && (gamePT->pads[1].on.button & BUTTON_A) == BUTTON_A) {
      debug_disp ^= TRUE;
    }

    if (debug_disp == TRUE) {
      mTM_disp_time(0);
    }
  }
  else {
    // Else, calculate the time based on the stored values and handle debug display
    add_sec = Common_Get(time.under_sec);
    add_sec += Common_Get(time.add_sec);
    add_min = add_sec / mTM_SECONDS_IN_MINUTE;

    for (time_add_sec = 0; add_sec >= 60; add_min--) {
      add_sec -= mTM_SECONDS_IN_MINUTE;
      time_add_sec++;
    }

    lbRTC_Add_ss(Common_GetPointer(time.rtc_time), time_add_sec);
    Common_Set(
      time.rtc_time.weekday,
      lbRTC_Week(
        Common_Get(time.rtc_time.year),
        Common_Get(time.rtc_time.month),
        Common_Get(time.rtc_time.day)
      )
    );

    Common_Set(time.under_sec, add_sec);

    if (zurumode_flag != 0 && (gamePT->pads[1].on.button & BUTTON_A) == BUTTON_A) {
      debug_disp ^= TRUE;
    }

    if (debug_disp == TRUE) {
      mTM_disp_time(add_sec);
    }
  }

  Common_Set(
    time.now_sec,
    Common_Get(time.rtc_time.sec) +
      Common_Get(time.rtc_time.min) * mTM_SECONDS_IN_MINUTE +
      Common_Get(time.rtc_time.hour) * mTM_SECONDS_IN_HOUR
  );

  // Update current time and trigger Stalk Market change if the day changed
  if (Common_Get(time.rtc_time.day) != day) {
    Kabu_manager();
  }

  // Calculate rad_hour and rad_min values for clock hands
  temp = Common_Get(time.rtc_time.sec) + Common_Get(time.rtc_time.min) * mTM_SECONDS_IN_MINUTE;
  Common_Set(time.rad_min, F32_TO_S16((temp / mTM_SECONDS_IN_HOUR_F) * SHORT_ANGLE_MAX));
  Common_Set(time.rad_hour, F32_TO_S16(((temp + Common_Get(time.rtc_time.hour) * mTM_SECONDS_IN_HOUR) /
                                       mTM_SECONDS_IN_HALFDAY_F) * SHORT_ANGLE_MAX));

  // Check if the renewal time has changed, and if so, update the renewal time and set renewal flags
  mTM_renewal_renew_time();
}

/**
 * Check if the RTC time is within the allowed limits and adjust if necessary.
 */
extern void mTM_rtcTime_limit_check() {
  lbRTC_time_c time;

  // Get the current time from the RTC
  lbRTC_GetTime(&time);

  // Check if the year is within the allowed limits and adjust if necessary
  if (time.year > mTM_MAX_YEAR) {
    time.year = mTM_MAX_YEAR;
    lbRTC_SetTime(&time);
    return;
  }

  if (time.year < mTM_MIN_YEAR) {
    time.year = mTM_MIN_YEAR;
    lbRTC_SetTime(&time);
  }
}
