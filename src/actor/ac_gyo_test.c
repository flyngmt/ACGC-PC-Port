#include "ac_gyoei.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_uki.h"

enum {
    aGTT_ACTION_SWIM,
    aGTT_ACTION_WAIT,
    aGTT_ACTION_ESCAPE,
    aGTT_ACTION_NEAR,
    aGTT_ACTION_TOUCH,
    aGTT_ACTION_BITE,
    aGTT_ACTION_COMEBACK,

    aGTT_ACTION_NUM
};

static void aGTT_actor_move(ACTOR* actorx, GAME* game);
static void aGTT_setupAction(aGYO_CTRL_ACTOR* gyo, int action);
static void aGTT_set_scale(ACTOR* actorx, f32 scale);
static void aGTT_speed_reset(ACTOR* actorx);
static s16 aGTT_Get_flow_angle(ACTOR* actorx);
static s16 aGTT_Get_flow_angle_rv(ACTOR* actorx);
static void aGTT_set_angle(ACTOR* actorx, s16 angleY);
static f32 aGTT_Get_water_surface_position_y(xyz_t pos);

#include "../src/actor/ac_gyoei_type.c_inc"

static f32 aGTT_speed[8] = {
   1.0f, 1.25f, 1.25f, 1.5f, 1.75f, 2.0f, 2.2f, 2.2f,
};

static f32 aGTT_back_speed[8] = {
   -0.38f, -0.4f, -0.42f, -0.42f, -0.45f, -0.5f, -0.7f, -0.7f,
};

static s16 aGTT_touch_count[8] = {
   19, 19, 19, 19, 20, 22, 24, 24,
};

static f32 aGTT_touch_distance[8] = {
   12.0f, 13.0f, 15.0f, 15.0f, 20.0f, 25.0f, 30.0f, 30.0f,
};

static f32 aGYO_shadow_scale[8] = {
   0.3f, 0.4f, 0.5f, 0.5f, 0.6f, 0.8f, 1.2f, 10.0f,
};

static f32 aGYO_search_area[][5] = {
   {40.0f, 40.0f, 40.0f, 50.0f, 60.0f}, // regular rod
   {40.0f, 40.0f, 40.0f, 50.0f, 60.0f}, // gold rod
};

static f32 aGYO_search_angle[][5] = {
   {3.0f, 7.0f, 30.0f, 50.0f, 180.0f}, // regular rod
   {7.5f, 15.0f, 40.0f, 60.0f, 180.0f}, // gold rod
};

static f32 aGYO_bite_time[][5] = {
   {10.0f, 11.0f, 12.0f, 15.0f, 45.0f}, // regular rod
   {11.0f, 12.0f, 13.0f, 18.0f, 60.0f}, // gold rod
};

extern void aGTT_actor_init(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    f32 scale;
    u32 attr;

    attr = mCoBG_Wpos2BgAttribute_Original(actorx->world.position);
    if (mCoBG_CheckWaterAttribute(attr) == TRUE) {
        actorx->world.position.y = aGTT_Get_water_surface_position_y(actorx->world.position);
    }

    gyo->size_type = gyoei_type[gyo->gyo_type].size;
    gyo->action = aGTT_ACTION_SWIM;
    gyo->fwork0 = 19.0f;
    scale = aGYO_shadow_scale[gyo->size_type] * 0.02f;
    aGTT_set_scale(actorx, scale);
    aGTT_speed_reset(actorx);
    actorx->mv_proc = aGTT_actor_move;
    aGTT_set_angle(actorx, aGTT_Get_flow_angle_rv(actorx));
    actorx->shape_info.draw_shadow = FALSE;
    aGTT_setupAction(gyo, aGTT_ACTION_WAIT);
}

static int aGYO_get_uki_type(void) {
    int ret = aGYO_ROD_NORMAL;

    if (Now_Private->equipment == ITM_GOLDEN_ROD) {
        ret = aGYO_ROD_GOLDEN;
    }

    return ret;
}

static void aGTT_speed_reset(ACTOR* actorx) {
    actorx->speed = 0.0f;
    actorx->max_velocity_y = 0.0f;
}

static void aGTT_set_scale(ACTOR* actorx, f32 scale) {
    actorx->scale.x = scale;
    actorx->scale.y = scale;
    actorx->scale.z = scale;
}

