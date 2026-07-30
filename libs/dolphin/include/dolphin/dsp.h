#ifndef DSP_H
#define DSP_H

#include "types.h"
#include "dolphin/os/OSTime.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DSP_TASK_FLAG_CLEARALL 0x00000000
#define DSP_TASK_FLAG_ATTACHED 0x00000001
#define DSP_TASK_FLAG_CANCEL 0x00000002

#define DSP_TASK_STATE_INIT 0
#define DSP_TASK_STATE_RUN 1
#define DSP_TASK_STATE_YIELD 2
#define DSP_TASK_STATE_DONE 3

typedef void (*DSPCallback)(void* task);

typedef struct STRUCT_DSP_TASK {
  vu32 state;
  vu32 priority;
  vu32 flags;
  u16* iram_mmem_addr;
  u32 iram_length;
  u32 iram_addr;

  u16* dram_mmem_addr;
  u32 dram_length;
  u32 dram_addr;

  u16 dsp_init_vector;
  u16 dsp_resume_vector;

  DSPCallback init_cb;
  DSPCallback res_cb;
  DSPCallback done_cb;
  DSPCallback req_cb;

  struct STRUCT_DSP_TASK* next;
  struct STRUCT_DSP_TASK* prev;

  OSTime t_context;
  OSTime t_task;

} DSPTaskInfo;

void DSPInit();
void DSPReset();
void DSPHalt();
void DSPSendMailToDSP(u32 mail);
u32 DSPCheckMailToDSP();
u32 DSPCheckMailFromDSP();
u32 DSPReadMailFromDSP();
u32 DSPGetDMAStatus();

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
void __DSP_boot_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
