#include <dolphin/os.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/db.h>
#include <dolphin/exi.h>
#include <string.h>
#include <macros.h>
#include "../src/static/dolphin/os/__os.h"

void EnableMetroTRKInterrupts(void);

#define OS_CURRENTCONTEXT_PADDR 0x00C0

#define OS_EXCEPTIONTABLE_ADDR 0x3000
#define OS_DBJUMPPOINT_ADDR    0x60
// memory locations for important stuff
#define OS_BI2_DEBUG_ADDRESS    0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define PAD3_BUTTON_ADDR        0x800030E4
#define OS_DVD_DEVICECODE       0x800030E6
#define DEBUGFLAG_ADDR          0x800030E8
#define OS_DEBUG_ADDRESS_2      0x800030E9
#define DB_EXCEPTIONRET_OFFSET  0xC
#define DB_EXCEPTIONDEST_OFFSET 0x8

extern unsigned long __DVDLongFileNameFlag;
extern unsigned long __PADSpec;
extern unsigned char __ArenaLo[];
extern char _stack_addr[];
extern unsigned char __ArenaHi[];

// dummy entry points to the OS Exception vector
void __OSEVStart(void);
void __OSEVEnd(void);
void __OSEVSetNumber(void);
void __OSExceptionVector(void);

void __DBVECTOR(void);
void __OSDBINTSTART(void);
void __OSDBINTEND(void);
void __OSDBJUMPSTART(void);
void __OSDBJUMPEND(void);

#define NOP 0x60000000

static OSBootInfo* BootInfo;
static volatile u32* BI2DebugFlag;
static u32* BI2DebugFlagHolder;
static f64 ZeroPS;
static f64 ZeroF;
static BOOL __OSIsGcam;
static BOOL AreWeInitialized;

typedef void (*OSExceptionHandler)(u8, struct OSContext*);
static OSExceptionHandler* OSExceptionTable;

static void* __OSSavedRegionEnd;
static void* __OSSavedRegionStart;
static BOOL __OSInIPL;
OSTime __OSStartTime;

static DVDDriveInfo DriveInfo __attribute__((aligned(0x20)));
static DVDCommandBlock DriveBlock;

// functions
static asm void __OSInitFPRs(void);
static void OSExceptionInit(void);
static void OSDefaultExceptionHandler(u8 exception /* r3 */,
                                      OSContext* context /* r4 */);

// NOTE: this is unused, but stuff won't align properly without it
static asm void __OSInitFPRs(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	mfmsr r3
	ori r3, r3, 0x2000
	mtmsr r3

	mfspr r3, 0x398
	rlwinm. r3, r3, 3, 0x1f, 0x1f
	beq skip_ps_init

	lis r3, ZeroPS@ha
	addi r3, r3, ZeroPS@l
	psq_l f0, 0(r3), 0, 0
	ps_mr f1, f0
	ps_mr f2, f0
	ps_mr f3, f0
	ps_mr f4, f0
	ps_mr f5, f0
	ps_mr f6, f0
	ps_mr f7, f0
	ps_mr f8, f0
	ps_mr f9, f0
	ps_mr f10, f0
	ps_mr f11, f0
	ps_mr f12, f0
	ps_mr f13, f0
	ps_mr f14, f0
	ps_mr f15, f0
	ps_mr f16, f0
	ps_mr f17, f0
	ps_mr f18, f0
	ps_mr f19, f0
	ps_mr f20, f0
	ps_mr f21, f0
	ps_mr f22, f0
	ps_mr f23, f0
	ps_mr f24, f0
	ps_mr f25, f0
	ps_mr f26, f0
	ps_mr f27, f0
	ps_mr f28, f0
	ps_mr f29, f0
	ps_mr f30, f0
	ps_mr f31, f0

skip_ps_init:
	lfd f0, ZeroF(r13)
	fmr f1, f0
	fmr f2, f0
	fmr f3, f0
	fmr f4, f0
	fmr f5, f0
	fmr f6, f0
	fmr f7, f0
	fmr f8, f0
	fmr f9, f0
	fmr f10, f0
	fmr f11, f0
	fmr f12, f0
	fmr f13, f0
	fmr f14, f0
	fmr f15, f0
	fmr f16, f0
	fmr f17, f0
	fmr f18, f0
	fmr f19, f0
	fmr f20, f0
	fmr f21, f0
	fmr f22, f0
	fmr f23, f0
	fmr f24, f0
	fmr f25, f0
	fmr f26, f0
	fmr f27, f0
	fmr f28, f0
	fmr f29, f0
	fmr f30, f0
	fmr f31, f0

	mtfsf 0xff, f0
	blr
#endif // clang-format on
}

