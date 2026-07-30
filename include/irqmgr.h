#ifndef IRQMGR_H
#define IRQMGR_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "libultra/os_timer.h"
#include "dolphin/os/OSMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IRQ_RESET_NORMAL 0
#define IRQ_RESET_PRENMI 1
#define IRQ_RESET_DELAY 2

#define IRQMGR_MESSAGES_MAX 8

typedef struct {
    s16 type;
    s8 data[30];
} irqmgr_mesg_t;

typedef struct irqmgr_client_s {
    struct irqmgr_client_s* next;
    OSMessageQueue* msgQueue;
} irqmgr_client_t;

typedef struct {
    irqmgr_mesg_t msgRetrace;
    irqmgr_mesg_t msgPreNMI;
    irqmgr_mesg_t msgDelayPreNMI;
    OSMessageQueue _msgQueue;
    OSMessage _msgBuf[IRQMGR_MESSAGES_MAX];
    OSThread thread;
    irqmgr_client_t* clients;
    u8 prenmi;
    OSTime prenmi_time;
    OSTimer timer;
    OSTime retraceTime;
} irqmgr_t;

extern void irqmgr_AddClient(irqmgr_client_t* client, OSMessageQueue* msgqueue);
/* @unused extern void irqmgr_RemoveClient(irqmgr_client_t* client) */
extern void CreateIRQManager(void* stack, size_t stack_size, int priority, u8 retracecount);

/* probably declared in os_vi.h */
extern void osViSetEvent(OSMessageQueue* mesgq, OSMessage msg, u32 retcount);

extern volatile int ResetStatus;
extern volatile OSTime ResetTime;
extern volatile OSTime RetraceTime;
extern volatile int RetraceCount;
extern irqmgr_t irqmgr_class;

#ifdef __cplusplus
};
#endif

#endif
