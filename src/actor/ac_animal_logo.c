#include "ac_animal_logo.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_event.h"
#include "m_play.h"
#include "m_bgm.h"
#include "m_npc.h"
#include "libc64/qrand.h"
#include "m_name_table.h"
#include "padmgr.h"
#include "audio.h"
#include "Famicom/famicom.h"
#include "m_land.h"
#include "m_titledemo.h"
#include "m_card.h"
#include "m_rcp.h"
#include "m_cpak.h"
#include "sys_matrix.h"
#include "m_time.h"
#include "m_font.h"
#include "libultra/libultra.h"
#include "m_flashrom.h"
#ifdef PC_ENHANCEMENTS
#include "pc_settings.h"
#include "main.h"
#include <stdio.h>
#endif

#define G_CC_TITLE PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0
#define G_CC_TM 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define G_CC_BACK 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define G_CC_PRESS_START PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0

#define TITLE_WIDTH 64
#define TITLE_HEIGHT 16

#if VERSION == VER_GAFE01_00
#define aAL_IN_FRAMES 121.0f
#elif VERSION == VER_GAFU01_00
#define aAL_IN_FRAMES 101.0f
#endif

extern u8 log_win_nintendo1_tex[];
extern u8 log_win_nintendo2_tex[];
extern u8 log_win_nintendo3_tex[];

extern Gfx logo_us_tm_model[];

extern Gfx logo_us_backA_model[];
extern Gfx logo_us_backB_model[];
extern Gfx logo_us_backC_model[];
extern Gfx logo_us_backD_model[];

extern u8 log_win_logo3_tex[];
extern u8 log_win_logo4_tex[];

extern cKF_Skeleton_R_c cKF_bs_r_logo_us_animal;
extern cKF_Skeleton_R_c cKF_bs_r_logo_us_cros;
extern cKF_Skeleton_R_c cKF_bs_r_logo_us_sing;

static void aAL_actor_ct(ACTOR* actor, GAME* game);
static void aAL_actor_dt(ACTOR* actor, GAME* game);
static void aAL_actor_move(ACTOR* actor, GAME* game);
static void aAL_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Animal_Logo_Profile = {
  mAc_PROFILE_ANIMAL_LOGO,
  ACTOR_PART_BG,
  ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(ANIMAL_LOGO_ACTOR),
  &aAL_actor_ct,
  &aAL_actor_dt,
  &aAL_actor_move,
  &aAL_actor_draw,
  NULL
};

#include "../src/actor/ac_animal_logo_misc.c"

static void aAL_setupAction(ANIMAL_LOGO_ACTOR* actor, GAME* game, int action);
static void aAL_title_decide_p_sel_npc();

static void aAL_actor_ct(ACTOR* actor, GAME* game) {
  ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;
  GAME_PLAY* play = (GAME_PLAY*)game;
  Clip_c* clip = Common_GetPointer(clip);
  aAL_SkeletonInfo_c* skeleton_info;

#ifdef TARGET_PC
  { extern int g_pc_verbose; if (g_pc_verbose) printf("[LOGO] aAL_actor_ct: Animal Logo actor created\n"); }
#else
  printf("[LOGO] aAL_actor_ct: Animal Logo actor created\n");
#endif

  if (clip->animal_logo_clip == NULL) {
    clip->animal_logo_clip = (aAL_Clip_c*)zelda_malloc(sizeof(aAL_Clip_c));
    clip->animal_logo_clip->data_init_proc = &title_action_data_init_start_select;
  }

  skeleton_info = &logo_actor->animal;
  skeleton_info->work_area_p = logo_actor->animal_work_area;
  skeleton_info->morph_area_p = logo_actor->animal_morph_area;
  cKF_SkeletonInfo_R_ct(&skeleton_info->skeleton, &cKF_bs_r_logo_us_animal, NULL, skeleton_info->work_area_p, skeleton_info->morph_area_p);

  skeleton_info = &logo_actor->cros;
  skeleton_info->work_area_p = logo_actor->cros_work_area;
  skeleton_info->morph_area_p = logo_actor->cros_morph_area;
  cKF_SkeletonInfo_R_ct(&skeleton_info->skeleton, &cKF_bs_r_logo_us_cros, NULL, skeleton_info->work_area_p, skeleton_info->morph_area_p);


  skeleton_info = &logo_actor->sing;
  skeleton_info->work_area_p = logo_actor->sing_work_area;
  skeleton_info->morph_area_p = logo_actor->sing_morph_area;
  cKF_SkeletonInfo_R_ct(&skeleton_info->skeleton, &cKF_bs_r_logo_us_sing, NULL, skeleton_info->work_area_p, skeleton_info->morph_area_p);

  aAL_setupAction(logo_actor, (GAME*)play, aAL_ACTION_IN);
}

static void aAL_actor_dt(ACTOR* actor, GAME* game) {
  ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;

  if (Common_Get(clip.animal_logo_clip) != NULL) {
    zelda_free(Common_Get(clip.animal_logo_clip));
    Common_Set(clip.animal_logo_clip, NULL);
  }

  if (mEv_CheckTitleDemo() != mEv_TITLEDEMO_LOGO) {
    mEv_SetTitleDemo(mEv_TITLEDEMO_NONE);
  }

  cKF_SkeletonInfo_R_dt(&logo_actor->animal.skeleton);
  cKF_SkeletonInfo_R_dt(&logo_actor->cros.skeleton);
  cKF_SkeletonInfo_R_dt(&logo_actor->sing.skeleton);

  if (mFRm_CheckSaveData() == TRUE) {
    aAL_title_decide_p_sel_npc();
  }
}

