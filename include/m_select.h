#ifndef M_SELECT_H
#define M_SELECT_H

#include "types.h"
#include "game.h"
#include "m_view.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SELECT_COURSE_NUM_VISIBLE 14

typedef void (*GAME_PROC)(GAME*, int);

enum {
  SELECT_CHECK_A_BUTTON_RTC,
  SELECT_CHECK_A_BUTTON_TIME,
  SELECT_CHECK_A_BUTTON_STEP,
  SELECT_CHECK_A_BUTTON_WEATHER,
  SELECT_CHECK_A_BUTTON_SEX,
  SELECT_CHECK_A_BUTTON_FACE_TYPE,
  SELECT_CHECK_A_BUTTON_SWELL,
  SELECT_CHECK_A_BUTTON_DECOY,
  SELECT_CHECK_A_BUTTON_CLOTH,
  SELECT_CHECK_A_BUTTON_SUNBURN,
  SELECT_CHECK_A_BUTTON_EVENT,

  SELECT_CHECK_A_BUTTON_NUM
};

enum {
  SELECT_STATUS_MAIN,
  SELECT_STATUS_SETUP,
  SELECT_STATUS_TIME_SET,
  SELECT_STATUS_CLOTH_SEL,

  SELECT_STATUS_NUM
};

/* sizeof(struct game_select_s) == 0x0238 */
typedef struct game_select_s {
  /* 0x0000 */ GAME game;
  /* 0x00E0 */ View view;
  /* 0x0200 */ int status;
  /* 0x0204 */ int cursor_x;
  /* 0x0208 */ int cursor_y;
  /* 0x020C */ int step;
  /* 0x0210 */ int step_add;
  /* 0x0214 */ int selected_course;
  /* 0x0218 */ int top_course; /* course at top of screen it seems */
  /* 0x021C */ u32 unk_21C;
  /* 0x0220 */ int button_step;
  /* 0x0224 */ u8 name[PLAYER_NAME_LEN];
  /* 0x0228 */ int unk_228[3];
#ifdef TARGET_PC
  /* Preserve the original 60 Hz D-pad repeat cadence at variable frame rates. */
  f32 button_step_accum;
#endif
} GAME_SELECT;

extern void select_init(GAME* game);
extern void select_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
