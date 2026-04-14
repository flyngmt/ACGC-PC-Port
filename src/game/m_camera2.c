#include "m_camera2.h"

#include "m_play.h"
#include "sys_math3d.h"
#include "MSL_C/math.h"
#include "c_keyframe.h"
#include "m_player_lib.h"
#include "m_room_type.h"
#include "m_collision_bg.h"
#include "m_scene_table.h"
#include "m_common_data.h"

#if VERSION >= VER_GAFU01_00
#define CAMERA2_STAFFROLL_CENTER_X_ROT_STEP_DIVISOR 3333
#define CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR 2166
#else
#define CAMERA2_STAFFROLL_CENTER_X_ROT_STEP_DIVISOR 4000
#define CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR 2600
#endif

static void Camera2_main_Normal_AdjustDistanceAndDirection(GAME_PLAY* play, f32* dist, s_xyz* dir);
static void Camera2_change_main_index(GAME_PLAY* play);

static void Camera2_DirectionCalc(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    xyz_t eye_minus_center;
    s_xyz dir;
    f32 mag;

    xyz_t_sub(&camera->lookat.eye, &camera->lookat.center, &eye_minus_center);
    dir = camera->direction;
    mag = Math3d_normalizeXyz_t(&eye_minus_center);

    if (F32_IS_ZERO(mag)) {
        camera->direction.x = 0;
        camera->direction.y = 0;
        camera->direction.z = 0;
    } else {
        camera->direction.x = RAD2SHORTANGLE(facos(eye_minus_center.y)) + (u16)SHT_MIN_S;
        camera->direction.y = atans_table(eye_minus_center.z, eye_minus_center.x) + (u16)SHT_MIN_S;
        camera->direction.z = 0;
    }

    camera->direction_velocity.x = camera->direction.x - dir.x;
    camera->direction_velocity.y = camera->direction.y - dir.y;
    camera->direction_velocity.z = camera->direction.z - dir.z;
}

static int Camera2_InDoorCheck() {
    mActor_name_t field_id = mFI_GetFieldId();
    int res = FALSE;

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0 || mFI_GET_TYPE(field_id) == mFI_FIELD_ROOM0 ||
        mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
        res = TRUE;
    }

    return res;
}

static int Camera2_CheckInDoorNearFar(GAME_PLAY* play) {
    if (play->camera.indoor_distance_addition_idx == 0 ||
        (Save_Get(scene_no) == SCENE_BROKER_SHOP && play->camera.now_main_index == CAMERA2_PROCESS_TALK)) {
        return TRUE;
    }

    return FALSE;
}

static f32 Camera2_GetUnderBorderAdjust() {
    if (Camera2_InDoorCheck()) {
        return 0.0f;
    } else {
        return -15.0f;
    }
}

static void Camera2_PolaPosCalc(xyz_t* eye, s16 inv_dir_x, s16 inv_dir_y, const xyz_t* center, f32 dist) {
    f32 dist_xz;
    f32 angle_x;
    f32 angle_y;

    angle_x = SHORTANGLE2RAD(inv_dir_x);
    angle_y = SHORTANGLE2RAD(inv_dir_y);

    *eye = *center;
    eye->y += dist * sinf(angle_x);
    dist_xz = dist * cosf(angle_x);
    eye->x += dist_xz * sinf(angle_y);
    eye->z += dist_xz * cosf(angle_y);
}

static void Camera2_SetEyePos_fromCenterPosCalc(GAME_PLAY* play, xyz_t* center, xyz_t* eye) {
    Camera2_PolaPosCalc(eye, play->camera.direction.x + (u16)SHT_MIN_S, play->camera.direction.y + (u16)SHT_MIN_S,
                        center, play->camera.focus_distance);
}

static void Camera2_SetEyePos_fromCenterPos(GAME_PLAY* play) {
    Camera2* camera = &play->camera;

    Camera2_SetEyePos_fromCenterPosCalc(play, &camera->lookat.center, &camera->lookat.eye);
}

static void Camera2_MoveDirectionAngleXYZ_morph(GAME_PLAY* play, const s_xyz* goal_dir, float delta) {
    s_xyz* dir;
    s_xyz* dir_vel;
    Camera2* camera = &play->camera;

    dir = &camera->direction;
    dir_vel = &camera->direction_velocity;

    if (delta == 0) {
        dir->x = goal_dir->x;
        dir->y = goal_dir->y;
        dir->z = goal_dir->z;

        dir_vel->x = 0;
        dir_vel->y = 0;
        dir_vel->z = 0;
    } else {
        f32 t = 1.0f / delta;
        s_xyz last_dir;
        last_dir.x = dir->x;
        last_dir.y = dir->y;
        last_dir.z = dir->z;

        cKF_SkeletonInfo_subRotInterpolation(t, &dir->x, last_dir.x, goal_dir->x); // order is wrong here
        cKF_SkeletonInfo_subRotInterpolation(t, &dir->y, last_dir.y, goal_dir->y);
        cKF_SkeletonInfo_subRotInterpolation(t, &dir->z, last_dir.z, goal_dir->z);

        dir_vel->x = dir->x - last_dir.x;
        dir_vel->y = dir->y - last_dir.y;
        dir_vel->z = dir->z - last_dir.z;
    }
}

static void Camera2_MoveDirectionAngleXYZ(GAME_PLAY* play, const s_xyz* goal_dir, int delta) {
    Camera2* camera = &play->camera;
    s_xyz* dir = &camera->direction;
    s_xyz* dir_vel = &camera->direction_velocity;

    if (delta != 0) {
        dir->x = goal_dir->x;
        dir->y = goal_dir->y;
        dir->z = goal_dir->z;

        dir_vel->x = 0;
        dir_vel->y = 0;
        dir_vel->z = 0;
    } else {
        s_xyz last_dir;
        s16 x = dir->x;
        s16 y = dir->y;
        s16 z = dir->z;

        add_calc_short_angle2(&dir->x, goal_dir->x, 0.051316679f, 11000, 100);
        add_calc_short_angle2(&dir->y, goal_dir->y, 0.051316679f, 11000, 75);
        add_calc_short_angle2(&dir->z, goal_dir->z, 0.051316679f, 11000, 150);

        dir_vel->x = dir->x - x;
        dir_vel->y = dir->y - y;
        dir_vel->z = dir->z - z;
    }
}

static void Camera2_SetDirectionAngleXYZ(GAME_PLAY* play, const s_xyz* goal_dir, int delta) {
    Camera2* camera = &play->camera;
    s_xyz* dir = &camera->direction;
    s_xyz* dir_vel = &camera->direction_velocity;

    if (delta != 0) {
        *dir_vel = ZeroSVec;
    } else {
        dir_vel->x = goal_dir->x - dir->x;
        dir_vel->y = goal_dir->y - dir->y;
        dir_vel->z = goal_dir->z - dir->z;
    }

    *dir = *goal_dir;
}

static void Camera2_SetView(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    xyz_t* eye;
    View* view;
    xyz_t* center;
    xyz_t final_center;
    xyz_t final_eye;

    eye = &camera->lookat.eye;
    view = &play->view;
    center = &camera->lookat.center;

    if (F32_IS_ZERO(Math3DLength(eye, center))) {
        eye->z = center->z + 1.0f;
    }

    if (Camera2_CheckInDoorNearFar(play)) {
        camera->perspective.near = 20.0f;
        camera->perspective.far = 1600.0f;
    } else {
        if (camera->now_main_index != CAMERA2_PROCESS_LOCK) {
            f32 dist_from_player = Math3DLength(eye, &get_player_actor_withoutCheck(play)->actor_class.world.position);

            if (dist_from_player < 540.0f) {
                chase_f(&camera->perspective.near, 145.0f, 4.0f);
            } else {
                chase_f(&camera->perspective.near, 200.0f, 4.0f);
            }

            camera->perspective.far = 1600.0f;
        }
    }

    if (F32_IS_ZERO(camera->perspective.fov_y)) {
        camera->perspective.fov_y += 1.0f;
    }

    setScaleView(view, camera->perspective.scale);
    setPerspectiveView(view, camera->perspective.fov_y, camera->perspective.near, camera->perspective.far);
    xyz_t_add(center, &camera->offset_center, &final_center);
    xyz_t_add(eye, &camera->offset_eye, &final_eye);
    setLookAtView(view, &final_eye, &final_center, &camera->lookat.up);
}

static f32 Camera2_BorderSize() {
    int type = mFI_GET_TYPE(mFI_GetFieldId());
    f32 size = 110.0f;

    switch (type) {
        case mFI_FIELD_NPCROOM0:
            size = 110.0f;
            break;
        case mFI_FIELD_ROOM0:
            size = 110.0f;
            break;
        case mFI_FIELD_PLAYER0_ROOM:
            size = 110.0f;
            break;
    }

    return size;
}

static void Camera2_GetBorderScale(GAME_PLAY* play, f32 scale, f32* x_min, f32* x_max, f32* z_min, f32* z_max) {
    static xyz_t local_border_base_pos = { 0.0f, 0.0f, 0.0f };

    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    xyz_t entrance_pos;
    int block_x;
    int block_z;

    if (mRmTp_GetEntranceBasePosition(&entrance_pos) == FALSE) {
        mFI_Wpos2BlockNum(&block_x, &block_z, player->actor_class.world.position);
        mFI_LposInBKtoWpos(&entrance_pos, local_border_base_pos, block_x, block_z);
    }

    *x_min = entrance_pos.x + mFI_GetBlockWidth() - (scale * Camera2_BorderSize(play));
    *x_max = entrance_pos.x + (scale * Camera2_BorderSize(play));
    *z_max =
        mFI_GetBlockHeight() + (entrance_pos.z - (scale * (Camera2_BorderSize(play) + Camera2_GetUnderBorderAdjust())));
    *z_min = entrance_pos.z + (scale * (Camera2_BorderSize(play) + mFI_UT_WORLDSIZE_Z_F));

    if (Camera2_InDoorCheck()) {
        *z_min += -mFI_UT_WORLDSIZE_Z_F;
    }
}

static void Camera2_GetLongBorderScale(GAME_PLAY* play, f32* scale) {
    if (play->camera.flags & 1) {
        *scale = 1.5f;
    } else {
        *scale = 1.0f;
    }
}

static void Camera2_GetBorder(GAME_PLAY* play, f32* x0, f32* x1, f32* z0, f32* z1) {
    f32 scale;

    Camera2_GetLongBorderScale(play, &scale);
    Camera2_GetBorderScale(play, scale, x0, x1, z0, z1);
}

static void Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(GAME_PLAY* play, const xyz_t* end_center_pos, int force) {
    Camera2* camera = &play->camera;
    xyz_t* move_vel = &camera->movement_velocity;
    xyz_t* center = &camera->lookat.center;

    if (force) {
        xyz_t_move(move_vel, &ZeroVec);
        xyz_t_move(center, end_center_pos);
    } else {
        xyz_t now_center = *center;

        add_calc(&center->x, end_center_pos->x, 0.13397461f, 8.75f, 0.25f);
        add_calc(&center->y, end_center_pos->y, 0.13397461f, 8.75f, 0.25f);
        add_calc(&center->z, end_center_pos->z, 0.13397461f, 8.75f, 0.25f);

        xyz_t_sub(center, &now_center, move_vel); // set velocity
    }
}

static void Camera2_SetCenterPosAndSpeed(GAME_PLAY* play, xyz_t* end_center_pos, int force) {
    Camera2* camera = &play->camera;
    xyz_t* move_vel = &camera->movement_velocity;
    xyz_t* center = &camera->lookat.center;

    if (force) {
        xyz_t_move(move_vel, &ZeroVec);
    } else {
        xyz_t_sub(end_center_pos, center, move_vel);
    }

    xyz_t_move(center, end_center_pos);
}

static void Camera2_SetDistancePosAndSpeed(GAME_PLAY* play, f32 end_distance, int force) {
    Camera2* camera = &play->camera;
    f32* distance = &camera->focus_distance;
    f32* distance_vel = &camera->focus_distance_velocity;

    if (force) {
        *distance_vel = 0.0f;
    } else {
        *distance_vel = end_distance - *distance;
    }

    *distance = end_distance;
}

static f32 Camera2_MoveDistancePosAndSpeed(GAME_PLAY* play, f32 end_distance, int force) {
    Camera2* camera = &play->camera;
    f32* distance = &camera->focus_distance;
    f32* distance_vel = &camera->focus_distance_velocity;
    f32 ret = 0.0f;

    if (force) {
        *distance = end_distance;
        *distance_vel = 0.0f;
    } else {
        f32 pre_dist = *distance;

        ret = add_calc(distance, end_distance, 0.13397461f, 8.75f, 0.25f);
        *distance_vel = *distance - pre_dist;
    }

    return ret;
}

