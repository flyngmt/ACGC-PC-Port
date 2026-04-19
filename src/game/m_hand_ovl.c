#include "m_hand_ovl.h"

#include "m_submenu_ovl.h"
#include "m_tag_ovl.h"
#include "m_debug.h"
#include "audio.h"
#include "m_common_data.h"
#include "m_cporiginal_ovl.h"
#include "m_gba_ovl.h"
#include "m_inventory_ovl.h"
#include "m_player_lib.h"
#include "m_needlework_ovl.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static mHD_Ovl_c hand_ovl_data;

extern cKF_Animation_R_c cKF_ba_r_hnd_sasu;
extern cKF_Animation_R_c cKF_ba_r_hnd_side;
extern cKF_Animation_R_c cKF_ba_r_hnd_catch;

static cKF_AnimInfo_c mHD_animeTable[mHD_ACTION_NUM] = {
    { &cKF_ba_r_hnd_sasu, 1.0f, 1.0f, 16.0f, cKF_FRAMECONTROL_REPEAT, 0.0f },
    { &cKF_ba_r_hnd_side, 1.0f, 1.0f, 16.0f, cKF_FRAMECONTROL_REPEAT, 0.0f },
    { &cKF_ba_r_hnd_catch, 1.0f, 1.0f, 7.0f, cKF_FRAMECONTROL_STOP, 0.0f },
    { &cKF_ba_r_hnd_catch, 1.0f, 7.0f, 7.0f, cKF_FRAMECONTROL_STOP, 0.0f },
    { &cKF_ba_r_hnd_catch, 1.0f, 7.0f, 1.0f, cKF_FRAMECONTROL_STOP, 0.0f },
    { &cKF_ba_r_hnd_catch, 1.0f, 1.0f, 7.0f, cKF_FRAMECONTROL_STOP, 0.0f },
    { &cKF_ba_r_hnd_sasu, 1.0f, 1.0f, 16.0f, cKF_FRAMECONTROL_REPEAT, 0.0f },
};

static f32 mHD_animeSpdTable[mHD_ACTION_NUM] = { 0.275f, 0.275f, 0.45f, 0.45f, 0.45f, 0.45f, 0.275f };

static f32 mHD_hand_offsetX_table[mHD_ACTION_NUM] = { 16.0f, 16.0f, 10.0f, 10.0f, 10.0f, 10.0f, 16.0f };
static f32 mHD_hand_offsetY_table[mHD_ACTION_NUM] = { 6.0f, 6.0f, 2.0f, 2.0f, 2.0f, 2.0f, 6.0f };

static void mHD_set_anime(Submenu* submenu, cKF_SkeletonInfo_R_c* keyframe) {
    int idx = submenu->overlay->hand_ovl->info.act;
    cKF_AnimInfo_c* anim_info = &mHD_animeTable[idx];
    f32 anim_speed = mHD_animeSpdTable[idx];

    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, anim_info->animation, anim_info->start_frame,
                            anim_info->end_frame, anim_info->start_frame, anim_speed, 0.0f, anim_info->mode, NULL);
}

extern cKF_Skeleton_R_c cKF_bs_r_hnd;

static void mHD_hand_shape_init(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    cKF_SkeletonInfo_R_c* keyframe = &hand_ovl->info.keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_hnd, NULL, hand_ovl->info.work, hand_ovl->info.morph);
    mHD_set_anime(submenu, keyframe);
    keyframe->morph_counter = 0.0f;
}

static void mHD_hand_shape_move(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    hand_ovl->info.keyframe_state = cKF_SkeletonInfo_R_play(&hand_ovl->info.keyframe);
}

static void mHD_calc_hand_offset(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    chase_f(&hand_ovl->info.ofs[0], mHD_hand_offsetX_table[hand_ovl->info.act], 0.5f);
    chase_f(&hand_ovl->info.ofs[1], mHD_hand_offsetY_table[hand_ovl->info.act], 0.5f);
}

static void mHD_hand_pos_get(Submenu* submenu, f32* pos, int table_type, int table_idx, mHD_Ovl_c* hand_ovl) {
    mActor_name_t item = hand_ovl->info.item;

    submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, table_type, table_idx);

    if (table_type == mTG_TABLE_MUSIC_MAIN) {
        pos[0] += 4.0f;
        pos[1] += 5.0f;
    }

    if (table_type == mTG_TABLE_NEEDLEWORK && item != EMPTY_NO && !(item >= RSV_CLOTH && item <= RSV_CLOTH7) &&
        !(item >= ITM_MY_ORG_UMBRELLA0 && item <= ITM_MY_ORG_UMBRELLA7)) {
        if (submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK].data0 == mNW_OPEN_DESIGN) {
            pos[0] += -11.0f;
            pos[1] += 23.0f;
        } else {
            pos[1] += 23.0f;
        }
    } else if ((table_type == mTG_TABLE_GBA || table_type == mTG_TABLE_GBA_NW || table_type == mTG_TABLE_CARD ||
                table_type == mTG_TABLE_CARD_NW || table_type == mTG_TABLE_CPORIGINAL ||
                table_type == mTG_TABLE_CPORIGINAL_NW) &&
               item != EMPTY_NO) {
        pos[0] += -2.0f;
        pos[1] += 17.0f;
    } else if (((item != EMPTY_NO && !(item >= RSV_CLOTH && item <= RSV_CLOTH7) &&
                 !(item >= ITM_MY_ORG_UMBRELLA0 && item <= ITM_MY_ORG_UMBRELLA7)) ||
                mMl_check_not_used_mail(&hand_ovl->info.mail) == FALSE) &&
               table_type != mTG_TABLE_CPMAIL_WC && table_type != mTG_TABLE_CPORIGINAL_WC) {
        pos[0] += -5.0f;
        pos[1] += 12.0f;
    }
}

