#include "m_private.h"

#include "m_land.h"
#include "m_font.h"
#include "m_lib.h"
#include "libultra/libultra.h"
#include "m_player_lib.h"
#include "m_name_table.h"
#include "libc64/qrand.h"
#include "m_field_info.h"
#include "m_house.h"
#include "m_mail.h"
#include "m_handbill.h"
#include "m_post_office.h"
#include "m_event.h"
#include "m_npc.h"
#include "m_submenu.h"
#include "m_room_type.h"
#include "m_common_data.h"

static Mail_c l_mpr_mail;
Private_c g_foreigner_private;

extern void mPr_ClearPlayerName(u8* buf) {
    mem_clear(buf, PLAYER_NAME_LEN, CHAR_SPACE);
}

extern void mPr_CopyPlayerName(u8* dst, u8* src) {
    mem_copy(dst, src, PLAYER_NAME_LEN);
}

extern int mPr_NullCheckPlayerName(u8* name_p) {
    int res = FALSE;
    int i;

    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        if (name_p[0] != CHAR_SPACE) {
            break;
        }
        name_p++;
    }

    if (i == PLAYER_NAME_LEN) {
        res = TRUE;
    }

    return res;
}

extern int mPr_CheckCmpPlayerName(u8* name0, u8* name1) {
    int res = FALSE;

    if (mPr_NullCheckPlayerName(name0) == FALSE && mPr_NullCheckPlayerName(name1) == FALSE) {
        res = mem_cmp(name0, name1, PLAYER_NAME_LEN);
    }

    return res;
}

extern int mPr_GetPlayerName(u8* buf, int player_no) {
    PersonalID_c* pid;
    int res = FALSE;

    if (mLd_PlayerManKindCheckNo(player_no) == FALSE) {
        pid = &Save_Get(private_data[player_no]).player_ID;

        if (mPr_NullCheckPersonalID(pid) == FALSE) {
            mPr_CopyPlayerName(buf, pid->player_name);
            res = TRUE;
        }
    } else if (mLd_PlayerManKindCheckNo(Common_Get(player_no)) == TRUE) {
        mPr_CopyPlayerName(buf, Common_Get(now_private)->player_ID.player_name);
        res = TRUE;
    }

    return res;
}

extern int mPr_NullCheckPersonalID(PersonalID_c* pid) {
    int res = FALSE;

    if (pid->land_id == 0xFFFF && mPr_NullCheckPlayerName(pid->player_name) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern void mPr_ClearPersonalID(PersonalID_c* pid) {
    mPr_ClearPlayerName(pid->player_name);
    mLd_ClearLandName(pid->land_name);
    pid->land_id = 0xFFFF;
    pid->player_id = 0xFFFF;
}

extern void mPr_ClearAnyPersonalID(PersonalID_c* pid, int count) {
    for (count; count != 0; count--) {
        mPr_ClearPersonalID(pid);
        pid++;
    }
}

extern void mPr_CopyPersonalID(PersonalID_c* dst, PersonalID_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(PersonalID_c));
}

extern int mPr_CheckCmpPersonalID(PersonalID_c* pid0, PersonalID_c* pid1) {
    int res = FALSE;

    if (pid0->land_id == pid1->land_id && pid0->player_id == pid1->player_id &&
        mLd_CheckCmpLandName(pid0->land_name, pid1->land_name) == TRUE &&
        mPr_CheckCmpPlayerName(pid0->player_name, pid1->player_name) == TRUE) {
        res = TRUE;
    }

    return res;
}

// TODO: this might actually be file-local but I'm not sure, DnM+ inlined it
extern void mPr_ClearPrivateBirthday(mPr_birthday_c* birthday) {
    birthday->year = 0xFFFF;
    birthday->month = 0xFF;
    birthday->day = 0xFF;
}

extern void mPr_ClearAnimalMemory(mPr_animal_memory_c* memory) {
    memory->npc_id = 0xFFFF;
    mLd_ClearLandName(memory->land_name);
}

extern void mPr_ClearPrivateInfo(Private_c* private_info) {
    bzero(private_info, sizeof(Private_c));

    mPr_ClearPersonalID(&private_info->player_ID);
    private_info->gender = mPr_SEX_MALE;
    mQst_ClearDelivery(private_info->deliveries, mPr_DELIVERY_QUEST_NUM);
    mQst_ClearErrand(private_info->errands, mPr_ERRAND_QUEST_NUM);
    mMl_clear_mail_box(private_info->mail, mPr_INVENTORY_MAIL_COUNT);
    mMl_clear_mail_header_common(&private_info->saved_mail_header);
    mPlib_change_player_cloth_info_lv2(private_info, ITM_CLOTH001);
    mNpc_ClearAnimalPersonalID(&private_info->stored_anm_id);
    mPr_ClearPrivateBirthday(&private_info->birthday);
    private_info->backgound_texture = ITM_CLOTH226;
    mNpc_ClearRemail(&private_info->remail);
    mPr_ClearAnimalMemory(&private_info->animal_memory);
    mPr_ClearMapInfo(private_info->maps, mPr_FOREIGN_MAP_COUNT);
    mMsm_ClearRecord(&private_info->museum_record);
    private_info->state_flags = 1;
}

static int mPr_GetRandomFace() {
    return (fqrand() * (f32)mPr_FACE_TYPE_NUM);
}

static int mPr_GetRandomOriginalFace() {
    Private_c* priv = Save_Get(private_data);
    Private_c* pr2;

    // Private_c* pr2;
    int j;
    int player_exist_num = 0;
    int face;
    int i;

    {
        Private_c* pr = priv;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (pr != NULL && mPr_NullCheckPersonalID(&pr->player_ID) == FALSE) {
                player_exist_num++;
            }
            pr++;
        }
    }

    face = RANDOM(mPr_FACE_TYPE_NUM - player_exist_num);
    for (player_exist_num; player_exist_num > 0; player_exist_num--) {
        pr2 = priv;
        for (j = 0; j < PLAYER_NUM; j++) {
            if (pr2 != NULL && mPr_NullCheckPersonalID(&pr2->player_ID) == FALSE && pr2->face == face) {
                face++;

                if (face >= mPr_FACE_TYPE_NUM) {
                    face = mPr_FACE_TYPE0;
                }
                break;
            }

            pr2++;
        }
    }

    return face;
}

