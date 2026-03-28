#include "m_actor.h"

#include "m_play.h"
#include "m_player_lib.h"
#include "m_name_table.h"
#include "ac_npc.h"
#include "m_scene.h"
#include "m_lib.h"
#include "m_bg_item.h"
#include "m_lights.h"
#include "m_collision_obj.h"
#include "libforest/gbi_extensions.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"
#include "m_field_info.h"
#include "m_event.h"
#include "m_skin_matrix.h"
#include "m_npc.h"
#include "m_malloc.h"
#include "m_common_data.h"
#ifdef TARGET_PC
#include "pc_platform.h"
#endif

#ifdef MUST_MATCH
/* @unused | necessary for proper float ordering*/
extern void __declspec(section "forcestrip") projection_pos_set(GAME_PLAY* play, xyz_t* pos, xyz_t* proj_pos,
                                                                f32* proj_w) {
    Skin_Matrix_PrjMulVector(&play->projection_matrix, pos, proj_pos, proj_w);
    *proj_w = *proj_w < 1.0f ? 1.0f : 1.0f / *proj_w;
}
#endif

extern void Actor_world_to_eye(ACTOR* actor, f32 eye_height) {
    /* Update position */
    actor->eye.position.x = actor->world.position.x;
    actor->eye.position.y = actor->world.position.y + eye_height;
    actor->eye.position.z = actor->world.position.z;

    /* Update rotation */
    actor->eye.angle.x = actor->world.angle.x;
    actor->eye.angle.y = actor->world.angle.y;
    actor->eye.angle.z = actor->world.angle.z;
}

extern void Actor_position_move(ACTOR* actor) {
    (*((GAME_PLAY*)gamePT)->kankyo.nature.proc)(actor);

    /* divide by 2 because of 30fps -> 60fps? */
    actor->world.position.x += 0.5f * actor->position_speed.x + actor->status_data.collision_vec.x;
    actor->world.position.y += 0.5f * actor->position_speed.y + actor->status_data.collision_vec.y;
    actor->world.position.z += 0.5f * actor->position_speed.z + actor->status_data.collision_vec.z;
}

extern void Actor_position_speed_set(ACTOR* actor) {
    actor->position_speed.x = actor->speed * sin_s(actor->world.angle.y);
    actor->position_speed.z = actor->speed * cos_s(actor->world.angle.y);

    /* divide by 2 because of 30fps -> 60fps? */
    chase_f(&actor->position_speed.y, actor->max_velocity_y, 0.5f * actor->gravity);
}

extern void Actor_position_moveF(ACTOR* actor) {
    Actor_position_speed_set(actor);
    Actor_position_move(actor);
}

extern int Actor_player_look_direction_check(ACTOR* actor, s16 angle, GAME_PLAY* play) {
    s16 player_rot_y = get_player_actor_withoutCheck(play)->actor_class.shape_info.rotation.y;
    s16 inv_angle = actor->player_angle_y - -0x8000;
    s16 diff = inv_angle - player_rot_y;
    int delta = ABS(diff);

    return delta < angle;
}

/* @unused ? Actor_display_position_set(... ?) */

static int Actor_data_bank_dma_end_check(ACTOR* actor, GAME_PLAY* play) {
    switch (ITEM_NAME_GET_TYPE(actor->npc_id)) {
        case NAME_TYPE_SPNPC:
        case NAME_TYPE_NPC:
            return TRUE;
    }

    return TRUE;
}

extern void Shape_Info_init(ACTOR* actor, f32 ofs_y, mActor_shadow_proc shadow_proc, f32 shadow_size_x,
                            f32 shadow_size_z) {
    actor->shape_info.ofs_y = ofs_y;
    actor->shape_info.shadow_proc = shadow_proc;
    actor->shape_info.shadow_size_x = shadow_size_x;
    actor->shape_info.shadow_size_z = shadow_size_z;
    actor->shape_info.draw_shadow = TRUE;
    actor->shape_info.shadow_position = &actor->world.position;
    actor->shape_info.unk_20 = 0;
    actor->shape_info.shadow_size_change_rate = 1.0f;
    actor->shape_info.shadow_alpha_change_rate = 1.0f;
    actor->shape_info.force_shadow_position = FALSE;

#ifndef BUGFIXES
    actor->shape_info.shadow_position = &actor->world.position; // ???
#endif

    actor->shape_info.move_bg_idx = -1;
    actor->shape_info.unk_2D = 0;
}

extern void Actor_delete(ACTOR* actor) {
    if (actor == NULL) {
        return;
    }

    actor->mv_proc = NULL;
    actor->dw_proc = NULL;
}

