#include "m_inventory_ovl.h"

#include "m_player_lib.h"
#include "ac_set_ovl_gyoei.h"
#include "ac_set_ovl_insect.h"
#include "m_room_type.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_bgm.h"
#include "zurumode.h"
#include "padmgr.h"
#include "m_play.h"
#include "m_font.h"

enum {
    mIV_ITEM_KIND_AXE,
    mIV_ITEM_KIND_NET,
    mIV_ITEM_KIND_UMBRELLA,
    mIV_ITEM_KIND_ROD,
    mIV_ITEM_KIND_SHOVEL,

    mIV_ITEM_KIND_GOLD_AXE,
    mIV_ITEM_KIND_GOLD_NET,
    mIV_ITEM_KIND_GOLD_ROD,
    mIV_ITEM_KIND_GOLD_SHOVEL,

    mIV_ITEM_KIND_RED_BALLOON,
    mIV_ITEM_KIND_YELLOW_BALLOON,
    mIV_ITEM_KIND_BLUE_BALLOON,
    mIV_ITEM_KIND_GREEN_BALLOON,
    mIV_ITEM_KIND_PURPLE_BALLOON,
    mIV_ITEM_KIND_BUNNY_P_BALLOON,
    mIV_ITEM_KIND_BUNNY_B_BALLOON,
    mIV_ITEM_KIND_BUNNY_O_BALLOON,

    mIV_ITEM_KIND_YELLOW_PINWHEEL,
    mIV_ITEM_KIND_RED_PINWHEEL,
    mIV_ITEM_KIND_TIGER_PINWHEEL,
    mIV_ITEM_KIND_GREEN_PINWHEEL,
    mIV_ITEM_KIND_PINK_PINWHEEL,
    mIV_ITEM_KIND_STRIPED_PINWHEEL,
    mIV_ITEM_KIND_FLOWER_PINWHEEL,
    mIV_ITEM_KIND_FANCY_PINWHEEL,

    mIV_ITEM_KIND_BLUEBELL_FAN,
    mIV_ITEM_KIND_PLUM_FAN,
    mIV_ITEM_KIND_BAMBOO_FAN,
    mIV_ITEM_KIND_CLOUD_FAN,
    mIV_ITEM_KIND_MAPLE_FAN,
    mIV_ITEM_KIND_FAN_FAN,
    mIV_ITEM_KIND_FLOWER_FAN,
    mIV_ITEM_KIND_LEAF_FAN,

    mIV_ITEM_KIND_AXE_USE_1,
    mIV_ITEM_KIND_AXE_USE_2,
    mIV_ITEM_KIND_AXE_USE_3,
    mIV_ITEM_KIND_AXE_USE_4,
    mIV_ITEM_KIND_AXE_USE_5,
    mIV_ITEM_KIND_AXE_USE_6,
    mIV_ITEM_KIND_AXE_USE_7,

    mIV_ITEM_KIND_NUM
};

static mIV_Ovl_c inv_ovl_data;

// clang-format off
#define F(n) aGYO_TYPE_##n

/* Fish collection layout */
static u8 mIV_fish_collect_list[] = {
    F(CRUCIAN_CARP), F(BROOK_TROUT),     F(CARP),             F(KOI),       F(BARBEL_STEED),  F(DACE),          F(CATFISH),         F(GIANT_CATFISH),
    F(PALE_CHUB),    F(BITTERLING),      F(LOACH),            F(BLUEGILL),  F(SMALL_BASS),    F(BASS),          F(LARGE_BASS),      F(GIANT_SNAKEHEAD),
    F(EEL),          F(FRESHWATER_GOBY), F(POND_SMELT),       F(SWEETFISH), F(CHERRY_SALMON), F(RAINBOW_TROUT), F(LARGE_CHAR),      F(STRINGFISH),
    F(SALMON),       F(GOLDFISH),        F(POPEYED_GOLDFISH), F(GUPPY),     F(ANGELFISH),     F(PIRANHA),       F(AROWANA),         F(COELACANTH),
    F(CRAWFISH),     F(FROG),            F(KILLIFISH),        F(JELLYFISH), F(SEA_BASS),      F(RED_SNAPPER),   F(BARRED_KNIFEJAW), F(ARAPAIMA),
};
#undef F
// clang-format on

// clang-format off
#define I(n) aINS_INSECT_TYPE_##n

/* Insect collection layout */
static u8 mIV_insect_collect_list[] = {
    I(COMMON_BUTTERFLY), I(YELLOW_BUTTERFLY), I(TIGER_BUTTERFLY),  I(PURPLE_BUTTERFLY), I(BROWN_CICADA),     I(ROBUST_CICADA),  I(WALKER_CICADA),    I(EVENING_CICADA),
    I(RED_DRAGONFLY),    I(COMMON_DRAGONFLY), I(DARNER_DRAGONFLY), I(BANDED_DRAGONFLY), I(CRICKET),          I(GRASSHOPPER),    I(PINE_CRICKET),     I(BELL_CRICKET),
    I(LADYBUG),          I(SPOTTED_LADYBUG),  I(MANTIS),           I(LONG_LOCUST),      I(MIGRATORY_LOCUST), I(COCKROACH),      I(BEE),              I(FIREFLY),
    I(DRONE_BEETLE),     I(LONGHORN_BEETLE),  I(JEWEL_BEETLE),     I(DYNASTID_BEETLE),  I(FLAT_STAG_BEETLE), I(SAW_STAG_BEETLE), I(MOUNTAIN_BEETLE), I(GIANT_BEETLE),
    I(POND_SKATER),      I(ANT),              I(PILL_BUG),         I(MOSQUITO),         I(MOLE_CRICKET),     I(SPIDER),          I(SNAIL),           I(BAGWORM),
};
#undef I
// clang-format on

static int mIV_Get_pl_main_anime_index(int type) {
    static u16 player_main_animation_index_table[mIV_ANIM_NUM] = {
        mPlayer_ANIM_WALK1,
        mPlayer_ANIM_MENU_CATCH1,
        mPlayer_ANIM_MENU_CHANGE1,
        mPlayer_ANIM_EAT1,
    };

    if (type >= mIV_ANIM_WALK && type < mIV_ANIM_NUM) {
        return player_main_animation_index_table[type];
    }

    return -1;
}

static mActor_name_t mIV_set_collect_itemNo(int type, int page) {
    if (page == mIV_PAGE_INSECT_COLLECTION) {
        int insect_no = mIV_insect_collect_list[type];
        int bit = mRmTp_FtrItemNo2FtrIdx(FTR_INSECT_START + FTR_NO_2_IDX(insect_no));

        if (Now_Private->furniture_collected_bitfield[bit >> 5] & (1 << (bit & 31))) {
            return ITM_INSECT_START + insect_no;
        } else {
            return EMPTY_NO;
        }
    } else {
        int fish_no = mIV_fish_collect_list[type];
        int bit = FTR_IDX_2_NO(FTR_NO_2_IDX(FTR_SUM_FUNA) + (u32)FTR_NO_2_IDX(fish_no));

        if (Now_Private->furniture_collected_bitfield[bit >> 5] & (1 << (bit & 31))) {
            return mNT_FishIdx2FishItemNo(fish_no);
        } else {
            return EMPTY_NO;
        }
    }
}

static s16 mIV_get_player_item_anime_id(void) {
    mActor_name_t item = Now_Private->equipment;
    s16 res;

    if (item >= ITM_NET && item <= ITM_NET) {
        res = mIV_ITEM_KIND_NET;
    } else if (item == ITM_AXE) {
        res = mIV_ITEM_KIND_AXE;
    } else if (item == ITM_GOLDEN_AXE) {
        res = mIV_ITEM_KIND_GOLD_AXE;
    } else if (item == ITM_AXE_USE_1) {
        res = mIV_ITEM_KIND_AXE_USE_1;
    } else if (item == ITM_AXE_USE_2) {
        res = mIV_ITEM_KIND_AXE_USE_2;
    } else if (item == ITM_AXE_USE_3) {
        res = mIV_ITEM_KIND_AXE_USE_3;
    } else if (item == ITM_AXE_USE_4) {
        res = mIV_ITEM_KIND_AXE_USE_4;
    } else if (item == ITM_AXE_USE_5) {
        res = mIV_ITEM_KIND_AXE_USE_5;
    } else if (item == ITM_AXE_USE_6) {
        res = mIV_ITEM_KIND_AXE_USE_6;
    } else if (item == ITM_AXE_USE_7) {
        res = mIV_ITEM_KIND_AXE_USE_7;
    } else if (item >= ITM_ROD && item <= ITM_ROD) {
        res = mIV_ITEM_KIND_ROD;
    } else if (item >= ITM_UMBRELLA_START && item <= ITM_MY_ORG_UMBRELLA7) {
        res = mIV_ITEM_KIND_UMBRELLA;
    } else if (item >= ITM_SHOVEL && item <= ITM_SHOVEL) {
        res = mIV_ITEM_KIND_SHOVEL;
    } else if (item >= ITM_GOLDEN_AXE && item <= ITM_GOLDEN_AXE) { /* duplicate golden axe check */
        res = mIV_ITEM_KIND_GOLD_AXE;
    } else if (item >= ITM_GOLDEN_NET && item <= ITM_GOLDEN_NET) {
        res = mIV_ITEM_KIND_GOLD_NET;
    } else if (item >= ITM_GOLDEN_ROD && item <= ITM_GOLDEN_ROD) {
        res = mIV_ITEM_KIND_GOLD_ROD;
    } else if (item >= ITM_GOLDEN_SHOVEL && item <= ITM_GOLDEN_SHOVEL) {
        res = mIV_ITEM_KIND_GOLD_SHOVEL;
    } else if (item == ITM_RED_BALLOON) {
        res = mIV_ITEM_KIND_RED_BALLOON;
    } else if (item == ITM_YELLOW_BALLOON) {
        res = mIV_ITEM_KIND_YELLOW_BALLOON;
    } else if (item == ITM_BLUE_BALLOON) {
        res = mIV_ITEM_KIND_BLUE_BALLOON;
    } else if (item == ITM_GREEN_BALLOON) {
        res = mIV_ITEM_KIND_GREEN_BALLOON;
    } else if (item == ITM_PURPLE_BALLOON) {
        res = mIV_ITEM_KIND_PURPLE_BALLOON;
    } else if (item == ITM_BUNNY_P_BALLOON) {
        res = mIV_ITEM_KIND_BUNNY_P_BALLOON;
    } else if (item == ITM_BUNNY_B_BALLOON) {
        res = mIV_ITEM_KIND_BUNNY_B_BALLOON;
    } else if (item == ITM_BUNNY_O_BALLOON) {
        res = mIV_ITEM_KIND_BUNNY_O_BALLOON;
    } else if (item == ITM_YELLOW_PINWHEEL) {
        res = mIV_ITEM_KIND_YELLOW_PINWHEEL;
    } else if (item == ITM_RED_PINWHEEL) {
        res = mIV_ITEM_KIND_RED_PINWHEEL;
    } else if (item == ITM_TIGER_PINWHEEL) {
        res = mIV_ITEM_KIND_TIGER_PINWHEEL;
    } else if (item == ITM_GREEN_PINWHEEL) {
        res = mIV_ITEM_KIND_GREEN_PINWHEEL;
    } else if (item == ITM_PINK_PINWHEEL) {
        res = mIV_ITEM_KIND_PINK_PINWHEEL;
    } else if (item == ITM_STRIPED_PINWHEEL) {
        res = mIV_ITEM_KIND_STRIPED_PINWHEEL;
    } else if (item == ITM_FLOWER_PINWHEEL) {
        res = mIV_ITEM_KIND_FLOWER_PINWHEEL;
    } else if (item == ITM_FANCY_PINWHEEL) {
        res = mIV_ITEM_KIND_FANCY_PINWHEEL;
    } else if (item == ITM_BLUEBELL_FAN) {
        res = mIV_ITEM_KIND_BLUEBELL_FAN;
    } else if (item == ITM_PLUM_FAN) {
        res = mIV_ITEM_KIND_PLUM_FAN;
    } else if (item == ITM_BAMBOO_FAN) {
        res = mIV_ITEM_KIND_BAMBOO_FAN;
    } else if (item == ITM_CLOUD_FAN) {
        res = mIV_ITEM_KIND_CLOUD_FAN;
    } else if (item == ITM_MAPLE_FAN) {
        res = mIV_ITEM_KIND_MAPLE_FAN;
    } else if (item == ITM_FAN_FAN) {
        res = mIV_ITEM_KIND_FAN_FAN;
    } else if (item == ITM_FLOWER_FAN) {
        res = mIV_ITEM_KIND_FLOWER_FAN;
    } else if (item == ITM_LEAF_FAN) {
        res = mIV_ITEM_KIND_LEAF_FAN;
    } else {
        res = mIV_ITEM_KIND_NUM; /* No animation */
    }

    return res;
}

