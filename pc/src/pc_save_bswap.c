/* pc_save_bswap.c - Bidirectional LE<->BE byte-swap for Save_t and ARAM blocks */
#include "pc_save_bswap.h"
#include "m_common_data.h"
#include "m_card.h"
#include "m_quest.h"
#include "m_museum.h"
#include "m_mushroom.h"
#include "m_event.h"
#include "m_field_assessment.h"
#include "m_mask_cat.h"
#include "m_all_grow_ovl.h"
#include "m_fishrecord.h"

#include <string.h>
#include <stdlib.h>
#include "dolphin/os.h"
#include "pc_bswap.h"

/* Leaf byte-swap helpers (all self-inverse) */

static void swap16(void* p) { u16 v; memcpy(&v, p, 2); v = pc_bswap16(v); memcpy(p, &v, 2); }
static void swap32(void* p) { u32 v; memcpy(&v, p, 4); v = pc_bswap32(v); memcpy(p, &v, 4); }
static void swap64(void* p) { u64 v; memcpy(&v, p, 8); v = pc_bswap64(v); memcpy(p, &v, 8); }

static void swap16_array(u16* arr, u32 count) {
    pc_bswap16_array(arr, (int)count);
}

static void swap32_array(u32* arr, u32 count) {
    pc_bswap32_array(arr, (int)count);
}

/* u8 bitfield repack helpers.
 * GCC packs u8 bitfields MSB-first on BE, LSB-first on LE.
 * Single-byte values have no byte-swap, so we repack bits explicitly. */

/* Reverse all 8 bits. Only correct when all fields are 1-bit wide. */
static u8 reverse_bits8(u8 v) {
    v = (u8)(((v & 0xF0) >> 4) | ((v & 0x0F) << 4));
    v = (u8)(((v & 0xCC) >> 2) | ((v & 0x33) << 2));
    v = (u8)(((v & 0xAA) >> 1) | ((v & 0x55) << 1));
    return v;
}

/* Direction-aware u8 bitfield repackers for multi-bit fields.
 * NOT self-inverse -- they need the direction parameter.
 * BE packs MSB-first, LE packs LSB-first. */

/* [a:5, b:3] */
static void repack_u8_5_3(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7:3], b=[2:0] → LE: b=[7:5], a=[4:0] */
        a = (v >> 3) & 0x1F;
        b = v & 0x07;
        *p = (u8)((b << 5) | a);
    } else {
        /* LE: a=[4:0], b=[7:5] → BE: a=[7:3], b=[2:0] */
        a = v & 0x1F;
        b = (v >> 5) & 0x07;
        *p = (u8)((a << 3) | b);
    }
}

/* [a:2, b:2, c:2, d:2] */
static void repack_u8_2222(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b, c, d;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7:6], b=[5:4], c=[3:2], d=[1:0] → LE: d=[7:6], c=[5:4], b=[3:2], a=[1:0] */
        a = (v >> 6) & 0x3;
        b = (v >> 4) & 0x3;
        c = (v >> 2) & 0x3;
        d = v & 0x3;
        *p = (u8)((d << 6) | (c << 4) | (b << 2) | a);
    } else {
        /* LE: a=[1:0], b=[3:2], c=[5:4], d=[7:6] → BE: a=[7:6], b=[5:4], c=[3:2], d=[1:0] */
        a = v & 0x3;
        b = (v >> 2) & 0x3;
        c = (v >> 4) & 0x3;
        d = (v >> 6) & 0x3;
        *p = (u8)((a << 6) | (b << 4) | (c << 2) | d);
    }
}

/* [a:1, b:1, c:6] */
static void repack_u8_1_1_6(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b, c;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7], b=[6], c=[5:0] → LE: c=[7:2], b=[1], a=[0] */
        a = (v >> 7) & 0x1;
        b = (v >> 6) & 0x1;
        c = v & 0x3F;
        *p = (u8)((c << 2) | (b << 1) | a);
    } else {
        /* LE: a=[0], b=[1], c=[7:2] → BE: a=[7], b=[6], c=[5:0] */
        a = v & 0x1;
        b = (v >> 1) & 0x1;
        c = (v >> 2) & 0x3F;
        *p = (u8)((a << 7) | (b << 6) | c);
    }
}

/* [a:1, b:1, c:1, d:1, e:1, f:3] */
static void repack_u8_11111_3(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b, c, d, e, f;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7],b=[6],c=[5],d=[4],e=[3],f=[2:0] → LE: f=[7:5],e=[4],d=[3],c=[2],b=[1],a=[0] */
        a = (v >> 7) & 1; b = (v >> 6) & 1; c = (v >> 5) & 1;
        d = (v >> 4) & 1; e = (v >> 3) & 1; f = v & 0x7;
        *p = (u8)((f << 5) | (e << 4) | (d << 3) | (c << 2) | (b << 1) | a);
    } else {
        /* LE: a=[0],b=[1],c=[2],d=[3],e=[4],f=[7:5] → BE: a=[7],b=[6],c=[5],d=[4],e=[3],f=[2:0] */
        a = v & 1; b = (v >> 1) & 1; c = (v >> 2) & 1;
        d = (v >> 3) & 1; e = (v >> 4) & 1; f = (v >> 5) & 0x7;
        *p = (u8)((a << 7) | (b << 6) | (c << 5) | (d << 4) | (e << 3) | f);
    }
}

