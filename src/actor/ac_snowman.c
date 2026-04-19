#include "ac_snowman.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_actor_shadow.h"
#include "m_roll_lib.h"
#include "m_handbill.h"
#include "m_malloc.h"

enum {
    aSMAN_PART0,
    aSMAN_PART1,

    aSMAN_PART_NUM
};

static void aSMAN_actor_ct(ACTOR* actorx, GAME* game);
static void aSMAN_actor_dt(ACTOR* actorx, GAME* game);
static void aSMAN_actor_move(ACTOR* actorx, GAME* game);
static void aSMAN_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Snowman_Profile = {
    mAc_PROFILE_SNOWMAN,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ETC_SNOWMAN_BALL_A,
    ACTOR_OBJ_BANK_PSNOWMAN,
    sizeof(SNOWMAN_ACTOR),
    aSMAN_actor_ct,
    aSMAN_actor_dt,
    aSMAN_actor_move,
    aSMAN_actor_draw,
    NULL,
};
// clang-format on

// clang-format off
static ClObjPipeData_c aSMAN_CoInfoData = {
    { 0x39, 0x20, ClObj_TYPE_PIPE },
    { 0x01 },
    { 5, 5, 0, { 0, 0, 0 } }
};
// clang-format on

// clang-format off
static StatusData_c aSMAN_StatusData = {
    0,
    5,
    5,
    0,
    196,
};
// clang-format on

static void aSMAN_process_normal_init(ACTOR* actorx);
static void aSMAN_process_combine_head_jump_init(ACTOR* actorx, GAME* game);
static void aSMAN_process_combine_body_init(ACTOR* actorx);
static void aSMAN_process_player_push_init(ACTOR* actorx, GAME* game);
static void aSMAN_process_air_init(ACTOR* actorx);
static void aSMAN_process_hole_init(ACTOR* actorx);
static void aSMAN_process_player_push_scroll_init(ACTOR* actorx);
static void aSMAN_process_swim_init(ACTOR* actorx);
static void aSMAN_process_combine_head_init(ACTOR* actorx);

static int aSMAN_process_normal(ACTOR* actorx, GAME* game);
static int aSMAN_process_player_push(ACTOR* actorx, GAME* game);
static int aSMAN_process_player_push_scroll(ACTOR* actorx, GAME* game);
static int aSMAN_process_combine_body(ACTOR* actorx, GAME* game);
static int aSMAN_process_combine_head_jump(ACTOR* actorx, GAME* game);
static int aSMAN_process_swim(ACTOR* actorx, GAME* game);
static int aSMAN_process_air(ACTOR* actorx, GAME* game);
static int aSMAN_process_hole(ACTOR* actorx, GAME* game);
static int aSMAN_process_combine_head(ACTOR* actorx, GAME* game);

static void aSMAN_actor_ct(ACTOR* actorx, GAME* game) {
    static int part_tbl[] = { aSMAN_PART0, aSMAN_PART1 };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (actorx->npc_id == ETC_SNOWMAN_BALL_A) {
        f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);

        if (move_dist != NULL) {
            actor->move_dist = *move_dist;
        } else {
            mEv_reserve_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
            actor->move_dist = 0.0f;
        }
    } else {
        f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);

        if (move_dist != NULL) {
            actor->move_dist = *move_dist;
        } else {
            mEv_reserve_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
            actor->move_dist = 0.0f;
        }
    }

    Shape_Info_init(actorx, 0.0f, mAc_ActorShadowEllipse, 10.0f, 10.0f);
    ClObjPipe_ct(game, &actor->col_pipe);
    ClObjPipe_set5(game, &actor->col_pipe, actorx, &aSMAN_CoInfoData);
    CollisionCheck_Status_set3(&actorx->status_data, &aSMAN_StatusData);
    actor->col_actor = NULL;
    actor->timer = 0;
    actor->snowman_part = part_tbl[actorx->npc_id != ETC_SNOWMAN_BALL_A];
    actorx->max_velocity_y = -30.0f;
    actorx->gravity = 0.8f;
    actorx->speed = 0.0f;
    actor->base_speed = 0.0f;
    actor->accel = 0.1f;
    actor->roll_speed = 0.0f;
    aSMAN_process_normal_init(actorx);
    actorx->scale.x = 0.01f;
    actorx->scale.y = 0.01f;
    actorx->scale.z = 0.01f;
}

static void aSNOWMAN_Set_PSnowman_info(SNOWMAN_ACTOR* actor) {
    mSN_snowman_info_c sman_info;

    xyz_t_move(&sman_info.pos, &actor->fg_pos);
    sman_info.data.exists = TRUE;
    sman_info.data.head_size = actor->normalized_scale * 255;
    sman_info.data.body_size = actor->body_scale * 255;
    sman_info.data.score = actor->result;
    mCoBG_SetPlussOffset(actor->actor_class.world.position, 0, mCoBG_ATTRIBUTE_NONE);
    if ((actor->flags & aSMAN_FLAG_DELETE) == 0) {
        mSN_regist_snowman_society(&sman_info);
    }
}

static void aSMAN_actor_dt(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    ClObjPipe_dt(game, &actor->col_pipe);
    if (actor->snowman_part == aSMAN_PART0) {
        if (actor->flags & aSMAN_FLAG_COMBINED) {
            if (actor->flags & aSMAN_FLAG_HEAD_JUMP) {
                if (actor->fg_pos.x != 0.0f || actor->fg_pos.z != 0.0f) {
                    aSNOWMAN_Set_PSnowman_info(actor);
                } else {
                    mCoBG_SetPlussOffset(actorx->world.position, 0, mCoBG_ATTRIBUTE_NONE);
                }
            }

            mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART0);
            mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
        } else {
            if ((actor->flags & aSMAN_FLAG_IN_HOLE) || (actor->flags & aSMAN_FLAG_MOVED) ||
                !mRlib_Set_Position_Check(actorx)) {
                mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART0);
                mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
            } else {
                f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);

                if (move_dist != NULL) {
                    *move_dist = actor->move_dist;
                }
            }
        }
    } else {
        if (actor->flags & aSMAN_FLAG_COMBINED) {
            if (actor->flags & aSMAN_FLAG_HEAD_JUMP) {
                if (actor->fg_pos.x != 0.0f || actor->fg_pos.z != 0.0f) {
                    aSNOWMAN_Set_PSnowman_info(actor);
                } else {
                    mCoBG_SetPlussOffset(actorx->world.position, 0, mCoBG_ATTRIBUTE_NONE);
                }
            }

            mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART1);
            mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
        } else {
            if ((actor->flags & aSMAN_FLAG_IN_HOLE) || (actor->flags & aSMAN_FLAG_MOVED) ||
                !mRlib_Set_Position_Check(actorx)) {
                mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART1);
                mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
            } else {
                f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);

                if (move_dist != NULL) {
                    *move_dist = actor->move_dist;
                }
            }
        }
    }

    mEv_actor_dying_message(mEv_EVENT_SNOWMAN_SEASON, actorx);
}

