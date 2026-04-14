#ifndef AC_ANIMAL_LOGO_H
#define AC_ANIMAL_LOGO_H

#include "types.h"
#include "game.h"
#include "m_actor.h"
#include "m_lib.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aAL_DATA_INIT_PROC)(GAME_PLAY*);

typedef struct animal_logo_clip_s {
  aAL_DATA_INIT_PROC data_init_proc;
} aAL_Clip_c;

#define aAL_BACK_FADEIN_RATE 20
#define aAL_BACK_FADEIN_MAX 220

#define aAL_TIMER 60
#define aAL_FADEOUT_TIMER 26

#define aAL_COPYRIGHT_ALPHA_RATE 63

typedef struct actor_animal_logo_s ANIMAL_LOGO_ACTOR;

typedef void (*ANIMAL_LOGO_ACTION_PROC)(ANIMAL_LOGO_ACTOR*, GAME*);

typedef struct logo_skeleton_info_s {
  cKF_SkeletonInfo_R_c skeleton;
  s_xyz* work_area_p;
  s_xyz* morph_area_p;
} aAL_SkeletonInfo_c;

struct actor_animal_logo_s {
  ACTOR actor_class;
  
  int action;
  ANIMAL_LOGO_ACTION_PROC action_proc;
  
  aAL_SkeletonInfo_c animal;
  aAL_SkeletonInfo_c cros;
  aAL_SkeletonInfo_c sing;

  s_xyz animal_work_area[22];
  s_xyz animal_morph_area[22];

  s_xyz cros_work_area[15];
  s_xyz cros_morph_area[15];

  s_xyz sing_work_area[15];
  s_xyz sing_morph_area[15];

  float back_opacity;
  float copyright_opacity;
  float press_start_opacity;
  float start_opacity_timer;
  float title_timer;
  int titledemo_no;

#ifdef PC_ENHANCEMENTS
  int pc_menu_sel;         /* 0=Start Game, 1=Options */
  int pc_options_open;     /* options sub-menu visible */
  int pc_options_sel;      /* highlighted option (unused for now) */
  float pc_cursor_cooldown;  /* stick debounce timer */
  int pc_unused[2];
#else
  int unused_56C[6];
#endif
};

enum {
  aAL_ACTION_IN,
  aAL_ACTION_BACK_FADE_IN,
  aAL_ACTION_START_KEY_CHK_START,
  aAL_ACTION_GAME_START,
  aAL_ACTION_FADE_OUT_START,
  aAL_ACTION_OUT,
  aAL_ACTION_6,

  aAL_ACTION_NUM
};

extern ACTOR_PROFILE Animal_Logo_Profile;

// TODO: these are private but due to the way our build system works,
// we must expose them to get them in a separate TU.
extern void flash_rom_and_player_info_clear();
extern int decide_next_scene_no();
extern void title_action_data_init_start_select(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
