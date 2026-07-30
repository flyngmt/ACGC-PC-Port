#ifndef _DOLPHIN_PPCARCH_H
#define _DOLPHIN_PPCARCH_H

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define HID0 0x3f0
#define HID0_ICE 0x8000
#define HID0_ICFI 0x800
#define HID0_DCE 0x4000
#define HID2 0x398
#define HID2_LCE_BIT 3
#define MSR_ME 0x1000
#define LC_BASE_PREFIX 0xE000
#define DBAT3L 3
#define DBAT3U 3
#define DMA_U 0x39a
#define DMA_L 0x39b
#define DMA_L_STORE 0
#define DMA_L_TRIGGER 2
#define LC_MAX_DMA_BLOCKS 128
#define LC_MAX_DMA_BYTES 0x1000

#define MSR_IR 0x00000020 // instruction relocate
#define MSR_DR 0x00000010 // data relocate

#define HID2_DCHERR 0x00800000 // ERROR: dcbz_l cache hit
#define HID2_DNCERR 0x00400000 // ERROR: DMA access to normal cache
#define HID2_DCMERR 0x00200000 // ERROR: DMA cache miss error
#define HID2_DQOERR 0x00100000 // ERROR: DMA queue overflow
#define HID2_DCHEE 0x00080000  // dcbz_l cache hit error enable
#define HID2_DNCEE 0x00040000  // DMA access to normal cache error enable
#define HID2_DCMEE 0x00020000  // DMA cache miss error error enable
#define HID2_DQOEE 0x00010000  // DMA queue overflow error enable

#define L2CR_L2E 0x80000000  // L2 Enable
#define L2CR_L2I 0x00200000  // Global invalidate
#define L2CR_L2IP 0x00000001 // L2 global invalidate in progress

#define SRR1_DMA_BIT 0x00200000
#define SRR1_L2DP_BIT 0x00100000

    u32 PPCMfmsr();
    void PPCMtmsr(u32 newMSR);
    // u32 PPCOrMsr(u32 value);
    void PPCOrMsr();
    u32 PPCMfhid0();
    void PPCMthid0(u32 newHID0);
    u32 PPCMfl2cr();
    void PPCMtl2cr(u32 newL2cr);
    void PPCMtdec(u32 newDec);
    void PPCSync();
    void PPCHalt();
    u32 PPCMffpscr();
    void PPCMtfpscr(u32 newFPSCR);
    u32 PPCMfhid2();
    void PPCMthid2(u32 newhid2);
    u32 PPCMfwpar();
    void PPCMtwpar(u32 newwpar);
    void PPCEnableSpeculation();
    void PPCDisableSpeculation();
    void PPCSetFpIEEEMode();
    void PPCSetFpNonIEEEMode();

#ifdef __cplusplus
}
#endif

#endif