static void aSMAN_GetSnowmanPresentMail(Mail_c* mail) {
    PersonalID_c* pid = &Now_Private->player_ID;
    int mail_idx = 0x202;
    int rnd = RANDOM(12);
    mActor_name_t item;
    u8 item_name[mIN_ITEM_NAME_LEN];
    int header_back_start;
    // clang-format off
    static mActor_name_t snow_item_table[] = {
        FTR_START(FTR_KON_SNOWFREEZER),
        FTR_START(FTR_KON_SNOWTABLE),
        FTR_START(FTR_KON_SNOWBED),
        FTR_START(FTR_TAK_SNOWISU),
        FTR_START(FTR_TAK_SNOWLAMP),
        FTR_START(FTR_KON_SNOWSOFA),
        FTR_START(FTR_KON_SNOWTV),
        FTR_START(FTR_KON_SNOWTANSU),
        FTR_START(FTR_KON_SNOWBOX),
        FTR_START(FTR_KON_SNOWCLOCK),
        ITM_CARPET25,
        ITM_WALL25,
    };
    // clang-format on

    // one chance at a re-roll if the player already has the item
    if (mSP_CollectCheck(snow_item_table[rnd])) {
        rnd = RANDOM(12);
    }

    item = snow_item_table[rnd];
    mail_idx += rnd;
    mIN_copy_name_str(item_name, item);
    mHandbill_Set_free_str(mHandbill_FREE_STR0, item_name, sizeof(item_name));
    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body,
                                   mail_idx);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_SNOWMAN;
    mail->present = item;
    mail->content.paper_type = (u8)ITM_PAPER12;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
}

static void aSMAN_SendPresentMail(void) {
    Mail_c* mail = (Mail_c*)zelda_malloc(sizeof(Mail_c));

    if (!mLd_PlayerManKindCheck() && mail != NULL && mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(mail);
        aSMAN_GetSnowmanPresentMail(mail);
        mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
    }

    zelda_free(mail);
}

static int aSNOWMAN_player_block_check(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int pbx;
    int pbz;
    int bx;
    int bz;

    mFI_Wpos2BlockNum(&pbx, &pbz, playerx->world.position);
    mFI_Wpos2BlockNum(&bx, &bz, actorx->world.position);
    if (pbx == bx && pbz == bz) {
        return TRUE;
    }

    return FALSE;
}

static int aSMAN_FG_Position_Get(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    // clang-format off
    static xy_t chk_pos_tbl[] = {
        {                 0.0f,                  0.0f},
        { mFI_UNIT_BASE_SIZE_F,                  0.0f},
        {-mFI_UNIT_BASE_SIZE_F,                  0.0f},
        {                 0.0f,  mFI_UNIT_BASE_SIZE_F},
        {                 0.0f, -mFI_UNIT_BASE_SIZE_F},
        { mFI_UNIT_BASE_SIZE_F,  mFI_UNIT_BASE_SIZE_F},
        {-mFI_UNIT_BASE_SIZE_F,  mFI_UNIT_BASE_SIZE_F},
        { mFI_UNIT_BASE_SIZE_F, -mFI_UNIT_BASE_SIZE_F},
        {-mFI_UNIT_BASE_SIZE_F, -mFI_UNIT_BASE_SIZE_F},
    };
    // clang-format on
    int i;

    for (i = 0; i < ARRAY_COUNT(chk_pos_tbl); i++) {
        mActor_name_t item;
        u32 attr;
        xyz_t pos;
        f32 ground_y;

        pos = actorx->world.position;
        pos.x += chk_pos_tbl[i].x;
        pos.z += chk_pos_tbl[i].y;
        pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);
        // @optimization - function call inside of ABS macro...
        ground_y = ABS(pos.y - mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f));
        item =
            *mFI_GetUnitFG(pos); // @BUG - they don't check for NULL here, and mFI_GetUnitFG can return a NULL pointer.
        attr = mCoBG_Wpos2Attribute(pos, NULL);

        if (!mCoBG_ExistHeightGap_KeepAndNow(pos) && item != RSV_NO && item != RSV_WALL_NO &&
            attr != mCoBG_ATTRIBUTE_STONE && attr != mCoBG_ATTRIBUTE_WOOD && ground_y < 60.0f) {
            actor->fg_pos = pos;
            return TRUE;
        }
    }

    actor->fg_pos = ZeroVec;
    return FALSE;
}

static void aSMAN_House_Tree_Rev_Check(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (mRlib_HeightGapCheck_And_ReversePos(actorx) != TRUE) {
        actor->flags |= aSMAN_FLAG_MOVED;
        Actor_delete(actorx);
    }
}

static void aSMAN_Make_Effect_Ground(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (actor->normalized_scale < 0.2f) {
        return;
    }

    if ((game->frame_counter & 0xF) == 0 && actorx->bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_BUSH &&
        actorx->speed > 1.0f) {
        xyz_t pos = actorx->world.position;
        s16 arg;
        s16 angle;

        angle = DEG2SHORT_ANGLE2(45.0f + RANDOM_F(45.0f));
        if (game->frame_counter & 0x10) {
            angle = -angle;
        }

        arg = actorx->speed > 4.0f ? 1 : 0;
        pos.x += (actor->normalized_scale * 20.0f + 10.0f) * sin_s(angle);
        pos.z += (actor->normalized_scale * 20.0f + 10.0f) * cos_s(angle);
        pos.y -= (actor->normalized_scale * 20.0f + 10.0f);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, 1, actorx->world.angle.y, game, actorx->npc_id, 0, arg);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, 1, actorx->world.angle.y, game, actorx->npc_id, 0, 0);
    }
}

static void aSMAN_get_hole_offset(ACTOR* actorx, f32 hole_dist) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    static f32 small_offset = -875.0f;
    static f32 middle_offset = -750.0f;
    static f32 large_offset = -250.0f;
    f32 ofs;
    f32 rate;
    f32 clamped_rate;

    rate = (hole_dist * 2.0f) / mFI_UNIT_BASE_SIZE_F;
    clamped_rate = M_CLAMP(rate, 0.0f, 1.0f);

    if (actor->normalized_scale < 0.2f) {
        ofs = small_offset + actor->normalized_scale * 3.0f * (middle_offset - small_offset);
    } else {
        ofs = middle_offset + (actor->normalized_scale * 1.5f - 0.5f) * (large_offset - middle_offset);
    }

    ofs *= clamped_rate;
    add_calc(&actor->y_ofs, ofs, 1.0f - sqrtf(0.5f), 100.0f, 2.5f);
}

