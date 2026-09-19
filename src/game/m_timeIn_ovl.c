#include "m_timeIn_ovl.h"

#include "m_common_data.h"
#include "m_font.h"
#include "sys_matrix.h"

static mTI_Ovl_c ti_ovl_data;

static int mTI_col_type0[] = { 255,  0,   0 };
static int mTI_col_type1[] = {  60, 90, 255 };

static void mTI_change_rtctime(lbRTC_time_c* time, u16* values) {
  time->year = GAME_YEAR_MIN + values[mTI_IDX_YEAR];
  time->month = values[mTI_IDX_MONTH];
  time->day = values[mTI_IDX_DAY];
  time->weekday = lbRTC_Week(time->year, time->month, time->day);
  time->hour = values[mTI_IDX_HOUR];
  time->min = values[mTI_IDX_MIN];
  time->sec = 0;
}

static void mTI_copy_time(u16* dst, u16* src) {
  int i;

  for (i = 0; i < mTI_IDX_NUM; i++) {
    *dst = *src;
    dst++;
    src++;
  }
}

static int mTI_get_now_min(Submenu* submenu) {
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  int	min;

  if (timeIn_ovl->values[mTI_IDX_HOUR] >= 12) {
    min = timeIn_ovl->values[mTI_IDX_MIN] + (timeIn_ovl->values[mTI_IDX_HOUR] - 12) * lbRTC_MINUTES_PER_HOUR;
  }
  else {
	  min = timeIn_ovl->values[mTI_IDX_MIN] + timeIn_ovl->values[mTI_IDX_HOUR] * lbRTC_MINUTES_PER_HOUR;
  }

  return min;
}

static void mTI_set_time(Submenu* submenu) {
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  int min = mTI_get_now_min(submenu);
#ifdef TARGET_PC
  int ticks = graph_dt_60hz_ticks(gamePT, &timeIn_ovl->clock_step_accum);

  while (ticks-- > 0 && timeIn_ovl->input_disabled_flag == TRUE) {
#endif
    int now_min;
    int old_min;

    old_min = timeIn_ovl->saved_min;
    now_min = old_min + 12;

    if (now_min >= 12 * lbRTC_MINUTES_PER_HOUR) {
      now_min -= (12 * lbRTC_MINUTES_PER_HOUR);
    }

    if (
      (old_min < min && min <= now_min) ||
      (old_min > now_min &&	(old_min < min || min <= now_min))
    ) {

      if (timeIn_ovl->init_flag) {
        now_min = min;
        timeIn_ovl->input_disabled_flag = FALSE;
        sAdo_SysLevStop(0xA);
        sAdo_SysTrgStart(0x41B);
      }
      else {
        now_min = old_min;
      }
    }

    if (timeIn_ovl->init_flag == FALSE) {
      timeIn_ovl->init_flag = TRUE;
    }

    timeIn_ovl->saved_min = now_min;
#ifdef TARGET_PC
  }
#endif
}