static void aGTT_set_angle(ACTOR* actorx, s16 angleY) {
    actorx->world.angle.y = angleY;
    actorx->shape_info.rotation.y = angleY;
}

static xyz_t aGTT_pos_calc(xyz_t pos, GAME* game, s16 angleY, f32 dist, f32 rr) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    xyz_t ret;
    f32 sin = sin_s(playerx->world.angle.y) * dist;
    f32 cos = cos_s(playerx->world.angle.y) * dist;
    f32 cos2 = cos_s(angleY) * -rr;
    f32 sin2 = sin_s(angleY) * rr;

    ret.x = pos.x + sin + cos2;
    ret.z = pos.z + cos + sin2;
    return ret;
}

static void aGTT_effect_sibuki(aGYO_CTRL_ACTOR* gyo, GAME* game, s16 arg) {
    xyz_t pos = gyo->tools_class.actor_class.world.position;
    f32 water_y = mCoBG_GetWaterHeight_File(pos, __FILE__, 334);
    s16 flow_angle;

    switch (arg) {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8: {
            static f32 rr[] = { 3.0f, 3.5f, 4.0f, 4.0f, 4.5f, 5.0f, 5.0f, 5.0f };

            pos = aGTT_pos_calc(gyo->linked_actor->world.position, game, gyo->linked_actor->world.angle.y, 4.0f, rr[gyo->size_type]);
            break;
        }
    }
    
    pos.y = water_y;
    flow_angle = aGTT_Get_flow_angle((ACTOR*)gyo);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1, flow_angle, game, EMPTY_NO, arg, 0);
}

static void aGTT_kage_make_actor(aGYO_CTRL_ACTOR* gyo, GAME* game, u8 state) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 height;

    if (state == 0) {
        gyo->gyo_flags |= 0x20;
    }
    
    height = aGTT_Get_water_surface_position_y(gyo->tools_class.actor_class.world.position);
    Actor_info_make_actor(
        // clang-format off
        &play->actor_info, game, mAc_PROFILE_GYO_KAGE,
        gyo->tools_class.actor_class.world.position.x, height, gyo->tools_class.actor_class.world.position.z,
        0, 0, 0,
        play->block_table.block_x, play->block_table.block_z,
        -1, EMPTY_NO, gyo->size_type, -1, ACTOR_OBJ_BANK_KEEP
        // clang-format on
    );
}

static void aGTT_fish_make_actor(aGYO_CTRL_ACTOR* gyo, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    // set uki actor's child actor to the fish actor being created
    ((UKI_ACTOR*)gyo->linked_actor)->child_actor = Actor_info_make_actor(
        // clang-format off
        &play->actor_info, game, mAc_PROFILE_GYO_RELEASE,
        gyo->tools_class.actor_class.world.position.x, gyo->tools_class.actor_class.world.position.y, gyo->tools_class.actor_class.world.position.z,
        0, gyo->swork4, 0,
        play->block_table.block_x, play->block_table.block_z,
        -1, EMPTY_NO, ITM_FISH_START + gyo->gyo_type, -1, ACTOR_OBJ_BANK_KEEP
        // clang-format on
    );
}

static void aGTT_effect_hamon(aGYO_CTRL_ACTOR* gyo, GAME* game, s16 arg) {
    xyz_t pos = gyo->tools_class.actor_class.world.position;
    f32 water_y = mCoBG_GetWaterHeight_File(gyo->tools_class.actor_class.world.position, __FILE__, 451);
    s16 flow_angle = aGTT_Get_flow_angle((ACTOR*)gyo);
    
    pos.y = water_y;
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, flow_angle, game, EMPTY_NO, arg, 0);
}

static u8 aGTT_random_check(f32 val) {
    u8 ret = FALSE;

    if (RANDOM_F(val) < 1.0f) {
        ret = TRUE;
    }

    return ret;
}

static int aGTT_chase_s_angle(aGYO_CTRL_ACTOR* gyo, s16 target, s16 step) {
    s16 angle;

    chase_angle(&gyo->tools_class.actor_class.world.angle.y, target, step);
    gyo->tools_class.actor_class.shape_info.rotation.y = gyo->tools_class.actor_class.world.angle.y;
    angle = ABS((s16)(gyo->tools_class.actor_class.world.angle.y - target));
    if (angle < step) {
        gyo->gyo_flags &= ~0x80;
    }

    return angle;
}

