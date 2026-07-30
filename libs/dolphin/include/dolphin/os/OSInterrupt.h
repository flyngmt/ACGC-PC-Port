#ifndef DOLPHIN_OSINTERRUPT_H
#define DOLPHIN_OSINTERRUPT_H

#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSException.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

typedef enum OSInterruptType {
    OS_INTR_MEM_0,
    OS_INTR_MEM_1,
    OS_INTR_MEM_2,
    OS_INTR_MEM_3,
    OS_INTR_MEM_ADDRESS,
    OS_INTR_DSP_AI,
    OS_INTR_DSP_ARAM,
    OS_INTR_DSP_DSP,
    OS_INTR_AI_AI,
    OS_INTR_EXI_0_EXI,
    OS_INTR_EXI_0_TC,
    OS_INTR_EXI_0_EXT,
    OS_INTR_EXI_1_EXI,
    OS_INTR_EXI_1_TC,
    OS_INTR_EXI_1_EXT,
    OS_INTR_EXI_2_EXI,
    OS_INTR_EXI_2_TC,
    OS_INTR_PI_CP,
    OS_INTR_PI_PE_TOKEN,
    OS_INTR_PI_PE_FINISH,
    OS_INTR_PI_SI,
    OS_INTR_PI_DI,
    OS_INTR_PI_RSW,
    OS_INTR_PI_ERROR,
    OS_INTR_PI_VI,
    OS_INTR_PI_DEBUG,
    OS_INTR_PI_HSP,
    OS_INTR_PI_ACR,
    OS_INTR_28,
    OS_INTR_29,
    OS_INTR_30,
    OS_INTR_31,

    OS_INTR_MAX
} OSInterruptType;

#define __OS_INTERRUPT_MEM_0        0
#define __OS_INTERRUPT_MEM_1        1
#define __OS_INTERRUPT_MEM_2        2
#define __OS_INTERRUPT_MEM_3        3
#define __OS_INTERRUPT_MEM_ADDRESS  4
#define __OS_INTERRUPT_DSP_AI       5
#define __OS_INTERRUPT_DSP_ARAM     6
#define __OS_INTERRUPT_DSP_DSP      7
#define __OS_INTERRUPT_AI_AI        8
#define __OS_INTERRUPT_EXI_0_EXI    9
#define __OS_INTERRUPT_EXI_0_TC     10
#define __OS_INTERRUPT_EXI_0_EXT    11
#define __OS_INTERRUPT_EXI_1_EXI    12
#define __OS_INTERRUPT_EXI_1_TC     13
#define __OS_INTERRUPT_EXI_1_EXT    14
#define __OS_INTERRUPT_EXI_2_EXI    15
#define __OS_INTERRUPT_EXI_2_TC     16
#define __OS_INTERRUPT_PI_CP        17
#define __OS_INTERRUPT_PI_PE_TOKEN  18
#define __OS_INTERRUPT_PI_PE_FINISH 19
#define __OS_INTERRUPT_PI_SI        20
#define __OS_INTERRUPT_PI_DI        21
#define __OS_INTERRUPT_PI_RSW       22
#define __OS_INTERRUPT_PI_ERROR     23
#define __OS_INTERRUPT_PI_VI        24
#define __OS_INTERRUPT_PI_DEBUG     25
#define __OS_INTERRUPT_PI_HSP       26
#define __OS_INTERRUPT_MAX          32

#define OS_INTERRUPTMASK(interrupt) (0x80000000u >> (interrupt))

#define OS_INTERRUPTMASK_MEM_0 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0)
#define OS_INTERRUPTMASK_MEM_1 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_1)
#define OS_INTERRUPTMASK_MEM_2 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_2)
#define OS_INTERRUPTMASK_MEM_3 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_3)
#define OS_INTERRUPTMASK_MEM_ADDRESS                                           \
	OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_ADDRESS)
#define OS_INTERRUPTMASK_MEM_RESET                                             \
	(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2  \
	 | OS_INTERRUPTMASK_MEM_3)
#define OS_INTERRUPTMASK_MEM                                                   \
	(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2  \
	 | OS_INTERRUPTMASK_MEM_3 | OS_INTERRUPTMASK_MEM_ADDRESS)
#define OS_INTERRUPTMASK_DSP_AI   OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_AI)
#define OS_INTERRUPTMASK_DSP_ARAM OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_ARAM)
#define OS_INTERRUPTMASK_DSP_DSP  OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_DSP)
#define OS_INTERRUPTMASK_DSP                                                   \
	(OS_INTERRUPTMASK_DSP_AI | OS_INTERRUPTMASK_DSP_ARAM                       \
	 | OS_INTERRUPTMASK_DSP_DSP)
