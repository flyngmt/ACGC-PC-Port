#ifndef M_CAMERA2_H
#define M_CAMERA2_H

#include "types.h"
#include "m_lib.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    CAMERA2_PROCESS_STOP,
    CAMERA2_PROCESS_NORMAL,
    CAMERA2_PROCESS_WADE,
    CAMERA2_PROCESS_TALK,
    CAMERA2_PROCESS_DEMO,
    CAMERA2_PROCESS_ITEM,
    CAMERA2_PROCESS_LOCK,
    CAMERA2_PROCESS_DOOR,
    CAMERA2_PROCESS_SIMPLE,
    CAMERA2_PROCESS_CUST_TALK,
    CAMERA2_PROCESS_INTER,
    CAMERA2_PROCESS_STAFF_ROLL,
    CAMERA2_PROCESS_INTER2,

    CAMERA2_PROCESS_NUM
};

typedef struct camera_main_cust_talk_s {
    ACTOR* speaker_actor;
    ACTOR* listener_actor;
    f32 center_ratio;
    f32 cull_timer;
    s16 angle_x;
    s16 angle_y;
    f32 distance;
} CameraCustTalk;

typedef struct camera_main_demo_s {
    xyz_t starting_center_pos;
    f32 starting_distance;
    s_xyz starting_direction;

    xyz_t goal_center_pos;
    f32 goal_distance;
    s_xyz goal_direction;

    f32 goal_delta;
    f32 acceleration_delta;
    f32 braking_delta;
    f32 now_delta;
} CameraDemo;

typedef struct camera_main_door_s {
    u32 flags;
    float morph_counter;
    xyz_t center_position;
} CameraDoor;

typedef struct camera_main_inter_s {
    xyz_t starting_center_pos;
    xyz_t starting_eye_pos;

    xyz_t goal_center_pos;
    xyz_t goal_eye_pos;

    f32 slope0;
    f32 slope1;

    u32 flags;

    float now_delta;
    float max_delta;

    int pad[2];
} CameraInter;

typedef struct camera_main_item_s {
    int type;
    f32 cull_timer;
} CameraItem;

typedef struct camera_main_lock_s {
    xyz_t center_pos;
    xyz_t eye_pos;

    f32 fov_y;

    float morph_counter;

    f32 near;
    f32 far;
} CameraLock;

typedef struct camera_main_normal_s {
    u32 flags;

    int last_indoor_distance_addition_idx;
    int last_indoor_direction_addition_idx;

    float morph_counter;
} CameraNormal;

typedef struct camera_main_simple_s {
    xyz_t center_pos;
    s_xyz angle;
    f32 distance;

    float morph_counter;
    int mode;

    f32 cull_timer;
} CameraSimple;

typedef struct camera_main_staff_roll_s {
    xyz_t last_center_pos;
    xyz_t last_eye_pos;
    f32 last_distance;

    ACTOR* speaker_actor;
    ACTOR* listener_actor;

    float rotation_y_delta;
    float rotation_x_delta;
    float r_delta;

    float morph_counter;
    float dist_counter;
    u16 flags;
    s_xyz last_direction;
} CameraStaffRoll;

typedef struct camera_main_talk_s {
    ACTOR* speaker_actor;
    ACTOR* listener_actor;

    xyz_t listener_pos;

    f32 cull_timer;
    u32 flags;

    xyz_t goal_center_pos;
} CameraTalk;

typedef struct camera_main_wade_s {
    f32 timer;

    xyz_t start_pos;
    xyz_t goal_pos;

    f32 goal_time;
} CameraWade;

typedef union camera_main_data_u {
    CameraCustTalk cust_talk;
    CameraDemo demo;
    CameraDoor door;
    CameraInter inter;
    CameraItem item;
    CameraLock lock;
    CameraNormal normal;
    CameraSimple simple;
    CameraStaffRoll staff_roll;
    CameraTalk talk;
    CameraWade wade;

    u64 align;
} CameraMainData;

/* request index data */