static void Actor_ct(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Object_Exchange_c* exchange;
    Object_Bank_c* bank;

    exchange = &play->object_exchange;
    bank = &exchange->banks[actor->data_bank_id];

    bank->num_exist++;
    if (actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;
        aNPC_draw_data_c draw_data;
        int tex_bank_id;

        (*Common_Get(clip).npc_clip->dma_draw_data_proc)(&draw_data, actor->npc_id);
        tex_bank_id = mSc_bank_regist_check(exchange, draw_data.texture_bank);
        npc_actor->draw.texture_bank_idx = tex_bank_id;

        bank = &exchange->banks[tex_bank_id];
        bank->num_exist++;
    }

    /* Initialize world position & rotation to home position & rotation */
    actor->world = actor->home;
    actor->shape_info.rotation = actor->world.angle;
    Actor_world_to_eye(actor, 0.0f);
    xyz_t_move(&actor->last_world_position, &actor->world.position);

    actor->scale.x = 0.01f;
    actor->scale.y = 0.01f;
    actor->scale.z = 0.01f;
    actor->max_velocity_y = -20.0f;
    actor->player_distance = FLT_MAX; //3.4028235E+38;
    actor->cull_width = 350.0f;
    actor->cull_height = 700.0f;
    actor->cull_distance = 1000.0f;
    actor->cull_radius = 350.0f;
    actor->talk_distance = 55.0f;
    actor->shape_info.shadow_size_change_rate = 1.0f;
    actor->shape_info.shadow_alpha_change_rate = 1.0f;
    CollisionCheck_Status_ct(&actor->status_data);
    Shape_Info_init(actor, 0.0f, NULL, 0.0f, 0.0f);

    if (Actor_data_bank_dma_end_check(actor, play) == TRUE) {
        (*actor->ct_proc)(actor, game);
        actor->ct_proc = NULL;
    }
}

static void Actor_dt(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Object_Exchange_c* exchange;
    ACTOR* t;

    if (actor->sv_proc != NULL) {
        (*actor->sv_proc)(actor, game);
        actor->sv_proc = NULL;
    }

    if (actor->dt_proc != NULL) {
        (*actor->dt_proc)(actor, game);
        actor->dt_proc = NULL;
    }

    t = actor->child_actor;
    if (t != NULL && t->parent_actor == actor) {
        t->parent_actor = NULL;
    }

    t = actor->parent_actor;
    if (t != NULL && t->child_actor == actor) {
        t->child_actor = NULL;
    }

    exchange = &play->object_exchange;
    if (ITEM_NAME_GET_TYPE(actor->npc_id) >= NAME_TYPE_PAD15 || ITEM_NAME_GET_TYPE(actor->npc_id) < NAME_TYPE_SPNPC) {
        int bank_id = actor->data_bank_id;

        if (bank_id >= exchange->exchange_id && exchange->banks[bank_id].num_exist > 0) {
            actor->data_bank_id = -1;
            exchange->banks[bank_id].num_exist--;
        }
    }
}

static void Actor_draw_ta_set(ACTOR* actor, GAME_PLAY* play) {
    GRAPH* g;

    if ((actor->state_bitfield & ACTOR_STATE_TA_SET) == 0) {
        return;
    }

    g = play->game.graph;
    OPEN_DISP(g);

    gDPSetTextureAdjustMode(NOW_POLY_OPA_DISP++, G_TA_DOLPHIN);
    gDPSetTextureAdjustMode(NOW_SHADOW_DISP++, G_TA_DOLPHIN);
    gDPSetTextureAdjustMode(NOW_POLY_XLU_DISP++, G_TA_DOLPHIN);

    gDPSetTexEdgeAlpha(NOW_POLY_OPA_DISP++, 127);
    gDPSetTexEdgeAlpha(NOW_SHADOW_DISP++, 127);
    gDPSetTexEdgeAlpha(NOW_POLY_XLU_DISP++, 127);

    CLOSE_DISP(g);
}

static void Actor_draw_ta_clr(ACTOR* actor, GAME_PLAY* play) {
    GRAPH* g;

    if ((actor->state_bitfield & ACTOR_STATE_TA_SET) == 0) {
        return;
    }

    g = play->game.graph;
    OPEN_DISP(g);

    gDPSetTextureAdjustMode(NOW_POLY_OPA_DISP++, G_TA_N64);
    gDPSetTextureAdjustMode(NOW_SHADOW_DISP++, G_TA_N64);
    gDPSetTextureAdjustMode(NOW_POLY_XLU_DISP++, G_TA_N64);

    gDPSetTexEdgeAlpha(NOW_POLY_OPA_DISP++, 144);
    gDPSetTexEdgeAlpha(NOW_SHADOW_DISP++, 144);
    gDPSetTexEdgeAlpha(NOW_POLY_XLU_DISP++, 144);

    CLOSE_DISP(g);
}

