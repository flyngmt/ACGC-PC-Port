#include "m_handbill.h"

#include "jsyswrap.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_font.h"
#include "libultra/libultra.h"

static u32 Ps_table_rom_start;
static u32 Ps_rom_start;
static u32 Handbill_table_rom_start;
static u32 Handbill_rom_start;
static u32 Super_table_rom_start;
static u32 Super_rom_start;
static u32 Handbillz_rom_start;
static u32 Handbillz_start;

static void mHandbillz_aram_init();

extern void mHandbill_aram_init() {
    Ps_table_rom_start = JW_GetAramAddress(RESOURCE_PS_TABLE);
    Ps_rom_start = JW_GetAramAddress(RESOURCE_PS);

    Handbill_table_rom_start = JW_GetAramAddress(RESOURCE_MAIL_TABLE);
    Handbill_rom_start = JW_GetAramAddress(RESOURCE_MAIL);

    Super_table_rom_start = JW_GetAramAddress(RESOURCE_SUPER_TABLE);
    Super_rom_start = JW_GetAramAddress(RESOURCE_SUPER);

    Handbillz_rom_start = JW_GetAramAddress(RESOURCE_MAILA);
    Handbillz_start = 0;

    mHandbillz_aram_init();
}

static mHandbill_Data_c mHandbill_data;

static void mHandbill_clr_force_art() {
    mHandbill_data.force_art = mIN_ARTICLE_NUM;
}

static void mHandbill_clr_capital_flag() {
#ifndef BUGFIXES
    mHandbill_data.force_art = mIN_ARTICLE_NUM; // copy-paste error
#else
    mHandbill_data.capital_flag = FALSE;
#endif
}

static void mHandbill_load_init() {
    mHandbill_clr_force_art();
    mHandbill_clr_capital_flag();
}

extern void mHandbill_Set_free_str(int str_num, u8* str, int str_len) {
    int i;
    int j;
    u8* free_str;
    mHandbill_Data_c* handbill_data;

    if (str_num < 0) {
        return;
    }

    if (str_num >= mHandbill_FREE_STR_NUM) {
        return;
    }

    if (str == NULL) {
        return;
    }

    handbill_data = &mHandbill_data;
    free_str = handbill_data->free_str[str_num];

    if (str_len > mHandbill_FREE_STR_LEN) {
        str_len = mHandbill_FREE_STR_LEN;
    }

    for (i = 0; i < str_len; i++) {
        free_str[i] = str[i];
    }

    for (j = i; j < mHandbill_FREE_STR_LEN; j++) {
        free_str[j] = CHAR_SPACE;
    }

    handbill_data->free_str_art[str_num] = mIN_ARTICLE_NONE;
}

extern void mHandbill_Set_free_str_art(int str_num, u8* str, int str_len, int article) {
    mHandbill_Set_free_str(str_num, str, str_len);
    mHandbill_data.free_str_art[str_num] = article;
}

static void mHandbill_CopyString(u8* dst, u8* src, int len) {
    int i;

    for (i = 0; i < len; i++) {
        *dst++ = *src++;
    }
}

extern int mHandbill_MoveDataCut(u8* data, int buf_size, int dst_idx, int src_idx, int data_len, int fill_type) {
    int new_len = data_len;

    if (dst_idx < src_idx) {
        for (src_idx; src_idx < data_len; src_idx++) {
            data[dst_idx] = data[src_idx];
            dst_idx++;
        }

        new_len -= src_idx - dst_idx;

        if (fill_type != mHandbill_FILL_NONE) {
            u8 fill_char;

            if (fill_type == mHandbill_FILL_RETURN) {
                fill_char = CHAR_NEW_LINE;
            } else {
                fill_char = CHAR_SPACE;
            }

            while (dst_idx < data_len) {
                data[dst_idx++] = fill_char;
            }
        }
    } else if (dst_idx > src_idx) {
        int move_size = data_len - src_idx;
        int i;
        u8* dst;
        u8* src;

        new_len += dst_idx - src_idx;
        if (new_len > buf_size) {
            data_len -= new_len - buf_size;
            move_size -= new_len - buf_size;
            new_len = buf_size;
        }

        dst = data + new_len - 1;
        src = data + data_len - 1;
        for (i = 0; i < move_size; i++) {
            *dst-- = *src--;
        }
    }

    return new_len;
}

