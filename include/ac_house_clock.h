#ifndef AC_HOUSE_CLOCK_H
#define AC_HOUSE_CLOCK_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aHC_JOINT_NUM 5 // body
#define aHC_ALL_JOINT_NUM aHC_JOINT_NUM + 2 // body + hands

enum {
    aHC_TYPE_SHOP1,
    aHC_TYPE_SHOP2,
    aHC_TYPE_SHOP3,
    aHC_TYPE_SHOP4,
    aHC_TYPE_SHOP4_2,
    aHC_TYPE_POST_OFFICE,
    aHC_TYPE_POLICE_BOX,
    aHC_TYPE_MUSEUM,
    aHC_TYPE_TAILORS,

    aHC_TYPE_NUM
};

typedef struct house_clock_s {
    s16 clock_num;
    xyz_t pos;
    u8* bank;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[aHC_JOINT_NUM];
    s_xyz morph[aHC_JOINT_NUM];
    N64Mtx mtx[2][aHC_ALL_JOINT_NUM];
} aHC_clock_c;

typedef struct house_clock_actor_s HOUSE_CLOCK_ACTOR;

struct house_clock_actor_s {
    ACTOR actor_class;
    aHC_clock_c clock;
    f32 phase_frame;
};

extern ACTOR_PROFILE House_Clock_Profile;

#ifdef __cplusplus
}
#endif

#endif