static int mIV_ChangeIndex_mIV_to_mPlib(s16 idx) {
    static const s8 data[] = {
        mPlayer_ITEM_KIND_AXE,
        mPlayer_ITEM_KIND_NET,
        mPlayer_ITEM_KIND_UMBRELLA00,
        mPlayer_ITEM_KIND_ROD,
        mPlayer_ITEM_KIND_SHOVEL,

        mPlayer_ITEM_KIND_GOLD_AXE,
        mPlayer_ITEM_KIND_GOLD_NET,
        mPlayer_ITEM_KIND_GOLD_ROD,
        mPlayer_ITEM_KIND_GOLD_SHOVEL,

        mPlayer_ITEM_KIND_RED_BALLOON,
        mPlayer_ITEM_KIND_YELLOW_BALLOON,
        mPlayer_ITEM_KIND_BLUE_BALLOON,
        mPlayer_ITEM_KIND_GREEN_BALLOON,
        mPlayer_ITEM_KIND_PURPLE_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_P_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_B_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_O_BALLOON,

        mPlayer_ITEM_KIND_YELLOW_PINWHEEL,
        mPlayer_ITEM_KIND_RED_PINWHEEL,
        mPlayer_ITEM_KIND_TIGER_PINWHEEL,
        mPlayer_ITEM_KIND_GREEN_PINWHEEL,
        mPlayer_ITEM_KIND_PINK_PINWHEEL,
        mPlayer_ITEM_KIND_STRIPED_PINWHEEL,
        mPlayer_ITEM_KIND_FLOWER_PINWHEEL,
        mPlayer_ITEM_KIND_FANCY_PINWHEEL,

        mPlayer_ITEM_KIND_BLUEBELL_FAN,
        mPlayer_ITEM_KIND_PLUM_FAN,
        mPlayer_ITEM_KIND_BAMBOO_FAN,
        mPlayer_ITEM_KIND_CLOUD_FAN,
        mPlayer_ITEM_KIND_MAPLE_FAN,
        mPlayer_ITEM_KIND_FAN_FAN,
        mPlayer_ITEM_KIND_FLOWER_FAN,
        mPlayer_ITEM_KIND_LEAF_FAN,

        mPlayer_ITEM_KIND_AXE_USE_1,
        mPlayer_ITEM_KIND_AXE_USE_2,
        mPlayer_ITEM_KIND_AXE_USE_3,
        mPlayer_ITEM_KIND_AXE_USE_4,
        mPlayer_ITEM_KIND_AXE_USE_5,
        mPlayer_ITEM_KIND_AXE_USE_6,
        mPlayer_ITEM_KIND_AXE_USE_7,
    };

    if (idx >= 0 && idx < mIV_ITEM_KIND_NUM) {
        return data[idx];
    }

    return -1;
}

static int mIV_Get_player_item_shape_index(int idx) {
    if (idx >= 0 && idx < mIV_ITEM_KIND_NUM) {
        int plib_idx = mIV_ChangeIndex_mIV_to_mPlib(idx);
        int shape_idx = mPlib_Get_BasicItemShapeIndex_fromItemKind(plib_idx);

        if (shape_idx >= 0 && shape_idx < mPlayer_ITEM_DATA_NUM) {
            return shape_idx;
        }

        return mPlayer_ITEM_DATA_NUM;
    }

    return -1;
}

static cKF_Skeleton_R_c* mIV_Get_pl_item_skeleton(int idx) {
    if (idx >= 0 && idx < mIV_ITEM_KIND_NUM) {
        int shape_idx = mIV_Get_player_item_shape_index(idx);

        if (shape_idx >= 0 && shape_idx < mPlayer_ITEM_DATA_NUM) {
            u8 data_type = mPlib_Get_Item_DataPointerType(shape_idx);

            if (data_type == mPlayer_ITEM_DATA_TYPE_SKELETON) {
                return (cKF_Skeleton_R_c*)mPlib_Get_Item_DataPointer(shape_idx);
            }
        }
    }

    return NULL;
}

static int mIV_Get_player_com_animation_index(s16 idx) {
    return mPlib_Get_BasicPlayerAnimeIndex_fromItemKind(mIV_ChangeIndex_mIV_to_mPlib(idx));
}

static cKF_Animation_R_c* mIV_Get_pl_com_anime(s16 idx) {
    return mPlib_Get_Pointer_Animation(mIV_Get_player_com_animation_index(idx));
}

static int mIV_Get_player_com_part_table_index(s16 idx) {
    int plib_idx = mIV_ChangeIndex_mIV_to_mPlib(idx);
    int anime_idx = mPlib_Get_BasicPlayerAnimeIndex_fromItemKind(plib_idx);

    return mPlib_Get_BasicPartTableIndex_fromAnimeIndex(anime_idx);
}

static int mIV_Get_player_item_anime_index(s16 idx) {
    int anime_idx = mPlib_Get_BasicItemAnimeIndex_fromItemKind(mIV_ChangeIndex_mIV_to_mPlib(idx));

    if (anime_idx >= 0 && anime_idx < mPlayer_ITEM_DATA_NUM) {
        return anime_idx == mPlayer_ITEM_DATA_BALLOON_GYAZA ? mPlayer_ITEM_DATA_BALLOON_WAIT : anime_idx;
    }

    return mPlayer_ITEM_DATA_NUM;
}

static cKF_Animation_R_c* mIV_Get_pl_item_anime(s16 idx) {
    int anime_idx = mIV_Get_player_item_anime_index(idx);

    if (anime_idx >= 0 && anime_idx < mPlayer_ITEM_DATA_NUM) {
        return (cKF_Animation_R_c*)mPlib_Get_Item_DataPointer(anime_idx);
    }

    return NULL;
}

static cKF_Animation_R_c* mIV_Get_pl_main_anime(int idx) {
    if (idx >= 0 && idx < mIV_ANIM_NUM) {
        return mPlib_Get_Pointer_Animation(mIV_Get_pl_main_anime_index(idx));
    }

    return NULL;
}

static void mIV_pl_load_player_anime(Submenu* submenu, f32 morph_frame) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int main_anim_idx = seg->player_main_anime_idx;
    int item_anim_idx = seg->player_item_anime_idx;
    int com_type = mIV_ITEM_KIND_NUM;
    int unused_idx0 = mIV_Get_pl_main_anime_index(main_anim_idx);
    cKF_Animation_R_c* anime = mIV_Get_pl_main_anime(main_anim_idx);
    int mode;
    int bank_idx;

    if (item_anim_idx != mIV_ITEM_KIND_NUM) {
        if (main_anim_idx == mIV_ANIM_EAT) {
            com_type = mIV_ITEM_KIND_NET; // ?
        } else if (main_anim_idx == mIV_ANIM_WALK) {
            com_type = item_anim_idx;
        }
    }

    if (com_type != mIV_ITEM_KIND_NUM) {
        mPlib_DMA_player_Part_Table(seg->player_part_table, mIV_Get_player_com_part_table_index(com_type));
    } else {
        mPlib_DMA_player_Part_Table(seg->player_part_table, mPlayer_PART_TABLE_NORMAL);
    }

    /* Select animation mode */
    if (main_anim_idx == mIV_ANIM_WALK) {
        mode = cKF_FRAMECONTROL_REPEAT;
    } else {
        mode = cKF_FRAMECONTROL_STOP;
    }

    /* Load main animation */
    if (main_anim_idx == mIV_ANIM_CHANGE) {
        cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(&inv_ovl->player_main_keyframe, anime, NULL,
                                                                         1.0f, 1.0f, morph_frame, mode);
    } else {
        cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(&inv_ovl->player_main_keyframe, anime, NULL,
                                                                         1.0f, 0.5f, morph_frame, mode);
    }

    if (com_type != mIV_ITEM_KIND_NUM) {
        int unused_anim1 = mIV_Get_player_com_animation_index(com_type);

        anime = mIV_Get_pl_com_anime(com_type);
    }

    /* Load com animation */
    if (main_anim_idx == mIV_ANIM_CHANGE) {
        cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(&inv_ovl->player_com_keyframe, anime, NULL,
                                                                         1.0f, 1.0f, morph_frame, mode);
    } else {
        cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(&inv_ovl->player_com_keyframe, anime, NULL,
                                                                         1.0f, 0.5f, morph_frame, mode);
    }

    /* Play animations */
    cKF_SkeletonInfo_R_combine_play(&inv_ovl->player_main_keyframe, &inv_ovl->player_com_keyframe,
                                    seg->player_part_table);

    seg->player_umbrella_bank_idx ^= 1;
    bank_idx = seg->player_umbrella_bank_idx;
    if (item_anim_idx == mIV_ITEM_KIND_UMBRELLA) {
        mActor_name_t item = Now_Private->equipment;

        seg->umbrella_ids[bank_idx] =
            (item >= ITM_UMBRELLA00 && item <= ITM_MY_ORG_UMBRELLA7) ? (item - ITM_UMBRELLA_START) : EMPTY_NO;
    } else if (item_anim_idx != mIV_ITEM_KIND_NUM) {
        int unused_shape_idx = mIV_Get_player_item_shape_index(item_anim_idx);
        cKF_Skeleton_R_c* item_skel = mIV_Get_pl_item_skeleton(item_anim_idx);
        int unused_anim_idx;
        cKF_Animation_R_c* item_anim;

        if (item_skel != NULL) {
            cKF_SkeletonInfo_R_ct(&inv_ovl->item_keyframe, item_skel, NULL, inv_ovl->item_work, inv_ovl->item_morph);
            unused_anim_idx = mIV_Get_player_item_anime_index(item_anim_idx);
            item_anim = mIV_Get_pl_item_anime(item_anim_idx);

            if (item_anim_idx >= mIV_ITEM_KIND_YELLOW_PINWHEEL && item_anim_idx <= mIV_ITEM_KIND_FANCY_PINWHEEL) {
                cKF_SkeletonInfo_R_init(&inv_ovl->item_keyframe, inv_ovl->item_keyframe.skeleton, item_anim, 1.0f,
                                        (f32)item_anim->frames, 1.0f, 7.5f, 0.0f, cKF_FRAMECONTROL_REPEAT, NULL);
            } else {
                cKF_SkeletonInfo_R_init(&inv_ovl->item_keyframe, inv_ovl->item_keyframe.skeleton, item_anim, 1.0f,
                                        (f32)item_anim->frames, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_REPEAT, NULL);
            }

            cKF_SkeletonInfo_R_play(&inv_ovl->item_keyframe);
        }
    }
}