typedef struct camera_request_cust_talk_s {
    ACTOR* speaker_actor;
    ACTOR* listener_actor;
    f32 center_ratio;
    s16 angle_x;
    s16 angle_y;
    f32 distance;
} CameraRequestCustTalk;

typedef struct camera_request_demo_s {
    xyz_t starting_center_pos;
    f32 starting_distance;
    s_xyz starting_direction;

    xyz_t goal_center_pos;
    f32 goal_distance;
    s_xyz goal_direction;

    f32 goal_delta;
    f32 acceleration_delta;
    f32 braking_delta;
} CameraRequestDemo;

typedef struct camera_request_door_s {
    ACTOR* door_actor;
    u32 flags;
} CameraRequestDoor;

typedef struct camera_request_inter_s {
    xyz_t starting_center_pos;
    xyz_t starting_eye_pos;

    xyz_t goal_center_pos;
    xyz_t goal_eye_pos;

    f32 slope0;
    f32 slope1;

    u32 flags;

    int morph_counter;

    int pad[2];
} CameraRequestInter;

typedef struct camera_request_item_s {
    int type;
} CameraRequestItem;

typedef struct camera_request_lock_s {
    xyz_t center_pos;
    xyz_t eye_pos;

    f32 fov_y;

    int morph_counter;

    f32 near;
    f32 far;
} CameraRequestLock;

typedef struct camera_request_normal_s {
    xyz_t position;

    int flags;
} CameraRequestNormal;

typedef struct camera_request_simple_s {
    xyz_t center_pos;
    s_xyz angle;
    f32 distance;

    int morph_counter;
    int mode;
} CameraRequestSimple;

typedef struct camera_request_staff_roll_s {
    ACTOR* speaker_actor;
    ACTOR* listener_actor;
} CameraRequestStaffRoll;

typedef struct camera_request_talk_s {
    ACTOR* speaker_actor;
    ACTOR* listener_actor;

    xyz_t listener_pos;

    u32 flags;
} CameraRequestTalk;

typedef struct camera_request_wade_s {
    xyz_t goal_pos;
    f32 goal_time;
} CameraRequestWade;

typedef union camera_request_data_u {
    CameraRequestCustTalk cust_talk;
    CameraRequestDemo demo;
    CameraRequestDoor door;
    CameraRequestInter inter;
    CameraRequestItem item;
    CameraRequestLock lock;
    CameraRequestNormal normal;
    CameraRequestSimple simple;
    CameraRequestStaffRoll staff_roll;
    CameraRequestTalk talk;
    CameraRequestWade wade;

    u64 align;
} CameraRequestData;

typedef struct camera_lookat_s {
    xyz_t eye;
    xyz_t center;
    xyz_t up;
} CameraLookat;

typedef struct camera_perspective_s {
    f32 fov_y;
    f32 aspect_ratio;
    f32 near;
    f32 far;
    f32 scale;
} CameraPerspective;

typedef struct camera_s {
    CameraLookat lookat;
    CameraPerspective perspective;

    s_xyz direction;          /* camera orientation */
    s_xyz direction_velocity; /* camera orentation rate of change */

    xyz_t movement_velocity; /* camera world position velocity */

    f32 focus_distance;          /* distance to the camera focal point/subject */
    f32 focus_distance_velocity; /* rate of change of the camera focus */

    int indoor_distance_addition_idx;  /* index of indoor distance adjustment LUT value to apply */
    int indoor_direction_addition_idx; /* index of indoor direction adjustment LUT value to apply */

    int now_main_index;                /* current main index type */
    int last_main_index;               /* previous main index type */
    int requested_main_index;          /* requested main index type */
    int requested_main_index_priority; /* requested main index priority value */
    int requested_main_index_flag;     /* TRUE/FALSE requested main index has been set */

    CameraMainData main_data;       /* current main index data */
    CameraRequestData request_data; /* requested index data */

    xyz_t mic_pos; /* mic position */
    u32 flags;     /* camera flags */

    xyz_t offset_eye;
    xyz_t offset_center;
} Camera2;