static int aSMAN_get_ground_norm(ACTOR* actorx, xyz_t* norm, xyz_t* pos) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    mCoBG_GetBgNorm_FromWpos(norm, *pos);
    if (Math3d_normalizeXyz_t(norm)) {
        f32 hole_dist;
        s16 norm_rate;
        s16 angle;

        if (mRlib_Get_ground_norm_inHole(actorx, norm, &hole_dist, &angle, &norm_rate,
                                         1.0f - actor->normalized_scale * 0.5f)) {
            aSMAN_get_hole_offset(actorx, hole_dist);
            if ((actor->flags & aSMAN_FLAG_IN_HOLE) == 0) {
                s16 angle_mod;
                f32 cos = cos_s(angle);
                f32 sin = sin_s(angle);
                f32 norm_f;

                angle_mod = norm_rate + (int)(actor->ground_angle.z * sin * sin + actor->ground_angle.x * cos * cos);
                norm_rate = (int)angle_mod;
                norm_rate = M_CLAMP((int)angle_mod, DEG2SHORT_ANGLE(90.0f), DEG2SHORT_ANGLE(-90.0f));

                if (actor->normalized_scale < 0.5f) {
                    actorx->position_speed.x *= 0.9f;
                    actorx->position_speed.z *= 0.9f;
                } else if (actor->ground_angle.x == 0 && actor->ground_angle.z == 0) {
                    actorx->position_speed.x *= 0.95f;
                    actorx->position_speed.z *= 0.95f;
                }

                norm_f = -cos_s(norm_rate);
                mRlib_spdF_Angle_to_spdXZ(norm, &norm_f, &angle);
                norm->y = sin_s(norm_rate);
                if (hole_dist < 1.0f) {
                    if (ABS(actorx->position_speed.x) < 1.0f && ABS(actorx->position_speed.z) < 1.0f) {
                        actor->flags |= aSMAN_FLAG_IN_HOLE;
                        actorx->state_bitfield &= ~ACTOR_STATE_NO_MOVE_WHILE_CULLED;
                        actorx->status_data.weight = MASSTYPE_HEAVY;
                        actorx->speed = 0.0f;
                    }
                }
            }
        } else {
            mRlib_Get_norm_Clif(actorx, norm);
            add_calc0(&actor->y_ofs, 1.0f - sqrtf(0.5f), 50.0f);
        }

        return TRUE;
    }

    return FALSE;
}

static void aSMAN_player_push_free(GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    playerx->speed = 0.0f;
    mPlib_request_main_push_snowball_end_type1(game);
}

static int aSMAN_player_push_HitWallCheck(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    u32 hit_wall = playerx->bg_collision_check.result.hit_wall;
    u32 hit_attr_wall = playerx->bg_collision_check.result.hit_attribute_wall;
    s16 wall_angle;
    s16 dAngle;

    if ((hit_wall & mCoBG_HIT_WALL) || (hit_attr_wall & mCoBG_HIT_WALL)) {
        wall_angle = mRlib_Get_HitWallAngleY(actorx);
        dAngle = (wall_angle - playerx->world.angle.y) + DEG2SHORT_ANGLE2(180.0f);
        if (ABS(dAngle) > DEG2SHORT_ANGLE2(45.0f)) {
            return TRUE;
        }
    }

    return FALSE;
}

static s16 aSMAN_get_norm_push_angle_distance(ACTOR* actorx, xyz_t* norm, s16 push_angle) {
    s16 norm_angle;

    mCoBG_GetBgNorm_FromWpos(norm, actorx->world.position);
    norm_angle = atans_table(norm->z, norm->x);
    return norm_angle - push_angle;
}

static void aSMAN_player_push_scroll_request(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int dir;
    xyz_t snowball_ofs;
    xyz_t rev;

    rev = mCoBG_UniqueWallCheck(playerx, 18.0f, 0.0f);
    dir = mPlib_CheckCondition_forWadeSnowball(&playerx->world.position, playerx->world.angle.y);
    if (dir != mFI_MOVEDIR_NONE) {
        xyz_t_sub(&actorx->world.position, &playerx->world.position, &snowball_ofs);
        mPlib_Set_ScrollDemo_forWade_snowball(dir, &snowball_ofs);
    } else if (!F32_IS_ZERO(rev.x) || !F32_IS_ZERO(rev.z)) {
        aSMAN_player_push_free(game);
        aSMAN_process_normal_init(actorx);
    }
}

static void aSMAN_set_speed_relations_norm_player_push(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    s16 dAngle = ABS(actorx->world.angle.y - playerx->world.angle.y);
    xyz_t norm;

    if (aSMAN_get_ground_norm(actorx, &norm, &actorx->world.position) &&
        (!F32_IS_ZERO(norm.x) || !F32_IS_ZERO(norm.z))) {
        if (dAngle < DEG2SHORT_ANGLE2(90.0f)) {
            f32 accel = 0.3f + actor->normalized_scale * 0.099999994f;
            f32 norm_speed;

            accel *= 0.2f;
            actorx->position_speed.x += norm.x * accel;
            actorx->position_speed.z += norm.z * accel;
            mRlib_spdXZ_to_spdF_Angle(&actorx->position_speed, &norm_speed, &actorx->world.angle.y);
            actor->base_speed =
                norm_speed + (actor->normalized_scale * 0.02f + 0.01f) * (actor->base_speed - norm_speed);
        } else if (actorx->speed > 0.5f) {
            actor->base_speed = 0.0f;
            actor->accel = 0.0f;
        }
    }
}

static ACTOR* aSMAN_get_oc_actor(SNOWMAN_ACTOR* actor) {
    if (ClObj_DID_COLLIDE(actor->col_pipe.collision_obj)) {
        ACTOR* oc_actor = actor->col_pipe.collision_obj.collided_actor;

        if (oc_actor != NULL) {
            return oc_actor;
        }
    }

    return NULL;
}

static void aSMAN_MakeBreakEffect(SNOWMAN_ACTOR* actor, GAME* game) {
    xyz_t pos = actor->actor_class.world.position;
    s16 arg = (s16)(actor->normalized_scale * 100.0f);

    pos.y -= actor->normalized_scale * 20.0f + 10.0f;
    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDARUMA, pos, 1, 0, game, actor->actor_class.npc_id, arg, 0);
    sAdo_OngenTrgStart(0x143, &actor->actor_class.world.position);
}

static int aSMAN_status_check_in_move(SNOWMAN_ACTOR* actor, GAME* game) {
    int ret = FALSE;

    if ((actor->flags & aSMAN_FLAG_ON_GROUND) != 0 && (actor->flags & aSMAN_FLAG_COMBINED) == 0) {
        actor->flags |= aSMAN_FLAG_MOVED;
        aSMAN_MakeBreakEffect(actor, game);
        Actor_delete((ACTOR*)actor);
        ret = TRUE;
    }

    if (actor->flags & aSMAN_FLAG_COMBINED) {
        ret = TRUE;
    }

    if (actor->flags & aSMAN_FLAG_IN_HOLE) {
        ret = TRUE;
    }

    if (ret == TRUE &&
        (actor->process == aSMAN_process_player_push || actor->process == aSMAN_process_player_push_scroll)) {
        aSMAN_player_push_free(game);
    }

    return ret;
}

static void aSMAN_position_move(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    mCoBG_GetBgY_AngleS_FromWpos(&actor->ground_angle, actorx->world.position, 0.0f);
    chase_f(&actorx->speed, actor->base_speed, actor->accel);

    if ((actor->flags & aSMAN_FLAG_COMBINED) != 0 || (actor->flags & aSMAN_FLAG_IN_HOLE) != 0 ||
        actor->process == aSMAN_process_combine_body || actor->process == aSMAN_process_player_push_scroll) {
        return;
    }

    Actor_position_speed_set(actorx);
    mRlib_position_move_for_sloop(actorx, &actor->ground_angle);
}

