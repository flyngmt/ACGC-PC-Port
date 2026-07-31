#include "m_watch_my_step.h"

#include "libultra/libultra.h"
#include "m_play.h"
#include "m_actor_type.h"
#include "m_item_name.h"
#include "m_name_table.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_font.h"
#include "m_mail.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_room_type.h"
#include "m_msg.h"
#include "audio.h"
#include "m_scene_table.h"
#include "m_private.h"

typedef struct watch_my_step_s {
    f32 pos_x;
    f32 pos_y;

    f32 opacity;

    f32 trans_x;
    f32 trans_y;

    f32 scale;

    f32 timer;

    mActor_name_t item_no;

    u8 mode;
    u8 item_name[mIN_ITEM_NAME_LEN];
    u8 draw_type;
} mWt_watch_my_step_c;

static mWt_watch_my_step_c S_watch_my_step;

typedef struct navigate_s {
    f32 opacity;
    f32 timer;
    u8 mode;
    u8 draw_type;
} mWt_navigate_c;

static mWt_navigate_c S_navigate;

typedef struct mybell_confirmation_s {
    f32 opacity;
    u32 all_money;
    f32 coin_sfx_timer;
    u8 mode;
    u8 draw_type;
    u8 update_money;
    u8 play_finish_sfx;
} mWt_mybell_confirmation_c;

static mWt_mybell_confirmation_c S_mybell_conf;

extern void watch_my_step_ct() {
    bzero(&S_watch_my_step, sizeof(mWt_watch_my_step_c));
    S_watch_my_step.item_no = EMPTY_NO;
    navigate_camera_ct();
    mWt_mybell_confirmation_ct();
}

extern void watch_my_step_move(GAME_PLAY* play) {
    mActor_name_t window_item;
    PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);
    int can_show =
        play->camera.now_main_index == CAMERA2_PROCESS_NORMAL && play->camera.main_data.normal.morph_counter > 20;

    navigate_camera_move(play);
    mWt_mybell_confirmation_move(play);

    S_watch_my_step.draw_type = 0;

    if (mEv_IsNotTitleDemo()) {
        window_item = mPlib_Get_itemNo_forWindow();

        switch (S_watch_my_step.mode) {
            case 0: {
                if (window_item != EMPTY_NO && !can_show) {
                    S_watch_my_step.opacity = 0.0f;
                    S_watch_my_step.timer = 2.0f;
                    S_watch_my_step.mode++;
                }
                break;
            }

            case 1:
            case 2: {
                S_watch_my_step.timer -= (f32)play->game.graph->dt_num_60fps_frames;
                if (S_watch_my_step.timer <= 0.0f) {
                    S_watch_my_step.timer = 2.0f;
                    S_watch_my_step.mode++;
                }
                break;
            }

            case 3: {
                add_calc(&S_watch_my_step.opacity, 1.0f, 1.0f - sqrtf(0.5), 0.25f, 0.15f);
                if (window_item == EMPTY_NO || can_show == TRUE) {
                    S_watch_my_step.mode++;
                }
                break;
            }

            case 4: {
                add_calc(&S_watch_my_step.opacity, 0.0f, 1.0f - sqrtf(0.5), 0.1f, 0.05f);
                add_calc(&S_watch_my_step.opacity, 0.0f, 1.0f - sqrtf(0.5), 0.005f, 0.005f);

                if (S_watch_my_step.opacity < 0.01f) {
                    S_watch_my_step.mode = 0;
                }
                break;
            }

            default: {
                S_watch_my_step.mode = 0;
                break;
            }
        }

        if (S_watch_my_step.mode != 0) {
            xyz_t position = player_actor->actor_class.world.position;
            xyz_t screen_pos;
            position.y += 30.0f;

            /* convert player position plus 75% of a unit up to screen position */
            Game_play_Projection_Trans(play, &position, &screen_pos);

            if (S_watch_my_step.mode < 4) {
                S_watch_my_step.trans_x = 1.0f;

                if (screen_pos.x > 200.0f) {
                    S_watch_my_step.trans_x = -1.0f;
                } else if (screen_pos.x > 120.0f && player_actor->actor_class.shape_info.rotation.y >= 0) {
                    S_watch_my_step.trans_x = -1.0f;
                }

                S_watch_my_step.trans_y = 1.0f;
                if (screen_pos.y < 68.0f) {
                    S_watch_my_step.trans_y = -1.0f;
                }

                S_watch_my_step.pos_x = screen_pos.x - (S_watch_my_step.trans_x * -40.0f + 160.0f);
                S_watch_my_step.pos_y = screen_pos.y - (S_watch_my_step.trans_y * 42.0f + 120.0f);
            }

            if (window_item != EMPTY_NO) {
                f32 size;
                int len;

                if (S_watch_my_step.item_no != window_item || S_watch_my_step.item_no == EMPTY_NO) {
                    S_watch_my_step.item_no = window_item;
                    mIN_copy_name_str(S_watch_my_step.item_name, (mActor_name_t)window_item);
                }

                len = mMl_strlen(S_watch_my_step.item_name, mIN_ITEM_NAME_LEN, CHAR_SPACE);
                size = (f32)(mFont_GetStringWidth(S_watch_my_step.item_name, len, TRUE)) * 0.875f - 17.5f;

                if (size < 0.0f) {
                    size = 0.0f;
                }

                S_watch_my_step.scale = size / 122.5f;
            } else {
                S_watch_my_step.item_no = EMPTY_NO;
            }

            if (S_watch_my_step.mode != 0) {
                if ((mFI_GET_TYPE(mFI_GetFieldId()) == mFI_TYPE(mFI_FIELDTYPE_FG) &&
                     mEv_CheckFirstIntro() != TRUE) || // all items when correct mode outside but not during nook intro
                    (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM &&
                     !ITEM_IS_FTR(window_item)) // Non-furniture items when in player house
                ) {
                    S_watch_my_step.draw_type = 1;
                }
            }
        }
    }
}