static void mTI_window_close(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  lbRTC_time_c set_time;

  (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
  mTI_change_rtctime(&set_time, timeIn_ovl->values);

  if (menu_info->data0 == mTI_OVL_OPEN_INITIAL) {
    lbRTC_SetTime(&set_time);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
  }
  else {
    if (
      set_time.year != timeIn_ovl->original_time.year ||
      set_time.month != timeIn_ovl->original_time.month ||
      set_time.day != timeIn_ovl->original_time.day ||
      set_time.hour != timeIn_ovl->original_time.hour ||
      set_time.min != timeIn_ovl->original_time.min
    ) {
        Save_Set(cheated_flag, TRUE);
    }

    Common_Set(time_changed_flag, TRUE);
    lbRTC_TimeCopy(Common_GetPointer(newly_set_time), &set_time);
    lbRTC_GetTime(Common_GetPointer(old_time));
  }

  sAdo_SysTrgStart(NA_SE_MENU_EXIT);
}

static void mTI_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mTI_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  u32 trigger = submenu->overlay->menu_control.trigger;

  if (timeIn_ovl->input_disabled_flag == TRUE) {
    mTI_set_time(submenu);
  }
  else if ((trigger & BUTTON_START)) {
    mTI_window_close(submenu, menu_info);
  }
  else if ((trigger & (BUTTON_B | BUTTON_CLEFT))) {
    if (timeIn_ovl->sel_idx > 0) {
      sAdo_SysTrgStart(0x1003);
      timeIn_ovl->sel_idx--;
    }
  }
  else if ((trigger & (BUTTON_A | BUTTON_CRIGHT))) {
    if (timeIn_ovl->sel_idx == mTI_IDX_OK) {
      if (!(trigger & BUTTON_CRIGHT)) {
        mTI_window_close(submenu, menu_info);
      }
    }
    else {
      timeIn_ovl->sel_idx++;

      if (timeIn_ovl->sel_idx == mTI_IDX_OK) {
        u16 now_min = mTI_get_now_min(submenu);

        if (timeIn_ovl->saved_min != now_min) {
          timeIn_ovl->input_disabled_flag = TRUE;
          sAdo_SysLevStart(0xA);
          timeIn_ovl->init_flag = FALSE;
#ifdef TARGET_PC
          timeIn_ovl->clock_step_accum = 0.0f;
#endif
        }
      }

      sAdo_SysTrgStart(0xD);
    }
  }
  else if ((trigger & (BUTTON_CDOWN | BUTTON_CUP))) {
    if (timeIn_ovl->sel_idx != mTI_IDX_OK) {
      lbRTC_time_c time;
      u16 values[mTI_IDX_NUM];
      int sel_idx = timeIn_ovl->sel_idx;

      mTI_copy_time(values, timeIn_ovl->values);

      if ((trigger & BUTTON_CUP)) {
        values[sel_idx]++;

        if (sel_idx == mTI_IDX_YEAR && values[mTI_IDX_YEAR] > mTI_MAX_YEAR) {
          values[mTI_IDX_YEAR] = mTI_MIN_YEAR;
        }
      }
      else if ((trigger & BUTTON_CDOWN)) {
        if (values[sel_idx] != 0) {
          values[sel_idx]--;

          if (sel_idx == mTI_IDX_YEAR && values[sel_idx] < mTI_MIN_YEAR) {
            values[mTI_IDX_YEAR] = mTI_MAX_YEAR;
          }
        }
        else if (sel_idx == mTI_IDX_HOUR) {
          values[mTI_IDX_HOUR] = 23;
        }
        else if (sel_idx == mTI_IDX_MIN) {
          values[mTI_IDX_MIN] = 59;
        }
      }

      mTI_change_rtctime(&time, values);

      if (lbRTC_IsValidTime(&time) == FALSE) {
        if (sel_idx == mTI_IDX_YEAR) {
          values[mTI_IDX_DAY] = 28;
        }
        else if (
          (sel_idx == mTI_IDX_MONTH && values[mTI_IDX_MONTH] > 0 && values[mTI_IDX_MONTH] < 13) ||
          ((trigger & BUTTON_CDOWN) && sel_idx == mTI_IDX_DAY)
        ) {
          time.day = 31;

          while (!lbRTC_IsValidTime(&time)) {
            time.day--;
          }

          values[mTI_IDX_DAY] = time.day;
        }
        else if ((trigger & BUTTON_CUP)) {
          if (sel_idx == mTI_IDX_MONTH || sel_idx == mTI_IDX_DAY) {
            values[sel_idx] = 1;
          }
          else {
            values[sel_idx] = 0;
          }
        }
        else if (sel_idx == mTI_IDX_MONTH) {
          values[mTI_IDX_MONTH] = lbRTC_DECEMBER;
        }
      }

      mTI_copy_time(timeIn_ovl->values, values);
      sAdo_SysTrgStart(0x1);
    }
  }
}

static void mTI_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  if (menu_info->data0 == mTI_OVL_OPEN_INITIAL) {
    mNtc_auto_nwrite_time_ct();
  }

  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mTI_timeIn_ovl_move(Submenu* submenu) {
  static mSM_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mTI_move_Move,
    &mTI_move_Play,
    (mSM_MOVE_PROC)&none_proc1,
    (mSM_MOVE_PROC)&none_proc1,
    &mTI_move_End
  };

  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_TIMEIN];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx tim_win_mode[];