static int aGTT_warp_event(aGYO_CTRL_ACTOR* gyo) {
    int ret = FALSE;

    if (mPlib_check_player_warp_forEvent()) {
        ((UKI_ACTOR*)gyo->linked_actor)->gyo_command = 0;
        aGTT_setupAction(gyo, aGTT_ACTION_ESCAPE);
        ret = TRUE;
    }

    return ret;
}

static f32 aGTT_speed_calc(f32 speed, s16 angle) {
    return speed * sin_s(angle);
}

static void aGTT_position_calc(aGYO_CTRL_ACTOR* gyo) {
    static f32 hosei[] = {
        // clang-format off
        -8.0f,
        -10.0f,
        -12.0f,
        -12.0f,
        -15.0f,
        -20.0f,
        -25.0f,
        -25.0f,
        // clang-format on
    };

    gyo->tools_class.actor_class.world.position.x += hosei[gyo->size_type] * sin_s(gyo->tools_class.actor_class.world.angle.y);
    gyo->tools_class.actor_class.world.position.z += hosei[gyo->size_type] * cos_s(gyo->tools_class.actor_class.world.angle.y);
}

static int aGTT_swim_speed_check(aGYO_CTRL_ACTOR* gyo, f32 target, f32 step, f32 speed) {
    int ret = chase_f(&gyo->fwork3, target, step * 0.5f);
    
    gyo->tools_class.actor_class.speed = aGTT_speed_calc(speed, DEG2SHORT_ANGLE2(gyo->fwork3));
    return ret;
}

static int aGTT_swim_speed_change(aGYO_CTRL_ACTOR* gyo, f32 target, f32 step, f32 speed) {
    int ret = chase_f(&gyo->fwork3, target, step * 0.5f);
    s16 angle = DEG2SHORT_ANGLE2(gyo->fwork3);

    if (gyo->fwork3 > step) {
        gyo->tools_class.actor_class.shape_info.rotation.y += gyo->swork2;
    } else if (gyo->fwork3 == step) {
        gyo->swork2 = (s16)(gyo->swork2 - gyo->tools_class.actor_class.world.angle.y) / (s16)(target / step);
    }

    gyo->tools_class.actor_class.speed = aGTT_speed_calc(speed, angle);
    if (ret == TRUE) {
        gyo->tools_class.actor_class.world.angle.y = gyo->tools_class.actor_class.shape_info.rotation.y;
    }

    return ret;
}

static s16 aGTT_Get_flow_angle(ACTOR* actorx) {
    xyz_t flow;
    
    mCoBG_GetWaterFlow(&flow, actorx->bg_collision_check.result.unit_attribute);
    return atans_table(flow.z, flow.x);
}

static s16 aGTT_Get_flow_angle_rv(ACTOR* actorx) {
    return aGTT_Get_flow_angle(actorx) + DEG2SHORT_ANGLE2(180.0f);
}

static void aGTT_flow_direction(ACTOR* actorx) {
    static s16 angl_add_table[] = { 0x100, 0x400 };
    s16 flow_rv = aGTT_Get_flow_angle_rv(actorx);

    chase_angle(&actorx->world.angle.y, flow_rv, angl_add_table[ABS((s16)(actorx->world.angle.y - flow_rv)) > 0x4000]);
    actorx->shape_info.rotation.y = actorx->world.angle.y;
}

static f32 aGTT_Get_water_surface_position_y(xyz_t pos) {
    f32 ret = mCoBG_GetWaterHeight_File(pos, __FILE__, 699);

    return ret - 8.0f;
}

