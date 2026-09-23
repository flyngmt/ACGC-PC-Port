#include "m_warning_ovl.h"

#include "audio.h"
#include "sys_matrix.h"
#include "m_font.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

typedef struct warning_ovl_line_s {
  f32 pos_x;
  f32 pos_y;
  u8* str;
  int str_len;
} mWR_line_c;

typedef struct warning_ovl_data_s {
  mWR_line_c* lines;
  int num_lines;
  f32 scale_x;
  f32 scale_y;
} mWR_data_c;

/**
 * Text displayed in the various warning messages.
 * This would have been done by using the CHAR_* definitions
 * located in m_font.h, but for readability, I chose to use
 * u8 arrays with defined lengths to remove the null terminator.
 */

static u8 wr_You_cant_hold[14] = "You can't hold";
static u8 wr_any_more_letters_Want_to[25] = "any more letters! Want to";
static u8 wr_throw_away_some_old_ones[25] = "throw away some old ones?";
static u8 wr_Yes[3] = "Yes";
static u8 wr_No[2] = "No";

static u8 wr_You_cant_pull_out_a_present[28] = "You can't pull out a present";
static u8 wr_when_your_item_screen_is_full[30] = "when your item screen is full!";

static u8 wr_You_cant_carry[15] = "You can't carry";
static u8 wr_more_than_99999_Bells[23] = "more than 99,999 Bells!";

static u8 wr_You_cant_mail[14] = "You can't mail";
static u8 wr_turnips_or_living_things[25] = "turnips or living things!";
static u8 wr_someone_elses_belongings[26] = "someone else's belongings!";
static u8 wr_a_wrapped_present[18] = "a wrapped present!";
static u8 wr_any_more_letters[17] = "any more letters,";
static u8 wr_so_you_cant_write_a_new_one[29] = "so you can't write a new one!";

static u8 wr_Your_item_screen_is_full[25] = "Your item screen is full,";
static u8 wr_so_you_cant_use_a_pattern[27] = "so you can't use a pattern!";
static u8 wr_an_exercise_card[17] = "an exercise card!";

static u8 wr_You_cant_put[13] = "You can't put";
static u8 wr_any_more_items_out[19] = "any more items out!";
static u8 wr_any_more_items_there[21] = "any more items there!";

static u8 wr_This_diary_is_locked[21] = "This diary is locked!";

static u8 wr_You_cant_pull_anything_out[27] = "You can't pull anything out";

static u8 wr_Theres_already_music_in_there[31] = "There's already music in there!";

static u8 wr_You_cant_drop[14] = "You can't drop";
static u8 wr_any_more_items_here[20] = "any more items here!";

static u8 wr_You_cant_plant[15] = "You can't plant";
static u8 wr_anything_else_here[19] = "anything else here!";

static u8 wr_You_cant_open_a_bag[20] = "You can't open a bag";
static u8 wr_unless_you_have_room[20] = "unless you have room";
static u8 wr_for_three_more_items[21] = "for three more items!";

static u8 wr_You_cant_plant_anything_here[30] = "You can't plant anything here!";

static u8 wr_You_cant_put_a_sign_up_here[29] = "You can't put a sign up here!";

static u8 wr_You_can_put_signs_up_only[25] = "You can put signs up only";
static u8 wr_in_your_own_village[20] = "in your own village!";

static u8 wr_You_cant_put_signs_on_the_island[34] = "You can't put signs on the island!";

static u8 wr_You_cant_leave[15] = "You can't leave";
static u8 wr_this_NES_on_the_island[23] = "this NES on the island!";

static u8 wr_You_dont_have_room[19] = "You don't have room";
static u8 wr_to_write_any_more[18] = "to write any more.";

static u8 wr_You_entered_letters[19] = "You entered letters";
static u8 wr_that_have_nothing_to_do[23] = "that have nothing to do";
static u8 wr_with_secret_codes[18] = "with secret codes!";

static u8 wr_this_item[10] = "this item!";

/* Line definitions */
#define mWR_LINE(str, pos_x, pos_y) { (pos_x), (pos_y), str, ARRAY_COUNT(str) }

