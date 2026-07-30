#include "m_field_assessment.h"
#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_all_grow.h"
#include "libultra/libultra.h"

static int l_good_block_num = 0;
static int l_field_assessment_rank = 0;

static u8 l_block_rank_tree_num[mFAs_TREE_RANK_COUNT] = { 8, 11, 14, 17, 255 };
static u8 l_block_rank_table[mFAs_TREE_RANK_COUNT] = { 0, 1, 2, 1, 0 };
static u8 l_block_max_by_rank[mFAs_FIELDRANK_NUM] = { 0, 2, 4, 7, 12, 16, 255 };
static int l_mfas_romf_check[5] = { 0, 0, 0, 0, 0 };

static void mFAs_ClearGoodField_common(mFAs_GoodField_c* good_field) {
    lbRTC_TimeCopy(&good_field->renew_time, &mTM_rtcTime_clear_code);
    good_field->perfect_day_streak = 0;
}

extern void mFAs_ClearGoodField() {
    mFAs_ClearGoodField_common(Save_GetPointer(good_field));
}

extern int mFAs_CheckGoodField() {
    int res = FALSE;
    if (Save_Get(good_field.perfect_day_streak) >= mFAs_PERFECT_DAY_STREAK_MAX) {
        res = TRUE;
    }

    return res;
}

static void mFAs_SetGoodField(int rank) {
    mFAs_GoodField_c* good_field = Save_GetPointer(good_field);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    if (rank == mFAs_FIELDRANK_SIX) {
        if (mTM_AreTimesEqual(&mTM_rtcTime_clear_code, &good_field->renew_time) == TRUE) {
            lbRTC_TimeCopy(&good_field->renew_time, rtc_time);
            good_field->perfect_day_streak = 0;
        } else {
            if (lbRTC_IsOverTime(&good_field->renew_time, rtc_time) == lbRTC_OVER) {
                int day_interval = lbRTC_GetIntervalDays(&good_field->renew_time, rtc_time);
                if (day_interval > 0) {
                    lbRTC_TimeCopy(&good_field->renew_time, rtc_time);
                    if (good_field->perfect_day_streak + day_interval > mFAs_PERFECT_DAY_STREAK_MAX) {
                        good_field->perfect_day_streak = mFAs_PERFECT_DAY_STREAK_MAX;
                    } else {
                        good_field->perfect_day_streak += day_interval;
                    }
                }
            } else {
                lbRTC_TimeCopy(&good_field->renew_time, rtc_time);
                good_field->perfect_day_streak = 0;
            }
        }
    } else {
        mFAs_ClearGoodField_common(good_field);
    }
}

static int mFAs_GetIdx(u8* points_by_rank, u8 total_points, int ranks_count) {
    int res = -1;
    int i;

    for (i = 0; i < ranks_count; i++) {
        if (total_points <= *points_by_rank) {
            res = i;
            break;
        }

        points_by_rank++;
    }

    return res;
}

static int mFAs_CheckDust(mActor_name_t item) {
    int res = FALSE;

    if (item == ITM_DUST0_EMPTY_CAN || item == ITM_DUST1_BOOT || item == ITM_DUST2_OLD_TIRE) {
        res = TRUE;
    }

    return res;
}

static int mFAs_GetBlockTreeNum2(int* tree_num,              /* trees */
                                 int* flower_num,            /* flowers */
                                 int* effective_grass_num,   /* weeds - flowers */
                                 int* total_grass_num,       /* weeds */
                                 int* dust_num,              /* trash not in dump */
                                 mFI_unit_c* dump_unit_info, /* dump location */
                                 mActor_name_t* block_items, /* items in acre */
                                 int block_item_count        /* item count */
) {
    int trees;
    int i;

    trees = 0;
    for (i = 0; i < block_item_count; i++) {
        mActor_name_t item = *block_items;
        if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM0) {
            int category = ITEM_NAME_GET_CAT(item);
            if (category == ENV_CATEGORY) {
                if (IS_ITEM_FLOWER(item)) {
                    (*flower_num)++;
                } else if (IS_ITEM_TREE(item)) {
                    trees++;
                }
            } else if (category == BG_CATEGORY) {
                if (IS_ITEM_GRASS(item)) {
                    (*effective_grass_num)++;
                }
                // IS_ITEM_GROWN_TREE is unnecessary here, as the majority of the conditional checks are impossible
                // They should've just checked the special trees that live in the "BG" range
                else if (IS_ITEM_GROWN_TREE(item)) {
                    trees++;
                }
            }
        } else if (mFAs_CheckDust(item) == TRUE) {
            int ut_x = i & 15;
            int ut_z = (i >> 4) & 15;

            if ((dump_unit_info == NULL) || (dump_unit_info->block_data == NULL) ||
                (dump_unit_info->unit_x < ut_x || dump_unit_info->unit_x - mAGrw_DUMP_WIDTH > ut_x) ||
                (dump_unit_info->unit_z < ut_z || dump_unit_info->unit_z - mAGrw_DUMP_HEIGHT > ut_z)) {
                (*dust_num)++; /* trash outside of dump */
            }
        }

        block_items++;
    }

    *tree_num = trees;
    *total_grass_num = *effective_grass_num;
    *effective_grass_num -= *flower_num; /* offset weeds by number of flowers */
    return trees;
}