static void Actor_draw(GAME_PLAY* play, ACTOR* actor) {
    LightsN* lights;
    lights = Global_light_read(&play->global_light, play->game.graph);

    /* Light actor */
    LightsN_list_check(lights, play->global_light.list,
                       (actor->state_bitfield & ACTOR_STATE_LIGHTING) ? NULL : &actor->world.position);
    LightsN_disp(lights, play->game.graph);
    LightsN_disp_BG(lights, play->game.graph);

    /* Load actor position/scale matrix */
    Matrix_softcv3_load(&actor->shape_info.rotation, actor->world.position.x,
                        actor->world.position.y + actor->shape_info.ofs_y * actor->scale.y, actor->world.position.z);
    Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, MTX_MULT);

    /* Draw actor */
    Actor_draw_ta_set(actor, play);
    (*actor->dw_proc)(actor, &play->game);
    Actor_draw_ta_clr(actor, play);

    /* Draw shadow */
    if (actor->shape_info.shadow_proc != NULL) {
        (*actor->shape_info.shadow_proc)(actor, lights, play);
    }
}

extern int Actor_draw_actor_no_culling_check(ACTOR* actor) {
    return Actor_draw_actor_no_culling_check2(actor, &actor->camera_position, actor->camera_w);
}

extern int Actor_draw_actor_no_culling_check2(ACTOR* actor, xyz_t* camera_pos, f32 camera_w) {
#ifdef TARGET_PC
    /* PC port: the GC projection matrix produced clip-space values in a range the
     * original culling thresholds were tuned for.  The PC/OpenGL projection produces
     * values in a different range, causing false-negative culling.  Disable software
     * frustum culling on PC — the GPU clips out-of-frustum geometry anyway.
     * TODO: properly recalibrate the clip-space thresholds for the PC projection. */
    (void)camera_pos;
    (void)camera_w;
    return TRUE;
#else
    int res = FALSE;

    if (-actor->cull_radius < camera_pos->z && camera_pos->z < actor->cull_distance + actor->cull_radius) {
        f32 m = camera_w < 1.0f ? 1.0f : 1.0f / camera_w;
        f32 x_edge = 1.0f;
        int width_OK = (m * (fabsf(camera_pos->x) - actor->cull_width)) < x_edge;

        if (width_OK &&
            (m * (camera_pos->y + actor->cull_height)) > -1.0f && (m * (camera_pos->y - actor->cull_radius) < 1.0f)) {
            res = TRUE;
        }
    }

    return res;
#endif
}

static void Actor_cull_check(ACTOR* actor) {
    if (Actor_draw_actor_no_culling_check(actor) == TRUE) {
        actor->state_bitfield |= ACTOR_STATE_NO_CULL;
    } else {
        actor->state_bitfield &= ~ACTOR_STATE_NO_CULL;
    }
}

static void Actor_delete_check(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((actor->state_bitfield &
         (ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_CULL)) == 0) {
        if (actor->npc_id != EMPTY_NO) {
            if (actor->block_x >= 0 && actor->block_z >= 0) {
                if (actor->block_x != play->block_table.block_x || actor->block_z != play->block_table.block_z) {
                    Actor_delete(actor);
                }
            }
        }
    }
}