static void mHD_update_logical_position(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int table_idx = submenu->overlay->tag_ovl->get_table_idx_proc(tag);
    f32 pos[2];
    f32 dX;
    f32 dY;
    f32 rate;

    if (hand_ovl->info.move_flag == mHD_MOVE_SWITCH_LEFT) {
        pos[0] = -160.0f;
        pos[1] = hand_ovl->info.pos[1];
        rate = 1.0f;
    } else if (hand_ovl->info.move_flag == mHD_MOVE_SWITCH_RIGHT) {
        pos[0] = 160.0f;
        pos[1] = hand_ovl->info.pos[1];
        rate = 1.0f;
    } else {
        mHD_hand_pos_get(submenu, pos, tag->table, table_idx, hand_ovl);
        rate = 0.5f;
    }

    dX = pos[0] - hand_ovl->info.pos[0];
    dY = pos[1] - hand_ovl->info.pos[1];

    if (fabsf(dX) > 0.01f || fabsf(dY) > 0.01f) {
        f32 dist;
        f32 dist2;
        f32 calc;

        dist = dist2 = sqrtf(SQ(dX) + SQ(dY));
        dist = dist2; // this second set is necessary for Aus version, seems sus
        calc = add_calc(&dist2, 0.0f, CALC_EASE(rate), (12.0f + GETREG(UREG, 19) * 0.1f) * 0.5f, (1.0f + GETREG(UREG, 20) * 0.1f) * 0.5f);

        if (fabsf(calc) < 0.1f) {
            if (hand_ovl->info.move_flag == mHD_MOVE_SWITCH_LEFT) {
                submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, hand_ovl->info.pos, tag->table, table_idx);
                hand_ovl->info.pos[0] = 160.0f;
                hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
            } else if (hand_ovl->info.move_flag == mHD_MOVE_SWITCH_RIGHT) {
                submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, hand_ovl->info.pos, tag->table, table_idx);
                hand_ovl->info.pos[0] = -160.0f;
                hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
            } else {
                hand_ovl->info.pos[0] = pos[0];
                hand_ovl->info.pos[1] = pos[1];
                hand_ovl->info.move_flag = mHD_MOVE_NONE;
            }
        } else {
            f32 percent;

            if (hand_ovl->info.move_flag == mHD_MOVE_NONE) {
                hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
            }

            percent = fabsf(dist - dist2) / dist;
            hand_ovl->info.pos[0] += dX * percent;
            hand_ovl->info.pos[1] += dY * percent;
        }
    } else {
        hand_ovl->info.move_flag = mHD_MOVE_NONE;
    }
}

static void mHD_update_visual_position(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;

#ifdef MOUSE_INPUT
    if (tag_ovl->mouse_active) {
        f32 target_x = (tag_ovl->mouse_x - 160.0f);
        f32 target_y = (120.0f - tag_ovl->mouse_y);
        
        f32 dX = target_x - hand_ovl->info.visual_pos[0];
        f32 dY = target_y - hand_ovl->info.visual_pos[1];
        
        if (fabsf(dX) > 0.1f || fabsf(dY) > 0.1f) {
            f32 speed = 0.3f;
            hand_ovl->info.visual_pos[0] += dX * speed;
            hand_ovl->info.visual_pos[1] += dY * speed;
        } else {
            hand_ovl->info.visual_pos[0] = target_x;
            hand_ovl->info.visual_pos[1] = target_y;
        }
    } else
#endif
    {
        f32 dX = hand_ovl->info.pos[0] - hand_ovl->info.visual_pos[0];
        f32 dY = hand_ovl->info.pos[1] - hand_ovl->info.visual_pos[1];
        
        if (fabsf(dX) > 0.1f || fabsf(dY) > 0.1f) {
            f32 speed = 0.3f;
            hand_ovl->info.visual_pos[0] += dX * speed;
            hand_ovl->info.visual_pos[1] += dY * speed;
        } else {
            hand_ovl->info.visual_pos[0] = hand_ovl->info.pos[0];
            hand_ovl->info.visual_pos[1] = hand_ovl->info.pos[1];
        }
    }
}

static void mHD_hand_position_move(Submenu* submenu) {
    /* Update logical position (what the game uses for item logic) */
    mHD_update_logical_position(submenu);
    
    /* Update visual position (what we render) */
    mHD_update_visual_position(submenu);
}

