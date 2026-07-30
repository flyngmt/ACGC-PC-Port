#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/base/PPCArch.h"

void DBPrintf(char* str, ...);
void OSReport(char* msg, ...);
void L2GlobalInvalidate(void);

/* clang-format off */
//Needs OSError stuff
asm void DCEnable(void){
	nofralloc
	sync
	mfspr r3, 0x3f0
	ori r3, r3, 0x4000
	mtspr 0x3f0, r3
	blr
}
asm void DCInvalidateRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pi_r
	addi len, len, 0x20
	
pi_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
inv_ran:
	dcbi 0, buf
	addi buf, buf, 0x20
	bdnz inv_ran
	
	blr
}
asm void DCFlushRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pf_r
	addi len, len, 0x20
	
pf_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
fls_ran:
	dcbf 0, buf
	addi buf, buf, 0x20
	bdnz fls_ran
	sc
	blr
}

asm void DCStoreRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- ps_r
	addi len, len, 0x20
	
ps_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
st_ran:
	dcbst 0, buf
	addi buf, buf, 0x20
	bdnz st_ran
	sc
	blr
}

asm void DCFlushRangeNoSync(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pfns_r
	addi len, len, 0x20
	
pfns_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
fls_ranns:
	dcbf 0, buf
	addi buf, buf, 0x20
	bdnz fls_ranns
	blr
}

asm void DCStoreRangeNoSync(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- psns_r
	addi len, len, 0x20
	
psns_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
st_ranns:
	dcbst 0, buf
	addi buf, buf, 0x20
	bdnz st_ranns
	blr
}

asm void DCZeroRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pzr_r
	addi len, len, 0x20
	
pzr_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
z_ran:
	dcbz 0, buf
	addi buf, buf, 0x20
	bdnz z_ran
	blr
}

asm void DCTouchRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- ptor_r
	addi len, len, 0x20
	
ptor_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
t_ran:
	dcbt 0, buf
	addi buf, buf, 0x20
	bdnz t_ran
	blr
}

asm void ICInvalidateRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pir_r
	addi len, len, 0x20
	
pir_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
i_ran:
	icbi 0, buf
	addi buf, buf, 0x20
	bdnz i_ran
	sync
	isync
	blr
}
asm void ICFlashInvalidate(void){
	nofralloc
	mfspr r3, 0x3f0
	ori r3, r3, 0x800
	mtspr 0x3f0, r3
	blr
}

asm void ICEnable(void){
	nofralloc
	isync
	mfspr r3, 0x3f0
	ori r3, r3, 0x8000
	mtspr 0x3f0, r3
	blr
}

asm void LCDisable(void){
	nofralloc
	lis r3, 0xE000
	li r4, 0x200
	mtctr r4
dis:
	dcbi 0, r3
	addi r3, r3, 0x20
	bdnz dis
	mfspr r4, 0x398
	rlwinm r4, r4, 0, 4, 2
	mtspr 0x398, r4
	blr
}
/* clang-format on */

void L2Enable(void) {
    PPCMtl2cr((PPCMfl2cr() | L2CR_L2E) & ~L2CR_L2I);
}

void L2Disable(void) {
    __sync();
    PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
    __sync();
}

void L2GlobalInvalidate(void) {
    L2Disable();
    PPCMtl2cr(PPCMfl2cr() | 0x00200000);
    while (PPCMfl2cr() & 0x00000001u)
        ;
    PPCMtl2cr(PPCMfl2cr() & ~0x00200000);
    while (PPCMfl2cr() & 0x00000001u) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

static void L2Init(void) {
    u32 oldMSR;
    oldMSR = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();
    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(oldMSR);
}

void DMAErrorHandler(OSError error, OSContext* context, ...) {
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);
    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) || !(context->srr1 & SRR1_DMA_BIT)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport("\t- Requested a locked cache tag that was already in the cache\n");
    }

    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }

    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }

    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    // write hid2 back to clear the error bits
    PPCMthid2(hid2);
}

void __OSCacheInit() {
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }
    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

	OSSetErrorHandler(1, DMAErrorHandler);

	DBPrintf("Locked cache machine check handler installed\n");
}