unsigned long OSGetConsoleType()
{
	if ((!BootInfo) || (BootInfo->consoleType == 0)) {
		return OS_CONSOLE_ARTHUR;
	}
	return BootInfo->consoleType;
}

volatile u16 __OSDeviceCode AT_ADDRESS(0x800030E6);

static void ClearArena()
{
	if (OSGetResetCode() != -0x80000000) {
		__OSSavedRegionStart = NULL;
		__OSSavedRegionEnd   = NULL;
		memset(OSGetArenaLo(), 0, (u8*)OSGetArenaHi() - (u8*)OSGetArenaLo());
		return;
	}

	__OSSavedRegionStart = BOOT_REGION_START;
	__OSSavedRegionEnd   = BOOT_REGION_END;

	if (BOOT_REGION_START == NULL) {
		memset(OSGetArenaLo(), 0, (u8*)OSGetArenaHi() - (u8*)OSGetArenaLo());
		return;
	}

	if ((u8*)OSGetArenaLo() < (u8*)__OSSavedRegionStart) {
		if ((u8*)OSGetArenaHi() <= (u8*)__OSSavedRegionStart) {
			memset(OSGetArenaLo(), 0,
			       (u8*)OSGetArenaHi() - (u8*)OSGetArenaLo());
			return;
		}

		memset(OSGetArenaLo(), 0,
		       (u8*)__OSSavedRegionStart - (u8*)OSGetArenaLo());

		if ((u8*)OSGetArenaHi() > (u8*)__OSSavedRegionEnd) {
			memset(__OSSavedRegionEnd, 0,
			       (u8*)OSGetArenaHi() - (u8*)__OSSavedRegionEnd);
		}
	}
}

static void InquiryCallback(s32 result, struct DVDCommandBlock* block)
{
	switch (block->state) {
	case 0:
		__OSDeviceCode = DriveInfo.deviceCode | 0x8000;
		break;
	default:
		__OSDeviceCode = 1;
		break;
	}
}

