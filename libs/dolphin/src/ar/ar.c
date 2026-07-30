#include <dolphin/ar.h>
// #include "fake_tgmath.h"
#include <dolphin.h>
#include <dolphin/base/PPCArch.h>
#include <string.h>
#include <macros.h>

#include "ar/__ar.h"

static void (*__AR_Callback)();
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;
static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32* __AR_BlockLength;
static int __AR_init_flag;

// functions
static void __ARHandler(__OSInterrupt exception, struct OSContext* context);
static void __ARWaitForDMA(void);
static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length);
static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length);
static void __ARChecksize(void);

ARQCallback ARRegisterDMACallback(ARQCallback callback)
{
	ARQCallback old_callback;
	int old;

	old_callback  = __AR_Callback;
	old           = OSDisableInterrupts();
	__AR_Callback = callback;
	OSRestoreInterrupts(old);
	return old_callback;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
	int old;

	old = OSDisableInterrupts();

	__DSPRegs[DSP_ARAM_DMA_MM_HI]
	    = (__DSPRegs[DSP_ARAM_DMA_MM_HI] & 0xFFFFFC00 | (mainmem_addr >> 0x10));
	__DSPRegs[DSP_ARAM_DMA_MM_LO]
	    = (__DSPRegs[DSP_ARAM_DMA_MM_LO] & 0xFFFF001F | ((u16)mainmem_addr));
	__DSPRegs[DSP_ARAM_DMA_ARAM_HI]
	    = (__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & 0xFFFFFC00 | (aram_addr >> 0x10));
	__DSPRegs[DSP_ARAM_DMA_ARAM_LO]
	    = (__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & 0xFFFF001F | ((u16)aram_addr));
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = __DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000 | ((type << 0xF) & ~0x7FFF);
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = (__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & 0xFFFFFC00) | (length >> 0x10);
	__DSPRegs[DSP_ARAM_DMA_SIZE_LO]
	    = (__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & 0xFFFF001F)
	      | (length & 0x0000FFFF);
	OSRestoreInterrupts(old);
}

u32 ARAlloc(u32 length)
{
	u32 tmp;
	int old;

	old = OSDisableInterrupts();
	ASSERTMSGLINE(0x17E, !(length & 0x1F),
	              "ARAlloc(): length is not multiple of 32bytes!");
	ASSERTMSGLINE(0x182, length <= (__AR_Size - __AR_StackPointer),
	              "ARAlloc(): Out of ARAM!");
	ASSERTMSGLINE(0x183, __AR_FreeBlocks, "ARAlloc(): No more free blocks!");
	tmp = __AR_StackPointer;
	__AR_StackPointer += length;
	*__AR_BlockLength = length;
	__AR_BlockLength += 1;
	__AR_FreeBlocks -= 1;
	OSRestoreInterrupts(old);
	return tmp;
}

u32 ARInit(u32* stack_index_addr, u32 num_entries)
{
	BOOL enabled;

	if (__AR_init_flag == 1) {
		return 0x4000;
	}
	enabled       = OSDisableInterrupts();
	__AR_Callback = NULL;
	__OSSetInterruptHandler(6, __ARHandler);
	__OSUnmaskInterrupts(0x02000000);
	__AR_StackPointer = 0x4000;
	__AR_FreeBlocks   = num_entries;
	__AR_BlockLength  = stack_index_addr;

	// WHY?
	__DSPRegs[DSP_ARAM_REFRESH] = __DSPRegs[DSP_ARAM_REFRESH] & 0xff
	                              | __DSPRegs[DSP_ARAM_REFRESH] & ~0xff;
	__ARChecksize();
	__AR_init_flag = 1;
	OSRestoreInterrupts(enabled);

	return __AR_StackPointer;
}

u32 ARGetBaseAddress(void) { return 0x4000; }

u32 ARGetSize(void) { return __AR_Size; }

static void __ARHandler(__OSInterrupt exception, struct OSContext* context)
{
	struct OSContext exceptionContext;
	u16 tmp;

	tmp                           = __DSPRegs[DSP_CONTROL_STATUS];
	tmp                           = (tmp & ~0x88) | 0x20;
	__DSPRegs[DSP_CONTROL_STATUS] = (tmp);
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);
	if (__AR_Callback) {
		__AR_Callback();
	}
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

static void __ARClearInterrupt(void)
{
	u16 tmp;
	tmp                           = __DSPRegs[DSP_CONTROL_STATUS];
	tmp                           = tmp & ~0x88 | 0x20;
	__DSPRegs[DSP_CONTROL_STATUS] = tmp;
}

static void __ARWaitForDMA(void)
{
	while (__DSPRegs[DSP_CONTROL_STATUS] & 0x200)
		;
}

static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
	// Main mem address
	__DSPRegs[DSP_ARAM_DMA_MM_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff)
	            | (u16)(mmem_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_MM_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0)
	            | (u16)(mmem_addr & 0xffff));

	// ARAM address
	__DSPRegs[DSP_ARAM_DMA_ARAM_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff)
	            | (u16)(aram_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_ARAM_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0)
	            | (u16)(aram_addr & 0xffff));

	// DMA buffer size
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000);

	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff)
	            | (u16)(length >> 16));
	__DSPRegs[DSP_ARAM_DMA_SIZE_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0)
	            | (u16)(length & 0xffff));

	__ARWaitForDMA();
	__ARClearInterrupt();
}

