#include "m_mushroom.h"
#include "m_time.h"
#include "m_event.h"
#include "m_actor_type.h"
#include "m_field_make.h"
#include "m_field_info.h"
#include "m_scene_table.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_lib.h"
#include "libc64/qrand.h"

/* 'zero' time (uninitialized time value for mushroom saved time) */
static lbRTC_time_c l_mmsr_zeto_time = { 0, 0, 0, 0, 0, 0, 0 };

/**
 * @brief Converts a saved time in mMsr_time_c format into its lbRTC_time_c representation.
 *
 * @param dst The destination lbRTC_time_c
 * @param src The source mMsr_time_c
 **/
static void mMsr_Mushtime2Rtc(lbRTC_time_c* dst, mMsr_time_c* src) {
    dst->year = src->year;
    dst->month = src->month;
    dst->day = src->day;
    dst->hour = src->hour;
    dst->min = src->hour_quarter * 15;
    dst->sec = 0;
    dst->weekday = lbRTC_Week(dst->year, dst->month, dst->day);
}

/**
 * @brief Converts time in lbRTC_time_c format into its mMsr_time_c representation.
 *
 * @param dst The destination mMsr_time_c
 * @param src The source lbRTC_time_c
 **/
static void mMsr_Rtc2MushTime(mMsr_time_c* dst, lbRTC_time_c* src) {
    dst->year = src->year;
    dst->month = src->month;
    dst->day = src->day;
    dst->hour = src->hour;
    dst->hour_quarter = src->min / 15;
}

/**
 * @brief Gets whether or not the mushroom season event is currently active.
 *
 * @return TRUE when event is active, FALSE otherwise
 **/
static int mMsr_CheckMushroomDay() {
    return mEv_check_status(mEv_EVENT_MUSHROOM_SEASON, mEv_STATUS_ACTIVE) == TRUE;
}

/**
 * @brief Transforms a source lbRTC_time_c's minute member to the closest 15 minute margin in the future
 *
 * @param dst The destination 15-minute demarcated lbRTC_time_c
 * @param src The source lbRTC_time_c
 **/
static void mMsr_Set15Minites(lbRTC_time_c* dst, lbRTC_time_c* src) {
    static u8 min_15_table[4] = { 45, 30, 15, 0 };
    int i;

    lbRTC_TimeCopy(dst, src);
    for (i = 0; i < 4; i++) {
        if (dst->min >= min_15_table[i]) {
            dst->min = min_15_table[i];
            break;
        }
    }
}

/**
 * @brief Gets the initial amount of mushrooms which should be removed.
 *
 * The amount removed is determined by how many 15-minute intervals
 * have passed since 8 AM.
 *
 * @param rtc_time The current rtc time
 * @param mush_time The current mushroom 15-minute demarcated time
 *
 * @return Number of mushrooms to initially remove
 **/
static u32 mMsr_GetFirstClearMushroomNum(lbRTC_time_c* rtc_time, lbRTC_time_c* mush_time) {
    u32 mushroom_num = 0;
    lbRTC_time_c rtc_15_min;
    lbRTC_time_c mush_15_min;

    if (mTM_AreTimesEqual(rtc_time, mush_time) != TRUE) {
        mMsr_Set15Minites(&rtc_15_min, rtc_time);
        mMsr_Set15Minites(&mush_15_min, mush_time);

        if (lbRTC_IsOverTime(&mush_15_min, &rtc_15_min) == lbRTC_OVER) {
            mushroom_num = lbRTC_IntervalTime(&rtc_15_min, &mush_15_min);
        } else {
            mushroom_num = lbRTC_IntervalTime(&mush_15_min, &rtc_15_min);
        }

        mushroom_num /= 15;
    }

    return mushroom_num;
}

/**
 * @brief Gets the number of removeable mushrooms in an acre and tracks which locations they are at.
 *
 * Clearable mushrooms are mushrooms which are not buried.
 *
 * @param fg_block_items Pointer to the acre's item data
 * @param save_deposit Pointer to the acre's buried item flags
 * @param block_candidates Pointer to the table of saved mushroom locations
 *
 * @return Number of removeable mushrooms in the acre
 **/