static void mHD_drop_item(Submenu* submenu, mTG_tag_c* tag, mActor_name_t* item, Mail_c* mail) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[submenu->menu_type];
    int table;
    int table_idx = submenu->overlay->tag_ovl->get_table_idx_proc(&submenu->overlay->tag_ovl->tags[0]);
    mActor_name_t now_item;

    if (hand_ovl->info.ret_flag) {
        table = hand_ovl->info.hold_tbl;
        table_idx = hand_ovl->info.hold_idx;
    } else {
        table = tag->table;
    }

    if (item != NULL && *item != EMPTY_NO && table != mTG_TABLE_CARD_NW && table != mTG_TABLE_GBA_NW) {
        now_item = *item;
        mTG_mark_mainX(submenu, menu_info, table, table_idx, 2, 0);

        /* Duplicate check */
        if ((table != mTG_TABLE_NEEDLEWORK || table != mTG_TABLE_NEEDLEWORK ||
             (hand_ovl->info.item != EMPTY_NO && !(hand_ovl->info.item >= 0xFE31 && hand_ovl->info.item <= 0xFE38) &&
              !(hand_ovl->info.item >= 0xFE39 && hand_ovl->info.item <= 0xFE98) &&
              !(hand_ovl->info.item >= 0xFE99 && hand_ovl->info.item <= 0xFEA0))) &&
            table != mTG_TABLE_CPORIGINAL && table != mTG_TABLE_CPORIGINAL_NW && table != mTG_TABLE_CARD &&
            table != mTG_TABLE_GBA) {
            *item = hand_ovl->info.item;
        }

        if (!(now_item >= RSV_CLOTH && now_item <= RSV_CLOTH7) &&
            !(now_item >= ITM_MY_ORG_UMBRELLA0 && now_item <= ITM_MY_ORG_UMBRELLA7) &&
            !(*item >= 0xFE99 && *item <= 0xFEA0)) {
            if (table != mTG_TABLE_PLAYER && table != mTG_TABLE_BG &&
                (table != mTG_TABLE_NEEDLEWORK ||
                 (table == mTG_TABLE_NEEDLEWORK &&
                  (*item == EMPTY_NO || (*item >= 0xFE31 && *item <= 0xFE38) || (*item >= 0xFE39 && *item <= 0xFE98) ||
                   (*item >= 0xFE99 && *item <= 0xFEA0))))) {
                switch (table) {
                    case mTG_TABLE_NEEDLEWORK:
                    case mTG_TABLE_CPORIGINAL:
                    case mTG_TABLE_CPORIGINAL_NW: {
                        if ((*item == EMPTY_NO ||
                             ((*item >= 0xFE31 && *item <= 0xFE38) || (*item >= 0xFE39 && *item <= 0xFE98) ||
                              (*item >= 0xFE99 && *item <= 0xFEA0)))) {
                            mCO_swap_image(submenu, hand_ovl->info.item, *item);
                        } else {
                            hand_ovl->info.item = now_item;
                        }
                        break;
                    }
                    default: {
                        hand_ovl->info.item = now_item;
                    }
                }

                hand_ovl->info.next_act = mHD_ACTION_CLOSE;
                sAdo_SysTrgStart(NA_SE_41C);

                if (mail != NULL) {
                    if (mail->content.font == mMl_FONT_RECV) {
                        mail->content.font = mMl_FONT_RECV_PLAYER_PRESENT;
                        hand_ovl->info.item_cond = mPr_ITEM_COND_PRESENT;
                    } else if (mail->content.font == mMl_FONT_RECV_READ) {
                        mail->content.font = mMl_FONT_RECV_PLAYER_PRESENT_READ;
                        hand_ovl->info.item_cond = mPr_ITEM_COND_PRESENT;
                    }
                }
            } else {
                int set_item = FALSE;

                hand_ovl->info.item = EMPTY_NO;
                hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
                hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
                hand_ovl->info.next_act = mHD_ACTION_SASU;

                if (hand_ovl->info.hold_tbl == mTG_TABLE_ITEM) {
                    if (Now_Private->inventory.pockets[hand_ovl->info.hold_idx] == EMPTY_NO) {
                        mPr_SetPossessionItem(Now_Private, hand_ovl->info.hold_idx, now_item, mPr_ITEM_COND_NORMAL);
                        set_item = TRUE;
                    }
                } else if (hand_ovl->info.hold_tbl == mTG_TABLE_MAIL) {
                    if (Now_Private->mail[hand_ovl->info.hold_idx].present == EMPTY_NO) {
                        Now_Private->mail[hand_ovl->info.hold_idx].present = now_item;
                        set_item = TRUE;
                    }
                }

                if (set_item == FALSE) {
                    int idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

                    if (idx >= 0) {
                        mPr_SetPossessionItem(Now_Private, idx, now_item, mPr_ITEM_COND_NORMAL);
                    } else {
                        /* No free inventory spots so put it back in the hand */
                        hand_ovl->info.item = now_item;
                        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
                    }
                }

                if (table == mTG_TABLE_BG) {
                    if (hand_ovl->info.item == EMPTY_NO) {
                        sAdo_SysTrgStart(NA_SE_60);
                    } else {
                        sAdo_SysTrgStart(NA_SE_41C);
                    }
                }
            }
        } else {
            hand_ovl->info.item = EMPTY_NO;
            hand_ovl->info.next_act = mHD_ACTION_SASU;
            hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        }
    } else {
        mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[submenu->menu_type];

        mTG_mark_mainX(submenu, menu_info, table, table_idx, 2, 0);

        if (table == mTG_TABLE_GBA_NW || table == mTG_TABLE_CARD_NW) {
            mGB_copy_image(submenu, hand_ovl->info.item, *item);
        } else if (item != NULL) {
            *item = hand_ovl->info.item;

            if (mail != NULL) {
                if (mail->content.font == mMl_FONT_RECV) {
                    mail->content.font = mMl_FONT_RECV_PLAYER_PRESENT;
                } else if (mail->content.font == mMl_FONT_RECV_READ) {
                    mail->content.font = mMl_FONT_RECV_PLAYER_PRESENT_READ;
                }
            }
        }

        hand_ovl->info.item = EMPTY_NO;
        hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
        hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        hand_ovl->info.next_act = mHD_ACTION_SASU;

        if (table != mTG_TABLE_PLAYER) {
            if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_EXCHANGE) {
                submenu->overlay->tag_ovl->exchange_proc(submenu, menu_info);
            } else {
                sAdo_SysTrgStart(NA_SE_60);
            }
        }
    }

    submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);

    if (overlay->segment.player_main_anime_idx == mIV_ANIM_CATCH) {
        overlay->segment.change_player_main_anime_idx = mIV_ANIM_WALK;
    }
}

#define mHD_TICKET_MONTH(item) (1 + (((item) >> 3) & 0xF))
#define mHD_TICKET_COUNT(item) ((item) & 7)

static void mHD_prepare_drop_ticket(mHD_Ovl_c* hand_ovl, mActor_name_t* item, int idx) {
    u32 cond = hand_ovl->info.item_cond;

    /* Both are ITEM1 type */
    if (ITEM_IS_ITEM1(hand_ovl->info.item) && ITEM_IS_ITEM1(*item)) {
        /* both are tickets */
        if (ITEM_NAME_GET_CAT(hand_ovl->info.item) == ITEM1_CAT_TICKET &&
            ITEM_NAME_GET_CAT(*item) == ITEM1_CAT_TICKET) {
            /* @BUG - only the hand item has a condition */
            if (cond == mPr_ITEM_COND_NORMAL && cond == mPr_ITEM_COND_NORMAL) {
                /* from same month */
                int month = mHD_TICKET_MONTH(hand_ovl->info.item);
                if (month == mHD_TICKET_MONTH(*item)) {
                    int held_num = mHD_TICKET_COUNT(hand_ovl->info.item) + 1;
                    int target_num = mHD_TICKET_COUNT(*item) + 1;

                    /* no max stack tickets */
                    if (held_num != TICKET_STACK_MAX && target_num != TICKET_STACK_MAX) {
                        int total = held_num + target_num;
                        int new_total = total - TICKET_STACK_MAX;

                        if (new_total > 0) {
                            /* Stack went over max */
                            Now_Private->inventory.pockets[idx] =
                                ITM_TICKET_START | ((month - 1) << 3) | (new_total - 1);
                            hand_ovl->info.item = ITM_TICKET_START | ((month - 1) << 3) | (TICKET_STACK_MAX - 1);
                        } else {
                            Now_Private->inventory.pockets[idx] = EMPTY_NO;
                            hand_ovl->info.item = ITM_TICKET_START | ((month - 1) << 3) | (total - 1);
                        }
                    }
                }
            }
        }
    }
}

