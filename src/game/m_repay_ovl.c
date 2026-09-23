#include "m_repay_ovl.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

static mRP_Ovl_c rp_ovl_data;
static mActor_name_t mRP_money_name[MONEY_NUM] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };
static u32 mRP_money_amount[MONEY_NUM] = { 100, 1000, 10000, 30000 };
static u8 mRP_ok_str[2] = "OK";

static int mRP_money_repay(mRP_Ovl_c* repay_ovl) {
  mActor_name_t* item_p;
  mActor_name_t* money_name_p = mRP_money_name;
  u32* money_amount_p = mRP_money_amount;
  u32 total_money = Common_Get(now_private)->inventory.wallet;
  int j;
  int i;
  u32 money_left = 0;

  if (total_money >= repay_ovl->repay_amount) {
    money_left = total_money - repay_ovl->repay_amount;
  }
  else {
    for (i = 0; i < MONEY_NUM; i++) {
      item_p = Common_Get(now_private)->inventory.pockets;
      for (j = 0; j < mPr_POCKETS_SLOT_COUNT; j++) {
        if (
          mPr_GET_ITEM_COND(Common_Get(now_private)->inventory.item_conditions, j) == mPr_ITEM_COND_NORMAL &&
          *item_p == *money_name_p
        ) {
          total_money += *money_amount_p;
          mPr_SetPossessionItem(Common_Get(now_private), j, EMPTY_NO, mPr_ITEM_COND_NORMAL);

          if (total_money >= repay_ovl->repay_amount) {
            return total_money - repay_ovl->repay_amount;
          }
        }

        item_p++;
      }

      money_name_p++;
      money_amount_p++;
    }
  }

  return money_left;
}

static void mRP_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

#ifdef MOUSE_INPUT
static u32 mRP_mouse_trigger(Submenu* submenu, mSM_MenuInfo_c* menu_info, u32 trigger) {
  mRP_Ovl_c* repay_ovl = submenu->overlay->repay_ovl;
  f32 mouse_x, mouse_y;
  u32 pressed;
  s32 wheel;
  int selected = -1;

  if (submenu->current_menu_type != mSM_OVL_REPAY ||
      !pc_mouse_update_owner(FALSE, trigger || getButton() || gamePT->mcon.move_pR > 0.5f) ||
      !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
    return trigger;
  }

  pressed = pc_mouse_button_pressed();
  if (pressed & PC_MOUSE_BUTTON_RIGHT) {
    return trigger | BUTTON_B;
  }

  mouse_x -= menu_info->position[0];
  mouse_y += menu_info->position[1];
  if (mouse_y >= 112.0f && mouse_y < 128.0f) {
    u8 amount_str[7];
    f32 x;
    int i;

    mFont_UnintToString(amount_str, sizeof(amount_str), repay_ovl->repay_amount, 6, FALSE, TRUE, TRUE);
    x = 206.0f - mFont_GetStringWidth(amount_str, sizeof(amount_str), TRUE);
    for (i = 0; i < sizeof(amount_str); i++) {
      int width = mFont_GetCodeWidth(amount_str[i], TRUE);

      if (i != mRP_CURSOR_100 && mouse_x >= x && mouse_x < x + width) {
        selected = i < mRP_CURSOR_100 ? i : i - 1;
        break;
      }
      x += width;
    }
  } else if (mouse_y >= 128.0f && mouse_y < 144.0f && mouse_x >= 205.0f &&
             mouse_x < 209.0f + mFont_GetStringWidth(mRP_ok_str, sizeof(mRP_ok_str), TRUE) * 0.875f) {
    selected = mRP_CURSOR_OK;
  }

  if (selected < 0) {
    return trigger;
  }
  if (repay_ovl->cursor_idx != selected) {
    repay_ovl->cursor_idx = selected;
    sAdo_SysTrgStart(NA_SE_CURSOL);
  }

  if (selected == mRP_CURSOR_OK) {
    return trigger | ((pressed & PC_MOUSE_BUTTON_LEFT) ? BUTTON_A : 0);
  }
  wheel = pc_mouse_scroll_wheel();
  if (wheel > 0 || (pressed & PC_MOUSE_BUTTON_LEFT)) {
    trigger |= BUTTON_CUP;
  } else if (wheel < 0) {
    trigger |= BUTTON_CDOWN;
  }
  return trigger;
}
#endif

static void mRP_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  static u32 step_money[mRP_CURSOR_NUM] = {
    100000,
     10000,
      1000,
       100,
        10,
         1,
         0
  };

  mRP_Ovl_c* repay_ovl = submenu->overlay->repay_ovl;
  u32 trigger = submenu->overlay->menu_control.trigger;

#ifdef MOUSE_INPUT
  trigger = mRP_mouse_trigger(submenu, menu_info, trigger);
