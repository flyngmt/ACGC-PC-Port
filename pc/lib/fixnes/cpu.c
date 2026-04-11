/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include "mapper.h"
#include "mem.h"
#include "ppu.h"
#include "apu.h"
#include "cpu.h"
#include "mapper_h/nsf.h"

#define P_FLAG_CARRY (1<<0)
#define P_FLAG_ZERO (1<<1)
#define P_FLAG_IRQ_DISABLE (1<<2)
#define P_FLAG_DECIMAL (1<<3)
#define P_FLAG_S1 (1<<4)
#define P_FLAG_S2 (1<<5)
#define P_FLAG_OVERFLOW (1<<6)
#define P_FLAG_NEGATIVE (1<<7)

#define CPU_OAM_DMA (1<<0)
#define CPU_DMC_DMA (1<<1)

extern bool nesPause;

//used externally
uint8_t interrupt;
bool cpu_odd_cycle;
bool cpuWriteTMP;

static struct {
	const uint8_t *action_arr;
	uint16_t pc, pc_nsf_bak, absAddr, indVal;
	uint8_t p,p_nsf_bak,a,x,y,s,tmp;
	uint8_t p_irq_req;
	uint8_t arr_pos;
	uint8_t instr;
	uint8_t irq;
	uint8_t irqMask;
	uint8_t dma;
	bool boot;
	bool reset;
	bool needsIndFix;
	bool allow_update_irq;
	bool currently_dma;
	bool oam_ready;
	bool dmc_dma_dummyread;
	bool dmc_halted;
	bool oam_halted;
	bool dmc_halt_attempt;
	bool oam_dma_pause;
	uint16_t oam_dma_addr;
	uint16_t dmc_dma_addr;
	uint8_t oam_dma_ptr;
	uint8_t oam_dma_val;
} cpu;

static void cpuSetStartArray();

void cpuInit()
{
	cpuSetStartArray();
	cpu.boot = true; //sets up P
	cpu.reset = true;
	cpu.allow_update_irq = false;
	cpu.needsIndFix = false;
	cpu.tmp = 0;
	cpu.absAddr = 0;
	cpu.pc = 0;
	cpu.pc_nsf_bak = 0;
	cpu.indVal = 0;
	cpu.p = 0;
	cpu.p_nsf_bak = 0;
	cpu.a = 0;
	cpu.x = 0;
	cpu.y = 0;
	cpu.s = 0;
	cpu.p_irq_req = 0;
	cpu.instr = 0;
	cpu.irq = 0;
	cpu.irqMask = 0;
	cpu.dma = 0;
	cpu.currently_dma = false;
	cpu.oam_ready = false;
	cpu.dmc_dma_dummyread = false;
	cpu.dmc_halted = false;
	cpu.oam_halted = false;
	cpu.dmc_halt_attempt = false;
	cpu.oam_dma_pause = false;
	cpu.oam_dma_addr = 0;
	cpu.dmc_dma_addr = 0;
	cpu.oam_dma_ptr = 0;
	cpu.oam_dma_val = 0;

	interrupt = 0;
	cpu_odd_cycle = false;
	cpuWriteTMP = false;

	//may still be set going from nsf to nes file
	//in retroarch, so clear those
	nsf_startPlayback = false;
	nsf_endPlayback = false;
}

FIXNES_ALWAYSINLINE inline static void setRegStats(uint8_t reg)
{
	if(reg == 0)
	{
		cpu.p |= P_FLAG_ZERO;
		cpu.p &= ~P_FLAG_NEGATIVE;
	}
	else
	{
		if(reg & (1<<7))
			cpu.p |= P_FLAG_NEGATIVE;
		else
			cpu.p &= ~P_FLAG_NEGATIVE;
		cpu.p &= ~P_FLAG_ZERO;
	}
}

FIXNES_ALWAYSINLINE inline static void cpuSetARRRegs()
{
	if((cpu.a & ((1<<5) | (1<<6))) == ((1<<5) | (1<<6)))
	{
		cpu.p |= P_FLAG_CARRY;
		cpu.p &= ~P_FLAG_OVERFLOW;
	}
	else if((cpu.a & ((1<<5) | (1<<6))) == 0)
	{
		cpu.p &= ~P_FLAG_CARRY;
		cpu.p &= ~P_FLAG_OVERFLOW;
	}
	else if(cpu.a & (1<<5))
	{
		cpu.p &= ~P_FLAG_CARRY;
		cpu.p |= P_FLAG_OVERFLOW;
	}
	else if(cpu.a & (1<<6))
	{
		cpu.p |= P_FLAG_CARRY;
		cpu.p |= P_FLAG_OVERFLOW;
	}
}

/* Helper functions for updating reg sets */

FIXNES_ALWAYSINLINE inline static void cpuSetA(uint8_t val)
{
	cpu.a = val;
	setRegStats(cpu.a);
}

FIXNES_ALWAYSINLINE inline static void cpuSetX(uint8_t val)
{
	cpu.x = val;
	setRegStats(cpu.x);
}

FIXNES_ALWAYSINLINE inline static void cpuSetY(uint8_t val)
{
	cpu.y = val;
	setRegStats(cpu.y);
}

FIXNES_ALWAYSINLINE inline static uint8_t cpuSetTMP(uint8_t val)
{
	setRegStats(val);
	return val;
}

/* Various Instructions used multiple times */

FIXNES_ALWAYSINLINE inline static void cpuAND()
{
	cpu.a &= cpu.tmp;
	setRegStats(cpu.a);
}

FIXNES_ALWAYSINLINE inline static void cpuORA()
{
	cpu.a |= cpu.tmp;
	setRegStats(cpu.a);
}

FIXNES_ALWAYSINLINE inline static void cpuEOR()
{
	cpu.a ^= cpu.tmp;
	setRegStats(cpu.a);
}

FIXNES_ALWAYSINLINE inline static uint8_t cpuASL(uint8_t val)
{
	if(val & (1<<7))
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;
	val <<= 1;
	setRegStats(val);
	return val;
}

FIXNES_ALWAYSINLINE inline static void cpuASLa() { cpuSetA(cpuASL(cpu.a)); };
FIXNES_ALWAYSINLINE inline static void cpuASLt() { cpu.tmp = cpuASL(cpu.tmp); };

FIXNES_ALWAYSINLINE inline static uint8_t cpuLSR(uint8_t val)
{
	if(val & (1<<0))
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;
	val >>= 1;
	setRegStats(val);
	return val;
}

FIXNES_ALWAYSINLINE inline static void cpuLSRa() { cpuSetA(cpuLSR(cpu.a)); };
FIXNES_ALWAYSINLINE inline static void cpuLSRt() { cpu.tmp = cpuLSR(cpu.tmp); };

FIXNES_ALWAYSINLINE inline static uint8_t cpuROL(uint8_t val)
{
	uint8_t oldP = cpu.p;
	if(val & (1<<7))
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;
	val<<=1;
	if(oldP & P_FLAG_CARRY)
		val |= (1<<0); //bit 0
	setRegStats(val);
	return val;
}

FIXNES_ALWAYSINLINE inline static void cpuROLa() { cpuSetA(cpuROL(cpu.a)); };
FIXNES_ALWAYSINLINE inline static void cpuROLt() { cpu.tmp = cpuROL(cpu.tmp); };

FIXNES_ALWAYSINLINE inline static uint8_t cpuROR(uint8_t val)
{
	uint8_t oldP = cpu.p;
	if(val & (1<<0))
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;
	val>>=1;
	if(oldP & P_FLAG_CARRY)
		val |= (1<<7); //bit 7
	setRegStats(val);
	return val;
}

FIXNES_ALWAYSINLINE inline static void cpuRORa() { cpuSetA(cpuROR(cpu.a)); };
FIXNES_ALWAYSINLINE inline static void cpuRORt() { cpu.tmp = cpuROR(cpu.tmp); };