/* [a:1, b:1, c:1, d:5] */
static void repack_u8_111_5(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b, c, d;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7], b=[6], c=[5], d=[4:0] → LE: d=[7:3], c=[2], b=[1], a=[0] */
        a = (v >> 7) & 1; b = (v >> 6) & 1; c = (v >> 5) & 1;
        d = v & 0x1F;
        *p = (u8)((d << 3) | (c << 2) | (b << 1) | a);
    } else {
        /* LE: a=[0], b=[1], c=[2], d=[7:3] → BE: a=[7], b=[6], c=[5], d=[4:0] */
        a = v & 1; b = (v >> 1) & 1; c = (v >> 2) & 1;
        d = (v >> 3) & 0x1F;
        *p = (u8)((a << 7) | (b << 6) | (c << 5) | d);
    }
}

/* [a:4, b:1, c:3] */
static void repack_u8_4_1_3(u8* p, pc_bswap_dir_t dir) {
    u8 v = *p;
    u8 a, b, c;
    if (dir == PC_BSWAP_FROM_BE) {
        /* BE: a=[7:4], b=[3], c=[2:0] → LE: c=[7:5], b=[4], a=[3:0] */
        a = (v >> 4) & 0xF;
        b = (v >> 3) & 0x1;
        c = v & 0x07;
        *p = (u8)((c << 5) | (b << 4) | a);
    } else {
        /* LE: a=[3:0], b=[4], c=[7:5] → BE: a=[7:4], b=[3], c=[2:0] */
        a = v & 0xF;
        b = (v >> 4) & 0x1;
        c = (v >> 5) & 0x07;
        *p = (u8)((a << 4) | (b << 3) | c);
    }
}


static void swap_lbRTC_time(lbRTC_time_c* t) {
    swap16(&t->year);
}

static void swap_lbRTC_ymd(lbRTC_ymd_c* t) {
    swap16(&t->year);
}

static void swap_PersonalID(PersonalID_c* pid) {
    swap16(&pid->player_id);
    swap16(&pid->land_id);
}

static void swap_AnmPersonalID(AnmPersonalID_c* anm) {
    swap16(&anm->npc_id);
    swap16(&anm->land_id);
}

static void swap_mLd_land_info(mLd_land_info_c* li) {
    swap16(&li->id);
}


static void swap_Mail_nm(Mail_nm_c* nm) {
    swap_PersonalID(&nm->personalID);
}

static void swap_Mail_hdr(Mail_hdr_c* hdr) {
    swap_Mail_nm(&hdr->recipient);
    swap_Mail_nm(&hdr->sender);
}

static void swap_Mail(Mail_c* mail) {
    swap_Mail_hdr(&mail->header);
    swap16(&mail->present);
}

static void swap_Mail_array(Mail_c* mail, u32 count) {
    u32 i;
    for (i = 0; i < count; i++) swap_Mail(&mail[i]);
}

/* mQst_base_c u32 bitfield: direction-aware repack.
 * BE: quest_type[31:30], quest_kind[29:24], time_limit_enabled[23], progress[22:19], give_reward[18], unused[17:16]
 * LE: quest_type[1:0], quest_kind[7:2], time_limit_enabled[8], progress[12:9], give_reward[13], unused[15:14] */
static void swap_mQst_base(mQst_base_c* qb, pc_bswap_dir_t dir) {
    u8* b = (u8*)qb;
    u32 raw;
    u32 quest_type, quest_kind, time_limit_enabled, progress, give_reward, unused_bits;

    if (dir == PC_BSWAP_FROM_BE) {
        raw = ((u32)b[0] << 24) | ((u32)b[1] << 16) | ((u32)b[2] << 8) | b[3];
        quest_type          = (raw >> 30) & 0x3;
        quest_kind          = (raw >> 24) & 0x3F;
        time_limit_enabled  = (raw >> 23) & 0x1;
        progress            = (raw >> 19) & 0xF;
        give_reward         = (raw >> 18) & 0x1;
        unused_bits         = (raw >> 16) & 0x3;

        raw = quest_type | (quest_kind << 2) | (time_limit_enabled << 8)
            | (progress << 9) | (give_reward << 13) | (unused_bits << 14);
        b[0] = (u8)(raw);
        b[1] = (u8)(raw >> 8);
        b[2] = (u8)(raw >> 16);
        b[3] = (u8)(raw >> 24);
    } else {
        raw = b[0] | ((u32)b[1] << 8) | ((u32)b[2] << 16) | ((u32)b[3] << 24);
        quest_type          = raw & 0x3;
        quest_kind          = (raw >> 2) & 0x3F;
        time_limit_enabled  = (raw >> 8) & 0x1;
        progress            = (raw >> 9) & 0xF;
        give_reward         = (raw >> 13) & 0x1;
        unused_bits         = (raw >> 14) & 0x3;

        raw = (quest_type << 30) | (quest_kind << 24) | (time_limit_enabled << 23)
            | (progress << 19) | (give_reward << 18) | (unused_bits << 16);
        b[0] = (u8)(raw >> 24);
        b[1] = (u8)(raw >> 16);
        b[2] = (u8)(raw >> 8);
        b[3] = (u8)(raw);
    }

    swap_lbRTC_time(&qb->time_limit);
}