extern void Actor_info_ct(GAME* game, Actor_info* actor_info, Actor_data* player_data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ACTOR* player_actor;
    ACTOR_DLFTBL* dlftbl;
    int i;

    bzero(actor_info, sizeof(Actor_info));
    actor_dlftbls_init();

    Matrix_copy_MtxF(&play->billboard_matrix, &MtxF_clear);
    Matrix_copy_MtxF(&play->projection_matrix, &MtxF_clear);

    /* Reset the actor dlf table info */
    dlftbl = actor_dlftbls;
    for (i = 0; i < mAc_PROFILE_NUM; i++) {
        dlftbl->alloc_buf = NULL;
        dlftbl->num_actors = 0;
        dlftbl++;
    }

    if (mEv_CheckFirstJob() == TRUE) {
        Common_Set(demo_profiles[0], mAc_PROFILE_INTRO_DEMO); // force intro demo to spawn
    }

    /* Spawn any demo actors */
    for (i = 0; i < 2; i++) {
        s16 demo_profile = Common_Get(demo_profiles[i]);

        if (demo_profile != mAc_PROFILE_NUM) {
            Actor_info_make_actor(actor_info, game, demo_profile, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, EMPTY_NO, -1,
                                  -1, -1);
        }

        Common_Set(demo_profiles[i], mAc_PROFILE_NUM);
    }

    /* Try spawning the player actor */
    player_actor =
        Actor_info_make_actor(actor_info, game, player_data->profile, player_data->position.x, player_data->position.y,
                              player_data->position.z, player_data->rotation.x, player_data->rotation.y,
                              player_data->rotation.z, -1, -1, -1, EMPTY_NO, player_data->arg, -1, -1);

    if (player_actor != NULL) {
        player_actor->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(player_actor->world.position, 0.0f);
        mFI_SetBearActor(play, player_actor->world.position, FALSE);
    }

    /* Spawn the current bg item type actor */
    if (Common_Get(bg_item_profile) != 0) {
        Actor_info_make_actor(actor_info, game, Common_Get(bg_item_profile), 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1,
                              EMPTY_NO, -1, -1, -1);
    }

    /* Spawn all pending control actors */
    if (play->ctrl_actor_data_num != 0) {
        s16* ctrl_actor_data = play->ctrl_actor_data;
        for (i = 0; i < play->ctrl_actor_data_num; i++) {
            Actor_info_make_actor(&play->actor_info, game, *ctrl_actor_data, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1,
                                  EMPTY_NO, -1, -1, -1);

            ctrl_actor_data++;
        }

        play->ctrl_actor_data_num = 0;
    }

    mSc_regist_initial_exchange_bank(play);

    /* Spawn all pending actors */
    if (play->actor_data_num != 0) {
        Actor_data* actor_data = play->actor_data;
        for (i = 0; i < play->actor_data_num; i++) {

            Actor_info_make_actor(&play->actor_info, (GAME*)play, actor_data->profile, actor_data->position.x,
                                  actor_data->position.y, actor_data->position.z, actor_data->rotation.x,
                                  actor_data->rotation.y, actor_data->rotation.z, -1, -1, -1, EMPTY_NO, actor_data->arg,
                                  -1, -1);

            actor_data++;
        }

        play->actor_data_num = 0;
    }
}

extern void Actor_info_dt(Actor_info* actor_info, GAME_PLAY* play) {
    int i;

    for (i = 0; i < ACTOR_PART_NUM; i++) {
        ACTOR* actor;

        while (actor = actor_info->list[i].actor, actor != NULL) {
            Actor_info_delete(actor_info, actor, (GAME*)play);
        }
    }

    actor_dlftbls_cleanup();
}

extern void Actor_info_call_actor(GAME_PLAY* play, Actor_info* actor_info) {
    // GAME* game = (GAME*)play;
    PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);
    ACTOR* actor;
    int i;

    mFI_FieldMove(player_actor->actor_class.world.position);
    mBI_move(play);

    for (i = 0; i < ACTOR_PART_NUM; i++) {
        ACTOR* next;
        actor = actor_info->list[i].actor;

        while (actor != NULL) {
            play->game.doing_point = actor->id;
            play->game.doing_point_specific = 151;

            if (actor->world.position.y < -25000.0f) {
                actor->world.position.y = -25000.0f;
            }

            if (actor->ct_proc != NULL) {
                if (Actor_data_bank_dma_end_check(actor, play) == TRUE) {
                    play->game.doing_point_specific = 152;
                    (*actor->ct_proc)(actor, (GAME*)play);
                    play->game.doing_point_specific = 153;
                    actor->ct_proc = NULL;
                }

                next = actor->next_actor;
            } else {
                if (Actor_data_bank_dma_end_check(actor, play) == FALSE) {
                    play->game.doing_point_specific = 154;
                    Actor_delete(actor);
                    play->game.doing_point_specific = 155;
                    next = actor->next_actor;
                } else if (actor->mv_proc == NULL) {
                    if (actor->drawn == FALSE) {
                        play->game.doing_point_specific = 156;
                        next = Actor_info_delete(&play->actor_info, actor, (GAME*)play);
                        play->game.doing_point_specific = 157;
                    } else {
                        play->game.doing_point_specific = 158;
                        Actor_dt(actor, (GAME*)play);
                        play->game.doing_point_specific = 159;
                        next = actor->next_actor;
                    }
                } else {
                    play->game.doing_point_specific = 160;
                    xyz_t_move(&actor->last_world_position, &actor->world.position);
                    actor->player_distance_xz =
                        search_position_distanceXZ(&actor->world.position, &player_actor->actor_class.world.position);
                    actor->player_distance_y = player_actor->actor_class.world.position.y - actor->world.position.y;
                    actor->player_distance = actor->player_distance_xz * actor->player_distance_xz +
                                             actor->player_distance_y * actor->player_distance_y;
                    actor->player_angle_y =
                        search_position_angleY(&actor->world.position, &player_actor->actor_class.world.position);
                    actor->state_bitfield &= ~ACTOR_STATE_24;

                    if ((actor->state_bitfield & (ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_CULL)) ||
                        actor->part == ACTOR_PART_NPC) {
                        play->game.doing_point_specific = 161;
                        (*actor->mv_proc)(actor, (GAME*)play);
                        play->game.doing_point_specific = 162;
                    }

                    CollisionCheck_Status_Clear(&actor->status_data);
                    next = actor->next_actor;
                }
            }

            actor = next;
        }
    }

    play->game.doing_point_specific = 163;
}