static int mMsr_GetBlockClearAbleMushroomNum(mActor_name_t* fg_block_items, u16* save_deposit, u16* block_candidates) {
    int clearable = 0;
    if (fg_block_items != NULL && save_deposit != NULL && block_candidates != NULL) {
        int ut_z;
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            int ut_x;
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if (*fg_block_items == ITM_FOOD_MUSHROOM && mFI_GetLineDeposit(save_deposit, ut_x) == FALSE) {
                    clearable++;
                    *block_candidates |= 1 << ut_x;
                }

                fg_block_items++;
            }

            save_deposit++;
            block_candidates++;
        }
    }

    return clearable;
}

/**
 * @brief Splits up an amount of cleared mushrooms between all acres in town.
 *
 * @param share_num Pointer to the list of mushrooms to remove for each acre
 * @param candidate_num Pointer to the list of mushrooms present for removal in each acre
 * @param candidate_block_num Total number of acres with clearable mushroom candidates
 * @param total_clearable Total number of clearable mushrooms in town
 * @param clear_num Amount of mushrooms to clear
 **/
static void mMsr_SetShareNum(u8* share_num, u8* candidate_num, int candidate_block_num, int total_clearable,
                             int clear_num) {
    u8* share_num_p = share_num;
    u8* candidate_num_p = candidate_num;
    int clearable;
    int i;

    /* count clearable mushrooms and log which acres */
    while (total_clearable != 0 && candidate_block_num != 0 && clear_num > candidate_block_num) {
        share_num = share_num_p;
        candidate_num = candidate_num_p;
        clearable = 0;
        for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
            if (*candidate_num - *share_num > 0) {
                clearable++;
                (*share_num)++;
                if (*candidate_num <= *share_num) {
                    candidate_block_num--; // acre doesn't have enough mushrooms in it, so remove it from the count
                }
            }

            share_num++;
            candidate_num++;
        }

        if (clearable == 0) {
            break; // no clearable mushrooms left
        }

        clear_num -= clearable;
        total_clearable -= clearable;
    }

    /* try to assign share for any cleared mushrooms left */
    while (clear_num != 0 && candidate_block_num != 0 && total_clearable != 0) {
        int selected_block;

        share_num = share_num_p;
        candidate_num = candidate_num_p;
        selected_block = (int)(fqrand() * candidate_block_num); // randomly selected acre

        for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
            if (*candidate_num - *share_num > 0) {
                if (selected_block == 0) {
                    clear_num--;
                    (*share_num)++;
                    total_clearable--;
                    if (*candidate_num <= *share_num) {
                        candidate_block_num--;
                    }
                    break;
                }

                selected_block--;
            }

            share_num++;
            candidate_num++;
        }
    }
}

/**
 * @brief Removes candidate mushrooms in an acre.
 *
 * @param fg_items Pointer to acre items
 * @param candidates Pointer to mushroom removal candidate location bitfield for the acre
 **/
static void mMsr_ClearBlockCandidateMushroom(mActor_name_t* fg_items, u16* candidates) {
    int ut_z;
    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        int ut_x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            /* check if the 'candidate' bit is set for our x unit */
            if ((((*candidates) >> ut_x) & 1) == 1) {
                *fg_items = EMPTY_NO; // clear item
                mFI_SetFGUpData();
            }

            fg_items++;
        }

        candidates++;
    }
}

/**
 * @brief Removes all candidate mushrooms from all acres
 *
 * @param fg Pointer to all acres' item data
 * @param candidates Pointer to mushroom removal candidate location bitfields
 * @param candidate_num Pointer to mushroom candidate number list
 **/
static void mMsr_ClearCandidateMushroom(mFM_fg_c* fg, u16* candidates, u8* candidate_num) {
    int i;

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        if (*candidate_num != 0) {
            mMsr_ClearBlockCandidateMushroom((mActor_name_t*)fg->items, candidates);
        }

        fg++;
        candidates += UT_Z_NUM;
        candidate_num++;
    }
}