static void swap_mQst_delivery(mQst_delivery_c* qd, pc_bswap_dir_t dir) {
    swap_mQst_base(&qd->base, dir);
    swap_AnmPersonalID(&qd->recipient);
    swap_AnmPersonalID(&qd->sender);
}

static void swap_mQst_errand(mQst_errand_c* qe, pc_bswap_dir_t dir) {
    int j;
    swap_mQst_base(&qe->base, dir);
    swap_AnmPersonalID(&qe->recipient);
    swap_AnmPersonalID(&qe->sender);
    swap16(&qe->item);
    repack_u8_5_3(((u8*)qe) + 0x2A, dir); /* pockets_idx:5, errand_type:3 */
    for (j = 0; j < mQst_ERRAND_CHAIN_ANIMAL_NUM; j++) {
        swap_AnmPersonalID(&qe->info.chain.used_ids[j]);
    }
}

static void swap_mQst_contest(mQst_contest_c* qc, pc_bswap_dir_t dir) {
    swap_mQst_base(&qc->base, dir);
    swap16(&qc->requested_item);
    swap_PersonalID(&qc->player_id);
    swap16(&qc->info.letter_data.present);
}


static void swap_mPr_cloth(mPr_cloth_c* cl) {
    swap16(&cl->idx);
    swap16(&cl->item);
}


static void swap_Anmplmail(Anmplmail_c* pm) {
    swap16(&pm->present);
    swap_lbRTC_ymd(&pm->date);
}

static void swap_Anmmem(Anmmem_c* mem, pc_bswap_dir_t dir) {
    swap_PersonalID(&mem->memory_player_id);
    swap_lbRTC_time(&mem->last_speak_time);
    /* Swap both union interpretations (overlapping but self-inverse) */
    swap16(&mem->memuni.land.id);
    swap32(&mem->memuni.island.check);
    swap16(&mem->memuni.island.have_bitfield);
    swap64(&mem->saved_town_tune);
    repack_u8_11111_3((u8*)&mem->letter_info, dir);
    swap_Anmplmail(&mem->letter);
}

static void swap_AnmHPMail(AnmHPMail_c* hp) {
    swap_lbRTC_time(&hp->receive_time);
}

static void swap_Animal(Animal_c* anm, pc_bswap_dir_t dir, int is_island) {
    int i;
    swap_AnmPersonalID(&anm->id);

    for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
        swap_Anmmem(&anm->memories[i], dir);
    }

    swap_mQst_contest(&anm->contest_quest, dir);
    /* anmuni is a union: island animal uses island_ftr (u16[4], needs swap),
       regular villagers use previous_land_name (u8[8], must NOT swap) 
       GBA messes with me even when the functionality is off. */
    if (is_island)
        swap16_array(anm->anmuni.island_ftr, mNpc_ISLAND_FTR_SAVE_NUM);

    swap16(&anm->previous_land_id);
    swap16(&anm->cloth);
    swap16(&anm->remove_info);
    swap16(&anm->present_cloth);

    for (i = 0; i < ANIMAL_HP_MAIL_NUM; i++) {
        swap_AnmHPMail(&anm->hp_mail[i]);
    }
}


static void swap_Haniwa_Item(Haniwa_Item_c* hi) {
    swap16(&hi->item);
    swap16((u16*)&hi->exchange_type);
    swap32(&hi->extra_data);
}

static void swap_Haniwa(Haniwa_c* h) {
    int i;
    for (i = 0; i < HANIWA_ITEM_HOLD_NUM; i++) {
        swap_Haniwa_Item(&h->items[i]);
    }
    swap32(&h->bells);
}

static void swap_mHm_lyr(mHm_lyr_c* lyr) {
    swap16_array(&lyr->items[0][0], UT_Z_NUM * UT_X_NUM);
    swap64(&lyr->ftr_switch);
    swap32_array(lyr->haniwa_step, 8);
}

static void swap_mHm_flr(mHm_flr_c* flr, pc_bswap_dir_t dir) {
    swap_mHm_lyr(&flr->layer_main);
    swap_mHm_lyr(&flr->layer_secondary);
    swap_mHm_lyr(&flr->layer_storage1);
    swap_mHm_lyr(&flr->layer_storage2);
    repack_u8_1_1_6((u8*)&flr->floor_bit_info, dir);
}

