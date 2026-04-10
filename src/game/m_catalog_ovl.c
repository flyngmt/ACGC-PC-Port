#include "m_catalog_ovl.h"

#include "f_furniture.h"
#include "m_room_type.h"
#include "m_field_info.h"
#include "m_shop.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_play.h"
#include "m_rcp.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_common_data.h"
#include "m_malloc.h"

enum {
    mCL_DRAW_TYPE_FTR,
    mCL_DRAW_TYPE_PAPER,
    mCL_DRAW_TYPE_WALL,
    mCL_DRAW_TYPE_CARPET,
    mCL_DRAW_TYPE_MUSIC,

    mCL_DRAW_TYPE_NONE,
    mCL_DRAW_TYPE_NUM = mCL_DRAW_TYPE_NONE
};

typedef struct {
    u16 ftr_idx;
    s16 draw_type;
} mCL_ftr_info_c;

typedef struct {
    u16* idx_list_p;
    int list_size;
} mCL_item_info_c;

typedef struct {
    f32 scale;
    f32 pos_y;
} mCL_furniture_draw_data_c;

typedef struct {
    u16* win_pal;
    u8* win_tex;
    Gfx* sel_gfx0;
    Gfx* sel_gfx1;
} mCL_win_data_c;

#include "../src/actor/ac_furniture_profile_data.c_inc" /* furniture quality */
#include "../src/game/m_catalog_ovl_paper_data.c_inc"
#include "../src/game/m_catalog_ovl_data.c_inc"

#define mCL_ITEM_INFO(list) \
    { (list), ARRAY_COUNT(list) }

// clang-format off
static mCL_item_info_c mCL_item_idx_data[] = {
    { NULL, mCL_FTR_LIST_COUNT },
    mCL_ITEM_INFO(mCL_wall_idx_list),
    mCL_ITEM_INFO(mCL_carpet_idx_list),
    mCL_ITEM_INFO(mCL_cloth_idx_list),
    mCL_ITEM_INFO(mCL_umbrella_idx_list),
    mCL_ITEM_INFO(mCL_paper_idx_list),
    mCL_ITEM_INFO(mCL_haniwa_idx_list),
    mCL_ITEM_INFO(mCL_fossil_idx_list),
    mCL_ITEM_INFO(mCL_music_idx_list),
};
// clang-format on

extern u16 clg_win_ha_tex_rgb_ci4_pal[];
extern u8 clg_win_ha_tex_rgb_ci4[];
extern Gfx clg_win_haT_model[];
extern Gfx clg_win_ha2T_model[];
extern u16 clg_win_kabe_tex_rgb_ci4_pal[];
extern u8 clg_win_kabe_tex_rgb_ci4[];
extern Gfx clg_win_kabeT_model[];
extern Gfx clg_win_kabe2T_model[];
extern u16 clg_win_jyuutan_tex_rgb_ci4_pal[];
extern u8 clg_win_jyuutan_tex_rgb_ci4[];
extern Gfx clg_win_jyuutanT_model[];
extern Gfx clg_win_jyuutan2T_model[];
extern u16 clg_win_fuku_tex_rgb_ci4_pal[];
extern u8 clg_win_fuku_tex_rgb_ci4[];
extern Gfx clg_win_fukuT_model[];
extern Gfx clg_win_fuku2T_model[];
extern u16 clg_win_kasa_tex_rgb_ci4_pal[];
extern u8 clg_win_kasa_tex_rgb_ci4[];
extern Gfx clg_win_kasaT_model[];
extern Gfx clg_win_kasa2T_model[];
extern u16 clg_win_tegami_tex_rgb_ci4_pal[];
extern u8 clg_win_tegami_tex_rgb_ci4[];
extern Gfx clg_win_tegamiT_model[];
extern Gfx clg_win_tegami2T_model[];
extern u16 clg_win_hani_tex_rgb_ci4_pal[];
extern u8 clg_win_hani_tex_rgb_ci4[];
extern Gfx clg_win_haniwaT_model[];
extern Gfx clg_win_haniwa2T_model[];
extern u16 clg_win_hone_tex_rgb_ci4_pal[];
extern u8 clg_win_hone_tex_rgb_ci4[];
extern Gfx clg_win_honeT_model[];
extern Gfx clg_win_hone2T_model[];
extern u16 clg_win_onpu_tex_rgb_ci4_pal[];
extern u8 clg_win_onpu_tex_rgb_ci4[];
extern Gfx clg_win_onpuT_model[];
extern Gfx clg_win_onpu2T_model[];

// clang-format off
static mCL_win_data_c mCL_win_data[] = {
    {
        clg_win_ha_tex_rgb_ci4_pal,
        clg_win_ha_tex_rgb_ci4,
        clg_win_haT_model,
        clg_win_ha2T_model
    },
    {
        clg_win_kabe_tex_rgb_ci4_pal,
        clg_win_kabe_tex_rgb_ci4,
        clg_win_kabeT_model,
        clg_win_kabe2T_model
    },
    {
        clg_win_jyuutan_tex_rgb_ci4_pal,
        clg_win_jyuutan_tex_rgb_ci4,
        clg_win_jyuutanT_model,
        clg_win_jyuutan2T_model
    },
    {
        clg_win_fuku_tex_rgb_ci4_pal,
        clg_win_fuku_tex_rgb_ci4,
        clg_win_fukuT_model,
        clg_win_fuku2T_model
    },
    {
        clg_win_kasa_tex_rgb_ci4_pal,
        clg_win_kasa_tex_rgb_ci4,
        clg_win_kasaT_model,
        clg_win_kasa2T_model
    },
    {
        clg_win_tegami_tex_rgb_ci4_pal,
        clg_win_tegami_tex_rgb_ci4,
        clg_win_tegamiT_model,
        clg_win_tegami2T_model
    },
    {
        clg_win_hani_tex_rgb_ci4_pal,
        clg_win_hani_tex_rgb_ci4,
        clg_win_haniwaT_model,
        clg_win_haniwa2T_model
    },
    {
        clg_win_hone_tex_rgb_ci4_pal,
        clg_win_hone_tex_rgb_ci4,
        clg_win_honeT_model,
        clg_win_hone2T_model
    },
    {
        clg_win_onpu_tex_rgb_ci4_pal,
        clg_win_onpu_tex_rgb_ci4,
        clg_win_onpuT_model,
        clg_win_onpu2T_model
    },
};
// clang-format on

static u8 not_sell[12] = "Not for Sale";

static void mCL_dma_furniture_program(mCL_Item_c* item) {
    item->profile = furniture_quality[item->ftr_actor.name];
}