static int aSMAN_BGcheck(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    f32 r = actor->normalized_scale * 20.0f + 10.0f;

    if ((actor->flags & aSMAN_FLAG_COMBINED) != 0 || actor->process == aSMAN_process_combine_head_jump ||
        actor->process == aSMAN_process_combine_body) {
        return FALSE;
    }

    if (actor->process == aSMAN_process_swim) {
        mCoBG_BgCheckControll(&actor->rev_pos, actorx, r, -r, mCoBG_WALL_TYPE0, mCoBG_REVERSE_TYPE_NO_REVERSE,
                              mCoBG_CHECK_TYPE_NORMAL);
        actorx->world.position.x += actor->rev_pos.x;
        actorx->world.position.z += actor->rev_pos.z;
    } else {
        mCoBG_BgCheckControll(&actor->rev_pos, actorx, r, -r, mCoBG_WALL_TYPE0, mCoBG_REVERSE_TYPE_REVERSE,
                              mCoBG_CHECK_TYPE_NORMAL);
        mRlib_Station_step_modify_to_wall(actorx);

        if (actorx->world.position.y - actorx->last_world_position.y > 60.0f) {
            actorx->world.position = actorx->last_world_position;
            actor->flags |= aSMAN_FLAG_MOVED;
            actor->flags |= aSMAN_FLAG_ON_GROUND;
            return FALSE;
        }
    }

    if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL) != 0) {
        s16 angle = mRlib_Get_HitWallAngleY(actorx);
        s16 colAngle = (angle - DEG2SHORT_ANGLE2(90.0f)) - actorx->world.angle.y;
        int diff;
        f32 speed = actorx->speed * sin_s(colAngle);

        if (ABS(speed) > 5.0f) {
            actor->flags |= aSMAN_FLAG_MOVED;
            actor->flags |= aSMAN_FLAG_ON_GROUND;
            return FALSE;
        }

        diff = actorx->world.angle.y - (angle - DEG2SHORT_ANGLE2(-180.0f));
        if (speed > 0.0f) {
            f32 speed2 = actorx->speed * cos_s(colAngle);

            actorx->world.angle.y = angle - diff;
            speed *= 0.7f;
            actorx->speed = sqrtf(SQ(speed) + SQ(speed2));

            if (actor->process != aSMAN_process_player_push && !actorx->bg_collision_check.result.is_in_water &&
                actorx->speed > 0.5f) {
                sAdo_OngenTrgStartSpeed(actorx->speed, 0x103, &actorx->world.position);
            }
        } else {
            if (actor->process == aSMAN_process_air) {
                sAdo_OngenTrgStartSpeed(actorx->speed, 0x103, &actorx->world.position);
                actorx->world.angle.y = angle;
                actorx->speed *= 1.2f;
                actorx->position_speed.y = 0.0f;
            }
        }

        mRlib_spdF_Angle_to_spdXZ(&actorx->position_speed, &actorx->speed, &actorx->world.angle.y);
    }

    return TRUE;
}

