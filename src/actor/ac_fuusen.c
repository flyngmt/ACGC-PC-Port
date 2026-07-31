#include "ac_fuusen.h"

#include "m_actor_shadow.h"
#include "m_common_data.h"
#include "m_debug_display.h"
#include "m_fuusen.h"
#include "m_play.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "zurumode.h"

static void aFSN_actor_ct(ACTOR* actorx, GAME* game);
static void aFSN_actor_dt(ACTOR* actorx, GAME* game);
static void aFSN_actor_move(ACTOR* actorx, GAME* game);
static void aFSN_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Fuusen_Profile = {
  mAc_PROFILE_FUUSEN,
  ACTOR_PART_CONTROL,
  ACTOR_STATE_NO_MOVE_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_FUUSEN,
  sizeof(FUUSEN_ACTOR),
  &aFSN_actor_ct,
  &aFSN_actor_dt,
  &aFSN_actor_move,
  &aFSN_actor_draw,
  NULL
};

static void aFSN_setupAction(FUUSEN_ACTOR* fuusen_actor, GAME* game, int action);

extern cKF_Skeleton_R_c cKF_bs_r_act_balloon;
extern cKF_Animation_R_c cKF_ba_r_act_balloon;

static void aFSN_actor_ct(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;
  cKF_SkeletonInfo_R_c* keyframe_p = &fuusen->keyframe;
  static xyz_t Init_Size = { 0.01f, 0.01f, 0.01f };
  f32 balloon_ground_y = mCoBG_GetBalloonGroundY(&actorx->world.position);

  fuusen->escape_timer = 2000.0f;
  cKF_SkeletonInfo_R_ct(keyframe_p, &cKF_bs_r_act_balloon, &cKF_ba_r_act_balloon, fuusen->work, fuusen->morph);
  cKF_SkeletonInfo_R_init_standard_repeat(keyframe_p, &cKF_ba_r_act_balloon, NULL);
  Shape_Info_init(actorx, 0.0f, &mAc_ActorShadowCircle, 10.0f, 10.0f);
  actorx->shape_info.draw_shadow = FALSE;
  cKF_SkeletonInfo_R_play(keyframe_p);
  keyframe_p->frame_control.speed = 1.0f;
  xyz_t_move(&actorx->scale, &Init_Size);
  actorx->world.position.y = balloon_ground_y + 200.0f;
  fuusen->y_offset = 110.0f;
  fuusen->segment_p = ((GAME_PLAY*)game)->object_exchange.banks[actorx->data_bank_id].ram_start;
  aFSN_setupAction(fuusen, game, aFSN_ACTION_BIRTH);
}

static void aFSN_actor_dt(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;

  if (fuusen->look_up_flag == TRUE) {
    Balloon_look_up();
  }
  else {
    Balloon_kill();
  }
}

static void aFSN_birth(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;

  aFSN_setupAction(fuusen, game, aFSN_ACTION_MOVING);
}