static int aGTT_search_Uki(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    GAME_PLAY* play;
    f32 target_dist;
    f32 target_y;
    f32 escape_dist;
    s16 target_angle;
    s16 goal_angle;
    s16 search_area;
    int ret;

    play = (GAME_PLAY*)game;
    search_area = gyoei_type[gyo->gyo_type].search_area;
    ret = FALSE;
    {
        UKI_ACTOR* uki = (UKI_ACTOR*)Actor_info_name_search(&play->actor_info, mAc_PROFILE_UKI, ACTOR_PART_BG);
        gyo->linked_actor = (ACTOR*)uki;
        if (uki != NULL) {
            target_dist = search_position_distance(&actorx->world.position, &uki->actor_class.world.position);
            target_y = actorx->world.position.y - uki->actor_class.world.position.y;
            target_angle = search_position_angleY(&actorx->world.position, &uki->actor_class.world.position);
            goal_angle = target_angle - actorx->shape_info.rotation.y;
            
            if (gyo->size_type == aGYO_SIZE_XXS || gyo->size_type == aGYO_SIZE_XS) {
                escape_dist = 17.0f;
            } else {
                escape_dist = 22.0f;
            }

            if (uki->hit_water_flag && target_dist < escape_dist) {
                aGTT_set_angle(actorx, target_angle + DEG2SHORT_ANGLE2(180.0f));
                aGTT_setupAction(gyo, aGTT_ACTION_ESCAPE);
            } else {
                int rod_type = aGYO_get_uki_type();

                if ((gyo->gyo_flags & 1) == 0 && uki->cast_timer == 0 &&
                    target_dist < aGYO_search_area[rod_type][search_area] && fabsf(target_y) < 10.0f &&
                    goal_angle > DEG2SHORT_ANGLE2(-aGYO_search_angle[rod_type][search_area]) &&
                    goal_angle < DEG2SHORT_ANGLE2(aGYO_search_angle[rod_type][search_area])) {
                    ret = TRUE;
                }
            }
        }
    }

    return ret;
}

static int aGTT_player_near(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    f32 dist;
    s16 target_angle;
    xyz_t pos;
    int ret = FALSE;

    dist = search_position_distance(&actorx->world.position, &playerx->world.position);
    target_angle = search_position_angleY(&actorx->world.position, &playerx->world.position);

    if (
        // clang-format off
        ((dist < 110.0f && mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DASH) ||
        (dist < 150.0f && (
            mPlib_Check_HitAxe(&pos) ||
            mPlib_Check_StopNet(&pos) ||
            mPlib_Check_HitScoop(&pos)
        ))) ||
        gyo->escape_flag
        // clang-format on
    ) {
        aGTT_set_angle(actorx, target_angle + DEG2SHORT_ANGLE2(180.0f));
        switch (gyo->size_type) {
            case aGYO_SIZE_XXS:
            case aGYO_SIZE_XS:
            case aGYO_SIZE_S:
            case aGYO_SIZE_M:
                aGTT_effect_hamon(gyo, game, 3);
                break;
            case aGYO_SIZE_L:
            case aGYO_SIZE_XL:
            case aGYO_SIZE_XXL:
                aGTT_effect_hamon(gyo, game, 2);
                break;
        }

        aGTT_kage_make_actor(gyo, game, 0);
        ret = TRUE;
    }

    return ret;
}

static int aGYO_check_wall(ACTOR* actorx) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    int ret = FALSE;
    
    if (actorx->bg_collision_check.result.hit_wall != mCoBG_DIDNT_HIT_WALL) {
        int count = actorx->bg_collision_check.result.hit_wall_count;

        if (count != 0) {
            int i;

            for (i = 0; i < count; i++) {
                if (actorx->bg_collision_check.wall_info[i].type == mCoBG_WALL_TYPE0) {
                    s16 wall_angle = actorx->bg_collision_check.wall_info[i].angleY;
                    s16 check_angle = wall_angle - (actorx->world.angle.y + DEG2SHORT_ANGLE2(180.0f));
                    
                    if (check_angle > 0) {
                        aGTT_set_angle(actorx, actorx->world.angle.y + DEG2SHORT_ANGLE2(90.0f));
                    } else {
                        aGTT_set_angle(actorx, actorx->world.angle.y - DEG2SHORT_ANGLE2(90.0f));
                    }

                    gyo->gyo_flags |= 0x40;
                    ret = TRUE;
                    break;
                }
            }
        }
    }

    return ret;
}

static int aGYO_check_bridge(aGYO_CTRL_ACTOR* gyo) {
    int ret = FALSE;
    
    if ((gyo->gyo_flags & 0x100) == 0) {
        switch (gyo->action) {
            case aGTT_ACTION_SWIM:
            case aGTT_ACTION_WAIT:
            case aGTT_ACTION_NEAR:
                if (((ACTOR*)gyo)->bg_collision_check.result.is_in_water) {
                    switch (mCoBG_Wpos2Attribute(((ACTOR*)gyo)->world.position, NULL)) {
                        case mCoBG_ATTRIBUTE_STONE:
                        case mCoBG_ATTRIBUTE_WOOD:
                            break;
                        default:
                            ret = TRUE;
                            break;
                    }
                } else {
                    ret = TRUE;
                }
                break;
            default:
                ret = TRUE;
                break;
        }
    }

    return ret;
}