static void Camera2_Get_PosBlockRatio(GAME_PLAY* play, xyz_t* pos, f32* x_ratio, f32* z_ratio) {
    f32 x0;
    f32 x1;
    f32 z1;
    f32 z0;

    f32 x_center;
    f32 z_center;

    f32 x_r;
    f32 z_l;

    *z_ratio = 0.0f;
    *x_ratio = 0.0f;

    Camera2_GetBorder(play, &x0, &x1, &z0, &z1);

    x_center = (x0 + x1) * 0.5f;
    x_r = x_center - x1;

    z_center = (z0 + z1) * 0.5f;
    z_l = z_center - z0;

    if (!F32_IS_ZERO(x_r)) {
        *x_ratio = (pos->x - x_center) / x_r;
    } else {
        *x_ratio = 0.0f;
    }

    if (*x_ratio > 1.0f) {
        *x_ratio = 1.0f;
    }

    if (*x_ratio < -1.0f) {
        *x_ratio = -1.0f;
    }

    if (!F32_IS_ZERO(z_l)) {
        *z_ratio = (pos->z - z_center) / z_l;
    } else {
        *z_ratio = 0.0f;
    }

    if (*z_ratio > 1.0f) {
        *z_ratio = 1.0f;
    }

    if (*z_ratio < -1.0f) {
        *z_ratio = -1.0f;
    }
}

static void Camera2_Normal_Swing(GAME_PLAY* play, f32* distance, s_xyz* dir) {
    xyz_t* pos = &get_player_actor_withoutCheck(play)->actor_class.eye.position;
    f32 x_ratio;
    f32 z_ratio;
    int block_x;
    int block_z;

    Camera2_Get_PosBlockRatio(play, pos, &x_ratio, &z_ratio);
    mFI_Wpos2BlockNum(&block_x, &block_z, *pos);

    if (block_z == 1 && z_ratio < 0.0f) {
        dir->x += (s16)(z_ratio * 250.0f);
    }
}

static const f32 add_distance_array[3] = { -280.0f, 0.0f, 300.0f };

static const s16 add_directionY_array[3] = {
    DEG2SHORT_ANGLE(-16.1f), // -2930
    DEG2SHORT_ANGLE(0.0f),   // 0
    DEG2SHORT_ANGLE(16.1f),  // 2930
};

static const s16 add_directionX_array[3] = {
    DEG2SHORT_ANGLE(-23.24f), // -4230
    DEG2SHORT_ANGLE(0.0f),    // 0
    DEG2SHORT_ANGLE(19.12f)   // 3480
};

static void Camera2_Get_GoalDistanceAndDirection(GAME_PLAY* play, f32* dist, s_xyz* dir) {
    static const f32 distance_array[CAMERA2_PROCESS_NUM] = {
        620.0f, /* CAMERA2_PROCESS_STOP */
        620.0f, /* CAMERA2_PROCESS_NORMAL */
        620.0f, /* CAMERA2_PROCESS_WADE */
        290.0f, /* CAMERA2_PROCESS_TALK */
        620.0f, /* CAMERA2_PROCESS_DEMO */
        620.0f, /* CAMERA2_PROCESS_ITEM */
        620.0f, /* CAMERA2_PROCESS_LOCK */
        620.0f, /* CAMERA2_PROCESS_DOOR */
        620.0f, /* CAMERA2_PROCESS_SIMPLE */
        290.0f, /* CAMERA2_PROCESS_CUST_TALK */
        620.0f, /* CAMERA2_PROCESS_INTER */
        620.0f, /* CAMERA2_PROCESS_STAFF_ROLL */
        620.0f  /* CAMERA2_PROCESS_INTER2 */
    };

    static const s_xyz direction_array[CAMERA2_PROCESS_NUM] = {
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-164.114f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-165.2125f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) },
    };

    Camera2* camera = &play->camera;
    int main_index = camera->now_main_index;
    int add_dist_idx = camera->indoor_distance_addition_idx;
    int add_dir_idx = camera->indoor_direction_addition_idx;

    if (main_index < 0 || main_index >= CAMERA2_PROCESS_NUM) {
        main_index = 0;
    }

    *dist = distance_array[main_index];
    *dir = direction_array[main_index];

    if (main_index == CAMERA2_PROCESS_NORMAL && Camera2_InDoorCheck()) {
        if (add_dist_idx < 0 || add_dist_idx >= 3) {
            add_dist_idx = 1;
        }

        if (add_dir_idx < 0 || add_dir_idx >= 3) {
            add_dir_idx = 1;
        }

        *dist += add_distance_array[add_dist_idx];
        dir->y += add_directionY_array[add_dir_idx];
        dir->x += add_directionX_array[add_dist_idx]; // adjust by add_dist_idx since rotation on X axis should be
                                                      // defined by distance of camera
    }

    if (main_index == CAMERA2_PROCESS_NORMAL || main_index == CAMERA2_PROCESS_WADE) {
        if (Camera2_InDoorCheck() == FALSE && (camera->flags & 1) == 0) {
            Camera2_Normal_Swing(play, dist, dir);
        }
    }

    Camera2_main_Normal_AdjustDistanceAndDirection(play, dist, dir);
}

static void Camera2_SetPos_fromStartEnd(GAME_PLAY* play, const xyz_t* start, const xyz_t* end, f32 now_time,
                                        f32 end_time) {
    Camera2* camera = &play->camera;
    f32 percent = get_percent_forAccelBrake(now_time, 0.0f, end_time, 1.1999999f, 34.8f);
    xyz_t center = camera->lookat.center;
    xyz_t* center_p = &camera->lookat.center;
    xyz_t* move_vel_p = &camera->movement_velocity;
    xyz_t goal;
    f32 dist;
    s_xyz dir;

    if (percent >= 1.0f) {
        goal = *end;
    } else {
        f32 x = start->x;
        f32 y = start->y;
        f32 z = start->z;

        x = start->x + percent * (end->x - x);
        y = start->y + percent * (end->y - y);
        z = start->z + percent * (end->z - z);

        goal.x = x;
        goal.y = y;
        goal.z = z;
    }

    *center_p = goal;
    xyz_t_sub(&goal, &center, move_vel_p);
    Camera2_Get_GoalDistanceAndDirection(play, &dist, &dir);
    Camera2_MoveDistancePosAndSpeed(play, dist, FALSE);
    Camera2_MoveDirectionAngleXYZ_morph(play, &dir, end_time - now_time);
    Camera2_SetEyePos_fromCenterPos(play);
    Camera2_SetView(play);
}

static void Camera2_setup_main_Base(GAME_PLAY* play) {
    play->camera.last_main_index = play->camera.now_main_index;
    play->camera.now_main_index = play->camera.requested_main_index;
    play->camera.requested_main_index_flag = FALSE;
}

extern s16 getCamera2AngleY(GAME_PLAY* play) {
    return play->camera.direction.y;
}

static int Camera2_check_request_main_priority(GAME_PLAY* play, int priority) {
    return priority - play->camera.requested_main_index_priority;
}

extern int Camera2_change_priority(GAME_PLAY* play, int priority) {
    play->camera.requested_main_index_priority = priority;
    return TRUE;
}

static void Camera2_request_main_index(GAME_PLAY* play, int main_index, int priority) {
    play->camera.requested_main_index = main_index;
    play->camera.requested_main_index_priority = priority;
    play->camera.requested_main_index_flag = TRUE;
}

static void Camera2_ChangeCameraPos_inBlock(GAME_PLAY* play, const xyz_t* pos, xyz_t* end_pos) {
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;

    f32 x00;
    f32 x01;
    f32 z00;
    f32 z01;

    f32 scale;

    Camera2_GetLongBorderScale(play, &scale);
    Camera2_GetBorder(play, &x0, &x1, &z1, &z0);
    Camera2_GetBorderScale(play, 1.0f, &x00, &x01, &z01, &z00);

    *end_pos = *pos;

    if (pos->x < x1) {
        if (pos->x < x1 - scale * Camera2_BorderSize(play)) {
            end_pos->x = x1 - (scale + 1.0f) * Camera2_BorderSize(play);
        } else if (end_pos->x < x01) {
            end_pos->x = x01;
        }
    } else if (pos->x > x0) {
        if (pos->x > x0 + scale * Camera2_BorderSize(play)) {
            end_pos->x = x0 + (scale + 1.0f) * Camera2_BorderSize(play);
        } else if (end_pos->x > x00) {
            end_pos->x = x00;
        }
    }

    if (pos->z < z1) {
        if (pos->z < z1 - scale * (Camera2_BorderSize(play) + mFI_UT_WORLDSIZE_Z_F)) {
            end_pos->z = (z1 - ((scale + 1.0f) * Camera2_BorderSize(play)) - (scale * mFI_UT_WORLDSIZE_Z_F)) -
                         Camera2_GetUnderBorderAdjust();
        } else if (end_pos->z < z01) {
            end_pos->z = z01;
        }
    } else if (pos->z > z0) {
        if (pos->z > scale * (Camera2_BorderSize(play) + Camera2_GetUnderBorderAdjust() + z0)) {
            end_pos->z = (z0 + (scale + 1.0f) * Camera2_BorderSize(play) + mFI_UT_WORLDSIZE_Z_F) +
                         scale * Camera2_GetUnderBorderAdjust();
        } else if (end_pos->z > z00) {
            end_pos->z = z00;
        }
    }
}

extern xyz_t* Camera2_getEyePos_p() {
    return &((GAME_PLAY*)gamePT)->camera.lookat.eye;
}

extern xyz_t* Camera2_getCenterPos_p() {
    return &((GAME_PLAY*)gamePT)->camera.lookat.center;
}

static void Camera2_SetCameraParameter(GAME_PLAY* play, xyz_t* center_pos, s_xyz* dir, int force, f32 dist) {
    Camera2_SetCenterPosAndSpeed(play, center_pos, force);
    Camera2_SetDistancePosAndSpeed(play, dist, force);
    Camera2_SetDirectionAngleXYZ(play, dir, force);
    Camera2_SetEyePos_fromCenterPos(play);
}

extern int Camera2_CheckCullingMode() {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    Camera2* camera = &play->camera;
    int main_index = camera->now_main_index;

    if (main_index == CAMERA2_PROCESS_TALK) {
        if (camera->main_data.talk.cull_timer >= 15.0f) {
            return TRUE;
        }
    } else if (main_index == CAMERA2_PROCESS_ITEM) {
        if (camera->main_data.item.cull_timer >= 6.0f) {
            return TRUE;
        }
    } else if (main_index == CAMERA2_PROCESS_DOOR) {
        if (camera->main_data.door.morph_counter < 70) {
            return TRUE;
        }
    } else if (main_index == CAMERA2_PROCESS_CUST_TALK) {
        if (camera->main_data.cust_talk.cull_timer >= 15.0f) {
            return TRUE;
        }
    } else if (main_index == CAMERA2_PROCESS_SIMPLE) {
        CameraSimple* simple = &camera->main_data.simple;

        if (simple->mode == 1 && simple->cull_timer >= 6.0f) {
            return TRUE;
        }
    }

    return FALSE;
}