static void aFSN_moving(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;
  GAME_PLAY* play = (GAME_PLAY*)game;
  f32 balloon_y = mCoBG_GetBalloonGroundY(&actorx->world.position) + fuusen->y_offset;
  xyz_t screen_pos;
  mActor_name_t* fg_item_p;

  if (fuusen->escape_timer > 0) {
    fuusen->escape_timer -= (f32)game->graph->dt_num_60fps_frames;
    if (fuusen->escape_timer < 0.0f) {
      fuusen->escape_timer = 0.0f;
    }
  }
  else {
    /* Escape if flown to the edge of the map */
    if (
      (actorx->world.position.x <= 660.0f || actorx->world.position.x >= 3820.0f) ||
      (actorx->world.position.z <= 660.0f || actorx->world.position.z >= 4460.0f)
    ) {
      fuusen->escape_timer = (f32)aFSN_ESCAPE_TIMER;
      aFSN_setupAction(fuusen, game, aFSN_ACTION_ESCAPE);
      return;
    }

    /* Escape if flown into the train station acre? */
    if (
      (actorx->world.position.x <= 2440.0f && actorx->world.position.x >= 2040.0f) &&
      (actorx->world.position.z <=  960.0f && actorx->world.position.z >=  800.0f)
    ) {
      fuusen->escape_timer = (f32)aFSN_ESCAPE_TIMER;
      aFSN_setupAction(fuusen, game, aFSN_ACTION_ESCAPE);
      return;
    }
  }

  fuusen->wind_power = mEnv_GetWindPowerF();
  actorx->speed = fuusen->wind_power * 0.5f + 1.0f;
  fuusen->fuwafuwa_cycle += (s16)(250.0f * game->graph->dt_num_60fps_frames);
  add_calc(
    &actorx->world.position.y,
    balloon_y + sin_s(fuusen->fuwafuwa_cycle) * 10.0f,
    1.0f - sqrtf(0.7f),
    0.5f, 0.0f
  );

  Game_play_Projection_Trans(play, &actorx->world.position, &screen_pos);

  if (-40.0f > screen_pos.x || screen_pos.x > 360.0f || -40.0f > screen_pos.y || screen_pos.y > 280.0f) {
    return;
  }

  mCoBG_BgCheckControll(NULL, actorx, 12.0f, 0.0f, 0, 0, 0);

  if (
    (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL) ||
    (actorx->bg_collision_check.result.hit_attribute_wall & mCoBG_HIT_WALL)
  ) {
    fuusen->y_offset += 0.05f; // raise quickly over walls

    if (fuusen->y_offset >= 300.0f) {
      fuusen->y_offset = 300.0f;
    }
  }
  else if (fuusen->y_offset > 110.0f) {
    fuusen->y_offset -= 0.005f; // slowly fall
  }

  fg_item_p = mFI_GetUnitFG(actorx->world.position);

  if (
    fg_item_p != NULL &&
    (
      *fg_item_p == TREE ||
      *fg_item_p == TREE_APPLE_NOFRUIT_0 ||
      *fg_item_p == TREE_APPLE_NOFRUIT_1 ||
      *fg_item_p == TREE_APPLE_NOFRUIT_2 ||
      *fg_item_p == TREE_ORANGE_NOFRUIT_0 ||
      *fg_item_p == TREE_ORANGE_NOFRUIT_1 ||
      *fg_item_p == TREE_ORANGE_NOFRUIT_2 ||
      *fg_item_p == TREE_PEACH_NOFRUIT_0 ||
      *fg_item_p == TREE_PEACH_NOFRUIT_1 ||
      *fg_item_p == TREE_PEACH_NOFRUIT_2 ||
      *fg_item_p == TREE_PEAR_NOFRUIT_0 ||
      *fg_item_p == TREE_PEAR_NOFRUIT_1 ||
      *fg_item_p == TREE_PEAR_NOFRUIT_2 ||
      *fg_item_p == TREE_CHERRY_NOFRUIT_0 ||
      *fg_item_p == TREE_CHERRY_NOFRUIT_1 ||
      *fg_item_p == TREE_CHERRY_NOFRUIT_2 ||
      *fg_item_p == TREE_PALM_NOFRUIT_0 ||
      *fg_item_p == TREE_PALM_NOFRUIT_1 ||
      *fg_item_p == TREE_PALM_NOFRUIT_2 ||
      *fg_item_p == CEDAR_TREE ||
      *fg_item_p == GOLD_TREE
    )
  ) {
    f32 dx;
    f32 dy;
    f32 dz;

    mFI_Wpos2UtCenterWpos(&screen_pos, actorx->world.position);

    if (*fg_item_p == CEDAR_TREE) {
      screen_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f) + 100.0f;
      screen_pos.z += 20.0f;
    }
    else {
      screen_pos.x -= 2.5f;
      screen_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f) + 97.5f;
      screen_pos.z += 7.5f;
    }

    dx = screen_pos.x - actorx->world.position.x;
    dy = screen_pos.y - actorx->world.position.y;
    dz = screen_pos.z - actorx->world.position.z;

    if (*fg_item_p == CEDAR_TREE) {
      if (dx * dx + dz * dz < 484.0f && dy * dy < 225.0f) {
        aFSN_setupAction(fuusen, game, aFSN_ACTION_WOOD_STOP);
      }
    }
    else if (dx * dx + dz * dz < 225.0f && dy * dy < 225.0f) {
      aFSN_setupAction(fuusen, game, aFSN_ACTION_WOOD_STOP);
    }
  }
  else {
    if (fuusen->wind_change_flag == FALSE) {
      static int senkou_check_data[] = { -2500, 0, 2500 };
      s16 new_angle;
      int i;

      for (i = 0; i < ARRAY_COUNT(senkou_check_data); i++) {
        xyz_t_move(&screen_pos, &actorx->world.position);
        new_angle = (int)actorx->world.angle.y + (s16)senkou_check_data[i];
        screen_pos.x += 80.0f * sin_s(new_angle);
        screen_pos.z += 80.0f * cos_s(new_angle);

        fg_item_p = mFI_GetUnitFG(screen_pos);
        if (
          fg_item_p != NULL &&
          (
            *fg_item_p == TREE ||
            *fg_item_p == TREE_APPLE_NOFRUIT_0 ||
            *fg_item_p == TREE_APPLE_NOFRUIT_1 ||
            *fg_item_p == TREE_APPLE_NOFRUIT_2 ||
            *fg_item_p == TREE_ORANGE_NOFRUIT_0 ||
            *fg_item_p == TREE_ORANGE_NOFRUIT_1 ||
            *fg_item_p == TREE_ORANGE_NOFRUIT_2 ||
            *fg_item_p == TREE_PEACH_NOFRUIT_0 ||
            *fg_item_p == TREE_PEACH_NOFRUIT_1 ||
            *fg_item_p == TREE_PEACH_NOFRUIT_2 ||
            *fg_item_p == TREE_PEAR_NOFRUIT_0 ||
            *fg_item_p == TREE_PEAR_NOFRUIT_1 ||
            *fg_item_p == TREE_PEAR_NOFRUIT_2 ||
            *fg_item_p == TREE_CHERRY_NOFRUIT_0 ||
            *fg_item_p == TREE_CHERRY_NOFRUIT_1 ||
            *fg_item_p == TREE_CHERRY_NOFRUIT_2 ||
            *fg_item_p == TREE_PALM_NOFRUIT_0 ||
            *fg_item_p == TREE_PALM_NOFRUIT_1 ||
            *fg_item_p == TREE_PALM_NOFRUIT_2 ||
            *fg_item_p == CEDAR_TREE ||
            *fg_item_p == GOLD_TREE
          )
        ) {
          actorx->world.angle.y = new_angle;
          fuusen->wind_change_flag = TRUE;
          break;
        }
      }
    }

    if (fuusen->wind_change_flag == FALSE) {
      actorx->world.angle.y = mEnv_GetWindAngleS();
    }
  }
}