static mActor_name_t mPr_boy_cloth_table[8] = { ITM_CLOTH000, ITM_CLOTH001, ITM_CLOTH002, ITM_CLOTH003,
                                                ITM_CLOTH004, ITM_CLOTH005, ITM_CLOTH006, ITM_CLOTH007 };
static mActor_name_t mPr_girl_cloth_table[8] = { ITM_CLOTH008, ITM_CLOTH009, ITM_CLOTH010, ITM_CLOTH011,
                                                 ITM_CLOTH012, ITM_CLOTH013, ITM_CLOTH014, ITM_CLOTH015 };

static mActor_name_t mPr_GetRandomCloth(u8 sex) {
    static mActor_name_t* cloth_table[mPr_SEX_NUM] = { mPr_boy_cloth_table, mPr_girl_cloth_table };
    static int cloth_max[mPr_SEX_NUM] = { 8, 8 };

    u8 s = sex;
    int sel_cloth;
    mActor_name_t* t;
    mActor_name_t cloth;

    if (s >= mPr_SEX_NUM) {
        s = mPr_SEX_MALE;
    }

    t = cloth_table[s];
    sel_cloth = RANDOM(cloth_max[s]);
    cloth = t[sel_cloth];
    return cloth;
}

extern void mPr_SetNowPrivateCloth() {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(priv->gender));
    }
}

extern void mPr_InitPrivateInfo(Private_c* priv) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);
    Private_c* o_priv = Save_Get(private_data);
    int id_existed = FALSE;
    int face = mPr_GetRandomOriginalFace();
    int pid;
    int i;

    priv->player_ID.land_id = land_info->id;
    mLd_CopyLandName(priv->player_ID.land_name, land_info->name);

    pid = fqrand() * 253.0f;

    for (i = 0; i < PLAYER_NUM - 1; i++) {
        int j;

        for (j = 0; j < PLAYER_NUM; j++) {
            if ((u16)pid == o_priv[j].player_ID.player_id) {
                id_existed = TRUE;
                pid++; // move to next PID
                break;
            }
        }

        if (id_existed == FALSE) {
            break;
        }

        id_existed = FALSE;
    }

    priv->player_ID.player_id = 0xF000 | pid;
    priv->exists = TRUE;
    mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(mPr_SEX_MALE));
    priv->gender = mPr_SEX_MALE;
    priv->inventory.loan = 100;
    priv->face = face;

    for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
        priv->my_org_no_table[i] = i;
    }
}

extern void mPr_CopyPrivateInfo(Private_c* dst, Private_c* src) {
    bcopy(src, dst, sizeof(Private_c));
}

extern int mPr_CheckPrivate(Private_c* priv) {
    int res = FALSE;

    if (mLd_CHECK_LAND_ID(priv->player_ID.land_id)) {
        res = TRUE;
    }

    return res;
}

extern int mPr_CheckCmpPrivate(Private_c* priv0, Private_c* priv1) {
    int res = FALSE;

    if (mPr_CheckCmpPersonalID(&priv0->player_ID, &priv1->player_ID) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern int mPr_GetPrivateIdx(PersonalID_c* pid) {
    Private_c* priv = Save_Get(private_data);
    int res = -1;

    if (mPr_NullCheckPersonalID(pid) == FALSE) {
        int i;

        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_CheckCmpPersonalID(pid, &priv->player_ID) == TRUE) {
                res = i;
                break;
            }

            priv++;
        }
    }

    return res;
}

extern int mPr_GetPossessionItemIdx(Private_c* priv, mActor_name_t item) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            mActor_name_t it = *pockets;
            if (it == item) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

extern int mPr_GetPossessionItemIdxWithCond(Private_c* priv, mActor_name_t item, u32 cond) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            mActor_name_t it = *pockets;
            if (it == item && cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

extern int mPr_GetPossessionItemIdxFGTypeWithCond_cancel(Private_c* priv, mActor_name_t fg_type, u32 cond,
                                                         mActor_name_t cancel_item) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == fg_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) && *pockets != cancel_item) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

extern int mPr_GetPossessionItemIdxItem1Category(Private_c* priv, u8 item1_type) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == NAME_TYPE_ITEM1 && GET_NAME_ITEM1_CATEGORY(*pockets) == item1_type) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}

extern int mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(Private_c* priv, u8 item1_type, u32 cond,
                                                                mActor_name_t cancel_item) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == NAME_TYPE_ITEM1 && GET_NAME_ITEM1_CATEGORY(*pockets) == item1_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) && *pockets != cancel_item) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}

extern int mPr_GetPossessionItemIdxKindWithCond(Private_c* priv, mActor_name_t kind_start, mActor_name_t kind_end,
                                                u32 cond) {
    int idx = -1;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets >= kind_start && *pockets < kind_end &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}

