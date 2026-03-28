#include "jaudio_NES/cmdstack.h"
#include "jaudio_NES/playercall.h"
#include "dolphin/os.h"

JPorthead_ cmd_once;
JPorthead_ cmd_stay;

/*
 * --INFO--
 * Address:	8000E300
 * Size:	000028
 */
void Add_PortcmdOnce(uintptr_t* a1)
{
	Add_Portcmd(&cmd_once, a1);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000028
 */
void Add_PortcmdStay(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000E340
 * Size:	000018
 */
int Set_Portcmd(int* a1, int a2, int a3)
{
	// Is this a struct? I have no idea
	a1[5] = a2;
	a1[6] = a3;
	a1[3] = 0;
	return 1;
}

/*
 * --INFO--
 * Address:	8000E360
 * Size:	000078
 */
BOOL Add_Portcmd(JPorthead_* port, uintptr_t* a2)
{
	BOOL interrupt = OSDisableInterrupts();

	if (a2[3]) {
		OSRestoreInterrupts(interrupt);
		return FALSE;
	}

	if (port->_04) {
		((uintptr_t*)port->_04)[4] = (uintptr_t)a2;
	} else {
		port->_00 = (uintptr_t)a2;
	}

	port->_04 = (uintptr_t)a2;
	a2[4]     = 0;
	a2[3]     = (uintptr_t)port;
	OSRestoreInterrupts(interrupt);
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000E3E0
 * Size:	000040
 */
static uintptr_t Get_Portcmd(JPorthead_* port)
{
	uintptr_t a = port->_00;
	if (a) {
		port->_00 = ((uintptr_t*)port->_00)[4];
		if (port->_00 == 0) {
			port->_04 = 0;
		}
		((uintptr_t*)a)[3] = 0;
	} else {
		a = 0;
	}

	return a;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
void Cancel_Portcmd(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000028
 */
void Cancel_PortcmdStay(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000E420
 * Size:	000050
 */
int Jac_Portcmd_Proc_Once(JPorthead_* port)
{
	uintptr_t p;
	while (1) {
		p = Get_Portcmd(port);
		if (!p) {
			break;
		}
		// Ckit ahh moment unless someone figures out what type Get_Portcmd actually returns
		((int (*)(uintptr_t)) * (uintptr_t*)(p + 5 * sizeof(uintptr_t)))(((uintptr_t*)p)[6]);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000E480
 * Size:	00004C
 */
int Jac_Portcmd_Proc_Stay(JPorthead_* port)
{
	uintptr_t p = port->_00;
	while (1) {
		if (!p) {
			break;
		}
		((int (*)(uintptr_t)) * (uintptr_t*)(p + 5 * sizeof(uintptr_t)))(((uintptr_t*)p)[6]);

		p = ((uintptr_t*)p)[4];
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000E4E0
 * Size:	000030
 */
static s32 Portcmd_Main(void* a)
{
	Jac_Portcmd_Proc_Once(&cmd_once);
	Jac_Portcmd_Proc_Stay(&cmd_stay);
	return 0;
}

/*
 * --INFO--
 * Address:	8000E520
 * Size:	000010
 */
void Jac_Porthead_Init(JPorthead_* port)
{
	port->_00 = 0;
	port->_04 = 0;
}

/*
 * --INFO--
 * Address:	8000E540
 * Size:	00003C
 */
void Jac_Portcmd_Init(void)
{
	Jac_Porthead_Init(&cmd_once);
	Jac_Porthead_Init(&cmd_stay);
	Jac_RegisterPlayerCallback(Portcmd_Main, 0);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void JP_Pitch1Shot(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void JP_Start1Shot(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void JP_Stop1Shot(void)
{
	// UNUSED FUNCTION
}