static int aGYO_check_fall(aGYO_CTRL_ACTOR* gyo) {
    int ret = FALSE;

    if (gyo->action == aGTT_ACTION_BITE || gyo->action == aGTT_ACTION_COMEBACK) {
        ret = TRUE;
    } else if ((gyo->gyo_flags & 0x100) == 0) {
        f32 now_y = ((ACTOR*)gyo)->world.position.y;
        f32 last_y = ((ACTOR*)gyo)->last_world_position.y;

        if (((ACTOR*)gyo)->bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_WATERFALL && now_y < last_y) {
            if (gyo->action == aGTT_ACTION_BITE || gyo->action == aGTT_ACTION_COMEBACK) {
                ((UKI_ACTOR*)gyo->linked_actor)->gyo_command = 0;
            }
        } else {
            ret = TRUE;
        }
    }

    return ret;
}

static void aGTT_wait(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    f32 rnd;

    aGTT_flow_direction(actorx);

    if (DECREMENT_TIMER(gyo->work0) == 0) {
        rnd = RANDOM_F(3.0f);
        
        if (rnd < 1.0f) {
            gyo->swim_flag = 0;
        } else if (rnd < 2.0f) {
            gyo->swim_flag = 1;
        } else {
            gyo->swim_flag = 2;
        }

        aGTT_setupAction(gyo, aGTT_ACTION_SWIM);
    } else {
        if (aGTT_player_near(actorx, game) == FALSE && aGTT_search_Uki(actorx, game) == TRUE) {
            aGTT_setupAction(gyo, aGTT_ACTION_NEAR);
        }
    }
}

static void aGTT_swim(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    int wait_flag = FALSE;

    if (aGYO_check_wall(actorx) == TRUE) {
        aGTT_setupAction(gyo, aGTT_ACTION_ESCAPE);
    } else {
        switch (gyo->swim_flag) {
            case 0:
                wait_flag = aGTT_swim_speed_check(gyo, 360.0f, 5.0f, 0.5f);
                break;
            case 1:
                wait_flag = aGTT_swim_speed_check(gyo, 180.0f, 5.0f, 0.5f);
                if (wait_flag == TRUE) {
                    actorx->world.angle.y = actorx->shape_info.rotation.y;
                }
                break;
            case 2:
                if ((gyo->gyo_flags & 0x80) != 0) {
                    aGTT_chase_s_angle(gyo, gyo->swork3, 0x400);
                } else {
                    wait_flag = aGTT_swim_speed_change(gyo, 180.0f, 5.0f, 1.0f);
                }
                break;
        }

        if (wait_flag == TRUE) {
            aGTT_setupAction(gyo, aGTT_ACTION_WAIT);
        } else {
            if (aGTT_player_near(actorx, game) == FALSE && aGTT_search_Uki(actorx, game) == TRUE) {
                aGTT_setupAction(gyo, aGTT_ACTION_NEAR);
            }
        }
    }
}

static void aGTT_near(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    f32 target_dist;
    f32 target_y;
    s16 angle_y;
    UKI_ACTOR* uki = (UKI_ACTOR*)gyo->linked_actor;
    s16 search_area = gyoei_type[gyo->gyo_type].search_area;
    int rod_type = aGYO_get_uki_type();
    
    angle_y = search_position_angleY(&actorx->world.position, &uki->actor_class.world.position);
    aGTT_set_angle(actorx, angle_y);
    target_dist = search_position_distance(&actorx->world.position, &uki->actor_class.world.position);
    target_y = actorx->world.position.y - uki->actor_class.world.position.y;
    if (target_dist > aGYO_search_area[rod_type][search_area] || fabsf(target_y) > 10.0f) {
        aGTT_setupAction(gyo, aGTT_ACTION_WAIT);
    } else if (target_dist < aGTT_touch_distance[gyo->size_type]) {
        if (uki->gyo_status == 1) {
            uki->gyo_command = 1;
            uki->gyo_type = gyo->gyo_type;
            uki->child_actor = actorx;
            uki->actor_class.world.angle.y = actorx->world.angle.y;
            uki->actor_class.shape_info.rotation.y = actorx->shape_info.rotation.y;
            aGTT_setupAction(gyo, aGTT_ACTION_TOUCH);
        } else {
            aGTT_setupAction(gyo, aGTT_ACTION_WAIT);
        }
    }
}