void OSInit()
{
	u32 consoleType;
	BI2Debug* bi2DebugInfo;

	if (AreWeInitialized != 0)
		return;

	AreWeInitialized = 1;
	__OSStartTime    = __OSGetSystemTime();
	OSDisableInterrupts();
	PPCDisableSpeculation();
	PPCSetFpNonIEEEMode();
	BootInfo              = (struct OSBootInfo_s*)OSPhysicalToCached(0);
	BI2DebugFlag          = NULL;
	__DVDLongFileNameFlag = 0;
	bi2DebugInfo          = (BI2Debug*)*(BI2Debug**)OS_BI2_DEBUG_ADDRESS;
	if (bi2DebugInfo != NULL) {
		BI2DebugFlag               = &bi2DebugInfo->debugFlag;
		__PADSpec                  = bi2DebugInfo->padSpec;
		*((u8*)DEBUGFLAG_ADDR)     = (u8)*BI2DebugFlag;
		*((u8*)OS_DEBUG_ADDRESS_2) = (u8)__PADSpec;
	} else if (BootInfo->arenaHi) {
		BI2DebugFlagHolder = (u32*)*((u8*)DEBUGFLAG_ADDR);
		BI2DebugFlag       = (u32*)&BI2DebugFlagHolder;
		__PADSpec          = (u32) * ((u8*)OS_DEBUG_ADDRESS_2);
	}

	__DVDLongFileNameFlag = 1;

	OSSetArenaLo((!BootInfo->arenaLo) ? &__ArenaLo : BootInfo->arenaLo);
	if ((!BootInfo->arenaLo) && (BI2DebugFlag) && (*(u32*)BI2DebugFlag < 2)) {
		OSSetArenaLo((void*)(((u32)(char*)&_stack_addr + 0x1F) & 0xFFFFFFE0));
	}
	OSSetArenaHi((!BootInfo->arenaHi) ? &__ArenaHi : BootInfo->arenaHi);
	OSExceptionInit();
	__OSInitSystemCall();
	OSInitAlarm();
	__OSModuleInit();
	__OSInterruptInit();
	__OSSetInterruptHandler(0x16, &__OSResetSWInterruptHandler);
	__OSContextInit();
	__OSCacheInit();
	EXIInit();
	SIInit();
	__OSInitSram();
	__OSThreadInit();
	__OSInitAudioSystem();
	PPCMthid2(PPCMfhid2() & 0xbfffffff);
	if ((BootInfo->consoleType & OS_CONSOLE_DEVELOPMENT) != 0) {
		BootInfo->consoleType = OS_CONSOLE_DEVHW1;
	} else {
		BootInfo->consoleType = OS_CONSOLE_RETAIL1;
	}
	BootInfo->consoleType += (__PIRegs[11] & 0xF0000000) >> 28;
	if (__OSInIPL == 0) {
		__OSInitMemoryProtection();
	}

	OSReport("\nDolphin OS $Revision: 54 $.\n");
	OSReport("Kernel built : %s %s\n", "Jun  5 2002", "02:09:12");

	OSReport("Console Type : ");

	consoleType = OSGetConsoleType();
	// work out what console type this corresponds to and report it
	// consoleTypeSwitchHi = inputConsoleType & 0xF0000000;
	if ((consoleType & 0x10000000) == OS_CONSOLE_RETAIL) { // check "first" byte
		OSReport("Retail %d\n", consoleType);
	} else {
		switch (consoleType) { // if "first" byte is 2, check "the rest"
		case OS_CONSOLE_EMULATOR:
			OSReport("Mac Emulator\n");
			break;
		case OS_CONSOLE_PC_EMULATOR:
			OSReport("PC Emulator\n");
			break;
		case OS_CONSOLE_ARTHUR:
			OSReport("EPPC Arthur\n");
			break;
		case OS_CONSOLE_MINNOW:
			OSReport("EPPC Minnow\n");
			break;
		default:
			OSReport("Development HW%d\n", ((u32)consoleType - 0x10000000) - 3);
			break;
		}
	}

	// report memory size
	OSReport("Memory %d MB\n", (u32)BootInfo->memorySize >> 0x14U);
	// report heap bounds
	OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());

	// if location of debug flag exists, and flag is >= 2, enable
	// MetroTRKInterrupts
	if (BI2DebugFlag && ((*BI2DebugFlag) >= 2)) {
		EnableMetroTRKInterrupts();
	}
	ClearArena();
	OSEnableInterrupts();
	if (__OSInIPL == 0) {
		DVDInit();

		if (__OSIsGcam) {
			__OSDeviceCode = 0x9000;
			return;
		}

		DCInvalidateRange(&DriveInfo, 0x20);
		DVDInquiryAsync(&DriveBlock, &DriveInfo, InquiryCallback);
	}
}

static u32 __OSExceptionLocations[] = {
	0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500,
	0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000C00,
	0x00000D00, 0x00000F00, 0x00001300, 0x00001400, 0x00001700,
};