/**
 * @brief Clears a set number of mushrooms around town while ignoring the acre the player is in.
 *
 * @param clear_num Number of mushrooms to clear
 * @param block_x The X-acre the player is currently in
 * @param block_z The Z-acre the player is currently in
 **/
static void mMsr_ClearMushrooms(int clear_num, int block_x, int block_z) {
    static u16 candidate[FG_BLOCK_TOTAL_NUM][UT_Z_NUM];
    static u8 candidate_num[FG_BLOCK_TOTAL_NUM];
    static u8 share_num[FG_BLOCK_TOTAL_NUM];

    mFM_fg_c* fg_block;
    int candidate_blocks = 0;
    int total_candidate_num = 0;
    int i;

    fg_block = (mFM_fg_c*)Save_Get(fg);
    bzero(candidate, FG_BLOCK_TOTAL_NUM * UT_Z_NUM * sizeof(u16));
    bzero(candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));
    bzero(share_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        int clearable_num =
            mMsr_GetBlockClearAbleMushroomNum((mActor_name_t*)fg_block->items, Save_Get(deposit[i]), candidate[i]);
        candidate_num[i] = clearable_num;
        if (candidate_num[i] != 0) {
            total_candidate_num += candidate_num[i];
            candidate_blocks++;
        }
        fg_block++;
    }

    if ((block_x - 1) >= 0 && (block_x - 1) < FG_BLOCK_X_NUM && (block_z - 1) >= 0 && (block_z - 1) < FG_BLOCK_Z_NUM) {
        u8 candidate_amt;

        int bx = (block_z - 1) * FG_BLOCK_X_NUM + (block_x - 1);
        candidate_amt = candidate_num[bx];
        if (candidate_num[bx] != 0) {
            candidate_num[bx] = 0;
            total_candidate_num -= candidate_amt;
            candidate_blocks--;
            bzero(candidate[bx], UT_Z_NUM * sizeof(u16));
        }
    }

    if (total_candidate_num > 0) {
        if (total_candidate_num < clear_num) {
            fg_block = (mFM_fg_c*)Save_Get(fg);
            mMsr_ClearCandidateMushroom(fg_block, (u16*)candidate, candidate_num);
        } else {
            mMsr_SetShareNum(share_num, candidate_num, candidate_blocks, total_candidate_num, clear_num);
            fg_block = (mFM_fg_c*)Save_Get(fg);
            for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
                if (share_num[i] != 0) {
                    int cleared = mFI_ClearBlockItemRandom_common(
                        ITM_FOOD_MUSHROOM, share_num[i], (mActor_name_t*)fg_block->items, Save_Get(deposit[i]), FALSE);
                    if (cleared > 0) {
                        mFI_SetFGUpData();
                    }
                }

                fg_block++;
            }
        }
    }
}

/**
 * @brief Clears mushrooms upon first load.
 *
 * This funciton is necessary to remove the already missed mushrooms
 * if there are any.
 **/
extern void mMsr_FirstClearMushroom() {
    int first_clear_num;
    lbRTC_time_c mush_rtc_time;
    mMsr_time_c* mush_time = Save_GetPointer(mushroom_time);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    mMsr_Mushtime2Rtc(&mush_rtc_time, mush_time);
    if (lbRTC_IsEqualTime(&mush_rtc_time, &l_mmsr_zeto_time, lbRTC_CHECK_ALL & ~lbRTC_CHECK_WEEKDAYS) == TRUE) {
        lbRTC_TimeCopy(&mush_rtc_time, rtc_time);
    }

    first_clear_num = mMsr_GetFirstClearMushroomNum(rtc_time, &mush_rtc_time);
    if (first_clear_num > 0) {
        mMsr_ClearMushrooms(first_clear_num, 0, 0);
    }

    if (lbRTC_IsEqualTime(&mush_rtc_time, rtc_time, lbRTC_CHECK_DAYS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS) ==
        FALSE) {
        mush_time->active = TRUE;
    }

    mMsr_Rtc2MushTime(mush_time, rtc_time);
}