static void aGTT_touch(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    UKI_ACTOR* uki;

    if (aGTT_warp_event(gyo)) {
        return;
    }

    uki = (UKI_ACTOR*)gyo->linked_actor;
    uki->actor_class.world.angle.y = actorx->world.angle.y;
    uki->actor_class.shape_info.rotation.y = actorx->shape_info.rotation.y;

    if (DECREMENT_TIMER(gyo->work0) == 0) {
        f32 target_dist;
        s16 angle;
        
        actorx->speed = aGTT_speed[gyo->size_type];
        angle = search_position_angleY(&actorx->world.position, &uki->actor_class.world.position);
        aGTT_set_angle(actorx, angle);
        target_dist = search_position_distance(&actorx->world.position, &uki->actor_class.world.position);

        if (target_dist < aGTT_touch_distance[gyo->size_type]) {
            if ((aGTT_random_check(4.0f) != FALSE && (aGYO_check_fall(gyo) == TRUE)) || DECREMENT_TIMER(gyo->touch_counter) == 0) {
                if (uki->gyo_status == 2) {
                    uki->gyo_command = 2;

                    // If a free space exists, 1/20 chance of switching the fish out for trash
                    if (mPlib_Get_space_putin_item() >= 0 && aGTT_random_check(20.0f) != 0) {
                        static int gomi[] = { aGYO_TYPE_EMPTY_CAN, aGYO_TYPE_EMPTY_CAN, aGYO_TYPE_BOOT, aGYO_TYPE_BOOT, aGYO_TYPE_BOOT, aGYO_TYPE_OLD_TIRE, aGYO_TYPE_OLD_TIRE, aGYO_TYPE_OLD_TIRE };

                        gyo->gyo_type = gomi[gyo->size_type];
                        uki->gyo_type = gyo->gyo_type;
                    }

                    aGTT_setupAction(gyo, aGTT_ACTION_BITE);
                }
            } else {
                uki->touched_flag = TRUE;
                gyo->work0 = (int)((aGTT_touch_count[gyo->size_type] + RANDOM2_F(30.0f)) * 2.0f);
                actorx->speed = aGTT_back_speed[gyo->size_type] + RANDOM2_F(0.2f);
            }
        }
    }

    if (uki->status == 6) {
        uki->gyo_command = 0;
        aGTT_effect_sibuki(gyo, game, 0);
        aGTT_kage_make_actor(gyo, game, 0);
    }
}

static void aGTT_bite(ACTOR* actorx, GAME* game) {
    static s16 eff_arg[] = { 8, 7, 4, 4, 5, 6, 6, 6 };

    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    UKI_ACTOR* uki = (UKI_ACTOR*)gyo->linked_actor;
    f32 now_y = actorx->world.position.y;
    f32 last_y = actorx->last_world_position.y;

    if (aGTT_warp_event(gyo)) {
        return;
    }

    if (uki->gyo_status == 4) {
        if (uki->actor_class.bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_WATERFALL) {
            actorx->world.position = uki->actor_class.world.position;

            if (now_y < actorx->world.position.y) {
                actorx->world.position.y = now_y;
            }

            sAdo_OngenPos((uintptr_t)actorx, NA_SE_24, &actorx->world.position);
        } else {
            static f32 rr[] = { 6.0f, 7.0f, 8.0f, 8.0f, 9.0f, 10.0f, 15.0f, 15.0f };
            xyz_t pos;

            pos = aGTT_pos_calc(uki->actor_class.world.position, game, uki->actor_class.world.angle.y, 8.0f, rr[gyo->size_type]);
            actorx->world.position.x = pos.x;
            actorx->world.position.z = pos.z;
            if (now_y < last_y) {
                actorx->world.position.y = last_y;
            }

            aGTT_set_angle(actorx, uki->actor_class.world.angle.y);
            sAdo_OngenPos((uintptr_t)actorx, NA_SE_24, &actorx->world.position);
            CLIP(gyo_clip)->hitcheck_gyoei_proc(&actorx->world.position, gyo->size_type);

            if (DECREMENT_TIMER(gyo->swork0) == 0) {
                if (aGTT_random_check(2.0f)) {
                    aGTT_effect_sibuki(gyo, game, eff_arg[gyo->size_type]);
                }

                gyo->swork0 = 3;
            }
        }
    } else {
        f32 now_y = actorx->world.position.y;
        f32 last_y = actorx->last_world_position.y;

        actorx->world.position.x = uki->actor_class.world.position.x;
        actorx->world.position.z = uki->actor_class.world.position.z;

        if (uki->actor_class.bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_WATERFALL) {
            actorx->world.position = uki->actor_class.world.position;
            if (now_y < actorx->world.position.y) {
                actorx->world.position.y = now_y;
            }
        } else {
            if (now_y < last_y) {
                actorx->world.position.y = last_y;
            }
        }

        aGTT_set_angle(actorx, uki->actor_class.world.angle.y);
        aGTT_position_calc(gyo);

        if (uki->gyo_status == 5) {
            actorx->speed = 0.0f;
            aGTT_setupAction(gyo, aGTT_ACTION_COMEBACK);
        } else if (DECREMENT_TIMER(gyo->work0) == 0) {
            uki->gyo_command = 0;
            aGTT_kage_make_actor(gyo, game, 0);
        }
    }

    uki->gyo_pos = actorx->world.position;
}