static void mIV_pl_shape_init(Submenu* submenu) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    cKF_SkeletonInfo_R_ct(&inv_ovl->player_main_keyframe, mPlib_get_player_mdl_p(), NULL, inv_ovl->player_work,
                          inv_ovl->player_morph);
    cKF_SkeletonInfo_R_ct(&inv_ovl->player_com_keyframe, mPlib_get_player_mdl_p(), NULL, inv_ovl->player_work,
                          inv_ovl->player_morph);
    seg->player_umbrella_bank_idx = 0;
    seg->player_main_anime_idx = mIV_ANIM_WALK;
    seg->player_item_anime_idx = mIV_get_player_item_anime_id();
    seg->change_player_main_anime_idx = mIV_ANIM_WALK;
    mIV_pl_load_player_anime(submenu, 0.0f);
}

static void mIV_pl_eff_move(Submenu* submenu) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mIV_pl_eff_c* effect_p = inv_ovl->pl_eff;
    f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;
    int i;

    for (i = 0; i < mIV_PLAYER_EFFECT_NUM; i++) {
        if (effect_p->timer > 0.0f) {
            effect_p->timer -= dt;
            if (effect_p->timer < 0.0f) {
                effect_p->timer = 0.0f;
            }

            if (effect_p->timer > 20.0f) {
                chase_f(&effect_p->scale, 0.009f, 0.0009f * dt);
            } else {
                chase_f(&effect_p->scale, 0.0f, 0.00045f * dt);
            }

            effect_p->speed += -0.05f * dt;
            effect_p->pos.y += effect_p->speed * dt;
        }

        effect_p++;
    }

    if (submenu->overlay->segment.player_main_anime_idx == mIV_ANIM_CHANGE) {
        f32 cur_frame = inv_ovl->player_main_keyframe.frame_control.current_frame;
        int effect_no = (int)cur_frame % mIV_PLAYER_EFFECT_NUM;
        s16 angle = (int)cur_frame * DEG2SHORT_ANGLE2(-36.0f);
        mIV_pl_eff_c* effect_p = &inv_ovl->pl_eff[effect_no];

        effect_p->timer = 30.0f;
        effect_p->speed = 0.0f;
        effect_p->scale = 0.0f;
        effect_p->pos.x = 22.0f * sin_s(angle) + RANDOM2_F(5.0f);
        effect_p->pos.z = 22.0f * cos_s(angle) + RANDOM2_F(5.0f);
        effect_p->pos.y = (35.0f / inv_ovl->player_main_keyframe.frame_control.end_frame) * cur_frame + RANDOM2_F(5.0f);
    }
}

static void mIV_pl_check_anm_change(Submenu* submenu) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    f32 morph_frame;

    if (seg->change_player_main_anime_idx != seg->player_main_anime_idx) {
        if (seg->change_player_main_anime_idx == mIV_ANIM_EAT) {
            morph_frame = 6.0f;
        } else if (seg->change_player_main_anime_idx == mIV_ANIM_CHANGE) {
            morph_frame = -5.0f;
        } else if (seg->change_player_main_anime_idx == mIV_ANIM_CATCH) {
            morph_frame = -7.0f;
        } else if (seg->player_main_anime_idx == mIV_ANIM_CHANGE) {
            morph_frame = -5.0f;
        } else if (seg->player_main_anime_idx == mIV_ANIM_EAT) {
            morph_frame = -5.0f;
        } else {
            seg->player_item_anime_idx = mIV_get_player_item_anime_id();
            morph_frame = -8.0f;
        }

        seg->player_main_anime_idx = seg->change_player_main_anime_idx;
        mIV_pl_load_player_anime(submenu, morph_frame);
    }
}

static void mIV_pl_shape_move(Submenu* submenu) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int anim_state = cKF_SkeletonInfo_R_combine_play(&inv_ovl->player_main_keyframe, &inv_ovl->player_com_keyframe,
                                                     seg->player_part_table);

    if (seg->player_item_anime_idx != mIV_ITEM_KIND_NUM &&
        mIV_Get_pl_item_skeleton(seg->player_item_anime_idx) != NULL) {
        cKF_SkeletonInfo_R_play(&inv_ovl->item_keyframe);
    }

    if (seg->player_anime_timer > 0) {
        static float player_anime_accum = 0.0f;
        int ticks = graph_dt_60hz_ticks(gamePT, &player_anime_accum);
        seg->player_anime_timer -= ticks;
        if (seg->player_anime_timer < 0) {
            seg->player_anime_timer = 0;
        }
    }

    mIV_pl_eff_move(submenu);
    if (seg->player_main_anime_idx == mIV_ANIM_CATCH) {
        seg->player_anime_timer = 8;
    } else if (seg->player_main_anime_idx == mIV_ANIM_CHANGE) {
        seg->player_anime_timer = 5;

        if (anim_state == cKF_STATE_STOPPED) {
            seg->change_player_main_anime_idx = mIV_ANIM_WALK;
        }
    } else if (seg->player_main_anime_idx == mIV_ANIM_EAT) {
        seg->player_anime_timer = 5;

        if (anim_state == cKF_STATE_STOPPED) {
            seg->change_player_main_anime_idx = mIV_ANIM_WALK;
        } else if (cKF_FrameControl_passCheck_now(&inv_ovl->player_main_keyframe.frame_control, 17.0f)) {
            sAdo_SysTrgStart(NA_SE_EAT);
        }
    }

    mIV_pl_check_anm_change(submenu);
}

static void mIV_pl_shape_item_draw_net(Submenu* submenu, GAME* game) {
    cKF_SkeletonInfo_R_c* item_kf = &submenu->overlay->inventory_ovl->item_keyframe;
    N64Mtx* mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, item_kf->skeleton->num_shown_joints);

    if (mtx != NULL) {
        cKF_Si3_draw_R_SV(game, item_kf, mtx, NULL, NULL, NULL);
    }
}

static void mIV_pl_shape_item_draw_axe(Submenu* submenu, GAME* game) {
    int shape_idx = mIV_Get_player_item_shape_index(submenu->overlay->segment.player_item_anime_idx);
    Gfx* axe_gfx = (Gfx*)mPlib_Get_Item_DataPointer(shape_idx);

    if (axe_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPDisplayList(NEXT_POLY_OPA_DISP, axe_gfx);

        CLOSE_DISP(game->graph);
    }
}

typedef struct umbrella_data_s {
    Gfx* e_model;
    Gfx* kasa_model;
} mIV_umbrella_data_c;

extern Gfx e_umb01_model[];
extern Gfx kasa_umb01_model[];
extern Gfx e_umb02_model[];
extern Gfx kasa_umb02_model[];
extern Gfx e_umb03_model[];
extern Gfx kasa_umb03_model[];
extern Gfx e_umb04_model[];
extern Gfx kasa_umb04_model[];
extern Gfx e_umb05_model[];
extern Gfx kasa_umb05_model[];
extern Gfx e_umb06_model[];
extern Gfx kasa_umb06_model[];
extern Gfx e_umb07_model[];
extern Gfx kasa_umb07_model[];
extern Gfx e_umb08_model[];
extern Gfx kasa_umb08_model[];
extern Gfx e_umb09_model[];
extern Gfx kasa_umb09_model[];
extern Gfx e_umb10_model[];
extern Gfx kasa_umb10_model[];
extern Gfx e_umb11_model[];
extern Gfx kasa_umb11_model[];
extern Gfx e_umb12_model[];
extern Gfx kasa_umb12_model[];
extern Gfx e_umb13_model[];
extern Gfx kasa_umb13_model[];
extern Gfx e_umb14_model[];
extern Gfx kasa_umb14_model[];
extern Gfx e_umb15_model[];
extern Gfx kasa_umb15_model[];
extern Gfx e_umb16_model[];
extern Gfx kasa_umb16_model[];
extern Gfx e_umb17_model[];
extern Gfx kasa_umb17_model[];
extern Gfx e_umb18_model[];
extern Gfx kasa_umb18_model[];
extern Gfx e_umb19_model[];
extern Gfx kasa_umb19_model[];
extern Gfx e_umb20_model[];
extern Gfx kasa_umb20_model[];
extern Gfx e_umb21_model[];
extern Gfx kasa_umb21_model[];
extern Gfx e_umb22_model[];
extern Gfx kasa_umb22_model[];
extern Gfx e_umb23_model[];
extern Gfx kasa_umb23_model[];
extern Gfx e_umb24_model[];
extern Gfx kasa_umb24_model[];
extern Gfx e_umb25_model[];
extern Gfx kasa_umb25_model[];
extern Gfx e_umb26_model[];
extern Gfx kasa_umb26_model[];
extern Gfx e_umb27_model[];
extern Gfx kasa_umb27_model[];
extern Gfx e_umb28_model[];
extern Gfx kasa_umb28_model[];
extern Gfx e_umb29_model[];
extern Gfx kasa_umb29_model[];
extern Gfx e_umb30_model[];
extern Gfx kasa_umb30_model[];
extern Gfx e_umb31_model[];
extern Gfx kasa_umb31_model[];
extern Gfx e_umb32_model[];
extern Gfx kasa_umb32_model[];
extern Gfx e_umb_w_model[];
extern Gfx kasa_umb_w_model[];