static void aFSN_wood_stop(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;

  fuusen->escape_timer -= (f32)game->graph->dt_num_60fps_frames;

  if (fuusen->escape_timer <= aFSN_ESCAPE_TIMER) {
    fuusen->escape_timer = (f32)aFSN_ESCAPE_TIMER;
    aFSN_setupAction(fuusen, game, aFSN_ACTION_ESCAPE);
  }
  else {
    xyz_t pos;
    xyz_t pos2;
    mActor_name_t* fg_item_p;
    f32 dx;
    f32 dz;

    mFI_Wpos2UtCenterWpos(&pos, actorx->world.position);
    xyz_t_move(&pos2, &pos);
    fg_item_p = mFI_GetUnitFG(actorx->world.position);

    if (fg_item_p != NULL && *fg_item_p == CEDAR_TREE) {
      pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f) + 100.0f;
      pos.z += 20.0f;
    }
    else {
      pos.x -= 2.5f;
      pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f) + 97.5f;
      pos.z += 7.5f;
    }

    dx = actorx->world.position.x - pos.x;
    dz = actorx->world.position.z - pos.z;

    if (sqrtf(dx * dx + dz * dz) > 2.0f) {
      add_calc(&actorx->world.position.x, pos.x, 1.0f - sqrtf(0.7f), 0.5f, 0.0f);
      add_calc(&actorx->world.position.y, pos.y, 1.0f - sqrtf(0.7f), 0.5f, 0.0f);
      add_calc(&actorx->world.position.z, pos.z, 1.0f - sqrtf(0.7f), 0.5f, 0.0f);
    }
    else if (mPlib_Check_tree_shaken_big(&pos2)) {
      actorx->shape_info.rotation.z = 0;
      aFSN_setupAction(fuusen, game, aFSN_ACTION_ESCAPE);
    }
    else if (mPlib_Check_tree_shaken_little(&pos2)) {
      if ((fuusen->count & 4) == 0) {
        actorx->shape_info.rotation.z = 500;
      }
      else {
        actorx->shape_info.rotation.z = -500;
        actorx->shape_info.rotation.z = 0; // set again???
      }

      fuusen->count++;
    }
    else {
      actorx->shape_info.rotation.z = 0;
      fuusen->count = 0;
    }
  }
}