static void mCL_dma_furniture_bank(mCL_Item_c* item, mActor_name_t item_no) {
    aFTR_PROFILE* profile = item->profile;

    if (profile->vtable != NULL && profile->vtable->dma_proc != NULL) {
        profile->vtable->dma_proc(item_no, item->seg1);
    }
}

static void mCL_furniture_init(mCL_Item_c* item, mActor_name_t item_no) {
    // clang-format off
    static mCL_furniture_draw_data_c furniture_draw_data[] = {
        { 0.90f, -3.0f },
        { 0.90f, -8.0f },
        { 0.85f, -3.0f },
        { 0.87f, -3.0f },
        { 0.90f, 0.0f },
        { 0.82f, -9.0f },
        { 0.82f, -5.0f },
        { 0.90f, -6.0f },
        { 0.90f, -7.0f },
        { 0.76f, -3.0f },
        { 0.77f, -25.0f },
        { 0.83f, -27.0f },
        { 0.90f, -10.0f },
        { 0.90f, -13.0f },
        { 0.86f, -20.0f },
        { 0.82f, -25.0f },
        { 0.69f, -6.0f },
        { 0.90f, -10.0f },
        { 0.49f, -29.0f },
        { 0.86f, -3.0f },
        { 0.65f, -3.0f },
        { 0.88f, -3.0f },
        { 0.78f, -3.0f },
        { 0.89f, -12.0f },
        { 0.85f, -3.0f },
        { 0.90f, -6.0f },
        { 0.89f, -9.0f },
        { 0.82f, -14.0f },
        { 0.84f, -3.0f },
        { 0.87f, -5.0f },
        { 0.74f, -3.0f },
        { 0.78f, -13.0f },
        { 0.72f, -3.0f },
        { 0.85f, -15.0f },
        { 0.81f, -3.0f },
        { 0.78f, -9.0f },
        { 0.77f, -3.0f },
        { 0.83f, -3.0f },
        { 0.86f, -6.0f },
        { 0.82f, -3.0f },
        { 0.82f, -30.0f },
    };
    // clang-format on

    aFTR_PROFILE* profile;
    FTR_ACTOR* ftr_actor;

    item->gfx_type = mCL_DRAW_TYPE_FTR;
    item->ftr_actor.name = mRmTp_FtrItemNo2FtrIdx(item_no);
    mCL_dma_furniture_program(item);
    mCL_dma_furniture_bank(item, item_no);

    ftr_actor = &item->ftr_actor;
    profile = item->profile;

    ftr_actor->tex_animation.frame = 0;
    ftr_actor->switch_bit = TRUE;

    if (profile->shape == aFTR_SHAPE_TYPEB_90) {
        ftr_actor->position.x = 0.0f;
        ftr_actor->position.z = -mFI_UT_WORLDSIZE_HALF_Z_F;
    } else if (profile->shape == aFTR_SHAPE_TYPEB_180) {
        ftr_actor->position.x = mFI_UT_WORLDSIZE_HALF_X_F;
        ftr_actor->position.z = 0.0f;
    } else if (profile->shape == aFTR_SHAPE_TYPEB_270) {
        ftr_actor->position.x = 0.0f;
        ftr_actor->position.z = mFI_UT_WORLDSIZE_HALF_Z_F;
    } else if (profile->shape == aFTR_SHAPE_TYPEB_0) {
        ftr_actor->position.x = -mFI_UT_WORLDSIZE_HALF_X_F;
        ftr_actor->position.z = 0.0f;
    } else {
        ftr_actor->position.x = 0.0f;
        ftr_actor->position.z = 0.0f;
    }

    ftr_actor->angle_y = 0.0f;
    ftr_actor->keyframe.skeleton = NULL;
    ftr_actor->keyframe.animation = NULL;
    item->timer = 15;

    if (profile->rig != NULL) {
        cKF_SkeletonInfo_R_ct(&ftr_actor->keyframe, profile->rig->skeleton, profile->rig->animation, ftr_actor->joint,
                              ftr_actor->morph);
        cKF_SkeletonInfo_R_init_standard_repeat(&ftr_actor->keyframe, profile->rig->animation, NULL);
        cKF_SkeletonInfo_R_play(&ftr_actor->keyframe);
        ftr_actor->keyframe.frame_control.speed = 0.5f;
    }

    if (profile->vtable != NULL && profile->vtable->ct_proc != NULL) {
        profile->vtable->ct_proc(ftr_actor, item->seg1);

        if (ftr_actor->keyframe.skeleton != NULL && ftr_actor->keyframe.animation != NULL) {
            ftr_actor->keyframe.frame_control.speed = 0.5f;
        }
    }

    if (item_no >= HANIWA_START && item_no <= HANIWA_END) {
        item->pos_y = 38.0f;
        item->scale = 1.0f;
        ftr_actor->position.y = -7.0f;
        item->price = 0;
    } else if (item_no >= FTR_CLOTH_START && item_no <= FTR_CLOTH_END) {
        mActor_name_t cloth_item;

        item->pos_y = 38.0f;
        item->scale = 1.0f;
        ftr_actor->position.y = -4.0f;
        cloth_item = mRmTp_FtrItemNo2Item1ItemNo(item_no, FALSE);

        if (mSP_SearchItemCategoryPriority(cloth_item, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, NULL) ||
            mSP_SearchItemCategoryPriority(cloth_item, mSP_KIND_CLOTH, mSP_LISTTYPE_UNCOMMON, NULL) ||
            mSP_SearchItemCategoryPriority(cloth_item, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, NULL)) {
            item->price = mSP_ItemNo2ItemPrice(cloth_item);
        } else {
            item->price = 0;
        }
    } else if (item_no >= FTR_UMBRELLA_START && item_no <= FTR_UMBRELLA_END) {
        item->pos_y = 36.0f;
        item->scale = 1.0f;
        ftr_actor->position.y = 0.0f;
        item->price = mSP_ItemNo2ItemPrice(item_no);
    } else if ((mRmTp_FtrItemNo2FtrIdx(item_no) >= 0x3FC && mRmTp_FtrItemNo2FtrIdx(item_no) <= 0x403) ||
               (item_no >= FTR_START(FTR_NOG_COLLEGENOTE) && item_no <= FTR_END(FTR_IKE_NIKKI_WAFU1)) ||
               (mRmTp_FtrItemNo2FtrIdx(item_no) >= 0x453 && mRmTp_FtrItemNo2FtrIdx(item_no) <= 0x45A) ||
               (mRmTp_FtrItemNo2FtrIdx(item_no) >= 0x45B && mRmTp_FtrItemNo2FtrIdx(item_no) <= 0x462) ||
               (mRmTp_FtrItemNo2FtrIdx(item_no) >= 0x44F && mRmTp_FtrItemNo2FtrIdx(item_no) <= 0x452) ||
               (mRmTp_FtrItemNo2FtrIdx(item_no) >= 0x463 && mRmTp_FtrItemNo2FtrIdx(item_no) <= 0x466)) {
        item->pos_y = 36.0f;
        item->scale = 1.0f;
        ftr_actor->position.y = 0.0f;
        item->price = mSP_ItemNo2ItemPrice(item_no);
    } else if (item_no >= FTR_DINO_START && item_no <= FTR_DINO_END) {
        item->pos_y = 45.0f;

        if (item_no == FTR_START(FTR_DIN_BRONT_HEAD)) {
            item->scale = 0.5f;
            ftr_actor->position.y = -mFI_UNIT_BASE_SIZE_F;
        } else {
            item->scale = 0.65f;
            ftr_actor->position.y = 0.0f;
        }

        item->price = 0;
    } else {
        mCL_ftr_info_c* ftr_info = mCL_furniture_list;
        int i;

        item->pos_y = 42.0f;
        for (i = 0; i < mCL_FTR_LIST_COUNT; i++, ftr_info++) {
            if (ftr_info->ftr_idx == ftr_actor->name) {
                ftr_actor->position.y = furniture_draw_data[ftr_info->draw_type].pos_y;
                item->scale = furniture_draw_data[ftr_info->draw_type].scale;
                break;
            }
        }

        if (i == mCL_FTR_LIST_COUNT) {
            /* Default to first entry */
            ftr_actor->position.y = furniture_draw_data[0].pos_y;
            item->scale = furniture_draw_data[0].scale;
        }

        if (mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_COMMON, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_UNCOMMON, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_TRAIN, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENT, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, NULL) ||
            mSP_SearchItemCategoryPriority(item_no, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENTPRESENTCHUMON, NULL)) {
            item->price = mSP_ItemNo2ItemPrice(item_no);
        } else {
            item->price = 0;
        }
    }
}

