#include <dolphin/os.h>
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os/OSReset.h"

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))
#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))

u32 OSGetConsoleSimulatedMemSize(void){
	return(SIM_MEM);
}

static BOOL OnReset(BOOL final){
	if (final) {
		__MEMRegs[8] = 0xff;
		__OSMaskInterrupts(0xF0000000);
	}
	return TRUE;
}

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext* ctx){
	u32 cause = __MEMRegs[0xf];
	u32 addr  =  (((u32) __MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
	__MEMRegs[0x10] = 0;
	
	if(__OSErrorTable[OS_ERROR_PROTECTION]) {
		__OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, ctx, cause, addr);
		return;
	}

    __OSUnhandledException(OS_ERROR_PROTECTION, ctx, cause, addr);
}

#define OS_PROTECT_CONTROL_NONE  0x00
#define OS_PROTECT_CONTROL_READ  0x01
#define OS_PROTECT_CONTROL_WRITE 0x02
#define OS_PROTECT_CONTROL_RDWR                                                \
	(OS_PROTECT_CONTROL_READ | OS_PROTECT_CONTROL_WRITE)

void OSProtectRange(u32 chan, void* addr, u32 nBytes, u32 control)
{
	BOOL enabled;
	u32 start;
	u32 end;
	u16 reg;
	if (4 <= chan) {
		return;
	}

	control &= OS_PROTECT_CONTROL_RDWR;

	end   = (u32)addr + nBytes;
	start = TRUNC(addr, 1u << 10);
	end   = ROUND(end, 1u << 10);

	DCFlushRange((void*)start, end - start);

	enabled = OSDisableInterrupts();

	__OSMaskInterrupts(OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0 + chan));

	__MEMRegs[0 + 2 * chan] = (u16)(start >> 10);
	__MEMRegs[1 + 2 * chan] = (u16)(end >> 10);

	reg = __MEMRegs[8];
	reg &= ~(OS_PROTECT_CONTROL_RDWR << 2 * chan);
	reg |= control << 2 * chan;
	__MEMRegs[8] = reg;

	if (control != OS_PROTECT_CONTROL_RDWR) {
		__OSUnmaskInterrupts(OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0 + chan));
	}

	OSRestoreInterrupts(enabled);
}

static asm void Config24MB(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	li r7, 0
	lis r4, 0x0000
	addi r4, r4, 0x0002
	lis r3, 0x8000
	addi r3, r3, 0x01FF
	lis r6, 0x0100
	addi r6, r6, 0x0002
	lis r5, 0x8100
	addi r5, r5, 0x00FF
	isync
	mtdbatu 0, r7
	mtdbatl 0, r4
	mtdbatu 0, r3
	isync
	mtibatu 0, r7
	mtibatl 0, r4
	mtibatu 0, r3
	isync
	mtdbatu 2, r7
	mtdbatl 2, r6
	mtdbatu 2, r5
	isync
	mtibatu 2, r7
	mtibatl 2, r6
	mtibatu 2, r5
	isync
	mfmsr r3
	ori r3, r3, 0x30
	mtspr 0x1b, r3
	mflr r3
	mtspr 0x1a, r3
	rfi
#endif // clang-format on
}

static asm void Config48MB(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	li r7, 0
	lis r4, 0x0000
	addi r4, r4, 0x0002
	lis r3, 0x8000
	addi r3, r3, 0x03FF
	lis r6, 0x0200
	addi r6, r6, 0x0002
	lis r5, 0x8200
	addi r5, r5, 0x01FF
	isync
	mtdbatu 0, r7
	mtdbatl 0, r4
	mtdbatu 0, r3
	isync
	mtibatu 0, r7
	mtibatl 0, r4
	mtibatu 0, r3
	isync
	mtdbatu 2, r7
	mtdbatl 2, r6
	mtdbatu 2, r5
	isync
	mtibatu 2, r7
	mtibatl 2, r6
	mtibatu 2, r5
	isync
	mfmsr r3
	ori r3, r3, 0x30
	mtspr 0x1b, r3
	mflr r3
	mtspr 0x1a, r3
	rfi
#endif // clang-format on
}

static asm void RealMode(register u32 config)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	clrlwi config, config, 2
	mtspr 0x1a, config
	mfmsr config
	rlwinm config, config, 0, 0x1c, 0x19
	mtspr 0x1b, config
	rfi
#endif // clang-format on
}

static OSResetFunctionInfo ResetFunctionInfo = {
	OnReset,
	0x7F,
};

u32 OSGetPhysicalMemSize() { return __OSPhysicalMemSize; }

void __OSInitMemoryProtection()
{
	char padding[0x28]; // TODO: wtf is this?
	u32 simulatedSize;
	BOOL enabled;
	simulatedSize = OSGetConsoleSimulatedMemSize();
	enabled       = OSDisableInterrupts();

	if (simulatedSize <= 0x1800000) {
		RealMode((u32)&Config24MB);
	} else if (simulatedSize <= 0x3000000) {
		RealMode((u32)&Config48MB);
	}

	__MEMRegs[16] = 0;
	__MEMRegs[8]  = 0xFF;

	__OSMaskInterrupts(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1
	                   | OS_INTERRUPTMASK_MEM_2 | OS_INTERRUPTMASK_MEM_3);
	__OSSetInterruptHandler(__OS_INTERRUPT_MEM_0, MEMIntrruptHandler);
	__OSSetInterruptHandler(__OS_INTERRUPT_MEM_1, MEMIntrruptHandler);
	__OSSetInterruptHandler(__OS_INTERRUPT_MEM_2, MEMIntrruptHandler);
	__OSSetInterruptHandler(__OS_INTERRUPT_MEM_3, MEMIntrruptHandler);
	__OSSetInterruptHandler(__OS_INTERRUPT_MEM_ADDRESS, MEMIntrruptHandler);
	OSRegisterResetFunction(&ResetFunctionInfo);

	simulatedSize = OSGetConsoleSimulatedMemSize();
	if (simulatedSize < OSGetPhysicalMemSize() && simulatedSize == 0x1800000) {
		__MEMRegs[20] = 2;
	}

	__OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
	OSRestoreInterrupts(enabled);
}
