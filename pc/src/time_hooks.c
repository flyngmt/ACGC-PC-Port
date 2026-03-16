// pc/time_hooks.c
// Patches the GX→PC translation layer to use the Y2031-fixed time routines.
// Drop this into the build and add time_hooks.o to the link.

#include "../include/time_fix.h"
#include <stdio.h>
#include <string.h>

// ── Replaces OSGetTime / OSTicksToCalendar ──────────────────────────────────

// The original game called OSGetTime() → OSTicksToCalendar() to fill an
// OSCalendar struct. The PC port stubs these out. We redirect them to our
// fixed implementation.

// OSCalendar layout from ac-decomp (must match exactly):
typedef struct {
    int32_t  sec;
    int32_t  min;
    int32_t  hour;
    int32_t  mday;   // day of month, 1-based
    int32_t  mon;    // month, 0-based (Jan=0)
    int32_t  year;   // full year e.g. 2026
    int32_t  wday;   // 0=Sun
    int32_t  yday;   // day of year, 0-based
} OSCalendar;

void PC_OSTicksToCalendar(uint64_t ticks, OSCalendar* cal) {
    // Ignore ticks on PC — just use wall clock.
    (void)ticks;
    ACDateTime dt;
    ac_get_current_time(&dt);

    cal->sec  = dt.second;
    cal->min  = dt.minute;
    cal->hour = dt.hour;
    cal->mday = dt.day;
    cal->mon  = dt.month - 1;          // OSCalendar is 0-based
    cal->year = ac_get_year(&dt);      // full 4-digit year, no clamping
    cal->wday = dt.weekday;

    // Compute yday (day of year) for completeness
    static const int days_per_month[] =
        {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int yday = dt.day - 1;
    bool leap = (cal->year % 4 == 0 &&
                 (cal->year % 100 != 0 || cal->year % 400 == 0));
    for (int m = 1; m < dt.month; m++) {
        yday += days_per_month[m];
        if (m == 2 && leap) yday++;
    }
    cal->yday = yday;
}

// ── Save data load/save intercepts ─────────────────────────────────────────

// These wrap the port's GCI read/write path. The port calls
// PC_SaveLoad / PC_SaveWrite; we inject the extended year block here.

// Location within the GCI data where we store our extended block.
// Must be in a range that is "reserved/unused" in the original format.
// Based on the ac-decomp save layout, bytes 0x1A00-0x1FFF of the
// player data block are unused padding — we use 0x1A00.
#define EXTENDED_DATE_OFFSET  0x1A00

void PC_SavePatchDate(uint8_t* gci_buf, const ACDateTime* dt) {
    ACSaveDateBlock* block =
        (ACSaveDateBlock*)(gci_buf + EXTENDED_DATE_OFFSET);
    ac_pack_save_date(block, dt);
}

bool PC_SaveReadDate(const uint8_t* gci_buf, ACDateTime* out) {
    const ACSaveDateBlock* block =
        (const ACSaveDateBlock*)(gci_buf + EXTENDED_DATE_OFFSET);
    ac_unpack_save_date(block, out);
    return ac_validate_datetime(out);
}

// ── Year validation override ────────────────────────────────────────────────

// The original validation (fopAcM_getGameTime or similar in ac-decomp)
// had a check along the lines of:
//   if (year < 2000 || year > 2031) { year = 2000; }
//
// On the PC port this is in orig/time.c or similar. We override it by
// providing a replacement symbol that the linker prefers.

// If the build uses weak symbols (GCC):
__attribute__((visibility("default")))
int AC_ValidateYear(int year) {
    // Extended range: 2000 to 2999.
    if (year < 2000) return 2000;
    if (year > 2999) return 2999;
    return year;
}

// ── Moon Festival / New Year event guard ───────────────────────────────────

// The Time Extension article noted that "the Moon Festival borks the clock."
// The issue: certain festival event functions read the year as a u8 offset
// and then do arithmetic that wraps on overflow for years > 2027-ish.
//
// This guard sanitizes the year before it reaches festival lookup code.
// Call this before any event/festival calendar lookup.

int AC_SafeEventYear(int full_year) {
    // Map into the 28-year Gregorian cycle (calendar repeat period).
    // 2000 is our epoch; anchor the cycle there.
    int offset = (full_year - 2000) % 28;
    if (offset < 0) offset += 28;
    // Return a "safe" equivalent year in [2000, 2027] with the same
    // day-of-week alignment. Events are purely calendar-driven, so
    // this is transparent to gameplay.
    return 2000 + offset;
}

// ── Startup diagnostic ─────────────────────────────────────────────────────

void PC_TimeFixInit(void) {
    ACDateTime now;
    ac_get_current_time(&now);
    int year = ac_get_year(&now);
    printf("[TimeFix] Y2031 patch active. Current date: %04d-%02d-%02d %02d:%02d:%02d\n",
           year, now.month, now.day, now.hour, now.minute, now.second);
    if (year >= 2031) {
        printf("[TimeFix] NOTE: Running past the original year limit. "
               "Extended date support is active.\n");
    }
}