extern Gfx tim_win_model[];
extern Gfx tim_win_month_model[];
extern Gfx tim_win_youbi_model[];

extern u8 tim_win_sun_tex_rgb_i4[];
extern u8 tim_win_mon_tex_rgb_i4[];
extern u8 tim_win_tue_tex_rgb_i4[];
extern u8 tim_win_wed_tex_rgb_i4[];
extern u8 tim_win_thu_tex_rgb_i4[];
extern u8 tim_win_fri_tex_rgb_i4[];
extern u8 tim_win_sat_tex_rgb_i4[];

extern u8 tim_win_january_tex_rgb_i4[];
extern u8 tim_win_february_tex_rgb_i4[];
extern u8 tim_win_march_tex_rgb_i4[];
extern u8 tim_win_april_tex_rgb_i4[];
extern u8 tim_win_may_tex_rgb_i4[];
extern u8 tim_win_june_tex_rgb_i4[];
extern u8 tim_win_july_tex_rgb_i4[];
extern u8 tim_win_august_tex_rgb_i4[];
extern u8 tim_win_september_tex_rgb_i4[];
extern u8 tim_win_october_tex_rgb_i4[];
extern u8 tim_win_november_tex_rgb_i4[];
extern u8 tim_win_december_tex_rgb_i4[];

static void mTI_set_frame_dl(Submenu* submenu, GRAPH* graph, f32 x, f32 y) {
  static u8* week_tex[lbRTC_WEEK] = {
    tim_win_sun_tex_rgb_i4,
    tim_win_mon_tex_rgb_i4,
    tim_win_tue_tex_rgb_i4,
    tim_win_wed_tex_rgb_i4,
    tim_win_thu_tex_rgb_i4,
    tim_win_fri_tex_rgb_i4,
    tim_win_sat_tex_rgb_i4
  };

  static u8* month_tex[lbRTC_MONTHS_MAX] = {
    tim_win_january_tex_rgb_i4,
    tim_win_february_tex_rgb_i4,
    tim_win_march_tex_rgb_i4,
    tim_win_april_tex_rgb_i4,
    tim_win_may_tex_rgb_i4,
    tim_win_june_tex_rgb_i4,
    tim_win_july_tex_rgb_i4,
    tim_win_august_tex_rgb_i4,
    tim_win_september_tex_rgb_i4,
    tim_win_october_tex_rgb_i4,
    tim_win_november_tex_rgb_i4,
    tim_win_december_tex_rgb_i4
  };

  int week;
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  Gfx* gfx;
  f32 tex_x;
  f32 tex_y;
  u8 s;
  u8 t;
  int* col;

  week = lbRTC_Week(GAME_YEAR_MIN + timeIn_ovl->values[mTI_IDX_YEAR], timeIn_ovl->values[mTI_IDX_MONTH], timeIn_ovl->values[mTI_IDX_DAY]);

  Matrix_translate(x * 16.0f, y * 16.0f, 140.0f, MTX_LOAD);
  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Initialize RDP settings */
  gSPDisplayList(gfx++, tim_win_mode);

  /* Setup matrix */
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  /* Adjust scrolling background texture position */
  tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
  tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
  s = (int)tex_x;
  t = (int)tex_y;
  gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, s, t, 32, 32);

  /* Draw window background */
  gSPDisplayList(gfx++, tim_win_model);
  
  /* Set text color */
  if (timeIn_ovl->sel_idx == mTI_IDX_MONTH) {
    col = mTI_col_type0;
  }
  else {
    col = mTI_col_type1;
  }

  gDPSetPrimColor(gfx++, 0, 255, col[0], col[1], col[2], 255);

  /* Draw month text */
  gSPSegment(gfx++, G_MWO_SEGMENT_8, month_tex[timeIn_ovl->values[mTI_IDX_MONTH] - 1]);
  gSPDisplayList(gfx++, tim_win_month_model);
  
  /* Draw weekday text */
  gSPSegment(gfx++, G_MWO_SEGMENT_8, week_tex[week]);
  gSPDisplayList(gfx++, tim_win_youbi_model);

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

extern Gfx tim_hari_mode[];
extern Gfx tim_hari_b1T_model[];
extern Gfx tim_hari_b2T_model[];
extern Gfx tim_hari_b3T_model[];

