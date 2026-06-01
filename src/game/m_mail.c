#include "m_mail.h"

#include "m_private.h"
#include "m_font.h"
#include "m_land.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_handbill.h"
#include "libultra/libultra.h"

/* TODO: fix bss ordering*/
static u8 free_str[16];
static Mail_c l_ml_mail;
static u8 footer[MAIL_FOOTER2_LEN];
static u8 header[MAIL_HEADER2_LEN];

extern int mMl_strlen(u8* str, int size, u8 end_char) {
    u8* end_p = str + size;
    int i;

    end_p--;
    for (size; size != 0; size--) {

        if (*end_p != end_char) {
            return size;
        }

        end_p--;
    }

    return 0;
}

extern int mMl_strlen2(int* found, u8* str, int size, u8 end_char) {
    int len = 0;

    if (found != NULL) {
        *found = FALSE;
    }

    for (size; size != 0; size--) {
        len++;
        if (*str == end_char) {
            if (found != NULL) {
                *found = TRUE;
            }
            break;
        }

        str++;
    }

    return len;
}

extern void mMl_clear_mail_header(Mail_hdr_c* header) {
    mPr_ClearPersonalID(&header->recipient.personalID);
    header->recipient.type = mMl_NAME_TYPE_CLEAR;

    mPr_ClearPersonalID(&header->sender.personalID);
    header->sender.type = mMl_NAME_TYPE_CLEAR;
}

extern void mMl_clear_mail(Mail_c* mail) {
    bzero(mail, sizeof(Mail_c));
    mMl_clear_mail_header(&mail->header);
    mem_clear(mail->content.header, MAIL_HEADER_LEN + MAIL_BODY_LEN + MAIL_FOOTER_LEN, CHAR_SPACE);
    mail->content.font = -1;
}

extern void mMl_clear_mail_box(Mail_c* mail, int num) {
    while (num != 0) {
        num--;
        mMl_clear_mail(mail);
        mail++;
    }
}

extern int mMl_check_not_used_mail(Mail_c* mail) {
    int res = FALSE;
    if (mail->content.font == 0xFF) {
        res = TRUE;
    }

    return res;
}

extern void mMl_copy_header_name(Mail_nm_c* dst, Mail_nm_c* src) {
    dst->type = src->type;
    mPr_CopyPersonalID(&dst->personalID, &src->personalID);
}

extern void mMl_set_to_plname(Mail_c* mail, PersonalID_c* pid) {
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
}

extern void mMl_set_playername(Mail_c* mail, PersonalID_c* pid) {
    mPr_CopyPersonalID(&mail->header.sender.personalID, pid);
    mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
}

extern void mMl_init_mail(Mail_c* mail, PersonalID_c* pid) {
    mMl_clear_mail(mail);
    mMl_set_playername(mail, pid);
    mail->content.font = mMl_FONT_SEND;
    mail->content.mail_type = 0;
    mail->content.paper_type = 0;
}

extern int mMl_chk_mail_free_space(Mail_c* mail, int num) {
    int free_idx;

    for (free_idx = 0; free_idx < num; free_idx++) {
        if (mMl_check_not_used_mail(mail) == TRUE) {
            return free_idx;
        }

        mail++;
    }

    return -1;
}

extern int mMl_count_use_mail_space(Mail_c* mail, int num) {
    int used = 0;
    int i;

    for (i = 0; i < num; i++) {
        if (mMl_check_not_used_mail(mail) != TRUE) {
            used++;
        }

        mail++;
    }

    return used;
}

extern void mMl_copy_mail(Mail_c* dst, Mail_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Mail_c));
}

extern void mMl_clear_mail_header_common(Mail_hs_c* header) {
    header->header_back_start = -1;
    header->unknown = 0;
    mem_clear(header->header, MAIL_HEADER_LEN, CHAR_SPACE);
    mem_clear(header->footer, MAIL_FOOTER_LEN, CHAR_SPACE);
}

extern void mMl_set_mail_name_npcinfo(Mail_nm_c* name, AnmPersonalID_c* anm_pid) {
    u8 animal_name[PLAYER_NAME_LEN];

    name->type = mMl_NAME_TYPE_NPC;
    mNpc_GetNpcWorldNameAnm(animal_name, anm_pid);
    mPr_CopyPlayerName(name->personalID.player_name, animal_name);
    name->personalID.land_id = anm_pid->land_id;
    mLd_CopyLandName(name->personalID.land_name, anm_pid->land_name);
    name->personalID.player_id = (((anm_pid->npc_id & 0xFF) << 8) | anm_pid->name_id);
}