static void aAL_title_game_data_init_start_select(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  GAME_PLAY* play = (GAME_PLAY*)game;

#ifdef TARGET_PC
  /* Reload save from disk; the title demo mutated save data in RAM.
   * On GC the memory card is re-read; on PC re-read the GCI file. */
  if (pc_save_loaded) {
    pc_save_reload();
  }
#endif

  play->fb_fade_type = FADE_TYPE_SELECT;
  play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;
  Common_Set(transition.wipe_type, WIPE_TYPE_FADE_BLACK);
  mBGMPsComp_make_ps_wipe(0x1168);
}

static void aAL_title_decide_p_sel_npc() {
  int selected;
  mActor_name_t npc_name;
  int idx;

  while (TRUE) {
    selected = (int)(fqrand() * (f32)ANIMAL_NUM_MAX);
    if (mNpc_CheckFreeAnimalPersonalID(Save_GetPointer(animals[selected].id)) == FALSE) {
      npc_name = Save_Get(animals[selected].id.npc_id);
      break;
    }
  }
  
  idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_name, ANIMAL_NUM_MAX);
  mNpc_RegistEventNpc(SP_NPC_P_SEL2, npc_name, npc_name, Save_Get(animals[idx].cloth));
}

static int aAL_wipe_end_check(GAME* game) {
  GAME_PLAY* play = (GAME_PLAY*)game;
  int res = FALSE;
  fbdemo_wipe* wipe = &play->fbdemo_wipe;

  if ((*wipe->wipe_procs.isfinished_proc)(&wipe->wipe_data)) {
    res = TRUE;
  }

  return res;
}

static int aAL_chk_start_key() {
  int res = FALSE;

  if (padmgr_isConnectedController(PAD0) && ((gamePT->pads[PAD0].on.button & BUTTON_START) == BUTTON_START || (gamePT->pads[PAD0].on.button & BUTTON_A) == BUTTON_A)) {
    res = TRUE;
  }

  return res;
}

static int aAL_chk_start_key2(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  int res = FALSE;

  if (aAL_chk_start_key() == TRUE) {
    aAL_setupAction(actor, game, aAL_ACTION_START_KEY_CHK_START);
    res = TRUE;
  }

  return res;
}

static void aAL_logo_in(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  int animal_done;
  int cros_done;
  int sing_done;
    
  if (aAL_chk_start_key2(actor, game) == FALSE) {
    animal_done = cKF_SkeletonInfo_R_play(&actor->animal.skeleton);
    cros_done = cKF_SkeletonInfo_R_play(&actor->cros.skeleton);
    sing_done = cKF_SkeletonInfo_R_play(&actor->sing.skeleton);
    if (animal_done == TRUE && cros_done == TRUE && sing_done == TRUE) {
      aAL_setupAction(actor, game, aAL_ACTION_BACK_FADE_IN);
    }
  }
}

static void aAL_back_fadein(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  if (aAL_chk_start_key2(actor, game) == FALSE) {
    s16 opacity = actor->back_opacity;
    opacity += aAL_BACK_FADEIN_RATE;
    
    if (opacity > aAL_BACK_FADEIN_MAX) {
      opacity = aAL_BACK_FADEIN_MAX;
      aAL_setupAction(actor, game, aAL_ACTION_START_KEY_CHK_START);
    }

    actor->back_opacity = opacity;
  }
}

static void aAL_start_key_chk_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  if (padmgr_isConnectedController(PAD0) && actor->title_timer <= 0 && famicom_mount_archive_end_check()) {
    aAL_setupAction(actor, game, aAL_ACTION_GAME_START);
  }
}

static void aAL_game_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  GAME_PLAY* play = (GAME_PLAY*)game;
  f32 start_opacity;
  s16 t;
  s16 new_opacity_timer;

  new_opacity_timer = actor->start_opacity_timer;
  new_opacity_timer += (s16)(32768.0f / (actor->start_opacity_timer > 0 ? 50.0f : 22.0f));
  start_opacity = 127.5f * sin_s(new_opacity_timer) + 127.5f; // 127.5f + 127.5f * [0, 1] = [127.5f, 255.0f] (opacity)

  if (start_opacity > 255.0f) {
    start_opacity = 255.0f;
  }
  else if (start_opacity < 0.0f) {
    start_opacity = 0.0f;
  }

  actor->press_start_opacity = start_opacity;
  actor->start_opacity_timer = new_opacity_timer;

  if (play->fb_fade_type == FADE_TYPE_SELECT_END) {
    aAL_setupAction(actor, game, aAL_ACTION_6);
  }
  else if (
     ((gamePT->pads[PAD0].on.button & BUTTON_START) == BUTTON_START || (gamePT->pads[PAD0].on.button & BUTTON_A) == BUTTON_A) &&
     mLd_CheckStartFlag() == TRUE &&
     aAL_wipe_end_check(game) == TRUE &&
     mTD_tdemo_button_ok_check()
  ) {
    aAL_setupAction(actor, game, aAL_ACTION_FADE_OUT_START);
  }
}