static mWR_line_c wr_mailbox_line[] = {
  mWR_LINE(wr_You_cant_hold,             70.0f, 28.0f),
  mWR_LINE(wr_any_more_letters_Want_to,  40.0f, 24.0f),
  mWR_LINE(wr_throw_away_some_old_ones,  36.0f, 24.0f),
  mWR_LINE(wr_Yes,                       94.0f, 24.0f),
  mWR_LINE(wr_No,                       140.0f,  0.0f)
};

static mWR_line_c wr_pr_leave_line[] = {
  mWR_LINE(wr_You_cant_pull_out_a_present,    44.0f, 40.0f),
  mWR_LINE(wr_when_your_item_screen_is_full,  40.0f, 24.0f)
};

static mWR_line_c wr_money_line[] = {
  mWR_LINE(wr_You_cant_carry,         66.0f, 40.0f),
  mWR_LINE(wr_more_than_99999_Bells,  44.0f, 24.0f)
};

static mWR_line_c wr_pr_food_line[] = {
  mWR_LINE(wr_You_cant_mail,            70.0f, 40.0f),
  mWR_LINE(wr_turnips_or_living_things, 42.0f, 24.0f)
};

static mWR_line_c wr_pr_quest_line[] = {
  mWR_LINE(wr_You_cant_mail,            74.0f, 40.0f),
  mWR_LINE(wr_someone_elses_belongings, 38.0f, 24.0f)
};

static mWR_line_c wr_present_mail_line[] = {
  mWR_LINE(wr_You_cant_mail,     74.0f, 40.0f),
  mWR_LINE(wr_a_wrapped_present, 62.0f, 24.0f)
};

static mWR_line_c wr_write_line[] = {
  mWR_LINE(wr_You_cant_carry,              85.0f, 40.0f),
  mWR_LINE(wr_any_more_letters,            82.0f, 24.0f),
  mWR_LINE(wr_so_you_cant_write_a_new_one, 45.0f, 24.0f)
};

static mWR_line_c wr_original_line[] = {
  mWR_LINE(wr_Your_item_screen_is_full,  54.0f, 40.0f),
  mWR_LINE(wr_so_you_cant_use_a_pattern, 48.0f, 24.0f)
};

static mWR_line_c wr_pr_card_line[] = {
  mWR_LINE(wr_You_cant_mail,    60.0f, 40.0f),
  mWR_LINE(wr_an_exercise_card, 54.0f, 24.0f)
};

static mWR_line_c wr_put_max_furniture_line[] = {
  mWR_LINE(wr_You_cant_put,       68.0f, 40.0f),
  mWR_LINE(wr_any_more_items_out, 50.0f, 24.0f)
};

static mWR_line_c wr_put_furniture_line[] = {
  mWR_LINE(wr_You_cant_put,         68.0f, 40.0f),
  mWR_LINE(wr_any_more_items_there, 46.0f, 24.0f)
};

static mWR_line_c wr_lock_diary_line[] = {
  mWR_LINE(wr_This_diary_is_locked, 38.0f, 46.0f)
};

static mWR_line_c wr_music_line[] = {
  mWR_LINE(wr_You_cant_pull_anything_out,    47.0f, 40.0f),
  mWR_LINE(wr_when_your_item_screen_is_full, 41.0f, 24.0f)
};

static mWR_line_c wr_music2_line[] = {
  mWR_LINE(wr_Theres_already_music_in_there, 38.0f, 46.0f)
};

static mWR_line_c wr_hukubukuro_open_line[] = {
  mWR_LINE(wr_You_cant_open_a_bag,  48.0f, 37.0f),
  mWR_LINE(wr_unless_you_have_room, 50.0f, 24.0f),
  mWR_LINE(wr_for_three_more_items, 52.0f, 24.0f)
};

static mWR_line_c wr_put_plant_line[] = {
  mWR_LINE(wr_You_cant_plant_anything_here, 39.0f, 46.0f)
};

static mWR_line_c wr_put_sign_line[] = {
  mWR_LINE(wr_You_cant_put_a_sign_up_here, 40.0f, 46.0f)
};

static mWR_line_c wr_put_sign_other_line[] = {
  mWR_LINE(wr_You_can_put_signs_up_only, 44.0f, 40.0f),
  mWR_LINE(wr_in_your_own_village,       64.0f, 24.0f)
};