FIXNES_ALWAYSINLINE inline static void cpuKIL()
{
	printf("Processor Requested Lock-Up at %04x\n", cpu.pc-1);
	nesPause = true;
}

FIXNES_ALWAYSINLINE inline static void cpuADCv(uint8_t in)
{
	//use uint16_t here to easly detect carry
	uint16_t res = cpu.a + in;

	if(cpu.p & P_FLAG_CARRY)
		res++;

	if(res > 0xFF)
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;

	if(!(cpu.a & (1<<7)) && !(in & (1<<7)) && (res & (1<<7)))
		cpu.p |= P_FLAG_OVERFLOW;
	else if((cpu.a & (1<<7)) && (in & (1<<7)) && !(res & (1<<7)))
		cpu.p |= P_FLAG_OVERFLOW;
	else
		cpu.p &= ~P_FLAG_OVERFLOW;

	cpuSetA(res);
}

FIXNES_ALWAYSINLINE inline static void cpuADC() { cpuADCv(cpu.tmp); }

FIXNES_ALWAYSINLINE inline static void cpuSBC() { cpuADCv(~cpu.tmp); }

FIXNES_ALWAYSINLINE inline static void cpuISC() { cpu.tmp = cpuSetTMP(cpu.tmp+1); cpuSBC(); }


FIXNES_ALWAYSINLINE inline static uint8_t cpuCMP(uint8_t reg)
{
	if(reg >= cpu.tmp)
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;

	uint8_t cmpVal = (reg - cpu.tmp);
	setRegStats(cmpVal);
	return cmpVal;
}

FIXNES_ALWAYSINLINE inline static void cpuCMPa() { cpuCMP(cpu.a); }
FIXNES_ALWAYSINLINE inline static void cpuCMPx() { cpuCMP(cpu.x); }
FIXNES_ALWAYSINLINE inline static void cpuCMPy() { cpuCMP(cpu.y); }
FIXNES_ALWAYSINLINE inline static void cpuCMPax() { cpu.x = cpuCMP(cpu.a&cpu.x); }
FIXNES_ALWAYSINLINE inline static void cpuDCP() { cpu.tmp = cpuSetTMP(cpu.tmp-1); cpuCMPa(); }

FIXNES_ALWAYSINLINE inline static void cpuBIT()
{
	if((cpu.a & cpu.tmp) == 0)
		cpu.p |= P_FLAG_ZERO;
	else
		cpu.p &= ~P_FLAG_ZERO;

	if(cpu.tmp & P_FLAG_OVERFLOW)
		cpu.p |= P_FLAG_OVERFLOW;
	else
		cpu.p &= ~P_FLAG_OVERFLOW;

	if(cpu.tmp & P_FLAG_NEGATIVE)
		cpu.p |= P_FLAG_NEGATIVE;
	else
		cpu.p &= ~P_FLAG_NEGATIVE;
}

FIXNES_ALWAYSINLINE inline static void cpuSLO() { cpuASLt(); cpuORA(); }
FIXNES_ALWAYSINLINE inline static void cpuRLA() { cpuROLt(); cpuAND(); }
FIXNES_ALWAYSINLINE inline static void cpuSRE() { cpuLSRt(); cpuEOR(); }
FIXNES_ALWAYSINLINE inline static void cpuRRA() { cpuRORt(); cpuADC(); }
FIXNES_ALWAYSINLINE inline static void cpuASR() { cpuAND(); cpuLSRa(); }

FIXNES_ALWAYSINLINE inline static void cpuARR()
{
	cpuAND();
	cpuRORa();
	cpuSetARRRegs();
}

FIXNES_ALWAYSINLINE inline static void cpuAAC()
{
	cpuAND();
	if(cpu.p & P_FLAG_NEGATIVE)
		cpu.p |= P_FLAG_CARRY;
	else
		cpu.p &= ~P_FLAG_CARRY;
}

FIXNES_ALWAYSINLINE inline static void cpuCLC() { cpu.p &= ~P_FLAG_CARRY; }
FIXNES_ALWAYSINLINE inline static void cpuSEC() { cpu.p |= P_FLAG_CARRY; }

FIXNES_ALWAYSINLINE inline static void cpuCLI() { cpu.p_irq_req = 2; }
FIXNES_ALWAYSINLINE inline static void cpuSEI() { cpu.p_irq_req = 1; }

FIXNES_ALWAYSINLINE inline static void cpuCLV() { cpu.p &= ~P_FLAG_OVERFLOW; }

FIXNES_ALWAYSINLINE inline static void cpuCLD() { cpu.p &= ~P_FLAG_DECIMAL; }
FIXNES_ALWAYSINLINE inline static void cpuSED() { cpu.p |= P_FLAG_DECIMAL; }

FIXNES_ALWAYSINLINE inline static void cpuINX() { cpuSetX(cpu.x+1); }
FIXNES_ALWAYSINLINE inline static void cpuINY() { cpuSetY(cpu.y+1); }
FIXNES_ALWAYSINLINE inline static void cpuINCt() { cpu.tmp = cpuSetTMP(cpu.tmp+1); }

FIXNES_ALWAYSINLINE inline static void cpuDEX() { cpuSetX(cpu.x-1); }
FIXNES_ALWAYSINLINE inline static void cpuDEY() { cpuSetY(cpu.y-1); }
FIXNES_ALWAYSINLINE inline static void cpuDECt() { cpu.tmp = cpuSetTMP(cpu.tmp-1); }

FIXNES_ALWAYSINLINE inline static void cpuTXA() { cpuSetA(cpu.x); }
FIXNES_ALWAYSINLINE inline static void cpuTYA() { cpuSetA(cpu.y); }
FIXNES_ALWAYSINLINE inline static void cpuTSX() { cpuSetX(cpu.s); }
FIXNES_ALWAYSINLINE inline static void cpuTXS() { cpu.s = cpu.x; }

FIXNES_ALWAYSINLINE inline static void cpuTAY() { cpuSetY(cpu.a); }
FIXNES_ALWAYSINLINE inline static void cpuTAX() { cpuSetX(cpu.a); }

FIXNES_ALWAYSINLINE inline static void cpuLDA() { cpuSetA(cpu.tmp); }
FIXNES_ALWAYSINLINE inline static void cpuLDX() { cpuSetX(cpu.tmp); }
FIXNES_ALWAYSINLINE inline static void cpuLDY() { cpuSetY(cpu.tmp); }
//written out XAA and ATX to what they could technically do depending on the magic (fixed to 0xFF here)
FIXNES_ALWAYSINLINE inline static void cpuXAA() { cpuSetA(/*(cpu.a|0xFF)&*/cpu.x&cpu.tmp); }
FIXNES_ALWAYSINLINE inline static void cpuATX() { cpuSetA(/*(cpu.a|0xFF)&*/cpu.tmp); cpuSetX(cpu.a); }
FIXNES_ALWAYSINLINE inline static void cpuLAX() { cpuSetA(cpu.tmp); cpuSetX(cpu.tmp); }
FIXNES_ALWAYSINLINE inline static void cpuLAR() { cpu.a = cpu.s; cpuAND(); cpuSetX(cpu.a); cpu.s = cpu.a; }

/* For Interrupt Handling */

#define DEBUG_INTR 0
#define DEBUG_JSR 0

/* Set up all CPU State Definitions */
typedef void (*cpu_action_t)(void);