static int mHandbill_Put_String_FREE(u8* str, int buf_size, int start_idx, int str_len, int str_no, int fill_type) {
    int code_size;
    int free_str_len;
    int cut_len;
    int article;
    int temp;

    if (str_no < mHandbill_FREE_STR0 || str_no >= mHandbill_FREE_STR_NUM) {
        str_no = mHandbill_FREE_STR0;
    }

    code_size = mFont_CodeSize_idx_get(str, start_idx);
    free_str_len = mMsg_Get_Length_String(mHandbill_data.free_str[str_no], mHandbill_FREE_STR_LEN);
    cut_len = mHandbill_MoveDataCut(str, buf_size, start_idx + free_str_len, start_idx + code_size, str_len, fill_type);

    if (cut_len >= buf_size && free_str_len > buf_size - start_idx) {
        free_str_len = buf_size - start_idx;
    }

    mHandbill_CopyString(&str[start_idx], mHandbill_data.free_str[str_no], free_str_len);

    switch (mHandbill_data.force_art) {
        default:
            article = mHandbill_data.force_art;
            break;

        case mIN_ARTICLE_NUM:
            article = mHandbill_data.free_str_art[str_no];
            break;
    }

    if (article != mIN_ARTICLE_NONE) {
        u8 article_buf[32];

        mString_Load_ArticleFromRom(article_buf, 16, article);  // Load string from string file into buffer
        free_str_len = mMsg_Get_Length_String(article_buf, 16); // Get length of article
        article_buf[free_str_len] = CHAR_SPACE;                 // Add a space to the end of the article
        cut_len = mHandbill_MoveDataCut(str, buf_size, start_idx + free_str_len + 1, start_idx, cut_len,
                                        mHandbill_FILL_NONE);                 // Create free space for the article
        mHandbill_CopyString(&str[start_idx], article_buf, free_str_len + 1); // Copy article to allocated space
    }

    if (mHandbill_data.capital_flag) {
        str[start_idx] = mFont_small_to_capital(str[start_idx]);
    }

    mHandbill_clr_force_art();
    mHandbill_clr_capital_flag();

    return cut_len;
}

static int mHandbill_Put_String_FREE0(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR0, fill_type);
}

static int mHandbill_Put_String_FREE1(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR1, fill_type);
}

static int mHandbill_Put_String_FREE2(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR2, fill_type);
}

static int mHandbill_Put_String_FREE3(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR3, fill_type);
}

static int mHandbill_Put_String_FREE4(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR4, fill_type);
}

static int mHandbill_Put_String_FREE5(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR5, fill_type);
}

static int mHandbill_Put_String_FREE6(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR6, fill_type);
}

static int mHandbill_Put_String_FREE7(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR7, fill_type);
}

static int mHandbill_Put_String_FREE8(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR8, fill_type);
}

static int mHandbill_Put_String_FREE9(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR9, fill_type);
}

static int mHandbill_Put_String_FREE10(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR10, fill_type);
}

static int mHandbill_Put_String_FREE11(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR11, fill_type);
}

static int mHandbill_Put_String_FREE12(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR12, fill_type);
}

static int mHandbill_Put_String_FREE13(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR13, fill_type);
}

static int mHandbill_Put_String_FREE14(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR14, fill_type);
}

static int mHandbill_Put_String_FREE15(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR15, fill_type);
}

static int mHandbill_Put_String_FREE16(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR16, fill_type);
}

static int mHandbill_Put_String_FREE17(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR17, fill_type);
}

static int mHandbill_Put_String_FREE18(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR18, fill_type);
}

static int mHandbill_Put_String_FREE19(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR19, fill_type);
}

static int mHandbill_Cut_Article(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    int code_size = mFont_CodeSize_idx_get(buf, start_idx);

    mHandbill_data.force_art = mIN_ARTICLE_NONE;
    return mHandbill_MoveDataCut(buf, buf_size, start_idx, start_idx + code_size, str_len,
                                 mHandbill_FILL_NONE); // remove the control code characters
}

static int mHandbill_Capital_Letter(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    int code_size = mFont_CodeSize_idx_get(buf, start_idx);

    mHandbill_data.capital_flag = TRUE;
    return mHandbill_MoveDataCut(buf, buf_size, start_idx, start_idx + code_size, str_len,
                                 mHandbill_FILL_NONE); // remove the control code characters
}

typedef int (*mHandbill_PUT_STRING_PROC)(u8*, int, int, int, int);