extern u32 mPr_GetPossessionItemSum(Private_c* priv, mActor_name_t item) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern u32 mPr_GetPossessionItemSumWithCond(Private_c* priv, mActor_name_t item, u32 cond) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item && cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern u32 mPr_GetPossessionItemSumFGTypeWithCond_cancel(Private_c* priv, mActor_name_t fg_type, u32 cond,
                                                         mActor_name_t cancel_item) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == fg_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) && *pockets != cancel_item) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern u32 mPr_GetPossessionItemSumItemCategoryWithCond_cancel(Private_c* priv, u8 item1_type, u32 cond,
                                                               mActor_name_t cancel_item) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == NAME_TYPE_ITEM1 && GET_NAME_ITEM1_CATEGORY(*pockets) == item1_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) && *pockets != cancel_item) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern u32 mPr_GetPossessionItemSumItemCategoryWithCond(Private_c* priv, u8 item1_type, u32 cond) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == NAME_TYPE_ITEM1 && GET_NAME_ITEM1_CATEGORY(*pockets) == item1_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern u32 mPr_GetPossessionItemSumKindWithCond(Private_c* priv, mActor_name_t kind_start, mActor_name_t kind_end,
                                                u32 cond) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets >= kind_start && *pockets < kind_end &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

extern void mPr_SetItemCollectBit(mActor_name_t item) {
    mActor_name_t ftr_item_no = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(item, 0);
    int item_type;

    if ((ftr_item_no >= FTR_FISH_START && ftr_item_no <= FTR_FISH_END) ||
        (ftr_item_no >= FTR_INSECT_START && ftr_item_no <= FTR_INSECT_END)) {
        return;
    }

    item_type = ITEM_NAME_GET_TYPE(ftr_item_no);

    if (item_type == NAME_TYPE_FTR0 || item_type == NAME_TYPE_FTR1) {
        int ftr_idx = mRmTp_FtrItemNo2FtrIdx(ftr_item_no);

        if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
            Common_Get(now_private)->furniture_collected_bitfield[ftr_idx >> 5] |= (1 << (ftr_idx & 31));
        }

    } else if (item_type == NAME_TYPE_ITEM1) {
        int category = ITEM_NAME_GET_CAT(ftr_item_no);

        if (category == ITEM1_CAT_PAPER) {
            int idx = (ftr_item_no - ITM_PAPER_START) % 64; // 64 unique stationery
            Common_Get(now_private)->paper_collected_bitfield[idx >> 5] |= (1 << (idx & 31));
        } else if (category == ITEM1_CAT_CARPET) {
            int idx = ftr_item_no - ITM_CARPET_START;
            Common_Get(now_private)->carpet_collected_bitfield[idx >> 5] |= (1 << (idx & 31));
        } else if (category == ITEM1_CAT_WALL) {
            int idx = ftr_item_no - ITM_WALL_START;
            Common_Get(now_private)->wall_collected_bitfield[idx >> 5] |= (1 << (idx & 31));
        } else if (category == ITEM1_CAT_MINIDISK) {
            mActor_name_t idx =
                ftr_item_no - ITM_MINIDISK_START; // why is this one u16, probably mActor_name_t type or something?
            Common_Get(now_private)->music_collected_bitfield[idx >> 5] |= (1 << (idx & 31));
        }
    }
}

extern mActor_name_t mPr_DummyPresentToTruePresent() {
    mActor_name_t true_present = EMPTY_NO;

    /* 80% chance of rolling furniture from town's rare list */
    if (RANDOM(5) != 0) {
        mSP_SelectRandomItem_New(NULL, &true_present, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, FALSE);
    }

    /* 20% (and default case) to get random non-native fruit */
    if (true_present == EMPTY_NO) {
        true_present = mFI_GetOtherFruit();
    }

    return true_present;
}

extern void mPr_SetPossessionItem(Private_c* priv, int idx, mActor_name_t item, u32 cond) {
    switch (item) {
        case ITM_PRESENT: {
            item = mPr_DummyPresentToTruePresent();
            cond = mPr_ITEM_COND_PRESENT;
            break;
        }

        case ITM_GOLDEN_NET_PRESENT: {
            item = ITM_GOLDEN_NET;
            cond = mPr_ITEM_COND_PRESENT;
            break;
        }

        case ITM_GOLDEN_AXE_PRESENT: {
            item = ITM_GOLDEN_AXE;
            cond = mPr_ITEM_COND_PRESENT;
            break;
        }

        case ITM_GOLDEN_SHOVEL_PRESENT: {
            item = ITM_GOLDEN_SHOVEL;
            cond = mPr_ITEM_COND_PRESENT;
            break;
        }

        case ITM_GOLDEN_ROD_PRESENT: {
            item = ITM_GOLDEN_ROD;
            cond = mPr_ITEM_COND_PRESENT;
            break;
        }
    }

    priv->inventory.pockets[idx] = item;
    priv->inventory.item_conditions =
        ((priv->inventory.item_conditions & (~(u32)(mPr_ITEM_COND_NUM << (idx * 2)))) | (cond << (idx * 2)));

    if (cond == mPr_ITEM_COND_NORMAL) {
        mPr_SetItemCollectBit(item);
    }
}

extern int mPr_SetFreePossessionItem(Private_c* priv, mActor_name_t item, u32 cond) {
    int idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
    int res;

    if (idx == -1) {
        res = FALSE;
    } else {
        mPr_SetPossessionItem(priv, idx, item, cond);
        res = TRUE;
    }

    return res;
}

extern void mPr_AddFirstJobHint(Private_c* priv) {
    int hints = priv->hint_count + 1;
    if ((hints & 0x7F) >= 10) {
        hints = 0x80; // signal all hints have been given
    }

    priv->hint_count = hints;
}

