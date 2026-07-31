#ifndef M_BANTI_H
#define M_BANTI_H

#include "types.h"
#include "m_play_h.h"
#include "c_keyframe.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define banti_JOINT_MAX 5

enum {
  banti_ANIM_STATE_STOPPED,
  banti_ANIM_STATE_PLAYING,

  banti_ANIM_STATE_NUM
};

typedef struct banti_anim_s {
  cKF_SkeletonInfo_R_c keyframe;
  s_xyz work[banti_JOINT_MAX];
  s_xyz morph[banti_JOINT_MAX];
  int state;
} Banti_anim_c;

typedef struct banti_callback_s {
  Gfx** gfx_pp;
  N64Mtx* mtx;
  int state;
} Banti_callback_c;

typedef struct banti_s {
  int addressable_type;
  int disabled;
  f32 timer;
  f32 alpha;
  int disp_left;
  int move_left;
  f32 move_timer;

  Banti_anim_c month_anim;
  Banti_anim_c day_anim;
  Banti_anim_c hour_upper_anim;
  Banti_anim_c hour_lower_anim;
  Banti_anim_c min_upper_anim;
  Banti_anim_c min_lower_anim;

  lbRTC_time_c displayed_time;
  lbRTC_time_c next_time; /* displayed during transition animation for any animations */
} Banti_c;

extern void banti_ct();
extern void banti_dt();
extern void banti_move(GAME_PLAY* play);
extern void banti_draw(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
