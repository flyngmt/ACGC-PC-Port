/* TODO: not sure if this should live here or in libultra/OSTimer.h */

#ifndef DOLPHIN_OS_TIMER_H
#define DOLPHIN_OS_TIMER_H

#include "types.h"
#include "dolphin/os/OSAlarm.h"
#include "dolphin/os/OSMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSTimer_s {
    OSAlarm alarm;
    struct OSTimer_s* next;
    struct OSTimer_s* prev;
    OSTime interval;
    OSTime value;
    OSMessageQueue* mq;
    OSMessage msg;
} OSTimer;

#ifdef __cplusplus
}
#endif

#endif