static void mIV_pl_shape_item_draw_umbrella(Submenu* submenu, GAME* game) {
    // clang-format off
    static mIV_umbrella_data_c pl_umb_data[] = {
        { e_umb01_model, kasa_umb01_model },
        { e_umb02_model, kasa_umb02_model },
        { e_umb03_model, kasa_umb03_model },
        { e_umb04_model, kasa_umb04_model },
        { e_umb05_model, kasa_umb05_model },
        { e_umb06_model, kasa_umb06_model },
        { e_umb07_model, kasa_umb07_model },
        { e_umb08_model, kasa_umb08_model },
        { e_umb09_model, kasa_umb09_model },
        { e_umb10_model, kasa_umb10_model },
        { e_umb11_model, kasa_umb11_model },
        { e_umb12_model, kasa_umb12_model },
        { e_umb13_model, kasa_umb13_model },
        { e_umb14_model, kasa_umb14_model },
        { e_umb15_model, kasa_umb15_model },
        { e_umb16_model, kasa_umb16_model },
        { e_umb17_model, kasa_umb17_model },
        { e_umb18_model, kasa_umb18_model },
        { e_umb19_model, kasa_umb19_model },
        { e_umb20_model, kasa_umb20_model },
        { e_umb21_model, kasa_umb21_model },
        { e_umb22_model, kasa_umb22_model },
        { e_umb23_model, kasa_umb23_model },
        { e_umb24_model, kasa_umb24_model },
        { e_umb25_model, kasa_umb25_model },
        { e_umb26_model, kasa_umb26_model },
        { e_umb27_model, kasa_umb27_model },
        { e_umb28_model, kasa_umb28_model },
        { e_umb29_model, kasa_umb29_model },
        { e_umb30_model, kasa_umb30_model },
        { e_umb31_model, kasa_umb31_model },
        { e_umb32_model, kasa_umb32_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
        { e_umb_w_model, kasa_umb_w_model },
    };
    // clang-format on
    GRAPH* graph = game->graph;
    int umbrella_idx = submenu->overlay->segment.umbrella_ids[submenu->overlay->segment.player_umbrella_bank_idx];
    mIV_umbrella_data_c* pl_umb_data_p = &pl_umb_data[umbrella_idx];
    int umbrella_item_kind = mPlayer_ITEM_KIND_UMBRELLA00 + umbrella_idx;

    _texture_z_light_fog_prim_npc(graph);

    OPEN_POLY_OPA_DISP(graph);

    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH);

    Matrix_RotateY(DEG2SHORT_ANGLE2(-90.0f), MTX_MULT);
    Matrix_translate(800.0f, 0.0f, 0.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, pl_umb_data_p->e_model);
    Matrix_translate(4000.0f, 0.0f, 0.0f, MTX_MULT);

    /* Handle custom designs */
    if (umbrella_item_kind >= mPlayer_ITEM_KIND_ORG_UMBRELLA00) {
        int org_idx = (umbrella_item_kind - mPlayer_ITEM_KIND_ORG_UMBRELLA00) & 7;

        gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_8, mNW_PaletteIdx2Palette(Now_Private->my_org[org_idx].palette));
        gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_9, Now_Private->my_org[org_idx].design.data);
    }

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, pl_umb_data_p->kasa_model);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx inv_uki_model[];  // rod
extern Gfx inv_uki2_model[]; // golden rod

static void mIV_pl_shape_item_draw_rod(Submenu* submenu, GAME* game) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    cKF_SkeletonInfo_R_c* item_kf = &submenu->overlay->inventory_ovl->item_keyframe;
    N64Mtx* mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, item_kf->skeleton->num_shown_joints);

    if (mtx != NULL) {
        xyz_t pos;

        Matrix_Position_VecZ(1500.0f, &pos);
        cKF_Si3_draw_R_SV(game, item_kf, mtx, NULL, NULL, NULL);
        Matrix_put(&submenu->overlay->inventory_ovl->item_mtx);
        Matrix_translate(0.0f, 0.0f, 1500.0f, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE2(24.219360f), MTX_MULT); // 0x1139
        Matrix_RotateX(DEG2SHORT_ANGLE2(65.494995f), MTX_MULT); // 0x2E93
        Matrix_RotateY(DEG2SHORT_ANGLE2(79.634399f), MTX_MULT); // 0x38A1
        Matrix_translate(0.0f, -500.0f, 0.0f, MTX_MULT);

        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (seg->player_item_anime_idx == mIV_ITEM_KIND_GOLD_ROD) {
            gSPDisplayList(NEXT_POLY_OPA_DISP, inv_uki2_model);
        } else {
            gSPDisplayList(NEXT_POLY_OPA_DISP, inv_uki_model);
        }

        CLOSE_DISP(game->graph);
    }
}

static void mIV_pl_shape_item_draw_scoop(Submenu* submenu, GAME* game) {
    int shape_idx = mIV_Get_player_item_shape_index(submenu->overlay->segment.player_item_anime_idx);
    Gfx* scoop_gfx = (Gfx*)mPlib_Get_Item_DataPointer(shape_idx);

    if (scoop_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPDisplayList(NEXT_POLY_OPA_DISP, scoop_gfx);

        CLOSE_DISP(game->graph);
    }
}

static int mIV_pl_shape_item_draw_balloon_Before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx,
                                                 Gfx** joint_shape, u8* joint_flags, void* arg, s_xyz* joint_rot,
                                                 xyz_t* joint_pos) {
    switch (joint_idx) {
        case 1:
        case 2:
        case 3: {
            OPEN_DISP(game->graph);

            gDPPipeSync(NEXT_POLY_OPA_DISP);
            gDPSetTexEdgeAlpha(NEXT_POLY_OPA_DISP, 80);

            CLOSE_DISP(game->graph);
            break;
        }
    }

    return TRUE;
}

static int mIV_pl_shape_item_draw_balloon_After(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx,
                                                Gfx** joint_shape, u8* joint_flags, void* arg, s_xyz* joint_rot,
                                                xyz_t* joint_pos) {
    switch (joint_idx) {
        case 1:
        case 2:
        case 3: {
            OPEN_DISP(game->graph);

            gDPPipeSync(NEXT_POLY_OPA_DISP);
            gDPSetTexEdgeAlpha(NEXT_POLY_OPA_DISP, 144);

            CLOSE_DISP(game->graph);
            break;
        }
    }

    return TRUE;
}

static void mIV_pl_shape_item_draw_balloon(Submenu* submenu, GAME* game) {
    cKF_SkeletonInfo_R_c* item_kf = &submenu->overlay->inventory_ovl->item_keyframe;
    N64Mtx* mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, item_kf->skeleton->num_shown_joints);

    if (mtx != NULL) {
        static xyz_t dummy_eye = { 0.0f, 0.0f, 1.0f };
        static xyz_t dummy_light_direction = { -SQRT_3_OVER_3_F, SQRT_3_OVER_3_F, SQRT_3_OVER_3_F };
        GRAPH* graph = game->graph;
        Hilite* hilite;

        OPEN_DISP(graph);

        SET_POLY_OPA_DISP(
            HiliteReflect_new(&ZeroVec, &dummy_eye, &dummy_light_direction, graph, NOW_POLY_OPA_DISP, &hilite));

        CLOSE_DISP(graph);

        cKF_Si3_draw_R_SV(game, item_kf, mtx, &mIV_pl_shape_item_draw_balloon_Before,
                          &mIV_pl_shape_item_draw_balloon_After, NULL);
    }
}

static void mIV_pl_shape_item_draw_windmill(Submenu* submenu, GAME* game) {
    cKF_SkeletonInfo_R_c* item_kf = &submenu->overlay->inventory_ovl->item_keyframe;
    N64Mtx* mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, item_kf->skeleton->num_shown_joints);

    if (mtx != NULL) {
        cKF_Si3_draw_R_SV(game, item_kf, mtx, NULL, NULL, NULL);
    }
}

static void mIV_pl_shape_item_draw_fan(Submenu* submenu, GAME* game) {
    int shape_idx = mIV_Get_player_item_shape_index(submenu->overlay->segment.player_item_anime_idx);
    Gfx* fan_gfx = (Gfx*)mPlib_Get_Item_DataPointer(shape_idx);

    if (fan_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPDisplayList(NEXT_POLY_OPA_DISP, fan_gfx);

        CLOSE_DISP(game->graph);
    }
}

static int mIV_pl_shape_after_draw(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                   u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 20: {
            Submenu* submenu = (Submenu*)arg;

            if (submenu->overlay->segment.player_item_anime_idx != mIV_ITEM_KIND_NUM) {
                Matrix_get(&submenu->overlay->inventory_ovl->item_mtx);
            }

            break;
        }

        case 16: {
            Submenu* submenu = (Submenu*)arg;

            if (submenu->overlay->segment.player_main_anime_idx == mIV_ANIM_EAT) {
                Matrix_get(&submenu->overlay->inventory_ovl->food_mtx);
            }

            break;
        }
    }

    return TRUE;
}

typedef void (*mIV_PL_EQUIP_ITEM_DRAW_PROC)(Submenu*, GAME*);

static void mIV_pl_equip_item_draw(Submenu* submenu, GAME* game) {
    // clang-format off
    static mIV_PL_EQUIP_ITEM_DRAW_PROC proc[mIV_ITEM_KIND_NUM] = {
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_net,
        &mIV_pl_shape_item_draw_umbrella,
        &mIV_pl_shape_item_draw_rod,
        &mIV_pl_shape_item_draw_scoop,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_net,
        &mIV_pl_shape_item_draw_rod,
        &mIV_pl_shape_item_draw_scoop,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_balloon,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_windmill,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_fan,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
        &mIV_pl_shape_item_draw_axe,
    };
    // clang-format on

    mSM_Segment_c* seg = &submenu->overlay->segment;

    if (seg->player_item_anime_idx != mIV_ITEM_KIND_NUM) {
        GRAPH* graph = game->graph;

        Matrix_put(&submenu->overlay->inventory_ovl->item_mtx);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        CLOSE_DISP(graph);

        (*proc[seg->player_item_anime_idx])(submenu, game);
    }
}