static void mCL_paper_init(mCL_Item_c* item, mActor_name_t item_no) {
    item->gfx_type = mCL_DRAW_TYPE_PAPER;
    item->profile = NULL;
    item->ftr_actor.name = (item_no - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
    item->pos_y = -93.0f;
    item->scale = 0.28f;

    if (mSP_SearchItemCategoryPriority(item_no, mSP_KIND_PAPER, mSP_LISTTYPE_COMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_PAPER, mSP_LISTTYPE_UNCOMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_PAPER, mSP_LISTTYPE_RARE, NULL)) {
        item->price = mSP_ItemNo2ItemPrice(item_no);
    } else {
        item->price = 0;
    }
}

static void mCL_wall_init(mCL_Item_c* item, mActor_name_t item_no) {
    item->gfx_type = mCL_DRAW_TYPE_WALL;
    item->profile = NULL;
    item->ftr_actor.name = (item_no - ITM_WALL_START);
    item->pos_y = -90.0f;
    item->scale = 0.54f;
    item->seg_ofs = (item_no - ITM_WALL_START) * (mNW_PALETTE_SIZE + 0x1000);

    mRmTp_CopyWallData(item->seg1, item_no - ITM_WALL_START);
    if (mSP_SearchItemCategoryPriority(item_no, mSP_KIND_WALLPAPER, mSP_LISTTYPE_COMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_WALLPAPER, mSP_LISTTYPE_UNCOMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_WALLPAPER, mSP_LISTTYPE_RARE, NULL)) {
        item->price = mSP_ItemNo2ItemPrice(item_no);
    } else {
        item->price = 0;
    }
}

static void mCL_carpet_init(mCL_Item_c* item, mActor_name_t item_no) {
    item->gfx_type = mCL_DRAW_TYPE_CARPET;
    item->profile = NULL;
    item->ftr_actor.name = (item_no - ITM_CARPET_START);
    item->pos_y = -90.0f;
    item->scale = 0.54f;
    item->seg_ofs = (item_no - ITM_CARPET_START) * (mNW_PALETTE_SIZE + 0x2000);

    mRmTp_CopyFloorData(item->seg1, item_no - ITM_CARPET_START);
    if (mSP_SearchItemCategoryPriority(item_no, mSP_KIND_CARPET, mSP_LISTTYPE_COMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_CARPET, mSP_LISTTYPE_UNCOMMON, NULL) ||
        mSP_SearchItemCategoryPriority(item_no, mSP_KIND_CARPET, mSP_LISTTYPE_RARE, NULL)) {
        item->price = mSP_ItemNo2ItemPrice(item_no);
    } else {
        item->price = 0;
    }
}

static void mCL_music_init(mCL_Item_c* item, mActor_name_t item_no) {
    item->profile = NULL;
    item->gfx_type = mCL_DRAW_TYPE_MUSIC;
    item->price = 0;
    item->timer = 60;
    item->scale = 0.55f;
    item->pos_y = -90.0f;
    item->ftr_actor.name = (item_no - ITM_MINIDISK_START);
}

static void mCL_item_data_set(Submenu* submenu, int page_no) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    mCL_Menu_c* page = &catalog_ovl->menu_data[page_no];
    mActor_name_t item_no;
    mCL_Item_c* item;
    mActor_name_t* item_list;
    u8* item_name;
    int i;

    catalog_ovl->item_data_idx ^= 1;
    item = &catalog_ovl->item_data[catalog_ovl->item_data_idx];
    item_no = page->item_list[page->top_idx + page->y_idx];
    item->item_no = item_no;

    if (ITEM_IS_FTR(item_no)) {
        mCL_furniture_init(item, item_no);
    } else if (ITEM_IS_ITEM1(item_no)) {
        int cat = ITEM_NAME_GET_CAT(item_no);

        xyz_t_move(&item->ftr_actor.position, &ZeroVec);

        if (cat == ITEM1_CAT_PAPER) {
            mCL_paper_init(item, item_no);
        } else if (cat == ITEM1_CAT_WALL) {
            mCL_wall_init(item, item_no);
        } else if (cat == ITEM1_CAT_CARPET) {
            mCL_carpet_init(item, item_no);
        } else if (cat == ITEM1_CAT_MINIDISK) {
            mCL_music_init(item, item_no);
        } else {
            item->gfx_type = mCL_DRAW_TYPE_NONE;
            item->price = 0;
        }
    } else {
        item->gfx_type = mCL_DRAW_TYPE_NONE;
        item->price = 0;
    }

    item_name = (u8*)page->item_name;
    item_list = &page->item_list[page->top_idx];
    for (i = 0; i < mCL_MENU_PAGE_SIZE; i++) {
        mIN_copy_name_str(item_name, *item_list);
        item_list++;
        item_name += mIN_ITEM_NAME_LEN;
    }
}