extern int mMl_get_npcinfo_from_mail_name(AnmPersonalID_c* anm_pid, Mail_nm_c* name) {
    int res = FALSE;

    if (name->type == mMl_NAME_TYPE_NPC) {
        anm_pid->npc_id = ((name->personalID.player_id & 0xFF00) >> 8) | NPC_START;
        anm_pid->land_id = name->personalID.land_id;
        mLd_CopyLandName(anm_pid->land_name, name->personalID.land_name);
        anm_pid->name_id = name->personalID.player_id;
        anm_pid->looks = mNpc_GetLooks(anm_pid->npc_id);

        res = TRUE;
    }

    return res;
}

extern int mMl_hunt_for_send_address(Mail_c* mail) {
    int i;

    if (mail->header.recipient.type != mMl_NAME_TYPE_PLAYER) {
        return -1;
    }

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        if (mPr_CheckCmpPersonalID(&Save_Get(homes[i]).ownerID, &mail->header.recipient.personalID) == TRUE) {
            return i;
        }
    }

    return -1;
}

extern int mMl_check_send_mail(Mail_c* mail) {
    return mail->content.font == mMl_FONT_SEND;
}

extern int mMl_check_set_present_myself(Mail_c* mail) {
    u8 font = mail->content.font;

    if (font == mMl_FONT_SEND || font == mMl_FONT_RECV_PLAYER_PRESENT || font == mMl_FONT_RECV_PLAYER_PRESENT_READ) {
        return TRUE;
    }

    return FALSE;
}

static void mMl_load_mail_data(Mail_c* mail, int mail_no) {
    int header_back_start;

    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body,
                                   mail_no);
    mail->content.header_back_start = header_back_start;
}

/* TODO: fix bss ordering */
static void mMl_load_mail_data2(Mail_c* mail, int mail_no) {
    // static u8 header[MAIL_HEADER2_LEN];
    // static u8 footer[MAIL_FOOTER2_LEN];
    int header_back_start;

    mHandbill_Load_HandbillFromRom2(header, MAIL_HEADER2_LEN, &header_back_start, footer, MAIL_FOOTER2_LEN,
                                    mail->content.body, mail_no);

    bcopy(header, mail->content.header, MAIL_HEADER_LEN);
    bcopy(footer, mail->content.footer, MAIL_FOOTER_LEN);
    mail->content.header_back_start = header_back_start;
}