static int aSMAN_snowman_hit_check(SNOWMAN_ACTOR* actor, GAME* game, ACTOR* oc_actorx) {
    int b_ux;
    int b_uz;

    actor->col_actor = oc_actorx;
    if (oc_actorx->id == mAc_PROFILE_SNOWMAN) {
        SNOWMAN_ACTOR* oc_actor = (SNOWMAN_ACTOR*)oc_actorx;
        u32 attr;
        xyz_t center_pos;

        if ((F32_IS_ZERO(actor->actor_class.speed) && F32_IS_ZERO(oc_actorx->speed))) {
            return FALSE;
        }

        if (actor->actor_class.speed >= oc_actorx->speed) {
            mFI_Wpos2UtCenterWpos(&center_pos, oc_actorx->world.position);
        } else {
            mFI_Wpos2UtCenterWpos(&center_pos, actor->actor_class.world.position);
        }

        attr = mCoBG_Wpos2Attribute(center_pos, NULL);
        mFI_Wpos2UtNum_inBlock(&b_ux, &b_uz, center_pos);
        if (attr == mCoBG_ATTRIBUTE_STONE || attr == mCoBG_ATTRIBUTE_WOOD ||
            mCoBG_Wpos2CheckSlateCol(&center_pos, FALSE) || b_ux == 0 || b_ux == (UT_X_NUM - 1) || b_uz == 0 ||
            b_uz == (UT_Z_NUM - 1) || (oc_actor->flags & aSMAN_FLAG_IN_HOLE) != 0 || oc_actor->ground_angle.x != 0 ||
            oc_actor->ground_angle.z != 0 || !aSNOWMAN_player_block_check((ACTOR*)actor, game)) {
            return FALSE;
        }

        if (actor->snowman_part != oc_actor->snowman_part && actor->normalized_scale > 0.2f &&
            oc_actor->normalized_scale > 0.2f) {
            actor->actor_class.status_data.weight = MASSTYPE_HEAVY;
            oc_actorx->status_data.weight = MASSTYPE_HEAVY;

            if (oc_actor->process == aSMAN_process_player_push || actor->process == aSMAN_process_player_push) {
                aSMAN_player_push_free(game);
            }

            if (actor->actor_class.speed >= oc_actorx->speed) {
                oc_actor->col_actor = (ACTOR*)actor;
                aSMAN_process_combine_head_jump_init((ACTOR*)actor, game);
                aSMAN_process_combine_body_init(oc_actorx);
            } else {
                oc_actor->col_actor = (ACTOR*)actor;
                aSMAN_process_combine_body_init((ACTOR*)actor);
                aSMAN_process_combine_head_jump_init(oc_actorx, game);
            }

            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}

static void aSMAN_OBJcheck(SNOWMAN_ACTOR* actor, GAME* game) {
    if ((actor->flags & aSMAN_FLAG_COMBINED) != 0) {
        return;
    }

    if (ClObj_DID_COLLIDE(actor->col_pipe.collision_obj)) {
        ACTOR* oc_actorx = actor->col_pipe.collision_obj.collided_actor;

        actor->col_pipe.collision_obj.collision_flags0 &= ~ClObj_FLAG_COLLIDED;
        if (oc_actorx != NULL) {
            xyz_t tmp;

            if (actor->col_actor != oc_actorx && !aSMAN_snowman_hit_check(actor, game, oc_actorx)) {
                f32 rate = (1.0f - actor->normalized_scale) * 0.4f;

                tmp = oc_actorx->position_speed;
                xyz_t_mult_v(&tmp, rate);
                if (oc_actorx->speed > 0.5f) {
                    sAdo_OngenTrgStartSpeed(oc_actorx->speed, 0x102, &actor->actor_class.world.position);
                }
            } else {
                f32 add = 0.16f - actor->normalized_scale * 0.14f;
                s16 angle = oc_actorx->world.angle.y;

                if (actor->normalized_scale > 0.2f) {
                    add *= 0.2f;
                }

                mRlib_spdF_Angle_to_spdXZ(&tmp, &add, &angle);
                tmp.y = 0.0f;
            }

            if (tmp.x * (actor->actor_class.world.position.x - oc_actorx->world.position.x) > 0.0f) {
                actor->actor_class.position_speed.x += tmp.x;
            }

            if (tmp.z * (actor->actor_class.world.position.z - oc_actorx->world.position.z) > 0.0f) {
                actor->actor_class.position_speed.z += tmp.z;
            }
        } else {
            actor->col_actor = NULL;
        }
    } else {
        actor->col_actor = NULL;
    }
}

static void aSMAN_set_speed_relations_norm(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    xyz_t norm;

    if (aSMAN_get_ground_norm(actorx, &norm, &actorx->world.position) &&
        (!F32_IS_ZERO(norm.x) || !F32_IS_ZERO(norm.z))) {
        f32 vel = actor->normalized_scale * 0.099999994f + 0.3f;

        actorx->position_speed.x += norm.x * vel;
        actorx->position_speed.z += norm.z * vel;
        actorx->world.angle.y = atans_table(actorx->position_speed.z, actorx->position_speed.x);
        actor->base_speed = fsqrt(SQ(actorx->position_speed.z) + SQ(actorx->position_speed.x));
        actor->accel = 0.0f;
    } else {
        actor->base_speed = 0.0f;
        actor->accel = 0.1f - actor->normalized_scale * 0.05f;
    }

    actorx->max_velocity_y = -30.0f;
    actorx->gravity = 0.8f;
    actor->roll_speed = actorx->speed;
}

static void aSMAN_set_speed_relations_swim(ACTOR* actorx) {
    static s16 angl_add_table[] = { DEG2SHORT_ANGLE2(1.40625f), DEG2SHORT_ANGLE2(5.625f) };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    xyz_t flow;
    s16 flow_angle;
    f32 water_height;

    water_height = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 1362);
    mCoBG_GetWaterFlow(&flow, actorx->bg_collision_check.result.unit_attribute);
    flow_angle = atans_table(flow.z, flow.x);
    chase_angle(&actorx->world.angle.y, flow_angle,
                angl_add_table[ABS(DIFF_SHORT_ANGLE(actorx->world.angle.y, flow_angle)) > DEG2SHORT_ANGLE2(90.0f)]);
    if (actorx->world.position.y < water_height) {
        actorx->max_velocity_y = 1.0f;
    } else {
        actorx->max_velocity_y = -1.0f;
    }

    actorx->gravity = 0.1f;
    actor->base_speed = 1.0f;
    actor->accel = 0.1f;
    add_calc0(&actor->roll_speed, 1.0f - sqrtf(0.5f), 0.25f);
}

static void aSMAN_calc_axis(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (!F32_IS_ZERO(actor->roll_speed) && actor->process != aSMAN_process_player_push_scroll) {
        s16 dAngle = (s16)(actor->roll_speed *
                           (DEG2SHORT_ANGLE3(180.0f) / (((actor->normalized_scale * 20.0f + 10.0f) * 2.0f) * 3.14f)));

        if (actor->process == aSMAN_process_swim) {
            f32 rate = (-1.0f - actorx->position_speed.y) / -2.0f;
            dAngle *= rate;
        }

        mRlib_Roll_Matrix_to_s_xyz(actorx, &actor->head_vec, dAngle);
    }
}

static void aSMAN_calc_scale(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    f32 scale;
    u32 attr = mCoBG_Wpos2Attribute(actorx->world.position, NULL);

    if (attr <= mCoBG_ATTRIBUTE_GRASS3) {
        actor->move_dist += actorx->speed;
    } else {
        actor->move_dist -= actorx->speed * 0.75f;
    }

    if (actor->move_dist > aSMAN_MOVE_DIST_MAX) {
        actor->move_dist = aSMAN_MOVE_DIST_MAX;
    } else if (actor->move_dist < 0.0f) {
        actor->move_dist = 0.0f;
    }

    actor->normalized_scale = actor->move_dist / aSMAN_MOVE_DIST_MAX;
    scale = actor->normalized_scale * 0.02f + 0.01f;

    if (scale > 0.03f) {
        scale = 0.03f;
    }

    actorx->scale.x = actorx->scale.y = actorx->scale.z = scale;
    actorx->shape_info.shadow_size_x = actorx->shape_info.shadow_size_z = actor->normalized_scale * 20.0f + 10.0f;
}

static void aSMAN_calc_objChkRange(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actor->col_pipe.attribute.pipe.height = (actor->normalized_scale * 15.0f + 5.0f) * 2.5f;
    actor->col_pipe.attribute.pipe.offset = -(actor->normalized_scale * 15.0f + 5.0f);

    if ((actor->flags & aSMAN_FLAG_IN_HOLE) != 0) {
        actor->col_pipe.attribute.pipe.radius = 20;
        actorx->status_data.weight = MASSTYPE_HEAVY;
    } else if (actor->process == aSMAN_process_combine_body && (actor->flags & aSMAN_FLAG_COMBINED) == 0) {
        actor->col_pipe.attribute.pipe.radius = 20;
    } else {
        actor->col_pipe.attribute.pipe.radius = actor->normalized_scale * 15.0f + 5.0f;
        actorx->status_data.weight = MIN(actor->normalized_scale * 375.0f, 250.0f);
    }
}

static int aSMAN_Player_push_Request(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    f32 dist = actorx->player_distance_xz;
    f32 y = actorx->world.position.y - playerx->world.position.y - (actor->normalized_scale * 20.0f + 10.0f);
    f32 move_pR = gamePT->mcon.move_pR;
    s16 player_angle = search_position_angleY(&playerx->world.position, &actorx->world.position);
    s16 move_angle = gamePT->mcon.move_angle + DEG2SHORT_ANGLE2(90.0f);
    s16 diff_angle = DIFF_SHORT_ANGLE(move_angle, player_angle);

    if (mPlib_Check_Label_main_push_snowball(actorx)) {
        aSMAN_process_player_push_init(actorx, game);
        return TRUE;
    }

    if ((actor->flags & aSMAN_FLAG_IN_HOLE) != 0) {
        aSMAN_process_hole_init(actorx);
        return FALSE;
    }

    if (!actorx->bg_collision_check.result.on_ground) {
        aSMAN_process_air_init(actorx);
        return FALSE;
    }

    if (actor->normalized_scale > 0.2f && dist < (actor->normalized_scale * 20.0f + 10.0f) + 15.0f) {
        int timer = actor->timer;

        if (timer >= 16) {
            timer = 16;
        } else {
            actor->timer++;
        }

        if (timer == 16 && y > -10.0f && y < 25.0f && move_pR > 0.0f && actorx->speed < 3.0f) {
            if (ABS(diff_angle) < DEG2SHORT_ANGLE2(55.0f)) {
                mPlib_request_main_push_snowball_type1(game, actorx);
            }
        }
    }

    return FALSE;
}

static void aSMAN_process_normal_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actor->timer = 0;
    actor->accel = 0.1f;
    actor->process = aSMAN_process_normal;
}

static int aSMAN_process_normal(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (aSMAN_Player_push_Request(actorx, game)) {
        return FALSE;
    }

    aSMAN_set_speed_relations_norm(actorx);
    aSMAN_Make_Effect_Ground(actorx, game);
    aSMAN_OBJcheck(actor, game);
    aSMAN_House_Tree_Rev_Check(actorx);
    mRlib_spdXZ_to_spdF_Angle(&actorx->position_speed, &actorx->speed, &actorx->world.angle.y);
    aSMAN_calc_scale(actorx);
    return TRUE;
}

static void aSMAN_process_player_push_init(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    f32 rate;
    f32 speed;

    speed = playerx->speed / 7.5f;
    rate = 3.0f - actor->normalized_scale * 1.5f;
    if (actor->process != aSMAN_process_player_push_scroll) {
        actorx->speed = (1.0f - actor->normalized_scale) * (rate * speed) * 1.15f;
        actor->accel = 0.0f;
    }

    actor->timer = 0;
    actor->process = aSMAN_process_player_push;
}