#endif

  if ((trigger & BUTTON_B)) {
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
    sAdo_SysTrgStart(NA_SE_MENU_EXIT);
  }
  else if (repay_ovl->cursor_idx >= mRP_CURSOR_OK || (trigger & BUTTON_START)) {
    if ((trigger & BUTTON_A) || (trigger & BUTTON_START)) {
      if (repay_ovl->repay_amount != 0) {
        mPlib_request_main_give_from_submenu(ITM_MONEY_10000, mSM_OVL_REPAY, FALSE, TRUE);
        Common_Get(now_private)->inventory.loan = repay_ovl->loan;
        Common_Get(now_private)->inventory.wallet = mRP_money_repay(repay_ovl);
      }

      (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
      sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    }
    else if ((trigger & (BUTTON_CUP | BUTTON_CLEFT))) {
      repay_ovl->cursor_idx--;
      sAdo_SysTrgStart(NA_SE_CURSOL);
    }
  }
  else if (repay_ovl->cursor_idx != 0 && (trigger & BUTTON_CLEFT)) {
    repay_ovl->cursor_idx--;
    sAdo_SysTrgStart(NA_SE_CURSOL);
  }
  else if ((trigger & BUTTON_CRIGHT)) {
    repay_ovl->cursor_idx++;
    sAdo_SysTrgStart(NA_SE_CURSOL);
  }
  else if ((trigger & (BUTTON_CDOWN | BUTTON_CUP))) {
    u32 repay_amount = repay_ovl->repay_amount;

    if ((trigger & BUTTON_CDOWN)) {
      if (repay_amount < step_money[repay_ovl->cursor_idx]) {
        if (repay_amount == 0) {
          sAdo_SysTrgStart(0x1003);
          return;
        }
        
        repay_amount = 0;
      }
      else {
        repay_amount -= step_money[repay_ovl->cursor_idx];
      }
    }
    else {
      if (repay_amount == repay_ovl->max_repay) {
        sAdo_SysTrgStart(0x1003);
        return;
      }

      repay_amount += step_money[repay_ovl->cursor_idx];
      if (repay_amount > repay_ovl->max_repay) {
        repay_amount = repay_ovl->max_repay;
      }
    }

    sAdo_SysTrgStart(0x426);
    repay_ovl->money = repay_ovl->max_money - repay_amount;
    repay_ovl->loan = Common_Get(now_private)->inventory.loan - repay_amount;
    repay_ovl->repay_amount = repay_amount;
  }
}

static void mRP_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mRP_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mRP_repay_ovl_move(Submenu* submenu) {
  static mRP_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mRP_move_Move,
    &mRP_move_Play,
    (mRP_MOVE_PROC)none_proc1,
    (mRP_MOVE_PROC)none_proc1,
    &mRP_move_End
  };

  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_REPAY];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx fkm_win_mode[];
extern Gfx fkm_win_model[];