static void mMl_get_mail_to_player_com(Mail_c* mail, PersonalID_c* recipient_pid, mActor_name_t present,
                                       mActor_name_t paper, u8* sender_name, int mail_no, u32 proc_type, u8 mail_type) {
    static void (*get_proc[2])(Mail_c*, int) = { &mMl_load_mail_data, &mMl_load_mail_data2 };
    proc_type %= 2;

    mMl_clear_mail(mail);
    (*get_proc[proc_type])(mail, mail_no);
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mail_type;

    mPr_CopyPersonalID(&mail->header.recipient.personalID, recipient_pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;

    mPr_ClearPersonalID(&mail->header.sender.personalID);
    mPr_CopyPlayerName(mail->header.sender.personalID.player_name, sender_name);
    mail->header.sender.type = mMl_NAME_TYPE_MUSEUM;

    mail->present = present;
    mail->content.paper_type = (paper - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
}

static int mMl_send_mail_box_com(PersonalID_c* recipient_pid, int player_no, Mail_c* mail, mActor_name_t present,
                                 mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type, u8 mail_type) {
    mHm_hs_c* house;
    int res = FALSE;

    house = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_CheckCmpPersonalID(recipient_pid, &house->ownerID) == TRUE) {
        int free_idx = mMl_chk_mail_free_space(house->mailbox, HOME_MAILBOX_SIZE);
        if (free_idx != -1) {
            mMl_get_mail_to_player_com(mail, recipient_pid, present, paper, sender_name, mail_no, proc_type, mail_type);
            mMl_copy_mail(house->mailbox + free_idx, mail);
            res = TRUE;
        }
    }

    return res;
}

extern int mMl_send_mail_box(PersonalID_c* recipient_pid, int player_no, Mail_c* mail, mActor_name_t present,
                             mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type) {
    return mMl_send_mail_box_com(recipient_pid, player_no, mail, present, paper, mail_no, sender_name, proc_type, 0);
}

static int mMl_send_mail_postoffice_com(Mail_c* mail, PersonalID_c* recipient_pid, int player_no, mActor_name_t present,
                                        mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type,
                                        u8 mail_type) {
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_get_mail_to_player_com(mail, recipient_pid, present, paper, sender_name, mail_no, proc_type, mail_type);
        res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

extern int mMl_send_mail_postoffice(PersonalID_c* recipient_pid, int player_no, mActor_name_t present,
                                    mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type, u8 mail_type) {
    return mMl_send_mail_postoffice_com(&l_ml_mail, recipient_pid, player_no, present, paper, mail_no, sender_name,
                                        proc_type, mail_type);
}

static int mMl_send_mail_com(PersonalID_c* recipient_pid, int player_no, mActor_name_t present, mActor_name_t paper,
                             int mail_no, u8* sender_name, u32 proc_type, u8 mail_type) {
    Mail_c* mail = &l_ml_mail;
    int res = mMl_send_mail_box_com(recipient_pid, player_no, mail, present, paper, mail_no, sender_name, proc_type,
                                    mail_type);
    if (res != TRUE) {
        res = mMl_send_mail_postoffice_com(mail, recipient_pid, player_no, present, paper, mail_no, sender_name,
                                           proc_type, mail_type);
    }

    return res;
}

extern int mMl_send_mail(PersonalID_c* recipient_pid, int player_no, mActor_name_t present, mActor_name_t paper,
                         int mail_no, u8* sender_name, u32 proc_type) {
    return mMl_send_mail_com(recipient_pid, player_no, present, paper, mail_no, sender_name, proc_type, 0);
}

typedef struct post_office_gift_info_s {
    int mail_no;
    mActor_name_t present;
    mActor_name_t paper;
    int player_received_flag;
    u32 required_balance;
} mMl_PostOffice_Info_c;

static mMl_PostOffice_Info_c l_mml_postoffice_info[mMl_POSTOFFICE_GIFT_NUM] = {
    { 0x0246, FTR_START(FTR_IKE_PST_TESYU01), ITM_PAPER00, mPr_FLAG_POSTOFFICE_GIFT0, 1000000 },
    { 0x0247, FTR_START(FTR_IKE_PST_PIG01), ITM_PAPER00, mPr_FLAG_POSTOFFICE_GIFT1, 10000000 },
    { 0x0248, FTR_START(FTR_YOS_MAILBOX), ITM_PAPER00, mPr_FLAG_POSTOFFICE_GIFT2, 100000000 },
    { 0x0249, FTR_START(FTR_NOG_YUBIN), ITM_PAPER00, mPr_FLAG_POSTOFFICE_GIFT3, 999999999 }
};

static void mMl_send_postoffice_mail() {
    // static u8 free_str[16]; // TODO: fix bss ordering
    static u8 debug_name[PLAYER_NAME_LEN] = { 0x91, 0x92, 0x93, 0x94, 0x95, 0x91, 0x00, 0x00 };

    Private_c* priv = Save_Get(private_data);
    mMl_PostOffice_Info_c* po_info;
    int town_name_len;
    int i;

    town_name_len = mLd_GetLandNameStringAddMura(free_str);
    mHandbill_Set_free_str(0, free_str, town_name_len);

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
            int j;

            mHandbill_Set_free_str(1, priv->player_ID.player_name, PLAYER_NAME_LEN);
            po_info = l_mml_postoffice_info;
            for (j = 0; j < mMl_POSTOFFICE_GIFT_NUM; j++) {
                if ((priv->bank_account >= po_info->required_balance) &&
                    (priv->state_flags & po_info->player_received_flag) == FALSE) {
                    int res = mMl_send_mail_com(&priv->player_ID, i, po_info->present, po_info->paper, po_info->mail_no,
                                                debug_name, 0, 10);

                    if (res == TRUE) {
                        priv->state_flags |= po_info->player_received_flag;
                    }

                    break;
                }

                po_info++;
            }
        }

        priv++;
    }
}

extern void mMl_start_send_mail() {
    mMl_send_postoffice_mail();
}