static void OSExceptionInit(void)
{
	__OSException exception;
	void* destAddr;

	// These two vars help us change the exception number embedded
	// in the exception handler code.
	u32* opCodeAddr;
	u32 oldOpCode;

	// Address range of the actual code to be copied.
	u8* handlerStart;
	u32 handlerSize;

	// Install the first level exception vector.
	opCodeAddr   = (u32*)__OSEVSetNumber;
	oldOpCode    = *opCodeAddr;
	handlerStart = (u8*)__OSEVStart;
	handlerSize  = (u32)((u8*)__OSEVEnd - (u8*)__OSEVStart);

	// Install the DB integrator, only if we are the first OSInit to be run
	destAddr = (void*)OSPhysicalToCached(OS_DBJUMPPOINT_ADDR);
	if (*(u32*)destAddr == 0) // Lomem should be zero cleared only once by BS2
	{
		DBPrintf("Installing OSDBIntegrator\n");
		memcpy(destAddr, (void*)__OSDBINTSTART,
		       (u32)__OSDBJUMPSTART - (u32)__OSDBINTSTART);
		DCFlushRangeNoSync(destAddr,
		                   (u32)__OSDBJUMPSTART - (u32)__OSDBINTSTART);
		__sync();
		ICInvalidateRange(destAddr, (u32)__OSDBJUMPSTART - (u32)__OSDBINTSTART);
	}

	// Copy the right vector into the table
	for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
		if (BI2DebugFlag && (*BI2DebugFlag >= 2)
		    && __DBIsExceptionMarked(exception)) {
			// this DBPrintf is suspicious.
			DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n",
			         exception);
			continue;
		}

		// Modify the copy of code in text before transferring
		// to the exception table.
		*opCodeAddr = oldOpCode | exception;

		// Modify opcodes at __DBVECTOR if necessary
		if (__DBIsExceptionMarked(exception)) {
			DBPrintf(">>> OSINIT: exception %d vectored to debugger\n",
			         exception);
			memcpy((void*)__DBVECTOR, (void*)__OSDBJUMPSTART,
			       (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART);
		} else {
			// make sure the opcodes are still nop
			u32* ops = (u32*)__DBVECTOR;
			int cb;

			for (cb = 0; cb < (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART;
			     cb += sizeof(u32)) {
				*ops++ = NOP;
			}
		}

		// Install the modified handler.
		destAddr
		    = (void*)OSPhysicalToCached(__OSExceptionLocations[(u32)exception]);
		memcpy(destAddr, handlerStart, handlerSize);
		DCFlushRangeNoSync(destAddr, handlerSize);
		__sync();
		ICInvalidateRange(destAddr, handlerSize);
	}
	// initialize pointer to exception table
	OSExceptionTable = (void*)OSPhysicalToCached(OS_EXCEPTIONTABLE_ADDR);

	// install default exception handlers
	for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
		__OSSetExceptionHandler(exception, OSDefaultExceptionHandler);
	}

	// restore the old opcode, so that we can re-start an application without
	// downloading the text segments
	*opCodeAddr = oldOpCode;

	DBPrintf("Exceptions initialized...\n");
}

static asm void __OSDBIntegrator(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
entry __OSDBINTSTART
	li	  r5, OS_DBINTERFACE_ADDR
	mflr	r3
	stw	 r3, DB_EXCEPTIONRET_OFFSET(r5)
	lwz	 r3, DB_EXCEPTIONDEST_OFFSET(r5)
	oris	r3, r3, OS_CACHED_REGION_PREFIX
	mtlr	r3
	li	  r3, 0x30 // MSR_IR | MSR_DR	 // turn on memory addressing
	mtmsr   r3
	blr
entry __OSDBINTEND
#endif // clang-format on
}

