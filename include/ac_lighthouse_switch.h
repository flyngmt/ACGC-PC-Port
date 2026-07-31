#ifndef AC_LIGHTHOUSE_SWITCH_H
#define AC_LIGHTHOUSE_SWITCH_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aLS_SWITCH_JOINT_NUM 1

enum {
    aLS_NICE_STATUS_OFF,
    aLS_NICE_STATUS_SWITCH_ON,
    aLS_NICE_STATUS_LIGHTHOUSE_PERIOD,

    aLS_NICE_STATUS_NUM
};

typedef struct lighthouse_switch_s {
    xyz_t pos;
    s16 state;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[aLS_SWITCH_JOINT_NUM+1];
    s_xyz morph[aLS_SWITCH_JOINT_NUM+1];
    N64Mtx mtx[2][aLS_SWITCH_JOINT_NUM+1];
} aLS_switch_c;

#define aLS_POLE_JOINT_NUM 10
#define aLS_POLE_ALL_JOINT_NUM 13

typedef struct lighthouse_pole_s {
    xyz_t pos;
    f32 speed;
    s16 state;
    f32 timer;
    f32 off_timer;
    int keyframe_state;
    int _1C;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[aLS_POLE_JOINT_NUM+1];
    s_xyz morph[aLS_POLE_JOINT_NUM+1];
    N64Mtx mtx[2][aLS_POLE_ALL_JOINT_NUM+1];
} aLS_pole_c;

typedef struct lighthouse_switch_actor_s LIGHTHOUSE_SWITCH_ACTOR;

struct lighthouse_switch_actor_s {
    ACTOR actor_class;
    aLS_switch_c ls_switch;
    aLS_pole_c ls_pole;
    s16 turning_on;
};

extern ACTOR_PROFILE Lighthouse_Switch_Profile;

#ifdef __cplusplus
}
#endif

#endif