#define OS_INTERRUPTMASK_AI_AI     OS_INTERRUPTMASK(__OS_INTERRUPT_AI_AI)
#define OS_INTERRUPTMASK_AI        (OS_INTERRUPTMASK_AI_AI)
#define OS_INTERRUPTMASK_EXI_0_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_EXI)
#define OS_INTERRUPTMASK_EXI_0_TC  OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_TC)
#define OS_INTERRUPTMASK_EXI_0_EXT OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_EXT)
#define OS_INTERRUPTMASK_EXI_0                                                 \
	(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC                    \
	 | OS_INTERRUPTMASK_EXI_0_EXT)
#define OS_INTERRUPTMASK_EXI_1_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_EXI)
#define OS_INTERRUPTMASK_EXI_1_TC  OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_TC)
#define OS_INTERRUPTMASK_EXI_1_EXT OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_EXT)
#define OS_INTERRUPTMASK_EXI_1                                                 \
	(OS_INTERRUPTMASK_EXI_1_EXI | OS_INTERRUPTMASK_EXI_1_TC                    \
	 | OS_INTERRUPTMASK_EXI_1_EXT)
#define OS_INTERRUPTMASK_EXI_2_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_2_EXI)
#define OS_INTERRUPTMASK_EXI_2_TC  OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_2_TC)
#define OS_INTERRUPTMASK_EXI_2                                                 \
	(OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC)
#define OS_INTERRUPTMASK_EXI                                                   \
	(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC                    \
	 | OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_1_EXI                 \
	 | OS_INTERRUPTMASK_EXI_1_TC | OS_INTERRUPTMASK_EXI_1_EXT                  \
	 | OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC)
#define OS_INTERRUPTMASK_PI_PE_TOKEN                                           \
	OS_INTERRUPTMASK(__OS_INTERRUPT_PI_PE_TOKEN)
#define OS_INTERRUPTMASK_PI_PE_FINISH                                          \
	OS_INTERRUPTMASK(__OS_INTERRUPT_PI_PE_FINISH)
#define OS_INTERRUPTMASK_PI_PE                                                 \
	(OS_INTERRUPTMASK_PI_PE_TOKEN | OS_INTERRUPTMASK_PI_PE_FINISH)
#define OS_INTERRUPTMASK_PI_CP    OS_INTERRUPTMASK(__OS_INTERRUPT_PI_CP)
#define OS_INTERRUPTMASK_PI_SI    OS_INTERRUPTMASK(__OS_INTERRUPT_PI_SI)
#define OS_INTERRUPTMASK_PI_DI    OS_INTERRUPTMASK(__OS_INTERRUPT_PI_DI)
#define OS_INTERRUPTMASK_PI_RSW   OS_INTERRUPTMASK(__OS_INTERRUPT_PI_RSW)
#define OS_INTERRUPTMASK_PI_ERROR OS_INTERRUPTMASK(__OS_INTERRUPT_PI_ERROR)
#define OS_INTERRUPTMASK_PI_VI    OS_INTERRUPTMASK(__OS_INTERRUPT_PI_VI)
#define OS_INTERRUPTMASK_PI_DEBUG OS_INTERRUPTMASK(__OS_INTERRUPT_PI_DEBUG)
#define OS_INTERRUPTMASK_PI_HSP   OS_INTERRUPTMASK(__OS_INTERRUPT_PI_HSP)
#define OS_INTERRUPTMASK_PI                                                    \
	(OS_INTERRUPTMASK_PI_CP | OS_INTERRUPTMASK_PI_SI | OS_INTERRUPTMASK_PI_DI  \
	 | OS_INTERRUPTMASK_PI_RSW | OS_INTERRUPTMASK_PI_ERROR                     \
	 | OS_INTERRUPTMASK_PI_VI | OS_INTERRUPTMASK_PI_PE_TOKEN                   \
	 | OS_INTERRUPTMASK_PI_PE_FINISH | OS_INTERRUPTMASK_PI_DEBUG               \
	 | OS_INTERRUPTMASK_PI_HSP)

typedef void (*__OSInterruptHandler)(__OSInterrupt, OSContext*);

extern volatile u32 __OSLastInterruptSrr0;
extern volatile s16 __OSLastInterrupt;
extern volatile s64 __OSLastInterruptTime;

void __RAS_OSDisableInterrupts_begin(void);
void __RAS_OSDisableInterrupts_end(void);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL);

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt, __OSInterruptHandler);
__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt);

void __OSInterruptInit(void);

u32 __OSMaskInterrupts(u32);
u32 __OSUnmaskInterrupts(u32);

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current);
void __OSDispatchInterrupt(__OSException exception, OSContext* context);


#ifdef __cplusplus
}
#endif

#endif
