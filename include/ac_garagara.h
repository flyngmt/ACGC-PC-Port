#ifndef AC_GARAGARA_H
#define AC_GARAGARA_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aGRGR_JOINT_NUM 3

enum {
    aGRGR_MODE_NONE,
    aGRGR_MODE_FUKUBIKI,

    aGRGR_MODE_NUM
};

enum {
    aGRGR_BALL_FIRST_PLACE,
    aGRGR_BALL_SECOND_PLACE,
    aGRGR_BALL_THIRD_PLACE,
    aGRGR_BALL_NOT_WINNER,

    aGRGR_BALL_TYPE_NUM
};

typedef int (*aGRGR_GARAGARA_ANIME_START_PROC)(int);
typedef int (*aGRGR_DELETE_BALL_PROC)(void);

typedef struct garagara_clip_s {
    ACTOR* actorx;
    aGRGR_GARAGARA_ANIME_START_PROC garagara_anime_start_proc;
    aGRGR_DELETE_BALL_PROC delete_ball_proc;
} aGRGR_clip_c;

typedef struct garagara_ball_s {
    xyz_t pos;
    xyz_t old_pos;
    int ball_type;
    s16 status;
    f32 vel_y;
    f32 acc_y;
    f32 max_vel_y;
    f32 vel_xz;
    s16 angle;
    s16 remove_timer;
    xyz_t src_pos;
    s16 old_on_ground;
    s16 on_ground;
    s16 hit_wall;
    s16 hit_wall_angle;
} aGRGR_ball_c;

typedef struct garagara_actor_s GARAGARA_ACTOR;

struct garagara_actor_s {
    ACTOR actor_class;
    int mode;
    s16 status;
    int ball_type;
    int anime_frame;
#ifdef TARGET_PC
    f32 logic_accum;
#endif
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[aGRGR_JOINT_NUM];
    s_xyz morph[aGRGR_JOINT_NUM];
    N64Mtx mtx[2][aGRGR_JOINT_NUM];
    aGRGR_clip_c clip;
    u8* bank;
    int request_flag;
    s16 request_status;
    aGRGR_ball_c ball;
};

extern ACTOR_PROFILE Garagara_Profile;

#ifdef __cplusplus
}
#endif

#endif