static int pos_cull_check(const xyz_t* pos, const f32 pos_x, const f32 pos_z, f32 width, const f32 size_x,
                          const f32 size_z) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    f32 pos_left;
    f32 x;
    f32 eye_left;
    f32 eye_right;
    f32 pos_right;

    width += size_x;

    if ((play->camera.lookat.center.z + size_z) <= pos_z) {
        eye_left = play->camera.lookat.eye.x - width;
        eye_right = play->camera.lookat.eye.x + width;

        x = pos->x;
        pos_left = x - width;
        pos_right = x + width;

        if (pos_left > eye_left) {
            pos_left = eye_left;
        }

        if (pos_right < eye_right) {
            pos_right = eye_right;
        }

        if ((pos_left <= pos_x) && (pos_x <= pos_right)) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int Camera2_CheckEnterCullingArea(f32 pos_x, f32 pos_z, f32 width) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    Camera2* camera = &play->camera;
    int main_index = camera->now_main_index;
    f32 center_z = camera->lookat.center.z;

    if (main_index == CAMERA2_PROCESS_SIMPLE) {
        return pos_cull_check(&camera->main_data.simple.center_pos, pos_x, pos_z, width, 50.0f, -50.0f);
    } else {
        ACTOR* actor0;
        ACTOR* actor1;

        if (main_index == CAMERA2_PROCESS_TALK) {
            actor0 = camera->main_data.talk.speaker_actor;
            actor1 = camera->main_data.talk.listener_actor;
        } else {
            actor1 = &get_player_actor_withoutCheck(play)->actor_class;
            actor0 = actor1;
        }

        if (center_z <= pos_z && (actor0 != NULL || actor1 != NULL)) {
            f32 x0;
            f32 x1;
            f32 fx;
            f32 eye_left = camera->lookat.eye.x - width;
            f32 eye_right = camera->lookat.eye.x + width;

            f32 t0;
            f32 t1;

            if (actor0 == NULL) {
                x0 = actor1->world.position.x;
                x1 = x0;
            } else if (actor1 == NULL) {
                x1 = actor0->world.position.x;
                x0 = x1;
            } else {
                x0 = actor0->world.position.x;
                x1 = actor1->world.position.x;
            }

            if (main_index == CAMERA2_PROCESS_TALK) {
                CameraTalk* talk = &camera->main_data.talk;

                if (talk->flags & 2) {
                    x1 = talk->listener_pos.x;
                }
            }

            if (x0 > x1) {
                fx = x1;
            } else {
                fx = x0;
                x0 = x1;
            }

            fx -= width;
            x0 += width;

            if (fx > eye_left) {
                fx = eye_left;
            }

            if (x0 < eye_right) {
                x0 = eye_right;
            }

            if (fx <= pos_x && pos_x <= x0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern void Camera2_ClearActorTalking_Cull(GAME_PLAY* play) {
    Actor_list* actor_list;
    int i;

    actor_list = play->actor_info.list;
    for (i = 0; i < ACTOR_PART_NUM; i++) {
        ACTOR* actor;

        for (actor = actor_list->actor; actor != NULL; actor = actor->next_actor) {
            actor->cull_while_talking = FALSE;
        }

        actor_list++;
    }
}

static void Camera2_AddCullTimer(f32* cull_timer, f32 max, const f32 dt_frames) {
    *cull_timer += dt_frames;

    if (*cull_timer > max) {
        *cull_timer = max;
    }
}

extern int Camera2_Check_main_index(GAME_PLAY* play, int main_index) {
    return play->camera.now_main_index == main_index;
}

extern xyz_t* Camera2_getMicPos_p(GAME_PLAY* play) {
    return &play->camera.mic_pos;
}

static int Camera2_Check_MicPosFix() {
    static const s8 data[SCENE_NUM] = {
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  FALSE,
        FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        TRUE,  TRUE,  TRUE,  FALSE, TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE,
    };

    int scene = Save_Get(scene_no);
    if (scene < 0 || scene >= SCENE_NUM) {
        return TRUE;
    }

    return data[scene];
}

static void Camera2_SetMicPos(GAME_PLAY* play) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    if (player != NULL) {
        xyz_t* player_pos = &player->actor_class.world.position;
        Camera2* camera = &play->camera;
        xyz_t* lookat = &camera->lookat.center;
        xyz_t* eye = &camera->lookat.eye;
        f32 x;
        f32 t;
        s16 s;
        s16 s2;

        if (Camera2_Check_MicPosFix()) {
            xyz_t* mic_pos;
            f32 z;
            f32 x;

            z = cos_s(0) * 77.0f;
            x = sin_s(0) * 77.0f;
            mic_pos = Camera2_getMicPos_p(play);

            mic_pos->x = player_pos->x + x;
            mic_pos->y = player_pos->y + 240.0f;
            mic_pos->z = player_pos->z + z;
        } else {
            s_xyz* dir = &camera->direction;
            s16 dirX;
            f32 p;
            f32 x0;
            f32 cosX;
            f32 sinX;
            f32 abs_cosX;
            s16 dirY;
            f32 cosY;
            f32 sinY;
            xyz_t* mic_pos;

            x0 = (eye->y - player_pos->y) - 472.0f;
            t = (x0 * 0.796f) + 261.0f;
            dirX = dir->x;
            cosX = t * cos_s(dirX);
            sinX = t * sin_s(dirX);

            switch (Save_Get(scene_no)) {
                case SCENE_MY_ROOM_S:
                    p = 100.0f;
                    break;

                case SCENE_POLICE_BOX:
                case SCENE_MY_ROOM_L:
                case SCENE_CONVENI:
                case SCENE_SUPER:
                case SCENE_DEPART:
                case SCENE_DEPART_2:
                    p = 190.0f;
                    break;

                default:
                    p = 150.0f;
                    break;
            }

            p += x0 * -0.186f;
            abs_cosX = ABS(cosX) + p;
            dirY = dir->y;
            cosY = abs_cosX * cos_s(dirY);
            sinY = abs_cosX * sin_s(dirY);
            mic_pos = Camera2_getMicPos_p(play);

            mic_pos->x = eye->x + sinY;
            mic_pos->y = eye->y + sinX;
            mic_pos->z = eye->z + cosY;
        }
    }
}

extern int Camera2NormalState_get(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    const s16 inv_dir_y = camera->direction.y + 0x8000;
    const s16 dir_vel_y = camera->direction_velocity.y;
    const int scene = Save_Get(scene_no);
    int state = 0;

    if (scene == SCENE_MUSEUM_ROOM_INSECT || scene == SCENE_MUSEUM_ROOM_FISH) {
        if (camera->now_main_index == CAMERA2_PROCESS_NORMAL) {
            if (dir_vel_y == 0) {
                if (inv_dir_y == 0) {
                    state = 2;
                } else if (inv_dir_y > 0) {
                    state = 1;
                } else {
                    state = 3;
                }
            } else if (dir_vel_y < 0) {
                if (inv_dir_y <= 0) {
                    state = 7;
                } else {
                    state = 4;
                }
            } else if (inv_dir_y < 0) {
                state = 6;
            } else {
                state = 5;
            }
        }
    }

    return state;
}

static void Camera2_sound_Set_Ground(GAME_PLAY* play) {
}

static void Camera2_process_other_func2(GAME_PLAY* play) {
}

static void Camera2_setup_main_Stop(GAME_PLAY* play) {
}

static void Camera2_main_Stop(GAME_PLAY* play) {
}

extern int Camera2_request_main_wade(GAME_PLAY* play, xyz_t* pos, int priority, f32 goal_time) {
    Camera2* camera = &play->camera;
    xyz_t goal_pos;
    int res = FALSE;

    if (Camera2_check_request_main_priority(play, priority) > 0) {
        Camera2_ChangeCameraPos_inBlock(play, pos, &goal_pos);
        camera->request_data.wade.goal_pos = goal_pos;
        camera->request_data.wade.goal_time = goal_time;
        Camera2_request_main_index(play, CAMERA2_PROCESS_WADE, priority);

        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Wade(GAME_PLAY* play) {
    play->camera.main_data.wade.timer = 0.0f;
    play->camera.main_data.wade.start_pos = play->camera.lookat.center;
    play->camera.main_data.wade.goal_pos = play->camera.request_data.wade.goal_pos;
    play->camera.main_data.wade.goal_time = play->camera.request_data.wade.goal_time;

    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 9;
}

static void Camera2_SetPos_Wade(GAME_PLAY* play) {
    Camera2_SetPos_fromStartEnd(play, &play->camera.main_data.wade.start_pos, &play->camera.main_data.wade.goal_pos,
                                play->camera.main_data.wade.timer, play->camera.main_data.wade.goal_time);
}

static void Camera2_request_proc_index_fromWade(GAME_PLAY* play) {
    play->camera.main_data.wade.timer += play->game.graph->dt_num_60fps_frames;

    if (play->camera.main_data.wade.timer > play->camera.main_data.wade.goal_time) {
        play->camera.requested_main_index_priority = 0;
        Camera2_request_main_normal(play, 0, 5);
    }
}

static void Camera2_main_Wade(GAME_PLAY* play) {
    Camera2_SetPos_Wade(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_request_proc_index_fromWade(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_main_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.talk.speaker_actor = speaker;
        play->camera.request_data.talk.listener_actor = listener;

        if (listener != NULL) {
            xyz_t_move(&play->camera.request_data.talk.listener_pos, &listener->eye.position);
        } else {
            xyz_t_move(&play->camera.request_data.talk.listener_pos, &ZeroVec);
        }

        play->camera.request_data.talk.flags = 0;
        Camera2_request_main_index(play, CAMERA2_PROCESS_TALK, priority);
        return TRUE;
    }

    return FALSE;
}

extern int Camera2_request_main_talk_pos(GAME_PLAY* play, ACTOR* speaker, const xyz_t* const listener_pos,
                                         int priority) {
    Camera2* camera = &play->camera;

    if ((camera->now_main_index == CAMERA2_PROCESS_TALK || camera->requested_main_index == CAMERA2_PROCESS_TALK) &&
        (Math3DLength(&camera->request_data.talk.listener_pos, listener_pos) < 1.0f)) {
        return FALSE;
    } else {
        if (Camera2_check_request_main_priority(play, priority) > 0) {
            CameraRequestTalk* req_p = &camera->request_data.talk;

            req_p->speaker_actor = speaker;
            req_p->listener_actor = NULL;
            req_p->listener_pos = *listener_pos;
            req_p->flags = 1;
            Camera2_request_main_index(play, CAMERA2_PROCESS_TALK, priority);
            return TRUE;
        }
    }

    return FALSE;
}

static void Camera2_setup_main_Talk(GAME_PLAY* play) {
    play->camera.main_data.talk.speaker_actor = play->camera.request_data.talk.speaker_actor;
    play->camera.main_data.talk.listener_actor = play->camera.request_data.talk.listener_actor;
    play->camera.main_data.talk.listener_pos = play->camera.request_data.talk.listener_pos;
    play->camera.main_data.talk.cull_timer = 0.0f;
    play->camera.main_data.talk.flags = (play->camera.request_data.talk.flags & 1) ? 2 : 0;
    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

static void Camera2_Talk_ChangeCameraCenterPos_BetweenSpeakerToListener(GAME_PLAY* play, ACTOR* speaker,
                                                                        ACTOR* listener, f32 dist) {
    xyz_t* pos0;
    xyz_t* pos1;
    xyz_t end_center_pos;
    f32 y_adjust;

    if (speaker != NULL || listener != NULL) {
        if (speaker == NULL) {
            pos0 = &listener->eye.position;
            pos1 = pos0;
        } else if (listener == NULL) {
            pos1 = &speaker->eye.position;
            pos0 = pos1;
        } else {
            pos1 = &listener->eye.position;
            pos0 = &speaker->eye.position;
        }

        if (play->camera.main_data.talk.flags & 2) {
            pos1 = &play->camera.main_data.talk.listener_pos;
        }

        y_adjust = 17.0f;
        if (!F32_IS_ZERO(dist)) {
            y_adjust -= -60.0f / dist;
        }

        end_center_pos.x = (pos0->x + pos1->x) * 0.5f;
        end_center_pos.y = (pos0->y + pos1->y) * 0.5f - y_adjust;
        end_center_pos.z = (pos0->z + pos1->z) * 0.5f;

        play->camera.main_data.talk.goal_center_pos = end_center_pos;
        Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(play, &end_center_pos, FALSE);
    }
}

static int Camera2_TalkCheckCliffLRRange(GAME_PLAY* play, int left_ut_x, int right_ut_x, int ut_z, f32 height) {
    int i;

    for (i = left_ut_x; i < right_ut_x + 1; i++) {
        u32 attribute = mCoBG_UtNum2BgAttr(i, ut_z);
        f32 center_y = mCoBG_UtNum2UtCenterY(i, ut_z);

        if ((mCoBG_CheckCliffAttr(attribute) && center_y > height + 30.0f) || center_y > height + 230.0f) {
            return TRUE;
        }
    }

    return FALSE;
}

static int Camera2_Talk_CheckCliffLR(GAME_PLAY* play, const xyz_t* pos) {
    int ut_x;
    int ut_z;

    int l_ut_x;
    int r_ut_x;

    mFI_Wpos2UtNum(&ut_x, &ut_z, *pos); // weirdness going on here with the struct copy
    l_ut_x = ut_x - 4;
    if (l_ut_x < 0) {
        l_ut_x = 0;
    }

    r_ut_x = ut_x + 4;

    if (Camera2_TalkCheckCliffLRRange(play, l_ut_x, r_ut_x, ut_z, pos->y) ||
        Camera2_TalkCheckCliffLRRange(play, l_ut_x, r_ut_x, ut_z + 3, pos->y) ||
        Camera2_TalkCheckCliffLRRange(play, l_ut_x, r_ut_x, ut_z + 6, pos->y)) {
        return TRUE;
    }

    return FALSE;
}

static int Camera2_Talk_NoLowAngleCheck(GAME_PLAY* play, const xyz_t* pos) {
    int block_x;
    int block_z;
    int ut_x;
    int ut_z;

    if (Camera2_InDoorCheck()) {
        return FALSE;
    }

    mFI_Wpos2BkandUtNuminBlock(&block_x, &block_z, &ut_x, &ut_z, *pos); /* ??? why is this here */
    return Camera2_Talk_CheckCliffLR(play, pos) != FALSE;
}

static void Camera2_Talk_GetAngleY(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, s_xyz* goal_dir,
                                   f32 dist_between) {
    int angle;
    s16 angle_y;

    if (play->camera.main_data.talk.flags & 2) {
        angle_y = (s16)search_position_angleY(&speaker->world.position, &play->camera.main_data.talk.listener_pos);
    } else {
        angle_y = (s16)search_position_angleY(&speaker->world.position, &listener->world.position);
    }

    if ((angle_y < DEG2SHORT_ANGLE(135.0f) && angle_y > DEG2SHORT_ANGLE(45.0f)) ||
        (angle_y > DEG2SHORT_ANGLE(-135.0f) && angle_y < DEG2SHORT_ANGLE(-45.0f))) {
        angle = 0;
    } else {
        f32 add_angle = cos_s(2 * angle_y) * 2730.0f; // cos_s(2 * y) * 15.0f (deg)
        f32 sin = sin_s(angle_y);
        f32 cos = cos_s(angle_y);

        if (cos * sin >= 0.0f) {
            angle = -add_angle; // angle = [-15 deg, 0 deg]
        } else {
            angle = add_angle; // angle = [0 deg, 15 deg]
        }
    }

    goal_dir->y += angle;
}

static void Camera2_Talk_GetGoalDirectionAngleXYZAndSetDistance_BetweenSpeakerToListener(GAME_PLAY* play,
                                                                                         ACTOR* speaker,
                                                                                         ACTOR* listener,
                                                                                         f32 dist_between, s_xyz* dir) {
    xyz_t pos = play->camera.main_data.talk.goal_center_pos;
    f32 dist;
    f32 x_ratio = 0.0f;
    f32 z_ratio = 0.0f;

    Camera2_Get_GoalDistanceAndDirection(play, &dist, dir);
    dir->x += 1440; // just shy of 8 degrees (~7.915)
    Camera2_Get_PosBlockRatio(play, &pos, &x_ratio, &z_ratio);

    if (Camera2_Talk_NoLowAngleCheck(play, &pos)) {
        Camera2_main_Simple_AngleDistStd(play, dir, &dist);
        dist *= 0.75f;
        dir->x -= DEG2SHORT_ANGLE(2.75f);
        play->camera.main_data.talk.flags |= 1;
    } else {
        Camera2_Talk_GetAngleY(play, speaker, listener, dir, dist_between);
        dist += dist_between * 1.46f;
        play->camera.main_data.talk.flags &= ~1;
    }

    Camera2_MoveDistancePosAndSpeed(play, dist, FALSE);
}

static void Camera2_SetPos_Talk(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    ACTOR* speaker = camera->main_data.talk.speaker_actor;
    ACTOR* listener = camera->main_data.talk.listener_actor;
    CameraMainData* main_data = &camera->main_data;
    f32 dist;
    s_xyz dir;

    if (speaker != NULL || listener != NULL) {
        if (speaker == NULL || listener == NULL) {
            dist = 0.0f;
        } else {
            dist = search_position_distance(&speaker->world.position, &listener->world.position);
        }

        if (main_data->talk.flags & 2) {
            dist = search_position_distance(&speaker->world.position, &main_data->talk.listener_pos);
        }

        Camera2_Talk_ChangeCameraCenterPos_BetweenSpeakerToListener(play, speaker, listener, dist);
        Camera2_Talk_GetGoalDirectionAngleXYZAndSetDistance_BetweenSpeakerToListener(play, speaker, listener, dist,
                                                                                     &dir);
        Camera2_MoveDirectionAngleXYZ(play, &dir, 0);
        Camera2_SetEyePos_fromCenterPos(play);
        Camera2_SetView(play);
    }
}

static void Camera2_Talk_AddCullTimer(GAME_PLAY* play) {
    Camera2_AddCullTimer(&play->camera.main_data.talk.cull_timer, 15.0f, play->game.graph->dt_num_60fps_frames);
}

static void Camera2_Talk_SetTalking_Cull(GAME_PLAY* play) {
    ACTOR* actor;
    f32 width;
    f32 x;
    f32 z;

    if (Camera2_CheckCullingMode()) {
        for (actor = play->actor_info.list[ACTOR_PART_ITEM].actor; actor != NULL; actor = actor->next_actor) {
            s16 id = actor->id;

            if ((s16)id == mAc_PROFILE_BGITEM || (s16)id == mAc_PROFILE_FALLS || (s16)id == mAc_PROFILE_FALLSESW ||
                (s16)id == mAc_PROFILE_TRAIN0 || (s16)id == mAc_PROFILE_TRAIN1 || (s16)id == mAc_PROFILE_STATION ||
                (s16)id == mAc_PROFILE_DUMP || (s16)id == mAc_PROFILE_GOZA || (s16)id == mAc_PROFILE_RADIO ||
                (s16)id == mAc_PROFILE_MIKUJI || (s16)id == mAc_PROFILE_TUKIMI || (s16)id == mAc_PROFILE_LOTUS ||
                (s16)id == mAc_PROFILE_BOAT || (s16)id == mAc_PROFILE_BRIDGE_A ||
                (s16)id == mAc_PROFILE_ROOM_SUNSHINE_MINSECT || (s16)id == mAc_PROFILE_S_CAR) {
                continue;
            }

            x = actor->world.position.x;
            z = actor->world.position.z;

            if ((s16)id == mAc_PROFILE_MUSEUM) {
                width = 142.0f;
            } else if ((s16)id == mAc_PROFILE_DEPART || (s16)id == mAc_PROFILE_SUPER) {
                width = 130.0f;
            } else if ((s16)id == mAc_PROFILE_CONVENI) {
                width = 110.0f;
            } else if ((s16)id == mAc_PROFILE_POST_OFFICE || (s16)id == mAc_PROFILE_SHOP ||
                       (s16)id == mAc_PROFILE_NEEDLEWORK_SHOP) {
                width = 90.0f;
            } else {
                width = 65.0f;
            }

            if (Camera2_CheckEnterCullingArea(x, z, width)) {
                actor->cull_while_talking = TRUE;
            }
        }
    }
}

static void Camera2_main_Talk(GAME_PLAY* play) {
    Camera2_SetPos_Talk(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_Talk_AddCullTimer(play);
    Camera2_Talk_SetTalking_Cull(play);
    Camera2_change_main_index(play);
}

static void Camera2_main_Normal_SetEndCenterPos_fromPlayer(GAME_PLAY* play, xyz_t* end_center_pos) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    f32 border_x0;
    f32 border_x1;
    f32 border_z1;
    f32 border_z0;
    f32 scale;
    int block_x;
    int block_z;

    Camera2_GetLongBorderScale(play, &scale);

    if (Camera2_InDoorCheck()) {
        int add_dir_idx;
        int add_dist_idx;

        add_dist_idx = play->camera.indoor_distance_addition_idx;
        add_dir_idx = play->camera.indoor_direction_addition_idx;

        scale *= (add_distance_array[add_dist_idx] + 620.0f) / 620.0f;

        if (add_dir_idx == 0 || add_dir_idx == 2) {
            scale *= 0.8f;
        }

        if (add_dist_idx == 2) {
            scale *= 0.88f;
        }
    }

    Camera2_GetBorderScale(play, scale, &border_x0, &border_x1, &border_z0, &border_z1);
    *end_center_pos = player->actor_class.eye.position;

    if (mPlib_get_player_actor_main_index((GAME*)play) == 114) {
        if (mFI_Wpos2BlockNum(&block_x, &block_z, player->actor_class.world.position)) {
            if (block_x == 5) {
                if (block_z == 7) {
                    end_center_pos->z +=
                        55.0f; // extra Z distance when travelling in Kapp'n's boat in the acre below the dock?
                }
            }
        }
    }

    if (play->camera.flags & 1) {
        f32 z_midpoint = (border_z0 + border_z1) * 0.5f;
        f32 z_left = z_midpoint - border_z0;
        f32 z_scale;

        if (F32_IS_ZERO(z_left)) {
            z_scale = 0.0f;
        } else {
            z_scale = (end_center_pos->z - z_midpoint) / z_left;
        }

        end_center_pos->z = z_midpoint + (z_scale * z_left) * 0.25f;
    }

    if (mFI_GetBlockWidth() < scale * 330.0f || border_x0 < border_x1) {
        end_center_pos->x = (border_x0 + border_x1) * 0.5f;
    } else if (end_center_pos->x > border_x0) {
        end_center_pos->x = border_x0;
    } else if (end_center_pos->x < border_x1) {
        end_center_pos->x = border_x1;
    }

    if (mFI_GetBlockHeight() < scale * 250.0f || border_z1 < border_z0) {
        end_center_pos->z = (border_z0 + border_z1) * 0.5f;
    } else if (end_center_pos->z < border_z0) {
        end_center_pos->z = border_z0;
    } else if (end_center_pos->z > border_z1) {
        end_center_pos->z = border_z1;
    }

    if (Camera2_InDoorCheck()) {
        end_center_pos->y = 73.0f;
    }
}

static int Camera2_MoveVparamCenter(GAME_PLAY* play, xyz_t* pos) {
    xyz_t new_center;
    Camera2* camera = &play->camera;
    xyz_t* center_p = &camera->lookat.center;
    xyz_t last_center = *center_p;
    xyz_t* center_vel_p = &camera->movement_velocity;

    Math3DInDivPos2(center_p, pos, &new_center, 0.2f); // weirdness with the float loading
    *center_p = new_center;

    xyz_t_sub(center_p, &last_center, center_vel_p);
    return TRUE;
}

static int Camera2_MoveDistancePosAndSpeedVParam(GAME_PLAY* play, f32 goal_dist) {
    f32 dist = play->camera.focus_distance;

    play->camera.focus_distance = dist + (goal_dist - dist) * 0.2f;
    play->camera.focus_distance_velocity = play->camera.focus_distance - dist;
    return FALSE;
}

static void Camera2_MoveDirectionAngleXYZVParam(GAME_PLAY* play, const s_xyz* goal_dir) {
    s_xyz last_dir;

    Camera2* camera = &play->camera;
    s_xyz* dir_vel = &camera->direction_velocity;
    s16 x;
    s16 y;
    s16 z;
    s_xyz* dir = &camera->direction;

    x = dir->x;
    y = dir->y;
    z = dir->z;

    add_calc_short_angle2(&dir->x, goal_dir->x, 0.10557282f, SHT_MAX_S, 2);
    add_calc_short_angle2(&dir->y, goal_dir->y, 0.10557282f, SHT_MAX_S, 2);
    add_calc_short_angle2(&dir->z, goal_dir->z, 0.10557282f, SHT_MAX_S, 2);

    dir_vel->x = dir->x - x;
    dir_vel->y = dir->y - y;
    dir_vel->z = dir->z - z;
}

static void Camera2_main_Normal_SetPos_fromPlayer(GAME_PLAY* play, int force) {
    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;
    f32 goal_dist;
    s_xyz goal_dir;

    if (main_data->normal.last_indoor_distance_addition_idx != camera->indoor_distance_addition_idx ||
        main_data->normal.last_indoor_direction_addition_idx != camera->indoor_direction_addition_idx) {
        main_data->normal.morph_counter = 80;
        main_data->normal.last_indoor_distance_addition_idx = camera->indoor_distance_addition_idx;
        main_data->normal.last_indoor_direction_addition_idx = camera->indoor_direction_addition_idx;
    }

    Camera2_Get_GoalDistanceAndDirection(play, &goal_dist, &goal_dir);

    if (main_data->normal.morph_counter <= 0) {
        Camera2_MoveDistancePosAndSpeed(play, goal_dist, FALSE);
        Camera2_MoveDirectionAngleXYZ(play, &goal_dir, force);
    } else {
        Camera2_MoveDistancePosAndSpeedVParam(play, goal_dist);
        Camera2_MoveDirectionAngleXYZVParam(play, &goal_dir);
    }

    if (main_data->normal.morph_counter <= 0) {
        xyz_t end_center_pos;

        Camera2_main_Normal_SetEndCenterPos_fromPlayer(play, &end_center_pos);
        Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(play, &end_center_pos, force);
        Camera2_SetEyePos_fromCenterPos(play);
    } else {
        xyz_t end_center_pos;

        Camera2_main_Normal_SetEndCenterPos_fromPlayer(play, &end_center_pos);
        Camera2_MoveVparamCenter(play, &end_center_pos);
        Camera2_SetEyePos_fromCenterPos(play);
        main_data->normal.morph_counter -= play->game.graph->dt_num_60fps_frames;
    }

    Camera2_SetView(play);
}

static void Camera2_main_Normal_AdjustDistanceAndDirection(GAME_PLAY* play, f32* dist, s_xyz* dir) {
    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;

    if ((camera->now_main_index == CAMERA2_PROCESS_NORMAL && (main_data->normal.flags & 1) != 0) || (camera->flags & 1) != 0) {
        *dist *= 1.5f;
    }
}

extern int Camera2_request_main_normal(GAME_PLAY* play, int flags, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.normal.flags = flags;
        Camera2_request_main_index(play, CAMERA2_PROCESS_NORMAL, priority);
        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Normal(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;

    Camera2_setup_main_Base(play);
    main_data->normal.flags = 0;
    main_data->normal.last_indoor_distance_addition_idx = camera->indoor_distance_addition_idx;
    main_data->normal.last_indoor_direction_addition_idx = camera->indoor_direction_addition_idx;
    main_data->normal.morph_counter = 0;

    if (play->camera.request_data.normal.flags & 1) {
        Camera2_main_Normal_SetPos_fromPlayer(play, TRUE);
    } else {
        Camera2_main_Normal_SetPos_fromPlayer(play, FALSE);
    }

    play->camera.requested_main_index_priority = 0;
}

static void Camera2_main_Normal(GAME_PLAY* play) {
    Camera2_main_Normal_SetPos_fromPlayer(play, FALSE);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_main_demo(GAME_PLAY* play, const xyz_t* start_center, const f32 start_dist,
                                     const s_xyz* start_dir, const xyz_t* goal_center, const f32 goal_dist,
                                     const s_xyz* goal_dir, const f32 goal_delta, const f32 accel_delta,
                                     const f32 braking_delta, const int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.demo.starting_center_pos = *start_center;
        play->camera.request_data.demo.starting_distance = start_dist;
        play->camera.request_data.demo.starting_direction = *start_dir;

        play->camera.request_data.demo.goal_center_pos = *goal_center;
        play->camera.request_data.demo.goal_distance = goal_dist;
        play->camera.request_data.demo.goal_direction = *goal_dir;

        play->camera.request_data.demo.goal_delta = goal_delta;
        play->camera.request_data.demo.acceleration_delta = accel_delta;
        play->camera.request_data.demo.braking_delta = braking_delta;

        Camera2_request_main_index(play, CAMERA2_PROCESS_DEMO, priority);
        return TRUE;
    }

    return FALSE;
}

extern int Camera2_request_main_demo_fromNowPos(GAME_PLAY* play, const xyz_t* goal_center, const s_xyz* goal_dir,
                                                const f32 goal_dist, const f32 goal_delta, const f32 accel_delta,
                                                const f32 braking_delta, const int priority) {
    return Camera2_request_main_demo(play, &play->camera.lookat.center, play->camera.focus_distance,
                                     &play->camera.direction, goal_center, goal_dist, goal_dir, goal_delta, accel_delta,
                                     braking_delta, priority);
}

extern int Camera2_request_main_demo_fromNowPos2(GAME_PLAY* play, const xyz_t* goal_center, const f32 goal_delta,
                                                 const f32 accel_delta, const f32 braking_delta, const int priority) {
    static const s_xyz goal_direction = { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0) };

    Camera2* camera = &play->camera;

    return Camera2_request_main_demo(play, &play->camera.lookat.center, play->camera.focus_distance,
                                     &play->camera.direction, goal_center, 620.0f, &goal_direction, goal_delta,
                                     accel_delta, braking_delta, priority);
}

static void Camera2_CalcPos_Demo(GAME_PLAY* play, xyz_t* pos, f32* dist, s_xyz* dir) {
    f32 now_delta = play->camera.main_data.demo.now_delta;
    f32 goal_delta = play->camera.main_data.demo.goal_delta;
    f32 accel_delta = play->camera.main_data.demo.acceleration_delta;
    f32 brake_delta = play->camera.main_data.demo.braking_delta;
    f32 percent;

    int sx;
    int dx;
    int sy;
    int dy;

    if (now_delta != goal_delta) {
        now_delta += play->game.graph->dt_num_60fps_frames;

        if (now_delta > goal_delta) {
            now_delta = goal_delta;
        }

        play->camera.main_data.demo.now_delta = now_delta;
    }

    percent = get_percent_forAccelBrake(now_delta, 0.0f, goal_delta, accel_delta, brake_delta);
    pos->x =
        play->camera.main_data.demo.starting_center_pos.x +
        percent * (play->camera.main_data.demo.goal_center_pos.x - play->camera.main_data.demo.starting_center_pos.x);
    pos->y =
        play->camera.main_data.demo.starting_center_pos.y +
        percent * (play->camera.main_data.demo.goal_center_pos.y - play->camera.main_data.demo.starting_center_pos.y);
    pos->z =
        play->camera.main_data.demo.starting_center_pos.z +
        percent * (play->camera.main_data.demo.goal_center_pos.z - play->camera.main_data.demo.starting_center_pos.z);

    *dist = play->camera.main_data.demo.starting_distance +
            percent * (play->camera.main_data.demo.goal_distance - play->camera.main_data.demo.starting_distance);

    sx = play->camera.main_data.demo.starting_direction.x;
    dx = play->camera.main_data.demo.goal_direction.x - sx;

    if (ABS(dx) > (u16)SHT_MIN_S) {
        if (dx > 0) {
            dx -= 2 * (u16)SHT_MIN_S;
        } else {
            dx += 2 * (u16)SHT_MIN_S;
        }
    }

    dir->x = sx + (s16)(percent * dx);

    sy = play->camera.main_data.demo.starting_direction.y;
    dy = play->camera.main_data.demo.goal_direction.y - sy;

    if (ABS(dy) > (u16)SHT_MIN_S) {
        if (dy > 0) {
            dy -= 2 * (u16)SHT_MIN_S;
        } else {
            dy += 2 * (u16)SHT_MIN_S;
        }
    }

    dir->y = sy + (s16)(percent * dy);
    dir->z = 0;
}

static void Camera2_SetPos_Demo(GAME_PLAY* play) {
    xyz_t pos;
    f32 dist;
    s_xyz dir;

    Camera2_CalcPos_Demo(play, &pos, &dist, &dir);
    Camera2_SetCameraParameter(play, &pos, &dir, FALSE, dist);
    Camera2_SetView(play);
}

static void Camera2_main_Demo(GAME_PLAY* play) {
    Camera2_SetPos_Demo(play);
    Camera2_change_main_index(play);
}

static void Camera2_setup_main_Demo(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;

    main_data->demo.now_delta = 0.0f;

    main_data->demo.starting_center_pos = play->camera.request_data.demo.starting_center_pos;
    main_data->demo.starting_distance = play->camera.request_data.demo.starting_distance;
    main_data->demo.starting_direction = play->camera.request_data.demo.starting_direction;

    main_data->demo.goal_center_pos = play->camera.request_data.demo.goal_center_pos;
    main_data->demo.goal_distance = play->camera.request_data.demo.goal_distance;
    main_data->demo.goal_direction = play->camera.request_data.demo.goal_direction;

    main_data->demo.goal_delta = play->camera.request_data.demo.goal_delta;
    main_data->demo.acceleration_delta = play->camera.request_data.demo.acceleration_delta;
    main_data->demo.braking_delta = play->camera.request_data.demo.braking_delta;

    Camera2_SetCameraParameter(play, &main_data->demo.starting_center_pos, &main_data->demo.starting_direction, TRUE,
                               main_data->demo.starting_distance);
    Camera2_SetView(play);
    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

extern int Camera2_request_main_item(GAME_PLAY* play, int type, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.item.type = type;
        Camera2_request_main_index(play, CAMERA2_PROCESS_ITEM, priority);

        return TRUE;
    }

    return FALSE;
}

static void Camera2_SetPos_Item(GAME_PLAY* play) {
    static const xyz_t offset = { 3.167068f, 28.884293f, 17.341202f };

    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    int type = main_data->item.type;
    xyz_t pos = player->actor_class.world.position;
    s_xyz dir;
    f32 dist;

    if (type == 0) {
        pos.x += offset.x;
        pos.y += offset.y;
        pos.z += offset.z;

        pos.y += -15.0f;
    }

    Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(play, &pos, FALSE);
    Camera2_Get_GoalDistanceAndDirection(play, &dist, &dir);

    dist += -250.0f;
    dir.x += -1400; // approx. -7.7 deg

    Camera2_MoveDistancePosAndSpeed(play, dist, FALSE);
    Camera2_MoveDirectionAngleXYZ(play, &dir, FALSE);
    Camera2_SetEyePos_fromCenterPos(play);
    Camera2_SetView(play);
}

static void Camera2_Item_AddCullTimer(GAME_PLAY* play) {
    Camera2_AddCullTimer(&play->camera.main_data.item.cull_timer, 6.0f, play->game.graph->dt_num_60fps_frames);
}

static void Camera2_Item_SetTalking_Cull(GAME_PLAY* play) {
    Camera2_Talk_SetTalking_Cull(play);
}

static void Camera2_main_Item(GAME_PLAY* play) {
    Camera2_SetPos_Item(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_Item_AddCullTimer(play);
    Camera2_Item_SetTalking_Cull(play);
    Camera2_change_main_index(play);
}

static void Camera2_setup_main_Item(GAME_PLAY* play) {
    play->camera.main_data.item.type = play->camera.request_data.item.type;
    play->camera.main_data.item.cull_timer = 0.0f;
    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

extern int Camera2_request_main_lock(GAME_PLAY* play, const xyz_t* center_pos, const xyz_t* eye_pos, f32 fov_y,
                                     int morph_counter, f32 near, f32 far, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.lock.center_pos = *center_pos;
        play->camera.request_data.lock.eye_pos = *eye_pos;
        play->camera.request_data.lock.fov_y = fov_y;
        play->camera.request_data.lock.morph_counter = (float)morph_counter;
        play->camera.request_data.lock.near = near;
        play->camera.request_data.lock.far = far;

        Camera2_request_main_index(play, CAMERA2_PROCESS_LOCK, priority);

        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Lock(GAME_PLAY* play) {
    play->camera.main_data.lock.center_pos = play->camera.request_data.lock.center_pos;
    play->camera.main_data.lock.eye_pos = play->camera.request_data.lock.eye_pos;
    play->camera.main_data.lock.fov_y = play->camera.request_data.lock.fov_y;
    play->camera.main_data.lock.morph_counter = (float)play->camera.request_data.lock.morph_counter;
    play->camera.main_data.lock.near = play->camera.request_data.lock.near;
    play->camera.main_data.lock.far = play->camera.request_data.lock.far;

    Camera2_setup_main_Base(play);
}

static void Camera2_Lock_SetCenterPos(GAME_PLAY* play, const xyz_t* center_pos, int step) {
    Camera2* camera = &play->camera;

    xyz_t* center_vel_p = &camera->movement_velocity;
    xyz_t* center_p = &camera->lookat.center;
    xyz_t pre_center = *center_p;

    inter_float(&center_p->x, center_pos->x, step);
    inter_float(&center_p->y, center_pos->y, step);
    inter_float(&center_p->z, center_pos->z, step);

    center_vel_p->x = center_p->x - pre_center.x;
    center_vel_p->y = center_p->y - pre_center.y;
    center_vel_p->z = center_p->z - pre_center.z;
}

static void Camera2_Lock_SetEyePos(GAME_PLAY* play, const xyz_t* eye, int step) {
    xyz_t* eye_p = &play->camera.lookat.eye;

    inter_float(&eye_p->x, eye->x, step);
    inter_float(&eye_p->y, eye->y, step);
    inter_float(&eye_p->z, eye->z, step);
}

static void Camera2_Lock_SetFovy(GAME_PLAY* play, f32 fov_y, int step) {
    inter_float(&play->camera.perspective.fov_y, fov_y, step);
}

static void Camera2_Lock_SetNearFar(GAME_PLAY* play, f32 near, f32 far, int step) {
    inter_float(&play->camera.perspective.near, near, step);
    inter_float(&play->camera.perspective.far, far, step);
}

static void Camera2_Lock_MorphCounterProc(GAME_PLAY* play) {
    float morph_counter = play->camera.main_data.lock.morph_counter;

    if (morph_counter <= 0) {
        play->camera.main_data.lock.morph_counter = 0;
    } else {
        play->camera.main_data.lock.morph_counter = morph_counter - play->game.graph->dt_num_60fps_frames;
    }
}

static void Camera2_SetPos_Lock(GAME_PLAY* play) {
    float morph_counter = play->camera.main_data.lock.morph_counter;
    f32 fov_y = play->camera.main_data.lock.fov_y;
    f32 near = play->camera.main_data.lock.near;
    f32 far = play->camera.main_data.lock.far;

    Camera2_Lock_SetCenterPos(play, &play->camera.main_data.lock.center_pos, (int)morph_counter);
    Camera2_Lock_SetEyePos(play, &play->camera.main_data.lock.eye_pos, (int)morph_counter);
    Camera2_Lock_SetFovy(play, fov_y, (int)morph_counter);
    Camera2_Lock_SetNearFar(play, near, far, (int)morph_counter);
    Camera2_Lock_MorphCounterProc(play);
    Camera2_DirectionCalc(play);
    Camera2_SetView(play);
}

static void Camera2_main_Lock(GAME_PLAY* play) {
    Camera2_SetPos_Lock(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_main_door(GAME_PLAY* play, ACTOR* door_actor, u32 flags, int priority) {
    if (door_actor == NULL) {
        return FALSE;
    } else if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.door.door_actor = door_actor;
        play->camera.request_data.door.flags = flags;

        Camera2_request_main_index(play, CAMERA2_PROCESS_DOOR, priority);

        return TRUE;
    } else {
        return FALSE;
    }
}

static void Camera2_setup_main_Door(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    CameraMainData* main_data = &camera->main_data;

    main_data->door.flags = camera->request_data.door.flags;
    main_data->door.center_position = camera->request_data.door.door_actor->eye.position;

    if (main_data->door.flags & 1) {
        main_data->door.morph_counter = 140;
    } else {
        main_data->door.morph_counter = 0;
        camera->requested_main_index_priority = 0;
    }

    Camera2_setup_main_Base(play);
}

static void Camera2_Door_SetCenterPos(GAME_PLAY* play, int step) {
    xyz_t goal_center;
    xyz_t start_center;
    Camera2* camera = &play->camera;
    xyz_t* center_vel_p = &camera->movement_velocity;
    xyz_t* center_p = &camera->lookat.center;

    start_center = *center_p;
    goal_center = camera->main_data.door.center_position;

    inter_float(&center_p->x, goal_center.x, step);
    inter_float(&center_p->y, goal_center.y, step);
    inter_float(&center_p->z, goal_center.z, step);

    center_vel_p->x = center_p->x - start_center.x;
    center_vel_p->y = center_p->y - start_center.y;
    center_vel_p->z = center_p->z - start_center.z;
}

static void Camera2_Door_SetEyePos(GAME_PLAY* play, float step) {
    Camera2* camera = &play->camera;
    CameraLookat* lookat = &camera->lookat;
    xyz_t* center = &lookat->center;
    xyz_t* eye = &lookat->eye;
    s_xyz* dir_vel = &camera->direction_velocity;
    f32* dist_p;
    f32 last_dist;
    s_xyz* dir;
    f32* vel_p;
    s_xyz angle;

    camera->focus_distance = camera->focus_distance; // what?

    dist_p = &camera->focus_distance;
    last_dist = camera->focus_distance;
    dir = &camera->direction;
    vel_p = &camera->focus_distance_velocity;

    angle.x = (s16)-0x7194;
    angle.y = (s16)-0x8000;
    angle.z = (s16)0;

    inter_float(dist_p, (float)350.0f, (int)step);
    *vel_p = last_dist - *dist_p; // inverted velocity?

    if (step == 0) {
        *dir = angle;

        dir_vel->x = 0;
        dir_vel->y = 0;
        dir_vel->z = 0;
    } else {
        f32 t = 1.5f / (f32)step;

        cKF_SkeletonInfo_subRotInterpolation(t, &dir->x, dir->x, angle.x);
        cKF_SkeletonInfo_subRotInterpolation(t, &dir->y, dir->y, angle.y);
    }

    Camera2_PolaPosCalc(eye, dir->x + (u16)SHT_MIN_S, dir->y + (u16)SHT_MIN_S, center, *dist_p);
}

static void Camera2_Door_MorphCounterProc(GAME_PLAY* play) {
    float morph_counter = play->camera.main_data.door.morph_counter;

    if (morph_counter <= 0) {
        play->camera.main_data.door.morph_counter = 0;
    } else {
        play->camera.main_data.door.morph_counter = morph_counter - play->game.graph->dt_num_60fps_frames;
    }
}

static void Camera2_SetPos_Door(GAME_PLAY* play) {
    float morph_counter = play->camera.main_data.door.morph_counter;

    Camera2_Door_SetCenterPos(play, (int)morph_counter);
    Camera2_Door_SetEyePos(play, morph_counter);
    Camera2_Door_MorphCounterProc(play);
    Camera2_SetView(play);
}

static void Camera2_Door_SetTalking_Cull(GAME_PLAY* play) {
    Camera2_Talk_SetTalking_Cull(play);
}

static void Camera2_main_Door(GAME_PLAY* play) {
    Camera2_SetPos_Door(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_Door_SetTalking_Cull(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_main_simple2(GAME_PLAY* play, const xyz_t* center, const s_xyz* dir, f32 dist,
                                        int morph_counter, int mode, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.simple.center_pos = *center;
        play->camera.request_data.simple.angle = *dir;
        play->camera.request_data.simple.distance = dist;
        play->camera.request_data.simple.morph_counter = (float)morph_counter;
        play->camera.request_data.simple.mode = mode;

        Camera2_request_main_index(play, CAMERA2_PROCESS_SIMPLE, priority);

        return TRUE;
    }

    return FALSE;
}

extern int Camera2_request_main_simple_kirin(GAME_PLAY* play, const xyz_t* center, int priority) {
    xyz_t pos;
    s_xyz dir;
    f32 dist;

    Camera2_main_Simple_AngleDistStd(play, &dir, &dist);
    dir.x += -1000;
    dir.y += 2000;

    pos.x = center->x + -45.0f;
    pos.y = center->y;
    pos.z = center->z + -105.0f;

    return Camera2_request_main_simple2(play, &pos, &dir, dist * 0.8f, 20, 1, priority);
}

extern int Camera2_request_main_simple_fishing(GAME_PLAY* play, const xyz_t* player_pos, const xyz_t* bobber_pos,
                                               int priority) {
    f32 dist_mult = 1.0f;

    xyz_t center;
    s_xyz dir;
    f32 dist;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;

    Camera2_main_Simple_AngleDistStd(play, &dir, &dist);

    if (player_pos->y - bobber_pos->y > 70.0f) {
        dist_mult = 1.15f;
        center.x = player_pos->x * 0.55f + bobber_pos->x * 0.45f;
        center.y = player_pos->y * 0.55f + bobber_pos->y * 0.45f;
        center.z = player_pos->z * 0.55f + bobber_pos->z * 0.45f;
    } else {
        center.x = player_pos->x * 0.65f + bobber_pos->x * 0.35f;
        center.y = player_pos->y * 0.65f + bobber_pos->y * 0.35f;
        center.z = player_pos->z * 0.65f + bobber_pos->z * 0.35f;
    }

    return Camera2_request_main_simple(play, &center, &dir, dist * dist_mult, 40, priority);
}
extern int Camera2_request_main_simple_fishing_return(GAME_PLAY* play, const xyz_t* player_pos, int priority) {
    xyz_t center_pos;
    s_xyz dir;
    f32 dist;

    Camera2_main_Normal_SetEndCenterPos_fromPlayer(play, &center_pos);
    Camera2_main_Simple_AngleDistStd(play, &dir, &dist);
    return Camera2_request_main_simple(play, &center_pos, &dir, dist, 30, priority);
}

extern int Camera2_request_main_simple(GAME_PLAY* play, const xyz_t* pos, const s_xyz* dir, f32 dist, int morph_counter,
                                       int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.simple.center_pos = *pos;
        play->camera.request_data.simple.angle = *dir;
        play->camera.request_data.simple.distance = dist;
        play->camera.request_data.simple.morph_counter = (float)morph_counter;
        play->camera.request_data.simple.mode = 0;
        Camera2_request_main_index(play, CAMERA2_PROCESS_SIMPLE, priority);

        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Simple(GAME_PLAY* play) {
    play->camera.main_data.simple.center_pos = play->camera.request_data.simple.center_pos;
    play->camera.main_data.simple.angle = play->camera.request_data.simple.angle;
    play->camera.main_data.simple.distance = play->camera.request_data.simple.distance;
    play->camera.main_data.simple.morph_counter = (float)play->camera.request_data.simple.morph_counter;
    play->camera.main_data.simple.mode = play->camera.request_data.simple.mode;
    play->camera.main_data.simple.cull_timer = 0.0f;
    Camera2_setup_main_Base(play);
}

extern void Camera2_main_Simple_AngleDistStd(GAME_PLAY* play, s_xyz* angle, f32* dist) {
    static const s_xyz std_angle = { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) };

    *angle = std_angle;
    *dist = 620.0f;

    if (Camera2_InDoorCheck() == FALSE && (play->camera.flags & 1) == 0) {
        Camera2_Normal_Swing(play, dist, angle);
    }
}

static void Camera2_Simple_MorphDistance(GAME_PLAY* play, f32 goal_dist, int step) {
    Camera2* camera = &play->camera;
    f32* dist_p = &camera->focus_distance;
    f32* dist_vel_p = &camera->focus_distance_velocity;
    f32 last_dist = *dist_p;

    inter_float(dist_p, goal_dist, step);
    if (step == 0) {
        *dist_vel_p = 0;
    } else {
        *dist_vel_p = *dist_p - last_dist;
    }
}

static void Camera2_Simple_AngleCalc(GAME_PLAY* play, const s_xyz* goal_angle, int morph_counter) {
    Camera2* camera = &play->camera;
    s_xyz* angle_p = &camera->direction;
    s_xyz* angle_vel_p = &camera->direction_velocity;
    s_xyz last_angle;
    f32 t;

    if (morph_counter == 0) {
        angle_p->x = goal_angle->x;
        angle_p->y = goal_angle->y;
        angle_p->z = goal_angle->z;

        angle_vel_p->x = 0;
        angle_vel_p->y = 0;
        angle_vel_p->z = 0;
    } else {
        last_angle = *angle_p;
        t = 1.0f / (f32)morph_counter;

        cKF_SkeletonInfo_subRotInterpolation(t, &angle_p->x, last_angle.x, goal_angle->x);
        cKF_SkeletonInfo_subRotInterpolation(t, &angle_p->y, last_angle.y, goal_angle->y);
        cKF_SkeletonInfo_subRotInterpolation(t, &angle_p->z, last_angle.z, goal_angle->z);

#ifndef BUGFIXES
        angle_vel_p->z = angle_p->x - last_angle.x; // BUG, it should be angle_vel_p->x
#else
        angle_vel_p->x = angle_p->x - last_angle.x;
#endif
        angle_vel_p->y = angle_p->y - last_angle.y;
        angle_vel_p->z = angle_p->z - last_angle.z;
    }
}

static void Camera2_SetPos_Simple(GAME_PLAY* play) {
    float morph_counter = play->camera.main_data.simple.morph_counter;
    f32 goal_dist = play->camera.main_data.simple.distance;

    Camera2_Lock_SetCenterPos(play, &play->camera.main_data.simple.center_pos, (int)morph_counter);
    Camera2_Simple_MorphDistance(play, goal_dist, (int)morph_counter);
    Camera2_Simple_AngleCalc(play, &play->camera.main_data.simple.angle, (int)morph_counter);
    Camera2_SetEyePos_fromCenterPos(play);
    Camera2_SetView(play);
}

static void Camera2_Simple_AddCullTimer(GAME_PLAY* play) {
    Camera2_AddCullTimer(&play->camera.main_data.simple.cull_timer, 6.0f, play->game.graph->dt_num_60fps_frames);
}

static void Camera2_main_Simple(GAME_PLAY* play) {
    Camera2_SetPos_Simple(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);

    if (play->camera.main_data.simple.mode == 1) {
        Camera2_Simple_AddCullTimer(play);
        Camera2_Talk_SetTalking_Cull(play);
    }

    Camera2_change_main_index(play);
}

extern int Camera2_request_main_listen_front_low_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority) {
    const s16 y = listener->world.angle.y;
    s16 angle_y;

    if (!(sin_s(y) < 0.0f)) {
        angle_y = DEG2SHORT_ANGLE(-169.06f);
    } else {
        angle_y = DEG2SHORT_ANGLE(169.06f);
    }

    return Camera2_request_main_cust_talk(play, speaker, listener, 1.0f, priority, DEG2SHORT_ANGLE(5.495f), angle_y,
                                          0.0f);
}

extern int Camera2_request_main_needlework_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority) {
    s16 angle_x;
    s16 angle_y;
    f32 diff_x = listener->eye.position.x - speaker->eye.position.x;

    angle_y = (s16)(diff_x * (20.0f / 3.0f) + -32768.0f);

    if (angle_y > 0) {
        angle_y = DEG2SHORT_ANGLE(-180.0f);
    }

    diff_x = fabsf(diff_x);
    angle_x = DEG2SHORT_ANGLE(5.495f);
    if (diff_x < mFI_UT_WORLDSIZE_X_F) {
        angle_x = DEG2SHORT_ANGLE(13.735f);
    }

    return Camera2_request_main_cust_talk(play, speaker, listener, 0.5f, priority, angle_x, angle_y, 50.0f);
}

extern int Camera2_request_main_cust_talk(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, f32 center_ratio,
                                          int priority, s16 angle_x, s16 angle_y, f32 distance) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.cust_talk.speaker_actor = speaker;
        play->camera.request_data.cust_talk.listener_actor = listener;
        play->camera.request_data.cust_talk.center_ratio = center_ratio;
        play->camera.request_data.cust_talk.angle_x = angle_x;
        play->camera.request_data.cust_talk.angle_y = angle_y;
        play->camera.request_data.cust_talk.distance = distance;

        Camera2_request_main_index(play, CAMERA2_PROCESS_CUST_TALK, priority);
        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Cust_talk(GAME_PLAY* play) {
    play->camera.main_data.cust_talk.speaker_actor = play->camera.request_data.cust_talk.speaker_actor;
    play->camera.main_data.cust_talk.listener_actor = play->camera.request_data.cust_talk.listener_actor;
    play->camera.main_data.cust_talk.center_ratio = play->camera.request_data.cust_talk.center_ratio;
    play->camera.main_data.cust_talk.angle_x = play->camera.request_data.cust_talk.angle_x;
    play->camera.main_data.cust_talk.angle_y = play->camera.request_data.cust_talk.angle_y;
    play->camera.main_data.cust_talk.distance = play->camera.request_data.cust_talk.distance;
    play->camera.main_data.cust_talk.cull_timer = 0.0f;

    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

static void Camera2_Cust_Talk_ChangeCameraCenterPos_BetweenSpeakerToListener(GAME_PLAY* play, ACTOR* speaker,
                                                                             ACTOR* listener, f32 dist,
                                                                             f32 center_ratio) {
    if (speaker != NULL || listener != NULL) {
        xyz_t* pos0;
        xyz_t* pos1;
        xyz_t center;
        f32 unused;

        if (speaker == NULL) {
            pos0 = &listener->eye.position;
            pos1 = pos0;
        } else if (listener == NULL) {
            pos1 = &speaker->eye.position;
            pos0 = pos1;
        } else {
            pos1 = &listener->eye.position;
            pos0 = &speaker->eye.position;
        }

        unused = fabsf(dist);
        center.x = pos0->x + center_ratio * (pos1->x - pos0->x);
        center.y = pos0->y + center_ratio * (pos1->y - pos0->y);
        center.z = pos0->z + center_ratio * (pos1->z - pos0->z);

        Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(play, &center, FALSE);
    }
}

static void Camera2_Cust_Talk_SetAngleDist(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, s_xyz* angle, f32 dist) {
    f32 goal_dist;

    Camera2_Get_GoalDistanceAndDirection(play, &goal_dist, angle);
    angle->x += play->camera.main_data.cust_talk.angle_x;
    angle->y = play->camera.main_data.cust_talk.angle_y;
    goal_dist += dist * 1.46f + play->camera.main_data.cust_talk.distance;
    Camera2_MoveDistancePosAndSpeed(play, goal_dist, FALSE);
}

static void Camera2_SetPos_Cust_Talk(GAME_PLAY* play) {
    ACTOR* speaker = play->camera.main_data.cust_talk.speaker_actor;
    ACTOR* listener = play->camera.main_data.cust_talk.listener_actor;

    if (speaker != NULL || listener != NULL) {
        f32 dist;
        f32 center_ratio = play->camera.main_data.cust_talk.center_ratio;
        s_xyz angle;

        if (speaker == NULL || listener == NULL) {
            dist = 0.0f;
        } else {
            dist = search_position_distance(&speaker->world.position, &listener->world.position);
        }

        Camera2_Cust_Talk_ChangeCameraCenterPos_BetweenSpeakerToListener(play, speaker, listener, dist, center_ratio);
        Camera2_Cust_Talk_SetAngleDist(play, speaker, listener, &angle, dist);
        Camera2_MoveDirectionAngleXYZ(play, &angle, 0);
        Camera2_SetEyePos_fromCenterPos(play);
        Camera2_SetView(play);
    }
}

static void Camera2_Cust_Talk_AddCullTimer(GAME_PLAY* play) {
    Camera2_AddCullTimer(&play->camera.main_data.cust_talk.cull_timer, 15.0f, play->game.graph->dt_num_60fps_frames);
}

static void Camera2_main_Cust_talk(GAME_PLAY* play) {
    Camera2_SetPos_Cust_Talk(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_Cust_Talk_AddCullTimer(play);
    Camera2_Talk_SetTalking_Cull(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_BuySikimono_WallPaper(GAME_PLAY* play, xyz_t* center, xyz_t* eye) {
    return Camera2_request_main_inter(play, center, eye, center, eye, 0.6f, 0.3f, 1, 28, 5);
}

extern int Camera2_Inter_set_reverse_mode(GAME_PLAY* play) {
    switch (play->camera.now_main_index) {
        case CAMERA2_PROCESS_INTER: {
            play->camera.main_data.inter.flags |= 2;
            break;
        }

        case CAMERA2_PROCESS_INTER2: {
            play->camera.main_data.inter.flags |= 4;
            break;
        }
    }

    return TRUE;
}

extern int Camera2_request_main_inter(GAME_PLAY* play, const xyz_t* start_center, const xyz_t* start_eye,
                                      const xyz_t* goal_center, const xyz_t* goal_eye, f32 s0, f32 s1, u32 flags,
                                      int morph_counter, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.inter.starting_center_pos = *start_center;
        play->camera.request_data.inter.starting_eye_pos = *start_eye;
        play->camera.request_data.inter.goal_center_pos = *goal_center;
        play->camera.request_data.inter.goal_eye_pos = *goal_eye;
        play->camera.request_data.inter.slope0 = s0;
        play->camera.request_data.inter.slope1 = s1;
        play->camera.request_data.inter.flags = flags;
        play->camera.request_data.inter.morph_counter = morph_counter;

        Camera2_request_main_index(play, CAMERA2_PROCESS_INTER, priority);
        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Inter(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    CameraRequestData* request_data = &camera->request_data;
    CameraMainData* main_data = &camera->main_data;

    main_data->inter.flags = request_data->inter.flags;

    if (main_data->inter.flags & 1) {
        main_data->inter.starting_center_pos = camera->lookat.center;
        main_data->inter.starting_eye_pos = camera->lookat.eye;
    } else {
        main_data->inter.starting_center_pos = request_data->inter.starting_center_pos;
        main_data->inter.starting_eye_pos = request_data->inter.starting_eye_pos;
    }

    main_data->inter.goal_center_pos = request_data->inter.goal_center_pos;
    main_data->inter.goal_eye_pos = request_data->inter.goal_eye_pos;
    main_data->inter.slope0 = request_data->inter.slope0;
    main_data->inter.slope1 = request_data->inter.slope1;
    main_data->inter.now_delta = 0;
    main_data->inter.max_delta = request_data->inter.morph_counter;

    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

static void Camera2_Inter_SetPosCenter(GAME_PLAY* play, f32 center_ratio) {
    Camera2* camera = &play->camera;
    xyz_t* center_p = &camera->lookat.center;
    const xyz_t last_center = *center_p;

    Math3DInDivPos2(&camera->main_data.inter.starting_center_pos, &camera->main_data.inter.goal_center_pos, center_p,
                    center_ratio);
    xyz_t_sub(center_p, &last_center, &camera->movement_velocity);
}

static void Camera2_Inter_SetPosEye(GAME_PLAY* play, f32 eye_ratio) {
    Camera2* camera = &play->camera;

    Math3DInDivPos2(&camera->main_data.inter.starting_eye_pos, &camera->main_data.inter.goal_eye_pos,
                    &camera->lookat.eye, eye_ratio);
}

static void Camera2_Inter_CounterProc(GAME_PLAY* play) {
    if (play->camera.main_data.inter.flags & 2) {
        float count = play->camera.main_data.inter.now_delta;

        if (count <= 0) {
            play->camera.main_data.inter.now_delta = 0;
            Camera2_request_main_normal(play, 0, 5);
        } else {
            play->camera.main_data.inter.now_delta = count - play->game.graph->dt_num_60fps_frames;
        }
    } else if (play->camera.main_data.inter.flags & 4) {
        float count = play->camera.main_data.inter.now_delta;
        xyz_t pos;
        s_xyz angle;
        f32 dist;
        int block_x;
        int block_z;

        if (count <= 0) {
            PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

            play->camera.main_data.inter.now_delta = 0;
            Camera2_main_Simple_AngleDistStd(play, &angle, &dist);
            mFI_BlockKind2BkNum(&block_x, &block_z, mRF_BLOCKKIND_SHRINE);
            mFI_BkNum2WposXZ(&pos.x, &pos.z, block_x, block_z);
            pos.x += (UT_X_NUM / 2) * mFI_UT_WORLDSIZE_X_F;
            pos.y = player->actor_class.world.position.y;
            pos.z += (UT_Z_NUM / 2 + 2) * mFI_UT_WORLDSIZE_Z_F;
            Camera2_request_main_simple(play, &pos, &angle, dist, 0, 6);
        } else {
            play->camera.main_data.inter.now_delta = count - play->game.graph->dt_num_60fps_frames;
        }
    } else {
        float count = play->camera.main_data.inter.now_delta;
        float max = play->camera.main_data.inter.max_delta;

        if (count >= max) {
            play->camera.main_data.inter.now_delta = max;
        } else {
            play->camera.main_data.inter.now_delta = count + play->game.graph->dt_num_60fps_frames;
        }
    }
}

static void Camera2_SetPos_Inter(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    f32 ratio;
    float now = camera->main_data.inter.now_delta;
    float max = camera->main_data.inter.max_delta;
    f32 slope0 = camera->main_data.inter.slope0;
    f32 slope1 = camera->main_data.inter.slope1;

    if (max != 0) {
        ratio = cKF_HermitCalc(now / max, 1.0f, 0.0f, 1.0f, slope0, slope1);
    } else {
        ratio = 0.0f;
    }

    Camera2_Inter_SetPosCenter(play, ratio);
    Camera2_Inter_SetPosEye(play, ratio);
    Camera2_Inter_CounterProc(play);
    Camera2_DirectionCalc(play);
    Camera2_SetView(play);
}

static void Camera2_main_Inter(GAME_PLAY* play) {
    Camera2_SetPos_Inter(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_change_main_index(play);
}

extern int Camera2_request_main_staff_roll(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, int priority) {
    if (Camera2_check_request_main_priority(play, priority) > 0) {
        play->camera.request_data.staff_roll.speaker_actor = speaker;
        play->camera.request_data.staff_roll.listener_actor = listener;
        Camera2_request_main_index(play, CAMERA2_PROCESS_STAFF_ROLL, priority);
        return TRUE;
    }

    return FALSE;
}

static void Camera2_setup_main_Staff_roll(GAME_PLAY* play) {
    play->camera.main_data.staff_roll.last_center_pos = play->camera.lookat.center;
    play->camera.main_data.staff_roll.last_eye_pos = play->camera.lookat.eye;
    play->camera.main_data.staff_roll.last_distance = play->camera.focus_distance;
    play->camera.main_data.staff_roll.last_direction = play->camera.direction;
    play->camera.main_data.staff_roll.speaker_actor = play->camera.request_data.staff_roll.speaker_actor;
    play->camera.main_data.staff_roll.listener_actor = play->camera.request_data.staff_roll.listener_actor;
    play->camera.main_data.staff_roll.rotation_y_delta = 0;
    play->camera.main_data.staff_roll.r_delta = 20;
    play->camera.main_data.staff_roll.rotation_x_delta = 40;
    play->camera.main_data.staff_roll.flags = 1;
    play->camera.main_data.staff_roll.dist_counter = 0;
    play->camera.main_data.staff_roll.morph_counter = 320;

    Camera2_setup_main_Base(play);
    play->camera.requested_main_index_priority = 0;
}

static void Camera2_Staff_Roll_Center(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, xyz_t* center, f32 distance,
                                      f32 t, int update) {
    Camera2* camera = &play->camera;

    xyz_t* pos0;
    xyz_t* pos1;
    xyz_t goal_center;
    f32 y_shift;

    f32 center_x;
    f32 center_y;
    f32 center_z;

    f32 h;
    f32 r_rot;
    f32 y_rot_x;
    f32 y_rot_z;
    int temp;
    s16 temp2;

    *center = ZeroVec;
    if (speaker != NULL || listener != NULL) {
        if (speaker == NULL) {
            pos0 = &listener->eye.position;
            pos1 = pos0;
        } else if (listener == NULL) {
            pos1 = &speaker->eye.position;
            pos0 = pos1;
        } else {
            pos1 = &listener->eye.position;
            pos0 = &speaker->eye.position;
        }

        y_shift = 17.0f;
        if (!F32_IS_ZERO(distance)) {
            y_shift -= -60.0f / distance;
        }

        center_x = (pos0->x + pos1->x) / 2.0f;
        center_y = (pos0->y + pos1->y) / 2.0f - y_shift;
        center_z = (pos0->z + pos1->z) / 2.0f;

        h = cKF_HermitCalc(t, 1.0f, 0.0f, 1.0f, 0.49f, 0.0f);
        temp2 = ((f32)camera->main_data.staff_roll.r_delta / 4600.0f) * 65535.0f;
        h *= ((1.0f + sin_s(temp2) * 0.2f) - 0.2f) * 45.0f;

        // likely fakematch
        temp =
            (int)((-(f32)camera->main_data.staff_roll.rotation_y_delta / CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR) *
                  65535.0f) +
            0x10000;
        temp += camera->main_data.staff_roll.last_direction.y;
        y_rot_x = sin_s(temp + DEG2SHORT_ANGLE2(-90.0f));

        goal_center.y = center_y;
        goal_center.x = center_x + h * y_rot_x;

        // likely fakematch
        temp =
            (int)((-(f32)camera->main_data.staff_roll.rotation_y_delta / CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR) *
                  65535.0f) +
            0x10000;
        temp += camera->main_data.staff_roll.last_direction.y;
        y_rot_z = cos_s(temp + DEG2SHORT_ANGLE2(-90.0f));

        goal_center.z = center_z + h * y_rot_z;

        *center = goal_center;

        if (update) {
            Camera2_MoveCenterPosAndSpeed_fromEndCenterPos(play, &goal_center, FALSE);
        }
    }
}

static void Camera2_Staff_Roll_DistAngle(GAME_PLAY* play, ACTOR* speaker, ACTOR* listener, s_xyz* angle, f32 distance) {
    Camera2* camera = &play->camera;
    s16 temp;
    f32 dist;

    temp = ((f32)camera->main_data.staff_roll.r_delta / 4600.0f) * 65535.0f;
    dist = ((sin_s(temp) * 0.2f + 1.0f) - 0.2f) * 575.0f;
    temp = ((f32)camera->main_data.staff_roll.rotation_x_delta / CAMERA2_STAFFROLL_CENTER_X_ROT_STEP_DIVISOR) * 65536.0f;

    angle->x = (s16)(sin_s(temp) * 5000.0f);
    angle->y = (s16)((-(f32)camera->main_data.staff_roll.rotation_y_delta / CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR) * 65535.0f) +
               camera->main_data.staff_roll.last_direction.y + (u16)SHT_MIN_S;
    angle->z = 0;

    Camera2_MoveDistancePosAndSpeed(play, dist, FALSE);
}

static void Camera2_main_Staff_Roll_SetPos(GAME_PLAY* play) {
    Camera2* camera = &play->camera;
    ACTOR* speaker = camera->main_data.staff_roll.speaker_actor;
    ACTOR* listener = camera->main_data.staff_roll.listener_actor;
    CameraMainData* main_data = &camera->main_data;
    f32 distance;
    xyz_t center;
    xyz_t eye;
    xyz_t last_center;
    s_xyz angle;

    if (speaker != NULL || listener != NULL) {
        u8* kk_save_area = mEv_get_save_area(mEv_EVENT_KK_SLIDER, 10);

        if (speaker == NULL || listener == NULL) {
            distance = 0.0f;
        } else {
            distance = search_position_distance(&speaker->world.position, &listener->world.position);
        }

        /* TODO: cast kk_save_area to correct struct type */
        if (((*(u16*)(kk_save_area + 2)) & 0x8000) && (main_data->staff_roll.flags & 2) == 0) {
            /* Start camera sequence? */
            main_data->staff_roll.flags &= ~1;
            main_data->staff_roll.flags |= 2;
            main_data->staff_roll.morph_counter = 240;
        }

        if (main_data->staff_roll.flags & 2) {
            Camera2_Lock_SetCenterPos(play, &main_data->staff_roll.last_center_pos,
                                      main_data->staff_roll.morph_counter);
            Camera2_Lock_SetEyePos(play, &main_data->staff_roll.last_eye_pos, main_data->staff_roll.morph_counter);
            Camera2_DirectionCalc(play);

            if (main_data->staff_roll.morph_counter > 0) {
                main_data->staff_roll.morph_counter -= play->game.graph->dt_num_60fps_frames;
            } else {
                camera->focus_distance = main_data->staff_roll.last_distance;
                camera->direction = main_data->staff_roll.last_direction;
                Camera2_change_priority(play, 0);
                Camera2_request_main_normal(play, 0, 5);
            }
        } else if (main_data->staff_roll.flags & 1) {
            xyz_t* center_vel_p = &camera->movement_velocity;
            xyz_t* center_p = &camera->lookat.center;
            f32 morph_counter = main_data->staff_roll.morph_counter;
            f32 t = (320.0f - morph_counter) / 320.0f;

            last_center = *center_p;

            Camera2_Staff_Roll_Center(play, speaker, listener, &center, distance, t, FALSE);
            Camera2_Lock_SetCenterPos(play, &center, (int)main_data->staff_roll.morph_counter);
            center_vel_p->x = center_p->x - last_center.x;
            center_vel_p->y = center_p->y - last_center.y;
            center_vel_p->z = center_p->z - last_center.z;
            Camera2_Staff_Roll_DistAngle(play, speaker, listener, &angle, distance);
            Camera2_PolaPosCalc(&eye, angle.x + (u16)SHT_MIN_S, angle.y + (u16)SHT_MIN_S, &center,
                                camera->focus_distance);
            Camera2_Lock_SetEyePos(play, &eye, (int)main_data->staff_roll.morph_counter);

            if (main_data->staff_roll.morph_counter > 0) {
                main_data->staff_roll.morph_counter -= play->game.graph->dt_num_60fps_frames;
            } else {
                main_data->staff_roll.flags &= ~1;
            }

            Camera2_DirectionCalc(play);
        } else {
            Camera2_Staff_Roll_Center(play, speaker, listener, &center, distance, 1.0f, TRUE);
            Camera2_Staff_Roll_DistAngle(play, speaker, listener, &angle, distance);
            Camera2_MoveDirectionAngleXYZ_morph(play, &angle, 0);
            Camera2_SetEyePos_fromCenterPos(play);

            main_data->staff_roll.r_delta += play->game.graph->dt_num_60fps_frames;
            if (main_data->staff_roll.r_delta > 4600) {
                main_data->staff_roll.r_delta = 0;
            }

            main_data->staff_roll.rotation_x_delta += play->game.graph->dt_num_60fps_frames;
            if (main_data->staff_roll.rotation_x_delta > CAMERA2_STAFFROLL_CENTER_X_ROT_STEP_DIVISOR) {
                main_data->staff_roll.rotation_x_delta = 0;
            }
        }

        main_data->staff_roll.rotation_y_delta += play->game.graph->dt_num_60fps_frames;
        if (main_data->staff_roll.rotation_y_delta > CAMERA2_STAFFROLL_CENTER_Y_ROT_STEP_DIVISOR) {
            main_data->staff_roll.rotation_y_delta = 0;
        }

        Camera2_SetView(play);
    }
}

static void Camera2_main_Staff_roll(GAME_PLAY* play) {
    Camera2_main_Staff_Roll_SetPos(play);
    Camera2_sound_Set_Ground(play);
    Camera2_SetMicPos(play);
    Camera2_change_main_index(play);
}

extern void Init_Camera2(GAME_PLAY* play) {
    static const Camera2 init_camera_data = {
        // lookat
        {
            { 0.0f, 876.81238f, 876.81238f }, // eye
            { 0.0f, 0.0f, 0.0f },             // center
            { 0.0f, 1.0f, 0.0f }              // up
        },
        // perspective
        {
            20.0f,       // fov_y
            4.0f / 3.0f, // aspect_ratio
            200.0f,      // near
            1600.0f,     // far
            1.0f         // scale
        },
        { DEG2SHORT_ANGLE(-135.0f), DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(0.0f) }, // direction
        { 0, 0, 0 },                                                                   // direction_velocity
        { 0.0f, 0.0f, 0.0f },                                                          // movement_velocity
        620.0f,                                                                        // focus_distance
        0.0f,                                                                          // focus_distance_velocity
        1,                                                                             // indoor_distance_addition_idx
        1,                                                                             // indoor_direction_addition_idx
        CAMERA2_PROCESS_NORMAL,                                                        // now_main_index
        CAMERA2_PROCESS_NORMAL,                                                        // last_main_index
        CAMERA2_PROCESS_NORMAL,                                                        // requested_main_index
        -1,                                                                            // requested_main_index_priority
        FALSE,                                                                         // requested_main_index_flag
        { 0 },                                                                         // main_data
        { 0 },                                                                         // request_data
        { 0.0f, 876.81238f, 876.81238f },                                              // mic_pos
        0,                                                                             // flags
        { 0.0f, 0.0f, 0.0f },                                                          // offset_eye
        { 0.0f, 0.0f, 0.0f }                                                           // offset_center
    };

    play->camera = init_camera_data;
}

typedef void (*CAMERA2_MAIN_INDEX_SETUP_PROC)(GAME_PLAY*);

static void Camera2_change_main_index(GAME_PLAY* play) {
    static const CAMERA2_MAIN_INDEX_SETUP_PROC proc[CAMERA2_PROCESS_NUM] = {
        &Camera2_setup_main_Stop,      &Camera2_setup_main_Normal, &Camera2_setup_main_Wade,
        &Camera2_setup_main_Talk,      &Camera2_setup_main_Demo,   &Camera2_setup_main_Item,
        &Camera2_setup_main_Lock,      &Camera2_setup_main_Door,   &Camera2_setup_main_Simple,
        &Camera2_setup_main_Cust_talk, &Camera2_setup_main_Inter,  &Camera2_setup_main_Staff_roll,
        &Camera2_setup_main_Inter,
    };

    if (play->camera.requested_main_index_flag != TRUE || play->camera.requested_main_index < CAMERA2_PROCESS_STOP ||
        play->camera.requested_main_index >= CAMERA2_PROCESS_NUM || proc[play->camera.requested_main_index] == NULL) {
        return;
    } else {
        CAMERA2_MAIN_INDEX_SETUP_PROC setup_proc = proc[play->camera.requested_main_index];
        (*setup_proc)(play);
    }
}

typedef void (*CAMERA2_MAIN_INDEX_PROC)(GAME_PLAY*);
extern void Camera2_process(GAME_PLAY* play) {
    static const CAMERA2_MAIN_INDEX_PROC proc[CAMERA2_PROCESS_NUM] = {
        &Camera2_main_Stop,   &Camera2_main_Normal,    &Camera2_main_Wade,  &Camera2_main_Talk,
        &Camera2_main_Demo,   &Camera2_main_Item,      &Camera2_main_Lock,  &Camera2_main_Door,
        &Camera2_main_Simple, &Camera2_main_Cust_talk, &Camera2_main_Inter, &Camera2_main_Staff_roll,
        &Camera2_main_Inter,
    };

    if (play->camera.now_main_index < CAMERA2_PROCESS_STOP || play->camera.now_main_index >= CAMERA2_PROCESS_NUM ||
        proc[play->camera.now_main_index] == NULL) {
        return;
    } else {
        CAMERA2_MAIN_INDEX_PROC main_proc = proc[play->camera.now_main_index];

        (*main_proc)(play);
        Camera2_process_other_func2(play);
    }
}

extern void Camera2_draw(GAME_PLAY* play) {
}