static void mCL_item_move(mCL_Ovl_c* catalog_ovl) {
    mCL_Item_c* item = catalog_ovl->item_data;
    int i;

    for (i = 0; i < mCL_ITEM_DATA_NUM; i++) {
        if (item->gfx_type == 0) {
            aFTR_tex_anim_c* tex_anim;
            aFTR_PROFILE* profile = item->profile;
            cKF_SkeletonInfo_R_c* keyframe = &item->ftr_actor.keyframe;

            if (profile != NULL) {
                tex_anim = profile->tex_anim;

                if (tex_anim != NULL) {
                    int count = tex_anim->animation_count;

                    item->ftr_actor.tex_animation.frame++;
                    if (item->ftr_actor.tex_animation.frame >= count || item->ftr_actor.tex_animation.frame < 0) {
                        item->ftr_actor.tex_animation.frame = 0;
                    }
                }
            }

            if (profile->rig != NULL || (keyframe->skeleton != NULL && keyframe->animation != NULL)) {
                if (cKF_SkeletonInfo_R_play(keyframe) == cKF_STATE_STOPPED) {
                    if (item->timer != 0) {
                        item->timer--;
                    } else {
                        /* Animation is ready to be played in the opposite direction */
                        f32 tmp;

                        item->timer = 15;
                        tmp = keyframe->frame_control.start_frame;
                        keyframe->frame_control.start_frame = keyframe->frame_control.end_frame;
                        keyframe->frame_control.end_frame = tmp;
                    }
                }
            }

            item->ftr_actor.angle_y += 1.25f; /* Step rotation */

            if (item->ftr_actor.angle_y > 360.0f) {
                item->ftr_actor.angle_y -= 360.0f;
            }
        } else if (item->gfx_type == 4) {
            item->timer--;
            item->pos_y = -90.0f + sin_s(item->timer * DEG2SHORT_ANGLE(6.0f)) * 6.0f;
            item->ftr_actor.position.x = sin_s(item->timer * DEG2SHORT_ANGLE(3.0f)) * 6.0f;
        }

        item++;
    }
}

static void mCL_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mCL_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;

    if (menu_info->open_flag == FALSE) {
        menu_info->open_flag = TRUE;
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, 14, 0, 0, 0.0f, 0.0f);
    } else if (catalog_ovl->page_timer != 0) {
        catalog_ovl->page_timer--;
        menu_info->position[1] = 100.0f * sinf_table((f32)catalog_ovl->page_timer * 0.078539819f); // needs macro?

        if (catalog_ovl->page_timer == 20) {
            u8* page_order = catalog_ovl->page_order;
            int i;

            for (i = 0; i < mCL_MENU_NUM; i++, page_order++) {
                if (*page_order == catalog_ovl->page_no) {
                    break;
                }
            }

            for (i; i > 0; i--) {
                page_order[0] = page_order[-1];
                page_order--;
            }

            catalog_ovl->page_order[0] = catalog_ovl->page_no;
        } else if (catalog_ovl->page_timer == 0) {
            menu_info->position[1] = 0.0f;
            submenu->overlay->hand_ovl->set_hand_func(submenu);
        }

        mCL_item_move(catalog_ovl);
    } else {
        submenu->overlay->menu_control.tag_move_func(submenu, menu_info);

        if (catalog_ovl->change_flag) {
            catalog_ovl->menu_data[catalog_ovl->page_order[0]].y_idx = submenu->overlay->tag_ovl->tags[0].tag_row;
            mCL_item_data_set(submenu, catalog_ovl->page_order[0]);
            catalog_ovl->change_flag = FALSE;
        } else {
            if (catalog_ovl->page_timer == 40) {
                mCL_item_data_set(submenu, catalog_ovl->page_no);
            } else {
                mCL_item_move(catalog_ovl);
            }
        }
    }
}

static void mCL_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mCL_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mCL_catalog_ovl_move(Submenu* submenu) {
    static mCL_OVL_MOVE_PROC ovl_move_proc[] = {
        &mCL_move_Move, &mCL_move_Play, (mCL_OVL_MOVE_PROC)none_proc1, (mCL_OVL_MOVE_PROC)none_proc1, mCL_move_End,
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CATALOG];
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

    catalog_ovl->counter = (catalog_ovl->counter + 1) % 35;
    if (catalog_ovl->counter < 17) {
        catalog_ovl->alpha = ((f32)catalog_ovl->counter * 255.0f) / 17.0f;
    } else {
        catalog_ovl->alpha = ((f32)(35 - catalog_ovl->counter) * 255.0f) / 18.0f;
    }
}

static void mCL_LoadTexturePal(aFTR_PROFILE* profile, GAME* game) {
    OPEN_DISP(game->graph);

    if (profile->opaque0 != NULL || profile->opaque1 != NULL || profile->rig != NULL) {
        if (profile->texture != NULL) {
            gDPLoadTextureBlockS(NEXT_POLY_OPA_DISP, profile->texture, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0,
                                 G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 7, 7, G_TX_NOLOD, G_TX_NOLOD);
        }

        if (profile->palette != NULL) {
            gDPLoadTLUT_pal16(NEXT_POLY_OPA_DISP, 15, profile->palette);
        }
    }

    if (profile->translucent0 != NULL || profile->translucent1 != NULL || profile->rig != NULL) {
        if (profile->texture != NULL) {
            gDPLoadTextureBlockS(NEXT_POLY_XLU_DISP, profile->texture, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0,
                                 G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 7, 7, G_TX_NOLOD, G_TX_NOLOD);
        }

        if (profile->palette != NULL) {
            gDPLoadTLUT_pal16(NEXT_POLY_XLU_DISP, 15, profile->palette);
        }
    }

    CLOSE_DISP(game->graph);
}

static void mCL_SetKankyoMapping(aFTR_PROFILE* profile, GAME_PLAY* play) {
    static xyz_t light_direction = { 0.0f, 60.0f, 60.0f };
    static xyz_t obj_pos = { 0.0f, 25.0f, 0.0f };
    xyz_t eye_pos;

    eye_pos.x = 0.0f;
    eye_pos.y = 25.0f + sin_s(0x900) * 330.0f;
    eye_pos.z = cos_s(0x900) * 330.0f;

    if (profile->kankyo_map == aFTR_KANKYO_MAP_OPA) {
        HiliteReflect_init(&obj_pos, &eye_pos, &light_direction, play->game.graph);
    } else if (profile->kankyo_map == aFTR_KANKYO_MAP_XLU) {
        HiliteReflect_xlu_init(&obj_pos, &eye_pos, &light_direction, play->game.graph);
    }
}