/**
 * @brief Gets number of mushrooms that should be placed
 *
 * @param mush_time Pointer to the next mushroom update time
 * @param rtc_time Pointer to the current RTC time
 * @param active Flag that force-controls whether mushrooms should be placed or not
 *
 **/
static int mMsr_GetMushroomNum(const lbRTC_time_c* mush_time, const lbRTC_time_c* rtc_time, u8 active) {
    int mushroom_num = 0;
    if (active == TRUE ||
        lbRTC_IsEqualTime(rtc_time, mush_time, lbRTC_CHECK_DAYS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS) == FALSE) {
        if (rtc_time->hour == mMsr_ACTIVE_HOUR) {
            mushroom_num = mMsr_NUM_MUSHROOMS - rtc_time->min / 15;
        } else if (rtc_time->hour == (mMsr_ACTIVE_HOUR + 1) && rtc_time->min < 15) {
            mushroom_num = mMsr_NUM_MUSHROOMS - 4; // 1 mushroom until 9:15 am
        }
    }

    return mushroom_num;
}

/**
 * @brief Gets whether an item is a valid tree and if that tree has space for a mushroom around it.
 *
 * Valid trees are:
 *  - Trees (not ones with hidden objects)
 *  - Cedar trees (not ones with hidden objects)
 *  - Fruit trees that currently have fruit
 *  - Golden trees (including with golden shovel on them)
 *  - Player-grown money trees (all denominations)
 *
 * Spot check map (x = valid spot, T = tree):
 *  xTx
 *  xxx
 *
 * @param item Pointer to the item to check
 * @param ut_x The X unit of the item
 * @param ut_z The Z unit of the item
 *
 * @return TRUE when item is a valid tree with a valid spot, FALSE otherwise
 **/
static int mMsr_CheckAroundTree(mActor_name_t* item, u8 ut_x, u8 ut_z) {
    static int area_table[5] = {
        -1, /* xT-  1 left of tree */
            /* --- */
        1,  /* -Tx  1 right of tree */
        /* --- */
        15, /* -T-  1 below, 1 left of tree */
        /* x-- */
        16, /* -T-  1 below of tree */
        /* -x- */
        17 /* -T-  1 below, 1 right of tree */
           /* --x */
    };

    int* area_p = area_table;
    int res = FALSE;
    if (ut_x < (UT_X_NUM - 1) && ut_z < (UT_Z_NUM - 1)) {
        mActor_name_t item_no = *item;
        if (item_no == TREE || item_no == TREE_APPLE_FRUIT || item_no == TREE_ORANGE_FRUIT ||
            item_no == TREE_PEACH_FRUIT || item_no == TREE_PEAR_FRUIT || item_no == TREE_CHERRY_FRUIT ||
            item_no == TREE_1000BELLS || item_no == TREE_10000BELLS || item_no == TREE_30000BELLS ||
            item_no == TREE_100BELLS || item_no == TREE_PALM_FRUIT || item_no == CEDAR_TREE || item_no == GOLD_TREE ||
            item_no == GOLD_TREE_SHOVEL) {
            int i;

            for (i = 0; i < 5; i++) {
                if (*(item + *area_p) == EMPTY_NO) {
                    res = TRUE;
                    break;
                }
                area_p++;
            }
        }
    }

    return res;
}

/**
 * @brief Counts all the valid mushroom trees in an acre.
 *
 * @param item_p Pointer to the acre items
 *
 * @return Number of valid mushroom trees in the acre
 **/
static u8 mMsr_GetBlockSetAbleMushroomTreeNum(mActor_name_t* item_p) {
    u8 num = 0;
    u8 ut_z;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        u8 ut_x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (mMsr_CheckAroundTree(item_p, ut_x, ut_z) == TRUE) {
                num++;
            }
            item_p++;
        }
    }

    return num;
}

/**
 * @brief Sets a mushroom at a random valid spot under a tree.
 *
 * @param item_p Pointer to the tree item
 **/