/* int tree_num, int grass_num */
typedef int (*mFAs_CheckProc)(int, int);

static int mFAs_CheckDustOver(int tree_num, int grass_num) {
    return FALSE;
}

static int mFAs_CheckTreeLess(int tree_num, int grass_num) {
    return tree_num <= l_block_rank_tree_num[0];
}

static int mFAs_CheckTreeOver(int tree_num, int grass_num) {
    return tree_num >= l_block_rank_tree_num[3];
}

static int mFAs_CheckGrassOver(int tree_num, int grass_num) {
    return grass_num >= mFAs_GRASS_OVER_NUM;
}

static int mFAs_CheckNoCase(int tree_num, int grass_num) {
    return FALSE;
}

static int mFAs_CheckCondition(int* condition_num, int tree_num, int grass_num) {
    static mFAs_CheckProc bk_chk[mFAs_CONDITION_NUM] = { &mFAs_CheckDustOver, &mFAs_CheckTreeLess, &mFAs_CheckTreeOver,
                                                         &mFAs_CheckGrassOver, &mFAs_CheckNoCase };

    int check;

    for (check = 0; check <= *condition_num; check++) {
        if ((*bk_chk[check])(tree_num, grass_num) == TRUE) {
            return check; /* current mFAs_CONDITION_* exists */
        }
    }

    return -1; /* no issue */
}

static int mFAs_CheckBlockNum(int* block_num, int block_x, int block_z, int failed_condition) {
    int res = TRUE;

    /* check if the failed condition is within a non-excluded acre */
    if (block_num != NULL && failed_condition <= mFAs_CONDITION_TREE_OVER) {
        if (block_z == FG_BLOCK_Z_NUM) {
            res = FALSE;
        } else {
            int x;
            for (x = 0; x < mFAs_FG_BLOCK_EXCLUDE_NUM; x++) {
                if (block_x == block_num[0] && block_z == block_num[1]) {
                    res = FALSE;
                    break;
                }

                block_num += 2;
            }
        }
    }

    return res;
}