static void mCL_SetLoopTextureAnime(mCL_Item_c* item, aFTR_PROFILE* profile, GAME* game) {
    aFTR_tex_anim_c* tex_anime = profile->tex_anim;

    if (tex_anime != NULL) {
        u8* tex_p = tex_anime->animation[item->ftr_actor.tex_animation.frame];

        OPEN_DISP(game->graph);

        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex_p);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, tex_p);

        CLOSE_DISP(game->graph);
    }
}

static void mCL_DrawRegistModel(aFTR_PROFILE* profile, GAME* game) {
    OPEN_DISP(game->graph);

    if (profile->opaque0 != NULL) {
        gSPDisplayList(NEXT_POLY_OPA_DISP, profile->opaque0);
    }

    if (profile->opaque1 != NULL) {
        gSPDisplayList(NEXT_POLY_OPA_DISP, profile->opaque1);
    }

    if (profile->translucent0 != NULL) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, profile->translucent0);
    }

    if (profile->translucent1 != NULL) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, profile->translucent1);
    }

    CLOSE_DISP(game->graph);
}

static void mCL_DrawSkelShape(mCL_Item_c* item, aFTR_PROFILE* profile, GAME* game) {
    if (profile->rig != NULL) {
        cKF_SkeletonInfo_R_c* keyframe = &item->ftr_actor.keyframe;
        int mtx_idx = game->frame_counter & 1;
        Mtx* mtx = item->ftr_actor.skeleton_mtx[mtx_idx];

        cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
    }
}

static void mCL_DrawUniqueShape(mCL_Item_c* item, aFTR_PROFILE* profile, GAME* game) {
    if (profile->vtable != NULL && profile->vtable->draw_proc != NULL) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        CLOSE_DISP(game->graph);

        profile->vtable->draw_proc(&item->ftr_actor, NULL, game, item->seg1);
    }
}

static void mCL_furniture_draw(mCL_Item_c* item, GAME* game) {
    // clang-format off
    static Lights0 light_data = {
        105, 90, 90,
        0,
        105, 90, 90,
        0,

        255, 255, 245,
        0,
        255, 255, 245,
        0,
        0, 60, 60,
        0,
    };
    // clang-format on

    aFTR_PROFILE* profile;
    FTR_ACTOR* ftr_actor;
    Gfx* xlu_main;
    Gfx* xlu_first;
    int edge_alpha;
    f32 scale;

    profile = item->profile;
    ftr_actor = &item->ftr_actor;

    OPEN_DISP(game->graph);
    xlu_main = NOW_POLY_XLU_DISP;
    NEXT_POLY_XLU_DISP;
    xlu_first = NOW_POLY_XLU_DISP;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    edge_alpha = aMR_GetAlphaEdge(ftr_actor->name);

    gDPSetTexEdgeAlpha(NEXT_POLY_OPA_DISP, edge_alpha);
    gDPSetTexEdgeAlpha(NEXT_POLY_XLU_DISP, edge_alpha);

    if (aMR_DrawDolphinMode(ftr_actor->name)) {
        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);
    } else {
        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);
    }

    gSPSetLights0(NEXT_POLY_OPA_DISP, light_data);
    gSPSetLights0(NEXT_POLY_XLU_DISP, light_data);

    mCL_LoadTexturePal(profile, game);
    mCL_SetKankyoMapping(profile, (GAME_PLAY*)game);

    scale = item->scale;
    Matrix_RotateY(RAD2SHORT_ANGLE2(DEG2RAD(ftr_actor->angle_y)), MTX_LOAD);
    Matrix_scale(scale, scale, scale, MTX_MULT);
    Matrix_translate(ftr_actor->position.x, ftr_actor->position.y, ftr_actor->position.z, MTX_MULT);
    Matrix_scale(profile->scale, profile->scale, profile->scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    mCL_SetLoopTextureAnime(item, profile, game);
    mCL_DrawRegistModel(profile, game);
    mCL_DrawSkelShape(item, profile, game);
    mCL_DrawUniqueShape(item, profile, game);

    gSPEndDisplayList(NEXT_POLY_XLU_DISP);
    gSPBranchList(xlu_main, NOW_POLY_XLU_DISP);
    gSPDisplayList(NEXT_POLY_OPA_DISP, xlu_first);

    gDPSetTexEdgeAlpha(NEXT_POLY_OPA_DISP, 144);
    gDPSetTexEdgeAlpha(NEXT_POLY_XLU_DISP, 144);

    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);

    CLOSE_DISP(game->graph);
}

extern Gfx mCL_lat_letter_sen_mode[];

