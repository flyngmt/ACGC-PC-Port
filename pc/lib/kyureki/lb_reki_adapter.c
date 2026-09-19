/* NONMATCHING enhancement adapter, not an original-binary reconstruction.
 * Replace the original lb_reki.c exports; do NOT link both implementations.
 * Host-tested using minimal interface stubs, NOT built with the GameCube SDK.
 *
 * Legacy month 13 denotes the year's sole leap month, NOT chronological month
 * 13. The core instead stores (month number 1..12, leap flag) chronologically.
 * This adapter has a two-year main-thread-only cache. Core API is caller-cached and
 * reentrant; use it directly for multithreaded callers or alternate astronomy.
 *
 * Intentional behavior change: harvest moon means regular lunar 8/15 in EVERY
 * year. This does not reproduce the original 2002..2030 festival overrides.
 * Existing void harvest callers MUST handle the documented zero-date failure,
 * or preferably migrate to lbRk_TryHarvestMoonDay and check its return value.
 */
#include "lb_reki.h"
#include "kyureki.h"
#include <stddef.h>

static qk_year cached_year[2];
static int have_cached_year[2];
static int next_cache;
static const qk_year *get_year(int year)
{
    int i, slot;
    for (i = 0; i < 2; ++i)
        if (have_cached_year[i] && cached_year[i].year == year) return &cached_year[i];
    slot = next_cache;
    if (qk_build_year(year, NULL, &cached_year[slot]) != QK_OK) return NULL;
    have_cached_year[slot] = 1;
    next_cache = 1 - slot;
    return &cached_year[slot];
}
static void write_date(lbRTC_ymd_c *out, const qk_gregorian *date)
{
    out->year = (lbRTC_year_t)date->year;
    out->month = (lbRTC_month_t)date->month;
    out->day = (lbRTC_day_t)date->day;
}
int lbRk_ToSeiyouReki(lbRTC_ymd_c *out, lbRTC_ymd_c *in)
{
    const qk_year *year;
    qk_gregorian result;
    int month, leap, i;
    if (!out || !in) return 0;
    year = get_year((int)in->year);
    if (!year) return 0;
    month = (int)in->month;
    leap = month == lbRk_KYUU_LEAP_MONTH;
    if (leap) {
        month = 0;
        for (i = 0; i < year->count; ++i)
            if (year->months[i].leap) month = year->months[i].number;
    }
    if (qk_to_gregorian(year, month, (int)in->day, leap, &result) != QK_OK)
        return 0;
    write_date(out, &result);
    return 1;
}
int lbRk_ToKyuuReki(lbRTC_ymd_c *out, lbRTC_ymd_c *in)
{
    qk_gregorian date;
    qk_date result;
    const qk_year *year;
    long ignored;
    int candidate;
    qk_status status;
    if (!out || !in) return 0;
    date.year = (int)in->year;
    date.month = (int)in->month;
    date.day = (int)in->day;
    if (qk_gregorian_to_jdn(&date, &ignored) != QK_OK) return 0;
    for (candidate = date.year; candidate >= date.year - 1; --candidate) {
        if (candidate < QK_MIN_YEAR || candidate > QK_MAX_YEAR) continue;
        year = get_year(candidate);
        if (!year) return 0;
        status = qk_from_gregorian(year, &date, &result);
        if (status == QK_OK) {
            out->year = (lbRTC_year_t)result.year;
            out->month = (lbRTC_month_t)(result.leap ? lbRk_KYUU_LEAP_MONTH : result.month);
            out->day = (lbRTC_day_t)result.day;
            return 1;
        }
        if (status != QK_DATE_NOT_IN_YEAR) return 0;
    }
    return 0;
}
int lbRk_VernalEquinoxDay(int year)
{
    qk_gregorian date;
    return qk_equinox(year, 0, NULL, &date) == QK_OK ? date.day : 0;
}
int lbRk_AutumnalEquinoxDay(int year)
{
    qk_gregorian date;
    return qk_equinox(year, 1, NULL, &date) == QK_OK ? date.day : 0;
}
int lbRk_TryHarvestMoonDay(lbRTC_ymd_c *out, int year)
{
    const qk_year *calendar;
    qk_gregorian date;
    if (!out) return 0;
    calendar = get_year(year);
    if (!calendar || qk_to_gregorian(calendar, 8, 15, 0, &date) != QK_OK) return 0;
    write_date(out, &date);
    return 1;
}
void lbRk_HarvestMoonDay(lbRTC_ymd_c *out, int year)
{
    if (out && !lbRk_TryHarvestMoonDay(out, year)) {
        out->year = 0;
        out->month = 0;
        out->day = 0;
    }
}