static asm void __OSDBJump(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
entry __OSDBJUMPSTART
	bla	 OS_DBJUMPPOINT_ADDR
entry __OSDBJUMPEND
#endif // clang-format on
}

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception,
                                             __OSExceptionHandler handler)
{
	__OSExceptionHandler oldHandler;

	oldHandler                  = OSExceptionTable[exception];
	OSExceptionTable[exception] = handler;
	return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(__OSException exception)
{
	return OSExceptionTable[exception];
}

static asm void OSExceptionVector(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

entry __OSEVStart
	// Save r4 into SPRG0
	mtsprg  0, r4

	// Load current context physical address into r4
	lwz	 r4, OS_CURRENTCONTEXT_PADDR

	// Save r3 - r5 into the current context
	stw	 r3, OS_CONTEXT_R3(r4)
	mfsprg  r3, 0
	stw	 r3, OS_CONTEXT_R4(r4)
	stw	 r5, OS_CONTEXT_R5(r4)

	lhz	 r3, OS_CONTEXT_STATE(r4)
	ori	 r3, r3, OS_CONTEXT_STATE_EXC
	sth	 r3, OS_CONTEXT_STATE(r4)

	// Save misc registers
	mfcr	r3
	stw	 r3, OS_CONTEXT_CR(r4)
	mflr	r3
	stw	 r3, OS_CONTEXT_LR(r4)
	mfctr   r3
	stw	 r3, OS_CONTEXT_CTR(r4)
	mfxer   r3
	stw	 r3, OS_CONTEXT_XER(r4)
	mfsrr0  r3
	stw	 r3, OS_CONTEXT_SRR0(r4)
	mfsrr1  r3
	stw	 r3, OS_CONTEXT_SRR1(r4)
	mr	  r5, r3

entry __DBVECTOR
	nop

	// Set SRR1[IR|DR] to turn on address
	// translation at the next RFI
	mfmsr   r3
	ori	 r3, r3, 0x30
	mtsrr1  r3

	// This lets us change the exception number based on the
	// exception we're installing.
entry __OSEVSetNumber
	addi	r3, 0, 0x0000

	// Load current context virtual address into r4
	lwz	 r4, 0xD4

	// Check non-recoverable interrupt
	rlwinm. r5, r5, 0, MSR_RI_BIT, MSR_RI_BIT
	bne	 recoverable
	addis   r5, 0,  OSDefaultExceptionHandler@ha
	addi	r5, r5, OSDefaultExceptionHandler@l
	mtsrr0  r5
	rfi
	// NOT REACHED HERE

recoverable:
	// Locate exception handler.
	rlwinm  r5, r3, 2, 22, 29			   // r5 contains exception*4
	lwz	 r5, OS_EXCEPTIONTABLE_ADDR(r5)
	mtsrr0  r5

	// Final state
	// r3 - exception number
	// r4 - pointer to context
	// r5 - garbage
	// srr0 - exception handler
	// srr1 - address translation enalbed, not yet recoverable

	rfi
	// NOT REACHED HERE
	// The handler will restore state

entry __OSEVEnd
	nop
#endif // clang-format on
}

void __OSUnhandledException(__OSException exception, OSContext* context,
                            u32 dsisr, u32 dar);
asm void OSDefaultExceptionHandler(register __OSException exception,
                                   register OSContext* context)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	OS_EXCEPTION_SAVE_GPRS(context)
	mfdsisr r5
	mfdar   r6
	stwu r1, -0x8(r1)
	b	   __OSUnhandledException
#endif // clang-format on
}

void __OSPSInit(void)
{
	PPCMthid2(PPCMfhid2() | 0x80000000 | 0x20000000);
	ICFlashInvalidate();
	__sync();
#ifdef __MWERKS__ // clang-format off
	asm
	{
		li	  r3, 0
		mtspr   GQR0, r3
	}
#endif // clang-format on
}

#define DI_CONFIG_IDX         0x9
#define DI_CONFIG_CONFIG_MASK 0xFF

u32 __OSGetDIConfig(void)
{
	return (__DIRegs[DI_CONFIG_IDX] & DI_CONFIG_CONFIG_MASK);
}