static void aGTT_comeback(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    f32 scale;
    UKI_ACTOR* uki = (UKI_ACTOR*)gyo->linked_actor;
    
    actorx->world.position = uki->uki_pos;
    aGTT_set_angle(actorx, uki->actor_class.world.angle.y);

    if (uki->gyo_status == 3) {
        aGTT_position_calc(gyo);
        if (aGTT_random_check(10.0f)) {
            aGTT_effect_hamon(gyo, game, 0);
        }
    } else if (uki->gyo_status == 5) {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

        if ((gyo->gyo_flags & 4) == 0) {
            switch (gyo->gyo_type) {
                case aGYO_TYPE_EMPTY_CAN:
                case aGYO_TYPE_BOOT:
                case aGYO_TYPE_OLD_TIRE:
                    aGTT_kage_make_actor(gyo, game, 1);
                    break;
            }

            gyo->swork4 = playerx->world.angle.y;
            gyo->gyo_flags |= 8;
        }
    } else if (uki->gyo_status == 6) {
        gyo->gyo_flags |= 0x200;
        if (gyo->anim_frame == 1) {
            sAdo_OngenTrgStart(NA_SE_11A, &actorx->world.position);
        }
    } else if (uki->gyo_status == 8) {
        uki->gyo_status = 0;
        aGTT_fish_make_actor(gyo, game);
        gyo->gyo_flags |= 0x20;
    } else if (uki->gyo_status == 7) {
        gyo->gyo_flags |= 0x10;
    } else if (uki->gyo_status == 0) {
        uki->gyo_command = 0;
        uki->child_actor = NULL;
        gyo->gyo_flags &= ~2;
        gyo->gyo_flags |= 0x20;
        return;
    }

    if ((gyo->gyo_flags & 0x10) != 0) {
        scale = uki->gyo_scale / 100.0f;
    } else if (gyo->draw_type == aGYO_DRAW_TYPE_FISH) {
        scale = 0.01f;
    } else {
        scale = aGYO_shadow_scale[gyo->size_type] * 0.02f;
    }

    aGTT_set_scale(actorx, scale);
    uki->gyo_pos = actorx->world.position;
}

static void aGTT_escape(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    
    if (aGTT_player_near(actorx, game) == FALSE) {
        if (aGTT_search_Uki(actorx, game) == TRUE) {
            aGTT_setupAction(gyo, aGTT_ACTION_NEAR);
        } else if ((gyo->gyo_flags & 0x40) != 0 || aGYO_check_wall(actorx) == FALSE) {
            if (DECREMENT_TIMER(gyo->work0) == 0) {
                gyo->gyo_flags &= ~0x40;
                aGTT_setupAction(gyo, aGTT_ACTION_WAIT);
            } else {
                chase_f(&actorx->speed, 0.0f, 0.02f);
            }
        }
    }
}

