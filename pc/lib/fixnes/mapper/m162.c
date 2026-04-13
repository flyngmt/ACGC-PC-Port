/*
 * Copyright (C) 2020 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "../apu.h"
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/m162.h"
#include "../mapper_h/common.h"

//implementation of the major code based on info from http://forums.nesdev.com/viewtopic.php?f=3&t=18000

static struct {
	bool usesPrgRAM;
	uint8_t prgBank;
	uint8_t prgBit;
	uint8_t prgMode;
	uint8_t VRAM[0x800];
	uint8_t *VRAMBankPtr[4];
	uint8_t chrRAM[0x2000];
	uint8_t *CHRBankPtr[2];
	bool chrUseNTBit;
	bool sprUseUpper;
	uint8_t NTBit;
	uint8_t reg[4];
} m162;

static struct {
	uint8_t bit5XXX;
	uint8_t reg5101;
} m163;

extern uint8_t emuInitialNT;
static void m162_SetInitialNT()
{
	if(emuInitialNT == NT_VERTICAL)
	{
		m162.VRAMBankPtr[0] = m162.VRAM+0x000; m162.VRAMBankPtr[1] = m162.VRAM+0x400;
		m162.VRAMBankPtr[2] = m162.VRAM+0x000; m162.VRAMBankPtr[3] = m162.VRAM+0x400;
	}
	else
	{
		if(emuInitialNT != NT_HORIZONTAL)
			printf("Unknown Initial Nametable, guessing horizontal\n");
		m162.VRAMBankPtr[0] = m162.VRAM+0x000; m162.VRAMBankPtr[1] = m162.VRAM+0x000;
		m162.VRAMBankPtr[2] = m162.VRAM+0x400; m162.VRAMBankPtr[3] = m162.VRAM+0x400;
	}
}

static void m162_setPrgBank()
{
	if(m162.prgMode == 4)
		prg32setBank0((m162.prgBank|m162.prgBit)<<15);
	else
		prg32setBank0(m162.prgBank<<15);
}

void m162_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)chrROMin; (void)chrROMsizeIn;
	prg32init(prgROMin,prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		m162.usesPrgRAM = true;
	}
	else
		m162.usesPrgRAM = false;
	memset(m162.VRAM,0,0x800);
	m162_SetInitialNT();
	memset(m162.chrRAM,0,0x2000);
	m162.CHRBankPtr[0] = m162.chrRAM+0x0000;
	m162.CHRBankPtr[1] = m162.chrRAM+0x1000;
	m162.NTBit = 0;
	m162.chrUseNTBit = false;
	m162.sprUseUpper = false;
	m162_reset(); //sets up prg regs
	printf("Mapper 162 inited\n");
}

void m163_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m162_init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m163_reset(); //clears out protection regs
	printf("Mapper 163 protection regs inited\n");
}


void m162_initGet8(uint16_t addr)
{
	if(m162.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg32initGet8(addr);
}

static uint8_t m163_getSecurity5XXX(uint16_t addr) { (void)addr; return m163.bit5XXX; }

void m163_initGet8(uint16_t ori_addr)
{
	if(ori_addr >= 0x5000 && ori_addr < 0x6000) //security reg of 163
		memInitMapperGetPointer(ori_addr, m163_getSecurity5XXX);
	else //rest is identical to 162
		m162_initGet8(ori_addr);
}


static uint8_t m164_getSecurity5XXX(uint16_t addr) { (void)addr; return m162.reg[1]&4; }

void m164_initGet8(uint16_t ori_addr)
{
	if(ori_addr >= 0x5000 && ori_addr < 0x6000) //security reg of 164
		memInitMapperGetPointer(ori_addr, m164_getSecurity5XXX);
	else //rest is identical to 162
		m162_initGet8(ori_addr);
}


static void m162_setParams5000(uint16_t addr, uint8_t val)
{
	(void)addr;
	m162.reg[0] = val;
	m162.prgBank &= ~0xF;
	m162.prgBank |= val&0xF;
	m162_setPrgBank();
	m162.chrUseNTBit = (val&0x80) != 0;
}

static void m162_setParams5100(uint16_t addr, uint8_t val)
{
	(void)addr;
	m162.reg[1] = val;
	m162.prgBit = (val&2) ? 1 : 0;
	m162_setPrgBank();
}

static void m162_setParams5200(uint16_t addr, uint8_t val)
{
	(void)addr;
	m162.reg[2] = val;
	m162.prgBank &= 0xF;
	m162.prgBank |= (val&3)<<4;
	m162_setPrgBank();
	m162.sprUseUpper = (val&8) != 0;
}

static void m162_setParams5300(uint16_t addr, uint8_t val)
{
	(void)addr;
	m162.reg[3] = val;
	m162.prgMode = val&7;
	m162_setPrgBank();
}

static void m162_commonSet8(uint16_t ori_addr, uint16_t proc_addr)
{
	if(m162.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(proc_addr == 0x5000) memInitMapperSetPointer(ori_addr, m162_setParams5000);
	else if(proc_addr == 0x5100) memInitMapperSetPointer(ori_addr, m162_setParams5100);
	else if(proc_addr == 0x5200) memInitMapperSetPointer(ori_addr, m162_setParams5200);
	else if(proc_addr == 0x5300) memInitMapperSetPointer(ori_addr, m162_setParams5300);
}

void m162_initSet8(uint16_t ori_addr)
{
	//basic set, just some ram and a few regs
	uint16_t proc_addr = ori_addr&0x7300;
	m162_commonSet8(ori_addr, proc_addr);
}

static void m163_setParams5101(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((m163.reg5101&1) && val == 0)
		m163.bit5XXX ^= 4;
	m163.reg5101 = val;
}

void m163_initSet8(uint16_t addr)
{
	if(addr == 0x5101) //security reg of 163 at 5101
		memInitMapperSetPointer(addr, m163_setParams5101);
	else //rest is identical to 162
		m162_initSet8(addr);
}

void m164_initSet8(uint16_t ori_addr)
{
	//only difference to 162 is A8 and A9 lines
	uint16_t proc_addr = (ori_addr&0x7000) | ((ori_addr>>1)&0x0100) | ((ori_addr<<1)&0x0200);
	m162_commonSet8(ori_addr, proc_addr);
}	


static uint8_t m162_CHRGetBank0(uint16_t addr)
{
	if(m162.chrUseNTBit)
	{
		if(mapperChrMode == 1 && m162.sprUseUpper) // sprite
			return m162.CHRBankPtr[1][addr&0xFFF];
		// BG
		return m162.CHRBankPtr[m162.NTBit][addr&0xFFF];
	}
	//normal operation
	return m162.CHRBankPtr[0][addr&0xFFF];
}
static uint8_t m162_CHRGetBank1(uint16_t addr)
{
	if(m162.chrUseNTBit)
	{
		if(mapperChrMode == 1 && m162.sprUseUpper) // sprite
			return m162.CHRBankPtr[1][addr&0xFFF];
		// BG
		return m162.CHRBankPtr[m162.NTBit][addr&0xFFF];
	}
	//normal operation
	return m162.CHRBankPtr[1][addr&0xFFF];
}

static uint8_t m162_VRAMGetBank0_NT(uint16_t addr)
{
	m162.NTBit = (addr&0x200)>>9;
	return m162.VRAMBankPtr[0][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank0_AT(uint16_t addr)
{
	return m162.VRAMBankPtr[0][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank1_NT(uint16_t addr)
{
	m162.NTBit = (addr&0x200)>>9;
	return m162.VRAMBankPtr[1][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank1_AT(uint16_t addr)
{
	return m162.VRAMBankPtr[1][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank2_NT(uint16_t addr)
{
	m162.NTBit = (addr&0x200)>>9;
	return m162.VRAMBankPtr[2][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank2_AT(uint16_t addr)
{
	return m162.VRAMBankPtr[2][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank3_NT(uint16_t addr)
{
	m162.NTBit = (addr&0x200)>>9;
	return m162.VRAMBankPtr[3][addr&0x3FF];
}
static uint8_t m162_VRAMGetBank3_AT(uint16_t addr)
{
	return m162.VRAMBankPtr[3][addr&0x3FF];
}
void m162_initPPUGet8(uint16_t addr)
{
	if(addr < 0x1000)
		memInitMapperPPUGetPointer(addr, m162_CHRGetBank0);
	else if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, m162_CHRGetBank1);
	else if(addr < 0x23C0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank0_NT);
	else if(addr < 0x2400)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank0_AT);
	else if(addr < 0x27C0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank1_NT);
	else if(addr < 0x2800)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank1_AT);
	else if(addr < 0x2BC0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank2_NT);
	else if(addr < 0x2C00)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank2_AT);
	else if(addr < 0x2FC0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank3_NT);
	else if(addr < 0x3000)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank3_AT);
	else if(addr < 0x33C0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank0_NT);
	else if(addr < 0x3400)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank0_AT);
	else if(addr < 0x37C0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank1_NT);
	else if(addr < 0x3800)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank1_AT);
	else if(addr < 0x3BC0)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank2_NT);
	else if(addr < 0x3C00)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank2_AT);
	else if(addr < 0x3F00)
		memInitMapperPPUGetPointer(addr, m162_VRAMGetBank3_NT);
}

static void m162_CHRSetBank0(uint16_t addr, uint8_t val)
{
	m162.CHRBankPtr[0][addr&0xFFF] = val;
}
static void m162_CHRSetBank1(uint16_t addr, uint8_t val)
{
	m162.CHRBankPtr[1][addr&0xFFF] = val;
}

static void m162_VRAMSetBank0(uint16_t addr, uint8_t val)
{
	m162.VRAMBankPtr[0][addr&0x3FF] = val;
}
static void m162_VRAMSetBank1(uint16_t addr, uint8_t val)
{
	m162.VRAMBankPtr[1][addr&0x3FF] = val;
}
static void m162_VRAMSetBank2(uint16_t addr, uint8_t val)
{
	m162.VRAMBankPtr[2][addr&0x3FF] = val;
}
static void m162_VRAMSetBank3(uint16_t addr, uint8_t val)
{
	m162.VRAMBankPtr[3][addr&0x3FF] = val;
}
void m162_initPPUSet8(uint16_t addr)
{
	if(addr < 0x1000)
		memInitMapperPPUSetPointer(addr, m162_CHRSetBank0);
	else if(addr < 0x2000)
		memInitMapperPPUSetPointer(addr, m162_CHRSetBank1);
	else if(addr < 0x2400)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank0);
	else if(addr < 0x2800)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank1);
	else if(addr < 0x2C00)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank2);
	else if(addr < 0x3000)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank3);
	else if(addr < 0x3400)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank0);
	else if(addr < 0x3800)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank1);
	else if(addr < 0x3C00)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank2);
	else if(addr < 0x3F00)
		memInitMapperPPUSetPointer(addr, m162_VRAMSetBank3);
}


void m162_reset()
{
	//copies of regs at 5000-5300
	m162.reg[0] = m162.reg[1] = m162.reg[2] = m162.reg[3] = 0;
	//basic prg setup
	m162.prgBank = 3;
	m162.prgBit = 0;
	m162.prgMode = 7;
	m162_setPrgBank();
}

void m163_reset()
{
	//common reset
	m162_reset();
	//starts at 1
	m163.reg5101 = 1;
	//bit 2 is set
	m163.bit5XXX = 4;
}
