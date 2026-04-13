/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	uint8_t *prgRAM;
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t *CHRNT0Ptr, *CHRNT1Ptr;
	uint8_t VRAM[0x800];
	uint8_t *VRAMNT0Ptr, *VRAMNT1Ptr;
	uint8_t *VRAMBank0Ptr, *VRAMBank1Ptr,
					*VRAMBank2Ptr, *VRAMBank3Ptr;
	uint8_t VRAMBank[4];
	bool enableRAM;
	bool chrVRAM;
} s4;

static void s4updateVRAMBankPtr()
{
	uint8_t *NT0Ptr = s4.chrVRAM ? s4.CHRNT0Ptr : s4.VRAMNT0Ptr;
	uint8_t *NT1Ptr = s4.chrVRAM ? s4.CHRNT1Ptr : s4.VRAMNT1Ptr;
	s4.VRAMBank0Ptr = s4.VRAMBank[0] ? NT1Ptr : NT0Ptr;
	s4.VRAMBank1Ptr = s4.VRAMBank[1] ? NT1Ptr : NT0Ptr;
	s4.VRAMBank2Ptr = s4.VRAMBank[2] ? NT1Ptr : NT0Ptr;
	s4.VRAMBank3Ptr = s4.VRAMBank[3] ? NT1Ptr : NT0Ptr;
}

void s4init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	s4.prgRAM = prgRAMin;
	(void)prgRAMsizeIn;
	if(chrROMin && chrROMsizeIn)
	{
		s4.chrROM = chrROMin;
		s4.chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
		printf("s4 missing chr rom??? this may crash\n");
	chr2init(chrROMin,chrROMsizeIn);
	s4.CHRNT0Ptr = s4.CHRNT1Ptr = chrROMin;
	s4.VRAMNT0Ptr = s4.VRAM, s4.VRAMNT1Ptr = s4.VRAM+0x400;
	s4.enableRAM = false;
	s4.chrVRAM = false;
	s4.VRAMBank[0] = s4.VRAMBank[1] = s4.VRAMBank[2] = s4.VRAMBank[3] = 0;
	s4updateVRAMBankPtr();
	printf("Sunsoft-4 inited\n");
}

extern uint8_t memLastVal;
static uint8_t s4getRAM(uint16_t addr)
{
	if(s4.enableRAM)
		return s4.prgRAM[addr&0x1FFF];
	return memLastVal;
}
void s4initGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperGetPointer(addr, s4getRAM);
	else
		prg16initGet8(addr);
}

static void s4setRAM(uint16_t addr, uint8_t val)
{
	if(s4.enableRAM)
		s4.prgRAM[addr&0x1FFF] = val;
}
static void s4setParams8000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank0(val<<11); }
static void s4setParams9000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank1(val<<11); }
static void s4setParamsA000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank2(val<<11); }
static void s4setParamsB000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank3(val<<11); }

static void s4setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	s4.CHRNT0Ptr = s4.chrROM+((((val&0x7F)|0x80)<<10)&s4.chrROMand);
	s4updateVRAMBankPtr();
}

static void s4setParamsD000(uint16_t addr, uint8_t val)
{
	(void)addr;
	s4.CHRNT1Ptr = s4.chrROM+((((val&0x7F)|0x80)<<10)&s4.chrROMand);
	s4updateVRAMBankPtr();
}

static void s4setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(val&3)
	{
		case 0:
			s4.VRAMBank[0] = 0; s4.VRAMBank[1] = 1;
			s4.VRAMBank[2] = 0; s4.VRAMBank[3] = 1;
			break;
		case 1:
			s4.VRAMBank[0] = 0; s4.VRAMBank[1] = 0;
			s4.VRAMBank[2] = 1; s4.VRAMBank[3] = 1;
			break;
		case 2:
			s4.VRAMBank[0] = 0; s4.VRAMBank[1] = 0;
			s4.VRAMBank[2] = 0; s4.VRAMBank[3] = 0;
			break;
		case 3:
			s4.VRAMBank[0] = 1; s4.VRAMBank[1] = 1;
			s4.VRAMBank[2] = 1; s4.VRAMBank[3] = 1;
			break;
	}
	s4.chrVRAM = !!(val&0x10);
	s4updateVRAMBankPtr();
}