static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
	// Main mem address
	__DSPRegs[DSP_ARAM_DMA_MM_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff)
	            | (u16)(mmem_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_MM_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0)
	            | (u16)(mmem_addr & 0xffff));

	// ARAM address
	__DSPRegs[DSP_ARAM_DMA_ARAM_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff)
	            | (u16)(aram_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_ARAM_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0)
	            | (u16)(aram_addr & 0xffff));

	// DMA buffer size
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] | 0x8000);

	__DSPRegs[DSP_ARAM_DMA_SIZE_HI]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff)
	            | (u16)(length >> 16));
	__DSPRegs[DSP_ARAM_DMA_SIZE_LO]
	    = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0)
	            | (u16)(length & 0xffff));

	__ARWaitForDMA();
	__ARClearInterrupt();
}

static void __ARChecksize(void)
{
	u8 test_data_pad[63];
	u8 dummy_data_pad[63];
	u8 buffer_pad[63];
	u32* test_data;
	u32* dummy_data;
	u32* buffer;
	u16 ARAM_mode;
	u32 ARAM_size;
	u32 i;

	do {
	} while (!(__DSPRegs[DSP_ARAM_MODE] & 1));

	ARAM_mode = 3;
	ARAM_size = __AR_InternalSize = 0x1000000;

	__DSPRegs[DSP_ARAM_SIZE]
	    = ((__DSPRegs[DSP_ARAM_SIZE] & 0xFFFFFFC0) | ARAM_mode) | 0x20;

	test_data  = (void*)ALIGN_NEXT((u32)test_data_pad, 0x20);
	dummy_data = (void*)ALIGN_NEXT((u32)dummy_data_pad, 0x20);
	buffer     = (void*)ALIGN_NEXT((u32)buffer_pad, 0x20);
	for (i = 0; i < 8; i++) {
		test_data[i]  = 0xDEADBEEF;
		dummy_data[i] = 0xBAD0BAD0;
	}

	DCFlushRange(test_data, 0x20);
	DCFlushRange(dummy_data, 0x20);

	__AR_ExpansionSize = 0;

	__ARWriteDMA((u32)dummy_data, ARAM_size + 0x0, 0x20U);
	__ARWriteDMA((u32)dummy_data, ARAM_size + 0x200000, 0x20U);
	__ARWriteDMA((u32)dummy_data, ARAM_size + 0x1000000, 0x20U);
	__ARWriteDMA((u32)dummy_data, ARAM_size + 0x200, 0x20U);
	__ARWriteDMA((u32)dummy_data, ARAM_size + 0x400000, 0x20U);

	memset(buffer, 0, 0x20);
	DCFlushRange(buffer, 0x20);

	__ARWriteDMA((u32)test_data, ARAM_size, 0x20U);
	DCInvalidateRange(buffer, 0x20);

	__ARReadDMA((u32)buffer, ARAM_size, 0x20U);
	PPCSync();

	if (*buffer == *test_data) {
		memset(buffer, 0, 0x20);
		DCFlushRange(buffer, 0x20);

		__ARReadDMA((u32)buffer, ARAM_size + 0x200000, 0x20U);
		PPCSync();

		if (*buffer == *test_data) {
			ARAM_size += 0x200000;
			__AR_ExpansionSize = 0x200000;
		} else {
			memset(buffer, 0, 0x20);
			DCFlushRange(buffer, 0x20);

			__ARReadDMA((u32)buffer, ARAM_size + 0x01000000, 0x20U);
			PPCSync();

			if (*buffer == *test_data) {
				ARAM_mode |= 8;
				ARAM_size += 0x400000;
				__AR_ExpansionSize = 0x400000;
			} else {
				memset(buffer, 0, 0x20);
				DCFlushRange(buffer, 0x20);

				__ARReadDMA((u32)buffer, ARAM_size + 0x200, 0x20U);
				PPCSync();

				if (*buffer == *test_data) {
					ARAM_mode |= 0x10;
					ARAM_size += 0x800000;
					__AR_ExpansionSize = 0x800000;
				} else {
					memset(buffer, 0, 0x20);
					DCFlushRange(buffer, 0x20);

					__ARReadDMA((u32)buffer, ARAM_size + 0x400000, 0x20U);
					PPCSync();

					if (*buffer == *test_data) {
						ARAM_mode |= 0x18;
						ARAM_size += 0x01000000;
						__AR_ExpansionSize = 0x1000000;
					} else {
						ARAM_mode |= 0x20;
						ARAM_size += 0x02000000;
						__AR_ExpansionSize = 0x2000000;
					}
				}
			}
		}

		__DSPRegs[DSP_ARAM_SIZE]
		    = ((u16)(__DSPRegs[DSP_ARAM_SIZE] & 0xFFFFFFC0) | ARAM_mode);
	}
	*(u32*)OSPhysicalToUncached(0xD0) = ARAM_size;
	__AR_Size                         = ARAM_size;
}