#define mHD_WISP2NUM(wisp) (1 + wisp - ITM_SPIRIT0)
static void mHD_prepare_drop_wisp(mHD_Ovl_c* hand_ovl, mActor_name_t* item, int idx) {
    u32 cond = hand_ovl->info.item_cond;

    /* Held item must be a spirit */
    if (ITEM_IS_WISP(hand_ovl->info.item)) {
        /* Target item must be a spirit */
        if (ITEM_IS_WISP(*item)) {
            /* Held item must not have any condition */
            if (cond == mPr_ITEM_COND_NORMAL && cond == mPr_ITEM_COND_NORMAL) {
                int held_num = ITEM_IS_WISP(hand_ovl->info.item) ? mHD_WISP2NUM(hand_ovl->info.item) : 0;
                int target_num = ITEM_IS_WISP(*item) ? mHD_WISP2NUM(*item) : 0;

                if (held_num != WISP_STACK_MAX && target_num != WISP_STACK_MAX) {
                    int total = held_num + target_num;
                    int new_total = total - WISP_STACK_MAX;

                    if (new_total > 0) {
                        Now_Private->inventory.pockets[idx] = ITM_SPIRIT0 + (new_total - 1);
                        hand_ovl->info.item = ITM_SPIRIT4; /* 5 in hand */
                    } else {
                        Now_Private->inventory.pockets[idx] = EMPTY_NO;
                        hand_ovl->info.item = ITM_SPIRIT0 + (total - 1);
                    }
                }
            }
        }
    }
}

static void mHD_prepare_drop_paper(mHD_Ovl_c* hand_ovl, mActor_name_t* item, int idx) {
    u32 cond = hand_ovl->info.item_cond;
    int type;

    /* Held item must be stationery */
    if (ITEM_IS_PAPER(hand_ovl->info.item)) {
        /* Target item must be stationery */
        if (ITEM_IS_PAPER(*item)) {
            int paper_idx = hand_ovl->info.item - ITM_PAPER_START;
            int paper_idx2 = *item - ITM_PAPER_START;

            type = PAPER2TYPE(paper_idx);

            /* Stationery must be the same type */
            if (type == PAPER2TYPE(paper_idx2)) {
                /* Held item must not have any condition */
                if (cond == mPr_ITEM_COND_NORMAL && cond == mPr_ITEM_COND_NORMAL) {
                    int held_num = 1 + PAPER2STACK(paper_idx);
                    int target_num = 1 + PAPER2STACK(paper_idx2);

                    if (held_num != PAPER_STACK_MAX && target_num != PAPER_STACK_MAX) {
                        int total = held_num + target_num;
                        int new_total = total - PAPER_STACK_MAX;

                        if (new_total > 0) {
                            Now_Private->inventory.pockets[idx] =
                                ITM_PAPER_START + type + (new_total - 1) * PAPER_UNIQUE_NUM;
                            hand_ovl->info.item = ITM_PAPER_STACK_FOUR_START + type; /* 4 stack in hand */
                        } else {
                            Now_Private->inventory.pockets[idx] = EMPTY_NO;
                            hand_ovl->info.item = ITM_PAPER_START + type + (total - 1) * PAPER_UNIQUE_NUM;
                        }
                    }
                }
            }
        }
    }
}

static void mHD_drop_item2(Submenu* submenu, mTG_tag_c* tag, mActor_name_t* item, int idx) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int cond = hand_ovl->info.item_cond;

    if (*item != EMPTY_NO) {
        hand_ovl->info.item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
    } else {
        hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
    }

    Now_Private->inventory.item_conditions = mPr_SET_ITEM_COND(Now_Private->inventory.item_conditions, idx, cond);
    mHD_prepare_drop_ticket(hand_ovl, item, idx);
    mHD_prepare_drop_wisp(hand_ovl, item, idx);
    mHD_prepare_drop_paper(hand_ovl, item, idx);
    mHD_drop_item(submenu, tag, item, NULL);
}

static void mHD_open_sack(Submenu* submenu) {
    static int sack_amount[] = { 1000, 10000, 30000, 100 };
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int amount = sack_amount[hand_ovl->info.item - ITM_MONEY_START];

    hand_ovl->info.item = EMPTY_NO;
    Now_Private->inventory.wallet += amount;
    hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
    hand_ovl->info.next_act = mHD_ACTION_SASU;
    hand_ovl->info.wait_timer = 42;
    sAdo_SysTrgStart(MONO(NA_SE_52));
    submenu->overlay->inventory_ovl->disp_money_chg_step = amount / 42;
}

static void mHD_drop_mail(Submenu* submenu, Mail_c* mail) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (mMl_check_not_used_mail(mail) == TRUE) {
        mMl_copy_mail(mail, &hand_ovl->info.mail);
        mMl_clear_mail(&hand_ovl->info.mail);
        hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        hand_ovl->info.next_act = mHD_ACTION_SASU;
        sAdo_SysTrgStart(NA_SE_60);
    } else {
        Mail_c tmp_mail;

        mTG_mark_main(submenu, &submenu->overlay->menu_info[submenu->menu_type], 2, 0);
        mMl_copy_mail(&tmp_mail, mail);
        mMl_copy_mail(mail, &hand_ovl->info.mail);
        mMl_copy_mail(&hand_ovl->info.mail, &tmp_mail);
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        sAdo_SysTrgStart(NA_SE_41C);
    }

    submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
}

static void mHD_change_iv_back_segment(void) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    int idx = ITEM_IS_CLOTH(Now_Private->backgound_texture) ? (Now_Private->backgound_texture - ITM_CLOTH_START) : 0;

    play->submenu_ground_idx ^= 1;
    mPlib_Load_PlayerTexAndPallet(play->submenu_ground_tex[play->submenu_ground_idx],
                                  play->submenu_ground_pallet[play->submenu_ground_idx], idx);
}

static void mHD_open_end_proc_item_type0(Submenu* submenu, int idx, int table) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    mQst_CheckPutItem(hand_ovl->info.item, idx);
    mHD_drop_item2(submenu, tag, &Now_Private->inventory.pockets[idx], idx);
}