static void s4setParamsF000(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val&0xF)<<14);
	s4.enableRAM = !!(val&0x10);
}

void s4initSet8(uint16_t ori_addr)
{
	if(ori_addr >= 0x6000 && ori_addr < 0x8000)
		memInitMapperSetPointer(ori_addr, s4setRAM);
	else if(ori_addr >= 0x8000)
	{
		uint16_t proc_addr = ori_addr&0xF000;
		if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, s4setParams8000);
		else if(proc_addr == 0x9000) memInitMapperSetPointer(ori_addr, s4setParams9000);
		else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, s4setParamsA000);
		else if(proc_addr == 0xB000) memInitMapperSetPointer(ori_addr, s4setParamsB000);
		else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, s4setParamsC000);
		else if(proc_addr == 0xD000) memInitMapperSetPointer(ori_addr, s4setParamsD000);
		else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, s4setParamsE000);
		else if(proc_addr == 0xF000) memInitMapperSetPointer(ori_addr, s4setParamsF000);
	}
}

static uint8_t s4getVRAMBank0(uint16_t addr) { return s4.VRAMBank0Ptr[addr&0x3FF]; }
static uint8_t s4getVRAMBank1(uint16_t addr) { return s4.VRAMBank1Ptr[addr&0x3FF]; }
static uint8_t s4getVRAMBank2(uint16_t addr) { return s4.VRAMBank2Ptr[addr&0x3FF]; }
static uint8_t s4getVRAMBank3(uint16_t addr) { return s4.VRAMBank3Ptr[addr&0x3FF]; }

void s4initPPUGet8(uint16_t addr)
{
	if(addr < 0x2000)
		chr2initPPUGet8(addr);
	else
	{
		if(addr < 0x2400) memInitMapperPPUGetPointer(addr, s4getVRAMBank0);
		else if(addr < 0x2800) memInitMapperPPUGetPointer(addr, s4getVRAMBank1);
		else if(addr < 0x2C00) memInitMapperPPUGetPointer(addr, s4getVRAMBank2);
		else if(addr < 0x3000) memInitMapperPPUGetPointer(addr, s4getVRAMBank3);
		else if(addr < 0x3400) memInitMapperPPUGetPointer(addr, s4getVRAMBank0);
		else if(addr < 0x3800) memInitMapperPPUGetPointer(addr, s4getVRAMBank1);
		else if(addr < 0x3C00) memInitMapperPPUGetPointer(addr, s4getVRAMBank2);
		else if(addr < 0x3F00) memInitMapperPPUGetPointer(addr, s4getVRAMBank3);
	}
}

static void s4setVRAMBank0(uint16_t addr, uint8_t val) { if(!s4.chrVRAM) s4.VRAMBank0Ptr[addr&0x3FF] = val; }
static void s4setVRAMBank1(uint16_t addr, uint8_t val) { if(!s4.chrVRAM) s4.VRAMBank1Ptr[addr&0x3FF] = val; }
static void s4setVRAMBank2(uint16_t addr, uint8_t val) { if(!s4.chrVRAM) s4.VRAMBank2Ptr[addr&0x3FF] = val; }
static void s4setVRAMBank3(uint16_t addr, uint8_t val) { if(!s4.chrVRAM) s4.VRAMBank3Ptr[addr&0x3FF] = val; }

void s4initPPUSet8(uint16_t addr)
{
	if(addr < 0x2000)
		chr2initPPUSet8(addr);
	else
	{
		if(addr < 0x2400) memInitMapperPPUSetPointer(addr, s4setVRAMBank0);
		else if(addr < 0x2800) memInitMapperPPUSetPointer(addr, s4setVRAMBank1);
		else if(addr < 0x2C00) memInitMapperPPUSetPointer(addr, s4setVRAMBank2);
		else if(addr < 0x3000) memInitMapperPPUSetPointer(addr, s4setVRAMBank3);
		else if(addr < 0x3400) memInitMapperPPUSetPointer(addr, s4setVRAMBank0);
		else if(addr < 0x3800) memInitMapperPPUSetPointer(addr, s4setVRAMBank1);
		else if(addr < 0x3C00) memInitMapperPPUSetPointer(addr, s4setVRAMBank2);
		else if(addr < 0x3F00) memInitMapperPPUSetPointer(addr, s4setVRAMBank3);
	}
}