static void aAL_fade_out_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  if (actor->title_timer <= 0) {
    aAL_title_game_data_init_start_select(actor, game);
    aAL_setupAction(actor, game, aAL_ACTION_OUT);
  }
}

extern cKF_Animation_R_c cKF_ba_r_logo_us_animal;
extern cKF_Animation_R_c cKF_ba_r_logo_us_cros;
extern cKF_Animation_R_c cKF_ba_r_logo_us_sing;

static void aAL_logo_in_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  cKF_SkeletonInfo_R_init(&actor->animal.skeleton, actor->animal.skeleton.skeleton, &cKF_ba_r_logo_us_animal, 1.0f, aAL_IN_FRAMES, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP, NULL);
  cKF_SkeletonInfo_R_init(&actor->cros.skeleton, actor->cros.skeleton.skeleton, &cKF_ba_r_logo_us_cros, 1.0f, aAL_IN_FRAMES, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP, NULL);
  cKF_SkeletonInfo_R_init(&actor->sing.skeleton, actor->sing.skeleton.skeleton, &cKF_ba_r_logo_us_sing, 1.0f, aAL_IN_FRAMES, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP, NULL);

  actor->copyright_opacity = 0;
  actor->titledemo_no = mTD_get_titledemo_no();

  mCD_set_aram_save_data();
  lbRTC_GetTime(Common_GetPointer(time.rtc_time));
  Common_Set(player_no, 0);
  Common_Set(player_data_mode, 0);
  Common_Set(scene_from_title_demo, -1);
}

static void aAL_back_fadein_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  actor->back_opacity = 0;
}

static void aAL_start_key_chk_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  /* move all animations to the final frame (in case animation was skipped) */
  actor->animal.skeleton.frame_control.current_frame = actor->animal.skeleton.frame_control.end_frame;
  actor->cros.skeleton.frame_control.current_frame = actor->cros.skeleton.frame_control.end_frame;
  actor->sing.skeleton.frame_control.current_frame = actor->sing.skeleton.frame_control.end_frame;

  cKF_SkeletonInfo_R_play(&actor->animal.skeleton);
  cKF_SkeletonInfo_R_play(&actor->cros.skeleton);
  cKF_SkeletonInfo_R_play(&actor->sing.skeleton);

  actor->copyright_opacity = 255;
  actor->back_opacity = aAL_BACK_FADEIN_MAX;
  actor->title_timer = aAL_TIMER;
}

static void aAL_fade_out_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  sAdo_SysTrgStart(0x44D);
  actor->title_timer = aAL_FADEOUT_TIMER;
  actor->press_start_opacity = 255.0f;
}