static void aFSN_escape(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;
  f32 balloon_y = mCoBG_GetBalloonGroundY(&actorx->world.position);

  if (fuusen->count == 0) {
    xyz_t pos;

    mFI_Wpos2UtCenterWpos(&pos, actorx->world.position);
    if (Common_Get(clip).bg_item_clip != NULL && Common_Get(clip).bg_item_clip->item_tree_fruit_drop_proc != NULL) {
      int ut_x;
      int ut_z;

      if (mFI_Wpos2UtNum(&ut_x, &ut_z, pos)) {
        (*Common_Get(clip).bg_item_clip->fruit_set_proc)(ITM_PRESENT, ut_x, ut_z, 1, 1);
        fuusen->count = 1;
      }
    }
  }

  if (fuusen->count == 1 && actorx->world.position.y > balloon_y + 500.0f) {
    Actor_delete(actorx);
  }
}

static void aFSN_birth_init(FUUSEN_ACTOR* fuusen, GAME* game) {
  static int data_index_data[16] = {
    0, 1, 1, 2,
    2, 3, 3, 4,
    4, 5, 5, 6,
    6, 7, 7, 0
  };

  static xyz_t birth_pos_data[8] = {
    { 1600.0f, 100.0f,  500.0f }, /* X:2.5, Z:0.8 - Acre Q-2 (above A-2) */
    {  500.0f, 100.0f,  500.0f }, /* X:0.8, Z:0.8 - Acre Q-0 (top-left corner acre) */
    {  500.0f, 100.0f, 1600.0f }, /* X:0.8, Z:2.5 - Acre B-0 (left of B-1) */
    {  500.0f, 100.0f, 4620.0f }, /* X:0.8, Z:7.2 - Acre G-0 (bottom-left corner acre)*/
    { 1600.0f, 100.0f, 4620.0f }, /* X:2.5, Z:7.2 - Acre G-2 (below F-2)*/
    { 3980.0f, 100.0f, 4620.0f }, /* X:6.2, Z:7.2 - Acre F-6 (bottom-right corner) */
    { 3980.0f, 100.0f, 1600.0f }, /* X:6.2, Z:2.5 - Acre B-6 (right of B-5) */
    { 3980.0f, 100.0f,  500.0f }  /* X:6.2, Z:0.8 - Acre Q-6 (top-right corner)*/
  };

  static xyz_t birth_pos_random_data[8] = {
    { 1280.0f, 100.0f,    0.0f },
    {  960.0f, 100.0f,  960.0f },
    {    0.0f, 100.0f, 1920.0f },
    {  960.0f, 100.0f, -960.0f },
    { 1280.0f, 100.0f,    0.0f },
    { -960.0f, 100.0f, -960.0f },
    {    0.0f, 100.0f, 1920.0f },
    { -960.0f, 100.0f,  960.0f }
  };

  GAME_PLAY* play = (GAME_PLAY*)game;
  f32 balloon_y = mCoBG_GetBalloonGroundY(&fuusen->actor_class.world.position);
  int randomize_z;
  
  fuusen->actor_class.world.angle.y = mEnv_GetWindAngleS();
  fuusen->wind_idx = ((s16)(fuusen->actor_class.world.angle.y & 0xF000)) >> 12;
  fuusen->wind_idx &= 0xF;
  fuusen->wind_idx = data_index_data[fuusen->wind_idx];

  xyz_t_move(&fuusen->actor_class.world.position, &birth_pos_data[fuusen->wind_idx]);
  randomize_z = FALSE;
  fuusen->actor_class.world.position.y = balloon_y + 200.0f;
  fuusen->type_idx = play->game_frame % 5;
  fuusen->timer = 10.0f;

  if (birth_pos_random_data[fuusen->wind_idx].x != 0.0f && birth_pos_random_data[fuusen->wind_idx].z != 0.0f) {
    randomize_z = play->game_frame & 1; // randomly choose between X & Z
  }
  else if (birth_pos_random_data[fuusen->wind_idx].z != 0.0f) {
    randomize_z = TRUE; // only Z can be randomized
  }

  if (randomize_z == FALSE) {
    /* Adjust X position */
    if (birth_pos_random_data[fuusen->wind_idx].x != 0.0f) {
      f32 rng = fqrand() * fabsf(birth_pos_random_data[fuusen->wind_idx].x);

      if (birth_pos_random_data[fuusen->wind_idx].x > 0.0f) {
        fuusen->actor_class.world.position.x += rng;
      }
      else {
        fuusen->actor_class.world.position.x -= rng;
      }
    }
  }
  else {
    /* Adjust Z position */
    if (birth_pos_random_data[fuusen->wind_idx].z != 0.0f) {
      f32 rng = fqrand() * fabsf(birth_pos_random_data[fuusen->wind_idx].z);

      if (birth_pos_random_data[fuusen->wind_idx].z > 0.0f) {
        fuusen->actor_class.world.position.z += rng;
      }
      else {
        fuusen->actor_class.world.position.z -= rng;
      }
    }
  }
}