static void mCL_paper_draw(mCL_Item_c* item, mSM_MenuInfo_c* menu_info, GRAPH* graph) {
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPDisplayList(gfx++, paper_disp_model[item->ftr_actor.name]);

    if (paper_disp_sen_model[item->ftr_actor.name] != NULL) {
        gSPDisplayList(gfx++, mCL_lat_letter_sen_mode);
        gSPDisplayList(gfx++, paper_disp_sen_model[item->ftr_actor.name]);
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx mCL_rom_myhome1_wall_model[];

static void mCL_wall_draw(mCL_Item_c* item, mSM_MenuInfo_c* menu_info, GRAPH* graph) {
    u8* wall_p = item->seg1;
    u8* tex0 = wall_p + mNW_PALETTE_SIZE;
    u8* tex1 = wall_p + mNW_PALETTE_SIZE + 0x800;
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_A, wall_p); /* palette */
    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex0);   /* texture 0 */
    gSPSegment(gfx++, G_MWO_SEGMENT_9, tex1);   /* texture 1 */
    gSPDisplayList(gfx++, mCL_rom_myhome1_wall_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx mCL_rom_myhome1_floor_model[];

static void mCL_carpet_draw(mCL_Item_c* item, mSM_MenuInfo_c* menu_info, GRAPH* graph) {
    u8* floor_p = item->seg1;
    u8* tex0 = floor_p + mNW_PALETTE_SIZE;
    u8* tex1 = floor_p + mNW_PALETTE_SIZE + 0x800;
    u8* tex2 = floor_p + mNW_PALETTE_SIZE + 0x1000;
    u8* tex3 = floor_p + mNW_PALETTE_SIZE + 0x1800;
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_D, floor_p); /* palette */
    gSPSegment(gfx++, G_MWO_SEGMENT_8, tex0);    /* texture 0 */
    gSPSegment(gfx++, G_MWO_SEGMENT_9, tex1);    /* texture 1 */
    gSPSegment(gfx++, G_MWO_SEGMENT_A, tex2);    /* texture 2 */
    gSPSegment(gfx++, G_MWO_SEGMENT_B, tex3);    /* texture 3 */
    gSPDisplayList(gfx++, mCL_rom_myhome1_floor_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx mCL_music_model[];

static void mCL_music_draw(mCL_Item_c* item, mSM_MenuInfo_c* menu_info, GRAPH* graph) {
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    Matrix_RotateZ(cos_s(item->timer * 0x222) * 0x1000, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, mCL_music_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx mCL_lat_letter_mode[];
typedef void (*mCL_ITEM_DRAW_PROC)(mCL_Item_c*, mSM_MenuInfo_c*, GRAPH*);

static void mCL_item_draw(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, GRAPH* graph, mCL_Item_c* item,
                          f32 pos_x, f32 pos_y) {
    static mCL_ITEM_DRAW_PROC draw_proc[mCL_DRAW_TYPE_NUM] = {
        (mCL_ITEM_DRAW_PROC)&none_proc1, &mCL_paper_draw, &mCL_wall_draw, &mCL_carpet_draw, &mCL_music_draw,
    };

    if (item->gfx_type == mCL_DRAW_TYPE_FTR) {
        Matrix_push();
        OPEN_DISP(graph);

        gDPPipeSync(NEXT_POLY_OPA_DISP);
        submenu->overlay->change_view_proc(graph, 330.0f, 25.0f, (pos_x + 15.0f) * 4.0f, (pos_y - 38.0f) * -4.0f, 0x900,
                                           0x100, 0x100);
        mCL_furniture_draw(item, game);
        submenu->overlay->setup_view_proc(submenu, graph, 0);

        CLOSE_DISP(graph);
        Matrix_pull();
    } else if (item->gfx_type != mCL_DRAW_TYPE_NONE) {
        Gfx* gfx;

        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate((-143.0f + pos_x) + 58.0f + item->ftr_actor.position.x, (97.0f + pos_y) + item->pos_y, 0.0f,
                         MTX_MULT);
        Matrix_scale(item->scale, item->scale, 1.0f, MTX_MULT);

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;

        gSPMatrix(gfx++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, mCL_lat_letter_mode);

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);

        (*draw_proc[item->gfx_type])(item, menu_info, graph);
    }
}

static void mCL_price_draw(Submenu* submenu, GAME* game, GRAPH* graph, mCL_Item_c* item, f32 pos_x, f32 pos_y) {
    submenu->overlay->set_char_matrix_proc(graph);

    if (item->price == 0) {
        // clang-format off
        mFont_SetLineStrings(
            game,
            not_sell, sizeof(not_sell),
            (-112.0f + pos_x) + 160.0f, 120 - (-47.0f + pos_y),
            205, 0, 0, 255,
            FALSE,
            TRUE,
            0.875f, 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on
    } else {
        u8 price_str[6];
        f32 str_x;
        f32 str_y;
        u32 price;
        f32 width;
        int i;

        mFont_UnintToString(price_str, sizeof(price_str), item->price, 5, TRUE, FALSE, TRUE);

        price = item->price;
        for (i = 1; i < 6; i++) {
            price /= 10;

            if (price == 0) {
                break;
            }
        }

        if (i > 3) {
            i++; /* account for comma */
        }

        width = mFont_GetStringWidth(price_str, i, TRUE) * 0.875f;
        str_x = 160.0f + (-73.5f + pos_x) - width;
        str_y = 120.0f - (-47.0f + pos_y);

        // clang-format off
        mFont_SetLineStrings(
            game,
            price_str, sizeof(price_str),
            str_x, str_y,
            205, 0, 0, 255,
            FALSE,
            TRUE,
            0.875f, 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on
    }
}

extern Gfx clg_win_na1T_model[];
extern Gfx clg_win_na2T_model[];
extern Gfx clg_win_na3T_model[];
extern Gfx clg_win_na4T_model[];
extern Gfx clg_win_na5T_model[];
extern Gfx clg_win_na6T_model[];
extern Gfx clg_win_na7T_model[];

extern Gfx clg_mwin_mode[];
extern Gfx clg_mwin1_model[];
extern Gfx clg_name_mode[];
extern Gfx clg_mwin2_model[];
extern Gfx clg_win_cbT_model[];
extern Gfx clg_win_beruT_model[];
extern Gfx clg_win_shirushi1T_model[];
extern Gfx clg_win_hoshiT_model[];

static void mCL_set_page_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, GRAPH* graph, int page_no,
                            int disp_entries_flag) {
    static Gfx* name_disp[] = {
        clg_win_na1T_model, clg_win_na2T_model, clg_win_na3T_model, clg_win_na4T_model,
        clg_win_na5T_model, clg_win_na6T_model, clg_win_na7T_model,
    };

    static int item_name_color[][3] = { { 155, 155, 155 }, { 255, 255, 255 } };

    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    mCL_win_data_c* win_data = &mCL_win_data[page_no];
    mCL_Menu_c* menu = &catalog_ovl->menu_data[page_no];
    mCL_Item_c* item;
    f32 pos_x = menu_info->position[0]; // f31
    f32 pos_y;                          // f30
    int i;
    Gfx* gfx;
    int x;
    int y;

    if (catalog_ovl->page_timer == 0 || page_no == catalog_ovl->page_no) {
        item = &catalog_ovl->item_data[catalog_ovl->item_data_idx];
        pos_y = menu_info->position[1];
    } else {
        item = &catalog_ovl->item_data[catalog_ovl->item_data_idx ^ 1];
        pos_y = -menu_info->position[1];
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (disp_entries_flag) {
        gSPDisplayList(gfx++, clg_mwin_mode);
        gDPLoadTLUT_Dolphin(gfx++, 14, 16, 1, win_data->win_pal);
        gDPSetTextureImage_Dolphin(gfx++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, win_data->win_tex);
        gDPSetTile_Dolphin(gfx++, G_DOLPHIN_TLUT_DEFAULT_MODE, G_TX_RENDERTILE, 14, GX_REPEAT, GX_REPEAT, GX_CLAMP,
                           GX_CLAMP);
        gDPTileSync(gfx++);
        x = (int)(-submenu->overlay->menu_control.texture_pos[0] * 4.0f);
        y = (int)(-submenu->overlay->menu_control.texture_pos[1] * 4.0f);
        gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, x, y, 32, 32);
        gSPDisplayList(gfx++, clg_mwin1_model);
        gSPDisplayList(gfx++, clg_name_mode);

        for (i = 0; i < mCL_MENU_PAGE_SIZE; i++) {
            if (i == menu->y_idx) {
                gDPSetPrimColor(gfx++, 0, 255, 205, 0, 0, 255);
            } else {
                gDPSetPrimColor(gfx++, 0, 255, 10, 10, 50, 255);
            }

            gSPDisplayList(gfx++, name_disp[i]);
        }

        gSPDisplayList(gfx++, clg_mwin2_model);
        gSPDisplayList(gfx++, clg_win_cbT_model);

        if (item->price != 0) {
            gSPDisplayList(gfx++, clg_win_beruT_model);
        }

        gDPSetPrimColor(gfx++, 0, 255, 0, 50, 255, catalog_ovl->alpha);

        if (menu->top_idx != 0) {
            Matrix_push();
            Matrix_translate(-11.0f, 80.0f, 0.0f, MTX_MULT);

            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, clg_win_shirushi1T_model);

            Matrix_pull();
        }

        if (menu->top_idx + mCL_MENU_PAGE_SIZE < menu->item_count) {
            Matrix_push();
            Matrix_translate(-11.0f, -66.0f, 0.0f, MTX_MULT);
            Matrix_RotateZ(DEG2SHORT_ANGLE2(-180.0f), MTX_MULT);

            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, clg_win_shirushi1T_model);

            Matrix_pull();
        }

        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    if (disp_entries_flag) {
        u8* item_name = menu->item_name[0];
        f32 str_x;
        f32 str_y;
        f32 tmp_x;
        int idx;
        int idx_str_len;
        f32 idx_str_width;
        u8 idx_str[3];
        f32 tmp;
        int width;
        int i;

        submenu->overlay->set_char_matrix_proc(graph);
        str_x = 160.0f + ((-64.0f + pos_x) + 24.0f); // r28
        str_y = 120.0f - ((69.0f + pos_y) - 2.0f);   // r27
        for (i = 0; i < mCL_MENU_PAGE_SIZE; i++) {
            int col_idx;

            if (i == menu->y_idx) {
                col_idx = 1;
            } else {
                col_idx = 0;
            }

            // clang-format off
            mFont_SetLineStrings(
                game,
                item_name, mIN_ITEM_NAME_LEN,
                str_x, str_y,
                item_name_color[col_idx][0], item_name_color[col_idx][1], item_name_color[col_idx][2], 255,
                FALSE,
                TRUE,
                0.875f, 0.875f,
                mFont_MODE_POLY
            );
            // clang-format on

            str_y += 18.0f;
            item_name += mIN_ITEM_NAME_LEN;
        }

        if (menu->item_count != 0) {
            idx = menu->top_idx + menu->y_idx + 1;
        } else {
            idx = 0;
        }

        idx_str_len = mFont_UnintToString(idx_str, sizeof(idx_str), idx, sizeof(idx_str), TRUE, FALSE, TRUE);
        width = mFont_GetStringWidth(idx_str, idx_str_len, TRUE);
        str_x = 160.0f + (28.0f + pos_x - width * 0.875f);
        str_y = 120.0f - ((-62.0f + pos_y) + 1.0f);

        // clang-format off
        mFont_SetLineStrings(
            game,
            idx_str, idx_str_len,
            str_x, str_y,
            20, 20, 70, 255,
            FALSE,
            TRUE,
            0.875f, 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on

        mFont_UnintToString(idx_str, sizeof(idx_str), menu->item_count, sizeof(idx_str), TRUE, FALSE, TRUE);
        str_x = (pos_x + 40.0f) + -2.0f;
        idx_str_width = 7.0f + (mMl_strlen(idx_str, sizeof(idx_str), CHAR_SPACE) * 8.0f) * 0.875f;
        tmp = str_x + (idx_str_width);

        // clang-format off
        mFont_SetLineStrings(
            game,
            idx_str, sizeof(idx_str),
            160.0f + str_x, str_y,
            20, 20, 70, 255,
            FALSE,
            TRUE,
            0.875f, 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on

        if (menu->completed_flag) {
            Gfx* gfx;

            Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
            Matrix_translate(tmp, (97.0f + pos_y) - 163.0f, 140.0f, MTX_MULT);

            OPEN_DISP(graph);
            gfx = NOW_POLY_OPA_DISP;

            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, mCL_lat_letter_mode);
            gSPDisplayList(gfx++, clg_win_hoshiT_model);

            SET_POLY_OPA_DISP(gfx);
            CLOSE_DISP(graph);
        }

        if (menu->item_count != 0) {
            mCL_item_draw(submenu, menu_info, game, graph, item, pos_x, pos_y);
            mCL_price_draw(submenu, game, graph, item, pos_x, pos_y);
        }
    }
}

extern Gfx clg_tag_win_mode[];
extern Gfx clg_tag_picture_mode[];

static void mCL_set_wchange_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GRAPH* graph) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    mCL_win_data_c* win_data;
    int i;
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], -menu_info->position[1], 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, clg_mwin_mode);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    win_data = mCL_win_data;
    gSPDisplayList(gfx++, clg_tag_win_mode);
    gDPSetPrimColor(gfx++, 0, 255, 0, 0, 0, 255);
    gDPSetEnvColor(gfx++, 50, 50, 125, 255);

    for (i = 0; i < mCL_MENU_NUM; i++, win_data++) {
        if (i != catalog_ovl->page_no) {
            gSPDisplayList(gfx++, win_data->sel_gfx0);
        }
    }

    win_data = mCL_win_data;
    gSPDisplayList(gfx++, clg_tag_picture_mode);
    gDPSetPrimColor(gfx++, 0, 255, 145, 145, 205, 255);

    for (i = 0; i < mCL_MENU_NUM; i++, win_data++) {
        if (i != catalog_ovl->page_no) {
            gSPDisplayList(gfx++, win_data->sel_gfx1);
        }
    }

    Matrix_translate(0.0f, menu_info->position[1] * 2.0f, 0.0f, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    win_data = &mCL_win_data[catalog_ovl->page_no];
    gSPDisplayList(gfx++, clg_tag_win_mode);
    gDPSetPrimColor(gfx++, 0, 255, 0, 20, 110, 255);
    gDPSetEnvColor(gfx++, 50, 50, 255, 255);
    gSPDisplayList(gfx++, win_data->sel_gfx0);
    gSPDisplayList(gfx++, clg_tag_picture_mode);
    gDPSetPrimColor(gfx++, 0, 255, 255, 255, 255, 255);
    gSPDisplayList(gfx++, win_data->sel_gfx1);

    if (catalog_ovl->page_timer < 20) {
        gSPDisplayList(gfx++, clg_name_mode);
        gSPDisplayList(gfx++, clg_win_cbT_model);
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mCL_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    u8* page_order = catalog_ovl->page_order + (mCL_MENU_NUM - 1);
    GRAPH* graph = game->graph;
    int flag;
    int i;

    for (i = mCL_MENU_NUM - 1; i >= 0; i--) {
        if (i == 0 || *page_order == catalog_ovl->page_no ||
            (catalog_ovl->page_timer != 0 && i == 1 && page_order[-1] == catalog_ovl->page_no)) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }

        mCL_set_page_dl(submenu, menu_info, game, graph, *page_order, flag);
        page_order--;
    }

    mCL_set_wchange_dl(submenu, menu_info, graph);
    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_CATALOG);
}

static void mCL_catalog_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CATALOG];

    menu_info->pre_draw_func(submenu, game);
    mCL_set_dl(submenu, menu_info, game);
}

