#include "dolphin/os/OSAlarm.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSException.h"

struct OSAlarmQueue {
    struct OSAlarm* head;
    struct OSAlarm* tail;
};

static struct OSAlarmQueue AlarmQueue;

static void DecrementerExceptionHandler(u8, OSContext*);

static void SetTimer(struct OSAlarm* alarm) {
    OSTime delta = alarm->fire - __OSGetSystemTime();

    if (delta < 0) {
        PPCMtdec(0);
    } else if (delta < 0x80000000) {
        PPCMtdec((u32)delta);
    } else {
        PPCMtdec(0x7fffffff);
    }
}

void OSInitAlarm(void) {

    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler) {
        AlarmQueue.tail = 0;
        AlarmQueue.head = 0;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler);
    }
}
void OSCreateAlarm(OSAlarm* alarm) {
    alarm->handler = NULL;
}

static void InsertAlarm(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler) {
    OSAlarm* next;
    OSAlarm* prev;

    if (0 < alarm->period) {
        OSTime time = __OSGetSystemTime();

        fire = alarm->start;
        if (alarm->start < time) {
            fire += alarm->period * ((time - alarm->start) / alarm->period + 1);
        }
    }

    alarm->handler = handler;
    alarm->fire = fire;

    for (next = AlarmQueue.head; next; next = next->next) {
        if (next->fire <= fire) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;

        if (prev) {
            prev->next = alarm;
        } else {
            AlarmQueue.head = alarm;
            SetTimer(alarm);
        }

        return;
    }

    alarm->next = 0;
    prev = AlarmQueue.tail;
    AlarmQueue.tail = alarm;
    alarm->prev = prev;

    if (prev) {
        prev->next = alarm;
    } else {
        AlarmQueue.head = AlarmQueue.tail = alarm;
        SetTimer(alarm);
    }
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler) {
    BOOL enabled;
    enabled = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);
    OSRestoreInterrupts(enabled);
}

void OSCancelAlarm(OSAlarm* alarm) {
    OSAlarm* next;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (alarm->handler == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        AlarmQueue.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }
    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        AlarmQueue.head = next;
        if (next) {
            SetTimer(next);
        }
    }
    alarm->handler = 0;
    OSRestoreInterrupts(enabled);
}

static void DecrementerExceptionCallback(register __OSException exception, register OSContext* context) {
    OSAlarm* alarm;
    OSAlarm* next;
    OSContext context2;
    OSAlarmHandler handler;
    OSTime time;

    time = __OSGetSystemTime();
    alarm = AlarmQueue.head;
    if (alarm == 0) {
        OSLoadContext(context);
    }

    if (time < alarm->fire) {
        SetTimer(alarm);
        OSLoadContext(context);
    }

    next = alarm->next;
    AlarmQueue.head = next;
    if (next == 0) {
        AlarmQueue.tail = 0;
    } else {
        next->prev = 0;
    }
    handler = alarm->handler;
    alarm->handler = 0;
    if (0 < alarm->period) {
        InsertAlarm(alarm, 0, handler);
    }

    if (AlarmQueue.head) {
        SetTimer(AlarmQueue.head);
    }

    OSDisableScheduler();
    OSClearContext(&context2);
    OSSetCurrentContext(&context2);
    handler(alarm, context);
    OSClearContext(&context2);
    OSSetCurrentContext(context);
    OSEnableScheduler();
    __OSReschedule();
    OSLoadContext(context);
}

/* clang-format off */
static asm void DecrementerExceptionHandler(register u8 type, register OSContext* ctx){
	nofralloc
	stw r0, ctx->gpr[0]
	stw r1, ctx->gpr[1]
	stw r2, ctx->gpr[2]
	stmw r6, ctx->gpr[6]
	
	mfspr r0, 0x391
	stw r0, ctx->gqr[1]
	mfspr r0, 0x392
	stw r0, ctx->gqr[2]
	mfspr r0, 0x393
	stw r0, ctx->gqr[3]
	mfspr r0, 0x394
	stw r0, ctx->gqr[4]
	mfspr r0, 0x395
	stw r0, ctx->gqr[5]
	mfspr r0, 0x396
	stw r0, ctx->gqr[6]
	mfspr r0, 0x397
	stw r0, ctx->gqr[7]
	
	stwu r1, -8(r1)
	b DecrementerExceptionCallback
}
/* clang-format on */