static void aFSN_moving_init(FUUSEN_ACTOR* fuusen, GAME* game) {
  fuusen->wind_change_flag = FALSE;
}

static void aFSN_wood_stop_init(FUUSEN_ACTOR* fuusen, GAME* game) {
  fuusen->actor_class.speed = 0.0f;
  fuusen->escape_timer = 18000.0f + (f32)aFSN_ESCAPE_TIMER;
  sAdo_OngenTrgStart(0x402, &fuusen->actor_class.world.position);
}

static void aFSN_escape_init(FUUSEN_ACTOR* fuusen, GAME* game) {
  PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
  ACTOR* actorx = (ACTOR*)fuusen;
  f32 dx = player->actor_class.world.position.x - actorx->world.position.x;
  f32 dz = player->actor_class.world.position.z - actorx->world.position.z;

  fuusen->count = 0;
  actorx->max_velocity_y = 5.0f;
  actorx->gravity = 0.5f;
  fuusen->look_up_flag = FALSE;

  if (fuusen->escape_timer <= (f32)aFSN_ESCAPE_TIMER) {
    fuusen->count = 1;

    /* If the balloon is within 1 acre of distance to the player when it flies away, the 'look up flag' is set */
    if (sqrtf(dx * dx + dz * dz) < (mFI_UNIT_BASE_SIZE_F * UT_BASE_NUM)) {
      fuusen->look_up_flag = TRUE;
    }
  }
}

typedef void (*aFSN_INIT_PROC)(FUUSEN_ACTOR*, GAME*);

static void aFSN_setupAction(FUUSEN_ACTOR* fuusen, GAME* game, int action) {
  static aFSN_INIT_PROC init_proc[aFSN_ACTION_NUM] = {
    &aFSN_birth_init,
    &aFSN_moving_init,
    &aFSN_wood_stop_init,
    &aFSN_escape_init
  };

  static mActor_proc act_proc[aFSN_ACTION_NUM] = {
    &aFSN_birth,
    &aFSN_moving,
    &aFSN_wood_stop,
    &aFSN_escape
  };
  
  fuusen->action = action;
  fuusen->action_proc = act_proc[action];
  (*init_proc[action])(fuusen, game);
}

static void aFSN_actor_move(ACTOR* actorx, GAME* game) {
  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;
  cKF_SkeletonInfo_R_c* keyframe_p = &fuusen->keyframe;

  if (fuusen->timer <= 0.0f) {
    Actor_position_moveF(actorx);
  }
  else if (fuusen->timer > 0) {
    fuusen->timer -= (f32)game->graph->dt_num_60fps_frames;
  }

  if (fuusen_DEBUG_mode_flag != FALSE && zurumode_flag != 0) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
    int rot_y = (int)actorx->player_angle_y - (s16)-0x8000;

    Debug_Display_new(
      player->actor_class.world.position.x + sin_s(actorx->player_angle_y - (s16)-0x8000) * 30.0f,
      player->actor_class.world.position.y + 60.0f,
      player->actor_class.world.position.z + cos_s(actorx->player_angle_y - (s16)-0x8000) * 30.0f,
      0, rot_y, 0,
      1.0f, 1.0f, 1.0f,
      250, 100, 120, 128,
      Debug_Display_SHAPE_ARROW_MODEL,
      game->graph
    );
  }

  cKF_SkeletonInfo_R_play(keyframe_p);
  (*fuusen->action_proc)(actorx, game);
}

