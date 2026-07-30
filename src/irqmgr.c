#include "irqmgr.h"
#include "libultra/os_thread.h"
#include "libultra/libultra.h"
#include "libultra/os_timer.h"
#include "libultra/osMesg.h"
#include "dolphin/os.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSTime.h"

#define MSEC(x) OSMicrosecondsToTicks(((u64)(x)) * (u64)1000)

volatile int ResetStatus = 0;             // 0x00
volatile OSTime ResetTime = 0;    // 0x08
volatile OSTime RetraceTime = 0;  // 0x10
volatile int RetraceCount = 0;    // 0x18
static irqmgr_t* this;               // 0x1C
irqmgr_t irqmgr_class;

#define IRQ_RETRACE_MSG 666
#define IRQ_PRENMI_MSG 669
#define IRQ_PRENMI450_MSG 671
#define IRQ_PRENMI480_MSG 672
#define IRQ_PRENMI500_MSG 673

/**
 * @brief Adds anew client to the IRQ manager with a callback message queue.
 * 
 * @param client The new client to add
 * @param msgqueue The callback message queue
 **/
extern void irqmgr_AddClient(irqmgr_client_t* client, OSMessageQueue* msgqueue) {
  BOOL enable = OSDisableInterrupts();
  client->msgQueue = msgqueue;
  client->next = this->clients;
  this->clients = client;
  OSRestoreInterrupts(enable);

  if (this->prenmi >= 1) {
    osSendMesg(client->msgQueue, &this->msgPreNMI, 0);
  }
  if (this->prenmi >= 2) {
    osSendMesg(client->msgQueue, &this->msgDelayPreNMI, 0);
  }
}

/* @unused extern void irqmgr_RemoveClient(irqmgr_client_t* client) */

/**
 * @brief Sends a new message to all active IRQ clients.
 * 
 * @param msg The message which will be sent
 **/
static void irqmgr_SendMesgForClient(irqmgr_mesg_t* msg) {
  irqmgr_client_t* i;
  OSMessageQueue* mesgq;
  for (i = this->clients; i != NULL; i = i->next) {
    mesgq = i->msgQueue;
    if (mesgq->usedCount < mesgq->msgCount) {
      osSendMesg(mesgq, msg, 0);
    }
  }
}

/**
 * @brief Sends a new message to all active IRQ clients. Duplicate of above.
 * 
 * @param msg The message which will be sent
 **/
static void irqmgr_JamMesgForClient(irqmgr_mesg_t* msg) {
  irqmgr_client_t* i;
  OSMessageQueue* mesgq;
  for (i = this->clients; i != NULL; i = i->next) {
    mesgq = i->msgQueue;
    if (mesgq->usedCount < mesgq->msgCount) {
      osSendMesg(mesgq, msg, 0);
    }
  }
}


/**
 * @brief Handler function for pre-NMI message.
 **/
static void irqmgr_HandlePreNMI() {
  ResetStatus = 1;
  this->prenmi = 1;
  ResetTime = this->prenmi_time = osGetTime();

  osSetTimer(&this->timer, MSEC(400), 0, &this->_msgQueue, (OSMessage)IRQ_PRENMI450_MSG);
  irqmgr_JamMesgForClient(&this->msgPreNMI);
}

/**
 * @brief Handler for pre-NMI message (post 400ms).
 **/
static void irqmgr_HandlePreNMI450() {
  ResetStatus = 2;
  this->prenmi = 2;
  osSetTimer(&this->timer, MSEC(50), 0, &this->_msgQueue, (OSMessage)IRQ_PRENMI480_MSG);
  irqmgr_SendMesgForClient(&this->msgDelayPreNMI);
}

/**
 * @brief Handler for pre-NMI message (post 450ms).
 **/
static void irqmgr_HandlePreNMI480() {
  osSetTimer(&this->timer, MSEC(50), 0, &this->_msgQueue, (OSMessage)IRQ_PRENMI500_MSG);
}

/**
 * @brief Handler for pre-NMI message (post 500ms).
 **/
static void irqmgr_HandlePreNMI500() {}


/**
 * @brief Handler for retrace message.
 **/
static void irqmgr_HandleRetrace() {
  OSTime time;
  if (RetraceTime == 0) {
    if (this->retraceTime == 0) {
      time = osGetTime();
      this->retraceTime = time;
    }
    else {
      time = osGetTime();
      RetraceTime = time - this->retraceTime;
    }
  }
  RetraceCount++;
  irqmgr_SendMesgForClient(&this->msgRetrace);
}

/**
 * @brief Main IRQ manager handler.
 * 
 * @param arg unused OSThread func arg
 **/
static void irqmgr_Main(void* arg) {
  OSMessage msg = (OSMessage)0;

  while (TRUE) {
    osRecvMesg(&this->_msgQueue, &msg, 1);
    switch ((uintptr_t)msg) {
      case IRQ_RETRACE_MSG:
        irqmgr_HandleRetrace();
        break;
      case IRQ_PRENMI_MSG:
        irqmgr_HandlePreNMI();
        break;
      case IRQ_PRENMI450_MSG:
        irqmgr_HandlePreNMI450();
        break;
      case IRQ_PRENMI480_MSG:
        irqmgr_HandlePreNMI480();
        break;
      case IRQ_PRENMI500_MSG:
        irqmgr_HandlePreNMI500();
        break;
      default:
        break;
    }
  }
}

/**
 * @brief Creates a new IRQ manager.
 * 
 * @param stack The IRQ manager's stack
 * @param stack_size The IRQ manager's stack size
 * @param priority The thread's priority
 * @param retracecount Taken by osViSetEvent, unused
 **/
extern void CreateIRQManager(void* stack, size_t stack_size, int priority, u8 retracecount) {
  this = &irqmgr_class;
  this->clients = NULL;
  this->msgRetrace.type = 1;
  this->msgPreNMI.type = 4;
  this->msgDelayPreNMI.type = 3;
  this->prenmi = 0;
  this->prenmi_time = 0;

  osCreateMesgQueue(&this->_msgQueue, this->_msgBuf, 8);
  osViSetEvent(&this->_msgQueue, (OSMessage)IRQ_RETRACE_MSG, retracecount);
  osCreateThread2(&this->thread, 9, irqmgr_Main, NULL, stack, stack_size, priority);
  osStartThread(&this->thread);
}

/* these were probably written in a header directly and included here */

#define VI_STACK_SIZE 0x1000

static u16 vc_retraceCount;
static OSMessage vc_msg;
static OSMessageQueue* vc_msgq;
static u8 viThreadStack[VI_STACK_SIZE];
static OSThread viThread;

/* @fabricated @unused */

void viMgrMain(void){
  static u16 retrace;

  retrace = 0;
  vc_retraceCount = 0;
} 

/* @unused ? osCreateViManager(?) */


/**
 * @brief Sets the VI event info. Stubbed outside this functionality.
 * 
 * @param msgq The OSMessageQueue which would be notified upon event invocation
 * @param msg The OSMessage which would be sent upon event invocation
 * @param retcount The retrace count before invoking the event
 **/
extern void osViSetEvent(OSMessageQueue* mesgq, OSMessage msg, u32 retcount) {
  vc_msgq = mesgq;
  vc_msg = msg;
  vc_retraceCount = retcount;
}