static void mHD_open_end_proc_item_type1(Submenu* submenu, int idx, int table) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    mHD_drop_item(submenu, tag, &Now_Private->mail[idx].present, &Now_Private->mail[idx]);
}

static void mHD_open_end_proc_item_type2(Submenu* submenu, int idx, int table) {
    mHD_open_sack(submenu);
}

static void mHD_open_end_proc_item_type3(Submenu* submenu, int idx, int table) {
    u16 cloth_idx;
    mPr_cloth_c* cloth_p;
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    mActor_name_t item = hand_ovl->info.item;
    int category = ITEM_NAME_GET_CAT(item);

    if (item == RSV_CLOTH || ITEM_IS_CLOTH(item)) {
        if (cKF_FrameControl_passCheck_now(&submenu->overlay->inventory_ovl->player_main_keyframe.frame_control,
                                           36.0f)) {
            cloth_p = &Now_Private->cloth;

            mHD_drop_item(submenu, tag, &cloth_p->item, NULL);
            if (cloth_p->item == RSV_CLOTH) {
                cloth_idx = 0x100 + mNW_get_image_no(submenu, submenu->overlay->tag_ovl->get_table_idx_proc(tag));
            } else {
                cloth_idx = ITEM_IS_CLOTH(cloth_p->item) ? (cloth_p->item - ITM_CLOTH_START) : 0;
            }

            cloth_p->idx = cloth_idx;
            mPlib_change_player_cloth(gamePT, Now_Private->cloth.idx);
        }
    } else if (category == ITEM1_CAT_FRUIT) {
        submenu->overlay->inventory_ovl->food_idx = (u8)(item - ITM_FOOD_START);
        mHD_drop_item(submenu, tag, NULL, NULL);
    } else if (category == ITEM1_CAT_KABU) {
        submenu->overlay->inventory_ovl->food_idx = 8; // TODO: needs enum
        mHD_drop_item(submenu, tag, NULL, NULL);
    } else {
        mHD_drop_item(submenu, tag, &Now_Private->equipment, NULL);
    }
}

static void mHD_open_end_proc_item_type4(Submenu* submenu, int idx, int table) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    mPr_SetItemCollectBit(Now_Private->backgound_texture);
    mHD_drop_item(submenu, tag, &Now_Private->backgound_texture, NULL);
    mHD_change_iv_back_segment();
}

static void mHD_open_end_proc_item_type6(Submenu* submenu, int idx, int table) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[submenu->menu_type];
    int flag;

    if (hand_ovl->info.ret_flag) {
        flag = FALSE;
    } else {
        flag = TRUE;
    }

    mHD_drop_item(submenu, tag, &Save_Get(homes[menu_info->data1]).haniwa.items[idx].item, NULL);
    if (flag == TRUE) {
        submenu->overlay->tag_ovl->item_name_wait_time = 0;
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, tag->table, mTG_TYPE_HANIWA_PUT_ITEM, 0, tag->base_pos[0],
                                                     tag->base_pos[1]);
    }
}

static void mHD_open_end_proc_item_type17(Submenu* submenu, int idx, int table) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int folder;
    mActor_name_t tmp_item;
    mActor_name_t hand_item;
    mActor_name_t cur_item;

    if (ITEM_IS_RSVNWORG(hand_ovl->info.item) || ITEM_IS_RSVCPORG(hand_ovl->info.item) ||
        ITEM_IS_RSVGBAORG(hand_ovl->info.item)) {
        switch (table) {
            case mTG_TABLE_NEEDLEWORK:
            case mTG_TABLE_CPORIGINAL_NW:
                if (mNW_check_hide_flg(submenu, idx)) {
                    tmp_item = EMPTY_NO;
                } else {
                    tmp_item = RSV_NW_ORIGINAL0 + idx;
                }
                break;
            case mTG_TABLE_GBA_NW:
            case mTG_TABLE_CARD_NW:
                tmp_item = RSV_NW_ORIGINAL0 + idx;
                break;
            case mTG_TABLE_CPORIGINAL:
                folder = mCO_top_folder(submenu);

                if (mCO_check_hide_flg(submenu, folder, idx)) {
                    tmp_item = EMPTY_NO;
                } else {
                    tmp_item = RSV_CPORIGINAL_FLD0_00 + folder * 12 + idx;
                }
                break;
            case mTG_TABLE_GBA:
            case mTG_TABLE_CARD:
                tmp_item = EMPTY_NO;
                break;
        }

        hand_item = hand_ovl->info.item;
        cur_item = tmp_item;

        mHD_drop_item(submenu, tag, &tmp_item, NULL);

        if (hand_item == tmp_item && cur_item == hand_ovl->info.item) {
            if (tmp_item == EMPTY_NO) {
                if (table == mTG_TABLE_CPORIGINAL) {
                    mCO_on_hide_flg(submenu, folder, idx);
                } else {
                    mNW_on_hide_flg(submenu, idx);
                }
            }

            if (hand_ovl->info.item == EMPTY_NO) {
                if (table == mTG_TABLE_CPORIGINAL) {
                    mCO_clear_hide_flg(submenu);
                } else {
                    mNW_clear_hide_flg(submenu);
                }

                submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
            }
        }
    }
}

typedef void (*mHD_OPEN_END_PROC)(Submenu*, int, int);

