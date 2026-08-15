#ifndef AC_BEE_H
#define AC_BEE_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aBEE_JOINT_NUM 4

typedef struct bee_actor_s BEE_ACTOR;

struct bee_actor_s {
    ACTOR actor_class;
    mActor_proc action_proc;
    int action;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[aBEE_JOINT_NUM];
    s_xyz morph[aBEE_JOINT_NUM];
    N64Mtx mtx[2][aBEE_JOINT_NUM];
    xyz_t size;
    f32 speed;
    f32 start_frame;
    f32 pos_y;
    f32 alpha;
    s16 bobbing_counter;
    s16 add_angle;
    s16 fly_angle[2];
    s16 base_angle;
    f32 catch_delay_frames;
    ACTOR* insect_actor;
    f32 disappear_timer;
};

extern ACTOR_PROFILE Bee_Profile;

#ifdef __cplusplus
}
#endif

#endif
