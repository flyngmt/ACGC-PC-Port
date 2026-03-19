#include "ac_birth_control.h"

#include "m_play.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "GBA2/gba2.h"

static void aBC_actor_move(ACTOR*, GAME*);

ACTOR_PROFILE Birth_Control_Profile = {
  mAc_PROFILE_BIRTH_CONTROL,
  ACTOR_PART_ITEM,
  ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(BIRTH_CONTROL_ACTOR),
  mActor_NONE_PROC1,
  mActor_NONE_PROC1,
  &aBC_actor_move,
  mActor_NONE_PROC1,
  NULL
};

static f32 aBC_pos_table[UT_BASE_NUM] = {
  mFI_UT_WORLDSIZE_X_F *  0 + mFI_UT_WORLDSIZE_HALF_X_F,  //  20.0f
  mFI_UT_WORLDSIZE_X_F *  1 + mFI_UT_WORLDSIZE_HALF_X_F,  //  60.0f
  mFI_UT_WORLDSIZE_X_F *  2 + mFI_UT_WORLDSIZE_HALF_X_F,  // 100.0f
  mFI_UT_WORLDSIZE_X_F *  3 + mFI_UT_WORLDSIZE_HALF_X_F,  // 140.0f
  mFI_UT_WORLDSIZE_X_F *  4 + mFI_UT_WORLDSIZE_HALF_X_F,  // 180.0f
  mFI_UT_WORLDSIZE_X_F *  5 + mFI_UT_WORLDSIZE_HALF_X_F,  // 220.0f
  mFI_UT_WORLDSIZE_X_F *  6 + mFI_UT_WORLDSIZE_HALF_X_F,  // 260.0f
  mFI_UT_WORLDSIZE_X_F *  7 + mFI_UT_WORLDSIZE_HALF_X_F,  // 300.0f
  mFI_UT_WORLDSIZE_X_F *  8 + mFI_UT_WORLDSIZE_HALF_X_F,  // 340.0f
  mFI_UT_WORLDSIZE_X_F *  9 + mFI_UT_WORLDSIZE_HALF_X_F,  // 380.0f
  mFI_UT_WORLDSIZE_X_F * 10 + mFI_UT_WORLDSIZE_HALF_X_F,  // 420.0f
  mFI_UT_WORLDSIZE_X_F * 11 + mFI_UT_WORLDSIZE_HALF_X_F,  // 460.0f
  mFI_UT_WORLDSIZE_X_F * 12 + mFI_UT_WORLDSIZE_HALF_X_F,  // 500.0f
  mFI_UT_WORLDSIZE_X_F * 13 + mFI_UT_WORLDSIZE_HALF_X_F,  // 540.0f
  mFI_UT_WORLDSIZE_X_F * 14 + mFI_UT_WORLDSIZE_HALF_X_F,  // 580.0f
  mFI_UT_WORLDSIZE_X_F * 15 + mFI_UT_WORLDSIZE_HALF_X_F   // 620.0f
};

static void aBC_deleteActor_part(GAME_PLAY* play, int part) {
  mFI_block_tbl_c* last_block_table = &play->last_block_table;
  s8 last_bx = last_block_table->block_x;
  s8 last_bz = last_block_table->block_z;
  s8 now_bx = play->block_table.block_x;
  s8 now_bz = play->block_table.block_z;
  s8 check_bx;
  s8 check_bz;
  ACTOR* actor = play->actor_info.list[part].actor;

  while (TRUE) {
    if (actor == NULL) {
      break;
    }
    
    check_bx = actor->block_x;
    check_bz = actor->block_z;

    /* Delete any actors which aren't in the current block or the last block */
    if (
      (check_bx >= 0 && check_bx != last_bx && check_bx != now_bx) &&
      (check_bz >= 0 && check_bz != last_bz && check_bz != now_bz)
    ) {
      Actor_delete(actor);
    }

    actor = actor->next_actor;
  }
}

static int aBC_setupOtherActor(GAME_PLAY* play, mActor_name_t actor_id, s16 profile, f32 pos_x, f32 pos_z, mActor_name_t clear_item) {
  ACTOR* actor;
  xyz_t pos;
  int res = FALSE;

  pos.x = pos_x;
  pos.z = pos_z;
  pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
  actor = Actor_info_make_actor(
    &play->actor_info,
    (GAME*)play,
    profile,
    pos.x, pos.y, pos.z,
    0, 0, 0,
    play->block_table.block_x, play->block_table.block_z,
    -1,
    actor_id,
    actor_id,
    -1,
    -1
  );

  if (actor != NULL) {
    actor->restore_fg = TRUE;
    mFI_SetFG_common(clear_item, pos, FALSE);
  }
  else {
    res = TRUE;
  }

  return res;
}