static int aSMAN_process_player_push(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    ACTOR* oc_actorx = aSMAN_get_oc_actor(actor);
    s16 player_angle = search_position_angleY(&playerx->world.position, &actorx->world.position);
    s16 move_angle = gamePT->mcon.move_angle + DEG2SHORT_ANGLE2(90.0f);
    s16 diff_angle = DIFF_SHORT_ANGLE(move_angle, player_angle);
    f32 move_pR = gamePT->mcon.move_pR;

    add_calc0(&actor->y_ofs, 1.0f - sqrtf(0.5f), 50.0f);
    add_calc(&actor->accel, 0.1f, 1.0f - sqrtf(0.8f), 0.005f, 0.0005f);

    if (oc_actorx != NULL && aSMAN_snowman_hit_check(actor, game, oc_actorx) == TRUE) {
        return FALSE;
    }

    if (mPlib_Check_Label_main_wade_snowball(actorx)) {
        aSMAN_process_player_push_scroll_init(actorx);
    } else if (!mPlib_Check_Label_main_push_snowball(actorx)) {
        aSMAN_process_normal_init(actorx);
        return FALSE;
    } else {
        xyz_t norm;
        s16 norm_angle_diff = aSMAN_get_norm_push_angle_distance(actorx, &norm, player_angle);

        {
            if ((ABS(diff_angle) > DEG2SHORT_ANGLE2(55.0f) || actor->normalized_scale <= 0.2f ||
                 aSMAN_player_push_HitWallCheck(actorx, game)) ||
                (((!F32_IS_ZERO(norm.x) || !F32_IS_ZERO(norm.z)) && ABS(norm_angle_diff) < DEG2SHORT_ANGLE2(120.0f)) ||
                 move_pR == 0.0f)) {
                aSMAN_player_push_free(game);
                aSMAN_process_normal_init(actorx);
                return FALSE;
            } else {
                xyz_t aim_pos = playerx->world.position;
                f32 dist;
                f32 speed;
                s16 player_angle_y;

                speed = (actor->normalized_scale * 20.0f + 10.0f) + 10.0f;
                player_angle_y = playerx->shape_info.rotation.y;
                actor->base_speed = move_pR * (3.0f - actor->normalized_scale * 1.5f) * cos_s(diff_angle);
                if (mPlib_CheckButtonOnly_forDush()) {
                    actor->base_speed *= 1.5f;
                }
                actorx->world.angle.y = move_angle;
                mRlib_spdF_Angle_to_spdXZ(&actorx->position_speed, &actorx->speed, &actorx->world.angle.y);
                aSMAN_set_speed_relations_norm_player_push(actorx, game);
                mRlib_spdF_Angle_to_spdXZ(&aim_pos, &speed, &player_angle);
                xyz_t_sub(&actorx->world.position, &aim_pos, &aim_pos);
                aim_pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, aim_pos, 0.0f);

                add_calc_short_angle2(&player_angle_y, player_angle, CALC_EASE2(0.5f), 455, 45);
                dist = search_position_distanceXZ(&actorx->world.position, &actorx->last_world_position);
                dist *= 0.4f;
                mPlib_SetParam_for_push_snowball(&aim_pos, player_angle_y, dist < 1.0f ? dist : 1.0f);

                mCoBG_BgCheckControll(NULL, playerx, 18.0f, 0.0f, mCoBG_WALL_TYPE1, mCoBG_REVERSE_TYPE_REVERSE,
                                      mCoBG_CHECK_TYPE_PLAYER);
                if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL) != 0) {
                    s16 wall_angle = mRlib_Get_HitWallAngleY(actorx);
                    s16 wall_angle_diff =
                        DIFF_SHORT_ANGLE(wall_angle - actorx->world.angle.y, DEG2SHORT_ANGLE(-180.0f));

                    if (wall_angle_diff < DEG2SHORT_ANGLE2(20.0f) && move_pR * cos_s(wall_angle_diff) > 0.7f) {
                        actor->timer++;
                        if (actor->timer > 120) {
                            actor->flags |= aSMAN_FLAG_MOVED;
                            actor->flags |= aSMAN_FLAG_ON_GROUND;
                        }
                    } else {
                        actor->timer = 0;
                    }
                } else {
                    actor->timer = 0;
                }

                aSMAN_Make_Effect_Ground(actorx, game);
                if (actorx->speed > 1.0f) {
                    sAdo_OngenPos((uintptr_t)actorx, 52, &actorx->world.position);
                }
                aSMAN_player_push_scroll_request(actorx, game);
            }
        }
    }

    if (!actorx->bg_collision_check.result.on_ground) {
        aSMAN_process_air_init(actorx);
        aSMAN_player_push_free(game);
    }

    actor->roll_speed = actorx->speed;
    aSMAN_calc_scale(actorx);
    return TRUE;
}

static void aSMAN_process_player_push_scroll_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actor->process = aSMAN_process_player_push_scroll;
}

static int aSMAN_process_player_push_scroll(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (!mPlib_Check_Label_main_wade_snowball(actorx)) {
        aSMAN_process_player_push_init(actorx, game);
    } else {
        xyz_t pos;
        f32 rev_x = actor->rev_pos.x;
        f32 rev_z = actor->rev_pos.z;
        f32 rev_xz = sqrtf(SQ(rev_x) + SQ(rev_z));

        mPlib_GetSnowballPos_forWadeSnowball(&pos);
        actorx->world.position = pos;
        if ((actor->flags & aSMAN_FLAG_ON_GROUND) != 0 || rev_xz > (actor->normalized_scale * 20.0f + 10.0f) * 0.5f) {
            actor->flags |= aSMAN_FLAG_MOVED;
            actor->flags |= aSMAN_FLAG_ON_GROUND;
            mPlib_Set_crash_snowball_for_wade(TRUE);
            return FALSE;
        }
    }

    return TRUE;
}

static void aSMAN_process_swim_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actorx->shape_info.draw_shadow = FALSE;
    actor->timer = 0;
    actor->flags |= aSMAN_FLAG_MOVED;
    actor->process = aSMAN_process_swim;
}

static int aSMAN_process_swim(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    aSMAN_set_speed_relations_swim(actorx);
    if (actorx->scale.x < 0.001f) {
        Actor_delete(actorx);
        return FALSE;
    }

    xyz_t_mult_v(&actorx->scale, 0.999f);
    actor->normalized_scale = (actorx->scale.x - 0.01f) / 0.02f;
    if (actorx->scale.x >= 0.01f) {
        if (CLIP(gyo_clip) != NULL) {
            CLIP(gyo_clip)->ballcheck_gyoei_proc(&actorx->world.position, (actorx->scale.x * 30.0f) / 0.03f,
                                                 aGYO_BALLCHECK_TYPE_SNOWMAN);
        }
    }

    if (!actorx->bg_collision_check.result.is_in_water &&
        actorx->bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_WATERFALL) {
        aSMAN_process_air_init(actorx);
    }

    if (actor->timer < 32) {
        if (((game->frame_counter & 3) == 0 && actor->timer < 16) || (game->frame_counter & 7) == 0) {
            xyz_t pos = actorx->world.position;
            pos.y = mCoBG_GetWaterHeight_File(pos, __FILE__, 1855);
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, actorx->world.angle.y, game, actorx->npc_id, 5,
                                       (s16)(actor->normalized_scale * 100.0f));
        }

        actor->timer++;
    }

    return TRUE;
}

