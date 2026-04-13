/*
 * Copyright (C) 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t chrRAM[0x2000];
	uint32_t curPRGBank0;
	uint32_t curPRGBank1;
	uint32_t curPRGBank2;
	uint32_t lastPRGBank;
	uint32_t CHRBank[8];
	uint8_t *chrROMBank0Ptr, *chrROMBank1Ptr,
			*chrROMBank2Ptr, *chrROMBank3Ptr,
			*chrROMBank4Ptr, *chrROMBank5Ptr,
			*chrROMBank6Ptr, *chrROMBank7Ptr;
	uint8_t writeAddr;
	uint8_t chr_bank_flip;
	bool chr_mode_full;
	bool prg_bank_flip;
	uint8_t irqCtr;
	uint8_t irqDelay;
	uint8_t irqPrescaler;
	bool irqReqReset;
	bool irqEnable;
	bool irqCyclemode;
	uint8_t irqReloadVal;
	uint16_t prevAddr;
} rambo1;

void rambo1SetPrgROMBankPtr()
{
	if(rambo1.prg_bank_flip)
	{
		prg8setBank0(rambo1.curPRGBank2);
		prg8setBank1(rambo1.curPRGBank0);
		prg8setBank2(rambo1.curPRGBank1);
	}
	else
	{
		prg8setBank0(rambo1.curPRGBank0);
		prg8setBank1(rambo1.curPRGBank1);
		prg8setBank2(rambo1.curPRGBank2);
	}
	prg8setBank3(rambo1.lastPRGBank);
}

void rambo1SetChrROMBankPtr()
{
	if(rambo1.chr_mode_full)
	{
		rambo1.chrROMBank0Ptr = rambo1.chrROM+((rambo1.CHRBank[0^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank1Ptr = rambo1.chrROM+((rambo1.CHRBank[1^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank2Ptr = rambo1.chrROM+((rambo1.CHRBank[2^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank3Ptr = rambo1.chrROM+((rambo1.CHRBank[3^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank4Ptr = rambo1.chrROM+((rambo1.CHRBank[4^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank5Ptr = rambo1.chrROM+((rambo1.CHRBank[5^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank6Ptr = rambo1.chrROM+((rambo1.CHRBank[6^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank7Ptr = rambo1.chrROM+((rambo1.CHRBank[7^rambo1.chr_bank_flip]<<10)&rambo1.chrROMand);
	}
	else if(rambo1.chr_bank_flip)
	{
		rambo1.chrROMBank0Ptr = rambo1.chrROM+((rambo1.CHRBank[4]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank1Ptr = rambo1.chrROM+((rambo1.CHRBank[5]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank2Ptr = rambo1.chrROM+((rambo1.CHRBank[6]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank3Ptr = rambo1.chrROM+((rambo1.CHRBank[7]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank4Ptr = rambo1.chrROM+((((rambo1.CHRBank[0])&0xFE)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank5Ptr = rambo1.chrROM+((((rambo1.CHRBank[0])|0x01)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank6Ptr = rambo1.chrROM+((((rambo1.CHRBank[2])&0xFE)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank7Ptr = rambo1.chrROM+((((rambo1.CHRBank[2])|0x01)<<10)&rambo1.chrROMand);
	}
	else
	{
		rambo1.chrROMBank0Ptr = rambo1.chrROM+((((rambo1.CHRBank[0])&0xFE)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank1Ptr = rambo1.chrROM+((((rambo1.CHRBank[0])|0x01)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank2Ptr = rambo1.chrROM+((((rambo1.CHRBank[2])&0xFE)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank3Ptr = rambo1.chrROM+((((rambo1.CHRBank[2])|0x01)<<10)&rambo1.chrROMand);
		rambo1.chrROMBank4Ptr = rambo1.chrROM+((rambo1.CHRBank[4]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank5Ptr = rambo1.chrROM+((rambo1.CHRBank[5]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank6Ptr = rambo1.chrROM+((rambo1.CHRBank[6]<<10)&rambo1.chrROMand);
		rambo1.chrROMBank7Ptr = rambo1.chrROM+((rambo1.CHRBank[7]<<10)&rambo1.chrROMand);
	}
}

void rambo1init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg8init(prgROMin,prgROMsizeIn);
	rambo1.curPRGBank0 = 0;
	rambo1.curPRGBank1 = 0x2000;
	rambo1.curPRGBank2 = 0x4000;
	rambo1.lastPRGBank = (prgROMsizeIn - 0x2000);
	rambo1.prg_bank_flip = false;
	rambo1SetPrgROMBankPtr();
	if(chrROMin && chrROMsizeIn)
	{
		rambo1.chrROM = chrROMin;
		rambo1.chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
	{
		rambo1.chrROM = rambo1.chrRAM;
		rambo1.chrROMand = 0x1FFF;
	}
	memset(rambo1.CHRBank, 0, 8*sizeof(uint32_t));
	rambo1.chr_bank_flip = 0;
	rambo1.chr_mode_full = false;
	rambo1SetChrROMBankPtr();
	rambo1.writeAddr = 0;
	rambo1.irqCtr = 0;
	rambo1.irqDelay = 0;
	rambo1.irqPrescaler = 4;
	rambo1.irqReqReset = false;
	rambo1.irqEnable = false;
	rambo1.irqCyclemode = false;
	rambo1.irqReloadVal = 0xFF;
	printf("RAMBO-1 inited\n");
}

static uint16_t m158nt[8];
static void m158refreshNT() //follows rambo1SetChrROMBankPtr logic
{
	if(rambo1.chr_mode_full)
		ppuSetNameTblCustom(m158nt[0^rambo1.chr_bank_flip],m158nt[1^rambo1.chr_bank_flip],m158nt[2^rambo1.chr_bank_flip],m158nt[3^rambo1.chr_bank_flip]);
	else if(rambo1.chr_bank_flip)
		ppuSetNameTblCustom(m158nt[4],m158nt[5],m158nt[6],m158nt[7]);
	else
		ppuSetNameTblCustom(m158nt[0],m158nt[0],m158nt[2],m158nt[2]);
}
void m158init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	rambo1init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	memset(m158nt,0,8*sizeof(uint16_t));
	m158refreshNT();
	printf("Mapper 158 (Mapper 64 Variant) inited\n");
}

void rambo1setParams8000(uint16_t addr, uint8_t val)
{
	(void)addr;
	rambo1.chr_bank_flip = ((val&(1<<7)) != 0) ? 4 : 0;
	rambo1.chr_mode_full = ((val&(1<<5)) != 0);
	rambo1SetChrROMBankPtr();
	rambo1.prg_bank_flip = ((val&(1<<6)) != 0);
	rambo1SetPrgROMBankPtr();
	rambo1.writeAddr = (val&0xF);
}
void rambo1setParams8001(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(rambo1.writeAddr)
	{
		case 0:
			rambo1.CHRBank[0] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 1:
			rambo1.CHRBank[2] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 2:
			rambo1.CHRBank[4] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 3:
			rambo1.CHRBank[5] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 4:
			rambo1.CHRBank[6] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 5:
			rambo1.CHRBank[7] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 6:
			rambo1.curPRGBank0 = (val<<13);
			rambo1SetPrgROMBankPtr();
			break;
		case 7:
			rambo1.curPRGBank1 = (val<<13);
			rambo1SetPrgROMBankPtr();
			break;
		case 8:
			rambo1.CHRBank[1] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 9:
			rambo1.CHRBank[3] = val;
			rambo1SetChrROMBankPtr();
			break;
		case 0xF:
			rambo1.curPRGBank2 = (val<<13);
			rambo1SetPrgROMBankPtr();
			break;
		default:
			break;
	}
}
void rambo1setParamsA000(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((val&1) == 0)
	{
		//printf("Vertical mode\n");
		ppuSetNameTblVertical();
	}
	else
	{
		//printf("Horizontal mode\n");
		ppuSetNameTblHorizontal();
	}
}
void rambo1setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	//printf("Reload value set to %i\n", val);
	rambo1.irqReloadVal = val;
}
void rambo1setParamsC001(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	//printf("Reset counter\n");
	rambo1.irqReqReset = true;
	rambo1.irqPrescaler = 4;
	rambo1.irqCyclemode = ((val&1) != 0);
}
extern uint8_t interrupt;
void rambo1setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	rambo1.irqEnable = false;
	rambo1.irqDelay = 0;
	interrupt &= ~MAPPER_IRQ;
	//printf("Interrupt disabled\n");
}
void rambo1setParamsE001(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	rambo1.irqEnable = true;
	rambo1.irqDelay = 0;
	interrupt &= ~MAPPER_IRQ;
	//printf("Interrupt enabled\n");
}

void rambo1initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, rambo1setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, rambo1setParams8001);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, rambo1setParamsA000);
	//  AXX1 seems to be not assigned
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, rambo1setParamsC000);
	else if(proc_addr == 0xC001) memInitMapperSetPointer(ori_addr, rambo1setParamsC001);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, rambo1setParamsE000);
	else if(proc_addr == 0xE001) memInitMapperSetPointer(ori_addr, rambo1setParamsE001);
}

static void m158setParams8000(uint16_t addr, uint8_t val)
{
	//call original function
	rambo1setParams8000(addr, val);
	//update nametable vals
	m158refreshNT();
}
static void m158setParams8001(uint16_t addr, uint8_t val)
{
	//steal upper chr bit
	switch(rambo1.writeAddr)
	{
		case 0:
			m158nt[0] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 1:
			m158nt[2] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 2:
			m158nt[4] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 3:
			m158nt[5] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 4:
			m158nt[6] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 5:
			m158nt[7] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 8:
			m158nt[1] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		case 9:
			m158nt[3] = (val&0x80)?0x400:0;
			rambo1setParams8001(addr, val&0x7F);
			break;
		default: //prg bank sets, call original function normally
			rambo1setParams8001(addr, val);
			break;
	}
	//update nametable vals
	m158refreshNT();
}
void m158initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	//special nametable regs
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m158setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m158setParams8001);
	else if(proc_addr == 0xA000) return; //Bypass standard mirroring controls
	else //do normal rambo1 sets
		rambo1initSet8(ori_addr);
}

void rambo1ctrcycle()
{
	if(rambo1.irqReqReset)
	{
		rambo1.irqReqReset = false;
		rambo1.irqCtr = rambo1.irqReloadVal;
		if(rambo1.irqReloadVal) rambo1.irqCtr |= 1;
	}
	else if(rambo1.irqCtr == 0)
		rambo1.irqCtr = rambo1.irqReloadVal;
	else
		rambo1.irqCtr--;
	if(rambo1.irqCtr == 0 && rambo1.irqEnable)
		rambo1.irqDelay = 6; //start countdown
}

void rambo1clock(uint16_t addr)
{
	if((addr & 0x1000) && !(rambo1.prevAddr & 0x1000) && !rambo1.irqCyclemode)
		rambo1ctrcycle();
	rambo1.prevAddr = addr;
}

static void rambo1chrSetRAM0(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank0Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM1(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank1Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM2(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank2Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM3(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank3Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM4(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank4Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM5(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank5Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM6(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank6Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}
static void rambo1chrSetRAM7(uint16_t addr, uint8_t val)
{	//remember, rambo1.chrROM = rambo1.chrRAM
	rambo1.chrROMBank7Ptr[addr&0x3FF] = val;
	rambo1clock(addr);
}

static void rambo1chrSetClock(uint16_t addr, uint8_t val)
{
	(void)val;
	rambo1clock(addr);
}

static uint8_t rambo1chrGetROM0(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank0Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM1(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank1Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM2(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank2Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM3(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank3Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM4(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank4Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM5(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank5Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM6(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank6Ptr[addr&0x3FF];
}
static uint8_t rambo1chrGetROM7(uint16_t addr)
{
	rambo1clock(addr);
	return rambo1.chrROMBank7Ptr[addr&0x3FF];
}

void rambo1initPPUGet8(uint16_t addr)
{
	if(addr >= 0x2000)
		return;
	if(addr < 0x400) memInitMapperPPUGetPointer(addr, rambo1chrGetROM0);
	else if(addr < 0x800) memInitMapperPPUGetPointer(addr, rambo1chrGetROM1);
	else if(addr < 0xC00) memInitMapperPPUGetPointer(addr, rambo1chrGetROM2);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, rambo1chrGetROM3);
	else if(addr < 0x1400) memInitMapperPPUGetPointer(addr, rambo1chrGetROM4);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, rambo1chrGetROM5);
	else if(addr < 0x1C00) memInitMapperPPUGetPointer(addr, rambo1chrGetROM6);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, rambo1chrGetROM7);
}

void rambo1initPPUSet8(uint16_t addr)
{
	if(addr >= 0x2000)
		return;
	if(rambo1.chrROM == rambo1.chrRAM) //Writable
	{
		if(addr < 0x400) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM0);
		else if(addr < 0x800) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM1);
		else if(addr < 0xC00) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM2);
		else if(addr < 0x1000) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM3);
		else if(addr < 0x1400) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM4);
		else if(addr < 0x1800) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM5);
		else if(addr < 0x1C00) memInitMapperPPUSetPointer(addr, rambo1chrSetRAM6);
		else memInitMapperPPUSetPointer(addr, rambo1chrSetRAM7);
	}
	else
		memInitMapperPPUSetPointer(addr, rambo1chrSetClock);
}

void rambo1cycle()
{
	if(rambo1.irqDelay && !(--rambo1.irqDelay))
	{
		interrupt |= MAPPER_IRQ;
	}
	else if(rambo1.irqCyclemode && !(--rambo1.irqPrescaler))
	{
		rambo1.irqPrescaler = 4;
		rambo1ctrcycle();
	}
}