static mWR_line_c wr_put_sign_island_line[] = {
  mWR_LINE(wr_You_cant_put_signs_on_the_island, 31.0f, 46.0f)
};

static mWR_line_c wr_put_fami_line[] = {
  mWR_LINE(wr_You_cant_leave,         72.0f, 40.0f),
  mWR_LINE(wr_this_NES_on_the_island, 44.0f, 24.0f)
};

static mWR_line_c wr_word_over_line[] = {
  mWR_LINE(wr_You_dont_have_room, 54.0f, 40.0f),
  mWR_LINE(wr_to_write_any_more,  63.0f, 24.0f)
};

static mWR_line_c wr_put_item_line[] = {
  mWR_LINE(wr_You_cant_drop,       72.0f, 40.0f),
  mWR_LINE(wr_any_more_items_here, 54.0f, 24.0f)
};

static mWR_line_c wr_pw_chk_line[] = {
  mWR_LINE(wr_You_entered_letters,     59.0f, 40.0f),
  mWR_LINE(wr_that_have_nothing_to_do, 45.0f, 24.0f),
  mWR_LINE(wr_with_secret_codes,       63.0f, 24.0f)
};

static mWR_line_c wr_pr_fork_line[] = {
  mWR_LINE(wr_You_cant_mail, 60.0f, 40.0f),
  mWR_LINE(wr_this_item,     80.0f, 24.0f)
};

#define mWR_DATA(line, scale_x, scale_y) { line, ARRAY_COUNT(line), (scale_x), (scale_y) }
#define mWR_NULL { NULL, 0, 1.0f, 1.0f }

static mWR_data_c wr_win_data[] = {
  mWR_DATA(wr_mailbox_line, 1.0f, 1.2f),
  mWR_DATA(wr_pr_leave_line, 1.15f, 1.0f),
  mWR_DATA(wr_money_line, 1.0f, 1.0f),
  mWR_DATA(wr_pr_food_line, 1.0f, 1.0f),
  mWR_DATA(wr_pr_quest_line, 1.0f, 1.0f),
  mWR_NULL,
  mWR_NULL,
  mWR_NULL,
  mWR_NULL,
  mWR_DATA(wr_put_max_furniture_line, 0.95f, 1.0f),
  mWR_DATA(wr_put_furniture_line, 0.95f, 1.0f),
  mWR_DATA(wr_put_item_line, 1.0f, 1.0f),
  mWR_DATA(wr_put_plant_line, 1.15f, 0.9f),
  mWR_DATA(wr_hukubukuro_open_line, 1.0f, 1.15f),
  mWR_DATA(wr_present_mail_line, 1.0f, 1.0f),
  mWR_DATA(wr_write_line, 1.15f, 1.2f),
  mWR_DATA(wr_music_line, 1.15f, 1.0f),
  mWR_DATA(wr_music2_line, 1.15f, 0.9f),
  mWR_DATA(wr_original_line, 1.13f, 1.0f),
  mWR_DATA(wr_put_sign_line, 1.13f, 0.9f),
  mWR_DATA(wr_put_sign_other_line, 1.1f, 1.0f),
  mWR_DATA(wr_put_sign_island_line, 1.15f, 0.9f),
  mWR_DATA(wr_pr_card_line, 0.9f, 1.0f),
  mWR_DATA(wr_lock_diary_line, 0.9f, 0.9f),
  mWR_DATA(wr_put_fami_line, 1.0f, 1.0f),
  mWR_DATA(wr_word_over_line, 1.0f, 1.0f),
  mWR_DATA(wr_pw_chk_line, 1.0f, 1.2f),
  mWR_DATA(wr_pr_fork_line, 0.9f, 1.0f)
};

static void mWR_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  static f32 add[mWR_STATE_NUM] = { -0.2f, 0.2f };

  mWR_Ovl_c* ovl = submenu->overlay->warning_ovl;
  f32 new_scale = ovl->scale;

  new_scale += add[ovl->state];
  if (new_scale > 1.0f) {
    menu_info->proc_status = menu_info->next_proc_status;
    new_scale = 1.0f;
  }
  else if (new_scale < 0.0f) {
    menu_info->proc_status = menu_info->next_proc_status;
    new_scale = 0.0f;
  }

  ovl->scale = new_scale;
}