static void swap_mHm_rmsz(mHm_rmsz_c* sz, pc_bswap_dir_t dir) {
    swap16(&sz->upgrade_order_date.year);

    /* Bitfield bytes at offset 4-5: direction-aware repack.
     * byte4: [size:3, next_size:3, statue_rank:2]
     * byte5: [renew:1, statue_ordered:1, basement_ordered:1, pad_1:1, pad:4] */
    {
        u8* raw = ((u8*)sz) + 4;  /* bytes at offset 4-5 in the struct */
        u8 b4 = raw[0];
        u8 b5 = raw[1];
        u8 size_val, next_size_val, statue_rank_val;
        u8 renew_val, stat_ord_val, base_ord_val, pad1_val, pad_val;

        if (dir == PC_BSWAP_FROM_BE) {
            size_val       = (b4 >> 5) & 0x7;
            next_size_val  = (b4 >> 2) & 0x7;
            statue_rank_val = b4 & 0x3;
            raw[0] = (statue_rank_val << 6) | (next_size_val << 3) | size_val;

            renew_val      = (b5 >> 7) & 0x1;
            stat_ord_val   = (b5 >> 6) & 0x1;
            base_ord_val   = (b5 >> 5) & 0x1;
            pad1_val       = (b5 >> 4) & 0x1;
            pad_val        = b5 & 0xF;
            raw[1] = (pad_val << 4) | (pad1_val << 3) | (base_ord_val << 2) | (stat_ord_val << 1) | renew_val;
        } else {
            size_val       = b4 & 0x7;
            next_size_val  = (b4 >> 3) & 0x7;
            statue_rank_val = (b4 >> 6) & 0x3;
            raw[0] = (size_val << 5) | (next_size_val << 2) | statue_rank_val;

            renew_val      = b5 & 0x1;
            stat_ord_val   = (b5 >> 1) & 0x1;
            base_ord_val   = (b5 >> 2) & 0x1;
            pad1_val       = (b5 >> 3) & 0x1;
            pad_val        = (b5 >> 4) & 0xF;
            raw[1] = (renew_val << 7) | (stat_ord_val << 6) | (base_ord_val << 5) | (pad1_val << 4) | pad_val;
        }
    }
}

static void swap_mHm_hs(mHm_hs_c* home, pc_bswap_dir_t dir) {
    int i;
    swap_PersonalID(&home->ownerID);
    swap_lbRTC_ymd(&home->hra_mark_time);
    swap32(&home->hra_mark_info);
    { u8* p = (u8*)&home->flags; *p = reverse_bits8(*p); } /* 8x 1-bit fields */
    swap_mHm_rmsz(&home->size_info, dir);

    for (i = 0; i < mHm_ROOM_NUM; i++) {
        swap_mHm_flr(&home->floors[i], dir);
    }

    swap_Mail_array(home->mailbox, HOME_MAILBOX_SIZE);
    swap_Haniwa(&home->haniwa);
    swap_lbRTC_time(&home->goki.time);
    swap32_array(home->music_box, 2);
}

static void swap_mHm_cottage(mHm_cottage_c* cot, pc_bswap_dir_t dir) {
    swap_mHm_flr(&cot->room, dir);
    swap_lbRTC_time(&cot->goki.time);
    swap32_array(cot->music_box, 2);
}


static void swap_mFM_fg(mFM_fg_c* fg) {
    swap16_array(&fg->items[0][0], 16 * 16);
}

static void swap_mFM_fg_array(mFM_fg_c* fg, u32 count) {
    u32 i;
    for (i = 0; i < count; i++) swap_mFM_fg(&fg[i]);
}

/* mFM_combination_c u16 bitfield: combination_type:14, height:2.
 * BE: [15:2]=type, [1:0]=height. LE: [13:0]=type, [15:14]=height.
 * Raw byte-swap doesn't repack bits -- direction-aware repack needed. */
static void swap_mFM_combination(mFM_combination_c* c, pc_bswap_dir_t dir) {
    u16 raw;
    u16 combination_type, height;
    u8* b = (u8*)c;

    if (dir == PC_BSWAP_TO_BE) {
        raw = b[0] | ((u16)b[1] << 8);
        combination_type = raw & 0x3FFF;
        height = (raw >> 14) & 0x3;

        raw = (combination_type << 2) | height;
        b[0] = (u8)(raw >> 8);
        b[1] = (u8)(raw);
    } else {
        raw = ((u16)b[0] << 8) | b[1];
        combination_type = (raw >> 2) & 0x3FFF;
        height = raw & 0x3;

        raw = combination_type | (height << 14);
        b[0] = (u8)(raw);
        b[1] = (u8)(raw >> 8);
    }
}

static void swap_combi_table(mFM_combination_c combi[BLOCK_Z_NUM][BLOCK_X_NUM], pc_bswap_dir_t dir) {
    int z, x;
    for (z = 0; z < BLOCK_Z_NUM; z++) {
        for (x = 0; x < BLOCK_X_NUM; x++) {
            swap_mFM_combination(&combi[z][x], dir);
        }
    }
}