#ifdef PC_ENHANCEMENTS
static void aAL_pc_game_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  GAME_PLAY* play = (GAME_PLAY*)game;
  u16 on_btn = gamePT->pads[PAD0].on.button;
  s8 stick_y = gamePT->pads[PAD0].now.stick_y;

  /* No blinking — full opacity for menu */
  actor->press_start_opacity = 255.0f;

  if (play->fb_fade_type == FADE_TYPE_SELECT_END) {
    aAL_setupAction(actor, game, aAL_ACTION_6);
    return;
  }

  /* Debounce */
  if (actor->pc_cursor_cooldown > 0) {
    actor->pc_cursor_cooldown--;
  }

  if (actor->pc_options_open) {
    s8 stick_x = gamePT->pads[PAD0].now.stick_x;
    int changed = 0;

    /* START to save, apply, and close */
    if (on_btn & BUTTON_START) {
      pc_settings_save();
      pc_settings_apply();
      actor->pc_options_open = 0;
      actor->pc_cursor_cooldown = 10;
      return;
    }

    /* B to discard and close */
    if (on_btn & BUTTON_B) {
      pc_settings_load();
      actor->pc_options_open = 0;
      actor->pc_cursor_cooldown = 10;
      return;
    }

    /* Up/down navigation within options (5 items: 0=res, 1=fs, 2=vsync, 3=msaa, 4=textures) */
    if (actor->pc_cursor_cooldown == 0) {
      if (stick_y > 30 || (on_btn & BUTTON_DUP)) {
        if (actor->pc_options_sel > 0) { actor->pc_options_sel--; actor->pc_cursor_cooldown = 8; }
      } else if (stick_y < -30 || (on_btn & BUTTON_DDOWN)) {
        if (actor->pc_options_sel < 4) { actor->pc_options_sel++; actor->pc_cursor_cooldown = 8; }
      }

      /* Left/right to change values */
      /* Resolution presets — custom .ini values snap to nearest on left/right */
      {
        static const int res_w[] = { 640, 960, 1280, 1600, 1920, 2560, 3840 };
        static const int res_h[] = { 480, 720,  720,  900, 1080, 1440, 2160 };
        enum { RES_COUNT = 7 };

      if (stick_x > 30 || (on_btn & BUTTON_DRIGHT)) {
        changed = 1; actor->pc_cursor_cooldown = 8;
        switch (actor->pc_options_sel) {
          case 0: { /* Resolution — cycle up */
            int i;
            for (i = 0; i < RES_COUNT - 1; i++) {
              if (g_pc_settings.window_width <= res_w[i]) break;
            }
            if (i < RES_COUNT - 1) i++;
            g_pc_settings.window_width = res_w[i];
            g_pc_settings.window_height = res_h[i];
          } break;
          case 1: g_pc_settings.fullscreen = (g_pc_settings.fullscreen + 1) % 3; break;
          case 2: g_pc_settings.vsync = !g_pc_settings.vsync; break;
          case 3: { /* MSAA cycle up: 0→2→4→8 */
            if (g_pc_settings.msaa == 0) g_pc_settings.msaa = 2;
            else if (g_pc_settings.msaa < 8) g_pc_settings.msaa *= 2;
          } break;
          case 4: { /* Textures cycle up: 0→1→2 */
            if (g_pc_settings.preload_textures < 2) g_pc_settings.preload_textures++;
          } break;
        }
      } else if (stick_x < -30 || (on_btn & BUTTON_DLEFT)) {
        changed = 1; actor->pc_cursor_cooldown = 8;
        switch (actor->pc_options_sel) {
          case 0: { /* Resolution — cycle down */
            int i;
            for (i = RES_COUNT - 1; i > 0; i--) {
              if (g_pc_settings.window_width >= res_w[i]) break;
            }
            if (i > 0) i--;
            g_pc_settings.window_width = res_w[i];
            g_pc_settings.window_height = res_h[i];
          } break;
          case 1: g_pc_settings.fullscreen = (g_pc_settings.fullscreen + 2) % 3; break;
          case 2: g_pc_settings.vsync = !g_pc_settings.vsync; break;
          case 3: { /* MSAA cycle down: 8→4→2→0 */
            if (g_pc_settings.msaa > 2) g_pc_settings.msaa /= 2;
            else g_pc_settings.msaa = 0;
          } break;
          case 4: { /* Textures cycle down: 2→1→0 */
            if (g_pc_settings.preload_textures > 0) g_pc_settings.preload_textures--;
          } break;
        }
      }
      } /* end resolution presets block */
    }
    (void)changed;
    return;
  }

  /* Main menu navigation */
  if (actor->pc_cursor_cooldown == 0) {
    if (stick_y > 30 || (on_btn & BUTTON_DUP)) {
      if (actor->pc_menu_sel > 0) {
        actor->pc_menu_sel--;
        actor->pc_cursor_cooldown = 10;
      }
    } else if (stick_y < -30 || (on_btn & BUTTON_DDOWN)) {
      if (actor->pc_menu_sel < 1) {
        actor->pc_menu_sel++;
        actor->pc_cursor_cooldown = 10;
      }
    }
  }

  /* Select */
  if (on_btn & (BUTTON_A | BUTTON_START)) {
    if (actor->pc_menu_sel == 0) {
      /* Start Game */
      if (mLd_CheckStartFlag() == TRUE &&
          aAL_wipe_end_check(game) == TRUE &&
          mTD_tdemo_button_ok_check()) {
        aAL_setupAction(actor, game, aAL_ACTION_FADE_OUT_START);
      }
    } else {
      /* Options */
      actor->pc_options_open = 1;
      actor->pc_cursor_cooldown = 10;
    }
  }
}
#endif