#ifdef MOUSE_INPUT
static u32 mWR_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu_info, u32 trigger) {
  mWR_Ovl_c* warning_ovl = submenu->overlay->warning_ovl;
  mWR_data_c* data = &wr_win_data[menu_info->data0];
  f32 scale = warning_ovl->scale;
  f32 mouse_x, mouse_y;
  f32 x, y;
  u32 pressed;
  int i;

  if (submenu->current_menu_type != mSM_OVL_WARNING ||
      !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.move_pR > 0.5f) ||
      !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
    return trigger;
  }

  pressed = pc_mouse_button_pressed();
  if (pressed & PC_MOUSE_BUTTON_RIGHT) {
    return trigger | BUTTON_B;
  }
  if (menu_info->data0 != mWR_WARNING_MAILBOX) {
    return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
  }

  x = 160.0f + menu_info->position[0] - data->scale_x * 120.0f * scale;
  y = 120.0f - menu_info->position[1] - data->scale_y * 60.0f * scale;
  for (i = 0; i < data->num_lines; i++) {
    mWR_line_c* line = &data->lines[i];

    y += line->pos_y * scale;
    if (i >= 3) {
      f32 line_x = x + line->pos_x * scale;
      f32 width = mFont_GetStringWidth(line->str, line->str_len, TRUE) * scale;

      if (mouse_x >= line_x - 2.0f && mouse_x < line_x + width + 2.0f &&
          mouse_y >= y && mouse_y < y + 16.0f * scale) {
        if (warning_ovl->selected != i - 3) {
          warning_ovl->selected = i - 3;
          sAdo_SysTrgStart(NA_SE_CURSOL);
        }
        return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
      }
    }
  }

  return trigger;
}
#endif

static void mWR_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  u32 trigger = submenu->overlay->menu_control.trigger;
  mWR_Ovl_c* warning_ovl = submenu->overlay->warning_ovl;

#ifdef MOUSE_INPUT
  trigger = mWR_mouse_trigger(submenu, menu_info, trigger);
#endif

  if ((trigger & (BUTTON_A | BUTTON_B | BUTTON_START)) != 0) {
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_END;
    warning_ovl->state = mWR_STATE_OUT;

    if ((trigger & BUTTON_B) != 0) {
      warning_ovl->selected = 1;
    }
    else if (warning_ovl->selected == 0) {
      sAdo_SysTrgStart(0x435);
    }

    if (menu_info->data0 == 0) {
      menu_info->data1 = warning_ovl->selected;
    }
  }
  else if (menu_info->data0 == 0) {
    if ((trigger & BUTTON_CLEFT) != 0) {
      if (warning_ovl->selected == 1) {
        warning_ovl->selected = 0;
        sAdo_SysTrgStart(NA_SE_CURSOL);
      }
    }
    else if ((trigger & BUTTON_CRIGHT) != 0) {
      if (warning_ovl->selected == 0) {
        warning_ovl->selected = 1;
        sAdo_SysTrgStart(NA_SE_CURSOL);
      }
    }
  }
}

static void mWR_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mWR_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mWR_warning_ovl_move(Submenu* submenu) {
  static mWR_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mWR_move_Move,
    &mWR_move_Play,
    (mWR_MOVE_PROC)&none_proc1,
    (mWR_MOVE_PROC)&none_proc1,
    &mWR_move_End
  };

  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_WARNING];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

  switch (menu_info->proc_status) {
    case mSM_OVL_PROC_PLAY:
      submenu->overlay->menu_control.animation_flag = TRUE;
      break;

    case mSM_OVL_PROC_MOVE:
      submenu->overlay->menu_control.animation_flag = FALSE;
      break;
  }
}

extern Gfx att_win_model[];
extern Gfx att_win_cursor_model[];

