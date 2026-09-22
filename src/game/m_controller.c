#include "m_controller.h"
#include "game.h"
#include "m_lib.h"
#include "m_event.h"
#include "MSL_C/w_math.h"
#include "sys_math.h"

#ifdef MOUSE_INPUT
#include "m_play.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_skin_matrix.h"
#include "pc_mouse_input.h"
#endif

/**
 * @brief Constructor for MCON.
 **/
extern void mCon_ct() { }

/**
 * @brief Destructor for MCON.
 **/
extern void mCon_dt() { }

/**
 * @brief Controller input processing function.
 * Only processes port 1 controller.
 * 
 * @param mcon Pointer to MCON struct which will be updated
 * @param stick_x Joystick X position
 * @param stick_y Joystick Y position
 **/
extern void mCon_calc(MCON* mcon, f32 stick_x, f32 stick_y) {
  f32 t;

  mcon->last_move_pX = mcon->move_pX;
  mcon->last_move_pY = mcon->move_pY;
  mcon->last_move_pR = mcon->move_pR;
  mcon->last_move_angle = mcon->move_angle;

  mcon->last_adjusted_pX = mcon->adjusted_pX;
  mcon->last_adjusted_pY = mcon->adjusted_pY;
  mcon->last_adjusted_pR = mcon->adjusted_pR;

  t = sqrtf(stick_x * stick_x + stick_y * stick_y);

  if (t <= STICK_MIN) {
    mcon->move_pX = 0.0f;
    mcon->move_pY = 0.0f;
    mcon->move_pR = 0.0f;

    mcon->adjusted_pX = 0.0f;
    mcon->adjusted_pY = 0.0f;
    mcon->adjusted_pR = 0.0f;
  }
  else {
    s16 stick_angle = atans_table(stick_x, stick_y);
    if (t > STICK_MAX) {
      stick_x = cos_s(stick_angle) * STICK_MAX;
      stick_y = sin_s(stick_angle) * STICK_MAX;
      t = STICK_MAX;
    }

    mcon->move_angle = stick_angle;
    mcon->move_pX = check_percent_abs(stick_x, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
    mcon->move_pY = check_percent_abs(stick_y, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
    mcon->move_pR = check_percent_abs(      t, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);

    mcon->adjusted_pX = check_percent_abs(stick_x, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
    mcon->adjusted_pY = check_percent_abs(stick_y, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
    mcon->adjusted_pR = check_percent_abs(      t, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
  }
}

#ifdef MOUSE_INPUT
static int mCon_mouse_ground_offset(GAME_PLAY* play, xyz_t* position, xyz_t* offset) {
  MtxF* matrix = &play->projection_matrix;
  rect* screen = &play->view.screen;
  xyz_t projected;
  f32 mouse_x, mouse_y, w;
  f32 xx, xz, yx, yz, x, y, determinant;

  if (!pc_mouse_get_ui_position(&mouse_x, &mouse_y) ||
      screen->r <= screen->l || screen->bottom <= screen->top) {
    return FALSE;
  }

  mouse_x = 2.0f * (mouse_x - screen->l) / (screen->r - screen->l) - 1.0f;
  mouse_y = 1.0f - 2.0f * (mouse_y - screen->top) / (screen->bottom - screen->top);
  Skin_Matrix_PrjMulVector(matrix, position, &projected, &w);
  if (w <= 0.0f) {
    return FALSE;
  }

  /* Solve the projection for an X/Z offset on the plane at the player's feet. */
  xx = matrix->xx - mouse_x * matrix->wx;
  xz = matrix->xz - mouse_x * matrix->wz;
  yx = matrix->yx - mouse_y * matrix->wx;
  yz = matrix->yz - mouse_y * matrix->wz;
  x = mouse_x * w - projected.x;
  y = mouse_y * w - projected.y;
  determinant = xx * yz - xz * yx;
  if (fabsf(determinant) < 0.000001f) {
    return FALSE;
  }

  offset->x = (x * yz - xz * y) / determinant;
  offset->y = 0.0f;
  offset->z = (xx * y - x * yx) / determinant;
  return w + matrix->wx * offset->x + matrix->wz * offset->z > 0.0f;
}

static void mCon_mouse_move(GAME_PLAY* play, f32* stick_x, f32* stick_y) {
  static int active;
  PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
  xyz_t offset;
  f32 distance, strength;
  s16 angle;

  if (!(pc_mouse_button_held() & PC_MOUSE_BUTTON_LEFT) || !pc_mouse_pointer_visible() ||
      mEv_IsTitleDemo() || player == NULL || play->game_frame == 0 || play->pause.enabled ||
      play->fb_mode != FBDEMO_MODE_NONE || play->fb_wipe_mode != WIPE_MODE_NONE ||
      play->submenu.start_refuse || play->submenu.process_status != mSM_PROCESS_WAIT ||
      play->submenu.current_menu_type != mSM_OVL_NONE || play->submenu.menu_type != mSM_OVL_NONE ||
      !mMsg_CHECK_MAINHIDE() ||
      player->now_main_index < mPlayer_INDEX_WAIT || player->now_main_index > mPlayer_INDEX_DASH ||
      (player->requested_main_index_changed &&
       (player->requested_main_index < mPlayer_INDEX_WAIT || player->requested_main_index > mPlayer_INDEX_DASH)) ||
      getButton() || *stick_x * *stick_x + *stick_y * *stick_y > STICK_MIN * STICK_MIN) {
    active = FALSE;
    return;
  }

  if (pc_mouse_button_pressed() & PC_MOUSE_BUTTON_LEFT) {
    active = TRUE;
  }
  if (!active) {
    return;
  }

  *stick_x = *stick_y = 0.0f;
  if (!mCon_mouse_ground_offset(play, &player->actor_class.world.position, &offset)) {
    return;
  }
  distance = sqrtf(offset.x * offset.x + offset.z * offset.z);
  if (distance <= 4.0f) {
    return;
  }

  strength = (distance - 4.0f) / 40.0f;
  if (strength > 1.0f) {
    strength = 1.0f;
  }
  strength = STICK_MIN + strength * (STICK_MAX - STICK_MIN);
  angle = atans_table(offset.z, offset.x) - getCamera2AngleY(play) + DEG2SHORT_ANGLE2(90.0f);
  *stick_x = cos_s(angle) * strength;
  *stick_y = sin_s(angle) * strength;
}
#endif

/**
 * @brief Controller main process.
 * 
 * @param game Pointer to current GAME structure
 **/
extern void mCon_main(GAME* game) {
  f32 stick_x = getJoystick_X();
  f32 stick_y = getJoystick_Y();

#ifdef MOUSE_INPUT
  mCon_mouse_move((GAME_PLAY*)game, &stick_x, &stick_y);
#endif
  mCon_calc(&game->mcon, stick_x, stick_y);
}

/**
 * @brief Checks if a specific button combination currently pressed.
 * 
 * @param mask Button combination to check
 * @return TRUE when the button combination is pressed, FALSE otherwise
 **/
extern int chkButton(u16 mask) {
  if (mEv_IsTitleDemo()) {
    return FALSE;
  }

  return (mask & (gamePT->pads[0].now.button)) == mask;
}

/**
 * @brief Gets the currently pressed buttons.
 * 
 * @return Pressed buttons
 **/
extern u16 getButton() {
  if (mEv_IsTitleDemo()) {
    return BUTTON_NONE;
  }

  return gamePT->pads[0].now.button;
}

/**
 * @brief Checks if a specific button combination was pressed this frame.
 * 
 * @param mask Button combination to check
 * @return TRUE when the button combination was pressed this frame, FALSE otherwise
 **/
extern int chkTrigger(u16 mask) {
  if (mEv_IsTitleDemo()) {
    return FALSE;
  }

  return (mask & (gamePT->pads[0].on.button)) == mask;
}

/**
 * @brief Gets the buttons pressed on the current frame.
 * 
 * @return Buttons pressed on the current frame
 **/
extern u16 getTrigger() {
  if (mEv_IsTitleDemo()) {
    return BUTTON_NONE;
  }

  return gamePT->pads[0].on.button;
}

/**
 * @brief Gets the current joystick X position.
 * 
 * @return Joystick X position
 **/
extern int getJoystick_X() {
  if (mEv_IsTitleDemo()) {
    return 0;
  }

  return gamePT->pads[0].now.stick_x;
}

/**
 * @brief Gets the current joystick Y position.
 * 
 * @return Joystick Y position
 **/
extern int getJoystick_Y() {
  if (mEv_IsTitleDemo()) {
    return 0;
  }

  return gamePT->pads[0].now.stick_y;
}
