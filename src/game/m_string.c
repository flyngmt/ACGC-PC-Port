#include "m_string.h"

#include "m_msg.h"
#include "jsyswrap.h"
#include "m_lib.h"
#include "m_font.h"
#include "m_mail.h"

ATTRIBUTE_ALIGN(32) static u8 buff[MAIL_BODY_LEN - 1]; // TODO: proper bss ordering
static u32 String_rom_start;
static u32 String_table_rom_start;

extern void mString_aram_init() {
    String_table_rom_start = JW_GetAramAddress(RESOURCE_STRING_TABLE);
    String_rom_start = JW_GetAramAddress(RESOURCE_STRING);
}

static void mString_Get_StringDataAddressAndSize(int string_no, u32* string_addr, u32* string_size) {
    mMsg_Get_BodyParam(String_table_rom_start, String_rom_start, string_no, string_addr, string_size);
}

extern void mString_Load_StringFromRom(u8* dst, int dst_len, int str_no) {
    // static u8 buff[MAIL_BODY_LEN - 1] ATTRIBUTE_ALIGN(32); // TODO: proper bss ordering

    u32 string_data_addr;
    u32 string_size;

    if (str_no >= 0 && str_no < mString_MAX_STR) {
        mString_Get_StringDataAddressAndSize(str_no, &string_data_addr, &string_size);

        if (string_size == 0) {
            mem_clear(dst, dst_len, CHAR_SPACE);
        } else if (string_data_addr != 0) {
            u32 base_addr = ALIGN_PREV(string_data_addr, 32);
            u32 ofs = string_data_addr - base_addr;
            u32 dma_size = ALIGN_NEXT(ofs + string_size, 32);
            int i;
            int copy_size;
            u8* s_dst;
            u8* s_src;

            _JW_GetResourceAram(base_addr, buff, dma_size);
            if (dst_len < (int)string_size) {
                string_size = dst_len;
            }

            s_src = buff + ofs;
            s_dst = dst;
            copy_size = string_size;
            for (i = 0; i < copy_size; i++) {
                *s_dst++ = *s_src++;
            }

            for (i; i < dst_len; i++) {
                *s_dst++ = CHAR_SPACE;
            }
        }
    }
}

extern int mString_Load_YearStringFromRom(u8* dst, lbRTC_year_t year) {
    if (year < lbRTC_YEAR_MIN || year > lbRTC_YEAR_MAX) {
        year = GAME_YEAR_MIN;
    }

    return mFont_UnintToString(dst, 6, year, 6, TRUE, FALSE, FALSE);
}

extern int mString_Load_MonthStringFromRom(u8* dst, lbRTC_month_t month) {
    if (month < lbRTC_JANUARY || month > lbRTC_DECEMBER) {
        month = lbRTC_JANUARY;
    }

    mString_Load_StringFromRom(dst, 9, mString_MONTH_START + month - 1);
    return mMsg_Get_Length_String(dst, 9);
}

extern int mString_Load_WeekStringFromRom(u8* dst, lbRTC_weekday_t weekday) {
    if (weekday > lbRTC_SATURDAY) {
        weekday = lbRTC_SUNDAY;
    }

    mString_Load_StringFromRom(dst, 9, mString_WEEKDAY_START + weekday);
    return mMsg_Get_Length_String(dst, 9);
}

extern int mString_Load_DayStringFromRom(u8* dst, lbRTC_day_t day) {
    if (day < 1 || day > 31) {
        day = 1;
    }

    mString_Load_StringFromRom(dst, 4, mString_DAY_START + day - 1);
    return mMsg_Get_Length_String(dst, 4);
}

extern int mString_Load_HourStringFromRom(u8* dst, lbRTC_hour_t hour) {
    int hour_num_len;
    int clamped_hour;
    int specifier;

    if (hour > 23) {
        hour = 0;
    }

    clamped_hour = hour;
    switch (clamped_hour) {
        case 0:
            clamped_hour = 12;
            break;
        case 12:
            clamped_hour = 12;
            break;

        default:
            clamped_hour %= 12;
            break;
    }

    specifier = hour < 12 ? mString_AM : mString_PM;
    hour_num_len = mFont_UnintToString(dst, 15, clamped_hour, 15, TRUE, FALSE, FALSE);
    dst[hour_num_len] = CHAR_SPACE;
    hour_num_len++;

    /* Load AM/PM string */
    mString_Load_StringFromRom(dst + hour_num_len, 15 - hour_num_len, specifier);
    return mMsg_Get_Length_String(dst, 15);
}

extern int mString_Load_HourStringFromRom2(u8* dst, lbRTC_hour_t hour) {
    int clamped_hour;

    if (hour > 23) {
        hour = 0;
    }

    clamped_hour = hour;
    switch (clamped_hour) {
        case 0:
        case 12:
            clamped_hour = 12;
            break;

        default:
            clamped_hour %= 12;
            break;
    }

    return mFont_UnintToString(dst, 15, clamped_hour, 2, TRUE, FALSE, FALSE);
}

extern int mString_Load_MinStringFromRom(u8* dst, lbRTC_min_t min) {
    if (min > 59) {
        min = 0;
    }

    return mFont_UnintToString(dst, 4, min, 2, TRUE, TRUE, TRUE);
}

extern int mString_Load_SecStringFromRom(u8* dst, lbRTC_sec_t sec) {
    if (sec > 59) {
        sec = 0;
    }

    return mFont_UnintToString(dst, 5, sec, 2, TRUE, TRUE, TRUE);
}

extern int mString_Load_NumberStringAddUnitFromRom(u8* dst, u16 num, int str_no) {
    int num_len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, num, mMsg_FREE_STRING_LEN, TRUE, FALSE, TRUE);
    u8* n_dst = dst + num_len;
    dst[num_len] = CHAR_SPACE;
    num_len++;

    /* Add the unit */
    mString_Load_StringFromRom(dst + num_len, mMsg_FREE_STRING_LEN - num_len, str_no);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}