enum {
	CPU_GET_INSTRUCTION = 0,
	CPU_NULL_READ8_PC,
	CPU_NULL_READ8_PC_INC,
	CPU_NULL_READ8_PC_CHK,
	CPU_NULL_READ8_PC_ACTION,
	CPU_NULL_READ8_PC_ADDR_ADDX_ZP,
	CPU_NULL_READ8_PC_ADDR_ADDY_ZP,
	CPU_NULL_READ8_PC_TMP_ADDX,
	CPU_NULL_READ8_PC_STACK_INC,
	CPU_NULL_READ8_PC_STACK_DEC,
	CPU_NULL_READ8_PC_STACK_DEC_SET_S1_S2_I,
	CPU_NULL_READ8_PC_STACK_DEC_SET_I,
	CPU_TMP_READ8_PC_INC,
	CPU_TMP_READ8_PC_INC_ACTION,
	CPU_TMP_READ8_PC_INC_CHECK_BCC,
	CPU_TMP_READ8_PC_INC_CHECK_BCS,
	CPU_TMP_READ8_PC_INC_CHECK_BNE,
	CPU_TMP_READ8_PC_INC_CHECK_BEQ,
	CPU_TMP_READ8_PC_INC_CHECK_BPL,
	CPU_TMP_READ8_PC_INC_CHECK_BMI,
	CPU_TMP_READ8_PC_INC_CHECK_BVC,
	CPU_TMP_READ8_PC_INC_CHECK_BVS,
	CPU_BRANCH_SETUP,
	CPU_PCL_FROM_TMP_PCH_READ8_PC,
	CPU_ADDR_READ8_PC_INC,
	CPU_ADDRL_READ8_PC_INC,
	CPU_ADDRH_READ8_PC_INC,
	CPU_ADDRH_READ8_PC_INC_ADDX,
	CPU_ADDRH_READ8_PC_INC_ADDY,
	CPU_ADDRL_READ8_TMP_INC,
	CPU_ADDRH_READ8_TMP,
	CPU_ADDRH_READ8_TMP_ADDY,
	CPU_ADDR_READ8,
	CPU_ADDR_READ8_CHK,
	CPU_ADDR_READ8_ACTION,
	CPU_ADDR_READ8_ACTION_CHK,
	CPU_INC_PAGE_ADDR_READ8_SET_PC,
	CPU_ADDR_WRITE8,
	CPU_ADDR_WRITE8_A,
	CPU_ADDR_WRITE8_X,
	CPU_ADDR_WRITE8_Y,
	CPU_ADDR_WRITE8_AX,
	CPU_ADDR_WRITE8_AXA,
	CPU_ADDR_WRITE8_XAS,
	CPU_ADDR_WRITE8_SYA,
	CPU_ADDR_WRITE8_SXA,
	CPU_ADDR_WRITE8_ACTION,
	CPU_STACK_GET_A,
	CPU_STACK_GET_P,
	CPU_STACK_GET_P_INC,
	CPU_STACK_GET_PCL_INC,
	CPU_STACK_GET_PCH,
	CPU_STACK_STORE_A_DEC,
	CPU_STACK_STORE_P_DEC,
	CPU_STACK_STORE_PCH_DEC,
	CPU_STACK_STORE_PCL_DEC,
	CPU_STACK_SET_S1_S2_STORE_P_DEC_SET_I,
	CPU_STACK_CLEAR_S1_SET_S2_STORE_P_DEC_SET_I,
	CPU_READ_RESETVEC_PCL,
	CPU_READ_RESETVEC_PCH,
	CPU_READ_NMI_IRQ_VEC_PCL,
	CPU_READ_NMI_IRQ_VEC_PCH,
	CPU_STATE_END,
};

enum {
	CPU_READ_PC = 0,
	CPU_READ_CPUTMP,
	CPU_READ_ABSADDR,
	CPU_READ_STACK,
	CPU_READ_RESETVECL,
	CPU_READ_RESETVECH,
	CPU_READ_NMI_IRQ_VECL,
	CPU_READ_NMI_IRQ_VECH,
	CPU_WRITE_ADDR,
	CPU_WRITE_STACK,
};

// every cpu state does cpu.a mem read/write, this defines all
static const uint8_t cpu_mem_type[CPU_STATE_END] = {
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_PC,
	CPU_READ_CPUTMP,
	CPU_READ_CPUTMP,
	CPU_READ_CPUTMP,
	CPU_READ_ABSADDR,
	CPU_READ_ABSADDR,
	CPU_READ_ABSADDR,
	CPU_READ_ABSADDR,
	CPU_READ_ABSADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_WRITE_ADDR,
	CPU_READ_STACK,
	CPU_READ_STACK,
	CPU_READ_STACK,
	CPU_READ_STACK,
	CPU_READ_STACK,
	CPU_WRITE_STACK,
	CPU_WRITE_STACK,
	CPU_WRITE_STACK,
	CPU_WRITE_STACK,
	CPU_WRITE_STACK,
	CPU_WRITE_STACK,
	CPU_READ_RESETVECL,
	CPU_READ_RESETVECH,
	CPU_READ_NMI_IRQ_VECL,
	CPU_READ_NMI_IRQ_VECH,
};

static const uint8_t cpu_start_arr[1] = { CPU_GET_INSTRUCTION };

FIXNES_ALWAYSINLINE inline static void cpuSetStartArray()
{
	cpu.action_arr = cpu_start_arr;
	cpu.arr_pos = 0;
}

/* arrays for non-callable instructions */
static const uint8_t cpu_boot_arr[6] = { CPU_NULL_READ8_PC_STACK_DEC, CPU_NULL_READ8_PC_STACK_DEC, CPU_NULL_READ8_PC_STACK_DEC_SET_S1_S2_I, CPU_READ_RESETVEC_PCL, CPU_READ_RESETVEC_PCH, CPU_GET_INSTRUCTION };
static const uint8_t cpu_reset_arr[6] = { CPU_NULL_READ8_PC_STACK_DEC, CPU_NULL_READ8_PC_STACK_DEC, CPU_NULL_READ8_PC_STACK_DEC_SET_I, CPU_READ_RESETVEC_PCL, CPU_READ_RESETVEC_PCH, CPU_GET_INSTRUCTION };
static const uint8_t cpu_irq_arr[7] = { CPU_NULL_READ8_PC, CPU_STACK_STORE_PCH_DEC, CPU_STACK_STORE_PCL_DEC, CPU_STACK_CLEAR_S1_SET_S2_STORE_P_DEC_SET_I, CPU_READ_NMI_IRQ_VEC_PCL, CPU_READ_NMI_IRQ_VEC_PCH, CPU_GET_INSTRUCTION };
static const uint8_t cpu_kill_arr[2] = { CPU_NULL_READ8_PC_ACTION, CPU_GET_INSTRUCTION };

/* arrays for single special instructions */
static const uint8_t cpu_brk_arr[7] = { CPU_NULL_READ8_PC_INC, CPU_STACK_STORE_PCH_DEC, CPU_STACK_STORE_PCL_DEC, CPU_STACK_SET_S1_S2_STORE_P_DEC_SET_I, CPU_READ_NMI_IRQ_VEC_PCL, CPU_READ_NMI_IRQ_VEC_PCH, CPU_GET_INSTRUCTION };
static const uint8_t cpu_rti_arr[6] = { CPU_NULL_READ8_PC, CPU_NULL_READ8_PC_STACK_INC, CPU_STACK_GET_P_INC, CPU_STACK_GET_PCL_INC, CPU_STACK_GET_PCH, CPU_GET_INSTRUCTION };
static const uint8_t cpu_rts_arr[6] = { CPU_NULL_READ8_PC, CPU_NULL_READ8_PC_STACK_INC, CPU_STACK_GET_PCL_INC, CPU_STACK_GET_PCH, CPU_NULL_READ8_PC_INC, CPU_GET_INSTRUCTION };
static const uint8_t cpu_php_arr[3] = { CPU_NULL_READ8_PC, CPU_STACK_STORE_P_DEC, CPU_GET_INSTRUCTION };
static const uint8_t cpu_pha_arr[3] = { CPU_NULL_READ8_PC, CPU_STACK_STORE_A_DEC, CPU_GET_INSTRUCTION };
static const uint8_t cpu_plp_arr[4] = { CPU_NULL_READ8_PC, CPU_NULL_READ8_PC_STACK_INC, CPU_STACK_GET_P, CPU_GET_INSTRUCTION };
static const uint8_t cpu_pla_arr[4] = { CPU_NULL_READ8_PC, CPU_NULL_READ8_PC_STACK_INC, CPU_STACK_GET_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_jsr_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_NULL_READ8_PC, CPU_STACK_STORE_PCH_DEC, CPU_STACK_STORE_PCL_DEC, CPU_PCL_FROM_TMP_PCH_READ8_PC, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absjmp_arr[3] = { CPU_TMP_READ8_PC_INC, CPU_PCL_FROM_TMP_PCH_READ8_PC, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indjmp_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_READ8, CPU_INC_PAGE_ADDR_READ8_SET_PC, CPU_GET_INSTRUCTION };

static const uint8_t cpu_zpsta_arr[3] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpstx_arr[3] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_WRITE8_X, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpsty_arr[3] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_WRITE8_Y, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpaax_arr[3] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_WRITE8_AX, CPU_GET_INSTRUCTION };