extern void Actor_info_draw_actor(GAME_PLAY* play, Actor_info* actor_info) {
    Actor_list* list;
    ACTOR* actor;
    int i;
    DRAW_CHK_PROC draw_chk_proc = play->draw_chk_proc;

    list = actor_info->list;
    for (i = 0; i < ACTOR_PART_NUM; i++) {
        int do_not_draw;

        for (actor = list->actor; actor != NULL; actor = actor->next_actor) {
            /* Apply projection matrix to actor position */
            Skin_Matrix_PrjMulVector(&play->projection_matrix, &actor->world.position, &actor->camera_position,
                                     &actor->camera_w);

            Actor_cull_check(actor);
            do_not_draw = (*draw_chk_proc)(actor, play);
            actor->drawn = FALSE;

            if (do_not_draw == FALSE && actor->ct_proc == NULL && actor->dw_proc != NULL) {
                if ((actor->state_bitfield & (ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_CULL))) {
                    if ((actor->state_bitfield & ACTOR_STATE_INVISIBLE) == 0 && actor->cull_while_talking == FALSE &&
                        actor->skip_drawing == FALSE) {
                        Actor_draw(play, actor);
                        actor->drawn = TRUE;
                    }
                } else {
                    Actor_delete_check(actor, (GAME*)play);
                }
            }
        }

        list++;
    }

    Light_list_point_draw(play);
}

static void Actor_info_part_new(Actor_info* actor_info, ACTOR* actor, u8 part) {
    ACTOR* next;

    actor->part = part;
    actor_info->total_num++;
    actor_info->list[part].num_actors++;

    next = actor_info->list[part].actor;
    if (next != NULL) {
        next->prev_actor = actor;
    }

    actor_info->list[part].actor = actor;
    actor->next_actor = next;
}

static ACTOR* Actor_info_part_delete(Actor_info* actor_info, ACTOR* actor) {
    ACTOR* next;

    actor_info->total_num--;
    actor_info->list[actor->part].num_actors--;

    if (actor->prev_actor != NULL) {
        actor->prev_actor->next_actor = actor->next_actor;
    } else {
        actor_info->list[actor->part].actor = actor->next_actor;
    }

    next = actor->next_actor;
    if (next != NULL) {
        next->prev_actor = actor->prev_actor;
    }

    actor->prev_actor = NULL;
    actor->next_actor = NULL;

    return next;
}

extern void Actor_free_overlay_area(ACTOR_DLFTBL* dlftbl) {
    if ((dlftbl->flags & 2) == 0) {
        if ((dlftbl->flags & 1)) {
            dlftbl->alloc_buf = NULL;
        } else {
            zelda_free(dlftbl->alloc_buf);
            dlftbl->alloc_buf = NULL;
        }
    }
}

static void actor_free_check(ACTOR_DLFTBL* dlftbl, mActor_name_t id) {
    if (dlftbl->num_actors == 0 && dlftbl->alloc_buf != NULL) {
        switch (ITEM_NAME_GET_TYPE(id)) {
            case NAME_TYPE_SPNPC:
            case NAME_TYPE_NPC:
                (*Common_Get(clip).npc_clip->free_overlay_area_proc)(dlftbl);
                break;

            case NAME_TYPE_STRUCT:
                (*Common_Get(clip).structure_clip->free_overlay_area_proc)(dlftbl);
                break;

            default:
                Actor_free_overlay_area(dlftbl);
                break;
        }
    }
}

extern void Actor_get_overlay_area(ACTOR_DLFTBL* dlftbl, int unused, size_t alloc_size) {
    if ((dlftbl->flags & 2)) {
        dlftbl->alloc_buf = (u8*)zelda_malloc_r(alloc_size);
    } else {
        dlftbl->alloc_buf = (u8*)zelda_malloc(alloc_size);
    }
}

static int Actor_data_bank_regist_check_npc(int* bank_id, ACTOR_PROFILE* profile, ACTOR_DLFTBL* dlftbl, GAME_PLAY* play,
                                            mActor_name_t name_id) {
    return TRUE;
}