static void aBC_setupActor(BIRTH_CONTROL_ACTOR* birth_control, GAME_PLAY* play) {
  mFI_block_tbl_c* block_table = &play->block_table;
  mActor_name_t* item_p = block_table->items;
  f32 base_x = block_table->pos_x;
  f32 base_z = block_table->pos_z;
  int setup_actor_flag = FALSE;
  mActor_name_t clear_item;
  int ut_z;
  int ut_x;

  for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
    for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
      switch (ITEM_NAME_GET_TYPE(*item_p)) {
        case NAME_TYPE_ITEM2:
        {
          int idx = *item_p - ETC_START;

          setup_actor_flag |= aBC_setupOtherActor(play, *item_p, move_obj_profile_table[idx], base_x + aBC_pos_table[ut_x], base_z + aBC_pos_table[ut_z], EMPTY_NO);
          break;
        }

        case NAME_TYPE_PROPS:
        {
          int idx;

          if (*item_p >= SNOWMAN0 && *item_p <= SNOWMAN8) {
            clear_item = EMPTY_NO;
          }
          else {
            clear_item = RSV_NO;
          }

          idx = *item_p - ACTOR_PROP_START;
          setup_actor_flag |= aBC_setupOtherActor(play, *item_p, props_profile_table[idx], base_x + aBC_pos_table[ut_x], base_z + aBC_pos_table[ut_z], clear_item);
          break;
        }

        case NAME_TYPE_STRUCT:
          if (Common_Get(clip).structure_clip != NULL) {
            STRUCTURE_ACTOR* actor = (*Common_Get(clip).structure_clip->setup_actor_proc)((GAME*)play, *item_p, -1, base_x + aBC_pos_table[ut_x], base_z + aBC_pos_table[ut_z]);
            setup_actor_flag |= actor == NULL;
          }

          break;
      }

      item_p++;
    }
  }

  birth_control->setup_actor_flag = setup_actor_flag;
}

static int aBC_setupCommonMvActor(GAME_PLAY* play, mFM_move_actor_c* mv_actor_list, int mv_actor_list_no, s16 profile, f32 pos_x, f32 pos_z) {
  Actor_info* actor_info = &play->actor_info;
  xyz_t pos;
  f32 y;
  int res = FALSE;

  pos.x = pos_x;
  pos.z = pos_z;
  pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(pos, 0.0f);

  if (Actor_info_make_actor(
    actor_info,
    (GAME*)play,
    profile,
    pos.x, pos.y, pos.z,
    0, 0, 0,
    play->block_table.block_x, play->block_table.block_z,
    mv_actor_list_no,
    mv_actor_list->name_id,
    mv_actor_list->arg,
    mv_actor_list->npc_info_idx,
    -1
  ) != NULL) {
    res = TRUE;
  }

  return res;
}

static void aBC_setupMvActor(BIRTH_CONTROL_ACTOR* birth_control, GAME_PLAY* play) {
  mFM_move_actor_c* mv_actor_list_p = birth_control->move_actor_data;
  
  if (mv_actor_list_p != NULL) {
    u16 mv_actor_bitfield = birth_control->move_actor_bitfield;
    mFI_block_tbl_c* block_table = &play->block_table;
    f32 base_x = block_table->pos_x;
    f32 base_z = block_table->pos_z;
    int was_born;
    int i;

    for (i = 0; i < mFM_MOVE_ACTOR_NUM; i++) {
      if (((mv_actor_bitfield >> i) & 1) == 1) {
        mActor_name_t mv_actor_name = mv_actor_list_p->name_id;

        switch (ITEM_NAME_GET_TYPE(mv_actor_name)) {
          case NAME_TYPE_ITEM2:
            was_born = aBC_setupCommonMvActor(play, mv_actor_list_p, i, move_obj_profile_table[mv_actor_name - ETC_START], base_x + aBC_pos_table[mv_actor_list_p->ut_x], base_z + aBC_pos_table[mv_actor_list_p->ut_z]);
            break;
          case NAME_TYPE_ACTOR:
            was_born = aBC_setupCommonMvActor(play, mv_actor_list_p, i, actor_profile_table[mv_actor_name - MISC_ACTOR_START], base_x + aBC_pos_table[mv_actor_list_p->ut_x], base_z + aBC_pos_table[mv_actor_list_p->ut_z]);
            break;
          case NAME_TYPE_SPNPC:
          case NAME_TYPE_NPC:
            if (Common_Get(clip).npc_clip != NULL && Common_Get(clip).npc_clip->setupActor_proc != NULL) {
              was_born = (*Common_Get(clip).npc_clip->setupActor_proc)(play, mv_actor_name, mv_actor_list_p->npc_info_idx, i, mv_actor_list_p->arg, block_table->block_x, block_table->block_z, mv_actor_list_p->ut_x, mv_actor_list_p->ut_z);
            }
            else {
              was_born = FALSE;
            }
            break;
          default:
            was_born = FALSE;
            break;
        }

        if (was_born == TRUE) {
          mv_actor_bitfield = ~(1 << i) & mv_actor_bitfield;
        }
      }

      mv_actor_list_p++;
    }

    birth_control->move_actor_bitfield = mv_actor_bitfield;
  }
}