static void aGTT_swim_init(aGYO_CTRL_ACTOR* gyo) {
    switch (gyo->swim_flag) {
        case 0:
            gyo->fwork3 = 50.0f;
            gyo->swork2 = 0;
            gyo->swork3 = 0;
            break;
        case 1:
            gyo->fwork3 = 0.0f;
            gyo->swork2 = 0;
            gyo->swork3 = RANDOM2_F(DEG2SHORT_ANGLE2(180.0f));
            gyo->tools_class.actor_class.world.angle.y += gyo->swork3;
            break;
        case 2:
            gyo->gyo_flags |= 0x80;
            gyo->fwork3 = 0.0f;
            gyo->swork2 = aGTT_Get_flow_angle_rv((ACTOR*)gyo);
            gyo->swork3 = ((ACTOR*)gyo)->world.angle.y + (s16)RANDOM2_F(DEG2SHORT_ANGLE2(90.0f));
            ((ACTOR*)gyo)->shape_info.rotation.y = ((ACTOR*)gyo)->world.angle.y;
            break;
    }

    aGTT_speed_reset((ACTOR*)gyo);
}

static void aGTT_near_init(aGYO_CTRL_ACTOR* gyo) {
    gyo->gyo_flags |= 2;
    ((ACTOR*)gyo)->speed = aGTT_speed[gyo->size_type];
    ((ACTOR*)gyo)->max_velocity_y = 12.0f;
}

static void aGTT_touch_init(aGYO_CTRL_ACTOR* gyo) {
    gyo->work0 = 0;
    gyo->range = 12.0f;
    gyo->touch_counter = 5;
    aGTT_speed_reset((ACTOR*)gyo);
}

static void aGTT_bite_init(aGYO_CTRL_ACTOR* gyo) {    
    gyo->work0 = (int)(aGYO_bite_time[aGYO_get_uki_type()][gyoei_type[gyo->gyo_type].bite_time] * 2.0f);
    gyo->swork0 = 3;
    aGTT_speed_reset((ACTOR*)gyo);
}

static void aGTT_comeback_init(aGYO_CTRL_ACTOR* gyo) {   
    gyo->swork2 = 1 + RANDOM(3);
    gyo->swork3 = 15 + RANDOM2(10);
    aGTT_speed_reset((ACTOR*)gyo);
}

static void aGTT_wait_init(aGYO_CTRL_ACTOR* gyo) {
    gyo->gyo_flags &= ~2;
    gyo->work0 = (int)((100.0f + RANDOM_F(30.0f)) * 2.0f);
    ((ACTOR*)gyo)->speed = -0.15f + RANDOM2_F(0.2f);
    ((ACTOR*)gyo)->max_velocity_y = 0.0f;  
}

static void aGTT_escape_init(aGYO_CTRL_ACTOR* gyo) {
    gyo->swork0 = 0;
    gyo->work0 = 100;
    ((ACTOR*)gyo)->speed = 2.0f;
}

typedef void (*aGTT_INIT_PROC)(aGYO_CTRL_ACTOR* gyo);

static void aGTT_setupAction(aGYO_CTRL_ACTOR* gyo, int action) {
    static aGTT_INIT_PROC init_proc[] = {
        aGTT_swim_init,
        aGTT_wait_init,
        aGTT_escape_init,
        aGTT_near_init,
        aGTT_touch_init,
        aGTT_bite_init,
        aGTT_comeback_init,
    };

    static aGYO_ACT_PROC act_proc[] = {
        aGTT_swim,
        aGTT_wait,
        aGTT_escape,
        aGTT_near,
        aGTT_touch,
        aGTT_bite,
        aGTT_comeback,
    };

    gyo->action = action;
    gyo->act_proc = act_proc[action];
    init_proc[action](gyo);
}

static void aGTT_actor_move(ACTOR* actorx, GAME* game) {
    aGYO_CTRL_ACTOR* gyo = (aGYO_CTRL_ACTOR*)actorx;
    
    actorx->world.position.y = aGTT_Get_water_surface_position_y(actorx->world.position);
    if (aGYO_check_bridge(gyo) == TRUE && aGYO_check_fall(gyo) == TRUE) {
        (*gyo->act_proc)(actorx, game);
    } else if ((gyo->gyo_flags & 0x100) == 0) {
        gyo->work0 = 60;
        gyo->gyo_flags |= 0x100;
    } else if (DECREMENT_TIMER(gyo->work0) == 0) {
        gyo->gyo_flags |= 0x20;
    }
}