extern void mCL_catalog_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mCL_catalog_ovl_move;
    control->menu_draw_func = &mCL_catalog_ovl_draw;
}

static int mCL_check_item_collect_bit(u32* bit_data, int idx) {
    int entry = idx >> 5;
    int subidx = idx & 0x1F;

    if (((1 << subidx) & bit_data[entry]) != 0) {
        return TRUE;
    }

    return FALSE;
}

static void mCL_catalog_ovl_init(Submenu* submenu) {
    int j;
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CATALOG];
    int i;
    mCL_Menu_c* menu;
    mActor_name_t* item_list;
    u8* item_name;
    int k;
    mCL_item_info_c* item_info;
    u16* idx_list;
    mCL_ftr_info_c* ftr_info;
    u32* bit_data;

    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_RIGHT);

    catalog_ovl->item_data[0].ftr_actor.scale.x = 1.0f;
    catalog_ovl->item_data[0].ftr_actor.scale.y = 1.0f;
    catalog_ovl->item_data[0].ftr_actor.scale.z = 1.0f;
    catalog_ovl->item_data[0].gfx_type = mCL_DRAW_TYPE_NONE;

    catalog_ovl->item_data[1].ftr_actor.scale.x = 1.0f;
    catalog_ovl->item_data[1].ftr_actor.scale.y = 1.0f;
    catalog_ovl->item_data[1].ftr_actor.scale.z = 1.0f;
    catalog_ovl->item_data[1].gfx_type = mCL_DRAW_TYPE_NONE;

    submenu->overlay->menu_control.animation_flag = FALSE;

    ftr_info = mCL_furniture_list;
    menu = &catalog_ovl->menu_data[mCL_MENU_FTR];
    item_list = menu->item_list;
    for (i = 0; i < mCL_FTR_LIST_COUNT; i++) {
        if (mCL_check_item_collect_bit(Now_Private->furniture_collected_bitfield, ftr_info->ftr_idx)) {
            *item_list++ = mRmTp_FtrIdx2FtrItemNo(ftr_info->ftr_idx, mRmTp_DIRECT_SOUTH);
            menu->item_count++;
        }

        ftr_info++;
    }

    menu++;
    item_info = &mCL_item_idx_data[mCL_MENU_WALL];
    for (k = mCL_MENU_WALL; k < mCL_MENU_NUM; k++) {
        if (k == mCL_MENU_WALL) {
            bit_data = Now_Private->wall_collected_bitfield;
        } else if (k == mCL_MENU_CARPET) {
            bit_data = Now_Private->carpet_collected_bitfield;
        } else if (k == mCL_MENU_PAPER) {
            bit_data = Now_Private->paper_collected_bitfield;
        } else if (k == mCL_MENU_MUSIC) {
            bit_data = Now_Private->music_collected_bitfield;
        } else {
            bit_data = Now_Private->furniture_collected_bitfield;
        }

        idx_list = item_info->idx_list_p;
        item_list = menu->item_list;

        for (j = 0; j < item_info->list_size; j++, idx_list++) {
            if (mCL_check_item_collect_bit(bit_data, *idx_list)) {
                if (k == mCL_MENU_WALL) {
                    *item_list = ITM_WALL_START + *idx_list;
                } else if (k == mCL_MENU_CARPET) {
                    *item_list = ITM_CARPET_START + *idx_list;
                } else if (k == mCL_MENU_PAPER) {
                    *item_list = ITM_PAPER_STACK_FOUR_START + *idx_list;
                } else if (k == mCL_MENU_MUSIC) {
                    *item_list = ITM_MINIDISK_START + *idx_list;
                } else {
                    *item_list = mRmTp_FtrIdx2FtrItemNo(*idx_list, mRmTp_DIRECT_SOUTH);
                }

                item_list++;
                menu->item_count++;
            }
        }

        menu++;
        item_info++;
    }

    item_info = mCL_item_idx_data;
    menu = catalog_ovl->menu_data;
    for (j = 0; j < mCL_MENU_NUM; j++) {
        item_list = menu->item_list;
        item_name = (u8*)menu->item_name;
        catalog_ovl->page_order[j] = j;
        for (i = 0; i < mCL_MENU_PAGE_SIZE; i++) {
            mIN_copy_name_str(item_name, *item_list);
            item_list++;
            item_name += mIN_ITEM_NAME_LEN;
        }

        if (menu->item_count == item_info->list_size) {
            menu->completed_flag = TRUE;
        } else {
            menu->completed_flag = FALSE;
        }

        menu++;
        item_info++;
    }

    menu = &catalog_ovl->menu_data[mCL_MENU_FTR];
    if (menu->item_list[0] != EMPTY_NO) {
        mCL_furniture_init(catalog_ovl->item_data, menu->item_list[0]);
    }
}