extern Gfx apple_DL_mode[];
extern Gfx nuts_DL_mode[];
extern Gfx pear_DL_mode[];
extern Gfx peach_DL_mode[];
extern Gfx orange_DL_mode[];
extern Gfx matutake_DL_mode[];
extern Gfx obj_item_cocoT_mat_model[];
extern Gfx kabu_DL_mode[];

extern Gfx apple_DL_vtx[];
extern Gfx nuts_DL_vtx[];
extern Gfx pear_DL_vtx[];
extern Gfx peach_DL_vtx[];
extern Gfx orange_DL_vtx[];
extern Gfx matutake_DL_vtx[];
extern Gfx obj_shop_candy_modelT[];
extern Gfx obj_item_cocoT_gfx_model[];
extern Gfx kabu_DL_vtx[];

static void mIV_pl_food_item_draw(Submenu* submenu, GAME* game) {
    // clang-format off
    static Gfx* food_mode[] = {
        apple_DL_mode,
        nuts_DL_mode,
        pear_DL_mode,
        peach_DL_mode,
        orange_DL_mode,
        matutake_DL_mode,
        NULL,
        obj_item_cocoT_mat_model,
        kabu_DL_mode,
    };
    // clang-format on

    // clang-format off
    static Gfx* food_model[] = {
        apple_DL_vtx,
        nuts_DL_vtx,
        pear_DL_vtx,
        peach_DL_vtx,
        orange_DL_vtx,
        matutake_DL_vtx,
        obj_shop_candy_modelT,
        obj_item_cocoT_gfx_model,
        kabu_DL_vtx,
    };
    // clang-format on

    if (submenu->overlay->segment.player_main_anime_idx == mIV_ANIM_EAT) {
        mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
        f32 cur_frame = inv_ovl->player_main_keyframe.frame_control.current_frame;
        f32 rate;
        GRAPH* graph = game->graph;
        int food_idx = inv_ovl->food_idx;
        MtxF* mtxf;
        f32 scale;
        f32 tmp;
        xyz_t l_ofs;
        xyz_t w_ofs;

        if (cur_frame < 3.0f || cur_frame >= 46.0f) {
            return;
        }

        if (cur_frame < 12.0f) {
            tmp = (cur_frame - 3.0f) * (1.0f / 9.0f);
            l_ofs.x = (tmp * 1.5f + 12.5f) * 100.0f;
            l_ofs.y = (tmp * 3.0f + 5.0f) * 100.0f;
            l_ofs.z = (tmp * -7.0f) * 100.0f;
        } else {
            tmp = (cur_frame - 12.0f) * (1.0f / 34.0f);
            l_ofs.x = (tmp * -5.0f + 14.0f) * 100.0f;
            l_ofs.y = (tmp * -11.75f + 8.0f) * 100.0f;
            l_ofs.z = (tmp * 6.0f + -7.0f) * 100.0f;
        }

        if (cur_frame < 27.0f) {
            scale = 1.0f;
        } else {
            scale = 1.0f - (cur_frame - 27.0f) * (1.0f / 19.0f);
        }

        scale *= 0.01f;

        _texture_z_light_fog_prim(graph);
        Matrix_put(&submenu->overlay->inventory_ovl->food_mtx);
        Matrix_Position(&l_ofs, &w_ofs);

        /* Update draw matrix */
        mtxf = get_Matrix_now();

        /* Scale */
        mtxf->xx = scale;
        mtxf->yy = scale;
        mtxf->zz = scale;

        mtxf->yx = 0.0f;
        mtxf->zx = 0.0f;
        mtxf->xy = 0.0f;
        mtxf->zy = 0.0f;
        mtxf->xz = 0.0f;
        mtxf->yz = 0.0f;

        /* Position */
        mtxf->xw = w_ofs.x;
        mtxf->yw = w_ofs.y - scale * 884.0f;
        mtxf->zw = w_ofs.z;

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (food_mode[food_idx] != NULL) {
            gSPDisplayList(NEXT_POLY_OPA_DISP, food_mode[food_idx]);
        }

        gSPDisplayList(NEXT_POLY_OPA_DISP, food_model[food_idx]);

        CLOSE_DISP(graph);
    }
}

static void mIV_pl_shape_draw(Submenu* submenu, GAME* game) {
    mSM_Segment_c* seg = &submenu->overlay->segment;
    cKF_SkeletonInfo_R_c* main_kf = &submenu->overlay->inventory_ovl->player_main_keyframe;
    GRAPH* graph = game->graph;
    N64Mtx* mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(graph, N64Mtx, main_kf->skeleton->num_shown_joints);
    u8* eye_tex_p = NULL;
    u8* mouth_tex_p = NULL;
    int anim_idx = mIV_Get_pl_main_anime_index(seg->player_main_anime_idx);
    u8* eye_tex_anim_p = mPlib_Get_PlayerEyeTexAnimation_p(anim_idx);
    u8* mouth_tex_anim_p = mPlib_Get_PlayerMouthTexAnimation_p(anim_idx);

    if (mtx != NULL) {
        OPEN_DISP(graph);

        if (eye_tex_anim_p != NULL || mouth_tex_anim_p != NULL) {
            cKF_FrameControl_c* frame_ctrl = &main_kf->frame_control;
            f32 cur_frame = frame_ctrl->current_frame;
            f32 max_frame = frame_ctrl->max_frames;

            if (1.0f <= cur_frame && cur_frame <= max_frame) {
                int tex_anim_idx = (int)(cur_frame - 1.0f);

                if (eye_tex_anim_p != NULL) {
                    eye_tex_p = mPlib_Get_eye_tex_p(eye_tex_anim_p[tex_anim_idx]);
                }

                if (mouth_tex_anim_p != NULL) {
                    mouth_tex_p = mPlib_Get_mouth_tex_p(mouth_tex_anim_p[tex_anim_idx]);
                }
            }
        }

        /* Load default textures if no animation */
        if (eye_tex_p == NULL) {
            eye_tex_p = mPlib_Get_eye_tex_p(0);
        }

        if (mouth_tex_p == NULL) {
            mouth_tex_p = mPlib_Get_mouth_tex_p(0);
        }

        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_LOAD);

        gDPPipeSync(NEXT_POLY_OPA_DISP);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        _texture_z_light_fog_prim(graph);

        /* Set dynamic player data */
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, eye_tex_p);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, mouth_tex_p);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, mPlib_get_player_tex_p(game));
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_B, mPlib_get_player_pallet_p(game));
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_C, mPlib_get_player_face_pallet_p(game));

        CLOSE_DISP(graph);

        /* Draw skeleton */
        cKF_Si3_draw_R_SV(game, main_kf, mtx, NULL, &mIV_pl_shape_after_draw, submenu);
        mIV_pl_equip_item_draw(submenu, game);
        mIV_pl_food_item_draw(submenu, game);
    }
}

extern Gfx ef_takurami01_menu_render_mode[];
extern Gfx ef_takurami01_kira_modelT[];

static void mIV_pl_eff_draw(GRAPH* graph, Submenu* submenu) {
    int i;
    mIV_pl_eff_c* pl_eff;

    _texture_z_light_fog_prim(graph);
    OPEN_DISP(graph);

    pl_eff = submenu->overlay->inventory_ovl->pl_eff;
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, ef_takurami01_menu_render_mode);
    for (i = 0; i < mIV_PLAYER_EFFECT_NUM; i++) {
        if (pl_eff->timer != 0) {
            Matrix_translate(pl_eff->pos.x, pl_eff->pos.y, pl_eff->pos.z, MTX_LOAD);
            Matrix_scale(pl_eff->scale, pl_eff->scale, pl_eff->scale, MTX_MULT);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(NEXT_POLY_OPA_DISP, ef_takurami01_kira_modelT);
        }

        pl_eff++;
    }

    CLOSE_DISP(graph);
}

extern Gfx ef_shadow_in_modelT[];

static void mIV_pl_shadow_draw(GAME_PLAY* play, ACTOR* actorx) {
    if (actorx != NULL) {
        GRAPH* graph = play->game.graph;

        Matrix_scale(actorx->shape_info.shadow_size_x * 0.001f, 1.0f, actorx->shape_info.shadow_size_z * 0.001f, MTX_LOAD);
        _texture_z_light_fog_prim(graph);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 255, 10, 0, 40, 150);
        gSPDisplayList(NEXT_POLY_OPA_DISP, ef_shadow_in_modelT);

        CLOSE_DISP(graph);
    }
}

static void mIV_set_player(Submenu* submenu, GRAPH* graph, GAME_PLAY* play, f32 pos_x, f32 pos_y) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        int x = (int)pos_x + 20;
        int y = (int)-pos_y + 9;
        /* NOTE: 128.0 and 0.0 are doubles here */
        int draw_flag = (128.0 + x >= 0.0) && (x < 320);

        OPEN_DISP(graph);

        gDPPipeSync(NEXT_POLY_OPA_DISP);

        CLOSE_DISP(graph);

        if (draw_flag) {
            submenu->overlay->change_view_proc(graph, 330.0f, 25.0f, x * 4.0f, y * 4.0f, 0x900, 256, 256);
        }

        mIV_pl_check_anm_change(submenu);
        if (draw_flag) {
            mIV_pl_shadow_draw(play, (ACTOR*)player);
            mIV_pl_shape_draw(submenu, (GAME*)play);
            mIV_pl_eff_draw(graph, submenu);
        }

        submenu->overlay->setup_view_proc(submenu, graph, FALSE);
    }
}

static void mIV_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static f32 mIV_page_move_accum = 0.0f;

static f32 mIV_page_pos_y(f32 timer) {
    return 100.0f * sinf_table(timer * 0.078539819f);
}