static void mHD_open_end_proc_item(Submenu* submenu) {
    static mHD_OPEN_END_PROC proc_table[] = {
        &mHD_open_end_proc_item_type0,  /* mTG_TABLE_ITEM */
        &mHD_open_end_proc_item_type1,  /* mTG_TABLE_MAIL */
        &mHD_open_end_proc_item_type2,  /* mTG_TABLE_MONEY */
        &mHD_open_end_proc_item_type3,  /* mTG_TABLE_PLAYER */
        &mHD_open_end_proc_item_type4,  /* mTG_TABLE_BG */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_MBOX */
        &mHD_open_end_proc_item_type6,  /* mTG_TABLE_HANIWA */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_COLLECT */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_WCHANGE */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPMAIL */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPMAIL_WC */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPMAIL_TI */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPEDIT */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPEDIT_END */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CATALOG */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CATALOG_WC */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_MUSIC_MAIN */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_NEEDLEWORK */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_CPORIGINAL */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_INVENTORY_WC_ORG */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_CPORIGINAL_NW */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPORIGINAL_WC */
        (mHD_OPEN_END_PROC)&none_proc1, /* mTG_TABLE_CPORIGINAL_TI */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_GBA */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_GBA_NW */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_CARD */
        &mHD_open_end_proc_item_type17, /* mTG_TABLE_CARD_NW */
    };

    mSM_MenuInfo_c* menu_info;
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx;
    int table;

    if (hand_ovl->info.ret_flag) {
        table = hand_ovl->info.hold_tbl;
        idx = hand_ovl->info.hold_idx;
    } else {
        table = tag->table;
        idx = submenu->overlay->tag_ovl->get_table_idx_proc(tag);
    }

    if (hand_ovl->info.item_cond == mPr_ITEM_COND_NORMAL) {
        mPr_SetItemCollectBit(hand_ovl->info.item);
    }

    (*proc_table[table])(submenu, idx, table);

    if (table == mTG_TABLE_HANIWA) {
        s16 tmp_cond = hand_ovl->info.haniwa_item_cond;
        u32 tmp_price = hand_ovl->info.haniwa_item_price;

        menu_info = &submenu->overlay->menu_info[submenu->menu_type];
        hand_ovl->info.haniwa_item_cond = Save_Get(homes[menu_info->data1]).haniwa.items[idx].exchange_type;
        hand_ovl->info.haniwa_item_price = Save_Get(homes[menu_info->data1]).haniwa.items[idx].extra_data;
        Save_Get(homes[menu_info->data1]).haniwa.items[idx].exchange_type = tmp_cond;
        Save_Get(homes[menu_info->data1]).haniwa.items[idx].extra_data = tmp_price;
    } else {
        hand_ovl->info.haniwa_item_cond = mHm_HANIWA_TRADE_1;
        hand_ovl->info.haniwa_item_price = 0;
    }
}

static void mHD_open_end_proc_mail(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    Mail_c* mail;

    if (hand_ovl->info.ret_flag) {
        mail = submenu->overlay->tag_ovl->get_mail_pointer_proc(submenu, hand_ovl);
    } else {
        mail = submenu->overlay->tag_ovl->get_mail_pointer_proc(submenu, NULL);
    }

    mHD_drop_mail(submenu, mail);
}

static void mHD_open_end_proc(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.item != EMPTY_NO) {
        mHD_open_end_proc_item(submenu);
    } else if (mMl_check_not_used_mail(&hand_ovl->info.mail) != TRUE) {
        mHD_open_end_proc_mail(submenu);
    }

    hand_ovl->info.ret_flag = FALSE;
}

static void mHD_close_move(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.keyframe_state == cKF_STATE_STOPPED) {
        hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        hand_ovl->info.next_act = mHD_ACTION_CLOSE_KEEP;
    }
}

static void mHD_open_move(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    if (hand_ovl->info.keyframe_state == cKF_STATE_STOPPED) {
        switch (tag->table) {
            case mTG_TABLE_CPMAIL_WC:
            case mTG_TABLE_CPORIGINAL_WC:
                hand_ovl->info.next_act = mHD_ACTION_SASU;
                hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
                break;
            default:
                mHD_open_end_proc(submenu);
                break;
        }
    } else if (hand_ovl->info.ret_flag) {
        switch (tag->table) {
            case mTG_TABLE_CPMAIL_WC:
            case mTG_TABLE_CPORIGINAL_WC:
                mHD_open_end_proc(submenu);
                break;
            default:
                break;
        }
    }
}

static void mHD_sasu2_move(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int category = ITEM_NAME_GET_CAT(hand_ovl->info.item);

    if (hand_ovl->info.item == RSV_CLOTH || ITEM_IS_CLOTH(hand_ovl->info.item)) {
        if (cKF_FrameControl_passCheck_now(&submenu->overlay->inventory_ovl->player_main_keyframe.frame_control,
                                           36.0f)) {
            mPr_cloth_c* cloth_p = &Now_Private->cloth;
            u16 cloth_idx;

            mHD_drop_item(submenu, tag, &cloth_p->item, NULL);
            if (cloth_p->item == RSV_CLOTH) {
                cloth_idx = 0x100 + mNW_get_image_no(submenu, submenu->overlay->tag_ovl->get_table_idx_proc(tag));
            } else {
                cloth_idx = ITEM_IS_CLOTH(cloth_p->item) ? (cloth_p->item - ITM_CLOTH_START) : 0;
            }

            cloth_p->idx = cloth_idx;
            mPlib_change_player_cloth(gamePT, Now_Private->cloth.idx);
            hand_ovl->info.next_act = mHD_ACTION_SASU;
            hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        }
    } else if (category == ITEM1_CAT_FRUIT) {
        // nothing
    } else if (category == ITEM1_CAT_KABU) {
        // nothing
    } else {
        if (hand_ovl->info.wait_timer <= 0) {
            mHD_drop_item(submenu, tag, &Now_Private->equipment, NULL);
            hand_ovl->info.next_act = mHD_ACTION_SASU;
            hand_ovl->info.move_flag = mHD_MOVE_NORMAL;
        }
    }
}

typedef void (*mHD_OVL_MOVE_PROC)(Submenu*);

static void mHD_hand_ovl_move(Submenu* submenu) {
    static mHD_OVL_MOVE_PROC process[mHD_ACTION_NUM] = {
        (mHD_OVL_MOVE_PROC)&none_proc1,
        (mHD_OVL_MOVE_PROC)&none_proc1,
        &mHD_close_move,
        (mHD_OVL_MOVE_PROC)&none_proc1,
        &mHD_open_move,
        &mHD_close_move,
        &mHD_sasu2_move,
    };

    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.type != 0) {
        mHD_hand_shape_move(submenu);
        mHD_hand_position_move(submenu);
        mHD_calc_hand_offset(submenu);

        (*process[hand_ovl->info.act])(submenu);
        if (hand_ovl->info.act != hand_ovl->info.next_act) {
            hand_ovl->info.act = hand_ovl->info.next_act;
            mHD_set_anime(submenu, &hand_ovl->info.keyframe);
        }
    }
}

extern Gfx inv_item_shadow_mode[];
extern Gfx inv_item_mode[];