static void mMsr_SetMushroomAroundTree(mActor_name_t* item_p) {
    static int area_table[5] = {
        -1, /* xT-  1 left of tree */
            /* --- */
        1,  /* -Tx  1 right of tree */
        /* --- */
        15, /* -T-  1 below, 1 left of tree */
        /* x-- */
        16, /* -T-  1 below of tree */
        /* -x- */
        17 /* -T-  1 below, 1 right of tree */
           /* --x */
    };

    int empty_space_num = 0;
    int i;

    for (i = 0; i < 5; i++) {
        if (*(item_p + area_table[i]) == EMPTY_NO) {
            empty_space_num++;
        }
    }

    if (empty_space_num > 0) {
        int selected = (int)(fqrand() * empty_space_num);

        for (i = 0; i < 5; i++) {
            if (*(item_p + area_table[i]) == EMPTY_NO) {
                if (selected <= 0) {
                    *(item_p + area_table[i]) = ITM_FOOD_MUSHROOM;
                    return;
                }
                selected--;
            }
        }
    }
}

/**
 * @brief Sets a mushroom randomly under N trees in an acre.
 *
 * @param fg_items Pointer to the acre items
 * @param block_x Number of candidate trees in the acre
 **/
static void mMsr_SetBlockMashroom(mActor_name_t* fg_items, u8 candidate_num) {
    int selected_num = (int)(fqrand() * candidate_num);
    u8 ut_z;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        u8 ut_x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (mMsr_CheckAroundTree(fg_items, ut_x, ut_z) == TRUE) {
                if (selected_num <= 0) {
                    mMsr_SetMushroomAroundTree(fg_items);
                    ut_z = UT_Z_NUM; /* break out by exceeding first loop case... bruh */
                    break;
                }

                selected_num--;
            }

            fg_items++;
        }
    }
}

/**
 * @brief Places all requested mushrooms in an acre column (A->F)
 *
 * @param fg_block_col Pointer to the town mFM_fg_c data
 * @param candidate_num Pointer to the list containing number of candidate trees per acre
 **/
static void mMsr_SetLineMushroom(mFM_fg_c* fg_block_col, u8* candidate_num) {
    u8* t_cand_num = candidate_num;
    int candidate_rows = 0;
    int bz;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        if (*candidate_num != 0) {
            candidate_rows++;
        }

        candidate_num += FG_BLOCK_X_NUM;
    }

    if (candidate_rows > 0) {
        int selected_z = (int)(fqrand() * candidate_rows);
        candidate_num = t_cand_num;
        for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
            if (*candidate_num != 0) {
                if (selected_z <= 0) {
                    mMsr_SetBlockMashroom((mActor_name_t*)fg_block_col->items, *candidate_num);
                    break;
                }
                selected_z--;
            }

            /* Check next Z row */
            candidate_num += FG_BLOCK_X_NUM;
            fg_block_col += FG_BLOCK_X_NUM;
        }
    }
}

/**
 * @brief Places N mushrooms around town, ignoring the acre the player is currently in.
 *
 * @param mushroom_num Number of mushrooms to place
 * @param player_bx The X-acre the player is currently in
 * @param player_bz The Z-acre the player is currently in
 **/
