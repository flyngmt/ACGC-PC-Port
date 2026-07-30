#include "dolphin/BASE/ppcarch.h"

asm u32 PPCMfmsr(void){
    nofralloc
    mfmsr r3
    blr
}

asm void PPCMtmsr(register u32 value){
    nofralloc
    mtmsr value
    blr
}

asm u32 PPCMfhid0(void){
    nofralloc
    mfspr r3, 0x3f0
    blr
}

asm void PPCMthid0(register u32 value) {
    nofralloc
    mtspr 0x3f0, value
    blr
} 

asm u32 PPCMfl2cr(void) {
    nofralloc
    mfspr r3, 0x3f9
    blr
}

asm void PPCMtl2cr(register u32 value) {
    nofralloc
    mtspr 0x3f9, value
    blr
}
asm void PPCMtdec(register u32 value) {
    nofralloc
    mtspr 0x16, value
    blr
}

asm void PPCSync(void){
    nofralloc
    sc
    blr
}

asm void PPCHalt(void){
    nofralloc 
    sync

loop:
    nop
    li r3, 0
    nop
    b loop
}
asm u32 PPCMfhid2(void){
    nofralloc
    mfspr r3, 0x398
    blr
}

asm void PPCMthid2(u32 register value){
    nofralloc
    mtspr 0x398, value
    blr
}
asm void PPCMtwpar(u32 register value){
    nofralloc
    mtspr 0x399, value
    blr
}

void PPCDisableSpeculation(void) { 
    PPCMthid0(PPCMfhid0() | (1 << (31 - 22))); 
}

asm void PPCSetFpNonIEEEMode(void){
    nofralloc
    mtfsb1 0x1D
    blr
}
 