static int mHandbill_Put_String(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    static const mHandbill_PUT_STRING_PROC proc[mFont_CONT_CODE_NUM] = { NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         &mHandbill_Put_String_FREE0,
                                                                         &mHandbill_Put_String_FREE1,
                                                                         &mHandbill_Put_String_FREE2,
                                                                         &mHandbill_Put_String_FREE3,
                                                                         &mHandbill_Put_String_FREE4,
                                                                         &mHandbill_Put_String_FREE5,
                                                                         &mHandbill_Put_String_FREE6,
                                                                         &mHandbill_Put_String_FREE7,
                                                                         &mHandbill_Put_String_FREE8,
                                                                         &mHandbill_Put_String_FREE9,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         &mHandbill_Put_String_FREE10,
                                                                         &mHandbill_Put_String_FREE11,
                                                                         &mHandbill_Put_String_FREE12,
                                                                         &mHandbill_Put_String_FREE13,
                                                                         &mHandbill_Put_String_FREE14,
                                                                         &mHandbill_Put_String_FREE15,
                                                                         &mHandbill_Put_String_FREE16,
                                                                         &mHandbill_Put_String_FREE17,
                                                                         &mHandbill_Put_String_FREE18,
                                                                         &mHandbill_Put_String_FREE19,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         &mHandbill_Cut_Article,
                                                                         &mHandbill_Capital_Letter,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,
                                                                         NULL };

    int type = buf[start_idx + 1];
    if (type >= mFont_CONT_CODE_BEGIN && type < mFont_CONT_CODE_NUM) {
        mHandbill_PUT_STRING_PROC p = proc[type];

        if (p != NULL) {
            return (*p)(buf, buf_size, start_idx, str_len, fill_type);
        }
    }

    return str_len;
}

static void mHandbill_Change_ControlCode(u8* buf, int buf_size, int str_len, int fill_type) {
    int pos = 0;
    int len = str_len;

    while (pos < len && pos < buf_size) {
        if (buf[pos] == CHAR_CONTROL_CODE) {
            len = mHandbill_Put_String(buf, buf_size, pos, len, fill_type);
        } else {
            pos++;
        }
    }
}

static void mHandbill_Change_ControlCode2(u8* buf, int buf_size, int str_len, int* header_back_start, int fill_type) {
    int now_str_len;

    int pos = 0;
    int len = str_len;

    while (pos < len && pos < buf_size) {
        if (buf[pos] == CHAR_CONTROL_CODE) {
            now_str_len = len;
            len = mHandbill_Put_String(buf, buf_size, pos, len, fill_type);

            if (pos < *header_back_start) {
                *header_back_start += len - now_str_len;
            }
        } else {
            pos++;
        }
    }
}

static void mHandbill_Get_SuperStringDataAddressAndSize(int super_no, u32* addr, u32* size) {
    mMsg_Get_BodyParam(Super_table_rom_start, Super_rom_start, super_no, addr, size);
}

static void mHandbill_Get_PsStringDataAddressAndSize(int ps_no, u32* addr, u32* size) {
    mMsg_Get_BodyParam(Ps_table_rom_start, Ps_rom_start, ps_no, addr, size);
}

static void mHandbill_Get_MailStringDataAddressAndSize(int mail_no, u32* addr, u32* size) {
    mMsg_Get_BodyParam(Handbill_table_rom_start, Handbill_rom_start, mail_no, addr, size);
}

static void mHandbill_CheckSuperStringBorderAndCopy(u8* dst, int dst_size, int* header_back_start, u8* src,
                                                    int src_size) {
    int src_pos;
    int lines;
    int dst_pos;
    u8* src_p = src;
    u8* dst_p = dst;
    int i;

    lines = 0;
    dst_pos = 0;
    src_pos = 0;

    for (i = 0; i < src_size; i++) {
        if (*src_p == CHAR_NEW_LINE) {
            *header_back_start = src_pos;
            lines++;
        } else if (dst_pos < dst_size) {
            *dst_p = *src_p;
            dst_p++;
            dst_pos++;
        }

        src_p++;
        src_pos++;
    }

    if (lines != 1) {
        *header_back_start = src_size;
    }
}

