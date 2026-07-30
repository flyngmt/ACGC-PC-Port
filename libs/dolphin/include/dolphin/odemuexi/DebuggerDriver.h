#ifndef ODEMUEXI_DEBUGGER_DRIVER_H
#define ODEMUEXI_DEBUGGER_DRIVER_H

#include <dolphin/os.h>

#ifdef __cplusplus
extern "C" {
#endif

int Hu_IsStub();

void DBInitComm(volatile u8** param_1, __OSInterruptHandler param_2);
void DBInitInterrupts(void);
u32 DBQueryData(void);
int DBRead(void* data, u32 size);
int DBWrite(const void* data, u32 size);
void DBOpen(void);
void DBClose(void);

#ifdef __cplusplus
}
#endif

#endif