extern int mPr_GetFirstJobHintTime(Private_c* priv) {
    return priv->hint_count & 0x7F;
}

extern int mPr_CheckFirstJobHint(Private_c* priv) {
    return (priv->hint_count & 0x80) >> 7;
}

extern s16 mPr_GetMoneyPower() {
    s16 money_power = Common_Get(money_power);
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        switch (priv->destiny.type) {
            case mPr_DESTINY_MONEY_LUCK: {
                money_power += 100;
                break;
            }

            case mPr_DESTINY_BAD_LUCK: {
                money_power -= 50;
                break;
            }
        }
    }

    if (money_power < mPr_MONEY_POWER_MIN) {
        money_power = mPr_MONEY_POWER_MIN;
    }

    return money_power;
}

extern s16 mPr_GetGoodsPower() {
    s16 goods_power = Common_Get(goods_power);
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        switch (priv->destiny.type) {
            case mPr_DESTINY_GOODS_LUCK: {
                goods_power += 30;
                break;
            }

            case mPr_DESTINY_BAD_LUCK: {
                goods_power -= 30;
                break;
            }
        }
    }

    if (goods_power > mPr_GOODS_POWER_MAX) {
        return mPr_GOODS_POWER_MAX;
    }

    if (goods_power < mPr_GOODS_POWER_MIN) {
        goods_power = mPr_GOODS_POWER_MIN;
    }

    return goods_power;
}

extern int mPr_CheckMuseumAddress(Private_c* priv) {
    int res = FALSE;

    if (priv != NULL && priv->museum_record.contacted) {
        res = TRUE;
    }

    return res;
}

extern int mPr_CheckMuseumInfoMail(Private_c* priv) {
    int res = FALSE;

    if (priv != NULL && priv->museum_record.send_info_mail) {
        res = TRUE;
    }

    return res;
}

extern Private_c* mPr_GetForeignerP() {
    return &g_foreigner_private;
}

extern int mPr_LoadPak_and_SetPrivateInfo2(Private_c* unused_private, u8 player_no) {
    Private_c* priv;
    int res = FALSE;

    if (player_no < mPr_FOREIGNER) {
        u32 loan;
        mHm_hs_c* house;
        Private_c* priv = Save_Get(private_data + player_no);
        if (mPr_CheckCmpPrivate(priv, &g_foreigner_private) == TRUE) {
            house = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);
            loan = priv->inventory.loan;
            mPr_CopyPrivateInfo(priv, &g_foreigner_private);
            if (mHm_CheckKeepHouseSize(player_no) == FALSE || house->size_info.next_size == mHm_HOMESIZE_STATUE) {
                priv->inventory.loan = loan;
            }

            res = TRUE;
            Common_Set(now_private, priv);
            Common_Set(player_no, player_no);
        }
    } else {
        mHm_hs_c* house;
        int exist_player;
        u32 loan;
        int i;

        priv = Save_Get(private_data);
        for (i = 0; i < PLAYER_NUM; i++) {
            exist_player = mPr_CheckCmpPrivate(priv, &g_foreigner_private);
            if (exist_player == TRUE) {
                house = Save_GetPointer(homes[mHS_get_arrange_idx(i)]);
                loan = priv->inventory.loan;

                g_foreigner_private.museum_record.contacted = priv->museum_record.contacted;
                mPr_CopyPrivateInfo(priv, &g_foreigner_private);

                if (mHm_CheckKeepHouseSize(i) == FALSE || house->size_info.next_size == mHm_HOMESIZE_STATUE) {
                    priv->inventory.loan = loan;
                }

                res = TRUE;
                Common_Set(now_private, priv);
                Common_Set(player_no, i);
                break;
            }

            priv++;
        }

        if (exist_player == FALSE) {
            res = TRUE;
            Common_Set(now_private, &g_foreigner_private);
            Common_Set(player_no, mPr_FOREIGNER);
        }
    }

    return res;
}

extern void mPr_ClearMotherMailInfo(mPr_mother_mail_info_c* mother_mail) {
    mother_mail->date = mTM_rtcTime_ymd_clear_code;
    bzero(&mother_mail->data, sizeof(mPr_mother_mail_data_c));
}

static int mPr_GetMotherMailPaperType(int month, int day) {
    static u8 paper_table[lbRTC_MONTHS_MAX] = { 13, 49, 32, 12, 62, 14, 19, 11, 59, 46, 47, 17 };

    Private_c* priv = Common_Get(now_private);
    int paper;

    /* TODO: should paper be enums? */
    if (priv->birthday.month == month && priv->birthday.day == day) {
        paper = 1;
    } else if (month == lbRTC_JANUARY && day == 1) {
        paper = 63;
    } else if (month == lbRTC_AUGUST && day == 8) {
        paper = 48;
    } else if (month == lbRTC_DECEMBER && day == 24) {
        paper = 23;
    } else {
        int idx = month - 1;
        paper = paper_table[idx];
    }

    return paper - 1;
}

static void mPr_GetMotherMail(Mail_c* mail, PersonalID_c* pid, mActor_name_t present, int stationery, int mail_no) {
    int header_back_pos;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_pos, mail->content.footer, mail->content.body,
                                   mail_no);
    mail->content.header_back_start = header_back_pos;
    mail->content.font = 0;      // TODO: enum
    mail->content.mail_type = 4; // TODO: enum, this is "from mom"
    mMl_set_to_plname(mail, pid);
    mail->present = present;
    mail->content.paper_type = stationery;
}