/* shop_info u16 bitfield: direction-aware repack (same class as mFM_combination_c) */
static void swap_Shop(Shop_c* shop, pc_bswap_dir_t dir) {
    int i;
    u16 raw;
    u8* b;
    u16 shop_level, upgrading_today, send_upgrade_notice, not_loaded_before, paint_color, unused_bits;

    for (i = 0; i < mSP_KIND_MAX; i++) {
        repack_u8_2222((u8*)&shop->priority_lists[i], dir);
    }

    for (i = 0; i < mSP_PERSONAL_ID_COUNT; i++) {
        swap_PersonalID(&shop->unused_ids[i]);
    }

    swap16_array(shop->items, mSP_GOODS_COUNT);
    swap16(&shop->rare_item);
    swap16_array(shop->lottery_items, mSP_LOTTERY_ITEM_COUNT);

    /* shop_info bitfield repack */
    b = (u8*)&shop->shop_info;
    if (dir == PC_BSWAP_TO_BE) {
        raw = b[0] | ((u16)b[1] << 8);
        shop_level = raw & 0x3;
        upgrading_today = (raw >> 2) & 0x1;
        send_upgrade_notice = (raw >> 3) & 0x1;
        not_loaded_before = (raw >> 4) & 0x1;
        paint_color = (raw >> 5) & 0xF;
        unused_bits = (raw >> 9) & 0x7F;

        raw = (shop_level << 14) | (upgrading_today << 13) | (send_upgrade_notice << 12)
            | (not_loaded_before << 11) | (paint_color << 7) | unused_bits;
        b[0] = (u8)(raw >> 8);
        b[1] = (u8)(raw);
    } else {
        raw = ((u16)b[0] << 8) | b[1];
        shop_level = (raw >> 14) & 0x3;
        upgrading_today = (raw >> 13) & 0x1;
        send_upgrade_notice = (raw >> 12) & 0x1;
        not_loaded_before = (raw >> 11) & 0x1;
        paint_color = (raw >> 7) & 0xF;
        unused_bits = raw & 0x7F;

        raw = shop_level | (upgrading_today << 2) | (send_upgrade_notice << 3)
            | (not_loaded_before << 4) | (paint_color << 5) | (unused_bits << 9);
        b[0] = (u8)(raw);
        b[1] = (u8)(raw >> 8);
    }

    swap32(&shop->sales_sum);
    swap_lbRTC_time(&shop->exchange_time);
    swap_lbRTC_time(&shop->renewal_time);
    swap32((u32*)&shop->visitor_flag);
}


static void swap_Kabu(Kabu_price_c* kabu) {
    swap16_array(kabu->daily_price, lbRTC_WEEKDAYS_MAX);
    swap16(&kabu->trade_market);
    swap_lbRTC_time(&kabu->update_time);
}


static void swap_PostOffice(PostOffice_c* po) {
    swap16((u16*)&po->keep_mail_sum_players);
    swap16((u16*)&po->keep_mail_sum_npcs);
    swap16((u16*)&po->mail_recipient_flags);
    swap16(&po->unused_6);
    swap_Mail_array(po->mail, mPO_MAIL_STORAGE_SIZE);
    swap_Mail(&po->leaflet);
    swap_Mail(&po->event_leaflet);
    swap32((u32*)&po->leaflet_recipient_flags.raw);
    swap_lbRTC_time(&po->delivery_time);
}


static void swap_PoliceBox(PoliceBox_c* pb) {
    swap16_array(pb->keep_items, mPB_POLICE_BOX_ITEM_STORAGE_COUNT);
}


static void swap_mEv_special(mEv_special_c* sp) {
    swap_lbRTC_time(&sp->scheduled);
    /* Check kind before and after swap to handle both load/save directions */
    u32 kind_pre = sp->kind;
    swap32(&sp->kind);
    u32 kind = (kind_pre <= mEv_SPNPC_GYPSY) ? kind_pre : sp->kind;

    switch (kind) {
    case mEv_SPNPC_SHOP: /* bargin */ {
        mEv_bargin_c* bg = &sp->event.bargin;
        swap_lbRTC_time(&bg->start_time);
        swap_lbRTC_time(&bg->end_time);
        swap16_array(bg->items, mEv_BARGIN_ITEM_NUM);
        swap32((u32*)&bg->kind);
        break;
    }
    case mEv_SPNPC_DESIGNER: /* designer */ {
        mEv_designer_c* ds = &sp->event.designer;
        int j;
        for (j = 0; j < mEv_DESGINER_NUM; j++) {
            swap_PersonalID(&ds->pids[j]);
        }
        swap32((u32*)&ds->used);
        swap16_array(ds->gifted_cloths, mEv_DESGINER_NUM);
        break;
    }
    case mEv_SPNPC_BROKER: /* broker */ {
        mEv_broker_c* bk = &sp->event.broker;
        int j;
        for (j = 0; j < mEv_BROKER_ITEM_NUM - 1; j++) {
            swap_PersonalID(&bk->pid[j]);
        }
        swap_lbRTC_time(&bk->end_time);
        swap32((u32*)&bk->used);
        swap16_array(bk->sold_items, mEv_BROKER_ITEM_NUM - 1);
        swap16_array(bk->items, mEv_BROKER_ITEM_NUM);
        break;
    }
    case mEv_SPNPC_ARTIST: /* artist */ {
        mEv_artist_c* ar = &sp->event.artist;
        int j;
        for (j = 0; j < mEv_ARTIST_ENTRY_SAVE_NUM; j++) {
            swap_PersonalID(&ar->pids[j]);
        }
        swap32((u32*)&ar->used);
        swap16_array(ar->walls, mEv_ARTIST_ENTRY_SAVE_NUM);
        break;
    }
    case mEv_SPNPC_ARABIAN: /* arabian */ {
        mEv_arabian_c* ab = &sp->event.arabian;
        swap32((u32*)&ab->used);
        swap16(&ab->carpet);
        break;
    }
    case mEv_SPNPC_GYPSY: /* gypsy */ {
        mEv_gypsy_c* gy = &sp->event.gypsy;
        swap32((u32*)&gy->_00);
        swap32((u32*)&gy->block_z);
        swap32((u32*)&gy->block_x);
        swap32((u32*)&gy->ut_z);
        swap32((u32*)&gy->ut_x);
        break;
    }
    default:
        break;
    }
}