static void mHandbill_Load_SuperStringFromRom(u8* buf, int buf_size, int* header_back_start, int super_no) {
    ATTRIBUTE_ALIGN(32) static u8 buff[90];
    u8 super_buf[43];

    u32 super_address;
    u32 super_size;
    int temp_header_back_start;
    s32 tmp_size;

    if (super_no >= 0 && super_no < mHandbill_MAIL_NUM) {
        tmp_size = buf_size;
        mHandbill_Get_SuperStringDataAddressAndSize(super_no, &super_address, &super_size);
        mem_clear(buf, tmp_size, CHAR_SPACE);

        if (super_address != 0 && super_size != 0) {
            u32 aligned_addr = ALIGN_PREV(super_address, 32); // align to 32 bytes for ARAM DMA
            u32 data_ofs = super_address - aligned_addr;      // calculate offset for desired data
            u32 size = ALIGN_NEXT(data_ofs + super_size, 32);
            int i;
            int move_size;
            u8* dst;
            u8* src;

            bzero(buff, 90);
            _JW_GetResourceAram(aligned_addr, buff, size);

            src = buff + data_ofs;
            dst = buff;
            move_size = super_size;
            /* Move desired data to begining of buffer */
            for (i = 0; i < move_size; i++) {
                *dst++ = *src++;
            }

            mem_clear(super_buf, 43, CHAR_SPACE);
            mHandbill_CheckSuperStringBorderAndCopy(super_buf, 43, &temp_header_back_start, buff, super_size);
            mHandbill_Change_ControlCode2(super_buf, 43, super_size - 1, &temp_header_back_start, mHandbill_FILL_SPACE);

            bcopy(super_buf, buf, tmp_size < 43 ? buf_size : 43);
            *header_back_start = temp_header_back_start;
        }
    }
}

static void mHandbill_Load_PsStringFromRom(u8* buf, int buf_size, int ps_no) {
    ATTRIBUTE_ALIGN(32) static u8 buff[120];

    if (ps_no >= 0 && ps_no < mHandbill_MAIL_NUM) {
        u32 ps_address;
        u32 ps_size;

        mHandbill_Get_PsStringDataAddressAndSize(ps_no, &ps_address, &ps_size);

        if (ps_size == 0) {
            mem_clear(buf, buf_size, CHAR_SPACE);
        } else if (ps_address != 0) {
            u32 aligned_addr = ALIGN_PREV(ps_address, 32); // align to 32 bytes for ARAM DMA
            u32 data_ofs = ps_address - aligned_addr;      // calculate offset for desired data
            u32 size = ALIGN_NEXT(data_ofs + ps_size, 32);
            int i;
            int sz;
            u8* dst;
            u8* src;

            _JW_GetResourceAram(aligned_addr, buff, size);

            /* Move desired data to output buffer */
            sz = (int)ps_size < buf_size ? ps_size : buf_size;
            dst = buf;
            src = buff + data_ofs;
            for (i = 0; i < sz; i++) {
                // *dst = src[data_ofs + i];
                *dst++ = *src++;
            }

            /* Initialize remaining buffer to spaces */
            for (i; i < buf_size; i++) {
                *dst = CHAR_SPACE;
                dst++;
            }

            /* Do any control code processing */
            mHandbill_Change_ControlCode(buf, buf_size, ps_size, mHandbill_FILL_SPACE);
        }
    }
}

ATTRIBUTE_ALIGN(32) static u8 mHandbill_mail_buff[263];

ATTRIBUTE_ALIGN(32) static u8 mHandbill_mail_buff[263];

static void mHandbill_Load_MailFromRom(u8* buf, int mail_no) {
    if (mail_no >= 0 && mail_no < mHandbill_MAIL_NUM) {
        u32 mail_address;
        u32 mail_size;

        mHandbill_Get_MailStringDataAddressAndSize(mail_no, &mail_address, &mail_size);

        if (mail_size == 0) {
            mem_clear(buf, mHandbill_BODY_LEN, CHAR_NEW_LINE);
        } else if (mail_address != 0) {
            u32 aligned_addr = ALIGN_PREV(mail_address, 32); // align to 32 bytes for ARAM DMA
            u32 data_ofs = mail_address - aligned_addr;      // calculate offset for desired data
            u32 size = ALIGN_NEXT(data_ofs + mail_size, 32);

            _JW_GetResourceAram(aligned_addr, mHandbill_mail_buff, size);

            /* Move desired data to output buffer */
            {
                int i;
                int j;
                u8* dst = buf;
                u8* src = &mHandbill_mail_buff[data_ofs];
                int sz = mHandbill_BODY_LEN;

                if (mail_size < mHandbill_BODY_LEN) {
                    sz = mail_size;
                }

                for (i = 0; i < sz; i++) {
                    *dst++ = *src++;
                }

                /* Initialize remaining buffer to spaces */
                for (i; i < mHandbill_BODY_LEN; i++) {
                    *dst++ = CHAR_NEW_LINE;
                }

                /* Do any control code processing */
                mHandbill_Change_ControlCode(buf, mHandbill_BODY_LEN, sz, mHandbill_FILL_RETURN);
            }
        }
    }
}

