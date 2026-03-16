// pc/time_fix.h
// Y2031 fix for ACGC-PC-Port
// The original game stores the year as (year - 2000) in a 5-bit field,
// giving a max of 31 → year 2031. We patch the save/load and clock
// routines to use a 7-bit extended field (years 2000–2127) in a
// backward-compatible way using reserved save data bytes.

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// ── Original game date struct (matches ac-decomp OSCalendar / RTC layout) ──

// The GC RTC counts seconds since 2000-01-01 00:00:00 as a u32.
// Max u32 value: 4,294,967,295 seconds ≈ year 2136. The RTC hardware
// is fine — the bug is entirely in how the game VALIDATES and CLAMPS
// the year when converting from/to its packed save format.

typedef struct {
    uint8_t  second;   // 0-59
    uint8_t  minute;   // 0-59
    uint8_t  hour;     // 0-23
    uint8_t  day;      // 1-31
    uint8_t  month;    // 1-12
    // Original: year stored as u8 but only 5 bits used (0-31 → 2000-2031)
    // Our fix:  treat the full u8 as (year - 2000), giving 2000-2255.
    //           Save data that wrote e.g. 0x1F (31→2031) now reads correctly.
    uint8_t  year_offset; // year - 2000, now 0-255 instead of 0-31
    uint8_t  weekday;  // 0=Sun ... 6=Sat
    uint8_t  _pad;
} ACDateTime;

// ── PC port time source ─────────────────────────────────────────────────────

// Replaces the GC RTC read. Returns wall-clock time from the OS.
// The original GC code called OSGetTime() → converted via a lookup table.
// On PC we just use time()/localtime() and fill the struct directly.
static inline void ac_get_current_time(ACDateTime* out) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    out->second      = (uint8_t)t->tm_sec;
    out->minute      = (uint8_t)t->tm_min;
    out->hour        = (uint8_t)t->tm_hour;
    out->day         = (uint8_t)t->tm_mday;
    out->month       = (uint8_t)(t->tm_mon + 1);   // tm_mon is 0-based
    // tm_year is years since 1900; tm_year - 100 = years since 2000.
    // Store the raw offset — no clamping. Works through year 2255.
    out->year_offset = (uint8_t)(t->tm_year - 100);
    out->weekday     = (uint8_t)t->tm_wday;         // 0=Sun, matches AC
    out->_pad        = 0;
}

// Recover a full 4-digit year from our fixed struct.
static inline int ac_get_year(const ACDateTime* dt) {
    return 2000 + (int)dt->year_offset;
}

// ── Save data patch ─────────────────────────────────────────────────────────

// The original save encodes the clock into the GCI header and player
// data using a packed bitfield. In the decomp this lives in
// "JFCheckSum" / "fopAcM_getGameTime" territory.
//
// Original packing (16-bit date word, little-endian):
//   bits 15-11 : year offset (5 bits, 0-31)
//   bits 10-7  : month       (4 bits, 1-12)
//   bits  6-1  : day         (6 bits, 1-31) ... [sic — only 5 needed but 6 allocated]
//   bit   0    : unused
//
// Fixed packing (we repurpose the unused bit + upper byte of a nearby
// reserved u16 to store the high bits of the year, giving 8-bit year offset):
//
// We use a "magic" sentinel in the save's reserved region to signal
// that extended year data is present, so old saves still load correctly.

#define AC_SAVE_YEAR_MAGIC  0xAC31u   // sentinel: "AC 2031 fix active"

typedef struct {
    uint16_t packed_date;        // original 16-bit date word (kept intact)
    uint16_t extended_year_magic;// AC_SAVE_YEAR_MAGIC if extended data valid
    uint8_t  extended_year_hi;   // high byte of year_offset (always 0 for
                                 // years ≤ 2255, but future-proofs to 2511)
    uint8_t  _reserved[3];
} ACSaveDateBlock;

// Pack a date into the save block.
// Writes both the original 5-bit field (for compatibility with Dolphin/
// original hardware if needed) and the extended field.
static inline void ac_pack_save_date(ACSaveDateBlock* block,
                                      const ACDateTime* dt)
{
    // Original 16-bit word — keep year clamped to 5 bits for the
    // vanilla field so Dolphin-imported saves don't look corrupted.
    uint8_t vanilla_year = dt->year_offset & 0x1F; // low 5 bits only
    block->packed_date =
        (uint16_t)(((vanilla_year & 0x1F) << 11) |
                   ((dt->month   & 0x0F) <<  7) |
                   ((dt->day     & 0x3F) <<  1));

    // Extended field: full year offset, no clamping.
    block->extended_year_magic = AC_SAVE_YEAR_MAGIC;
    block->extended_year_hi    = (uint8_t)(dt->year_offset >> 5);
    // (For years 2000-2127: year_offset is 0-127, so hi = 0 or 1.
    //  The 5 low bits come from vanilla_year above.)
}

// Unpack a date from the save block.
// If extended magic is present, use full year. Otherwise fall back to
// the vanilla 5-bit year (graceful degradation for old saves).
static inline void ac_unpack_save_date(const ACSaveDateBlock* block,
                                        ACDateTime* out)
{
    uint8_t vanilla_year = (uint8_t)((block->packed_date >> 11) & 0x1F);
    out->month = (uint8_t)((block->packed_date >>  7) & 0x0F);
    out->day   = (uint8_t)((block->packed_date >>  1) & 0x3F);

    if (block->extended_year_magic == AC_SAVE_YEAR_MAGIC) {
        // Extended: reconstruct full 8-bit year_offset from hi + low 5 bits.
        out->year_offset = (uint8_t)((block->extended_year_hi << 5) |
                                      (vanilla_year & 0x1F));
    } else {
        // Old save: use vanilla 5-bit value as-is (2000-2031).
        out->year_offset = vanilla_year;
    }
}

// ── Validation patch ────────────────────────────────────────────────────────

// The original game has a validation function that rejects years outside
// [2000, 2031] and resets to 2000 if out of range. This is the proximate
// cause of the loop. On the PC port we replace it with a wide-range check.

static inline bool ac_validate_datetime(const ACDateTime* dt) {
    int year = ac_get_year(dt);
    if (year < 2000 || year > 2999) return false; // sane upper bound
    if (dt->month < 1 || dt->month > 12) return false;
    if (dt->day   < 1 || dt->day   > 31) return false;
    if (dt->hour  > 23) return false;
    if (dt->minute > 59) return false;
    if (dt->second > 59) return false;
    return true;
}

// ── Event calendar patch ────────────────────────────────────────────────────

// Several seasonal events (New Year's, Sports Fair, Harvest Festival, etc.)
// are looked up by year % 28 for the day-of-week anchor (the Gregorian
// calendar repeats every 28 years). The original code uses a precomputed
// table indexed 0-28, which is fine — but the year is fed into it after
// being clamped to 2000-2031, breaking events post-2031.
//
// Fix: compute the calendar anchor from the unclamped year directly.

static inline int ac_calendar_cycle_index(int full_year) {
    // Gregorian 28-year cycle anchor relative to year 2000.
    return (full_year - 2000) % 28;
}

// Wrapper to call instead of the original hardcoded year-table lookup.
// The original looked up gCalendarTable[year - 2000] where year was
// pre-clamped. We pass the full year and mod it ourselves.
static inline int ac_event_day_anchor(int full_year, const int* calendar_table_28) {
    return calendar_table_28[ac_calendar_cycle_index(full_year)];
}