static int Actor_data_bank_regist_check(int* bank_id, ACTOR_PROFILE* profile, ACTOR_DLFTBL* dlftbl, GAME_PLAY* play,
                                        mActor_name_t name_id) {
    int res = TRUE;

    if (*bank_id == -1) {
        if (profile->part == ACTOR_PART_NPC) {
            res = Actor_data_bank_regist_check_npc(bank_id, profile, dlftbl, play, name_id);
        } else {
            // in DnM, this was another func call
            res = TRUE;
        }
    }

    return res;
}

static int Actor_malloc_actor_class(ACTOR** actor_pp, ACTOR_PROFILE* profile, ACTOR_DLFTBL* dlftbl, const char* name,
                                    mActor_name_t id) {
    aNPC_draw_data_c draw_data;

    switch (ITEM_NAME_GET_TYPE(id)) {
        case NAME_TYPE_SPNPC:
        case NAME_TYPE_NPC: {
#ifdef TARGET_PC
            if (CLIP(npc_clip) == NULL) {
                *actor_pp = (ACTOR*)zelda_malloc(profile->class_size);
                break;
            }
#endif
            *actor_pp = CLIP(npc_clip)->get_actor_area_proc(profile->class_size, name, 1);
            (*Common_Get(clip).npc_clip->dma_draw_data_proc)(&draw_data, id); // leftover?
            break;
        }

        case NAME_TYPE_STRUCT: {
#ifdef TARGET_PC
            if (Common_Get(clip).structure_clip == NULL) {
                *actor_pp = (ACTOR*)zelda_malloc(profile->class_size);
                break;
            }
#endif
            *actor_pp = (ACTOR*)((*Common_Get(clip).structure_clip->get_actor_area_proc)());
            break;
        }

        default: {
            *actor_pp = (ACTOR*)zelda_malloc(profile->class_size);
            break;
        }
    }

    if (*actor_pp == NULL) {
        actor_free_check(dlftbl, id);
        return FALSE;
    }

    return TRUE;
}

extern void Actor_init_actor_class(ACTOR* actor, ACTOR_PROFILE* profile, ACTOR_DLFTBL* dlftbl, GAME_PLAY* play,
                                   int bank_idx, f32 x, f32 y, f32 z, s16 rot_x, s16 rot_y, s16 rot_z, s8 block_x,
                                   s8 block_z, s16 move_actor_list_idx, mActor_name_t name_id, s16 arg) {
    mem_clear((u8*)actor, profile->class_size, 0);
    actor->dlftbl = dlftbl;
    actor->id = profile->id;
    actor->state_bitfield = profile->initial_flags_state;
    actor->data_bank_id = bank_idx;
    actor->ct_proc = profile->ct_proc;
    actor->dt_proc = profile->dt_proc;
    actor->mv_proc = profile->mv_proc;
    actor->dw_proc = profile->dw_proc;
    actor->sv_proc = profile->sv_proc;
    actor->actor_specific = arg;
    actor->scene_id = play->scene_id;
    actor->home.position.x = x;
    actor->home.position.y = y;
    actor->home.position.z = z;
    actor->home.angle.x = rot_x;
    actor->home.angle.y = rot_y;
    actor->home.angle.z = rot_z;
    actor->block_x = block_x;
    actor->block_z = block_z;
    actor->move_actor_list_idx = move_actor_list_idx;
    actor->npc_id = name_id;
}

typedef struct overlay_struct {
    const char* actor_name;
} mAc_overlay_info_c;

extern ACTOR* Actor_info_make_actor(Actor_info* actor_info, GAME* game, s16 profile_no, f32 x, f32 y, f32 z, s16 rot_x,
                                    s16 rot_y, s16 rot_z, s8 block_x, s8 block_z, s16 move_actor_list_idx,
                                    mActor_name_t name_id, s16 arg, s8 npc_info_idx, int data_bank_idx) {
    GAME_PLAY* play;
    ACTOR* actor;
    ACTOR_PROFILE* profile;
    ACTOR_DLFTBL* dlftbl;
    mAc_overlay_info_c overlay_info; /* Required to be a struct, stubbed in GC */

    play = (GAME_PLAY*)game;
    dlftbl = actor_dlftbls + profile_no;
    overlay_info.actor_name = "";
    if (actor_info->total_num > mAc_MAX_ACTORS) {
        return NULL;
    }

    profile = dlftbl->profile;
#ifdef TARGET_PC
    /* Skip actors with NULL or stubbed profiles (stub functions masquerading as struct data) */
    if (profile == NULL || profile->class_size == 0 || profile->class_size > 0x100000) {
        return NULL;
    }
#endif
    if (Actor_data_bank_regist_check(&data_bank_idx, profile, dlftbl, play, name_id) == FALSE) {
        return NULL;
    }

    if (Actor_malloc_actor_class(&actor, profile, dlftbl, overlay_info.actor_name, name_id) == FALSE) {
        return NULL;
    }

    dlftbl->num_actors++;
    Actor_init_actor_class(actor, profile, dlftbl, play, data_bank_idx, x, y, z, rot_x, rot_y, rot_z, block_x, block_z,
                           move_actor_list_idx, name_id, arg);
    Actor_info_part_new(actor_info, actor, profile->part);
    mNpc_SetNpcinfo(actor, npc_info_idx);
    Actor_ct(actor, game);

    return actor;
}