static void mMsr_SetMushroomNum(int mushroom_num, int player_bx, int player_bz) {
    static u8 candidate_num[FG_BLOCK_TOTAL_NUM];

    mFM_fg_c* fg_block = (mFM_fg_c*)Save_Get(fg);
    u8* candidate_p = candidate_num;
    u8 possible_col_bitfield = 0;
    int possible_cols = 0;
    int bz;
    int bx;

    bzero(candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));

    /* Check all acres for candidate mushroom locations */
    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            /* ensure we do not spawn a mushroom in the acre the player is currently in */
            if (bx != player_bx - 1 && bz != player_bz - 1) {
                *candidate_p = mMsr_GetBlockSetAbleMushroomTreeNum((mActor_name_t*)fg_block->items);
                if (*candidate_p != 0 && ((possible_col_bitfield >> bx) & 1) == 0) {
                    possible_cols++;
                    possible_col_bitfield |= 1 << bx;
                }
            }

            fg_block++;
            candidate_p++;
        }
    }

    if (possible_cols > 0) {
        for (mushroom_num; mushroom_num != 0; mushroom_num--) {
            int selected;
            fg_block = (mFM_fg_c*)Save_Get(fg);
            candidate_p = candidate_num;

            /* if we've run out of X cols to place mushrooms in, look again */
            if (possible_cols == 0) {
                possible_col_bitfield = 0;
                possible_cols = 0;
                for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                    candidate_p = candidate_num + bx;
                    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
                        if (*candidate_p != 0) {
                            possible_cols++;
                            possible_col_bitfield |= 1 << bx;
                            break;
                        }
                        candidate_p += FG_BLOCK_X_NUM; /* move onto next Z row */
                    }
                }

                candidate_p = candidate_num;
                if (possible_cols == 0) {
                    break; /* no possible locations left */
                }
            }

            /* randomly select one of the possible X columns */
            selected = (int)(fqrand() * possible_cols);

            for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                u8 bit = possible_col_bitfield >> bx;
                if ((bit & 1) == 1) {
                    if (selected <= 0) {
                        mMsr_SetLineMushroom(fg_block, candidate_p); /* set mushroom on our X column */
                        break;
                    }

                    selected--;
                }

                /* move onto next X column */
                fg_block++;
                candidate_p++;
            }
        }
    }
}

/**
 * @brief Places or removes mushrooms around town based on game state.
 *
 * For mushrooms to be placed/cleared:
 *  - Field data must be ready.
 *  - Scene must be outside in town.
 *  - Field type must be FG (outside).
 *  - 'MushroomDay' must be an active event.
 *  - Mushrooms are placed if mMsr_GetMushroomNum is non-zero, otherwise they're cleared.
 *
 * @param mushroom_num player_pos Current world position of the player
 **/
extern void mMsr_SetMushroom(xyz_t player_pos) {
    int player_bx, player_bz;
    lbRTC_time_c mush_rtc;
    mMsr_time_c* mush_time = Save_GetPointer(mushroom_time);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    mMsr_Mushtime2Rtc(&mush_rtc, mush_time);
    if (mTM_AreTimesEqual(&mush_rtc, &l_mmsr_zeto_time) == TRUE) {
        /* mushroom time is not initialized, so initialize it to yesterday */
        lbRTC_TimeCopy(&mush_rtc, rtc_time);
        lbRTC_Sub_DD(&mush_rtc, 1);
    }

    mFI_Wpos2BlockNum(&player_bx, &player_bz, player_pos);
    if (mFI_CheckFieldData() == TRUE) {
        mActor_name_t field_id = mFI_GetFieldId();

        if (Save_Get(scene_no) == SCENE_FG && mFI_GET_TYPE(field_id) == mFI_FIELDTYPE_FG &&
            mMsr_CheckMushroomDay() == TRUE) {
            int mushroom_num = mMsr_GetMushroomNum(&mush_rtc, rtc_time, mush_time->active);
            if (mushroom_num > 0 && mushroom_num <= mMsr_NUM_MUSHROOMS) {
                mMsr_SetMushroomNum(mushroom_num, player_bx, player_bz);
                mMsr_Rtc2MushTime(mush_time, rtc_time);
                mush_time->active = FALSE;
            } else {
                int clear_num = mMsr_GetFirstClearMushroomNum(rtc_time, &mush_rtc);
                if (clear_num > 0) {
                    mMsr_ClearMushrooms(clear_num, player_bx, player_bz);
                    if (mush_time->active != TRUE &&
                        lbRTC_IsEqualTime(&mush_rtc, rtc_time,
                                          lbRTC_CHECK_DAYS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS) == FALSE) {
                        mush_time->active = TRUE;
                    }

                    mMsr_Rtc2MushTime(mush_time, rtc_time);
                }
            }
        }
    }
}
