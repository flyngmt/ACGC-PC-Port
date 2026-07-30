#ifndef DB_H
#define DB_H

#include "types.h"
#include <dolphin/db/DBInterface.h>

#ifdef __cplusplus
extern "C"{
#endif

#define OS_DBINTERFACE_ADDR 0x00000040

BOOL DBIsDebuggerPresent(void);
void DBPrintf(char* str, ...);

#ifdef __cplusplus
}
#endif
#endif