static int aFSN_actor_draw_before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** gfx_pp, u8* data_p, void* arg, s_xyz* joint_p, xyz_t* pos_p) {
  static rgba_t balloon_prim_data[] = {
    { 255, 210, 200, 255 },
    { 200, 230, 200, 255 },
    { 255, 250, 200, 255 },
    { 220, 255, 200, 255 },
    { 240, 210, 255, 255 }
  };

  static rgba_t balloon_env_data[] = {
    { 255,  40,   0, 255 },
    {   0, 180, 255, 255 },
    { 255, 200,   0, 255 },
    { 100, 255,   0, 255 },
    { 200,  30, 255, 255 }
  };

  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)arg;
  GRAPH* graph = game->graph;
  Gfx* gfx;

  if (joint_num == 3) {
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gDPSetPrimColor(gfx++, 0, 255, balloon_prim_data[fuusen->type_idx].r, balloon_prim_data[fuusen->type_idx].g, balloon_prim_data[fuusen->type_idx].b, balloon_prim_data[fuusen->type_idx].a);
    gDPSetEnvColor(gfx++, balloon_env_data[fuusen->type_idx].r, balloon_env_data[fuusen->type_idx].g, balloon_env_data[fuusen->type_idx].b, balloon_env_data[fuusen->type_idx].a);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
  }

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  if (joint_num != 3) {
    gDPSetTexEdgeAlpha(gfx++, 80);
  }
  else {
    gDPSetTexEdgeAlpha(gfx++, 144);
  }

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);

  return TRUE;
}

extern Gfx present_DL_mode[];
extern Gfx present_DL_vtx[];

static void aFSN_actor_draw(ACTOR* actorx, GAME* game) {
  static xyz_t offset0 = { 0.0f, 0.0f, 0.0f };

  FUUSEN_ACTOR* fuusen = (FUUSEN_ACTOR*)actorx;
  N64Mtx* mtx = fuusen->mtx[game->frame_counter & 1];
  GAME_PLAY* play = (GAME_PLAY*)game;
  GRAPH* graph = game->graph;
  Gfx* gfx;

  if (
    Camera2_CheckCullingMode() == FALSE ||
    Camera2_CheckEnterCullingArea(actorx->world.position.x, actorx->world.position.z, 60.0f) == FALSE
  ) {
    Matrix_push();

    if (fuusen->action != aFSN_ACTION_ESCAPE || fuusen->escape_timer <= (f32)aFSN_ESCAPE_TIMER || (fuusen->action == aFSN_ACTION_ESCAPE && fuusen->count == 0)) {
      /* Draw present */
      Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
      Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
      Matrix_RotateX(actorx->shape_info.rotation.x, MTX_MULT);
      Matrix_RotateZ(actorx->shape_info.rotation.z, MTX_MULT);
      Matrix_RotateY(actorx->shape_info.rotation.y, MTX_MULT);
      _texture_z_light_fog_prim(graph);

      OPEN_DISP(graph);
      gfx = NOW_POLY_OPA_DISP;

      gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
      gSPDisplayList(gfx++, present_DL_mode);
      gSPDisplayList(gfx++, present_DL_vtx);

      SET_POLY_OPA_DISP(gfx);
      CLOSE_DISP(graph);
    }

    Setpos_HiliteReflect_init(&actorx->world.position, (GAME_PLAY*)game);
    cKF_Si3_draw_R_SV(game, &fuusen->keyframe, mtx, &aFSN_actor_draw_before, NULL, actorx);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gDPSetTexEdgeAlpha(gfx++, 144);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    mAc_ActorShadowDraw_ShadowDrawFlagOn(actorx, play, 0, offset0, 170.0f);
    Matrix_pull();
  }
}