extern void mCL_catalog_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->catalog_ovl == NULL) {
        mCL_Ovl_c* catalog_ovl;
        u8* seg0_p;
        int i;

        overlay->catalog_ovl = (mCL_Ovl_c*)zelda_malloc(sizeof(mCL_Ovl_c));
        mem_clear((u8*)overlay->catalog_ovl, sizeof(mCL_Ovl_c), 0);
        overlay->catalog_ovl->item_data_idx = 0;
        seg0_p = (u8*)submenu->next_overlay_address;

        for (i = 0; i < mCL_ITEM_DATA_NUM; i++) {
            overlay->catalog_ovl->item_data[i].seg0 = seg0_p;
            seg0_p += 0x2000;

            overlay->catalog_ovl->item_data[i].seg1 =
                (u8*)ALIGN_NEXT((uintptr_t)overlay->catalog_ovl->item_data[i].segment_data, 32);
        }

        submenu->next_overlay_address = (char*)seg0_p;
    }

    mCL_catalog_ovl_init(submenu);
    mCL_catalog_ovl_set_proc(submenu);
}

extern void mCL_catalog_ovl_destruct(Submenu* submenu) {
    if (submenu->overlay->catalog_ovl != NULL) {
        zelda_free(submenu->overlay->catalog_ovl);
    }

    submenu->overlay->catalog_ovl = NULL;
}
