#ifndef AC_FUUSEN_H
#define AC_FUUSEN_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aFSN_ESCAPE_TIMER 1554

enum {
  aFSN_ACTION_BIRTH,
  aFSN_ACTION_MOVING,
  aFSN_ACTION_WOOD_STOP,
  aFSN_ACTION_ESCAPE,

  aFSN_ACTION_NUM
};

typedef struct fuusen_actor_s FUUSEN_ACTOR;

struct fuusen_actor_s {
  ACTOR actor_class;
  int action;
  mActor_proc action_proc;
  char* segment_p;
  int type_idx;
  f32 escape_timer;
  f32 timer;
  int count;
  int look_up_flag;
  int wind_idx;
  s16 fuwafuwa_cycle;
  f32 wind_power;
  f32 y_offset;
  u8 wind_change_flag;
  cKF_SkeletonInfo_R_c keyframe;
  s_xyz work[5];
  s_xyz morph[5];
  int _254;
  N64Mtx mtx[2][3];
};

extern ACTOR_PROFILE Fuusen_Profile;

#ifdef __cplusplus
}
#endif

#endif

