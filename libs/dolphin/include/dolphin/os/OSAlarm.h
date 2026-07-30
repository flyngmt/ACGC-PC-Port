#ifndef DOLPHIN_OS_ALARM_H
#define DOLPHIN_OS_ALARM_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSContext.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSAlarm  OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm
{
    OSAlarmHandler handler;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;

    // Periodic alarm
    OSTime period;
    OSTime start;
};

void OSInitAlarm(void);
void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);
void OSSetAbsAlarm(OSAlarm *alarm, OSTime time, OSAlarmHandler handler);
void OSSetPeriodicAlarm(OSAlarm *alarm, OSTime start, OSTime period,
                        OSAlarmHandler handler);
void OSCreateAlarm(OSAlarm *alarm);
void OSCancelAlarm(OSAlarm *alarm);

BOOL OSCheckAlarmQueue(void);

#ifdef __cplusplus
}
#endif

#endif  // DOLPHIN_OS_ALARM_H