static int aBC_chk_near_boat_block(BIRTH_CONTROL_ACTOR* birth_control, GAME_PLAY* play) {
  /* Check to spawn boat while in E-5 or F-4 */
  static int chk_bx[] = { 5, 4 }; // 4 & 5 column
  static int chk_bz[] = { 5, 6 }; // E & F row
  int res = FALSE;
  int i;

  for (i = 0; i < 2; i++) {
    if (play->block_table.block_x == chk_bx[i] && play->block_table.block_z == chk_bz[i]) {
      if (birth_control->boat_spawned == FALSE) {
        mGcgba_InitVar();
        birth_control->boat_spawned = TRUE;
      }
      
      res = TRUE;
      break;
    }
  }

  return res;
}

static void aBC_set_boat(BIRTH_CONTROL_ACTOR* birth_control, GAME_PLAY* play) {
  if (mEv_IsNotTitleDemo() && aBC_chk_near_boat_block(birth_control, play) == TRUE) {
    mActor_name_t* boat_ut_p = mFI_UtNum2UtFG(5 * UT_X_NUM + 5, 6 * UT_Z_NUM + 10); // Set boat at F-5, unit 5-10 (x-z)

    if (boat_ut_p != NULL) {
      mActor_name_t boat_item = *boat_ut_p;

      switch (mGcgba_ConnectEnabled()) {
        case GBA2_GBA_STATE_SUCCESS:
          /* Successfully connected to the GBA */
          mGcgba_InitVar();
          boat_item = BOAT; // set boat
          break;
        default:
          /* Failed to connect to the GBA */
          mGcgba_InitVar();
          boat_item = EMPTY_NO; // clear boat
          break;
        case GBA2_GBA_STATE_TRANSMITTING:
          /* Still transmitting */
          break;
      }

      *boat_ut_p = boat_item;
    }
  }
  else {
    /* We're not in a boat acre, so allow initial communication again */
    birth_control->boat_spawned = FALSE;
  }
}

static void aBC_actor_move(ACTOR* actorx, GAME* game) {
  BIRTH_CONTROL_ACTOR* birth_control = (BIRTH_CONTROL_ACTOR*)actorx;
  GAME_PLAY* play = (GAME_PLAY*)game;
  if (Common_Get(bg_item_type) == 0) {
    birth_control->setup_actor_flag |= mFI_ActorisBorn() == TRUE;
    aBC_set_boat(birth_control, play);
  }

  if (mFI_ActorisBorn() == TRUE) {
    int bx = play->block_table.block_x;
    int bz = play->block_table.block_z;
    birth_control->move_actor_data = mFI_MoveActorListDma(bx, bz);
    mNpc_AddActor_inBlock(birth_control->move_actor_data, bx, bz);

    if (birth_control->move_actor_data != NULL) {
      birth_control->move_actor_bitfield = mFI_GetMoveActorBitData(bx, bz);
      birth_control->move_actor_list_exists_flag = TRUE;
    }
    else {
      birth_control->move_actor_bitfield = 0;
    }
  }

  g_fdinfo->born_actor = FALSE;
  
  if (play->game.pad_initialized == TRUE) {
    if (birth_control->setup_actor_flag) {
      aBC_deleteActor_part(play, ACTOR_PART_ITEM);
      aBC_setupActor(birth_control, play);
    }

    if (birth_control->move_actor_list_exists_flag == TRUE && birth_control->move_actor_bitfield != 0) {
      int bx = play->block_table.block_x;
      int bz = play->block_table.block_z;

      aBC_deleteActor_part(play, ACTOR_PART_NPC);
      aBC_setupMvActor(birth_control, play);
      mFI_SetMoveActorBitData(bx, bz, birth_control->move_actor_bitfield);
    }
  }

  /* Only refresh the list when transitioning between acres or transitioning between scenes */
  if (mFI_CheckPlayerWade(mFI_WADE_NONE) == TRUE && play->fb_fade_type == FADE_TYPE_NONE) {
    birth_control->move_actor_list_exists_flag = FALSE;
  }
}