static void mHD_draw_item(Submenu* submenu, GRAPH* graph, f32* pos) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.item != EMPTY_NO &&
        (!ITEM_IS_RSVCLOTH(hand_ovl->info.item) &&
         !(hand_ovl->info.item >= ITM_MY_ORG_UMBRELLA0 && hand_ovl->info.item <= ITM_MY_ORG_UMBRELLA7) &&
         !ITEM_IS_RSVNWORG(hand_ovl->info.item) && /* Needlework designs */
         !ITEM_IS_RSVCPORG(hand_ovl->info.item) && /* Stored original designs */
         !ITEM_IS_RSVGBAORG(hand_ovl->info.item)   /* GBA designs */
         )) {
        int present_flag = hand_ovl->info.item_cond & mPr_ITEM_COND_PRESENT;
        Gfx* gfx;

        /* Draw item shadow */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_shadow_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        submenu->overlay->draw_item_proc(graph, pos[0] + 4.0f, pos[1] - 4.0f, 1.0f, hand_ovl->info.item, present_flag,
                                         TRUE, 0, TRUE, FALSE);

        /* Draw item icon */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        submenu->overlay->draw_item_proc(graph, pos[0], pos[1], 1.0f, hand_ovl->info.item, present_flag, TRUE, 0, FALSE,
                                         FALSE);
    }
}

static void mHD_draw_mail(Submenu* submenu, GRAPH* graph, f32* pos) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    Mail_c* mail = &hand_ovl->info.mail;

    if (mMl_check_not_used_mail(mail) != TRUE) {
        Gfx* gfx;

        /* Draw item shadow */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_shadow_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        submenu->overlay->draw_mail_proc(graph, pos[0] + 4.0f, pos[1] - 4.0f, 1.0f, mail, TRUE, TRUE, FALSE);

        /* Draw item icon */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        submenu->overlay->draw_mail_proc(graph, pos[0], pos[1], 1.0f, mail, TRUE, FALSE, FALSE);
    }
}

static void mHD_draw_original(Submenu* submenu, GRAPH* graph, f32* pos) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (ITEM_IS_RSVNWORG(hand_ovl->info.item) || /* Needlework designs */
        ITEM_IS_RSVCPORG(hand_ovl->info.item) || /* Stored original designs */
        ITEM_IS_RSVGBAORG(hand_ovl->info.item)   /* GBA designs */
    ) {
        Gfx* gfx;

        /* Draw item shadow */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_shadow_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        mSM_draw_original(submenu, graph, pos[0] + 4.0f, pos[1] - 4.0f, 1.0f, hand_ovl->info.item, TRUE);

        /* Draw item icon */
        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPDisplayList(gfx++, inv_item_mode);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        mSM_draw_original(submenu, graph, pos[0], pos[1], 1.0f, hand_ovl->info.item, FALSE);
    }
}

#define mHD_ROT_X DEG2SHORT_ANGLE(-135.0f)
#define mHD_ROT_Y DEG2SHORT_ANGLE(0.0f)
#define mHD_ROT_Z DEG2SHORT_ANGLE(70.3125f)

static void mHD_hand_shape_draw(Submenu* submenu, GAME* game, int shadow_flag) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    GRAPH* graph = game->graph;
    Mtx* mtx = (Mtx*)GRAPH_ALLOC_TYPE(graph, Mtx, hand_ovl->info.keyframe.skeleton->num_shown_joints);

    if (mtx != NULL) {
        if (shadow_flag) {
            Matrix_translate(0.0f, 0.0f, 76.4f, MTX_LOAD);
        } else {
            Matrix_translate(0.0f, 0.0f, 77.0f, MTX_LOAD);
        }

        if (shadow_flag) {
            Matrix_scale(0.042f, 0.042f, 0.0f, MTX_MULT);
        } else {
            Matrix_scale(0.04f, 0.04f, 0.04f, MTX_MULT);
        }

        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
        Matrix_rotateXYZ(mHD_ROT_X, mHD_ROT_Y, mHD_ROT_Z, MTX_MULT);

        OPEN_DISP(graph);

        gDPPipeSync(NEXT_POLY_OPA_DISP);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        _texture_z_light_fog_prim(game->graph);
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 128, 255, 255, 255, 255);
        gSPLoadGeometryMode(NEXT_POLY_OPA_DISP,
                            G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH);

        if (shadow_flag) {
            gSPLoadGeometryMode(NEXT_POLY_OPA_DISP, G_ZBUFFER | G_CULL_BACK | G_FOG);
            gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 0, 0, 0, 0, 128);
            gDPSetRenderMode(NEXT_POLY_OPA_DISP,
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                                 G_RM_FOG_SHADE_A,
                             AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                                 GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
            gDPSetCombineLERP(NEXT_POLY_OPA_DISP, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                              PRIMITIVE);
        }

        cKF_Si3_draw_R_SV(game, &hand_ovl->info.keyframe, mtx, NULL, NULL, NULL);

        CLOSE_DISP(graph);
    }
}