extern ACTOR* Actor_info_make_child_actor(Actor_info* actor_info, ACTOR* parent_actor, GAME* game, s16 profile, f32 x,
                                          f32 y, f32 z, s16 rot_x, s16 rot_y, s16 rot_z, s16 move_actor_list_idx,
                                          mActor_name_t name_id, s16 arg, int data_bank_idx) {
    ACTOR* actor = Actor_info_make_actor(actor_info, game, profile, x, y, z, rot_x, rot_y, rot_z, -1, -1,
                                         move_actor_list_idx, name_id, arg, -1, data_bank_idx);

    if (actor != NULL) {
        parent_actor->child_actor = actor;
        actor->parent_actor = parent_actor;
    }

    return actor;
}

static void restore_fgdata(ACTOR* actor, GAME_PLAY* play) {
    mActor_name_t name = actor->npc_id;

    if (name != EMPTY_NO && actor->move_actor_list_idx == -1 && actor->block_x >= 0 && actor->block_z >= 0) {
        if (ITEM_NAME_GET_TYPE(name) == NAME_TYPE_ITEM2) {
            xyz_t pos;

            xyz_t_move(&pos, &actor->home.position);
            if (mFI_search_unit_around(&pos, EMPTY_NO) == TRUE) {
                /* pos now holds the position of the empty unit */
                mFI_SetFG_common(actor->npc_id, pos, FALSE); /* This causes the airplane duplication "bug" */
            }
        } else {
            mFI_SetFG_common(name, actor->home.position, FALSE);
        }
    }
}

static int restore_flag[ACTOR_PART_NUM] = {
    TRUE,  /* FG */
    TRUE,  /* ITEM */
    FALSE, /* PLAYER */
    FALSE, /* 3 */
    FALSE, /* NPC */
    FALSE, /* BG */
    FALSE, /* EFFECT */
    FALSE  /* CONTROL */
};

static void restore_fgdata_one(ACTOR* actor, GAME_PLAY* play) {
    if (restore_flag[actor->part] == TRUE) {
        restore_fgdata(actor, play);
    } else if (actor->restore_fg == TRUE) {
        restore_fgdata(actor, play);
    }
}

extern void restore_fgdata_all(GAME_PLAY* play) {
    Actor_info* info;
    ACTOR* actor;
    int i;

    info = &play->actor_info;
    for (i = 0; i < ACTOR_PART_NUM; i++) {
        if (restore_flag[i] == TRUE) {
            for (actor = info->list[i].actor; actor != NULL; actor = actor->next_actor) {
                restore_fgdata(actor, play);
            }
        } else {
            for (actor = info->list[i].actor; actor != NULL; actor = actor->next_actor) {
                if (actor->restore_fg == TRUE) {
                    restore_fgdata(actor, play);
                }
            }
        }
    }
}

extern void Actor_info_save_actor(GAME_PLAY* play) {
    Actor_info* info;
    ACTOR* actor;
    int i;

    info = &play->actor_info;
    for (i = 0; i < ACTOR_PART_NUM; i++) {
        for (actor = info->list[i].actor; actor != NULL; actor = actor->next_actor) {
            if (actor->sv_proc != NULL) {
                (*actor->sv_proc)(actor, (GAME*)play);
                actor->sv_proc = NULL;
            }
        }
    }

    restore_fgdata_all(play);
}

extern ACTOR* Actor_info_delete(Actor_info* actor_info, ACTOR* actor, GAME* game) {
    mActor_name_t name_id = actor->npc_id;
    ACTOR_DLFTBL* dlftbl = actor->dlftbl;
    ACTOR* next_actor;

    restore_fgdata_one(actor, (GAME_PLAY*)game);
    Actor_dt(actor, game);
    next_actor = Actor_info_part_delete(actor_info, actor);

    switch (ITEM_NAME_GET_TYPE(name_id)) {
        case NAME_TYPE_SPNPC:
        case NAME_TYPE_NPC: {
            (*Common_Get(clip).npc_clip->free_actor_area_proc)(actor);
            break;
        }

        case NAME_TYPE_STRUCT: {
            (*Common_Get(clip).structure_clip->free_actor_area_proc)((STRUCTURE_ACTOR*)actor);
            break;
        }

        default: {
            zelda_free(actor);
            break;
        }
    }

    if (dlftbl->ram_start == NULL) {
        dlftbl->num_actors--;
    } else {
        dlftbl->num_actors--;
        actor_free_check(dlftbl, actor->npc_id);
    }

    return next_actor;
}