static void mTI_set_clock(Submenu* submenu, GRAPH* graph, f32 x, f32 y) {
  static Gfx* displayList_table[] = {
    tim_hari_b2T_model,
    tim_hari_b1T_model,
    tim_hari_b3T_model
  };

  s16 r[3];
  int i;
  u16 save_min = submenu->overlay->timeIn_ovl->saved_min;
  Gfx* gfx;

  r[0] = F32_TO_S16(-(((f32)(save_min % lbRTC_MINUTES_PER_HOUR) / (f32)lbRTC_MINUTES_PER_HOUR) *
                       65536.0f)); // minute hand
  r[1] = F32_TO_S16(-(((f32)save_min / (f32)((lbRTC_MINUTES_PER_HOUR * lbRTC_HOURS_PER_DAY) / 2)) *
                       65536.0f)); // hour hand
  r[2] = 0; // second hand?

  Matrix_translate((x + -61.0f) * 16.0f, (y + 45.0f) * 16.0f, 140.0f, MTX_LOAD);
  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_MULT);
  Matrix_translate(-5.0f, -4.0f, 0.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Initialize RDP settings */
  gSPDisplayList(gfx++, tim_hari_mode);

  for (i = 0; i < 3; i++) {
    /* Rotate & draw the clock hand */
    Matrix_push();
    Matrix_RotateZ(r[i], MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, displayList_table[i]);
    Matrix_pull();
  }

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mTI_set_character(Submenu* submenu, GAME* game, f32 x, f32 y) {
  static u8 str_line_adjust[17] = "Adjust the clock.";
  static u8 str_line_ok[2] = "OK";
  static f32 set_pos[mTI_IDX_NUM][2] = {
    {  79.0f, 115.0f }, // mTI_IDX_HOUR
    { 103.0f, 115.0f }, // mTI_IDX_MIN
    {   0.0f,   0.0f }, // mTI_IDX_MONTH
    { 151.0f, 141.0f }, // mTI_IDX_DAY
    { 196.0f, 141.0f }  // mTI_IDX_YEAR
  };

  u8 str[4];
  int* col;
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;
  f32* set_pos_p = &set_pos[0][0];
  int i;

  /* Draw 'Adjust the clock.' title text */
  mFont_SetLineStrings(
    game,
    str_line_adjust, sizeof(str_line_adjust),
    x + 131.0f, -y + 82.0f,
    255, 255, 255, 255,
    FALSE,
    TRUE,
    0.875f, 0.875f,
    mFont_MODE_POLY
  );

  /* Draw all numeric values */
  for (i = 0; i < mTI_IDX_NUM; set_pos_p += 2, i++) {
    if (i != mTI_IDX_MONTH) {
      int digits = 2;
      int value = timeIn_ovl->values[i];
      f32 text_x = set_pos_p[0];
#ifdef TARGET_PC
      if (i == mTI_IDX_YEAR) {
        value += GAME_YEAR_MIN;
        digits = 4;
        text_x -= 12.0f;
      }
#endif
      if (i == timeIn_ovl->sel_idx) {
        col = mTI_col_type0;
      }
      else {
        col = mTI_col_type1;
      }

      mFont_UnintToString(str, digits, value, digits, FALSE, TRUE, FALSE);
      mFont_SetLineStrings(
        game,
        str, digits,
        x + text_x, -y + set_pos_p[1],
        col[0], col[1], col[2], 255,
        FALSE,
        TRUE,
        1.0f, 1.0f,
        mFont_MODE_POLY
      );
    }
  }

  if (timeIn_ovl->sel_idx == mTI_IDX_OK) {
    col = mTI_col_type0;
  }
  else {
    col = mTI_col_type1;
  }

  /* Draw 'OK' */
  mFont_SetLineStrings(
    game,
    str_line_ok, sizeof(str_line_ok),
    x + 220.0f, -y + 141.0f,
    col[0], col[1], col[2], 255,
    FALSE,
    TRUE,
    1.0f, 1.0f,
    mFont_MODE_POLY
  );
}

static void mTI_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];
  GRAPH* graph = game->graph;

  mTI_set_frame_dl(submenu, graph, x, y);
  mTI_set_clock(submenu, graph, x, y);
  (*submenu->overlay->set_char_matrix_proc)(graph);
  mTI_set_character(submenu, game, x, y);
}