static void aSMAN_process_air_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    f32 bg_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f);
    f32 min_speed = (actor->normalized_scale * 20.0f + 10.0f) * 0.1f;

    if (actorx->world.position.y - bg_y > 20.0f) {
        sAdo_OngenTrgStart(0x43D, &actorx->world.position);
    }

    actor->fall_height = actorx->world.position.y;
    actorx->gravity = 0.8f;
    actorx->max_velocity_y = -30.0f;
    if (actorx->speed < min_speed) {
        actorx->speed = min_speed;
    }
    actorx->position_speed.y = 3.2f;
    actor->process = aSMAN_process_air;
}

static int aSMAN_process_air(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    add_calc0(&actor->y_ofs, CALC_EASE(0.5f), 50.0f);
    if (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL) {
        s16 wall_angle = mRlib_Get_HitWallAngleY(actorx);

        add_calc_short_angle2(&actorx->world.angle.y, wall_angle, CALC_EASE2(0.2f), DEG2SHORT_ANGLE2(22.5f), 45);
        add_calc(&actorx->speed, 3.0f, CALC_EASE(0.5f), 0.25f, 0.05f);
    }

    if (actorx->bg_collision_check.result.is_in_water) {
        xyz_t pos = actorx->world.position;

        pos.y = mCoBG_GetWaterHeight_File(pos, __FILE__, 1934);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_AMI_MIZU, pos, 1, 0, game, actorx->npc_id, 2,
                                   (s16)(actor->normalized_scale * 100.0f));
        if (CLIP(gyo_clip) != NULL) {
            CLIP(gyo_clip)->ballcheck_gyoei_proc(&actorx->world.position, (actorx->scale.x * 30.0f) / 0.03f,
                                                 aGYO_BALLCHECK_TYPE_NORMAL);
        }

        sAdo_OngenTrgStart(NA_SE_27, &actorx->world.position);
        aSMAN_process_swim_init(actorx);
    } else if (actorx->bg_collision_check.result.on_ground) {
        if (actor->fall_height - actorx->world.position.y >= 55.0f ||
            mCoBG_ExistHeightGap_KeepAndNow_Detail(actorx->world.position)) {
            actor->flags |= aSMAN_FLAG_MOVED;
            actor->flags |= aSMAN_FLAG_ON_GROUND;
        } else {
            aSMAN_process_normal_init(actorx);
        }
    }

    return TRUE;
}

static void aSMAN_process_hole_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actorx->gravity = 0.0f;
    actorx->speed = 0.0f;
    actor->roll_speed = 0.0f;
    actor->accel = 0.1f;
    actor->base_speed = 0.0f;
    actor->process = aSMAN_process_hole;
}

static int aSMAN_process_hole(ACTOR* actorx, GAME* game) {
    return TRUE;
}

static int aSMAN_decide_scale_result(f32 head_scale, f32 body_scale) {
    f32 ratio = head_scale / body_scale;
    f32 adjusted_ratio = ABS(ratio - 0.85f);
    int result;

    if (adjusted_ratio <= 0.05f) { // [0%, 5%] margin = perfect
        result = mSN_RESULT_PERFECT;
    } else if (adjusted_ratio <= 0.15f) { // (5%, 15%] margin = good
        result = mSN_RESULT_GOOD;
    } else if (adjusted_ratio <= 0.25f) { // (15%, 25%] margin = okay
        result = mSN_RESULT_OK;
    } else { // anything larger = bad
        result = mSN_RESULT_BAD;
    }

    return result;
}

static int aSMAN_get_snowman_indx(void) {
    mSN_snowman_data_c* snowman_p = Save_Get(snowmen).snowmen_data;
    int i;

    for (i = 0; i < mSN_SAVE_COUNT; i++) {
        if (!snowman_p->exists) {
            return i;
        }

        snowman_p++;
    }

    return -1;
}

static void aSMAN_process_combine_head_jump_init(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* oc_actorx = actor->col_actor;
    SNOWMAN_ACTOR* oc_actor = (SNOWMAN_ACTOR*)oc_actorx;
    xyz_t oc_pos = oc_actorx->world.position;
    xyz_t pos;
    f32 height = (actor->normalized_scale * 20.0f + 10.0f) + (oc_actor->normalized_scale * 20.0f + 10.0f);

    mPlib_request_main_demo_wait_type1(game, FALSE, actorx);
    actor->flags |= aSMAN_FLAG_COMBINED;
    actor->flags |= aSMAN_FLAG_HEAD_JUMP;
    actor->timer = 0;
    actorx->parent_actor = oc_actorx;
    actor->roll_speed = 0.0f;
    mFI_Wpos2UtCenterWpos(&pos, oc_pos);
    oc_pos.y += height * 0.6f;
    oc_pos.x = pos.x;
    oc_pos.z = pos.z;
    xyz_t_sub(&actorx->world.position, &oc_pos, &actor->combine_dist);
    xyz_t_mult_v(&actor->combine_dist, 1.0f / 60.0f);
    actorx->shape_info.draw_shadow = FALSE;
    actor->result = aSMAN_decide_scale_result(actorx->scale.x, oc_actorx->scale.x);
    actor->msg_no =
        MSG_2209 + ((Common_Get(snowman_msg_id) + aSMAN_get_snowman_indx()) % mSN_SAVE_COUNT) + actor->result * 3;
    actor->body_scale = oc_actor->normalized_scale;

    if (actor->result == mSN_RESULT_PERFECT) {
        aSMAN_SendPresentMail();
    }

    Save_Set(snowman_year, Common_Get(time.rtc_time.year) % 100);
    Save_Set(snowman_month, Common_Get(time.rtc_time.month));
    Save_Set(snowman_day, Common_Get(time.rtc_time.day));
    Save_Set(snowman_hour, Common_Get(time.rtc_time.hour));

    mQst_NextSnowman(actorx->world.position);
    sAdo_OngenTrgStart(NA_SE_104, &actorx->world.position);
    actor->process = aSMAN_process_combine_head_jump;
}

static int aSMAN_process_combine_head_jump(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (actor->timer == 0 && mPlib_check_label_player_demo_wait(game, actorx)) {
        mPlib_Set_able_force_speak_label(actorx);
    }

    if (actor->timer == 60) {
        int i;
        s16 angle = DEG2SHORT_ANGLE2(-90.0f);
        xyz_t pos = actorx->world.position;

        pos.y -= (actor->normalized_scale * 20.0f + 10.0f) * 0.7f;
        for (i = 0; i < 5; i++) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, 1, angle, game, actorx->npc_id, 0, 9);
            angle += DEG2SHORT_ANGLE2(45.0f);
        }
        actorx->shape_info.ofs_y = 0.0f;
        aSMAN_FG_Position_Get(actorx);
        aSMAN_process_combine_head_init(actorx);
        return FALSE;
    } else {
        xyz_t_sub(&actorx->world.position, &actor->combine_dist, &actorx->world.position);
        actorx->shape_info.ofs_y = (actor->timer * 8.0f + actor->timer * -(1.0f / 7.5f) * actor->timer) * 25.0f;
        add_calc_short_angle2(&actor->head_vec.x, 0, CALC_EASE(0.5f), DEG2SHORT_ANGLE2(22.5f), 91);
        add_calc_short_angle2(&actor->head_vec.y, 0, CALC_EASE(0.5f), DEG2SHORT_ANGLE2(22.5f), 91);
        add_calc_short_angle2(&actor->head_vec.z, 0, CALC_EASE(0.5f), DEG2SHORT_ANGLE2(22.5f), 91);
        actor->timer++;
        return TRUE;
    }
}

