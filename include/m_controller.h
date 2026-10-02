#ifndef M_CONTROLLER_H
#define M_CONTROLLER_H

#include "types.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)

/* sizeof(struct controller_s) == 0x38 */
typedef struct controller_s {
  /* 0x00 */ f32 move_pX;
  /* 0x04 */ f32 move_pY;
  /* 0x08 */ f32 move_pR;
  /* 0x0C */ s16 move_angle;

  /* 0x10 */ f32 last_move_pX;
  /* 0x14 */ f32 last_move_pY;
  /* 0x18 */ f32 last_move_pR;
  /* 0x1C */ s16 last_move_angle;

  /* 0x20 */ f32 adjusted_pX;
  /* 0x24 */ f32 adjusted_pY;
  /* 0x28 */ f32 adjusted_pR;
  
  /* 0x2C */ f32 last_adjusted_pX;
  /* 0x30 */ f32 last_adjusted_pY;
  /* 0x34 */ f32 last_adjusted_pR;
} MCON;

#define STICK_MIN 9.899495f
#define STICK_MAX 61.0f
#define STICK_UNCORRECTED_SCALE (1.0f / STICK_MAX)
#define STICK_CORRECTED_SCALE (1.0f / (STICK_MAX - STICK_MIN))

extern void mCon_ct();
extern void mCon_dt();
extern void mCon_calc(MCON* mcon, f32 stick_x, f32 stick_y);
extern void mCon_main(GAME* game);
extern int mCon_mouse_action_pressed(void);
extern int mCon_mouse_dash_held(void);

extern int chkButton(u16 button);
extern u16 getButton();
extern int chkTrigger(u16 button);
extern u16 getTrigger();
extern int getJoystick_X();
extern int getJoystick_Y();

#ifdef __cplusplus
}
#endif

#endif