static void mRP_set_frame_dl(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 x, f32 y) {
  f32 tex_x;
  f32 tex_y;
  int s;
  int t;
  Gfx* gfx;

  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
  Matrix_translate(x, y, 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Setup RDP */
  gSPDisplayList(gfx++, fkm_win_mode);

   /* Setup matrix */
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  /* Set background texture scroll position */
  tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
  tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
  s = (int)tex_x & 0xFF;
  t = (int)tex_y & 0xFF;
  gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, s, t, 32, 32);

  /* Draw background frame */
  gSPDisplayList(gfx++, fkm_win_model);

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mRP_set_num_str(GAME* game, u32 num, rgba_t* str_col_p, f32 x, f32 y, f32 scale) {
  u8 str[7];

  mFont_UnintToString(str, sizeof(str), num, 6, FALSE, FALSE, TRUE);
  x -= scale * mFont_GetStringWidth(str, sizeof(str), TRUE);
  mFont_SetLineStrings(
    game,
    str, sizeof(str),
    x, y,
    str_col_p->r, str_col_p->g, str_col_p->b, 255,
    FALSE,
    TRUE,
    scale, scale,
    mFont_MODE_POLY
  );
}

static void mRP_set_character_dl(Submenu* submenu, GAME* game, f32 x, f32 y) {
  static u8 kingaku_str[9] = "Your Loan";
  static rgba_t money_col  = { 100,  40, 255, 255 };
  static rgba_t repay_col  = {  70, 120, 245, 255 };
  static rgba_t select_col = { 215,   0,   0, 255 };
  static rgba_t kettei_col = {  70, 120, 245, 255 };
  static rgba_t loan_col   = {  40, 185, 110, 255 };

  mRP_Ovl_c* repay_ovl = submenu->overlay->repay_ovl;
  rgba_t* color_p;
  u8 repay_amount_str[7];
  int sel;
  f32 char_y;
  f32 char_x;
  int i;

  (*submenu->overlay->set_char_matrix_proc)(game->graph);
  mFont_SetLineStrings(
    game,
    kingaku_str, sizeof(kingaku_str),
    x + 153.0f, -y + 64.0f,
    255, 255, 255, 255,
    FALSE,
    TRUE,
    0.875f, 0.875f,
    mFont_MODE_POLY
  );

  mRP_set_num_str(game, repay_ovl->money, &money_col, x + 206.0f, -y + 91.0f, 0.875f);
  sel = repay_ovl->cursor_idx;
  if (sel >= mRP_CURSOR_100) {
    sel++; // move past the comma
  }

  mFont_UnintToString(repay_amount_str, sizeof(repay_amount_str), repay_ovl->repay_amount, 6, FALSE, TRUE, TRUE);
  
  /* Draw each individual character in the repayment amount string */
  char_x =  x - mFont_GetStringWidth(repay_amount_str, 7, TRUE) + 206.0f;
  char_y = -y + 112.0f;
  for (i = 0; i < 7; i++) {
    if (sel == i) {
      color_p = &select_col;
    }
    else {
      color_p = &repay_col;
    }

    mFont_SetLineStrings(
      game,
      &repay_amount_str[i], 1,
      char_x, char_y,
      color_p->r, color_p->g, color_p->b, 255,
      FALSE,
      TRUE,
      1.0f, 1.0f,
      mFont_MODE_POLY
    );

    char_x += mFont_GetStringWidth(&repay_amount_str[i], 1, TRUE);
  }

  if (repay_ovl->cursor_idx < mRP_CURSOR_OK) {
    color_p = &kettei_col;
  }
  else {
    color_p = &select_col;
  }

  mFont_SetLineStrings(
    game,
    mRP_ok_str, sizeof(mRP_ok_str),
    x + 207.0f, -y + 128.0f,
    color_p->r, color_p->g, color_p->b, 255,
    FALSE,
    TRUE,
    0.875f, 0.875f,
    mFont_MODE_POLY
  );

  mRP_set_num_str(game, repay_ovl->loan, &loan_col, x + 209.0f, -y + 155.0f, 0.875f);
}

static void mRP_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  GRAPH* graph = game->graph;
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];

  mRP_set_frame_dl(submenu, graph, menu_info, x, y);
  mRP_set_character_dl(submenu, game, x, y);
}

static void mRP_repay_ovl_draw(Submenu* submenu, GAME* game) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_REPAY];

  (*menu_info->pre_draw_func)(submenu, game);
  mRP_set_dl(submenu, game, menu_info);
}

extern void mRP_repay_ovl_set_proc(Submenu* submenu) {
  mSM_Control_c* control = &submenu->overlay->menu_control;

  control->menu_move_func = &mRP_repay_ovl_move;
  control->menu_draw_func = &mRP_repay_ovl_draw;
}

static void mRP_repay_ovl_init(Submenu* submenu) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_REPAY];
  mRP_Ovl_c* repay_ovl = submenu->overlay->repay_ovl;
  mActor_name_t* item_p = Common_Get(now_private)->inventory.pockets;
  int i;
  u32 max_repay;

  submenu->overlay->menu_control.animation_flag = FALSE;
  menu_info->proc_status = mSM_OVL_PROC_MOVE;
  menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
  menu_info->move_drt = mSM_MOVE_IN_TOP;

  repay_ovl->money = Common_Get(now_private)->inventory.wallet;

  for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item_p++) {
    if (mPr_GET_ITEM_COND(Common_Get(now_private)->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL) {
      int j;

      for (j = 0; j < MONEY_NUM; j++) {
        if (*item_p == mRP_money_name[j]) {
          repay_ovl->money += mRP_money_amount[j];
          break;
        }
      }
    }
  }

  repay_ovl->max_money = repay_ovl->money;
  repay_ovl->loan = Common_Get(now_private)->inventory.loan;
  repay_ovl->repay_amount = 0;

  if (repay_ovl->max_money > Common_Get(now_private)->inventory.loan) {
    max_repay = Common_Get(now_private)->inventory.loan;
  }
  else {
    max_repay = repay_ovl->max_money;
  }

  repay_ovl->max_repay = max_repay;
  repay_ovl->cursor_idx = mRP_CURSOR_100000;
}

extern void mRP_repay_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->repay_ovl == NULL) {
    mem_clear((u8*)&rp_ovl_data, sizeof(mRP_Ovl_c), 0);
    overlay->repay_ovl = &rp_ovl_data;
  }

  mRP_repay_ovl_init(submenu);
  mRP_repay_ovl_set_proc(submenu);
}

extern void mRP_repay_ovl_destruct(Submenu* submenu) {
  submenu->overlay->repay_ovl = NULL;
}