extern s16 getCamera2AngleY(GAME_PLAY* play);
extern int Camera2_change_priority(GAME_PLAY* play, int priority);
extern xyz_t* Camera2_getEyePos_p();
extern xyz_t* Camera2_getCenterPos_p();
extern int Camera2_CheckCullingMode();
extern int Camera2_CheckEnterCullingArea(f32 pos_x, f32 pos_z, f32 width);
extern void Camera2_ClearActorTalking_Cull(GAME_PLAY* play);
extern int Camera2_Check_main_index(GAME_PLAY* play, int main_index);
extern xyz_t* Camera2_getMicPos_p(GAME_PLAY* play);
extern int Camera2NormalState_get(GAME_PLAY* play);
extern int Camera2_request_main_wade(GAME_PLAY* play, xyz_t* pos, int priority, f32 goal_time);
extern int Camera2_request_main_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority);
extern int Camera2_request_main_talk_pos(GAME_PLAY* play, ACTOR* speaker, const xyz_t* const listener_pos, int priority);
extern int Camera2_request_main_normal(GAME_PLAY* play, int flags, int priority);
extern int Camera2_request_main_demo(GAME_PLAY* play, const xyz_t* start_center, const f32 start_dist,
                                     const s_xyz* start_dir, const xyz_t* goal_center, const f32 goal_dist,
                                     const s_xyz* goal_dir, const f32 goal_delta, const f32 accel_delta,
                                     const f32 braking_delta, const int priority);
extern int Camera2_request_main_demo_fromNowPos(GAME_PLAY* play, const xyz_t* goal_center, const s_xyz* goal_dir,
                                                const f32 goal_dist, const f32 goal_delta, const f32 accel_delta,
                                                const f32 braking_delta, const int priority);
extern int Camera2_request_main_demo_fromNowPos2(GAME_PLAY* play, const xyz_t* goal_center, const f32 goal_delta,
                                                 const f32 accel_delta, const f32 braking_delta, const int priority);
extern int Camera2_request_main_item(GAME_PLAY* play, int type, int priority);
extern int Camera2_request_main_lock(GAME_PLAY* play, const xyz_t* center_pos, const xyz_t* eye_pos, f32 fov_y, int morph_counter,
                                     f32 near, f32 far, int priority);
extern int Camera2_request_main_door(GAME_PLAY* play, ACTOR* door_actor, u32 flags, int priority);
extern int Camera2_request_main_simple2(GAME_PLAY* play, const xyz_t* center, const s_xyz* dir, f32 dist, int morph_counter,
                                        int mode, int priority);
extern int Camera2_request_main_simple_kirin(GAME_PLAY* play, const xyz_t* center, int priority);
extern int Camera2_request_main_simple_fishing(GAME_PLAY* play, const xyz_t* player_pos, const xyz_t* bobber_pos,
                                               int priority);
extern int Camera2_request_main_simple_fishing_return(GAME_PLAY* play, const xyz_t* player_pos, int priority);
extern int Camera2_request_main_simple(GAME_PLAY* play, const xyz_t* pos, const s_xyz* dir, f32 dist, int morph_counter,
                                       int priority);
extern void Camera2_main_Simple_AngleDistStd(GAME_PLAY* play, s_xyz* angle, f32* dist);
extern int Camera2_request_main_listen_front_low_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority);
extern int Camera2_request_main_needlework_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority);
extern int Camera2_request_main_cust_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, f32 center_ratio,
                                          int priority, s16 angle_x, s16 angle_y, f32 distance);
extern int Camera2_request_BuySikimono_WallPaper(GAME_PLAY* play, xyz_t* center, xyz_t* eye);
extern int Camera2_Inter_set_reverse_mode(GAME_PLAY* play);
extern int Camera2_request_main_inter(GAME_PLAY* play, const xyz_t* start_center, const xyz_t* start_eye, const xyz_t* goal_center,
                                      const xyz_t* goal_eye, f32 s0, f32 s1, u32 flags, int morph_counter, int priority);
extern int Camera2_request_main_staff_roll(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority);
extern void Init_Camera2(GAME_PLAY* play);
extern void Camera2_process(GAME_PLAY* play);
extern void Camera2_draw(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