static void aAL_setupAction(ANIMAL_LOGO_ACTOR* actor, GAME* game, int action) {
  static const ANIMAL_LOGO_ACTION_PROC init_proc[aAL_ACTION_NUM] = {
    &aAL_logo_in_init,
    &aAL_back_fadein_init,
    &aAL_start_key_chk_start_wait_init,
    (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
    &aAL_fade_out_start_wait_init,
    (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
    (ANIMAL_LOGO_ACTION_PROC)&none_proc1
  };

  static ANIMAL_LOGO_ACTION_PROC process[aAL_ACTION_NUM] = {
    &aAL_logo_in,
    &aAL_back_fadein,
    &aAL_start_key_chk_start_wait,
#ifdef PC_ENHANCEMENTS
    (ANIMAL_LOGO_ACTION_PROC)&aAL_pc_game_start_wait,
#else
    &aAL_game_start_wait,
#endif
    &aAL_fade_out_start_wait,
    (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
    (ANIMAL_LOGO_ACTION_PROC)&none_proc1
  };

#ifdef TARGET_PC
  { extern int g_pc_verbose; if (g_pc_verbose) printf("[LOGO] aAL_setupAction: %d -> %d\n", actor->action, action); }
#else
  printf("[LOGO] aAL_setupAction: %d -> %d\n", actor->action, action);
#endif
  (*init_proc[action])(actor, game);
  actor->action = action;
  actor->action_proc = process[action];
}

static void aAL_actor_move(ACTOR* actor, GAME* game) {
  ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;

  lbRTC_Sampling();
  if (logo_actor->title_timer > 0) {
    logo_actor->title_timer--;
  }

  (*logo_actor->action_proc)(logo_actor, game);
}

#if VERSION == VER_GAFE01_00
static void aAL_copyright_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
  static const u32 draw_pos_x[3] = { 61, 125, 189 };
  static const u32 draw_pos_y[3] = { 198, 198, 198 };

  Gfx* gfx;

  actor->copyright_opacity += aAL_COPYRIGHT_ALPHA_RATE;
  if (actor->copyright_opacity >= 255) {
    actor->copyright_opacity = 255;
  }

  OPEN_DISP(graph);

  gfx = NOW_FONT_DISP;
  gDPSetPrimColor(gfx++, 0, 255, 40, 40, 45, actor->copyright_opacity);
  gDPSetEnvColor(gfx++, 210, 210, 215, 0);
  gDPSetOtherMode(gfx++, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2);
  gSPLoadGeometryMode(gfx++, 0);
  gDPSetCombineMode(gfx++, G_CC_TITLE, G_CC_TITLE);

  gDPLoadTextureTile(
    gfx++,
    log_win_nintendo1_tex,
    G_IM_FMT_IA, G_IM_SIZ_8b,
    TITLE_WIDTH, TITLE_HEIGHT,
    0, 0, TITLE_WIDTH - 1, TITLE_HEIGHT - 1,
    0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
  );
  gfx = gfx_gSPTextureRectangle1(
    gfx,
    draw_pos_x[0] << 2, draw_pos_y[0] << 2,
    (TITLE_WIDTH + draw_pos_x[0]) << 2, (TITLE_HEIGHT + draw_pos_y[0]) << 2,
    0,
    0 << 5, 0 << 5,
    1 << 10, 1 << 10
  );

  gDPLoadTextureTile(
    gfx++,
    log_win_nintendo2_tex,
    G_IM_FMT_IA, G_IM_SIZ_8b,
    TITLE_WIDTH, TITLE_HEIGHT,
    0, 0, TITLE_WIDTH - 1, TITLE_HEIGHT - 1,
    0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
  );
  gfx = gfx_gSPTextureRectangle1(
    gfx,
    draw_pos_x[1] << 2, draw_pos_y[1] << 2,
    (TITLE_WIDTH + draw_pos_x[1]) << 2, (TITLE_HEIGHT + draw_pos_y[1]) << 2,
    0,
    0 << 5, 0 << 5,
    1 << 10, 1 << 10
  );

  gDPLoadTextureTile(
    gfx++,
    log_win_nintendo3_tex,
    G_IM_FMT_IA, G_IM_SIZ_8b,
    TITLE_WIDTH, TITLE_HEIGHT,
    0, 0, TITLE_WIDTH - 1, TITLE_HEIGHT - 1,
    0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
  );
  gfx = gfx_gSPTextureRectangle1(
    gfx,
    draw_pos_x[2] << 2, draw_pos_y[2] << 2,
    (TITLE_WIDTH + draw_pos_x[2]) << 2, (TITLE_HEIGHT + draw_pos_y[2]) << 2,
    0,
    0 << 5, 0 << 5,
    1 << 10, 1 << 10
  );

  SET_FONT_DISP(gfx);

  CLOSE_DISP(graph);
}
#elif VERSION == VER_GAFU01_00
extern Gfx logo_nin_copyT_model[];

static void aAL_copyright_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
    // clang-format off
    static const Gfx init_disp[] = {
        gsSPTexture(0, 0, 0, 0, G_ON),
        gsSPLoadGeometryMode(G_CULL_BACK),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
        gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
        gsSPEndDisplayList(),
    };
    // clang-format on

    actor->copyright_opacity += aAL_COPYRIGHT_ALPHA_RATE;
    if (actor->copyright_opacity >= 255) {
        actor->copyright_opacity = 255;
    }

    Matrix_push();

    OPEN_FONT_DISP(graph);

    Matrix_translate(32.0f, -1376.0f, 0.0f, MTX_MULT);
    Matrix_scale(0.16208267f, 0.16208267f, 0.16208267f, MTX_MULT);
    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 255, 255, actor->copyright_opacity);
    gSPDisplayList(FONT_DISP++, init_disp);
    gSPDisplayList(FONT_DISP++, logo_nin_copyT_model);

    CLOSE_FONT_DISP(graph);

    Matrix_pull();
}
#endif

static void aAL_tm_draw(GRAPH* graph) {
  static const Gfx init_disp[] = {
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_TM, G_CC_TM),
    gsSPEndDisplayList()
  };

  Gfx* gfx;

  Matrix_push();
  Matrix_translate(1530.0f, 690.0f, 0.0f, MTX_MULT);
  Matrix_scale(0.162082675f, 0.162082675f, 0.162082675f, MTX_MULT);

  OPEN_DISP(graph);

  gfx = NOW_FONT_DISP;
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPDisplayList(gfx++, init_disp);
  gSPDisplayList(gfx++, logo_us_tm_model);
  SET_FONT_DISP(gfx);
  
  CLOSE_DISP(graph);

  Matrix_pull();
}

static void aAL_back_draw(GRAPH* graph, ANIMAL_LOGO_ACTOR* actor) {
  static const Gfx init_disp[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_BACK, G_CC_BACK),
    gsSPEndDisplayList()
  };

  Gfx* gfx;

  Matrix_push();
  Matrix_translate(0.0f, 730.0f, 0.0f, MTX_MULT);
  Matrix_scale(0.135f, 0.135f, 0.135f, MTX_MULT);

  OPEN_DISP(graph);

  gfx = NOW_FONT_DISP;
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gDPSetPrimColor(gfx++, 0, 255, 80, 60, 0, actor->back_opacity);
  gSPDisplayList(gfx++, init_disp);
  gSPDisplayList(gfx++, logo_us_backA_model);
  gSPDisplayList(gfx++, logo_us_backB_model);
  gSPDisplayList(gfx++, logo_us_backC_model);
  gSPDisplayList(gfx++, logo_us_backD_model);
  SET_FONT_DISP(gfx);

  CLOSE_DISP(graph);

  Matrix_pull();
}