static void swap_mEv_weekly(mEv_weekly_u* wk) {
    int i;
    for (i = 0; i < TOTAL_PLAYER_NUM; i++) {
        swap_PersonalID(&wk->kabu_peddler.spoken_pids[i]);
    }
}

static void swap_mEv_event_save(mEv_event_save_c* es) {
    swap_mEv_special(&es->special);
    swap_mEv_weekly(&es->weekly);
    swap32(&es->flags);
}

static void swap_mEv_area(mEv_area_c* area) {
    swap16(&area->info.year);
    swap16(&area->info.start_date.raw);
    swap16(&area->info.end_date.raw);
    swap32_array((u32*)area->data, 11);
}

static void swap_mEv_save_common(mEv_save_common_data_c* sc) {
    int i;
    swap16_array(sc->dates, mEv_SAVE_DATE_NUM);
    swap32((u32*)&sc->area_use_bitfield);
    for (i = 0; i < mEv_AREA_NUM; i++) {
        swap_mEv_area(&sc->area[i]);
    }
    swap32((u32*)&sc->last_date);
    swap32((u32*)&sc->delete_event_id);
    swap32(&sc->valentines_day_date);
    swap32(&sc->white_day_date);
    swap16(&sc->ghost_day);
    swap16(&sc->bridge_day);
}


static void swap_mPr_catalog_order(mPr_catalog_order_c* co) {
    swap16(&co->item);
}

static void swap_mPr_map_info(mPr_map_info_c* mi) {
    swap16(&mi->land_id);
}

static void swap_mPr_calendar(mCD_player_calendar_c* cal) {
    swap32_array(cal->played_days, 12);
    swap32_array(cal->event_days, 12);
    swap16(&cal->event_flags);
    swap16(&cal->year);
}

static void swap_mMsm_remail_info(mMsm_remail_info_c* ri) {
    swap16_array(ri->items, mMsm_REMAIL_SLOTS);
}

static void swap_mMsm_record(mMsm_record_c* rec, pc_bswap_dir_t dir) {
    repack_u8_111_5((u8*)rec, dir);
    swap_mMsm_remail_info(&rec->remail_info);
}

static void swap_Anmremail(Anmremail_c* ar) {
    swap_lbRTC_ymd(&ar->date);
}

static void swap_Private(Private_c* prv, pc_bswap_dir_t dir) {
    int i;

    swap_PersonalID(&prv->player_ID);
    swap_mMsm_record(&prv->museum_record, dir);

    swap16_array(prv->inventory.pockets, mPr_POCKETS_SLOT_COUNT);
    swap32(&prv->inventory.item_conditions);
    swap32(&prv->inventory.wallet);
    swap32(&prv->inventory.loan);

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        swap_mQst_delivery(&prv->deliveries[i], dir);
    }
    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        swap_mQst_errand(&prv->errands[i], dir);
    }

    swap16(&prv->equipment);
    swap_Mail_array(prv->mail, mPr_INVENTORY_MAIL_COUNT);
    swap16(&prv->backgound_texture);
    swap_mPr_cloth(&prv->cloth);

    swap_AnmPersonalID(&prv->stored_anm_id);
    swap_lbRTC_time(&prv->destiny.received_time);
    swap16(&prv->birthday.year);

    for (i = 0; i < mPr_CATALOG_ORDER_NUM; i++) {
        swap_mPr_catalog_order(&prv->catalog_orders[i]);
    }

    swap32_array(prv->aircheck_collect_bitfield, 2);
    swap_Anmremail(&prv->remail);
    swap32(&prv->reset_code);
    swap16(&prv->animal_memory.npc_id);
    swap16(&prv->celebrated_birthday_year);
    swap32_array(prv->furniture_collected_bitfield, 43);
    swap32_array(prv->wall_collected_bitfield, 3);
    swap32_array(prv->carpet_collected_bitfield, 3);
    swap32_array(prv->paper_collected_bitfield, 2);
    swap32_array(prv->music_collected_bitfield, 2);

    for (i = 0; i < mPr_FOREIGN_MAP_COUNT; i++) {
        swap_mPr_map_info(&prv->maps[i]);
    }

    swap32(&prv->bank_account);
    swap32(&prv->state_flags);
    swap_mPr_calendar(&prv->calendar);
    swap32(&prv->soncho_trophy_field0);
    swap_lbRTC_ymd(&prv->nw_visitor.last_date);
    swap_lbRTC_ymd(&prv->radiocard.last_date);
    swap_lbRTC_ymd(&prv->sunburn.last_changed_date);
    swap16(&prv->birthday_present_npc);
    swap32(&prv->soncho_trophy_field1);
    swap_lbRTC_ymd(&prv->ecard_letter_data.letter_send_date);
}


static void swap_noticeboard(mNtc_board_post_c* posts, int count) {
    int i;
    for (i = 0; i < count; i++) {
        swap_lbRTC_time(&posts[i].post_time);
    }
}


static void swap_Island(Island_c* isl, pc_bswap_dir_t dir) {
    swap_mLd_land_info(&isl->landinfo);
    swap_mFM_fg_array(&isl->fgblock[0][0], mISL_FG_BLOCK_Z_NUM * mISL_FG_BLOCK_X_NUM);
    swap_mHm_cottage(&isl->cottage, dir);
    swap_Animal(&isl->animal, dir, 1);
    swap16_array(&isl->deposit[0][0], mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM * UT_Z_NUM);
    swap_lbRTC_time(&isl->renew_time);
}