/* TODO: @fake match */
static int mFAs_GetFieldGoodBlockNum_common(int* condition_num, int* block_x, int* block_z, int* block_num) {
    mFI_unit_c dump_unit;
    int set_bad_block;
    mFM_fg_c* fg_block_items;
    int bx;
    int bz;
    int perfect_block_num;
    int good_blocks;
    int condition_result;
    int flower_num;
    int block_dust_num;
    int dust_num;
    int i;
    int selected_block_x;
    int selected_block_z;
    int tree_num;
    int grass_num;
    int effective_grass_num;
    int total_trees;
    int total_flowers;
    int total_grass;
    int rank;
    int good_block_num;
    mFI_unit_c* dump_info;
    int trees;

    set_bad_block = 0;
    tree_num = 0;
    grass_num = 0;
    effective_grass_num = 0;
    dump_unit.block_data = NULL;
    dump_info = NULL;
    perfect_block_num = 0;
    good_blocks = 0;
    dust_num = 0;
    selected_block_x = 0;
    selected_block_z = 0;
    total_trees = 0;
    total_flowers = 0;
    total_grass = 0;
    fg_block_items = &Save_Get(fg[0][0]);

    if (mFI_CheckFieldData()) {
        mAGrw_SearchDump(&dump_unit);
    }

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        bx = 1 + (i % 5);
        bz = 1 + (i / 5);
        block_dust_num = 0;
        tree_num = 0;
        effective_grass_num = 0;
        grass_num = 0;
        flower_num = 0;

        if (dump_unit.block_data != NULL && dump_unit.block_x == bx && dump_unit.block_z == bz) {
            dump_info = &dump_unit;
        } else {
            dump_info = NULL;
        }

        trees = mFAs_GetBlockTreeNum2(&tree_num, &flower_num, &effective_grass_num, &grass_num, &block_dust_num,
                                      dump_info, (mActor_name_t*)fg_block_items->items, UT_TOTAL_NUM);
        dust_num += block_dust_num;

        if (condition_num != NULL) {
            condition_result = mFAs_CheckCondition(condition_num, tree_num, effective_grass_num);
            if (condition_result != mFAs_CONDITION_NONE &&
                mFAs_CheckBlockNum(block_num, bx, bz, condition_result) == TRUE) {
                if (condition_result != *condition_num) {
                    *condition_num = condition_result;
                    condition_result = 1;
                } else {
                    condition_result = (fqrand() * 3.0f);
                }

                if (condition_result == 1 && block_x != NULL && block_z != NULL) {
                    *block_x = bx;
                    *block_z = bz;
                }
            }
        }

        if (block_dust_num != 0) {
            // bug here? this only executes when the value is not FALSE, but value is only
            // updated within the if statement block.
            if (set_bad_block == FALSE) {
                selected_block_x = bx;
                selected_block_z = bz;

#ifdef BUGFIXES
                set_bad_block = TRUE;
#endif
            } else {
                if (RANDOM(3) == 1) {
                    selected_block_x = bx;
                    selected_block_z = bz;
                }
#ifndef BUGFIXES
                set_bad_block = TRUE;
#endif
            }

            rank = 0;
        } else {
            if (effective_grass_num >= 3) {
                rank = 0; /* 0 points if there are 3 or more weeds in a single acre */
            } else {
                rank = l_block_rank_table[mFAs_GetIdx(l_block_rank_tree_num, trees, mFAs_TREE_RANK_COUNT)];
            }
        }

        if (rank == 2) {
            perfect_block_num++;
        } else if (rank == 1) {
            good_blocks++;
        }

        total_trees += tree_num;
        total_flowers += flower_num;
        total_grass += grass_num;
        fg_block_items++;
    }

    l_mfas_romf_check[0] = good_blocks;
    l_mfas_romf_check[1] = FG_BLOCK_TOTAL_NUM - (good_blocks + perfect_block_num); /* "bad" block count */
    l_mfas_romf_check[2] = total_trees;
    l_mfas_romf_check[3] = total_flowers;
    l_mfas_romf_check[4] = total_grass;
    perfect_block_num += good_blocks / 2;

    if (dust_num >= mFAs_DUST_OVER_NUM) {
        perfect_block_num = 0;
        Save_Set(dust_flag, TRUE);
        if (condition_num != NULL) {
            *condition_num = mFAs_CONDITION_DUST_OVER;
        }

        if (block_x != NULL && block_z != NULL) {
            *block_x = selected_block_x;
            *block_z = selected_block_z;
        }
    }

    if (condition_num != NULL && *condition_num != mFAs_CONDITION_NO_CASE) {
        mFAs_ClearGoodField(); /* reset perfect town streak */
    }

    return perfect_block_num;
}

static int mFAs_GetFieldGoodBlockNum() {
    int block_x = 0;
    int block_z = 0;

    return mFAs_GetFieldGoodBlockNum_common(NULL, &block_x, &block_z, NULL);
}

static int mFAs_GetFieldRankbyFGoodBlock(u8 good_block_num) {
    return mFAs_GetIdx(l_block_max_by_rank, good_block_num, mFAs_FIELDRANK_NUM);
}

/* TODO: @fake match */
static int mFAs_GetDustNum(int* block_x, int* block_z) {
    int set_bad_block;
    mFM_fg_c* fg_block_items;
    mActor_name_t* items;
    int dust_num;
    int block_dust_num;
    int bz, bx;
    int ut_z, ut_x;
    int dump_ut_z, dump_ut_x;
    int i;
    mFI_unit_c dump_unit;

    dust_num = 0;
    set_bad_block = FALSE;
    dump_unit.block_data = NULL;
    fg_block_items = Save_GetPointer(fg[0][0]);

    if (mFI_CheckFieldData()) {
/* @BUG - this method is broken when used during initial loading.
 *
 * The fdinfo structure still contains the info for the start demo scene,
 * and thus cannot return the proper block info for the dump. It fails in
 * mFI_BlockCheck.
 */
#ifndef BUGFIXES
        mAGrw_SearchDump(&dump_unit);
#else
        if (mFI_BlockKind2BkNum(&dump_unit.block_x, &dump_unit.block_z, mRF_BLOCKKIND_DUMP)) {
            mActor_name_t* dump_fg_p = Save_Get(fg[dump_unit.block_z - 1][dump_unit.block_x - 1]).items[0];
            int j;

            for (j = 0; j < UT_TOTAL_NUM; j++) {
                if (dump_fg_p[j] == DUMP) {
                    dump_unit.unit_x = j % UT_X_NUM;
                    dump_unit.unit_z = j / UT_X_NUM;
                    dump_unit.block_data = dump_fg_p;

                    break;
                }
            }
        }
#endif
    }

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            block_dust_num = 0;

            if (fg_block_items != NULL) {
                items = (mActor_name_t*)fg_block_items->items;
                if (dump_unit.block_data != NULL && bx + 1 == dump_unit.block_x && bz + 1 == dump_unit.block_z) {
                    // we're in the dump acre so check if the trash is in the dump bounds
                    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                            dump_ut_z = dump_unit.unit_z;
                            // surely the variable assignment within the if condition is wrong?
                            if ((ut_z < (dump_ut_z - mAGrw_DUMP_HEIGHT) || (ut_z > dump_ut_z)) ||
                                ((dump_ut_x = dump_unit.unit_x), ut_x < (dump_ut_x - mAGrw_DUMP_WIDTH)) ||
                                (ut_x > dump_ut_x)) {
                                if (mFAs_CheckDust(*items) == TRUE) {
                                    dust_num++;
                                    block_dust_num++;
                                }
                            }
                            items++;
                        }
                    }
                } else {
                    for (ut_z = 0; ut_z < UT_TOTAL_NUM; ut_z++) {
                        if (mFAs_CheckDust(*items) == TRUE) {
                            dust_num++;
                            block_dust_num++;
                        }
                        items++;
                    }
                }
            }

            if (block_dust_num != 0) {
                if (!set_bad_block) {
                    *block_x = bx + 1;
                    *block_z = bz + 1;

#ifdef BUGFIXES
                    set_bad_block = TRUE;
#endif
                } else {
                    if (RANDOM(3) == 1) {
                        *block_x = bx + 1;
                        *block_z = bz + 1;
                    }

#ifndef BUGFIXES
                    set_bad_block = TRUE;
#endif
                }
            }

            fg_block_items++;
        }
    }

    return dust_num;
}