static const uint8_t cpu_zpXsta_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDX_ZP, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpXsty_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDX_ZP, CPU_ADDR_WRITE8_Y, CPU_GET_INSTRUCTION };

static const uint8_t cpu_zpYstx_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDY_ZP, CPU_ADDR_WRITE8_X, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpYaax_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDY_ZP, CPU_ADDR_WRITE8_AX, CPU_GET_INSTRUCTION };

static const uint8_t cpu_abssta_arr[4] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absstx_arr[4] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_WRITE8_X, CPU_GET_INSTRUCTION };
static const uint8_t cpu_abssty_arr[4] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_WRITE8_Y, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absaax_arr[4] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_WRITE8_AX, CPU_GET_INSTRUCTION };

static const uint8_t cpu_absXsta_arr[7] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDX, CPU_ADDR_READ8_CHK, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absXsya_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDX, CPU_ADDR_READ8, CPU_ADDR_WRITE8_SYA, CPU_GET_INSTRUCTION };

static const uint8_t cpu_absYsta_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absYaxa_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_WRITE8_AXA, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absYxas_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8, CPU_ADDR_WRITE8_XAS, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absYsxa_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8, CPU_ADDR_WRITE8_SXA, CPU_GET_INSTRUCTION };

static const uint8_t cpu_indXsta_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_NULL_READ8_PC_TMP_ADDX, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indXaax_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_NULL_READ8_PC_TMP_ADDX, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP, CPU_ADDR_WRITE8_AX, CPU_GET_INSTRUCTION };

static const uint8_t cpu_indYsta_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_WRITE8_A, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indYaxa_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_WRITE8_AXA, CPU_GET_INSTRUCTION };

static const uint8_t cpu_bcc_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BCC, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bcs_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BCS, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bne_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BNE, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_beq_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BEQ, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bpl_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BPL, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bmi_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BMI, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bvc_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BVC, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };
static const uint8_t cpu_bvs_arr[4] = { CPU_TMP_READ8_PC_INC_CHECK_BVS, CPU_BRANCH_SETUP, CPU_NULL_READ8_PC_CHK, CPU_GET_INSTRUCTION };

FIXNES_ALWAYSINLINE inline static void cpuCheckIrq()
{
	cpu.irq |= (interrupt & cpu.irqMask) | ppuNMI();
}

/* useful for the branch checks */
FIXNES_ALWAYSINLINE inline static void cpuBranchCheck(bool takeBranch)
{
	cpuCheckIrq();
	if(!takeBranch) //get next instruction
		cpuSetStartArray();
}

FIXNES_ALWAYSINLINE inline static void cpuBranchSetup()
{
	cpu.indVal = cpu.pc + (int8_t)cpu.tmp;
	//only need extra cycle if it needs fixup
	if((cpu.pc&0xFF00) != (cpu.indVal&0xFF00))
	{
		//printf("branch %04x %04x %02x\n", cpu.pc, cpu.indVal, cpu.tmp);
		cpu.needsIndFix = true;
	}
	else
		cpu.arr_pos++;
	cpu.pc = (cpu.pc&0xFF00)|(cpu.indVal&0x00FF);
}

/* arrays for multiple similar instructions */
static const uint8_t cpu_direct_arr[2] = { CPU_NULL_READ8_PC_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_imm_arr[2] = { CPU_TMP_READ8_PC_INC_ACTION, CPU_GET_INSTRUCTION };

static const uint8_t cpu_zpread_arr[3] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpreadwrite_arr[5] = { CPU_ADDR_READ8_PC_INC, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };

static const uint8_t cpu_zpXread_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDX_ZP, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpYread_arr[4] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDY_ZP, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_zpXreadwrite_arr[6] = { CPU_ADDR_READ8_PC_INC, CPU_NULL_READ8_PC_ADDR_ADDX_ZP, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };

static const uint8_t cpu_absread_arr[4] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absreadwrite_arr[6] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };

static const uint8_t cpu_absXread_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDX, CPU_ADDR_READ8_ACTION_CHK, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absYread_arr[5] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8_ACTION_CHK, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absXreadwrite_arr[7] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDX, CPU_ADDR_READ8_CHK, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };
static const uint8_t cpu_absYreadwrite_arr[7] = { CPU_ADDRL_READ8_PC_INC, CPU_ADDRH_READ8_PC_INC_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };

static const uint8_t cpu_indXread_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_NULL_READ8_PC_TMP_ADDX, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indXreadwrite_arr[8] = { CPU_TMP_READ8_PC_INC, CPU_NULL_READ8_PC_TMP_ADDX, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indYread_arr[6] = { CPU_TMP_READ8_PC_INC, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP_ADDY, CPU_ADDR_READ8_ACTION_CHK, CPU_ADDR_READ8_ACTION, CPU_GET_INSTRUCTION };
static const uint8_t cpu_indYreadwrite_arr[8] = { CPU_TMP_READ8_PC_INC, CPU_ADDRL_READ8_TMP_INC, CPU_ADDRH_READ8_TMP_ADDY, CPU_ADDR_READ8_CHK, CPU_ADDR_READ8, CPU_ADDR_WRITE8_ACTION, CPU_ADDR_WRITE8, CPU_GET_INSTRUCTION };

/* Set up array pointers to all instruction types */
static const uint8_t *cpu_instr_arr[256] = {
	cpu_brk_arr, cpu_indXread_arr, cpu_kill_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_php_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr,
	cpu_absread_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,

	cpu_bpl_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr,
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,

	cpu_jsr_arr, cpu_indXread_arr, cpu_kill_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_plp_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr,
	cpu_absread_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,
	
	cpu_bmi_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr,
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,
	
	cpu_rti_arr, cpu_indXread_arr, cpu_kill_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_pha_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr,
	cpu_absjmp_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,
	
	cpu_bvc_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr,
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,
	
	cpu_rts_arr, cpu_indXread_arr, cpu_kill_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_pla_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr,
	cpu_indjmp_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,
	
	cpu_bvs_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr,
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,
	
	cpu_imm_arr, cpu_indXsta_arr, cpu_imm_arr, cpu_indXaax_arr,
	cpu_zpsty_arr, cpu_zpsta_arr, cpu_zpstx_arr, cpu_zpaax_arr, 
	cpu_direct_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr, 
	cpu_abssty_arr, cpu_abssta_arr, cpu_absstx_arr, cpu_absaax_arr,
	
	cpu_bcc_arr, cpu_indYsta_arr, cpu_kill_arr, cpu_indYaxa_arr,
	cpu_zpXsty_arr, cpu_zpXsta_arr, cpu_zpYstx_arr, cpu_zpYaax_arr,
	cpu_direct_arr, cpu_absYsta_arr, cpu_direct_arr, cpu_absYxas_arr,
	cpu_absXsya_arr, cpu_absXsta_arr, cpu_absYsxa_arr, cpu_absYaxa_arr,
	
	cpu_imm_arr, cpu_indXread_arr, cpu_imm_arr, cpu_indXread_arr, 
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpread_arr, cpu_zpread_arr,
	cpu_direct_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr, 
	cpu_absread_arr, cpu_absread_arr, cpu_absread_arr, cpu_absread_arr,
	
	cpu_bcs_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYread_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpYread_arr, cpu_zpYread_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYread_arr, 
	cpu_absXread_arr, cpu_absXread_arr, cpu_absYread_arr, cpu_absYread_arr,
	
	cpu_imm_arr, cpu_indXread_arr, cpu_imm_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_direct_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr, 
	cpu_absread_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,
	
	cpu_bne_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr, 
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,
	
	cpu_imm_arr, cpu_indXread_arr, cpu_imm_arr, cpu_indXreadwrite_arr,
	cpu_zpread_arr, cpu_zpread_arr, cpu_zpreadwrite_arr, cpu_zpreadwrite_arr,
	cpu_direct_arr, cpu_imm_arr, cpu_direct_arr, cpu_imm_arr, 
	cpu_absread_arr, cpu_absread_arr, cpu_absreadwrite_arr, cpu_absreadwrite_arr,
	
	cpu_beq_arr, cpu_indYread_arr, cpu_kill_arr, cpu_indYreadwrite_arr,
	cpu_zpXread_arr, cpu_zpXread_arr, cpu_zpXreadwrite_arr, cpu_zpXreadwrite_arr,
	cpu_direct_arr, cpu_absYread_arr, cpu_direct_arr, cpu_absYreadwrite_arr, 
	cpu_absXread_arr, cpu_absXread_arr, cpu_absXreadwrite_arr, cpu_absXreadwrite_arr,
};

static bool cpuHandleIrqUpdates()
{
	//update irq flag if requested
	if(cpu.p_irq_req)
	{
		if(cpu.p_irq_req == 1)
		{
			#if DEBUG_INTR
			printf("Setting irq disable %02x %02x %d %d %d %d\n", cpu.p, P_FLAG_IRQ_DISABLE, cpu.irq, apu_interrupt, 
				!(cpu.p & P_FLAG_IRQ_DISABLE), (cpu.p & P_FLAG_IRQ_DISABLE) == 0);
			#endif
			cpu.p |= P_FLAG_IRQ_DISABLE;
			cpu.irqMask = 0;
		}
		else
		{
			#if DEBUG_INTR
			printf("Clearing irq disable %02x %02x %d %d %d %d\n", cpu.p, P_FLAG_IRQ_DISABLE, cpu.irq, apu_interrupt, 
				!(cpu.p & P_FLAG_IRQ_DISABLE), (cpu.p & P_FLAG_IRQ_DISABLE) == 0);
			#endif
			cpu.p &= ~P_FLAG_IRQ_DISABLE;
			cpu.irqMask = IRQ_MASK;
		}
		cpu.p_irq_req = 0;
	}
	//handle incoming IRQs
	if(cpu.reset)
	{
		//for consistent apu reset times
		cpu_odd_cycle = true;
		if(cpu.boot)
		{
			apuBoot();
			cpu.action_arr = cpu_boot_arr;
		}
		else
		{
			apuReset();
			ppuReset();
			mapperReset();
			cpu.action_arr = cpu_reset_arr;
		}
		cpu.arr_pos = 0;
		//cpu.instr = 0;
		cpu.boot = false;
		cpu.reset = false;
		return true;
	}
	else if(cpu.irq)
	{
		cpu.action_arr = cpu_irq_arr;
		cpu.arr_pos = 0;
		//cpu.instr = 0;
		#if DEBUG_INTR
		printf("NMI/INTR from instr %02x cpu.p %02x cpu.pc %04x\n",instr,cpu.p,cpu.pc);
		#endif
		return true;
	}
	//acts similar to an irq
	if(nsf_startPlayback)
	{
		cpuStartPlayNSF();
		nsf_startPlayback = false;
		return true;
	}
	else if(nsf_endPlayback)
	{
		cpuEndPlayNSF();
		nsf_endPlayback = false;
		return true;
	}
	return false;
}

FIXNES_ALWAYSINLINE inline static void cpuSetAddrIndFix()
{
	//first read will be at wrong pos
	//so let cpu know it needs fixup
	if((cpu.absAddr&0xFF00) != (cpu.indVal&0xFF00))
	{
		//printf("%04x %04x\n", cpu.absAddr, cpu.indVal);
		cpu.needsIndFix = true;
	}
}

FIXNES_ALWAYSINLINE inline static bool cpuDoAddrIndFix()
{
	if(cpu.needsIndFix)
	{
		cpu.absAddr = cpu.indVal;
		cpu.needsIndFix = false;
		return true;
	}
	else
		return false;
}

extern bool nesPAL;
static bool cpuDMATryHalt()
{
	bool ret = true;
	uint8_t cpuType = cpu_mem_type[cpu.action_arr[cpu.arr_pos]];
	switch(cpuType)
	{
		case CPU_READ_PC:
			if(nesPAL) break;
			memGet8(cpu.pc);
			break;
		case CPU_READ_CPUTMP:
			if(nesPAL) break;
			memGet8(cpu.tmp);
			break;
		case CPU_READ_ABSADDR:
			if(nesPAL) break;
			memGet8(cpu.absAddr);
			break;
		case CPU_READ_STACK:
			if(nesPAL) break;
			memGet8(0x100+cpu.s);
			break;
		case CPU_READ_RESETVECL:
			if(nesPAL) break;
			memGet8(0xFFFC);
			break;
		case CPU_READ_RESETVECH:
			if(nesPAL) break;
			memGet8(0xFFFD);
			break;
		case CPU_READ_NMI_IRQ_VECL:
			if(nesPAL) break;
			if(cpu.irq & PPU_NMI) //NMI
				memGet8(0xFFFA);
			else //IRQ
				memGet8(0xFFFE);
			break;
		case CPU_READ_NMI_IRQ_VECH:
			if(nesPAL) break;
			if(cpu.irq & PPU_NMI) //NMI
				memGet8(0xFFFB);
			else //IRQ
				memGet8(0xFFFF);
			break;
		default: //CPU_WRITE
			ret = false;
			break;
	}
	return ret;
}

static bool cpuTryTakeover()
{
	//printf("DMA Takeover tick\n");
	bool cpu_is_read = cpuDMATryHalt();
	if(cpu_is_read)
	{
		//printf("DMA Takeover done\n");
		cpu.currently_dma = true;
		//reset OAM DMA pointer
		cpu.oam_dma_ptr = 0;
		//set OAM ready to false
		cpu.oam_ready = false;
		//set dmc dummy read to true
		cpu.dmc_dma_dummyread = true;
		return true;
	}
	return false;
}

FIXNES_NOINLINE static void cpuDoDMA()
{
	if(cpu.dma & CPU_DMC_DMA)
	{
		if(cpu.currently_dma && cpu.dmc_halted)
		{
			if(cpu.dmc_dma_dummyread) //1st read always dummy read
			{
				cpu.dmc_dma_dummyread = false;
				if(!(cpu.dma&CPU_OAM_DMA) || cpu.oam_dma_pause)
				{
					cpuDMATryHalt();
					return;
				}
			}
			else if(!cpu_odd_cycle) //READ on even
			{
				uint8_t dmc_dma_val = memGet8(cpu.dmc_dma_addr);
				apuWriteDMCBuf(dmc_dma_val);
				cpu.dma &= ~CPU_DMC_DMA;
				if(!cpu.oam_halted) //done with DMA
					cpu.currently_dma = false;
				//for next dmc dma
				cpu.dmc_halt_attempt = false;
				cpu.dmc_halted = false;
				return;
			}
			else //WRITE on odd, possibly another dummy read
			{
				if(!(cpu.dma&CPU_OAM_DMA) || cpu.oam_dma_pause)
				{
					cpuDMATryHalt();
					return;
				}
			}
		}
		else
		{
			//First DMC halt attempt ALWAYS during odd (write) cycle
			//Second (or 3rd) halt attempt during any cycle
			if(cpu_odd_cycle || cpu.dmc_halt_attempt)
			{
				if(cpu.currently_dma || cpuTryTakeover())
				{
					cpu.dmc_halted = true;
					//fully ignore OAM DMA if this is out 2nd/3rd attempt
					if((cpu.dma&CPU_OAM_DMA) && cpu.dmc_halt_attempt)
						cpu.oam_dma_pause = true;
					else //was first halt attempt, possibly allows next OAM DMA cycle
						cpu.oam_dma_pause = false;
				}
				else
					cpu.dmc_halt_attempt = true;
			}
		}
	}
	if(cpu.dma&CPU_OAM_DMA)
	{
		if(cpu.currently_dma && cpu.oam_halted)
		{
			if(!cpu_odd_cycle) //READ on even
			{
				//printf("OAM DMA Read %04x\n",cpu.oam_dma_addr|cpu.oam_dma_ptr);
				cpu.oam_dma_val = memGet8(cpu.oam_dma_addr|cpu.oam_dma_ptr);
				cpu.oam_ready = true;
			}
			else //WRITE on odd
			{
				if(cpu.oam_ready)
				{
					cpu.oam_ready = false;
					//printf("OAM DMA Write %02x\n", cpu.oam_dma_val);
					memSet8(0x2004,cpu.oam_dma_val);
					cpu.oam_dma_ptr++;
					//wrapped back, done with DMA
					if(cpu.oam_dma_ptr == 0)
					{
						//printf("OAM DMA Done\n");
						cpu.dma &= ~CPU_OAM_DMA;
						if(!cpu.dmc_halted) //done with DMA
							cpu.currently_dma = false;
						cpu.oam_halted = false;
					}
				}
				else //alignment cycle
					cpuDMATryHalt();
			}
		}
		else if(cpu.currently_dma || cpuTryTakeover())
			cpu.oam_halted = true;
	}
}

/* Main CPU Interpreter */
FIXNES_ALWAYSINLINE bool cpuCycle()
{
	cpu_odd_cycle^=true;
	//printf("CPU Cycle\n");
	//do DMC and OAM DMA first
	if(cpu.dma)
	{
		cpuDoDMA();
		if(cpu.currently_dma)
			return true;
	}
	uint8_t instr, cpu_action;
	cpu_action = cpu.action_arr[cpu.arr_pos];
	cpu.arr_pos++;
	//update interrupts right before next instruction get cycle
	if(cpu_action != CPU_GET_INSTRUCTION && cpu.action_arr[cpu.arr_pos] == CPU_GET_INSTRUCTION && cpu.allow_update_irq)
		cpuCheckIrq();

	switch(cpu_action)
	{
		case CPU_GET_INSTRUCTION:
			instr = memGet8(cpu.pc);
			//if IRQ occurs end this cycle early
			if(cpuHandleIrqUpdates())
			{
				cpu.allow_update_irq = false;
				break;
			}
			else //only set allow to true if its not a BRK
				cpu.allow_update_irq = (instr != 0x00);
			cpu.action_arr = cpu_instr_arr[instr];
			cpu.arr_pos = 0;
			cpu.instr = instr;
			//printf("%04x %02x %02x %02x %02x %02x\n", cpu.pc, instr, cpu.a, cpu.x, cpu.y, cpu.p);
			cpu.pc++;
			break;
		case CPU_NULL_READ8_PC:
			memGet8(cpu.pc);
			break;
		case CPU_NULL_READ8_PC_INC:
			memGet8(cpu.pc++);
			break;
		case CPU_NULL_READ8_PC_CHK:
			memGet8(cpu.pc);
			if(cpu.needsIndFix)
			{
				cpu.pc = cpu.indVal;
				cpu.needsIndFix = false;
			}
			break;
		case CPU_NULL_READ8_PC_ACTION:
			memGet8(cpu.pc);
		cpu_action_func:
			switch(cpu.instr)
			{
				case 0x01: case 0x05: case 0x09: case 0x0D:
				case 0x11: case 0x15: case 0x1D:
					cpuORA();
					break;
				case 0x02: case 0x12: case 0x22: case 0x32:
				case 0x42: case 0x52: case 0x62: case 0x72:
				case 0x92: case 0xB2: case 0xD2: case 0xF2:
					cpuKIL();
					break;
				case 0x03: case 0x07: case 0x0F: case 0x13:
				case 0x17: case 0x1B: case 0x1F: 
					cpuSLO();
					break;
				case 0x06: case 0x0E: case 0x16: case 0x1E:
					cpuASLt();
					break; 
				case 0x0A:
					cpuASLa();
					break;
				case 0x0B: case 0x2B:
					cpuAAC();
					break; 
				case 0x18:
					cpuCLC();
					break;
				case 0x19:
					cpuORA();
					break;  
				case 0x21: case 0x25: case 0x29: case 0x2D:
				case 0x31: case 0x35: case 0x39: case 0x3D:
					cpuAND();
					break;
				case 0x23: case 0x27: case 0x2F: case 0x33:
				case 0x37: case 0x3B: case 0x3F:
					cpuRLA();
					break;
				case 0x24: case 0x2C:
					cpuBIT();
					break;
				case 0x26: case 0x2E: case 0x36: case 0x3E:
					cpuROLt();
					break;
				case 0x2A:
					cpuROLa();
					break;
				case 0x38:
					cpuSEC();
					break;
				case 0x41: case 0x45: case 0x49: case 0x4D:
				case 0x51: case 0x55: case 0x59: case 0x5D:
					cpuEOR();
					break;
				case 0x43: case 0x47: case 0x4F: case 0x53:
				case 0x57: case 0x5B: case 0x5F:
					cpuSRE();
					break;
				case 0x46: case 0x4E: case 0x56: case 0x5E:
					cpuLSRt();
					break;
				case 0x4A:
					cpuLSRa();
					break;
				case 0x4B:
					cpuASR();
					break; 
				case 0x58:
					cpuCLI();
					break;
				case 0x61: case 0x65: case 0x69: case 0x6D:
				case 0x71: case 0x75: case 0x79: case 0x7D:
					cpuADC();
					break;
				case 0x63: case 0x67: case 0x6F: case 0x73:
				case 0x77: case 0x7B: case 0x7F:
					cpuRRA();
					break;
				case 0x66: case 0x6E: case 0x76: case 0x7E:
					cpuRORt();
					break;
				case 0x6A:
					cpuRORa();
					break;
				case 0x6B:
					cpuARR();
					break; 
				case 0x78:
					cpuSEI();
					break;
				case 0x88:
					cpuDEY();
					break;
				case 0x8A:
					cpuTXA();
					break;
				case 0x8B:
					cpuXAA();
					break; 
				case 0x98:
					cpuTYA();
					break;
				case 0x9A:
					cpuTXS();
					break;  
				case 0xA0: case 0xA4: case 0xAC: case 0xB4:
				case 0xBC:
					cpuLDY();
					break;
				case 0xA1: case 0xA5: case 0xA9: case 0xAD:
				case 0xB1: case 0xB5: case 0xB9: case 0xBD:
					cpuLDA();
					break;
				case 0xA2: case 0xA6: case 0xAE: case 0xB6:
				case 0xBE:
					cpuLDX();
					break;
				case 0xA3: case 0xA7: case 0xAF: case 0xB3:
				case 0xB7: case 0xBF:
					cpuLAX();
					break;
				case 0xA8:
					cpuTAY();
					break;
				case 0xAA:
					cpuTAX();
					break;
				case 0xAB:
					cpuATX();
					break; 
				case 0xB8:
					cpuCLV();
					break;
				case 0xBA:
					cpuTSX();
					break;
				case 0xBB:
					cpuLAR();
					break; 
				case 0xC0: case 0xC4: case 0xCC:
					cpuCMPy();
					break;
				case 0xC1: case 0xC5: case 0xC9: case 0xCD:
				case 0xD1: case 0xD5: case 0xD9: case 0xDD:
					cpuCMPa();
					break;
				case 0xC3: case 0xC7: case 0xCF: case 0xD3:
				case 0xD7: case 0xDB: case 0xDF:
					cpuDCP();
					break;
				case 0xC6: case 0xCE: case 0xD6: case 0xDE:
					cpuDECt();
					break;
				case 0xC8:
					cpuINY();
					break;
				case 0xCA:
					cpuDEX();
					break;
				case 0xCB:
					cpuCMPax();
					break; 
				case 0xD8:
					cpuCLD();
					break;
				case 0xE0: case 0xE4: case 0xEC:
					cpuCMPx();
					break;
				case 0xE1: case 0xE5: case 0xE9: case 0xEB:
				case 0xED: case 0xF1: case 0xF5: case 0xF9:
				case 0xFD:
					cpuSBC();
					break;
				case 0xE6: case 0xEE: case 0xF6: case 0xFE:
					cpuINCt();
					break;
				case 0xE3: case 0xE7: case 0xEF: case 0xF3:
				case 0xF7: case 0xFB: case 0xFF:
					cpuISC();
					break;
				case 0xE8:
					cpuINX();
					break;
				case 0xF8:
					cpuSED();
					break;
				default:
					break;
			}
			break;
		case CPU_NULL_READ8_PC_ADDR_ADDX_ZP:
			memGet8(cpu.pc);
			cpu.absAddr += cpu.x;
			cpu.absAddr &= 0xFF;
			break;
		case CPU_NULL_READ8_PC_ADDR_ADDY_ZP:
			memGet8(cpu.pc);
			cpu.absAddr += cpu.y;
			cpu.absAddr &= 0xFF;
			break;
		case CPU_NULL_READ8_PC_TMP_ADDX:
			memGet8(cpu.pc);
			cpu.tmp += cpu.x;
			break;
		case CPU_NULL_READ8_PC_STACK_INC:
			memGet8(cpu.pc);
			cpu.s++;
			break;
		case CPU_NULL_READ8_PC_STACK_DEC:
			memGet8(cpu.pc);
			cpu.s--;
			break;
		case CPU_NULL_READ8_PC_STACK_DEC_SET_I:
			memGet8(cpu.pc);
			cpu.s--;
			cpu.p |= P_FLAG_IRQ_DISABLE;
			cpu.irqMask = 0;
			break;
		case CPU_NULL_READ8_PC_STACK_DEC_SET_S1_S2_I:
			memGet8(cpu.pc);
			cpu.s--;
			cpu.p |= (P_FLAG_IRQ_DISABLE | P_FLAG_S1 | P_FLAG_S2);
			cpu.irqMask = 0;
			break;
		case CPU_TMP_READ8_PC_INC:
			cpu.tmp = memGet8(cpu.pc++);
			break;
		case CPU_TMP_READ8_PC_INC_ACTION:
			cpu.tmp = memGet8(cpu.pc++);
			goto cpu_action_func;
		case CPU_TMP_READ8_PC_INC_CHECK_BCC:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!(cpu.p & P_FLAG_CARRY));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BCS:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!!(cpu.p & P_FLAG_CARRY));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BNE:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!(cpu.p & P_FLAG_ZERO));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BEQ:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!!(cpu.p & P_FLAG_ZERO));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BPL:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!(cpu.p & P_FLAG_NEGATIVE));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BMI:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!!(cpu.p & P_FLAG_NEGATIVE));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BVC:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!(cpu.p & P_FLAG_OVERFLOW));
			break;
		case CPU_TMP_READ8_PC_INC_CHECK_BVS:
			cpu.tmp = memGet8(cpu.pc++);
			cpuBranchCheck(!!(cpu.p & P_FLAG_OVERFLOW));
			break;
		case CPU_PCL_FROM_TMP_PCH_READ8_PC:
			cpu.pc = (cpu.tmp | (memGet8(cpu.pc)<<8));
			break;
		case CPU_ADDR_READ8_PC_INC:
			cpu.absAddr = memGet8(cpu.pc++);
			break;
		case CPU_ADDRL_READ8_PC_INC:
			cpu.absAddr = memGet8(cpu.pc++);
			break;
		case CPU_ADDRH_READ8_PC_INC:
			cpu.absAddr |= (memGet8(cpu.pc++)<<8);
			break;
		case CPU_ADDRH_READ8_PC_INC_ADDX:
			cpu.indVal = cpu.absAddr + cpu.x;
			cpuSetAddrIndFix();
			cpu.absAddr += cpu.x;
			cpu.absAddr &= 0xFF;
			cpu.absAddr |= (memGet8(cpu.pc++)<<8);
			cpu.indVal += (cpu.absAddr&0xFF00);
			break;
		case CPU_ADDRH_READ8_PC_INC_ADDY:
			cpu.indVal = cpu.absAddr + cpu.y;
			cpuSetAddrIndFix();
			cpu.absAddr += cpu.y;
			cpu.absAddr &= 0xFF;
			cpu.absAddr |= (memGet8(cpu.pc++)<<8);
			cpu.indVal += (cpu.absAddr&0xFF00);
			break;
		case CPU_ADDRL_READ8_TMP_INC:
			cpu.absAddr = memGet8(cpu.tmp++);
			break;
		case CPU_ADDRH_READ8_TMP:
			cpu.absAddr |= (memGet8(cpu.tmp)<<8);
			break;
		case CPU_ADDRH_READ8_TMP_ADDY:
			cpu.indVal = cpu.absAddr + cpu.y;
			cpuSetAddrIndFix();
			cpu.absAddr += cpu.y;
			cpu.absAddr &= 0xFF;
			cpu.absAddr |= (memGet8(cpu.tmp)<<8);
			cpu.indVal += (cpu.absAddr&0xFF00);
			break;
		case CPU_ADDR_READ8:
			cpu.tmp = memGet8(cpu.absAddr);
			break;
		case CPU_ADDR_READ8_CHK:
			cpu.tmp = memGet8(cpu.absAddr);
			cpuDoAddrIndFix();
			break;
		case CPU_ADDR_READ8_ACTION:
			cpu.tmp = memGet8(cpu.absAddr);
			goto cpu_action_func;
		case CPU_ADDR_READ8_ACTION_CHK:
			cpu.tmp = memGet8(cpu.absAddr);
			if(!cpuDoAddrIndFix())
			{
				//only execute extra cycle
				//if fixup is needed
				cpu.arr_pos++;
				goto cpu_action_func;
			}
			break;
		case CPU_INC_PAGE_ADDR_READ8_SET_PC:
			cpu.pc = cpu.tmp; //low cpu.pc bytes
			cpu.tmp = (cpu.absAddr & 0xFF);
			cpu.absAddr &= ~0xFF; //clear low address bytes
			//emulate 6502 jmp wrap bug 
			cpu.tmp++; //possibly FF->00 without page increase!
			cpu.absAddr |= cpu.tmp; //add back low address bytes
			cpu.pc |= (memGet8(cpu.absAddr)<<8); //high cpu.pc bytes
			break;
		case CPU_ADDR_WRITE8:
			memSet8(cpu.absAddr, cpu.tmp);
			cpuWriteTMP = false;
			break;
		case CPU_ADDR_WRITE8_A:
			memSet8(cpu.absAddr, cpu.a);
			break;
		case CPU_ADDR_WRITE8_X:
			memSet8(cpu.absAddr, cpu.x);
			break;
		case CPU_ADDR_WRITE8_Y:
			memSet8(cpu.absAddr, cpu.y);
			break;
		case CPU_ADDR_WRITE8_AX:
			memSet8(cpu.absAddr, cpu.a&cpu.x);
			break;
		case CPU_ADDR_WRITE8_AXA:
			memSet8(cpu.absAddr, cpu.a&cpu.x&(cpu.absAddr>>8));
			break;
		case CPU_ADDR_WRITE8_XAS:
			if(cpu.needsIndFix)
			{
				cpu.absAddr &= cpu.y << 8;
				cpu.needsIndFix = false;
			}
			cpu.s = cpu.a & cpu.x;
			memSet8(cpu.absAddr, cpu.a & cpu.x & ((cpu.absAddr >> 8) + 1));
			break;
		case CPU_ADDR_WRITE8_SYA:
			if(cpu.needsIndFix)
			{
				cpu.absAddr &= cpu.y << 8;
				cpu.needsIndFix = false;
			}
			memSet8(cpu.absAddr, cpu.y & ((cpu.absAddr >> 8) + 1));
			break;
		case CPU_ADDR_WRITE8_SXA:
			if(cpu.needsIndFix)
			{
				cpu.absAddr &= cpu.x << 8;
				cpu.needsIndFix = false;
			}
			memSet8(cpu.absAddr, cpu.x & ((cpu.absAddr >> 8) + 1));
			break;
		case CPU_ADDR_WRITE8_ACTION:
			memSet8(cpu.absAddr, cpu.tmp);
			cpuWriteTMP = true;
			goto cpu_action_func;
		case CPU_BRANCH_SETUP:
			cpuBranchSetup();
			memGet8(cpu.pc);
			break;
		case CPU_STACK_GET_A:
			cpuSetA(memGet8(0x100+cpu.s));
			break;
		case CPU_STACK_GET_P:
			cpu.tmp = memGet8(0x100+cpu.s);
			cpu.p &= P_FLAG_IRQ_DISABLE;
			cpu.irqMask = IRQ_MASK;
			cpu.p |= (cpu.tmp & ~P_FLAG_IRQ_DISABLE);
			//will do it for us after
			if(cpu.tmp & P_FLAG_IRQ_DISABLE)
			{
				//printf("PLP IRQ Set 1\n");
				cpu.p_irq_req = 1;
			}
			else
			{
				//printf("PLP IRQ Set 2\n");
				cpu.p_irq_req = 2; 
			}
			break;
		case CPU_STACK_GET_P_INC:
			cpu.p = memGet8(0x100+cpu.s);
			cpu.irqMask = (cpu.p & P_FLAG_IRQ_DISABLE) ? 0 : IRQ_MASK;
			cpu.s++;
			break;
		case CPU_STACK_GET_PCL_INC:
			cpu.pc &= ~0xFF;
			cpu.pc |= memGet8(0x100+cpu.s);
			cpu.s++;
			break;
		case CPU_STACK_GET_PCH:
			cpu.pc &= 0xFF;
			cpu.pc |= memGet8(0x100+cpu.s)<<8;
			break;
		case CPU_STACK_STORE_A_DEC:
			memSet8(0x100+cpu.s,cpu.a);
			cpu.s--;
			break;
		case CPU_STACK_STORE_P_DEC:
			cpu.p |= (P_FLAG_S1 | P_FLAG_S2);
			memSet8(0x100+cpu.s,cpu.p);
			cpu.s--;
			break;
		case CPU_STACK_STORE_PCH_DEC:
			memSet8(0x100+cpu.s,cpu.pc>>8);
			cpu.s--;
			break;
		case CPU_STACK_STORE_PCL_DEC:
			memSet8(0x100+cpu.s,cpu.pc&0xFF);
			cpu.s--;
			break;
		case CPU_STACK_SET_S1_S2_STORE_P_DEC_SET_I:
			cpuCheckIrq();
			cpu.p |= (P_FLAG_S1 | P_FLAG_S2);
			memSet8(0x100+cpu.s,cpu.p);
			cpu.s--;
			cpu.p |= P_FLAG_IRQ_DISABLE;
			cpu.irqMask = 0;
			break;
		case CPU_STACK_CLEAR_S1_SET_S2_STORE_P_DEC_SET_I:
			cpuCheckIrq();
			cpu.p &= ~P_FLAG_S1;
			cpu.p |= P_FLAG_S2;
			memSet8(0x100+cpu.s,cpu.p);
			cpu.s--;
			cpu.p |= P_FLAG_IRQ_DISABLE;
			cpu.irqMask = 0;
			break;
		case CPU_READ_RESETVEC_PCL:
			cpu.pc &= ~0xFF;
			cpu.pc |= memGet8(0xFFFC);
			break;
		case CPU_READ_RESETVEC_PCH:
			cpu.pc &= 0xFF;
			cpu.pc |= memGet8(0xFFFD)<<8;
			break;
		case CPU_READ_NMI_IRQ_VEC_PCL:
			cpu.pc &= ~0xFF;
			if(cpu.irq & PPU_NMI) //NMI
				cpu.pc |= memGet8(0xFFFA);
			else //IRQ
				cpu.pc |= memGet8(0xFFFE);
			break;
		case CPU_READ_NMI_IRQ_VEC_PCH:
			cpu.pc &= 0xFF;
			if(cpu.irq & PPU_NMI) //NMI
				cpu.pc |= memGet8(0xFFFB)<<8;
			else //IRQ
			{
				cpu.pc |= memGet8(0xFFFF)<<8;
				//just in case, clear if its set
				interrupt &= ~FDS_TRANSFER_IRQ;
			}
			//clear these, will get set later
			cpu.irq = 0;
			break;
		default: //should never happen
			printf("Unknown action %i\n", cpu_action);
			memDumpMainMem();
			return false;
	}
	return true;
}