static void swap_fishRecord(mFR_record_c* fr, int count) {
    int i;
    for (i = 0; i < count; i++) {
        swap_PersonalID(&fr[i].pid);
        swap_lbRTC_time(&fr[i].time);
        swap32((u32*)&fr[i].size);
    }
}


static void swap_MaskCat(MaskCat_c* mc) {
    swap_PersonalID(&mc->design.creator_pid);
    swap_lbRTC_time(&mc->time);
}


static void swap_PlusBridge(PlusBridge_c* br, pc_bswap_dir_t dir) {
    repack_u8_1_1_6(((u8*)br) + 2, dir); /* exists:1, pending:1, pad:6 */
    swap_lbRTC_ymd(&br->build_date);
}


static void swap_LightHouse(LightHouse_c* lh) {
    swap_lbRTC_ymd(&lh->renew_time);
}


static void swap_GoodField(mFAs_GoodField_c* gf) {
    swap_lbRTC_time(&gf->renew_time);
    swap32((u32*)&gf->perfect_day_streak);
}


static void swap_Anmret(Anmret_c* ar) {
    swap16(&ar->npc_id);
    swap_lbRTC_time(&ar->renew_time);
}


static void swap_mother_mail_info(mPr_mother_mail_info_c* mm) {
    swap_lbRTC_ymd(&mm->date);
}

/* mMsr_time_c: u16 year:12/month:4 needs direction-aware swap, u8 bitfields need repack */
static void swap_mMsr_time(mMsr_time_c* mt, pc_bswap_dir_t dir) {
    u8* b = (u8*)mt;
    u16 raw;
    u16 year, month;

    if (dir == PC_BSWAP_TO_BE) {
        raw = b[0] | ((u16)b[1] << 8);
        year = raw & 0xFFF;
        month = (raw >> 12) & 0xF;
        raw = (year << 4) | month;
        b[0] = (u8)(raw >> 8);
        b[1] = (u8)(raw);
    } else {
        raw = ((u16)b[0] << 8) | b[1];
        year = (raw >> 4) & 0xFFF;
        month = raw & 0xF;
        raw = year | (month << 12);
        b[0] = (u8)(raw);
        b[1] = (u8)(raw >> 8);
    }
    repack_u8_5_3(&b[2], dir);
    repack_u8_5_3(&b[3], dir);
    repack_u8_4_1_3(&b[4], dir);
}


static void swap_save_check(mFRm_chk_t* chk) {
    swap32((u32*)&chk->version);
    swap32(&chk->code);
    swap16(&chk->land_id);
    swap_lbRTC_time(&chk->time);
    swap16(&chk->checksum);
}

void pc_save_bswap(Save_t* save, pc_bswap_dir_t dir) {
    int i;

    swap_save_check(&save->save_check);
    swap32((u32*)&save->scene_no);
    swap16(&save->copy_protect);

    for (i = 0; i < PLAYER_NUM; i++)
        swap_Private(&save->private_data[i], dir);

    swap_mLd_land_info(&save->land_info);
    swap_noticeboard(save->noticeboard, mNtc_BOARD_POST_COUNT);

    for (i = 0; i < PLAYER_NUM; i++)
        swap_mHm_hs(&save->homes[i], dir);

    swap_mFM_fg_array(&save->fg[0][0], FG_BLOCK_Z_NUM * FG_BLOCK_X_NUM);
    swap_combi_table(save->combi_table, dir);

    for (i = 0; i < ANIMAL_NUM_MAX; i++)
        swap_Animal(&save->animals[i], dir, 0);

    swap_AnmPersonalID(&save->last_removed_animal_id);
    swap_Shop(&save->shop, dir);
    swap_Kabu(&save->kabu_price_schedule);
    swap_mEv_event_save(&save->event_save_data);
    swap_mEv_save_common(&save->event_save_common);

    swap16(&save->fruit);
    swap_lbRTC_time(&save->all_grow_renew_time);
    swap_PostOffice(&save->post_office);
    swap_PoliceBox(&save->police_box);
    swap64(&save->melody);
    swap_lbRTC_ymd(&save->renew_time);
    swap16_array(&save->deposit[0][0], FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM * UT_Z_NUM);
    swap_lbRTC_time(&save->last_grow_time);

    for (i = 0; i < PLAYER_NUM; i++)
        swap_mother_mail_info(&save->mother_mail[i]);

    swap_mMsr_time(&save->mushroom_time, dir);
    swap_lbRTC_ymd(&save->_021322);
    swap16_array(save->_021326, 20);
    swap_lbRTC_time(&save->_02136E);
    swap_lbRTC_time(&save->treasure_buried_time);
    swap_lbRTC_time(&save->treasure_checked_time);
    swap16((u16*)&save->event_year);
    swap_lbRTC_ymd(&save->force_remove_date);
    swap_PlusBridge(&save->bridge, dir);
    swap64((u64*)&save->time_delta);
    swap_Island(&save->island, dir);
    swap_fishRecord(save->fishRecord, mFR_RECORD_NUM);

    swap_MaskCat(&save->mask_cat);

    swap_Anmret(&save->return_animal);

    swap_LightHouse(&save->LightHouse);
    swap_GoodField(&save->good_field);
    swap64((u64*)&save->travel_hard_time);

    swap_lbRTC_time(&save->saved_auto_nwrite_time);
}