static void aAL_press_start_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
  static const u32 draw_pos_x[2] = { 96, 160 };
  static const u32 draw_pos_y[2] = { 159, 159 };

  static const u32 ps_prim_r[5] = { 70, 60, 60, 40, 40 };
  static const u32 ps_prim_g[5] = { 40, 50, 40, 50, 50 };
  static const u32 ps_prim_b[5] = { 40, 30, 60, 70, 60 };
  
  static const u32 ps_env_r[5] = { 255, 255, 255, 120, 165 };
  static const u32 ps_env_g[5] = {  90, 135, 100, 205, 245 };
  static const u32 ps_env_b[5] = {  30,   0, 255, 245,   0 };

  Gfx* gfx;
  int titledemo_no;
  f32 alpha;
  titledemo_no = actor->titledemo_no;
  alpha = actor->press_start_opacity;

  OPEN_DISP(graph);

  gfx = NOW_FONT_DISP;
  gDPSetPrimColor(gfx++, 0, 255, ps_prim_r[titledemo_no], ps_prim_g[titledemo_no], ps_prim_b[titledemo_no], (u32)alpha);
  gDPSetEnvColor(gfx++, ps_env_r[titledemo_no], ps_env_g[titledemo_no], ps_env_b[titledemo_no], 0);
  gDPSetOtherMode(gfx++, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
  gSPLoadGeometryMode(gfx++, 0);
  gDPSetCombineMode(gfx++, G_CC_PRESS_START, G_CC_PRESS_START);

  gDPLoadTextureTile(
    gfx++,
    log_win_logo3_tex,
    G_IM_FMT_IA, G_IM_SIZ_8b,
    TITLE_WIDTH, TITLE_HEIGHT,
    0, 0, TITLE_WIDTH - 1, TITLE_HEIGHT - 1,
    0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
  );

  gfx = gfx_gSPTextureRectangle1(
    gfx,
    draw_pos_x[0] << 2, draw_pos_y[0] << 2,
    (TITLE_WIDTH + draw_pos_x[0]) << 2, (TITLE_HEIGHT + draw_pos_y[0]) << 2,
    0,
    0 << 5, 0 << 5,
    1 << 10, 1 << 10
  );

  gDPLoadTextureTile(
    gfx++,
    log_win_logo4_tex,
    G_IM_FMT_IA, G_IM_SIZ_8b,
    TITLE_WIDTH, TITLE_HEIGHT,
    0, 0, TITLE_WIDTH - 1, TITLE_HEIGHT - 1,
    0,
    G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
  );

  gfx = gfx_gSPTextureRectangle1(
    gfx,
    draw_pos_x[1] << 2, draw_pos_y[1] << 2,
    (TITLE_WIDTH + draw_pos_x[1]) << 2, (TITLE_HEIGHT + draw_pos_y[1]) << 2,
    0,
    0 << 5, 0 << 5,
    1 << 10, 1 << 10
  );

  SET_FONT_DISP(gfx);

  CLOSE_DISP(graph);
}

static void aAL_skl_draw(GAME* game, cKF_SkeletonInfo_R_c* skl_keyframe) {
  Mtx* m;

  OPEN_DISP(game->graph);

  m = GRAPH_ALLOC_TYPE(game->graph, Mtx, skl_keyframe->skeleton->num_shown_joints);
  if (m != NULL) {
    cKF_Si3_draw_R_SV(game, skl_keyframe, m, NULL, NULL, NULL);
  }

  CLOSE_DISP(game->graph);
}