/* Access for other .c files */

uint16_t cpuGetPc()
{
	return cpu.pc;
}

void cpuStartPlayNSF()
{
	//used in NSF mapper to detect play return
	uint16_t absAddr = 0x456A-1;
	memSet8(0x100+cpu.s,absAddr>>8);
	cpu.s--;
	memSet8(0x100+cpu.s,absAddr&0xFF);
	cpu.s--;
	//back up old PC and P
	cpu.pc_nsf_bak = cpu.pc;
	cpu.p_nsf_bak = cpu.p;
	cpu.pc = nsfGetPlayAddr(); //jump to play
	cpuSetStartArray();
	//printf("Playback Start at %04x\n", cpu.pc);
}

void cpuEndPlayNSF()
{
	//restore old PC and P
	cpu.pc = cpu.pc_nsf_bak;
	cpu.p = cpu.p_nsf_bak;
	cpu.irqMask = (cpu.p & P_FLAG_IRQ_DISABLE) ? 0 : IRQ_MASK;
	cpuSetStartArray();
	//printf("Playback End at %04x\n", cpu.pc);
}

void cpuInitNSF(uint16_t addr, uint8_t newA, uint8_t newX)
{
	//full reset
	cpuInit();
	ppuInit();
	memInit();
	apuInit();
	//we dont just "(re)boot" though, set new vals
	cpu.boot = false;
	cpu.reset = false;
	cpu.p |= (P_FLAG_IRQ_DISABLE | P_FLAG_S1 | P_FLAG_S2);
	cpu.irqMask = 0;
	cpu.a = newA;
	cpu.x = newX;
	cpu.y = 0;
	cpu.s = 0xFD;
	//prepare APU regs
	apuSetReg15(0x15,0xF);
	apuSetReg17(0x17,0x40);
	//used in NSF mapper to detect init return
	uint16_t initRet = 0x4567-1;
	memSet8(0x100+cpu.s,initRet>>8);
	cpu.s--;
	memSet8(0x100+cpu.s,initRet&0xFF);
	cpu.s--;
	cpu.pc = addr;
	//printf("Init at %04x\n", addr);
}

void cpuSoftReset()
{
	cpu.boot = false; //soft-reset
	cpu.reset = true;
}

void cpuDoOAM_DMA(uint16_t addr, uint8_t val)
{
	(void)addr;
	cpu.dma |= CPU_OAM_DMA;
	cpu.oam_dma_addr = (val<<8);
}

void cpuDoDMC_DMA(uint16_t addr)
{
	cpu.dma |= CPU_DMC_DMA;
	cpu.dmc_dma_addr = addr|0x8000;
}

bool cpuInDMC_DMA()
{
	return !!(cpu.dma&CPU_DMC_DMA);
}