extern void watch_my_step_draw(GAME_PLAY* play) {
    GAME* game = (GAME*)play;
    GRAPH* g = play->game.graph;
    N64Mtx* font_mtx;

    OPEN_DISP(g);

    font_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    navigate_camera_draw(play);
    mWt_mybell_confirmation_draw(play);

    if (S_watch_my_step.draw_type == 0) {
        return;
    }

    /* load new world-view projection matrix for font */
    if (font_mtx != NULL) {
        mFont_CulcOrthoMatrix(font_mtx);
        gSPMatrix(NOW_FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }

    Matrix_scale(16.0f, 16.0f, 16.0f, MTX_LOAD);
    Matrix_translate(S_watch_my_step.pos_x, -S_watch_my_step.pos_y, 0.0f, MTX_MULT);

    {
        Gfx* font_gfx = NOW_FONT_DISP;
        gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(font_gfx++, fki_win_mode);
        gDPSetRenderMode(font_gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);

        switch (S_watch_my_step.mode) {
            case 3: {
                Matrix_push();
                Matrix_scale(S_watch_my_step.opacity * (S_watch_my_step.scale * 0.75f + 0.25f),
                             S_watch_my_step.opacity * (S_watch_my_step.scale * 0.23333335f + 0.76666665f),
                             S_watch_my_step.opacity, MTX_MULT);

                gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_pull();
                gSPDisplayList(font_gfx++, fki_win_w3T_model);
            }
            /* fallthrough 3 -> 2 */
            case 2: {
                Matrix_push();
                Matrix_translate(S_watch_my_step.trans_x * -1.0f, S_watch_my_step.trans_y * -20.0f, 0.0f, MTX_MULT);

                gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_pull();
                gSPDisplayList(font_gfx++, fki_win_w2T_model);
            }
            /* fallthrough 2 -> 1 */
            case 1: {
                Matrix_push();
                Matrix_translate(S_watch_my_step.trans_x * -13.0f, S_watch_my_step.trans_y * -30.0f, 0.0f, MTX_MULT);

                gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_pull();
                gSPDisplayList(font_gfx++, fki_win_w1T_model);
                break;
            }

            case 4: {
                u8 a = S_watch_my_step.opacity * 255.0f;
                gDPSetPrimColor(font_gfx++, 0, a, 255, 255, 215, a);

                Matrix_push();
                Matrix_scale(S_watch_my_step.scale * 0.75f + 0.25f, S_watch_my_step.scale * 0.23333335f + 0.76666665f,
                             1.0f, MTX_MULT);

                gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_pull();
                gSPDisplayList(font_gfx++, fki_win_w4_model);
                break;
            }
        }

        /* Reset font matrix scale */
        Matrix_scale(1.0f, 1.0f, 1.0f, MTX_LOAD);
        gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        SET_FONT_DISP(font_gfx);
    }

    CLOSE_DISP(g);

    if (S_watch_my_step.mode >= 3) {
        f32 text_opacity = (S_watch_my_step.opacity - 0.5f) * 2.0f;

        if (text_opacity > 0.0f) {
            mFont_SetLineStrings(
                game, S_watch_my_step.item_name, mIN_ITEM_NAME_LEN,
                (10.0f + ((S_watch_my_step.pos_x + 160.0f) - (0.5f * (40.0f + (S_watch_my_step.scale * 120.0f))))) +
                    (1.0f - S_watch_my_step.scale),
                120.0f + ((3.0f * S_watch_my_step.scale) +
                          (5.0f + (S_watch_my_step.pos_y - (0.5f * (23.0f + (S_watch_my_step.scale * 7.0f)))))),
                45, 45, 35, (int)(255.0f * text_opacity), FALSE, TRUE, 0.875f, 0.875f, mFont_MODE_FONT);
        }
    }
}

static void navigate_camera_ct() {
    bzero(&S_navigate, sizeof(mWt_navigate_c));
}

static void navigate_camera_move(GAME_PLAY* play) {
    S_navigate.draw_type = 0;

    switch (S_navigate.mode) {
        case 0: {
            if (mPlib_check_able_change_camera_normal_index() != 0 && play->fb_fade_type == FADE_TYPE_NONE) {
                S_navigate.timer = 150.0f;
                S_navigate.mode++;
            }
            break;
        }

        case 1: {
            add_calc(&S_navigate.opacity, 1.0f, 1.0f - sqrtf(0.8), 0.075f, 0.005f);
            S_navigate.timer -= (f32)play->game.graph->dt_num_60fps_frames;

            if (S_navigate.timer <= 0.0f || play->submenu.process_status != mSM_PROCESS_WAIT ||
                mMsg_Check_MainHide(mMsg_Get_base_window_p()) == FALSE) {
                S_navigate.mode++;
            }

            if (mRmTp_PleaseDrawLightSwitch()) {
                S_navigate.draw_type = 2;
            } else {
                S_navigate.draw_type = 1;
            }
            break;
        }

        case 2: {
            add_calc(&S_navigate.opacity, 0.0f, 1.0f - sqrtf(0.8), 0.05f, 0.005f);

            if (S_navigate.opacity < 0.0001f) {
                S_navigate.mode++;
            } else if (mRmTp_PleaseDrawLightSwitch()) {
                S_navigate.draw_type = 2;
            } else {
                S_navigate.draw_type = 1;
            }

            break;
        }

        case 3: {
            break;
        }
    }
}

static void navigate_camera_draw(GAME_PLAY* play) {
    GRAPH* g = play->game.graph;
    Gfx* font_gfx;
    N64Mtx* font_mtx;

    OPEN_DISP(g);

    font_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    if (S_navigate.draw_type != 0) {
        u8 a = S_navigate.opacity * 255.0f;

        if (font_mtx != NULL) {
            mFont_CulcOrthoMatrix(font_mtx);
            gSPMatrix(NOW_FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        }

        Matrix_scale(16.0f, 16.0f, 16.0f, MTX_LOAD);

        font_gfx = NOW_FONT_DISP;
        gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(font_gfx++, fki_win_mode);

        /* draw camera movement guide gfx */
        gDPSetPrimColor(font_gfx++, 0, 255, 40, 40, 140, a);
        gSPDisplayList(font_gfx++, cam_win_winT_model);

        gDPSetPrimColor(font_gfx++, 0, 255, 245, 245, 30, a);
        gSPDisplayList(font_gfx++, cam_win_cT_model);

        gDPSetPrimColor(font_gfx++, 0, 255, 255, 255, 255, a);
        gSPDisplayList(font_gfx++, cam_win_mojiT_model);

        gDPSetPrimColor(font_gfx++, 0, 255, 30, 165, 30, a);
        gSPDisplayList(font_gfx++, cam_win_yajirushi_model);

        if (S_navigate.draw_type == 2) {
            /* draw light switch guide */
            gDPSetPrimColor(font_gfx++, 0, 255, 40, 40, 140, a);
            gSPDisplayList(font_gfx++, elc_win_winT_model);

            gDPSetPrimColor(font_gfx++, 0, 255, 30, 0, 50, a);
            gSPDisplayList(font_gfx++, elc_win_zT_model);

            gDPSetPrimColor(font_gfx++, 0, 255, 215, 225, 255, a);
            gSPDisplayList(font_gfx++, elc_win_moji_model);

            gDPSetPrimColor(font_gfx++, 0, 255, 255, 255, 255, a);
            gSPDisplayList(font_gfx++, elc_win_moji2T_model);
        }

        SET_FONT_DISP(font_gfx); // comenting this out fixes above flow but is wrong
    }

    CLOSE_DISP(g);
}

static void mWt_set_coin_se(int play_flag) {
    static int S_se_play_flg;

    if (play_flag == FALSE) {
        if (S_se_play_flg == TRUE) {
            sAdo_SysLevStop(NA_SE_COIN); // TODO: enum for sound effects
            S_mybell_conf.update_money = FALSE;
            S_mybell_conf.play_finish_sfx = FALSE;
            S_mybell_conf.coin_sfx_timer = 0;
        }
    } else if (S_se_play_flg == FALSE) {
        sAdo_SysLevStart(NA_SE_COIN);
        S_mybell_conf.update_money = TRUE;
        S_mybell_conf.play_finish_sfx = FALSE;
        S_mybell_conf.coin_sfx_timer = 300.0f;
    }

    S_se_play_flg = play_flag;
}

static u32 get_all_money();

static void mWt_mybell_confirmation_ct() {
    bzero(&S_mybell_conf, sizeof(S_mybell_conf));

    S_mybell_conf.all_money = get_all_money();
    mWt_set_coin_se(FALSE);
}

static void mWt_mybell_confirmation_move(GAME_PLAY* play) {
    static int place_chk[8] = {
        SCENE_SHOP0,    SCENE_CONVENI,     SCENE_SUPER,       SCENE_DEPART,
        SCENE_DEPART_2, SCENE_BROKER_SHOP, SCENE_POST_OFFICE, SCENE_NEEDLEWORK,
    };

    int i;

    S_mybell_conf.draw_type = 0;

    if (S_mybell_conf.play_finish_sfx == TRUE) {
        sAdo_SysTrgStart(SE_REGISTER);
        S_mybell_conf.play_finish_sfx = FALSE;
    }

    if (S_mybell_conf.coin_sfx_timer > 0.0f) {
        S_mybell_conf.coin_sfx_timer -= (f32)play->game.graph->dt_num_60fps_frames;
        if (S_mybell_conf.coin_sfx_timer <= 0.0f) {
            mWt_set_coin_se(FALSE);
        }
    }

    for (i = 0; i < 8; i++) {
        if (Save_Get(scene_no) == place_chk[i]) {
            break;
        }
    }

    if ((u32)i == 8 || mEv_CheckFirstJob() == TRUE ||
        (i <= 4 && Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI)) {
        if (S_mybell_conf.update_money == TRUE) {
            S_mybell_conf.all_money = get_all_money();
            mWt_set_coin_se(FALSE);
        }

        S_mybell_conf.update_money = FALSE;
    } else {
        switch (S_mybell_conf.mode) {
            case 0: {
                if (play->submenu.process_status == mSM_PROCESS_WAIT) {
                    S_mybell_conf.mode++;
                }
                break;
            }

            case 1: {
                f32 money = S_mybell_conf.all_money;
                u32 now_money = get_all_money();

                if (S_mybell_conf.all_money != now_money) {
                    mWt_set_coin_se(TRUE);
                }

                if (play->submenu.process_status != mSM_PROCESS_WAIT) {
                    S_mybell_conf.mode++;
                }

                if ((S_mybell_conf.update_money == TRUE) &&
                    (S_mybell_conf.all_money == now_money || S_mybell_conf.mode == 2)) {
                    mWt_set_coin_se(FALSE);
                    if (S_mybell_conf.all_money == now_money) {
                        S_mybell_conf.play_finish_sfx = TRUE;
                    }
                }

                add_calc(&money, now_money, 0.1f, 10000.0f, 1.0f);
                S_mybell_conf.all_money = money;
                add_calc(&S_mybell_conf.opacity, 1.0f, 1.0f - sqrtf(0.8), 0.075f, 0.005f);
                S_mybell_conf.draw_type = 1;
                break;
            }

            case 2: {
                add_calc(&S_mybell_conf.opacity, 0.0f, 1.0f - sqrtf(0.8), 0.05f, 0.005f);

                if (S_mybell_conf.opacity < 0.0001f) {
                    S_mybell_conf.mode = 0;
                } else {
                    S_mybell_conf.draw_type = 1;
                }
                break;
            }

            case 3: {
                break;
            }
        }
    }
}

static void mWt_mybell_confirmation_draw(GAME_PLAY* play) {
    GAME* game = (GAME*)play;
    GRAPH* g = play->game.graph;
    N64Mtx* font_mtx;
    Gfx* font_gfx;

    font_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    if (S_mybell_conf.draw_type != 0) {
        u8 a = S_mybell_conf.opacity * 255.0f;

        OPEN_DISP(g);

        if (font_mtx != NULL) {
            mFont_CulcOrthoMatrix(font_mtx);
            gSPMatrix(NOW_FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        }

        Matrix_scale(16.0f, 16.0f, 16.0f, MTX_LOAD);

        font_gfx = NOW_FONT_DISP;
        gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(font_gfx++, fki_win_mode);

        gDPSetRenderMode(font_gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetPrimColor(font_gfx++, 0, a, 95, 50, 175, a);
        gSPDisplayList(font_gfx++, mny_win_ueT_model);

        gDPSetRenderMode(font_gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(font_gfx++, 0, a, 255, 245, 255, a);
        gSPDisplayList(font_gfx++, mny_win_beruT_model);

        /* Draw "Bells" string (as pre-rendered image) */
        gDPSetPrimColor(font_gfx++, 0, a, 255, 245, 255, a);
        gSPDisplayList(font_gfx++, mny_win_mojiT_model);

        Matrix_scale(1.0f, 1.0f, 1.0f, MTX_LOAD);
        gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        SET_FONT_DISP(font_gfx);

        CLOSE_DISP(g);
        /* Draw bell amount */
        {
            u8 bell_str[7];
            f32 t;
            int len;

            mFont_UnintToString(bell_str, 7, S_mybell_conf.all_money, 6, TRUE, FALSE, TRUE);
            len = mMl_strlen(bell_str, 7, CHAR_SPACE);

            mFont_SetLineStrings(game, bell_str, 7, 260.0f - (mFont_GetStringWidth(bell_str, len, TRUE) * 0.75f), 48.0f,
                                 255, 245, 0, a, FALSE, TRUE, 0.75f, 0.75f, mFont_MODE_FONT);
        }
    }
}

static u32 get_all_money() {
    static mActor_name_t fg_name[MONEY_NUM] = { ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000, ITM_MONEY_100 };
    static u32 amount[MONEY_NUM] = { 1000, 10000, 30000, 100 };

    u32 money = Common_Get(now_private)->inventory.wallet;
    int i;

    for (i = 0; i < MONEY_NUM; i++) {
        int sum = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), fg_name[i], mPr_ITEM_COND_NORMAL);
        money += sum * amount[i];
    }

    return money;
}