extern void mHandbill_Load_HandbillFromRom(u8* header, int* header_back_start, u8* footer, u8* body, int mail_no) {
    mHandbill_load_init();
    mHandbill_Load_SuperStringFromRom(header, mHandbill_HEADER_LEN, header_back_start, mail_no);
    mHandbill_Load_PsStringFromRom(footer, mHandbill_FOOTER_LEN, mail_no);
    mHandbill_Load_MailFromRom(body, mail_no);
}

extern void mHandbill_Load_HandbillFromRom2(u8* header, int header_size, int* header_back_start, u8* footer,
                                            int footer_size, u8* body, int mail_no) {
    mHandbill_load_init();
    mHandbill_Load_SuperStringFromRom(header, header_size, header_back_start, mail_no);
    mHandbill_Load_PsStringFromRom(footer, footer_size, mail_no);
    mHandbill_Load_MailFromRom(body, mail_no);
}

static u32 mHandbillz_table_pos[mHandbillz_TYPE_NUM];
static u32 mHandbillz_data_pos[mHandbillz_TYPE_NUM];

static u32 mHandbillz_dummy_size_tbl[mHandbillz_TYPE_NUM] = {
    27,  /* SUPER */
    200, /* MAILA */
    200, /* MAILB*/
    200, /* MAILC */
    34   /* PS */
};

static void mHandbillz_aram_init() {
    mHandbillz_table_pos[mHandbillz_TYPE_SUPER] = JW_GetAramAddress(RESOURCE_SUPERZ_TABLE);
    mHandbillz_data_pos[mHandbillz_TYPE_SUPER] = JW_GetAramAddress(RESOURCE_SUPERZ);

    mHandbillz_table_pos[mHandbillz_TYPE_MAILA] = JW_GetAramAddress(RESOURCE_MAILA_TABLE);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILA] = JW_GetAramAddress(RESOURCE_MAILA);

    mHandbillz_table_pos[mHandbillz_TYPE_MAILB] = JW_GetAramAddress(RESOURCE_MAILB_TABLE);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILB] = JW_GetAramAddress(RESOURCE_MAILB);

    mHandbillz_table_pos[mHandbillz_TYPE_MAILC] = JW_GetAramAddress(RESOURCE_MAILC_TABLE);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILC] = JW_GetAramAddress(RESOURCE_MAILC);

    mHandbillz_table_pos[mHandbillz_TYPE_PS] = JW_GetAramAddress(RESOURCE_PSZ_TABLE);
    mHandbillz_data_pos[mHandbillz_TYPE_PS] = JW_GetAramAddress(RESOURCE_PSZ);
}

typedef struct {
    int type;
    int num;

    u8* ram_buf;
    size_t ram_buf_size;

    u32 dma_addr;
    u32 dma_size;
} mHandbillzDMA_c;

static int mHandbillzDMA_body_addr_set(mHandbillzDMA_c* dma_info) {
    int type = dma_info->type;
    int num = dma_info->num;

    mMsg_Get_BodyParam(mHandbillz_table_pos[type], mHandbillz_data_pos[type], num, &dma_info->dma_addr,
                       &dma_info->dma_size);

    if (dma_info->dma_size > mHandbillz_dummy_size_tbl[dma_info->type]) {
        return FALSE;
    }
    return TRUE;
}

static int mHandbillzDMA_body_load(mHandbillzDMA_c* dma_info) {
    if (mHandbillzDMA_body_addr_set(dma_info)) {
        mem_clear(dma_info->ram_buf, dma_info->ram_buf_size, CHAR_SPACE);

        if (dma_info->dma_size != 0) {
            u32 dma_size = dma_info->dma_size;
            u32 aligned_addr = ALIGN_PREV(dma_info->dma_addr, 32);
            u32 data_ofs = dma_info->dma_addr & (32 - 1);
            u32 size = ALIGN_NEXT(dma_size + data_ofs, 32);

            _JW_GetResourceAram(aligned_addr, dma_info->ram_buf, size);

            if (data_ofs != 0) {
                int i;
                const int size = dma_info->dma_size;
                u8* src;
                u8* dst;

                dst = dma_info->ram_buf;
                src = dst + data_ofs;
                for (i = 0; i < size; i++, dst++, src++) {
                    *dst = *src;
                }
            }
        }

        return TRUE;
    } else {
        return FALSE;
    }
}