static void mWR_set_frame_dl(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, mWR_data_c* data) {
  Gfx* gfx;
  f32 scale = submenu->overlay->warning_ovl->scale * 16.0f;

  Matrix_scale(scale * data->scale_x, scale * data->scale_y, 1.0f, MTX_LOAD);
  Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Draw background */
  gDPPipeSync(gfx++);
  gDPSetBlendColor(gfx++, 255, 255, 255, 40);
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPDisplayList(gfx++, att_win_model);
  gDPPipeSync(gfx++);
  gDPSetAlphaCompare(gfx++, G_AC_NONE);
  gDPSetBlendColor(gfx++, 255, 255, 255, 8);

  /* Draw cursor */
  if (menu_info->data0 == 0) {
    f32 x;
    f32 y;

    x = (menu_info->position[0] - 120.0f * data->scale_x) - 8.0f;
    if (submenu->overlay->warning_ovl->selected == 0) {
      x += data->lines[3].pos_x;
    }
    else {
      x += data->lines[4].pos_x;
    }

    y = (menu_info->position[1] + 60.0f * data->scale_y) - (data->lines[0].pos_y + data->lines[1].pos_y + data->lines[2].pos_y + data->lines[3].pos_y + 8.0f);

    Matrix_scale(scale, scale, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 0.0f, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, att_win_cursor_model);
  }

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mWR_set_strings(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, mWR_data_c* data) {
  static int col_type0[3] = { 255, 255,   0 }; // base color
  static int col_type1[3] = { 255, 175, 175 }; // selected choice color
  static int col_type2[3] = { 255, 255, 255 }; // unselected choice color

  mWR_Ovl_c* warning_ovl = submenu->overlay->warning_ovl;
  int selected_idx = 3 + warning_ovl->selected;
  f32 scale = warning_ovl->scale;
  f32 x;
  f32 y;
  f32 line_x;
  int i;
  mWR_line_c* line;
  int* color;
  
  (*submenu->overlay->set_char_matrix_proc)(game->graph);

  line = data->lines;
  x = (160.0f + menu_info->position[0]) - (data->scale_x * 120.0f) * scale;
  y = (120.0f - menu_info->position[1]) - (data->scale_y * 60.0f) * scale;

  for (i = 0; i < data->num_lines; i++) {
    if (i == selected_idx) {
      color = col_type1;
    }
    else if (i >= 3 && menu_info->data0 == 0) {
      color = col_type2;
    }
    else {
      color = col_type0;
    }

    line_x = line->pos_x * scale;
    y += line->pos_y * scale;

    mFont_SetLineStrings(
      game,
      line->str,
      line->str_len,
      x + line_x,
      y,
      color[0],
      color[1],
      color[2],
      255,
      FALSE,
      TRUE,
      scale,
      scale,
      mFont_MODE_POLY
    );

    line++;
  }
}

static void mWR_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  int str_no = menu_info->data0;

  mWR_set_frame_dl(submenu, game->graph, menu_info, &wr_win_data[str_no]);
  mWR_set_strings(submenu, game, menu_info, &wr_win_data[str_no]);
}

static void mWR_warning_ovl_draw(Submenu* submenu, GAME* game) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_WARNING];

  (*menu_info->pre_draw_func)(submenu, game);
  mWR_set_dl(submenu, game, menu_info);
}

extern void mWR_warning_ovl_set_proc(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->menu_control.menu_move_func = &mWR_warning_ovl_move;
  overlay->menu_control.menu_draw_func = &mWR_warning_ovl_draw;
}

extern void mWR_warning_ovl_init(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mWR_Ovl_c* warning_ovl = overlay->warning_ovl;

  overlay->menu_control.animation_flag = FALSE;
  overlay->menu_info[mSM_OVL_WARNING].proc_status = mSM_OVL_PROC_MOVE;
  overlay->menu_info[mSM_OVL_WARNING].next_proc_status = mSM_OVL_PROC_PLAY;
  warning_ovl->selected = 1;
  warning_ovl->scale = 0.0f;
  warning_ovl->state = mWR_STATE_IN;
}

static mWR_Ovl_c wr_ovl_data;

extern void mWR_warning_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->warning_ovl == NULL) {
    mem_clear((u8*)&wr_ovl_data, sizeof(mWR_Ovl_c), 0);
    overlay->warning_ovl = &wr_ovl_data;
  }

  mWR_warning_ovl_init(submenu);
  mWR_warning_ovl_set_proc(submenu);
}

extern void mWR_warning_ovl_destruct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->warning_ovl = NULL;
}
