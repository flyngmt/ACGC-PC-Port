#ifndef PPCARCH_H
#define PPCARCH_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 PPCMfmsr(void);
void PPCMtmsr(u32);

u32 PPCMfhid0(void);
void PPCMthid0(u32);

u32 PPCMfl2cr(void);
void PPCMtl2cr(u32);

void PPCMtdec(u32);

void PPCSync(void);
void PPCHalt(void);

u32 PPCMfhid2(void);
void PPCMthid2(u32);


void PPCMtwpar(u32);

void PPCDisableSpeculation(void);
void PPCSetFpNonIEEEMode(void);

#define HID0_EMCP       0x80000000u  // Enable MCP
#define HID0_DBP        0x40000000u  // Enable 60x bus address and data parity chk
#define HID0_EBA        0x20000000u  // Enable 60x address parity checking
#define HID0_EBD        0x10000000u  // Enable 60x data parity checking
#define HID0_BCLK       0x08000000u  // CLK_OUT output enable and clk selection
#define HID0_ECLK       0x02000000u  // CLK_OUT output enable and clk selection
#define HID0_PAR        0x01000000u  // Disable !ARTRY precharge
#define HID0_DOZE       0x00800000u  // Doze mode enable
#define HID0_NAP        0x00400000u  // Nap mode enable
#define HID0_SLEEP      0x00200000u  // Sleep mode enable
#define HID0_DPM        0x00100000u  // Dynamic power management enable
#define HID0_NHR        0x00010000u  // Not hard reset (0 hard reset if s/w set it)
#define HID0_ICE        0x00008000u  // Instruction cache enable
#define HID0_DCE        0x00004000u  // Data cache enable
#define HID0_ILOCK      0x00002000u  // ICache lock
#define HID0_DLOCK      0x00001000u  // DCache lock
#define HID0_ICFI       0x00000800u  // ICache flash invalidate
#define HID0_DCFI       0x00000400u  // DCache flash invalidate
#define HID0_SPD        0x00000200u  // Speculative cache access enable (0 enable)
#define HID0_IFEM       0x00000100u  // Enable M bit on bus for Ifetch
#define HID0_SGE        0x00000080u  // Store gathering enable
#define HID0_DCFA       0x00000040u  // DCache flush assist - set before a flush
#define HID0_BTIC       0x00000020u  // Branch target icache enable
#define HID0_ABE        0x00000008u  // Address bcast enable
#define HID0_BHT        0x00000004u  // Branch history table enable
#define HID0_NOOPTI     0x00000001u  // No-op Dcache touch instructions

#define HID2_DCHERR         0x00800000  // ERROR: dcbz_l cache hit
#define HID2_DNCERR         0x00400000  // ERROR: DMA access to normal cache
#define HID2_DCMERR         0x00200000  // ERROR: DMA cache miss error
#define HID2_DQOERR         0x00100000  // ERROR: DMA queue overflow
#define HID2_DCHEE          0x00080000  // dcbz_l cache hit error enable
#define HID2_DNCEE          0x00040000  // DMA access to normal cache error enable
#define HID2_DCMEE          0x00020000  // DMA cache miss error error enable
#define HID2_DQOEE          0x00010000  // DMA queue overflow error enable

#define SRR1_DMA_BIT                0x00200000
#define SRR1_L2DP_BIT               0x00100000

#define L2CR_L2E                    0x80000000  // L2 Enable
#define L2CR_L2PE                   0x40000000  // L2 data parity generation and checking enable

#define L2CR_L2DO                   0x00400000  // Data only
#define L2CR_L2I                    0x00200000  // Global invalidate
#define L2CR_L2CTL                  0x00100000  // ZZ enable
#define L2CR_L2WT                   0x00080000  // L2 write through
#define L2CR_L2TS                   0x00040000  // L2 test support

#define MSR_POW         0x00040000  // Power Management
#define MSR_ILE         0x00010000  // Interrupt Little Endian
#define MSR_EE          0x00008000  // external interrupt
#define MSR_PR          0x00004000  // privilege level(should be 0)
#define MSR_FP          0x00002000  // floating point available
#define MSR_ME          0x00001000  // machine check enable
#define MSR_FE0         0x00000800  // floating point exception enable
#define MSR_SE          0x00000400  // single step trace enable
#define MSR_BE          0x00000200  // branch trace enable
#define MSR_FE1         0x00000100  // floating point exception enable
#define MSR_IP          0x00000040  // Exception prefix
#define MSR_IR          0x00000020  // instruction relocate
#define MSR_DR          0x00000010  // data relocate
#define MSR_PM          0x00000004  // Performance monitor marked mode
#define MSR_RI          0x00000002  // Recoverable interrupt
#define MSR_LE          0x00000001  // Little Endian

#define MSR_POW_BIT 13 // Power Management
#define MSR_ILE_BIT 15 // Interrupt Little Endian
#define MSR_EE_BIT  16 // external interrupt
#define MSR_PR_BIT  17 // privilege level (should be 0)
#define MSR_FP_BIT  18 // floating point available
#define MSR_ME_BIT  19 // machine check enable
#define MSR_FE0_BIT 20 // floating point exception enable
#define MSR_SE_BIT  21 // single step trace enable
#define MSR_BE_BIT  22 // branch trace enable
#define MSR_FE1_BIT 23 // floating point exception enable
#define MSR_IP_BIT  25 // Exception prefix
#define MSR_IR_BIT  26 // instruction relocate
#define MSR_DR_BIT  27 // data relocate
#define MSR_PM_BIT  29 // Performance monitor marked mode
#define MSR_RI_BIT  30 // Recoverable interrupt
#define MSR_LE_BIT  31 // Little Endian

#ifdef __cplusplus
}
#endif
#endif