static int mHandbillz_super_load(mHandbillz_Info_c* info) {
    ATTRIBUTE_ALIGN(32) static u8 ram[90];
    mHandbillzDMA_c dma_info;

    bzero(ram, 90);

    dma_info.type = mHandbillz_TYPE_SUPER;
    dma_info.num = info->super_no;
    dma_info.ram_buf = ram;
    dma_info.ram_buf_size = 90;

    if (mHandbillzDMA_body_load(&dma_info)) {
        u8 super_buf[43];
        int header_back_start;

        mem_clear(super_buf, 43, CHAR_SPACE);
        mHandbill_CheckSuperStringBorderAndCopy(super_buf, 43, &header_back_start, ram, dma_info.dma_size);
        mHandbill_Change_ControlCode2(super_buf, 43, dma_info.dma_size - 1, &header_back_start, mHandbill_FILL_SPACE);
        mem_clear(info->super_buf_p, info->super_buf_size, CHAR_SPACE);
        bcopy(super_buf, info->super_buf_p, info->super_buf_size < 43 ? info->super_buf_size : 43);

        info->header_back_start = header_back_start;
        return TRUE;
    } else {
        return FALSE;
    }
}

static int mHandbillz_mail_load(mHandbillz_Info_c* info) {
    mHandbillzDMA_c dma_info[3];
    mHandbillzDMA_c* dma_p;
    int i;
    int success = TRUE;
    u32 total_size = 0;
    u8* dst = info->mail_buf_p;

    dma_info[0].type = mHandbillz_TYPE_MAILA;
    dma_info[0].num = info->maila_no;
    dma_info[1].type = mHandbillz_TYPE_MAILB;
    dma_info[1].num = info->mailb_no;
    dma_info[2].type = mHandbillz_TYPE_MAILC;
    dma_info[2].num = info->mailc_no;

    dma_p = dma_info;
    for (i = 0; i < 3 && success; i++, dma_p++) {
        bzero(mHandbill_mail_buff, 263);
        dma_p->ram_buf = mHandbill_mail_buff;
        dma_p->ram_buf_size = 263;

        if (mHandbillzDMA_body_load(dma_p)) {
            total_size += dma_p->dma_size;

            if (total_size <= info->mail_buf_size) {
                bcopy(mHandbill_mail_buff, dst, dma_p->dma_size);
                dst += dma_p->dma_size;
            } else {
                success = FALSE;
            }
        } else {
            success = FALSE;
        }
    }

    if (success) {
        if (info->mail_buf_size > total_size) {
            mem_clear(dst, info->mail_buf_size - total_size, CHAR_NEW_LINE);
        }

        mHandbill_Change_ControlCode(info->mail_buf_p, info->mail_buf_size, total_size, mHandbill_FILL_RETURN);
    }

    return success;
}

static int mHandbillz_ps_load(mHandbillz_Info_c* info) {
    ATTRIBUTE_ALIGN(32) static u8 ram[97];
    mHandbillzDMA_c dma_info;

    bzero(ram, 97);

    dma_info.type = mHandbillz_TYPE_PS;
    dma_info.num = info->ps_no;
    dma_info.ram_buf = ram;
    dma_info.ram_buf_size = 97;

    if (mHandbillzDMA_body_load(&dma_info)) {
        u8 ps_buf[43];

        bcopy(ram, info->ps_buf_p, dma_info.dma_size);

        if (info->ps_buf_size > dma_info.dma_size) {
            mem_clear(info->ps_buf_p + dma_info.dma_size, info->ps_buf_size - dma_info.dma_size, CHAR_SPACE);
        }

        mHandbill_Change_ControlCode(info->ps_buf_p, info->ps_buf_size, dma_info.dma_size, mHandbill_FILL_SPACE);
        return TRUE;
    } else {
        return FALSE;
    }
}

extern int mHandbillz_load(mHandbillz_Info_c* info) {
    int super_res;
    int mail_res;
    int ps_res;
    int res;

    mHandbill_load_init();

    super_res = mHandbillz_super_load(info);
    mail_res = mHandbillz_mail_load(info);
    ps_res = mHandbillz_ps_load(info);
    res = FALSE;

    if (super_res && mail_res && ps_res) {
        res = TRUE;
    }

    return res;
}