static void aSMAN_set_talk_info_combine_head_init(ACTOR* actorx) {
    static int base_msg_no[] = { MSG_2197, MSG_2200, MSG_2203, MSG_2206 };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    actor->head_vec = ZeroSVec;
    mDemo_Set_msg_num(base_msg_no[actor->result] + RANDOM(3));
    mDemo_Set_talk_turn(TRUE);
}

static void aSMAN_set_talk_info_normal_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    mDemo_Set_msg_num(actor->msg_no);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mPlib_Set_able_hand_all_item_in_demo(FALSE);
}

static void aSMAN_process_combine_head_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* parentx = actorx->parent_actor;
    SNOWMAN_ACTOR* parent = (SNOWMAN_ACTOR*)parentx;
    f32 ofs_y;
    f32 ofs;

    ofs_y = ((actor->normalized_scale * 20.0f + 10.0f) + (parent->normalized_scale * 20.0f + 10.0f));
    ofs_y *= 0.6f;
    actor->timer = 0;
    ofs = ((actorx->scale.y + actorx->parent_actor->scale.y) * 10.0f);
    Actor_world_to_eye(actorx, (ofs * 0.8f) * 100.0f);
    actorx->world.position.x = parentx->world.position.x;
    actorx->world.position.z = parentx->world.position.z;
    actorx->world.position.y = parentx->world.position.y + ofs_y;
    actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(-17.578125f);
    mCoBG_SetPlussOffset(actorx->world.position, 3, mCoBG_ATTRIBUTE_NONE);
    if ((actorx->state_bitfield & ACTOR_STATE_NO_CULL) == 0) {
        actor->flags |= aSMAN_FLAG_NO_SPEAK;
    } else {
        mDemo_Request(mDemo_TYPE_SPEAK, actorx, aSMAN_set_talk_info_combine_head_init);
    }

    actor->process = aSMAN_process_combine_head;
}

static int aSMAN_process_combine_head(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if ((actor->flags & aSMAN_FLAG_NO_SPEAK) == 0) {
        if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE) {
            if (!mDemo_Check_ListenAble()) {
                mDemo_Set_ListenAble();
                mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
                mPlib_Set_able_hand_all_item_in_demo(FALSE);
            }
        } else {
            actor->flags |= aSMAN_FLAG_NO_SPEAK;
        }
    } else if (!mRlib_PSnowman_NormalTalk(actorx, (GAME_PLAY*)game, &actor->impact_speed,
                                          aSMAN_set_talk_info_normal_init)) {
        SNOWMAN_ACTOR* parent = (SNOWMAN_ACTOR*)actorx->parent_actor;

        actor->flags |= aSMAN_FLAG_MOVED;
        actor->flags |= aSMAN_FLAG_DELETE;
        parent->flags |= aSMAN_FLAG_DELETE;
        aSMAN_MakeBreakEffect(actor, game);
        mQst_BackSnowman(actorx->world.position);
        Actor_delete(actorx);
        return FALSE;
    }

    return TRUE;
}

static void aSMAN_process_combine_body_init(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    xyz_t pos;
    f32 speed_x;
    f32 speed_z;

    mFI_Wpos2UtCenterWpos(&pos, actorx->world.position);
    xyz_t_sub(&actorx->world.position, &pos, &actor->combine_dist);
    xyz_t_mult_v(&actor->combine_dist, 1.0f / 60.0f);
    speed_x = actor->combine_dist.x;
    speed_z = actor->combine_dist.z;
    actor->roll_speed = sqrtf(SQ(speed_x) + SQ(speed_z));
    actorx->world.angle.y = atans_table(-speed_z, -speed_x);
    actor->timer = 0;
    actorx->speed = 0.0f;
    actor->accel = 0.0f;
    actor->base_speed = 0.0f;
    actor->process = aSMAN_process_combine_body;
}

static int aSMAN_process_combine_body(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if ((actor->flags & aSMAN_FLAG_COMBINED) == 0) {
        if (actor->timer >= 60) {
            actor->roll_speed = 0.0f;
            actor->flags |= aSMAN_FLAG_COMBINED;
        } else {
            xyz_t_sub(&actorx->world.position, &actor->combine_dist, &actorx->world.position);
            actor->timer++;
        }
    }

    if ((actor->flags & aSMAN_FLAG_DELETE) != 0) {
        actor->flags |= aSMAN_FLAG_MOVED;
        aSMAN_MakeBreakEffect(actor, game);
        Actor_delete(actorx);
    }

    return TRUE;
}

static void aSMAN_actor_move(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((actorx->state_bitfield & ACTOR_STATE_NO_CULL) == 0) {
        if ((actor->flags & aSMAN_FLAG_COMBINED) != 0 && (actor->flags & aSMAN_FLAG_HEAD_JUMP) != 0 &&
            !aSNOWMAN_player_block_check(actorx, game) && (actor->flags & aSMAN_FLAG_NO_SPEAK) != 0) {
            Actor_delete(actorx);
            Actor_delete(actorx->parent_actor);
            return;
        } else if (actorx->speed == 0.0f && actor->process != aSMAN_process_combine_head) {
            actor->col_pipe.collision_obj.collision_flags0 &= ~ClObj_FLAG_COLLIDED;
            actor->col_pipe.collision_obj.collided_actor = NULL;
            return;
        }
    }

    aSMAN_status_check_in_move(actor, game);
    aSMAN_position_move(actorx);
    aSMAN_BGcheck(actorx, game);
    actor->process(actorx, game);
    aSMAN_calc_objChkRange(actorx);
    aSMAN_calc_axis(actorx);

    if ((actor->flags & aSMAN_FLAG_COMBINED) == 0) {
        CollisionCheck_Uty_ActorWorldPosSetPipeC(actorx, &actor->col_pipe);
        CollisionCheck_setOC(game, &play->collision_check, &actor->col_pipe.collision_obj);
    }
}

extern Gfx act_darumaA_model[];
extern Gfx act_darumaB_model[];

static void aSMAN_actor_draw(ACTOR* actorx, GAME* game) {
    static Gfx* displayList[] = { act_darumaA_model, act_darumaB_model };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    GRAPH* graph = game->graph;
    int idx;

    if ((actor->flags & aSMAN_FLAG_HEAD_JUMP) == 0 || actor->process != aSMAN_process_combine_head) {
        Matrix_translate(0.0f, actor->y_ofs, 0.0, MTX_MULT);
        Matrix_rotateXYZ(actor->head_vec.x, actor->head_vec.y, actor->head_vec.z, MTX_MULT);
        idx = 1;
    } else {
        idx = 0;
        mRlib_PSnowmanBreakNeckSwing(&actor->head_vec.y, actor->impact_speed, actor->normalized_scale);
    }

    _texture_z_light_fog_prim(graph);

    OPEN_POLY_OPA_DISP(graph);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, displayList[idx]);

    CLOSE_POLY_OPA_DISP(graph);
}