static int mPr_SendMotherMailPost(PersonalID_c* pid, int player_no, mActor_name_t present, int stationery,
                                  int mail_no) {
    Mail_c* mail;
    mHm_hs_c* home;
    int res = FALSE;

    mail = &l_mpr_mail;
    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        int mailbox_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);
        if (mailbox_idx != -1) {
            mPr_GetMotherMail(mail, pid, present, stationery, mail_no);
            mMl_copy_mail(&home->mailbox[mailbox_idx], mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mPr_GetMotherMail(mail, pid, present, stationery, mail_no);
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

static int mPr_SendMotherMailDate(mPr_mother_mail_info_c* mother_mail, lbRTC_time_c* send_time) {
    mActor_name_t present = EMPTY_NO;
    int mail_no = -1;
    int res = FALSE;

    if (Common_Get(now_private)->birthday.month == send_time->month &&
        Common_Get(now_private)->birthday.day == send_time->day) {
        mail_no = 0x184 + RANDOM(mPr_MOTHER_MAIL_MONTHLY_NUM);
        present = FTR_START(FTR_SUM_BDCAKE01);
    } else if (send_time->month == send_time->day) {
        int letter_num = (send_time->month - 1) * mPr_MOTHER_MAIL_MONTHLY_NUM + RANDOM(mPr_MOTHER_MAIL_MONTHLY_NUM);
        mail_no = 0x164 + letter_num;

        if (send_time->month == lbRTC_JANUARY) {
            present = ITM_MONEY_10000;
        } else if (letter_num == 18) { // TODO: these probably have enums...
            present = ITM_FOOD_MUSHROOM;
        }
    } else {
        if (send_time->month == lbRTC_APRIL && send_time->day == 1) {
            mail_no = 0x180; // April Fools
        } else if (mEv_check_status(mEv_EVENT_MOTHERS_DAY, mEv_STATUS_ACTIVE) == TRUE) {
            mail_no = 0x17C;
        } else if (mEv_check_status(mEv_EVENT_FATHERS_DAY, mEv_STATUS_ACTIVE) == TRUE) {
            mail_no = 0x17E;
        } else if (send_time->month == lbRTC_DECEMBER && send_time->day == 24) {
            mail_no = 0x182; // Toy Day (Christmas)
            mSP_SelectRandomItem_New(NULL, &present, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_ABC, FALSE);
        }

        if (mail_no != -1) {
            /* Randomize between two letter variants */
            mail_no += RANDOM(mPr_MOTHER_MAIL_MONTHLY_NUM);
        }
    }

    if (mail_no != -1) {
        if (mPr_SendMotherMailPost(&Common_Get(now_private)->player_ID, Common_Get(player_no), present,
                                   mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
            mTM_set_renew_time(&mother_mail->date, send_time);
        }

        res = TRUE;
    }

    return res;
}

static int mPr_CheckMotherMailMonthly(mPr_mother_mail_data_c* send_data, int month, int idx) {
    if (month == lbRTC_AUGUST) {
        return (send_data->august >> (idx)) & 1; // August gets its own byte because it has more than two event letters
    } else {
        int shift = (month - 1) * 2;
        int slot = shift / 8;
        shift -= slot * 8;
        idx += shift;

        return (send_data->monthly[slot] >> idx) & 1;
    }
}

static int mPr_GetMotherMailMonthlyNotSendNum(mPr_mother_mail_data_c* send_data, int month) {
    int slot;
    int not_send_num = 0;
    int i;

    if (month == lbRTC_AUGUST) {
        for (i = 0; i < 8; i++) {
            if (((send_data->august >> i) & 1) == 0) {
                not_send_num++;
            }
        }
    } else {
        u8 byte;
        int shift = (month - 1) * 2;
        slot = shift / 8;
        shift -= slot * 8;
        byte = send_data->monthly[slot];

        for (i = 0; i < 2; i++) {
            if (((byte >> shift) & 1) == 0) {
                not_send_num++;
                shift++;
            }
        }
    }

    return not_send_num;
}

static void mPr_SetMotherMailMonthly(mPr_mother_mail_data_c* send_data, int month, int idx) {
    if (month == lbRTC_AUGUST) {
        send_data->august |= 1 << idx;
    } else {
        /* TODO: almost certainly a fake match */
        u8* s;
        int slot;
        int shift;

        shift = (month - 1) * 2;
        slot = ((month - 1) * 2) / 8;
        shift -= slot * 8;
        idx += shift;

        s = send_data->monthly + slot;
        *s |= 1 << idx;
    }
}

static void mPr_GetMotherMailMonthlyData(mPr_mother_mail_data_c* send_data, int* mail_no, mActor_name_t* present,
                                         int* event_no, int month, int not_send_num) {
    static int mail_start_no_table[mTM_SEASON_NUM] = { 0x18C, 0x192, 0x186, 0x19E };
    static mActor_name_t may_2_item_table[1] = { ITM_CLOTH105 }; // fortune shirt
    static mActor_name_t december_2_item_table[6] = {
        ITM_CLOTH108, // aurora knit
        ITM_CLOTH109, // winter sweater
        ITM_CLOTH110, // go-go shirt
        ITM_CLOTH144, // deer shirt
        ITM_CLOTH145, // blue check shirt
        ITM_CLOTH156  // fish knit
    };

    int max;
    int mail_start_idx;
    int selected_event;
    int i;

    *present = EMPTY_NO;
    mail_start_idx = 3;

    if (month <= lbRTC_FEBRUARY) {
        mail_start_idx = 3;
    } else if (month <= lbRTC_MAY) {
        mail_start_idx = 0;
    } else if (month <= lbRTC_AUGUST) {
        mail_start_idx = 1;
    } else if (month <= lbRTC_NOVEMBER) {
        mail_start_idx = 2;
    }

    *mail_no = mail_start_no_table[mail_start_idx];

    selected_event = RANDOM(not_send_num);
    max = mPr_MOTHER_MAIL_MONTHLY_NUM;
    if (month == lbRTC_AUGUST) {
        max = 8;
    }

    for (i = 0; i < max; i++) {
        if (mPr_CheckMotherMailMonthly(send_data, month, i) == FALSE) {
            if (selected_event <= 0) {
                *event_no = i;
                break;
            }

            selected_event--;
        }
    }

    *mail_no += *event_no + (month - 1 - mail_start_idx * 3) * 2;

    if (month == lbRTC_MAY && *event_no == 1) {
        *present = may_2_item_table[RANDOM(1)];
    } else if (month == lbRTC_DECEMBER) {
        if (*event_no == 0) {
            *present = ITM_FOOD_APPLE;
        } else {
            *present = december_2_item_table[RANDOM(6)];
        }
    } else if (month == lbRTC_NOVEMBER) {
        *present = ITM_FOOD_MUSHROOM;
    }
}

static int mPr_GetMotherMailNormalNotSendNum(mPr_mother_mail_data_c* send_data) {
    int not_send_num = 0;
    int i;
    int j;

    for (i = 0; i < mPr_MOTHER_MAIL_NORMAL_NUM; i++) {
        for (j = 0; j < 8; j++) {
            if (((send_data->normal[i] >> j) & 1) == 0) {
                not_send_num++;
            }
        }
    }

    return not_send_num;
}

static void mPr_SetMotherMailNormal(mPr_mother_mail_data_c* send_data, int idx) {
    int slot = idx / 8;
    idx -= (idx / 8) * 8;
    send_data->normal[slot] |= (1 << idx);
}

static int mPr_CheckMotherMailNormal(mPr_mother_mail_data_c* send_data, int idx) {
    int slot = idx / 8;
    idx -= (idx / 8) * 8;
    return (send_data->normal[slot] >> idx) & 1;
}

// TODO: we need to make an enum for each player mother mail event id
static void mPr_GetMotherMailNormalData(mPr_mother_mail_data_c* send_data, int* mail_no, mActor_name_t* present,
                                        int* event_no, int no_send_num) {
    int selected_event;
    int i;

    *event_no = -1;
    selected_event = RANDOM(no_send_num);

    for (i = 0; i < 56; i++) {
        if (mPr_CheckMotherMailNormal(send_data, i) == FALSE) {
            if (selected_event <= 0) {
                *event_no = i;
                break;
            }

            selected_event--;
        }
    }

    *mail_no = 0x12C + *event_no;

    switch (*event_no) {
        case 1:
        case 16:
            mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);
            break;

        case 3:
        case 21:
        case 22:
        case 47:
            *present = mFI_GetOtherFruit();
            break;

        case 12:
            *present = ITM_MONEY_1000;
            break;

        case 37:
            *present = FTR_START(FTR_SUM_DOLL02);
            break;

        case 38:
            *present = FTR_START(FTR_SUM_PL_DRACAENA);
            break;

        case 40:
            mSP_RandomUmbSelect(present, 1);
            break;

        default:
            *present = EMPTY_NO;
            break;
    }
}

static void mPr_SendMotherMailNormal(mPr_mother_mail_info_c* mother_mail, lbRTC_time_c* send_time) {
    int mail_no = -1;
    int monthly_not_send_num = 0;
    int event_no;
    mActor_name_t present = EMPTY_NO;

    if (RANDOM(100) < 20) {
        int not_send_num = mPr_GetMotherMailNormalNotSendNum(&mother_mail->data);
        if (not_send_num == 0) {
            bzero(&mother_mail->data, sizeof(mPr_mother_mail_data_c));
            monthly_not_send_num = mPr_GetMotherMailMonthlyNotSendNum(&mother_mail->data, send_time->month);
        }

        if (monthly_not_send_num > 0) {
            mPr_GetMotherMailMonthlyData(&mother_mail->data, &mail_no, &present, &event_no, send_time->month,
                                         monthly_not_send_num);

            if (mPr_SendMotherMailPost(&Common_Get(now_private)->player_ID, Common_Get(player_no), present,
                                       mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
                mPr_SetMotherMailMonthly(&mother_mail->data, send_time->month, event_no);
            }
        } else {
            mPr_GetMotherMailNormalData(&mother_mail->data, &mail_no, &present, &event_no, not_send_num);

            if (mPr_SendMotherMailPost(&Common_Get(now_private)->player_ID, Common_Get(player_no), present,
                                       mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
                mPr_SetMotherMailNormal(&mother_mail->data, event_no);
            }
        }
    }

    mTM_set_renew_time(&mother_mail->date, send_time);
}

static void mPr_SendMotherMail(mPr_mother_mail_info_c* mother_mail, lbRTC_time_c* send_time) {
    if (mPr_SendMotherMailDate(mother_mail, send_time) == FALSE) {
        mPr_SendMotherMailNormal(mother_mail, send_time);
    }
}

extern void mPr_SendMailFromMother() {
    Private_c* priv = Common_Get(now_private);
    u8 player_no = Common_Get(player_no);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (mLd_PlayerManKindCheckNo(player_no) == FALSE && priv != NULL &&
        mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
        mPr_mother_mail_info_c* mother_mail = Save_GetPointer(mother_mail[player_no]);
        lbRTC_ymd_c* mail_date = &mother_mail->date;

        if (mail_date->year != mTM_rtcTime_ymd_clear_code.year &&
            mail_date->month != mTM_rtcTime_ymd_clear_code.month && mail_date->day != mTM_rtcTime_ymd_clear_code.day) {
            if (mail_date->year != rtc_time->year || mail_date->month != rtc_time->month ||
                mail_date->day != rtc_time->day) {
                mPr_SendMotherMail(mother_mail, rtc_time);
            }
        } else {
            mTM_set_renew_time(mail_date, rtc_time);
        }
    }
}

static void mPr_GetForeingerAnimalMail(Mail_c* mail, Private_c* priv, mPr_animal_memory_c* anm_mem) {
    AnmPersonalID_c anm_pid;
    int mail_no;
    u8 npc_name[ANIMAL_NAME_LEN];
    u8 header[40];
    u8 footer[48];
    int ofs;
    u8 looks;
    int header_back_start;

    looks = mNpc_GetLooks(anm_mem->npc_id);
    ofs = RANDOM(3);
    mail_no = 0xFC;
    mail_no += ofs + looks * 3;
    mHandbill_Set_free_str(0, priv->player_ID.player_name, PLAYER_NAME_LEN); // player's name
    mNpc_LoadNpcNameString(npc_name, anm_mem->npc_id);
    mHandbill_Set_free_str(1, npc_name, ANIMAL_NAME_LEN);                 // animal's name
    mHandbill_Set_free_str(2, anm_mem->land_name, LAND_NAME_SIZE);        // animal's current town name
    mHandbill_Set_free_str(3, priv->player_ID.land_name, LAND_NAME_SIZE); // player's town name
    mHandbill_Load_HandbillFromRom2(header, 40, &header_back_start, footer, 48, mail->content.body, mail_no);
    mem_copy(mail->content.header, header, mHandbill_HEADER_LEN);
    mem_copy(mail->content.footer, footer, mHandbill_FOOTER_LEN);

    mail->content.header_back_start = header_back_start;
    mail->content.font = 0;
    mail->content.mail_type = 0;
    mail->present = EMPTY_NO;
    mail->content.paper_type = mNpc_GetPaperType();

    anm_pid.npc_id = anm_mem->npc_id;
    anm_pid.land_id = mLd_BITMASK;
    mLd_CopyLandName(anm_pid.land_name, anm_mem->land_name);
    anm_pid.name_id = anm_mem->npc_id;
    anm_pid.looks = looks;

    mMl_set_mail_name_npcinfo(&mail->header.sender, &anm_pid);
    mPr_CopyPersonalID(&mail->header.recipient.personalID, &priv->player_ID);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
}

extern void mPr_SendForeingerAnimalMail(Private_c* priv) {
    Mail_c* mail = &l_mpr_mail;
    mPr_animal_memory_c* anm_mem = &priv->animal_memory;

    if (mLd_PlayerManKindCheck() == FALSE) {
        if (anm_mem->npc_id != RSV_NO && ITEM_NAME_GET_TYPE(anm_mem->npc_id) == NAME_TYPE_NPC &&
            mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mMl_clear_mail(mail);
            mPr_GetForeingerAnimalMail(mail, priv, anm_mem);
            mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
            mPr_ClearAnimalMemory(anm_mem);
        }
    }
}

extern void mPr_StartSetCompleteTalkInfo() {
    if (mSM_CHECK_ALL_FISH_GET()) {
        Common_Get(now_private)->complete_fish_insect_flags |= (1 << 0);
    }

    if (mSM_CHECK_ALL_INSECT_GET()) {
        Common_Get(now_private)->complete_fish_insect_flags |= (1 << 2);
    }
}

static void mPr_SetCompleteTalk(u8* comp_insect_fish_flags, int type) {
    *comp_insect_fish_flags |= (1 << (type * 2) + 1);
}

static int mPr_GetCompleteTalk(u8 comp_insect_fish_flags, int type) {
    return (comp_insect_fish_flags >> ((type * 2) + 1)) & 1;
}

extern void mPr_SetFishCompleteTalk() {
    mPr_SetCompleteTalk(&Common_Get(now_private)->complete_fish_insect_flags, 0);
}

extern int mPr_CheckFishCompleteTalk(u8 player_no) {
    int res = FALSE;

    if (player_no < mPr_FOREIGNER &&
        mPr_GetCompleteTalk(Save_Get(private_data[player_no]).complete_fish_insect_flags, 0) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern void mPr_SetInsectCompleteTalk() {
    mPr_SetCompleteTalk(&Common_Get(now_private)->complete_fish_insect_flags, 1);
}

extern int mPr_CheckInsectCompleteTalk(u8 player_no) {
    int res = FALSE;

    if (player_no < mPr_FOREIGNER &&
        mPr_GetCompleteTalk(Save_Get(private_data[player_no]).complete_fish_insect_flags, 1) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int mPr_GetTalkPermission(u8 comp_insect_fish_flags, int type) {
    int base = type * 2;
    int talk = base + 1;

    int res = FALSE;
    if (((comp_insect_fish_flags >> base) & 1) == 0 || ((comp_insect_fish_flags >> talk) & 1) == 0) {
        res = TRUE;
    }

    return res;
}

extern int mPr_GetFishCompTalkPermission() {
    int res = FALSE;

    if (mSM_CHECK_ALL_FISH_GET()) {
        res = mPr_GetTalkPermission(Common_Get(now_private)->complete_fish_insect_flags, 0);
    }

    return res;
}

extern int mPr_GetInsectCompTalkPermission() {
    int res = FALSE;

    if (mSM_CHECK_ALL_INSECT_GET()) {
        res = mPr_GetTalkPermission(Common_Get(now_private)->complete_fish_insect_flags, 1);
    }

    return res;
}

extern void mPr_ClearMapInfo(mPr_map_info_c* map_info, int max) {
    for (max; max != 0; max--) {
        mLd_ClearLandName(map_info->land_name);
        map_info->land_id = 0;
        map_info++;
    }
}

static void mPr_CopyMapInfo(mPr_map_info_c* dst, mPr_map_info_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(mPr_map_info_c));
}

static void mPr_SetMapThisLand(mPr_map_info_c* map_info) {
    if (map_info != NULL) {
        mLd_CopyLandName(map_info->land_name, Save_Get(land_info).name);
        map_info->land_id = Save_Get(land_info).id;
    }
}

static int mPr_GetMapFreeIdx(mPr_map_info_c* map_info, int max) {
    int res = -1;
    int i;

    for (i = 0; i < max; i++) {
        if (!mLd_CheckId(map_info->land_id) || mLd_NullCheckLandName(map_info->land_name) == TRUE) {
            res = i;
            break;
        }

        map_info++;
    }

    return res;
}

static int mPr_GetLandMapIdx(mPr_map_info_c* map_info, int max, mLd_land_info_c* land_info) {
    int res = -1;

    if (map_info != NULL && land_info != NULL) {
        int i;

        for (i = 0; i < max; i++) {
            if (mLd_CheckCmpLand(map_info->land_name, map_info->land_id, land_info->name, land_info->id) == TRUE) {
                res = i;
                break;
            }

            map_info++;
        }
    }

    return res;
}

extern int mPr_GetThisLandMapIdx(mPr_map_info_c* map_info, int max) {
    return mPr_GetLandMapIdx(map_info, max, Save_GetPointer(land_info));
}

static void mPr_PushMapInfo(mPr_map_info_c* map_info, int max) {
    if (map_info != NULL) {
        max--;

        if (max > 0) {
            for (max; max > 0; max--) {
                mPr_CopyMapInfo(map_info, map_info + 1);
                map_info++;
            }
        }

        mPr_ClearMapInfo(map_info, 1);
    }
}

extern void mPr_SetNewMap(mPr_map_info_c* map_info, int max) {
    if (map_info != NULL && mPr_GetThisLandMapIdx(map_info, max) == -1) {
        int free_idx = mPr_GetMapFreeIdx(map_info, max);
        if (free_idx != -1) {
            map_info += free_idx;
        } else {
            mPr_PushMapInfo(map_info, max);
            free_idx = max - 1;
            map_info += free_idx;
        }

        if (map_info != NULL) {
            mPr_SetMapThisLand(map_info);
        }
    }
}

extern void mPr_RenewalMapInfo(mPr_map_info_c* map_info, int max, mLd_land_info_c* land_info) {
    mPr_map_info_c map_save;

    int map_idx = mPr_GetLandMapIdx(map_info, max, land_info);
    if (map_idx != -1) {
        mPr_CopyMapInfo(&map_save, map_info + map_idx);
        mPr_PushMapInfo(map_info + map_idx, max - map_idx);

        map_idx = mPr_GetMapFreeIdx(map_info, max);
        if (map_idx != -1) {
            mPr_CopyMapInfo(map_info + map_idx, &map_save);
        }
    }
}

extern void mPr_RandomSetPlayerData_title_demo() {
    Private_c* priv = Common_Get(now_private);
    int i;

    priv->gender = RANDOM(4); // why not RANDOM(2)???
    priv->gender &= 1;
    mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(priv->gender));
    priv->face = mPr_GetRandomFace();

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        Save_Get(homes[i]).door_original = -1;
    }
}

extern void mPr_PrintMapInfo_debug(gfxprint_t* gfxprint) {
    Private_c* priv = Common_Get(now_private);
    mPr_map_info_c* map_info;
    int i;

    if (priv != NULL) {
        map_info = priv->maps;
        gfxprint_color(gfxprint, 30, 100, 100, 255);
        gfxprint_locate8x8(gfxprint, 3, 21);
        gfxprint_printf(gfxprint, "%04x ", Save_Get(land_info).id);

        gfxprint_locate8x8(gfxprint, 3, 22);
        gfxprint_color(gfxprint, 30, 200, 70, 255);

        for (i = 0; i < mPr_FOREIGN_MAP_COUNT; i++) {
            if (i == 4) {
                gfxprint_locate8x8(gfxprint, 3, 23);
            }

            if (mLd_CheckId(map_info->land_id) == TRUE) {
                gfxprint_printf(gfxprint, "%04x ", map_info->land_id);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            map_info++;
        }
    }
}

#ifdef PC_ENHANCEMENTS
/* bell amount for a money-bag item, 0 if not one */
extern u32 mPr_GetAmountForMoneyItem(mActor_name_t item) {
    int type = mNT_get_itemTableNo(item);
    int idx = item & 0xFF;

    if (type != 9) return 0;

    switch (idx) {
        case 0: return 1000;
        case 1: return 10000;
        case 2: return 30000;
    }

    if (idx >= 3 && idx <= 0x0B) {
        return (u32)(idx - 2) * 100;
    }
    if (idx >= 0x0C && idx <= 0x6E) {
        return (u32)(idx - 0x0B) * 1000;
    }

    return 0;
}

/* deposit bells to wallet; fails without change unless the whole amount fits */
extern int mPr_GivePossessionBells(u32 amount) {
    if (amount > mPr_WALLET_MAX - Now_Private->inventory.wallet) {
        return FALSE;
    }

    Now_Private->inventory.wallet += amount;
    return TRUE;
}

#endif
