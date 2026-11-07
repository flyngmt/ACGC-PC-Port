#ifndef AC_BOAT_H
#define AC_BOAT_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct boat_s BOAT_ACTOR;

typedef void (*aBT_PROC)(BOAT_ACTOR*, GAME_PLAY*);

struct boat_s {
  ACTOR actor_class;
  int _174;
  cKF_SkeletonInfo_R_c keyframe;
  int _1E8;
  s_xyz work[15];
  s_xyz morph[15];
  aBT_PROC action_proc;
  f32 roll_timer_accum;
  f32 roll_cycle_accum;
  f32 logic_accum;
  int action;
  int roll_cycle;
  int roll_timer;
  int point;
  int direction;
  f32 furrow_scroll;
  f32 wave_angl0;
  f32 wave_angl1;
  f32 rudder;
  xyz_t sim_pos;
  xyz_t prev_pos;
  s16 sim_angle;
  s16 prev_angle;
};

extern ACTOR_PROFILE Boat_Profile;

#ifdef __cplusplus
}
#endif

#endif