static void mIV_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mTG_Ovl_c* tag_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    if (menu_info->open_flag == FALSE) {
        int unselected_num;

        tag_ovl = submenu->overlay->tag_ovl;
        if (menu_info->data0 == mSM_IV_OPEN_SEND_MAIL) {
            for (unselected_num = 0; unselected_num < mPr_INVENTORY_MAIL_COUNT; unselected_num++) {
                if (inv_ovl->selectable_mail_bitfield & (1 << unselected_num)) {
                    break;
                }
            }

            if (unselected_num == mPr_INVENTORY_MAIL_COUNT) {
                unselected_num = 0;
            }
        } else {
            for (unselected_num = 0; unselected_num < mPr_POCKETS_SLOT_COUNT; unselected_num++) {
                if (inv_ovl->selectable_item_bitfield & (1 << unselected_num)) {
                    break;
                }
            }

            if (unselected_num == mPr_POCKETS_SLOT_COUNT) {
                unselected_num = 0;
            }
        }

        switch (menu_info->data0) {
            case mSM_IV_OPEN_NORMAL:
            case mSM_IV_OPEN_SELL:
            case mSM_IV_OPEN_GIVE:
            case mSM_IV_OPEN_TAKE:
            case mSM_IV_OPEN_PUTIN_FTR:
            case mSM_IV_OPEN_MINIDISK:
            case mSM_IV_OPEN_SHRINE:
            case mSM_IV_OPEN_CURATOR:
            case mSM_IV_OPEN_PASSWORD:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_ITEM, mTG_TYPE_NONE, unselected_num,
                                                             0.0f, 0.0f);
                break;
            case mSM_IV_OPEN_EXCHANGE:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_ITEM, mTG_TYPE_NONE, unselected_num,
                                                             0.0f, 0.0f);
                submenu->overlay->hand_ovl->info.pos[0] += -5.0f;
                submenu->overlay->hand_ovl->info.pos[1] += 12.0f;
                break;
            case mSM_IV_OPEN_QUEST:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_ITEM, mTG_TYPE_NONE, unselected_num,
                                                             0.0f, 0.0f);
                tag_ovl->item_name_wait_time = 0;
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_ITEM, mTG_TYPE_QUEST_ITEM, 0,
                                                             tag_ovl->tags[0].base_pos[0], tag_ovl->tags[0].base_pos[1]);
                break;
            case mSM_IV_OPEN_SEND_MAIL:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_MAIL, mTG_TYPE_NONE, unselected_num,
                                                             0.0f, 0.0f);
                break;
        }

        menu_info->open_flag = TRUE;
    } else if (inv_ovl->page_move_timer != 0) {
        int old_timer = inv_ovl->page_move_timer;
        int ticks = graph_dt_60hz_ticks(gamePT, &mIV_page_move_accum);
        int y;

        if (ticks > 0) {
            inv_ovl->page_move_timer -= ticks;
            if (inv_ovl->page_move_timer < 0) {
                inv_ovl->page_move_timer = 0;
            }
        }
        y = mIV_page_pos_y((f32)inv_ovl->page_move_timer);
        menu_info->position[1] = (f32)y;

        if (old_timer > 20 && inv_ovl->page_move_timer <= 20) {
            if (inv_ovl->page_order[2] == inv_ovl->next_page_id) {
                inv_ovl->page_order[2] = inv_ovl->page_order[1];
            }

            inv_ovl->page_order[1] = inv_ovl->page_order[0];
            inv_ovl->page_order[0] = inv_ovl->next_page_id;
        } else if (old_timer > 0 && inv_ovl->page_move_timer == 0) {
            menu_info->position[1] = 0.0f;
            submenu->overlay->hand_ovl->set_hand_func(submenu);
        }
    } else {
        ctrl->tag_move_func(submenu, menu_info);
    }
}

static void mIV_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu_info->menu_type == mSM_OVL_NEEDLEWORK) {
        mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

        mIV_pl_shape_move(submenu);
        ctrl->animation_flag = TRUE;
        if (inv_ovl->original_flag) {
            if (next_menu_info->proc_status == mSM_OVL_PROC_MOVE &&
                next_menu_info->next_proc_status == mSM_OVL_PROC_END) {
                submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
            }
        } else if (next_menu_info->proc_status == mSM_OVL_PROC_END) {
            mTG_Ovl_c* tag_ovl;
            mTG_tag_c* tag;
            int i;

            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            tag_ovl = submenu->overlay->tag_ovl;
            tag = tag_ovl->tags;

            for (i = 0; i < mTG_TAG_NUM; i++) {
                tag->type = mTG_TYPE_NONE;
                tag++;
            }

            tag_ovl->sel_tag_idx = -1;
            tag_ovl->ret_tag_idx = -1;
            inv_ovl->wc_flag = FALSE;

            submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_INVENTORY_WC_ORG, mTG_TYPE_NONE, 0, 0.0f,
                                                         0.0f);
            submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        }
    } else if (next_menu_info->proc_status == mSM_OVL_PROC_MOVE &&
               next_menu_info->next_proc_status == mSM_OVL_PROC_END) {
        submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_LEFT);
        submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
    }
}

static void mIV_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu_info->proc_status == mSM_OVL_PROC_MOVE) {
        if (next_menu_info->next_proc_status == mSM_OVL_PROC_END) {
            int move_dir;

            if (menu_info->data0 == mSM_IV_OPEN_CPMAIL) {
                move_dir = mSM_MOVE_OUT_LEFT;
                sAdo_SysTrgStart(NA_SE_31);
            } else {
                move_dir = mSM_MOVE_OUT_RIGHT;
            }

            submenu->overlay->move_chg_base_proc(menu_info, move_dir);
        } else {
            menu_info->position[0] = next_menu_info->position[0];
            menu_info->position[1] = next_menu_info->position[1];
        }
    }
}

static void mIV_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mBGMPsComp_pause(mBGM_PAUSE_STOP);
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mIV_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mIV_inventory_ovl_move(Submenu* submenu) {
    // clang-format off
    static mIV_OVL_MOVE_PROC ovl_move_proc[] = {
        &mIV_move_Move,
        &mIV_move_Play,
        &mIV_move_Wait,
        &mIV_move_Obey,
        &mIV_move_End,
    };
    // clang-format on

    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_INVENTORY];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

    switch (menu_info->proc_status) {
        case mSM_OVL_PROC_PLAY: {
            mIV_pl_shape_move(submenu);
            ctrl->animation_flag = TRUE;

            /**
             * Debug controls on controller #2
             *  - C stick left: +1,000 added to wallet
             *  - C stick right: fill all free inventory spaces with 30,000 bell bags
             *  - C stick down: fill first 4 free inventory slots with all tools
             */
            if (menu_info->data0 == mSM_IV_OPEN_NORMAL && ZURUMODE2_ENABLED() && zurumode_flag != 0) {
                if ((gamePT->pads[PAD1].on.button & BUTTON_CLEFT) == BUTTON_CLEFT) {
                    u32 wallet = Now_Private->inventory.wallet + 1000;

                    if (wallet > mPr_WALLET_MAX) {
                        wallet = mPr_WALLET_MAX;
                    }

                    Now_Private->inventory.wallet = wallet;
                    submenu->overlay->inventory_ovl->disp_money = wallet;
                }

                if ((gamePT->pads[PAD1].on.button & BUTTON_CDOWN) == BUTTON_CDOWN) {
                    int i;

                    for (i = 0; i < MONEY_NUM; i++) {
                        int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);

                        if (idx == -1) {
                            break;
                        }

                        mPr_SetPossessionItem(Now_Private, idx, ITM_TOOL_START + i, mPr_ITEM_COND_NORMAL);
                    }
                }

                if ((gamePT->pads[PAD1].on.button & BUTTON_CRIGHT) == BUTTON_CRIGHT) {
                    int i;

                    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                        int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);

                        if (idx == -1) {
                            break;
                        }

                        mPr_SetPossessionItem(Now_Private, idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                    }
                }
            }
            break;
        }

        case mSM_OVL_PROC_MOVE: {
            ctrl->animation_flag = FALSE;
            break;
        }
    }
}

extern Gfx inv_mwin_mode[];
extern Gfx inv_sakana_model[];
extern Gfx inv_mwin_model[];
extern Gfx inv_mushi_model[];
extern Gfx inv_sakana_part_model[];
extern Gfx inv_mushi_part_model[];
extern Gfx inv_sakana_scroll_mode[];
extern Gfx inv_mushi_scroll_mode[];

static void mIV_set_base_frame_dl(Submenu* submenu, GAME_PLAY* play, GRAPH* graph, int page, int scroll_flag, f32 pos_x,
                                  f32 pos_y) {
    static Gfx* base_frame[] = { inv_sakana_model, inv_mwin_model, inv_mushi_model };
    static Gfx* part_frame[] = { inv_sakana_part_model, inv_mwin_model, inv_mushi_part_model };
    static Gfx* scroll_set[] = { inv_sakana_scroll_mode, NULL, inv_mushi_scroll_mode };

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_mwin_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (scroll_flag) {
        int tex_x;
        int tex_y;

        if (page == mIV_PAGE_INVENTORY) {
            gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 14, 16, 1, mSM_Get_ground_pallet_p(play));
            gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, mSM_Get_ground_tex_p(play));
            gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, G_TX_RENDERTILE, 14, GX_REPEAT, GX_REPEAT,
                               GX_CLAMP, GX_CLAMP);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, scroll_set[page]);
        }

        gDPTileSync(POLY_OPA_DISP++);
        tex_x = (int)-submenu->overlay->menu_control.texture_pos[0] & 0x7F;
        tex_y = (int)-submenu->overlay->menu_control.texture_pos[1] & 0x7F;
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, tex_x, tex_y, tex_x + (31 << 2), tex_y + (31 << 2));
        gSPDisplayList(POLY_OPA_DISP++, base_frame[page]);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, part_frame[page]);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

/* letter slots */
extern Gfx inv_mwin_1aT_model[];
extern Gfx inv_mwin_2aT_model[];
extern Gfx inv_mwin_3aT_model[];
extern Gfx inv_mwin_4aT_model[];
extern Gfx inv_mwin_5aT_model[];
extern Gfx inv_mwin_6aT_model[];
extern Gfx inv_mwin_7aT_model[];
extern Gfx inv_mwin_8aT_model[];
extern Gfx inv_mwin_9aT_model[];
extern Gfx inv_mwin_10aT_model[];

/* item slots */
extern Gfx inv_mwin_1bT_model[];
extern Gfx inv_mwin_2bT_model[];
extern Gfx inv_mwin_3bT_model[];
extern Gfx inv_mwin_4bT_model[];
extern Gfx inv_mwin_5bT_model[];
extern Gfx inv_mwin_6bT_model[];
extern Gfx inv_mwin_7bT_model[];
extern Gfx inv_mwin_8bT_model[];
extern Gfx inv_mwin_9bT_model[];
extern Gfx inv_mwin_10bT_model[];
extern Gfx inv_mwin_11bT_model[];
extern Gfx inv_mwin_12bT_model[];
extern Gfx inv_mwin_13bT_model[];
extern Gfx inv_mwin_14bT_model[];
extern Gfx inv_mwin_15bT_model[];

extern Gfx inv_mwin_item_frame_mode[];
extern Gfx inv_mwin_kuni_model[];
extern Gfx inv_mwin_kuni2_model[];

