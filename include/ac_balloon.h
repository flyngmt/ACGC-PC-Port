#ifndef AC_BALLOON_H
#define AC_BALLOON_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    Ac_Balloon_TYPE0,
    Ac_Balloon_TYPE1,
    Ac_Balloon_TYPE2,
    Ac_Balloon_TYPE3,
    Ac_Balloon_TYPE4,
    Ac_Balloon_TYPE5,
    Ac_Balloon_TYPE6,
    Ac_Balloon_TYPE7,

    Ac_Balloon_TYPE_NUM
};

#define Ac_Balloon_TYPE_VALID(n) ((n) >= 0 && (n) < Ac_Balloon_TYPE_NUM)

#define Ac_Balloon_JOINT_NUM 8

typedef struct balloon_actor_s BALLOON_ACTOR;

struct balloon_actor_s {
    ACTOR actor_class;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[Ac_Balloon_JOINT_NUM];
    s_xyz morph[Ac_Balloon_JOINT_NUM];
    int _244;
    N64Mtx mtx[2][4];
    int main_mode;
    int saved_type;
    int setup_mode;
    int balloon_type;
    s_xyz angle;
    s16 lean;
    f32 start_frame;
    f32 speed;
    xyz_t pos;
    int _474;
};

extern void Ac_Balloon_request_hide(ACTOR* actorx, GAME* game);
extern void Ac_Balloon_request_fly(ACTOR* actorx, GAME* game, int balloon_type, const s_xyz* angle_p, s16 lean,
                                   const xyz_t* pos_p, f32 start_frame, f32 speed);

extern ACTOR_PROFILE Balloon_Profile;

#ifdef __cplusplus
}
#endif

#endif