static void mTI_timeIn_ovl_draw(Submenu* submenu, GAME* game) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_TIMEIN];

  (*menu_info->pre_draw_func)(submenu, game);
  mTI_set_dl(submenu, game, menu_info);
}

extern void mTI_timeIn_ovl_set_proc(Submenu* submenu) {
  mSM_Control_c* control = &submenu->overlay->menu_control;

  control->menu_move_func = &mTI_timeIn_ovl_move;
  control->menu_draw_func = &mTI_timeIn_ovl_draw;
}

static void mTI_timeIn_ovl_init(Submenu* submenu) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_TIMEIN];
  mTI_Ovl_c* timeIn_ovl = submenu->overlay->timeIn_ovl;

  if (Common_Get(time_changed_flag)) {
    lbRTC_time_c time;

    lbRTC_GetTime(&time);
    lbRTC_Sub_ss(&time, Common_Get(old_time).sec);
    lbRTC_Sub_mm(&time, Common_Get(old_time).min);
    lbRTC_Sub_hh(&time, Common_Get(old_time).hour);
    time.day = 0;
    time.month = 0;
    time.year = 0;

    lbRTC_TimeCopy(&timeIn_ovl->original_time, Common_GetPointer(newly_set_time));
    lbRTC_Add_Date(&timeIn_ovl->original_time, &time);
  }
  else {
    lbRTC_GetTime(&timeIn_ovl->original_time);
  }

  if (timeIn_ovl->original_time.year > (GAME_YEAR_MIN + mTI_MAX_YEAR)) {
    timeIn_ovl->values[mTI_IDX_YEAR] = mTI_MAX_YEAR;
    timeIn_ovl->original_time.year = GAME_YEAR_MIN + mTI_MAX_YEAR;
  }
  else if (timeIn_ovl->original_time.year < (GAME_YEAR_MIN + mTI_MIN_YEAR)) {
    timeIn_ovl->values[mTI_IDX_YEAR] = mTI_MIN_YEAR;
    timeIn_ovl->original_time.year = GAME_YEAR_MIN + mTI_MIN_YEAR;
  }
  else {
    timeIn_ovl->values[mTI_IDX_YEAR] = timeIn_ovl->original_time.year - GAME_YEAR_MIN;
  }

  timeIn_ovl->values[mTI_IDX_MONTH] = timeIn_ovl->original_time.month;
  timeIn_ovl->values[mTI_IDX_DAY] = timeIn_ovl->original_time.day;
  timeIn_ovl->values[mTI_IDX_HOUR] = timeIn_ovl->original_time.hour;
  timeIn_ovl->values[mTI_IDX_MIN] = timeIn_ovl->original_time.min;

  timeIn_ovl->saved_min = timeIn_ovl->values[mTI_IDX_MIN] + timeIn_ovl->values[mTI_IDX_HOUR] * lbRTC_MINUTES_PER_HOUR;
  if (timeIn_ovl->saved_min >= (12 * lbRTC_MINUTES_PER_HOUR)) {
    timeIn_ovl->saved_min -= (12 * lbRTC_MINUTES_PER_HOUR);
  }

  timeIn_ovl->sel_idx = mTI_IDX_HOUR;
  timeIn_ovl->input_disabled_flag = FALSE;

  submenu->overlay->menu_control.animation_flag = FALSE;
  menu_info->proc_status = mSM_OVL_PROC_MOVE;
  menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
  menu_info->move_drt = mSM_MOVE_IN_TOP;
}

extern void mTI_timeIn_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->timeIn_ovl == NULL) {
    mem_clear((u8*)&ti_ovl_data, sizeof(mTI_Ovl_c), 0);
    overlay->timeIn_ovl = &ti_ovl_data;
  }

  mTI_timeIn_ovl_init(submenu);
  mTI_timeIn_ovl_set_proc(submenu);
}

extern void mTI_timeIn_ovl_destruct(Submenu* submenu) {
  submenu->overlay->timeIn_ovl = NULL;
}