static void mHD_hand_ovl_draw(Submenu* submenu, GAME* game) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    GRAPH* graph = game->graph;

    if (hand_ovl->info.type != 0) {
        f32 cos_x = cos_s(mHD_ROT_X);
        f32 sin_z = sin_s(mHD_ROT_Z);
        f32 cos_z = cos_s(mHD_ROT_Z);
        f32 target_pos[2];
        f32 pos[3];
        f32 pos_adj;
        mTG_tag_c* tag;

        /* Use visual_pos for rendering */
        target_pos[0] = (hand_ovl->info.visual_pos[0] + hand_ovl->info.ofs[0] * cos_z + 
                        hand_ovl->info.ofs[1] * (-cos_x * sin_z)) + 4.0f;
        target_pos[1] = (hand_ovl->info.visual_pos[1] + hand_ovl->info.ofs[0] * sin_z + 
                        hand_ovl->info.ofs[1] * (cos_x * cos_z)) - 4.0f;

        /* Draw hand shadow first */
        Matrix_push();
        submenu->overlay->change_view_proc(graph, 80.0f, 0.0f, ((target_pos[0] + 160.0f) - 4.0f - 12.0f) * 4.0f,
                                           (120.0f - target_pos[1] + 4.0f - 20.0f) * 4.0f, 0, 64, 64);
        mHD_hand_shape_draw(submenu, game, TRUE);
        submenu->overlay->setup_view_proc(submenu, graph, 0);
        Matrix_pull();

        tag = &submenu->overlay->tag_ovl->tags[0];
        target_pos[0] -= 2.5f;
        target_pos[1] += 2.5f;

        // is this an xyz_t?
        pos[0] = target_pos[0] + (cos_z * -6.9f + 7.0f * (-cos_x * sin_z));
        pos[1] = target_pos[1] + (sin_z * -6.9f + 7.0f * (cos_x * cos_z) - 10.0f);
        pos[2] = 0.0f;

        switch (tag->table) {
            case mTG_TABLE_CPMAIL:
            case mTG_TABLE_CPMAIL_WC:
            case mTG_TABLE_CPORIGINAL:
            case mTG_TABLE_CPORIGINAL_WC:
                if (hand_ovl->info.act == mHD_ACTION_SASU || hand_ovl->info.act == mHD_ACTION_SASU2) {
                    pos_adj = 1.0f;
                } else if (hand_ovl->info.act == mHD_ACTION_CLOSE2 ||
                           (hand_ovl->info.act == mHD_ACTION_OPEN &&
                            (tag->table == mTG_TABLE_CPMAIL_WC || tag->table == mTG_TABLE_CPORIGINAL_WC))) {
                    pos_adj = 1.0f - hand_ovl->info.keyframe.frame_control.current_frame /
                                         mHD_animeTable[mHD_ACTION_CLOSE].end_frame;
                } else {
                    pos_adj = 0.0f;
                }

                pos[0] += pos_adj * 5.0f;
                pos[1] += pos_adj * 15.0f;
                break;
        }

        /* Draw hand items next */
        mHD_draw_item(submenu, graph, pos);
        mHD_draw_mail(submenu, graph, pos);
        mHD_draw_original(submenu, graph, pos);

        /* Draw hand model last */
        Matrix_push();
        submenu->overlay->change_view_proc(graph, 80.0f, 0.0f, ((target_pos[0] + 160.0f) - 4.0f - 12.0f) * 4.0f,
                                           (120.0f - target_pos[1] + 4.0f - 20.0f) * 4.0f, 0, 64, 64);
        mHD_hand_shape_draw(submenu, game, FALSE);
        submenu->overlay->setup_view_proc(submenu, graph, 0);
        Matrix_pull();
    }
}

static void mHD_nop_hand_func(Submenu* submenu) {
    submenu->overlay->menu_control.hand_move_func = (mSM_HAND_MOVE_FUNC)&none_proc1;
    submenu->overlay->menu_control.hand_draw_func = (mSM_HAND_DRAW_FUNC)&none_proc1;
}

static void mHD_set_hand_func(Submenu* submenu) {
    submenu->overlay->menu_control.hand_move_func = &mHD_hand_ovl_move;
    submenu->overlay->menu_control.hand_draw_func = &mHD_hand_ovl_draw;
}

extern void mHD_hand_ovl_construct(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[submenu->menu_type];
    Submenu_Overlay_c* overlay = submenu->overlay;
    mHD_Ovl_c* hand_ovl;

    if (overlay->hand_ovl != NULL) {
        return;
    }

    mem_clear((u8*)&hand_ovl_data, sizeof(mHD_Ovl_c), 0);
    overlay->menu_control.hand_move_func = &mHD_hand_ovl_move;
    overlay->menu_control.hand_draw_func = &mHD_hand_ovl_draw;
    overlay->hand_ovl = &hand_ovl_data;

    submenu->overlay->hand_ovl->nop_hand_func = &mHD_nop_hand_func;
    submenu->overlay->hand_ovl->set_hand_func = &mHD_set_hand_func;
    hand_ovl = &hand_ovl_data;

    hand_ovl->info.type = 0;
    hand_ovl->info.move_flag = mHD_MOVE_NONE;
    mMl_clear_mail(&hand_ovl->info.mail);
    hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;

    hand_ovl->info.visual_pos[0] = 0.0f;
    hand_ovl->info.visual_pos[1] = 0.0f;
 
    if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_EXCHANGE) {
        mActor_name_t item;
        int item_cond;

        switch (menu_info->data1) {
            case ITM_PRESENT:
                item = mPr_DummyPresentToTruePresent();
                item_cond = mPr_ITEM_COND_PRESENT;
                break;
            case ITM_GOLDEN_NET_PRESENT:
                item = ITM_GOLDEN_NET;
                item_cond = mPr_ITEM_COND_PRESENT;
                break;
            case ITM_GOLDEN_AXE_PRESENT:
                item = ITM_GOLDEN_AXE;
                item_cond = mPr_ITEM_COND_PRESENT;
                break;
            case ITM_GOLDEN_SHOVEL_PRESENT:
                item = ITM_GOLDEN_SHOVEL;
                item_cond = mPr_ITEM_COND_PRESENT;
                break;
            case ITM_GOLDEN_ROD_PRESENT:
                item = ITM_GOLDEN_ROD;
                item_cond = mPr_ITEM_COND_PRESENT;
                break;
            default:
                item = (mActor_name_t)menu_info->data1;
                item_cond = hand_ovl->info.item_cond;
                break;
        }

        hand_ovl->info.item = item;
        hand_ovl->info.item_cond = item_cond;
        hand_ovl->info.act = mHD_ACTION_CLOSE_KEEP;
        hand_ovl->info.next_act = mHD_ACTION_CLOSE_KEEP;
    } else {
        hand_ovl->info.item = EMPTY_NO;
        hand_ovl->info.act = mHD_ACTION_SASU;
        hand_ovl->info.next_act = mHD_ACTION_SASU;
    }

    hand_ovl->info.ofs[0] = mHD_hand_offsetX_table[hand_ovl->info.act];
    hand_ovl->info.ofs[1] = mHD_hand_offsetY_table[hand_ovl->info.act];
    mHD_hand_shape_init(submenu);
    mHD_hand_shape_move(submenu);
    mHD_set_hand_func(submenu);
}

extern void mHD_hand_ovl_destruct(Submenu* submenu) {
    cKF_SkeletonInfo_R_dt(&submenu->overlay->hand_ovl->info.keyframe);
    mHD_nop_hand_func(submenu);
    submenu->overlay->hand_ovl = NULL;
}
