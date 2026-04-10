#ifndef _JAUDIO_CMDSTACK_H
#define _JAUDIO_CMDSTACK_H

#include "types.h"

typedef struct JPorthead_ {
	uintptr_t _00; // _00
	uintptr_t _04; // _04
} JPorthead_;

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

void Add_PortcmdOnce(uintptr_t*);
void Add_PortcmdStay(void); // UNUSED but we know it's extern "C"
int Set_Portcmd(int*, int, int);
BOOL Add_Portcmd(JPorthead_*, uintptr_t*);
void Cancel_Portcmd(void);     // UNUSED but we know it's extern "C"
void Cancel_PortcmdStay(void); // UNUSED but we know it's extern "C"
int Jac_Portcmd_Proc_Once(JPorthead_*);
int Jac_Portcmd_Proc_Stay(JPorthead_*);
void Jac_Porthead_Init(JPorthead_*);
void Jac_Portcmd_Init(void);
void JP_Pitch1Shot(void); // UNUSED but we know it's extern "C"
void JP_Start1Shot(void); // UNUSED but we know it's extern "C"
void JP_Stop1Shot(void);  // UNUSED but we know it's extern "C"

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

static uintptr_t Get_Portcmd(JPorthead_* port);
static s32 Portcmd_Main(void* a);

#endif
