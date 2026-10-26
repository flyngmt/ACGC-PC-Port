#include "pc_platform.h"
#include "m_common_data.h"

#include <dolphin/os.h>

int pc_clock_minutes(void) {
    lbRTC_time_c rtc;
    OSCalendarTime host;
    int hour, minute;

    if (Common_Get(time.rtc_enabled) == TRUE && Common_Get(time.rtc_crashed) == FALSE) {
        lbRTC_GetTime(&rtc);
        return rtc.hour * 60 + rtc.min;
    }

    OSTicksToCalendarTime(OSGetTime(), &host);
    hour = g_pc_time_override >= 0 ? g_pc_time_override : host.hour;
    minute = g_pc_min_override >= 0 ? g_pc_min_override : host.min;
    return hour * 60 + minute;
}