static void mIV_set_normal_frame_dl(Submenu* submenu, GAME_PLAY* play, GRAPH* graph, f32 pos_x, f32 pos_y) {
    static Gfx* item_frame_disp[] = {
        inv_mwin_1bT_model,  inv_mwin_2bT_model,  inv_mwin_3bT_model,  inv_mwin_4bT_model,  inv_mwin_5bT_model,
        inv_mwin_6bT_model,  inv_mwin_7bT_model,  inv_mwin_8bT_model,  inv_mwin_9bT_model,  inv_mwin_10bT_model,
        inv_mwin_11bT_model, inv_mwin_12bT_model, inv_mwin_13bT_model, inv_mwin_14bT_model, inv_mwin_15bT_model,
    };

    static Gfx* letter_frame_disp[] = {
        inv_mwin_1aT_model, inv_mwin_2aT_model, inv_mwin_3aT_model, inv_mwin_4aT_model, inv_mwin_5aT_model,
        inv_mwin_6aT_model, inv_mwin_7aT_model, inv_mwin_8aT_model, inv_mwin_9aT_model, inv_mwin_10aT_model,
    };

    Gfx** frame_p;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int i;

    mIV_set_base_frame_dl(submenu, play, graph, mIV_PAGE_INVENTORY, TRUE, pos_x, pos_y);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_mwin_item_frame_mode);

    frame_p = item_frame_disp;
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        gDPPipeSync(POLY_OPA_DISP++);

        if ((inv_ovl->selectable_item_bitfield & (1 << i)) != 0) {
            gDPSetEnvColor(POLY_OPA_DISP++, 100, 100, 255, 255);
        } else {
            gDPSetEnvColor(POLY_OPA_DISP++, 120, 140, 255, 255);
        }

        gSPDisplayList(POLY_OPA_DISP++, *frame_p);
        frame_p++;
    }

    frame_p = letter_frame_disp;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        gDPPipeSync(POLY_OPA_DISP++);

        if ((inv_ovl->selectable_mail_bitfield & (1 << i)) != 0) {
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 60, 60, 255);
        } else {
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 90, 90, 255);
        }

        gSPDisplayList(POLY_OPA_DISP++, *frame_p);
        frame_p++;
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_mwin_kuni_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_mwin_kuni2_model);

    CLOSE_POLY_OPA_DISP(graph);
}

static int mIV_is_mark_check(mIV_Ovl_c* inv_ovl, int idx) {
    if ((inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
        return TRUE;
    }

    return FALSE;
}

extern Gfx inv_item_mode[];

static void mIV_set_item(Submenu* submenu, mSM_MenuInfo_c* menu_info, GRAPH* graph, f32 pos_x, f32 pos_y) {
    mIV_Ovl_c* inv_ovl;
    mActor_name_t* item;
    u8* scale_type;
    mTG_tag_c* tag;
    int i;
    int anim_frame;
    f32 hand_pos[2];
    f32 scale;
    int no_wc_flag;
    
    tag = &submenu->overlay->tag_ovl->tags[0];
    inv_ovl = submenu->overlay->inventory_ovl;
    item = Now_Private->inventory.pockets;
    scale_type = inv_ovl->item_scale_type;

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);

    CLOSE_POLY_OPA_DISP(graph);

    no_wc_flag = inv_ovl->wc_flag;
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item++, scale_type++) {
        if (*item != EMPTY_NO) {
            submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, hand_pos, mTG_TABLE_ITEM, i);
            if (tag->table == mTG_TABLE_ITEM) {
                switch (*scale_type) {
                    case mIV_ITEM_SCALE_TYPE_PRESENT: {
                        scale = 1.0f;

                        /* @fakematch -- why do I have to set this twice? */
                        if (inv_ovl->remove_timer != 0) {
                            anim_frame = 48 - inv_ovl->remove_timer;
                        } else {
                            anim_frame = 0;
                        }

                        anim_frame = (inv_ovl->remove_timer != 0 ? 48 - inv_ovl->remove_timer : 0);
                        break;
                    }

                    case mIV_ITEM_SCALE_TYPE_NONE: {
                        scale = 1.0f;
                        anim_frame = 0;
                        break;
                    }

                    case mIV_ITEM_SCALE_TYPE_SHRINK: {
                        scale = (f32)inv_ovl->remove_timer * (1.0f / 12.0f);
                        anim_frame = 70 - inv_ovl->remove_timer;

                        if (anim_frame >= 6) {
                            anim_frame = 5;
                        }
                        break;
                    }

                    default: {
                        scale =
                            1.0f - (f32)(inv_ovl->remove_timer - 14 - (*scale_type - mIV_ITEM_SCALE_TYPE_GROW) * 14) *
                                       (1.0f / 12.0f);
                        anim_frame = 0;
                        break;
                    }
                }

                if (scale > 1.0f) {
                    scale = 1.0f;
                } else if (scale < 0.0f) {
                    scale = 0.0f;
                }
            } else {
                scale = 1.0f;
                anim_frame = 0;
            }

            /* @BUG - they compare int (anim_frame) to float (0.0f) here instead of just 0 */
            if (*scale_type == mIV_ITEM_SCALE_TYPE_PRESENT && anim_frame != 0.0f) {
                submenu->overlay->draw_item_proc(graph, pos_x + hand_pos[0], pos_y + hand_pos[1], scale, *item, FALSE,
                                                 (inv_ovl->selectable_item_bitfield & (1 << i)), 0, FALSE, FALSE);
            }

            submenu->overlay->draw_item_proc(
                graph, pos_x + hand_pos[0], pos_y + hand_pos[1], scale, *item,
                (NowPrivate_GetItemCond(i) & mPr_ITEM_COND_PRESENT) != 0,
                !no_wc_flag && (inv_ovl->selectable_item_bitfield & (1 << i)), anim_frame, FALSE,
                mIV_is_mark_check(inv_ovl, i));
        }
    }
}

static void mIV_set_mail(Submenu* submenu, mSM_MenuInfo_c* menu_info, GRAPH* graph, f32 pos_x, f32 pos_y) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    Mail_c* mail = Now_Private->mail;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    u16 select_mask = 0;
    f32 scale;
    f32 pos[2];
    int i;
    int menu_flag;
    int mark_flag;

    if (inv_ovl->remove_timer > 0 && (tag->table == mTG_TABLE_MAIL || inv_ovl->mail_mark_flag == TRUE)) {
        if (inv_ovl->mail_mark_flag == TRUE) {
            select_mask = inv_ovl->mail_mark_bitfield2;
        } else if (inv_ovl->mail_mark_flag == FALSE) {
            select_mask = 1 << tag_ovl->get_table_idx_proc(tag);
        }
    }

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);

    CLOSE_POLY_OPA_DISP(graph);

    if (menu_info->data0 == mSM_IV_OPEN_CPMAIL) {
        pos_x -= -155.0f;
    }

    menu_flag = TRUE;
    if (menu_info->next_menu_type == mSM_OVL_NEEDLEWORK) {
        menu_flag = FALSE;
    }

    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++, mail++) {
        if ((inv_ovl->mail_mark_bitfield & (1 << i)) == 0 && mMl_check_not_used_mail(mail) != TRUE) {
            if ((select_mask & (1 << i)) != 0) {
                scale = (f32)inv_ovl->remove_timer * (1.0f / 24.0f);
            } else {
                scale = 1.0f;
            }

            if ((inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0 && inv_ovl->mail_mark_flag == FALSE) {
                mark_flag = TRUE;
            } else {
                mark_flag = FALSE;
            }

            submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, mTG_TABLE_MAIL, i);

            submenu->overlay->draw_mail_proc(graph, pos_x + pos[0], pos_y + pos[1], scale, mail,
                                             menu_flag && (inv_ovl->selectable_mail_bitfield & (1 << i)), FALSE,
                                             mark_flag);
        }
    }
}

static void mIV_set_money(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y) {
    u8 money_str[6];
    f32 width;

    mFont_UnintToString(money_str, sizeof(money_str), submenu->overlay->inventory_ovl->disp_money,
                        sizeof(money_str) - 1, FALSE, FALSE, TRUE);

    width = (f32)mFont_GetStringWidth(money_str, sizeof(money_str), TRUE) * 0.875f;
    pos_x = (160.0f + pos_x + -22.0f + 38.5f) - width;
    pos_y = 120.0f - (pos_y + 18.0f);

    // clang-format off
    mFont_SetLineStrings(
        game,
        money_str, sizeof(money_str),
        pos_x, pos_y,
        255, 60, 0, 255,
        FALSE,
        TRUE,
        0.875f, 0.875f,
        mFont_MODE_POLY
    );
    // clang-format on
}

typedef struct inventory_line_data_s {
    int max_str_len;
    f32 pos_x;
    f32 pos_y;
    f32 scale;
    rgba_t color;
    f32 max_width;
} mIV_line_data_c;

static void mIV_SetLineStrings_centering(GAME* game, u8* string, int type, f32 x, f32 y) {
    // clang-format off
    static mIV_line_data_c line_data[] = {
        {
            8,
            105.0f, 52.0f,
            0.875f,
            { 60, 80, 110, 255 },
            90.0f
        },

        {
            8,
            111.0f, 64.0f,
            0.9375f,
            { 70, 70, 100, 255 },
            90.0f
        },
    };
    // clang format on

    mIV_line_data_c* line_data_p = &line_data[type];
    f32 scale = line_data_p->scale;
    int len = mMl_strlen(string, line_data_p->max_str_len, CHAR_SPACE);
    f32 width = (f32)mFont_GetStringWidth(string, len, TRUE) * scale;
    f32 max_width = line_data_p->max_width;

    if (width > max_width) {
        width = max_width;
    }

    x += (max_width - width) * 0.5f;

    // clang-format off
    mFont_SetLineStrings(
        game,
        string, line_data_p->max_str_len,
        x + line_data_p->pos_x, -y + line_data_p->pos_y,
        line_data_p->color.r, line_data_p->color.g, line_data_p->color.b, line_data_p->color.a,
        FALSE,
        TRUE,
        scale, scale,
        mFont_MODE_POLY
    );
    // clang-format on
}

static f32 mIV_get_win_posY(Submenu* submenu, mSM_MenuInfo_c* menu_info, int page) {
    if (page == submenu->overlay->inventory_ovl->next_page_id) {
        return menu_info->position[1];
    } else {
        return -menu_info->position[1];
    }
}

static int mIV_up_page_draw_check(Submenu* submenu, int page) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    if (inv_ovl->page_move_timer > 20) {
        if (inv_ovl->next_page_id == page || inv_ovl->page_order[0] == page) {
            return TRUE;
        }
    } else if (inv_ovl->page_move_timer != 0) {
        if (inv_ovl->page_order[2] != page) {
            return TRUE;
        }
    } else if (inv_ovl->page_order[0] == page) {
        return TRUE;
    }

    return FALSE;
}