extern int mFAs_GetFieldRank_Condition(int* rank, int* block_x, int* block_z) {
    static u32 block_kind[mFAs_FG_BLOCK_EXCLUDE_NUM] = { mRF_BLOCKKIND_SHRINE, mRF_BLOCKKIND_POOL,
                                                         mRF_BLOCKKIND_STATION, mRF_BLOCKKIND_PLAYER,
                                                         mRF_BLOCKKIND_MUSEUM };

    int block_pos_tbl[2 * mFAs_FG_BLOCK_EXCLUDE_NUM];
    int condition = mFAs_CONDITION_NO_CASE;

    *block_x = 0;
    *block_z = 0;
    bzero(block_pos_tbl, 2 * mFAs_FG_BLOCK_EXCLUDE_NUM * sizeof(int));
    mFI_GetSpecialBlockNum(block_pos_tbl, block_kind, mFAs_FG_BLOCK_EXCLUDE_NUM);

    if (Save_Get(dust_flag) == TRUE) {
        if (mFAs_GetDustNum(block_x, block_z) == FALSE) {
            Save_Set(dust_flag, FALSE);
        } else {
            condition = mFAs_CONDITION_DUST_OVER; // trash still exists in acre
        }

        l_good_block_num = 0;
    }

    if (Save_Get(dust_flag) == FALSE) {
        l_good_block_num = mFAs_GetFieldGoodBlockNum_common(&condition, block_x, block_z, block_pos_tbl);
    }

    l_field_assessment_rank = mFAs_GetFieldRankbyFGoodBlock(l_good_block_num);
    *rank = l_field_assessment_rank;
    mFAs_SetGoodField(l_field_assessment_rank);
    return condition;
}

extern void mFAs_SetFieldRank() {
    int bx, bz;
    if (Save_Get(dust_flag) == TRUE) {
        if (mFAs_GetDustNum(&bx, &bz) == FALSE) {
            Save_Set(dust_flag, FALSE);
        }

        l_good_block_num = 0;
    }

    if (Save_Get(dust_flag) == FALSE) {
        l_good_block_num = mFAs_GetFieldGoodBlockNum();
    }

    l_field_assessment_rank = mFAs_GetFieldRankbyFGoodBlock(l_good_block_num);
    mFAs_SetGoodField(l_field_assessment_rank);
}

extern int mFAs_GetFieldRank() {
    return l_field_assessment_rank;
}

extern void mFAs_PrintFieldAssessment(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 240, 50, 150, 255);
    gfxprint_locate8x8(gfxprint, 3, 14);
    gfxprint_printf(gfxprint, "%04d %04d %04d", l_mfas_romf_check[2], l_mfas_romf_check[3],
                    l_mfas_romf_check[4]); /* total trees, total flowers, total weeds(grass) */
    gfxprint_locate8x8(gfxprint, 3, 15);
    gfxprint_printf(gfxprint, " %02d %02d %02d", l_good_block_num, l_mfas_romf_check[0],
                    l_mfas_romf_check[1]); /* total good acres, 'ok' acres, 'bad' acres */
    gfxprint_locate8x8(gfxprint, 3, 16);
    gfxprint_printf(gfxprint, " %02d", l_field_assessment_rank); /* current field rank */
}
