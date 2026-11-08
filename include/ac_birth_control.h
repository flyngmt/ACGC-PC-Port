#ifndef AC_BIRTH_CONTROL_H
#define AC_BIRTH_CONTROL_H

#include "types.h"
#include "m_actor.h"
#include "m_field_make.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct birth_control_s BIRTH_CONTROL_ACTOR;

struct birth_control_s {
  ACTOR actor_class;
  int setup_actor_flag;
  mFM_move_actor_c* move_actor_data;
  u16 move_actor_bitfield;
  s16 move_actor_list_exists_flag;
  int boat_spawned;
  int last_quadrant;
  mFM_move_actor_c move_actor_list[mFM_MOVE_ACTOR_NUM];
  s8 nearby_block[mFM_VISIBLE_BLOCK_NUM - 1][2];
  u16 nearby_retry_bitfield[mFM_VISIBLE_BLOCK_NUM - 1];
};

extern ACTOR_PROFILE Birth_Control_Profile;

void aBC_RequestNearbyRefresh(void);

#ifdef __cplusplus
}
#endif

#endif