static void aAL_title_draw(GAME* game, ANIMAL_LOGO_ACTOR* actor) {
  static const Gfx init_disp[] = {
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPEndDisplayList()
  };

  Gfx* poly_save;
  GRAPH* graph = game->graph;

  Matrix_push();
  Matrix_translate(0.0f, 730.0f, 0.0f, MTX_MULT);
  Matrix_scale(0.135f, 0.135f, 0.135f, MTX_MULT);

  OPEN_DISP(graph);

  // we need to save the opaque polygon gfx buffer and swap with font because cKF utilizes opaque polygon gfx,
  // but we want this on the font gfx buffer
  poly_save = NOW_POLY_OPA_DISP;
  SET_POLY_OPA_DISP(NOW_FONT_DISP);
  gSPMatrix(NOW_POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPDisplayList(NOW_POLY_OPA_DISP++, init_disp);
  
  aAL_skl_draw(game, &actor->animal.skeleton);
  aAL_skl_draw(game, &actor->cros.skeleton);
  aAL_skl_draw(game, &actor->sing.skeleton);

  SET_FONT_DISP(NOW_POLY_OPA_DISP);
  SET_POLY_OPA_DISP(poly_save);

  CLOSE_DISP(graph);

  Matrix_pull();
}

#ifdef PC_ENHANCEMENTS
static void aAL_pc_options_draw(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  GRAPH* graph = game->graph;
  char buf[48];
  int len;
  f32 x = 80.0f;
  f32 y = 68.0f;
  f32 line_h = 16.0f;

  /* Semi-transparent background behind options panel */
  {
    Gfx* gfx;
    int x0 = 45, y0_bg = 58, x1 = 295, y1_bg = 196;
    OPEN_DISP(graph);
    gfx = NOW_FONT_DISP;
    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
      G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT |
      G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
      G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
      G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 160);
    gfx = gfx_gSPTextureRectangle1(gfx,
      x0 << 2, y0_bg << 2, x1 << 2, y1_bg << 2,
      0, 0, 0, 0, 0);
    gDPPipeSync(gfx++);
    SET_FONT_DISP(gfx);
    CLOSE_DISP(graph);
  }

  int sel = actor->pc_options_sel;
  int item = 0;
  static u8 str_arrow[] = { '>' };

  /* Title */
  {
    static u8 str_title[] = { '-', ' ', 'O', 'p', 't', 'i', 'o', 'n', 's', ' ', '-' };
    f32 tw = (f32)mFont_GetStringWidth(str_title, sizeof(str_title), TRUE);
    mFont_SetLineStrings(game, str_title, sizeof(str_title),
      (SCREEN_WIDTH_F - tw) * 0.5f, y,
      255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  y += line_h * 1.2f;

  /* Resolution */
  len = sprintf(buf, "< %dx%d >", g_pc_settings.window_width, g_pc_settings.window_height);
  {
    static u8 lbl[] = { 'R', 'e', 's', 'o', 'l', 'u', 't', 'i', 'o', 'n' };
    mFont_SetLineStrings(game, lbl, sizeof(lbl), x, y,
      sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
      sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  mFont_SetLineStrings(game, (u8*)buf, len, 180.0f, y,
    sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
    sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  if (sel == item) mFont_SetLineStrings(game, str_arrow, 1, x - 12.0f, y, 255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  item++; y += line_h;

  /* Fullscreen */
  {
    const char* fs = g_pc_settings.fullscreen == 0 ? "< Windowed >" :
                     g_pc_settings.fullscreen == 1 ? "< Fullscreen >" : "< Borderless >";
    len = sprintf(buf, "%s", fs);
  }
  {
    static u8 lbl[] = { 'D', 'i', 's', 'p', 'l', 'a', 'y' };
    mFont_SetLineStrings(game, lbl, sizeof(lbl), x, y,
      sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
      sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  mFont_SetLineStrings(game, (u8*)buf, len, 180.0f, y,
    sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
    sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  if (sel == item) mFont_SetLineStrings(game, str_arrow, 1, x - 12.0f, y, 255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  item++; y += line_h;

  /* VSync */
  len = sprintf(buf, "< %s >", g_pc_settings.vsync ? "On" : "Off");
  {
    static u8 lbl[] = { 'V', 'S', 'y', 'n', 'c' };
    mFont_SetLineStrings(game, lbl, sizeof(lbl), x, y,
      sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
      sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  mFont_SetLineStrings(game, (u8*)buf, len, 180.0f, y,
    sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
    sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  if (sel == item) mFont_SetLineStrings(game, str_arrow, 1, x - 12.0f, y, 255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  item++; y += line_h;

  /* MSAA */
  if (g_pc_settings.msaa > 0)
    len = sprintf(buf, "< %dx >", g_pc_settings.msaa);
  else
    len = sprintf(buf, "< Off >");
  {
    static u8 lbl[] = { 'M', 'S', 'A', 'A' };
    mFont_SetLineStrings(game, lbl, sizeof(lbl), x, y,
      sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
      sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  mFont_SetLineStrings(game, (u8*)buf, len, 180.0f, y,
    sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
    sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  if (sel == item) mFont_SetLineStrings(game, str_arrow, 1, x - 12.0f, y, 255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  item++; y += line_h;

  /* Textures */
  {
    const char* tp = g_pc_settings.preload_textures == 0 ? "< On Demand >" :
                     g_pc_settings.preload_textures == 1 ? "< Preload >" : "< Preload&Cache >";
    len = sprintf(buf, "%s", tp);
  }
  {
    static u8 lbl[] = { 'T', 'e', 'x', 't', 'u', 'r', 'e', 's' };
    mFont_SetLineStrings(game, lbl, sizeof(lbl), x, y,
      sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
      sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
  mFont_SetLineStrings(game, (u8*)buf, len, 180.0f, y,
    sel == item ? 255 : 180, sel == item ? 255 : 180, sel == item ? 255 : 180,
    sel == item ? 255 : 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  if (sel == item) mFont_SetLineStrings(game, str_arrow, 1, x - 12.0f, y, 255, 255, 255, 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  y += line_h * 1.5f;

  /* Hints */
  {
    static u8 str_save[] = { 'S', 'T', 'A', 'R', 'T', ':', ' ', 'S', 'a', 'v', 'e' };
    static u8 str_back[] = { 'B', ':', ' ', 'B', 'a', 'c', 'k' };
    mFont_SetLineStrings(game, str_save, sizeof(str_save), x, y, 255, 255, 255, 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
    mFont_SetLineStrings(game, str_back, sizeof(str_back), 190.0f, y, 255, 255, 255, 160, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }
}

static void aAL_pc_menu_draw(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
  GRAPH* graph = game->graph;
  int td = actor->titledemo_no;

  /* Reset modelview to identity — title_draw leaves it transformed */
  {
    Gfx* gfx;
    OPEN_DISP(graph);
    gfx = NOW_FONT_DISP;
    gSPMatrix(gfx++, &Mtx_clear, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    SET_FONT_DISP(gfx);
    CLOSE_DISP(graph);
  }

  static const u32 sel_r[5] = { 255, 255, 255, 120, 165 };
  static const u32 sel_g[5] = {  90, 135, 100, 205, 245 };
  static const u32 sel_b[5] = {  30,   0, 255, 245,   0 };
  static const u32 dim_r[5] = {  70,  60,  60,  40,  40 };
  static const u32 dim_g[5] = {  40,  50,  40,  50,  50 };
  static const u32 dim_b[5] = {  40,  30,  60,  70,  60 };

  static u8 str_start[] = { 'S', 't', 'a', 'r', 't', ' ', 'G', 'a', 'm', 'e' };
  static u8 str_options[] = { 'O', 'p', 't', 'i', 'o', 'n', 's' };
  static u8 str_arrow[] = { '>' };

  f32 start_w = (f32)mFont_GetStringWidth(str_start, sizeof(str_start), TRUE);
  f32 opt_w = (f32)mFont_GetStringWidth(str_options, sizeof(str_options), TRUE);
  f32 start_x = (SCREEN_WIDTH_F - start_w) * 0.5f;
  f32 opt_x = (SCREEN_WIDTH_F - opt_w) * 0.5f;
  f32 y0 = 135.0f;
  f32 y1 = 153.0f;
  int sel = actor->pc_menu_sel;

  /* "Start Game" */
  mFont_SetLineStrings(game, str_start, sizeof(str_start), start_x, y0,
    sel == 0 ? sel_r[td] : dim_r[td],
    sel == 0 ? sel_g[td] : dim_g[td],
    sel == 0 ? sel_b[td] : dim_b[td],
    sel == 0 ? 255 : 160,
    FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);

  /* "Options" */
  mFont_SetLineStrings(game, str_options, sizeof(str_options), opt_x, y1,
    sel == 1 ? sel_r[td] : dim_r[td],
    sel == 1 ? sel_g[td] : dim_g[td],
    sel == 1 ? sel_b[td] : dim_b[td],
    sel == 1 ? 255 : 160,
    FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);

  /* Cursor ">" */
  {
    f32 arrow_x = (sel == 0 ? start_x : opt_x) - 14.0f;
    f32 arrow_y = sel == 0 ? y0 : y1;
    mFont_SetLineStrings(game, str_arrow, 1, arrow_x, arrow_y,
      sel_r[td], sel_g[td], sel_b[td], 255,
      FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_FONT);
  }

  /* Options sub-menu overlay */
  if (actor->pc_options_open) {
    aAL_pc_options_draw(actor, game);
  }
}
#endif

static int aAL_draw_log_counter = 0;
static void aAL_actor_draw(ACTOR* actor, GAME* game) {
  ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;
  GRAPH* graph = game->graph;
  int pad_connected = padmgr_isConnectedController(PAD0);

#ifdef TARGET_PC
  { extern int g_pc_verbose; if (g_pc_verbose && (aAL_draw_log_counter % 60) == 0) {
    printf("[LOGO] draw: action=%d pad_connected=%d back_opacity=%d copyright_opacity=%d press_start_opacity=%.0f\n",
           logo_actor->action, pad_connected, logo_actor->back_opacity, logo_actor->copyright_opacity, logo_actor->press_start_opacity);
  }}
#else
  if ((aAL_draw_log_counter % 60) == 0) {
    printf("[LOGO] draw: action=%d pad_connected=%d back_opacity=%d copyright_opacity=%d press_start_opacity=%.0f\n",
           logo_actor->action, pad_connected, logo_actor->back_opacity, logo_actor->copyright_opacity, logo_actor->press_start_opacity);
  }
#endif
  aAL_draw_log_counter++;

  mFont_SetMatrix(graph, mFont_MODE_FONT);

  if (logo_actor->action >= aAL_ACTION_BACK_FADE_IN) {
    aAL_back_draw(graph, logo_actor);
  }

  aAL_title_draw(game, logo_actor);

  if (logo_actor->action >= aAL_ACTION_START_KEY_CHK_START) {
    aAL_copyright_draw(logo_actor, graph);
    aAL_tm_draw(graph);
  }

  mFont_SetMode(graph, mFont_MODE_FONT);
  if (pad_connected) {
    switch (logo_actor->action) {
      case aAL_ACTION_GAME_START:
      case aAL_ACTION_FADE_OUT_START:
      case aAL_ACTION_OUT:
#ifdef PC_ENHANCEMENTS
        aAL_pc_menu_draw(logo_actor, game);
#else
        aAL_press_start_draw(logo_actor, graph);
#endif
        break;
    }
  }

  mFont_UnSetMatrix(graph, mFont_MODE_FONT);
  game_debug_draw_last(game, graph);
  game_draw_last(graph);
}