static void mIV_set_collect_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, int page) {
    GRAPH* graph = game->graph;
    mActor_name_t item;
    int i;
    f32 pos_x;
    f32 pos_y;
    int flag;
    f32 pos[2];

    if (menu_info->data0 == mSM_IV_OPEN_CPMAIL) {
        pos_x = menu_info->position[0] + -155.0f;
    } else {
        pos_x = menu_info->position[0];
    }

    pos_y = mIV_get_win_posY(submenu, menu_info, page);

    if (menu_info->data0 == mSM_IV_OPEN_NORMAL && mIV_up_page_draw_check(submenu, page)) {
        flag = TRUE;
    } else {
        flag = FALSE;
    }

    mIV_set_base_frame_dl(submenu, (GAME_PLAY*)game, graph, page, flag, pos_x, pos_y);
    if (flag) {
        OPEN_POLY_OPA_DISP(graph);

        gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);

        CLOSE_POLY_OPA_DISP(graph);

        for (i = 0; i < mIV_COLLECT_NUM; i++) {
            item = mIV_set_collect_itemNo(i, page);

            if (item != EMPTY_NO) {
                submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, mTG_TABLE_COLLECT, i);
                submenu->overlay->draw_item_proc(graph, pos_x + pos[0], pos_y + pos[1], 1.0f, item, FALSE, TRUE, 1,
                                                 FALSE, FALSE);
            }
        }
    }
}

static void mIV_set_normal_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    GRAPH* graph = game->graph;
    f32 pos_x;
    f32 pos_y;

    if (menu_info->data0 == mSM_IV_OPEN_CPMAIL) {
        pos_x = menu_info->position[0] + -155.0f;
    } else {
        pos_x = menu_info->position[0];
    }

    pos_y = mIV_get_win_posY(submenu, menu_info, mIV_PAGE_INVENTORY);
    mIV_set_normal_frame_dl(submenu, (GAME_PLAY*)game, graph, pos_x, pos_y);

    if (mIV_up_page_draw_check(submenu, mIV_PAGE_INVENTORY)) {
        mIV_set_item(submenu, menu_info, graph, pos_x, pos_y);
        mIV_set_mail(submenu, menu_info, graph, pos_x, pos_y);

        Matrix_push();
        mIV_set_player(submenu, graph, (GAME_PLAY*)game, pos_x, pos_y);
        Matrix_pull();

        submenu->overlay->set_char_matrix_proc(graph);
        mIV_SetLineStrings_centering(game, Now_Private->player_ID.land_name, mIV_STRING_LAND_NAME, pos_x, pos_y);
        mIV_SetLineStrings_centering(game, Now_Private->player_ID.player_name, mIV_STRING_PLAYER_NAME, pos_x, pos_y);
        mIV_set_money(submenu, game, pos_x, pos_y);
    }
}

static void mIV_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    u8* page_order = inv_ovl->page_order;
    int i;

    for (i = mIV_PAGE_INSECT_COLLECTION; i >= 0; i--) {
        if (page_order[i] == mIV_PAGE_INVENTORY) {
            mIV_set_normal_dl(submenu, menu_info, game);
        } else {
            mIV_set_collect_dl(submenu, menu_info, game, page_order[i]);
        }
    }

    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_INVENTORY);
}

static void mIV_inventory_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_INVENTORY];
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    f32 pos_y = menu_info->position[1];

    menu_info->pre_draw_func(submenu, game);
    if (inv_ovl->page_move_timer != 0 && mIV_page_move_accum > 0.0f) {
        f32 timer = (f32)inv_ovl->page_move_timer - mIV_page_move_accum;

        if (timer < 0.0f) {
            timer = 0.0f;
        }
        menu_info->position[1] = mIV_page_pos_y(timer);
    }
    mIV_set_dl(submenu, menu_info, game);
    menu_info->position[1] = pos_y;
}

extern void mIV_inventory_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_INVENTORY];

    overlay->menu_control.menu_move_func = &mIV_inventory_ovl_move;
    overlay->menu_control.menu_draw_func = &mIV_inventory_ovl_draw;

    if (overlay->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mIV_inventory_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME_PLAY* play) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    mActor_name_t dig_item = EMPTY_NO;
    int i;
    Mail_c* mail = Now_Private->mail;

    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mSM_MOVE_IN_RIGHT;
    i = 0;

    switch (menu_info->data0) {
        case mSM_IV_OPEN_HANIWA_TAKE: {
            inv_ovl->selectable_item_bitfield = 0;
            inv_ovl->selectable_mail_bitfield = 0;
            break;
        }

        case mSM_IV_OPEN_QUEST: {
            inv_ovl->selectable_item_bitfield |= 1 << menu_info->data1;
            inv_ovl->selectable_mail_bitfield = 0;
            break;
        }

        case mSM_IV_OPEN_PASSWORD: {
            inv_ovl->selectable_item_bitfield = menu_info->data1;
            inv_ovl->selectable_mail_bitfield = 0;
            break;
        }

        case mSM_IV_OPEN_SEND_MAIL: {
            inv_ovl->selectable_item_bitfield = 0;
            inv_ovl->selectable_mail_bitfield = 0;
            for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
                if (mMl_check_not_used_mail(mail) == FALSE && mMl_check_send_mail(mail)) {
                    inv_ovl->selectable_mail_bitfield |= 1 << i;
                }

                mail++;
            }
            break;
        }

        case mSM_IV_OPEN_MAILBOX: {
            inv_ovl->selectable_mail_bitfield = 0xFFFF;
            inv_ovl->selectable_item_bitfield = 0;
            break;
        }

        case mSM_IV_OPEN_CPMAIL: {
            inv_ovl->selectable_item_bitfield = 0;
            inv_ovl->selectable_mail_bitfield = 0;
            for (i; i < mPr_INVENTORY_MAIL_COUNT; i++) {
                if (mMl_check_not_used_mail(mail) || mMl_check_send_mail(mail) == FALSE) {
                    inv_ovl->selectable_mail_bitfield |= 1 << i;
                }

                mail++;
            }

            menu_info->move_drt = mSM_MOVE_IN_LEFT;
            break;
        }

        default: {
            inv_ovl->selectable_item_bitfield = mSM_check_open_inventory_itemlist(menu_info->data0, menu_info->data1);

            if (menu_info->data0 == mSM_IV_OPEN_NORMAL || menu_info->data0 == mSM_IV_OPEN_EXCHANGE) {
                inv_ovl->selectable_mail_bitfield = 0xFFFF;
            } else {
                inv_ovl->selectable_mail_bitfield = 0;
            }
            break;
        }
    }

    menu_info->next_proc_status = mSM_OVL_PROC_OBEY;

    if (menu_info->data0 == mSM_IV_OPEN_CPMAIL) {
        mSM_open_submenu(submenu, mSM_OVL_CPMAIL, 0, 0);
    } else if (menu_info->data0 == mSM_IV_OPEN_MAILBOX) {
        mSM_open_submenu(submenu, mSM_OVL_MAILBOX, 0, 0);
    } else if (menu_info->data0 == mSM_IV_OPEN_HANIWA_ENTRUST) {
        mSM_open_submenu(submenu, mSM_OVL_HANIWA, mSM_HANIWA_OPEN_ENTRUST, menu_info->data1);
    } else if (menu_info->data0 == mSM_IV_OPEN_HANIWA_TAKE) {
        mSM_open_submenu(submenu, mSM_OVL_HANIWA, mSM_HANIWA_OPEN_TAKE, menu_info->data1);
    } else {
        menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    }

    inv_ovl->disp_money = Now_Private->inventory.wallet;

    if (menu_info->data0 == mSM_IV_OPEN_EXCHANGE && ITEM_NAME_GET_TYPE(menu_info->data1) == NAME_TYPE_ITEM1 &&
        ITEM_NAME_GET_CAT(menu_info->data1) == ITEM1_CAT_FISH) {
        inv_ovl->release_flag = TRUE;
    } else {
        inv_ovl->release_flag = mCoBG_SearchWaterLimitDistN(&inv_ovl->release_pos, player->actor_class.world.position,
                                                            player->actor_class.shape_info.rotation.y, 120.0f, 12);
    }

    if (mPlib_Check_scoop_after((GAME*)play, &inv_ovl->shovel_pos, &dig_item, NULL, FALSE) ==
        mPlayer_INDEX_FILL_SCOOP) {
        inv_ovl->shovel_flag = TRUE;
    } else {
        inv_ovl->shovel_flag = FALSE;
    }

    inv_ovl->page_order[0] = mIV_PAGE_INVENTORY;
    inv_ovl->page_order[1] = mIV_PAGE_FISH_COLLECTION;
    inv_ovl->page_order[2] = mIV_PAGE_INSECT_COLLECTION;
    inv_ovl->page_move_timer = 0;
    inv_ovl->mail_mark_flag = FALSE;
    inv_ovl->item_mark_bitfield = 0;
    inv_ovl->mail_mark_bitfield2 = 0;
    inv_ovl->wc_flag = FALSE;

    if (menu_info->data0 == mSM_IV_OPEN_MAILBOX) {
        sAdo_SysTrgStart(SE_SINGLETON(NA_SE_ZOOMUP));
    } else {
        sAdo_SysTrgStart(NA_SE_MENU_PAUSE);
    }

    mBGMPsComp_pause(mBGM_PAUSE_1);
}

extern void mIV_inventory_ovl_construct(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_INVENTORY];
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    mIV_Ovl_c** inv_ovl_p = &submenu->overlay->inventory_ovl;

    if (*inv_ovl_p == NULL) {
        mem_clear((u8*)&inv_ovl_data, sizeof(mIV_Ovl_c), 0);
        *inv_ovl_p = &inv_ovl_data;
        mIV_pl_shape_init(submenu);
        mIV_pl_shape_move(submenu);
        mQst_ClearGrabItemInfo();
    }

    mIV_inventory_ovl_init(submenu, menu_info, play);
    mIV_inventory_ovl_set_proc(submenu);
    submenu->overlay->inventory_ovl->set_collect_itemNo_proc = &mIV_set_collect_itemNo;
}

extern void mIV_inventory_ovl_destruct(Submenu* submenu) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    cKF_SkeletonInfo_R_dt(&inv_ovl->player_main_keyframe);
    cKF_SkeletonInfo_R_dt(&inv_ovl->player_com_keyframe);
    cKF_SkeletonInfo_R_dt(&inv_ovl->item_keyframe);
    submenu->overlay->inventory_ovl = NULL;
}
