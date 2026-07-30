#ifndef ACGC_PC_DOLPHIN_OS_TIMER_H
#define ACGC_PC_DOLPHIN_OS_TIMER_H

/*
 * OSTimer is a libultra compatibility type in this game, not an Aurora OS
 * service.  Code which needs it must include libultra/os_timer.h.  Keeping
 * this header intentionally empty also prevents Aurora's umbrella os.h from
 * falling through to the matching-SDK copy while OSAlarm.h is being parsed.
 */

#endif