extern ACTOR* Actor_info_name_search_sub(ACTOR* actor, s16 name) {
    while (actor != NULL) {
        if (actor->id == name) {
            return actor;
        }

        actor = actor->next_actor;
    }

    return actor;
}

extern ACTOR* Actor_info_name_search(Actor_info* actor_info, s16 name, int part) {
    ACTOR* actor = actor_info->list[part].actor;

    if (actor != NULL) {
        return Actor_info_name_search_sub(actor, name);
    }

    return NULL;
}

extern ACTOR* Actor_info_fgName_search_sub(ACTOR* actor, mActor_name_t fgName) {
    while (actor != NULL) {
        if (actor->npc_id == fgName) {
            return actor;
        }

        actor = actor->next_actor;
    }

    return actor;
}

extern ACTOR* Actor_info_fgName_search(Actor_info* actor_info, mActor_name_t fgName, int part) {
    ACTOR* actor = actor_info->list[part].actor;

    if (actor != NULL) {
        return Actor_info_fgName_search_sub(actor, fgName);
    }

    return NULL;
}

extern Gfx* HiliteReflect_new(xyz_t* pos, xyz_t* eye, xyz_t* light_direction, GRAPH* graph, Gfx* gfx, Hilite** hilite) {
    static Mtx work_view_matrix;

    LookAt* lookat = GRAPH_ALLOC_TYPE(graph, LookAt, 1);
    int pos_eye_equal = FALSE;
    f32 eye_x = eye->x;

    if (eye_x == pos->x && eye->z == pos->z) {
        pos_eye_equal = TRUE;
    }

    if (pos_eye_equal) {
        eye_x = 0.001f + eye_x;
    }

    *hilite = GRAPH_ALLOC_TYPE(graph, Hilite, 1);
    guLookAtHilite(&work_view_matrix, lookat, *hilite, eye_x, eye->y, eye->z, pos->x, pos->y, pos->z, 0.0f, 1.0f, 0.0f,
                   light_direction->x, light_direction->y, light_direction->z, light_direction->x, light_direction->y,
                   light_direction->z, 16, 16);

    gSPLookAt(gfx++, lookat);
    gDPPipeSync(gfx++);
    gDPSetTileSize(gfx++, 1, (*hilite)->h.x1, (*hilite)->h.y1, (*hilite)->h.x1 + 60, (*hilite)->h.y1 + 60);

    return gfx;
}

extern Hilite* HiliteReflect_init(xyz_t* pos, xyz_t* eye, xyz_t* light_direction, GRAPH* graph) {
    Hilite* hilite;

    OPEN_DISP(graph);

    SET_POLY_OPA_DISP(HiliteReflect_new(pos, eye, light_direction, graph, NOW_POLY_OPA_DISP, &hilite));

    CLOSE_DISP(graph);

    return hilite;
}

extern Hilite* HiliteReflect_xlu_init(xyz_t* pos, xyz_t* eye, xyz_t* light_direction, GRAPH* graph) {
    Hilite* hilite;

    OPEN_DISP(graph);

    SET_POLY_XLU_DISP(HiliteReflect_new(pos, eye, light_direction, graph, NOW_POLY_XLU_DISP, &hilite));

    CLOSE_DISP(graph);

    return hilite;
}

extern void Setpos_HiliteReflect_init(xyz_t* pos, GAME_PLAY* play) {
    Kankyo* kankyo = &play->kankyo;
    xyz_t sun_pos;

    sun_pos.x = (int)kankyo->sun_light.lights.diffuse.x;
    sun_pos.y = (int)kankyo->sun_light.lights.diffuse.y;
    sun_pos.z = (int)kankyo->sun_light.lights.diffuse.z;

    HiliteReflect_init(pos, &play->view.eye, &sun_pos, play->game.graph);
}

extern void Setpos_HiliteReflect_xlu_init(xyz_t* pos, GAME_PLAY* play) {
    Kankyo* kankyo = &play->kankyo;
    xyz_t sun_pos;

    sun_pos.x = (int)kankyo->sun_light.lights.diffuse.x;
    sun_pos.y = (int)kankyo->sun_light.lights.diffuse.y;
    sun_pos.z = (int)kankyo->sun_light.lights.diffuse.z;

    HiliteReflect_xlu_init(pos, &play->view.eye, &sun_pos, play->game.graph);
}