/* ARAM block swaps for the "Others" section of the GCI file */

void pc_save_bswap_keep_mail(mCD_keep_mail_c* mail, pc_bswap_dir_t dir) {
    int page, slot;
    (void)dir;
    swap16(&mail->checksum);
    swap16(&mail->landid);
    for (page = 0; page < mCD_KEEP_MAIL_PAGE_COUNT; page++) {
        for (slot = 0; slot < mCD_KEEP_MAIL_COUNT; slot++) {
            swap_Mail(&mail->mail[page][slot]);
        }
    }
}

void pc_save_bswap_keep_original(mCD_keep_original_c* orig, pc_bswap_dir_t dir) {
    (void)dir;
    swap16(&orig->checksum);
    swap16(&orig->landid);
    swap32((u32*)&orig->_CC80);
}

void pc_save_bswap_keep_diary(mCD_keep_diary_c* diary, pc_bswap_dir_t dir) {
    (void)dir;
    swap16(&diary->checksum);
}

/* Round-trip verification: load(BE->LE) then save(LE->BE), compare with original */

static int verify_compare(const char* label, const u8* original, const u8* roundtripped, u32 size) {
    int mismatches = 0;
    int printed = 0;
    u32 i;

    for (i = 0; i < size; i++) {
        if (roundtripped[i] != original[i]) {
            if (mismatches == 0) {
                OSReport("[PC] BSWAP verify: %s round-trip FAILED!\n", label);
            }
            if (printed < 20) {
                OSReport("[PC] BSWAP verify:   offset 0x%05X: expected 0x%02X, got 0x%02X\n",
                         i, original[i], roundtripped[i]);
                printed++;
            }
            mismatches++;
        }
    }

    if (mismatches == 0) {
        OSReport("[PC] BSWAP verify: %s round-trip PASSED (%u bytes)\n", label, size);
    } else {
        OSReport("[PC] BSWAP verify: %s total mismatches: %d / %u bytes\n", label, mismatches, size);
    }
    return mismatches;
}

int pc_save_bswap_verify_roundtrip(const u8* original_be, u32 size) {
    u8* temp = (u8*)malloc(size);
    int result;
    if (!temp) {
        OSReport("[PC] BSWAP verify: malloc(%u) failed\n", size);
        return -1;
    }
    memcpy(temp, original_be, size);
    pc_save_bswap((Save_t*)temp, PC_BSWAP_FROM_BE);
    pc_save_bswap((Save_t*)temp, PC_BSWAP_TO_BE);
    result = verify_compare("Save_t", original_be, temp, size);
    free(temp);
    return result;
}

int pc_save_bswap_verify_roundtrip_mail(const u8* original_be, u32 size) {
    u8* temp = (u8*)malloc(size);
    int result;
    if (!temp) return -1;
    memcpy(temp, original_be, size);
    pc_save_bswap_keep_mail((mCD_keep_mail_c*)temp, PC_BSWAP_FROM_BE);
    pc_save_bswap_keep_mail((mCD_keep_mail_c*)temp, PC_BSWAP_TO_BE);
    result = verify_compare("keep_mail", original_be, temp, size);
    free(temp);
    return result;
}

int pc_save_bswap_verify_roundtrip_original(const u8* original_be, u32 size) {
    u8* temp = (u8*)malloc(size);
    int result;
    if (!temp) return -1;
    memcpy(temp, original_be, size);
    pc_save_bswap_keep_original((mCD_keep_original_c*)temp, PC_BSWAP_FROM_BE);
    pc_save_bswap_keep_original((mCD_keep_original_c*)temp, PC_BSWAP_TO_BE);
    result = verify_compare("keep_original", original_be, temp, size);
    free(temp);
    return result;
}

int pc_save_bswap_verify_roundtrip_diary(const u8* original_be, u32 size) {
    u8* temp = (u8*)malloc(size);
    int result;
    if (!temp) return -1;
    memcpy(temp, original_be, size);
    pc_save_bswap_keep_diary((mCD_keep_diary_c*)temp, PC_BSWAP_FROM_BE);
    pc_save_bswap_keep_diary((mCD_keep_diary_c*)temp, PC_BSWAP_TO_BE);
    result = verify_compare("keep_diary", original_be, temp, size);
    free(temp);
    return result;
}

/* BE-aware checksum matching mFRm_GetFlatCheckSum on GC.
 * Reads byte stream as BE u16 pairs (GC reads native PPC u16 directly). */

u16 pc_checksum_be(const u8* data, u32 size, u16 old_checksum) {
    u32 i;
    u32 sum = 0;
    u32 num_u16 = size / 2;
    u16 raw;

    for (i = 0; i < num_u16; i++) {
        u16 val = ((u16)data[i * 2] << 8) | data[i * 2 + 1];
        sum += val;
    }

    /* Two's complement: subtract old_checksum (included in sum), negate */
    raw = (u16)((sum - old_checksum) & 0xFFFF);
    return (u16)((~raw + 1) & 0xFFFF);
}
